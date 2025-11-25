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
  //thread ID of waiting thread is the map key 
  //and thread ID of the waited thread is the map value  
  std::map<unsigned, unsigned> waitThreads;
  //Map that contains the 1:1 puller-pusher relationship of two threads
  //thread ID is the map key and 
  //the pointer to the value between pusher and puller threads is the map value 
  std::map<unsigned, void *> pullpushThreads;	
  //Thread scheduling
  
  void schedule() {//not shown here}
  
  //Wait for the thread
  int wait_thread(ThreadID id, void ** value) {//not shown here}

}