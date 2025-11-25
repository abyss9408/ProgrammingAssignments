/*  Start Header
*****************************************************************/
/*!
\file new-coro-lib.cpp
\author Bryan Ang Wei Ze
\par email: bryanweize.ang\@digipen.edu
\date 01/11/2024
\brief
contains the implementaion for cooperative threading library new coro lib
as well as some structs and functions needed for the library to work
Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is
prohibited.
*/
/* End Header
*******************************************************************/


#include <map>            //std::map
#include <queue>          //std::queue
#include <stack>          //std::stack
#include <cstdlib>        //std::atexit
#include <ucontext.h>
//#define UCONTEXT
//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif
#include "new-coro-lib.h" //declarations
#include "new-coro-helper.h" //declarations

namespace CORO
{
  //extern ThreadID TotalID;
  //Current thread
  extern ThreadID CurrentID;
  //Swapback thread
  extern ThreadID SwapbackID;
    
  //Struct to store threads
  extern ThreadList threadList;
  
  //FIFO queue that contains thread that are in ready state
  extern std::queue<unsigned> readyThreads;
  //FIFO queue  that contains newly created thread
  extern std::queue<unsigned> newThreads;
  //Map that contains threads in waiting state
  //thread ID of waited thread is the map key 
  //and thread ID of the waiting thread is the map value  
  extern std::map<unsigned, unsigned> waitThreads;
  //Map that contains the 1:1 puller-pusher relationship of two threads
  //thread ID is the map key and 
  //the pointer to the value between pusher and puller threads is the map value 
  //extern std::map<unsigned, void *> pullpushThreads;
  
  void schedule() 
  {
    // First try to schedule from ready threads queue
    if (!readyThreads.empty())
    {
      TCB& currentThread = threadList.threadsMap[CurrentID];

      // If current thread is not terminated or waiting, mark it as ready
      if (currentThread.state != TERMINATED && currentThread.state != WAITING)
      {
        currentThread.state = READY;
        readyThreads.push(CurrentID);
      }
      
      // Save current thread ID for context switching
      SwapbackID = CurrentID;

      // Get next thread from ready queue
      CurrentID = readyThreads.front();
      readyThreads.pop();

      // Mark new thread as running
      TCB& nextThread = threadList.threadsMap[CurrentID];
      nextThread.state = RUNNING;

      // Set up context link
      nextThread.ctx->uc_link = threadList.threadsMap[SwapbackID].ctx;

      // Perform context switch
      swapcontext(threadList.threadsMap[SwapbackID].ctx, nextThread.ctx);
      return;
    }
    
    // If no ready threads, try to schedule from new threads queue
    if (!newThreads.empty())
    {
      TCB& currentThread = threadList.threadsMap[CurrentID];

      // If current thread is not terminated or waiting, mark it as ready
      if (currentThread.state != TERMINATED && currentThread.state != WAITING)
      {
        currentThread.state = READY;
        readyThreads.push(CurrentID);
      }

      // Save current thread ID for context switching
      SwapbackID = CurrentID;

      // Get next thread from new queue
      CurrentID = newThreads.front();
      newThreads.pop();

      // Mark new thread as running
      TCB& nextThread = threadList.threadsMap[CurrentID];
      nextThread.state = RUNNING;

      // Allocate stack for new thread
      nextThread.stack = new char[SIZE];  // SIZE is defined as 1 << 20 in the header

      // Initialize context
      getcontext(nextThread.ctx);
      nextThread.ctx->uc_link = threadList.threadsMap[SwapbackID].ctx;
      nextThread.ctx->uc_stack.ss_sp = nextThread.stack;
      nextThread.ctx->uc_stack.ss_size = SIZE;

      // Set up thread function
      makecontext(nextThread.ctx, 
                  (void(*)())funcWrapper, 
                  2, 
                  (void*)nextThread.functionPtr, 
                  nextThread.param);

      // Perform context switch
      swapcontext(threadList.threadsMap[SwapbackID].ctx, nextThread.ctx);
    }
  }	  

  int wait_thread(ThreadID id, void ** value) 
  {
	  // Try to find the thread with given ID in the thread List
    auto threadIter = threadList.threadsMap.find(id);

    // If thread exists
    if (threadIter != threadList.threadsMap.end())
    {
      // Mark current thread as waiting and store the relationship in waitThreads map
      waitThreads[id] = CurrentID;
      threadList.threadsMap[CurrentID].state = WAITING;
      
      // Wait until the target thread is terminated
      while (threadList.threadsMap[id].state != TERMINATED)
      {
        schedule(); // Yield control to other threads while waiting
      }

      // Clean up the waiting relationship
      waitThreads.erase(id);
      
      // If value pointer is provided, store the return value
      if (value != nullptr)
      {
        *value = threadList.threadsMap[id].returnVal;
      }
      
      // Clean up the terminated thread from thread list
      threadList.threadsMap.erase(id);
      
      return WAIT_SUCCESSFUL;
    }
    
    return NO_THREAD_FOUND;
  }
}