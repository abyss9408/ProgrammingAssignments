#include "uShell3.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

void uShell3::doExternalCmd(TokenList const & tokenList)
{
    // Checks if the first token is a pipe.
    if (tokenList[0] == "|")
    {
        std::cout << "syntax error near unexpected token '|'" << std::endl;
        return;
    }

    // Count number of pipes and push back with information for each
    std::vector<PipeInfo> pipeList;
    for (unsigned i = 0; i < tokenList.size(); ++i)
    {
        if (tokenList[i] == "|")
        {
            // Create a pipe
            int pipefd[2];
            pipe(pipefd);

            // Set pipe into our struct
            PipeInfo pipe;
            pipe.posInToken = i;
            pipe.descriptor[PipeInfo::IN_DESCRIPTOR] = pipefd[0];
            pipe.descriptor[PipeInfo::OUT_DESCRIPTOR] = pipefd[1];
            pipeList.push_back(pipe);
        }
    }
    
    bool isBackgroundProcess = false;
    std::vector<pid_t> childPids;

    // Loop through all processes, which is 1 + the number of pipe arguments
    for (unsigned i = 0; i < pipeList.size() + 1; ++i)
    {
        size_t start_arg = (i == 0) ? 0 : pipeList[i - 1].posInToken + 1; // Argument is always one after the pipe identifier unless its the first
        size_t end_arg = (i == pipeList.size()) ? tokenList.size() : pipeList[i].posInToken; // End argument is always the pipe position unless its the last in which it will be the oen past the end of tokenList

        // Check for background process token
        if (i == pipeList.size() && tokenList.back() == "&")
        {
            isBackgroundProcess = true;
            end_arg = tokenList.size() - 1;
        }

        // Check if between pipe has nothing inside
        if (start_arg == end_arg) 
        {
            std::cout << "Error: syntax error" << std::endl;
            return;
        }

        // Check if command bteween pipe exists
        if (!exist(tokenList, start_arg, end_arg))
        {
            std::cout << "Error: " << tokenList[start_arg] << " cannot be found" << std::endl;
            return;
        }

        // Valid process, begin fork
        int pid = fork();

        // Parent process handles adding to the processlist
        if (pid != 0)
        {   
            childPids.push_back(pid);
        }
        else if (pid == 0)
        {
            // Manage pipes of child process...
            // Not first to be created
            if (i != 0) 
            {
                // Set read end of pipe to stdin by closing it then duplicating the descriptor, which sets to the lowest available file descriptor
                close(STDIN_FILENO); 
                dup(pipeList[i-1].descriptor[PipeInfo::IN_DESCRIPTOR]);    
            }

            // Not last to be created
            if (i != pipeList.size()) 
            {
                // Set write end of pipe to stdout by closing it then duplicating the descriptor, which sets to the lowest available file descriptor
                close(STDOUT_FILENO);
                dup(pipeList[i].descriptor[PipeInfo::OUT_DESCRIPTOR]);    
            }
            
            // Close all pipe descriptors
            for (const auto& pInfo : pipeList)
            {
                close(pInfo.descriptor[PipeInfo::IN_DESCRIPTOR]);
                close(pInfo.descriptor[PipeInfo::OUT_DESCRIPTOR]);
            }
            
            execute(tokenList, start_arg, end_arg);
            _exit(EXIT_FAILURE);
        }
        else std::cout << "Failed to fork process" << std::endl;
    }

    // Parent process: close all pipes
    for (const auto& pInfo : pipeList)
    {
        close(pInfo.descriptor[PipeInfo::IN_DESCRIPTOR]);
        close(pInfo.descriptor[PipeInfo::OUT_DESCRIPTOR]);
    }

    // Exclude background token if it there are no more pipes // TODO: or it is the only process.
    if (isBackgroundProcess)
    {
        // Is background, push and dont wait
        ProcessInfo process;
        process.PID = childPids.back();
        process.bActive = true;
        m_bgProcessList.push_back(process);

        std::cout << "[" << m_bgProcessList.size() - 1 << "] process " << process.PID << std::endl;
    }
    else
    {
        // Wait for all child processes
        for (pid_t childPid : childPids)
        {
            int status;
            waitpid(childPid, &status, 0);
        }
    }
}