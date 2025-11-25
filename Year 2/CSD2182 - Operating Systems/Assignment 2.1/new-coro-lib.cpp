/**
 * @file new-coro-lib.cpp
 * @brief Implementation of a coroutine library providing thread management and scheduling functionality
 * @author Original Implementation Team
 * @date 2024
 */

#include <map>            
#include <queue>          
#include <stack>          
#include <cstdlib>        
#include <ucontext.h>

#ifdef DEBUG
#include <iostream>
#endif
#include "new-coro-lib.h"
#include "new-coro-helper.h"

/**
 * @namespace CORO 
 * @brief Contains all coroutine-related functionality including thread management and scheduling
 *
 * This namespace encapsulates the entire coroutine implementation, providing thread
 * creation, management, scheduling, and inter-thread communication mechanisms.
 */
namespace CORO
{
  /** @brief Global counter for total number of threads created */
  extern ThreadID TotalID;
  /** @brief ID of the currently executing thread */
  extern ThreadID CurrentID;
  /** @brief ID of the thread to swap back to */
  extern ThreadID SwapbackID;
    
  /** @brief Main container for all thread control blocks */
  extern ThreadList threadList;
  
  /** @brief Queue of threads that are ready to execute */
  extern std::queue<unsigned> readyThreads;
  /** @brief Queue of newly created threads awaiting first execution */
  extern std::queue<unsigned> newThreads;
  /** @brief Maps waiting threads to the threads they're waiting for
   *  @details Key: ID of thread being waited for, Value: ID of waiting thread
   */
  extern std::map<unsigned, unsigned> waitThreads;
  /** @brief Maps thread relationships for pull/push operations
   *  @details Key: Thread ID, Value: Pointer to shared data between threads
   */
  extern std::map<unsigned, void *> pullpushThreads;

    /**
     * @brief Constructs a new Thread Control Block (TCB)
     * @param id Unique identifier for the thread
     * @param func Function pointer to the thread's execution routine
     * @param arg Arguments to be passed to the thread function
     * @param parentID ID of the parent/creator thread
     * @throw std::bad_alloc If memory allocation for the stack fails
     * @throw std::runtime_error If context creation fails
     */
    TCB::TCB(ThreadID id, FnPtr func, void* arg, ThreadID parentID)
    : ID(id), PullerID(parentID), state(ThreadState::NEW), stack(nullptr), ctx(new ucontext_t), 
      functionPtr(func), param(arg), returnVal(nullptr)
    {
        void* stack = new char[SIZE];
        if (stack == nullptr) {
            throw std::bad_alloc();
        }

        // Set up the stack and context properties
        ctx->uc_stack.ss_sp = stack;
        ctx->uc_stack.ss_size = SIZE;
        ctx->uc_link = nullptr;

        // Establish the context and arguments
        makecontext(ctx, reinterpret_cast<void (*)()>(funcWrapper), 2, func, arg);
    }

    /**
     * @brief Destroys the Thread Control Block and frees associated resources
     * @details Cleans up stack memory and context for non-main threads
     */
    TCB::~TCB()
    {
        if (ID != 0) {
            if (stack) {
                delete[] stack;
                stack = nullptr;
            }

            if (ctx && state == ThreadState::TERMINATED) {
                delete ctx;
                ctx = nullptr;
            }
        }
    }

    /**
     * @brief Wrapper function for thread execution
     * @param fptr Function pointer to the user-provided thread routine
     * @param params Arguments to be passed to the thread function
     * @details Executes the user function and handles thread termination
     */
    void funcWrapper(void* (*fptr) (void*), void* params)
    {
        thread_exit(fptr(params));
    }

    /**
     * @brief Creates a new thread
     * @param thd_function_t Pointer to the function the thread will execute
     * @param param Parameters to be passed to the thread function
     * @return ThreadID Unique identifier for the newly created thread
     * @details Creates a new TCB and adds it to the thread management system
     */
    ThreadID new_thd(void*(*thd_function_t)(void *), void* param)
    {
        threadList.threadsMap.emplace(TotalID, TCB(TotalID, thd_function_t, param, SwapbackID));
        
        if (TotalID > 0) {
            newThreads.push(TotalID);
        }

        return TotalID++;
    }

    /**
     * @brief Initializes the coroutine system
     * @details Creates the main thread and sets up initial thread management state
     */
    void thd_init()
    {
        SwapbackID = CurrentID = new_thd(nullptr, nullptr);
        TotalID = 1;
    }

    /**
     * @brief Voluntarily yields CPU control to another thread
     * @details Triggers the scheduler to select the next thread for execution
     */
    void thd_yield()
    {
        schedule();
    }

    /**
     * @brief Terminates the current thread
     * @param ret Return value from the thread's execution
     * @details Handles cleanup and notification of waiting threads upon termination
     */
    void thread_exit(void* ret)
    {
        TCB& currentThread = threadList.threadsMap[CurrentID];
        currentThread.returnVal = ret;
        currentThread.state = ThreadState::TERMINATED;

        std::map<unsigned, unsigned>::iterator it = waitThreads.find(CurrentID);
        if (it != waitThreads.end()) {
            threadList.threadsMap[it->second].state = ThreadState::READY;
            readyThreads.push(it->second);
            waitThreads.erase(it);
        }

        schedule();
    }

    /**
     * @brief Retrieves a value pushed by another thread
     * @param[out] value Pointer to store the pulled value
     * @details Blocks the current thread if no value is available
     */
    void pull_value(void** value)
    {
        std::map<unsigned, void*>::iterator puller = pullpushThreads.find(CurrentID);
        if (puller == pullpushThreads.end())
        {
            TCB& currThread = threadList.threadsMap[CurrentID];
            currThread.state = ThreadState::WAITING;
            schedule();
        }
        *value = pullpushThreads[CurrentID];
        pullpushThreads.erase(CurrentID);
    }

    /**
     * @brief Pushes a value to a waiting thread
     * @param value Pointer to the value being pushed
     * @details Makes the value available to the waiting thread and marks it as ready
     */
    void push_value(void* value)
    {
        pullpushThreads[SwapbackID] = value;
        threadList.threadsMap[SwapbackID].state = ThreadState::READY;
        readyThreads.emplace(SwapbackID);
        thd_yield();
    }

}