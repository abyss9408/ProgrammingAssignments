/*  Start Header
*****************************************************************/
/*!
\file new-coro-helper.h
\author William ZHENG
\par email: william.zheng\@digipen.edu
\date 1/10/2024
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
#ifndef NEW_CORO_HELPER_H
#define NEW_CORO_HELPER_H

#include <map>            //std::map
#include <queue>          //std::queue
#include <stack>          //std::stack
#include <cstdlib>        //std::atexit
#include <ucontext.h>
#include "new-coro-lib.h"

namespace CORO
{
  static constexpr unsigned SIZE = 1 << 20;
  
  enum ThreadState : int
  {
    NEW = 0,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
  };
  
  //Thread control block
  struct TCB
  { 
    typedef void*(*FnPtr)(void*);   
    
    ThreadID ID;//Thread ID
    
    ThreadID PullerID;//Puller thread ID
    
    ThreadState state;//Current state of thread
    
    char * stack;//Pointer to stack
    
    ucontext_t* ctx;//Pointer to context
    
    FnPtr functionPtr;//Function pointer of the thread
    
    void * param;//Arguments
    
    void * returnVal;//Return
    
    TCB()//Default constructor
    {}
    
    //non-default constructor
    TCB(ThreadID id, FnPtr ptr, void * param, ThreadID pid);

    //Destructor
    ~TCB();
  };
  
  //List of all existing threads
  struct ThreadList
  {
    //contains all the threads
    std::map<ThreadID, TCB> threadsMap;
  };
  
  //thread function wrapper
  void funcWrapper(void* (*fptr) (void*), void* params);

  //Yield CPU cycles
  void schedule();

  //Wait for thread
  int wait_thread(ThreadID id, void ** value);
  
}  
#endif