/*  Start Header
*****************************************************************/
/*!
\file new-coro-helper.cpp
\author William ZHENG
\par email: william.zheng\@digipen.edu
\date 01/10/2024
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

#include "new-coro-helper.h"

namespace CORO
{
  //Number of threads
  ThreadID TotalID = 0;
  //Current thread
  ThreadID CurrentID;
  //Swapback thread
  ThreadID SwapbackID;
  
  //Struct to store threads
  ThreadList threadList;
  
  //FIFO queue that contains thread that are in ready state
  std::queue<unsigned> readyThreads;
  //FIFO queue  that contains newly created thread
  std::queue<unsigned> newThreads;
  //Map that contains threads in waiting state
  //thread ID of waited thread is the map key 
  //and thread ID of the waiting thread is the map value  
  std::map<unsigned, unsigned> waitThreads;
  //Map that contains the 1:1 puller-pusher relationship of two threads
  //thread ID is the map key and 
  //the pointer to the value between pusher and puller threads is the map value 
  std::map<unsigned, void *> pullpushThreads;	
  //Thread scheduling
  
  //Yield CPU cycles
  extern void schedule();

  //Wait for thread
  extern int wait_thread(ThreadID id, void ** value);
  
  //non-default constructor
  TCB::TCB(ThreadID id, FnPtr ptr, void * param, ThreadID pid) 
  {	
	//not shown here  
  }
    
  //Destructor
  TCB::~TCB()
  {	
	//not shown here  
  }
  
  void funcWrapper(void* (*fptr) (void*), void* params)
  {	
	//not shown here  
  }
  
  
  //Create a new thread
  ThreadID new_thd(void*(*thd_function_t)(void *), void* param)
  {	
	//not shown here  
  }

  //Initialise the main thread
  void thd_init()
  {	
	//not shown here  
  }

  void thd_yield()
  {	
	//not shown here  
  }
  
  //Terminate thread
  void thread_exit(void * ret)
  {	
	//not shown here  
  }
  
  //Retrieve pull value
  void pull_value(void ** val)
  {	
	//not shown here  
  }
  
  //Push value to the pusher that created it
  void push_value(void * val)
  {	
	//not shown here  
  }

}