#include "uShell3.h"
#include <iostream>   //std::cin, std::cout
#include <sstream>    //std::istringstream
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

// Default constructor for ProcessInfo
uShell3::ProcessInfo::ProcessInfo()
    : PID(0), bActive(false) {}

// Parameterized constructor for ProcessInfo
uShell3::ProcessInfo::ProcessInfo(int id, bool state)
    : PID(id), bActive(state) {}

bool uShell3::exist(TokenList const & tokenList, unsigned startParam, unsigned endParam)
{
    // Check if the start and end parameters are valid
    if (startParam > endParam || startParam >= tokenList.size())
    {
        return false;
    }

    // Get the command (first token)
    std::string cmd = tokenList[startParam];

    // Check if it's an absolute path or starts with ./
    if (cmd[0] == '/' || (cmd.size() > 1 && cmd[0] == '.' && cmd[1] == '/'))
    {
        // For absolute paths or ./commands, directly check if the file exists and is executable
        return access(cmd.c_str(), X_OK) == 0;
    }
    else
    {
        // For other commands, search in the directories listed in the PATH environment variable
        const char* path = m_vars["PATH"].c_str();
        std::istringstream pathStream(path);
        std::string dir;
        while (std::getline(pathStream, dir, ':'))
        {
            // Construct the full path to the potential command
            std::string fullPath = dir + "/" + cmd;
            if (access(fullPath.c_str(), X_OK) == 0)
            {
                return true;
            }
        }
    }
    
    // If we reach here, the command was not found
    return false;
}

// Implementation of the finish command
void uShell3::finish(TokenList const & tokenList)
{
    // Check if a process index was provided
    if (tokenList.size() < 2)
    {
        std::cout << "Error: no such process index." << std::endl;
        return;
    }

    // Convert the process index to an integer
    int processIndex = std::stoi(tokenList[1]);

    // Check if the process index is valid
    if (processIndex < 0 || processIndex >= static_cast<int>(m_bgProcessList.size()))
    {
        std::cout << "Error: no such process index." << std::endl;
        return;
    }
    
    ProcessInfo& process = m_bgProcessList[processIndex];

    // Check if the process is still active
    if (!process.bActive)
    {
        std::cout << "Process Index " << processIndex << " process " << process.PID 
                  << " is no longer a child process." << std::endl;
        return;
    }
    
    int status;
     // Try to wait for the process without blocking
    pid_t result = waitpid(process.PID, &status, 0);

    if (result == -1)
    {
        perror("waitpid");
        return;
    }

    // Print the exit status or termination signal of the process
    if (WIFEXITED(status))
    {
        std::cout << "process " << process.PID << " exited with exit status " << WEXITSTATUS(status) << std::endl;
    }
     // Mark the process as inactive
    process.bActive = false;
}

uShell3::uShell3(bool bFlag) : uShell2(bFlag) {}

// Main run loop of the shell
int uShell3::run()
{
    // This function has a loop and firstly check whether an exit state occurs 
	// (e.g. due to that exit command is called ). If so, it stops. 
	while (true)
	{
		if (m_exit)
		{
			break;
		}
		
		// Otherwise it prints out the prompt, with the right arrow.
		std::cout<<m_prompt<<'>';
		
		// Then it gets user input.
		// If there are no more lines from the input 
		// (or EOF is read if it gets re-directed input from the file), 
		//it exits from the program after setting m_exitCode
		std::string input;
		if (!getInput(input))
		{
			m_exitCode = 0;
			m_exit = true;
		}
		
		// Otherwise, it clears the input buffer for next input. 
		// Obviously, it needs to skip if there is no input (e.g. empty line).
		std::cin.clear();
		if (input.empty())
		{
			continue;
		}
		
		
		// It starts to tokenize the input otherwise. 
		// After this, it prints the input if verbose mode is set. 
		// It replaces all variables if possible. 
		// When the function calls for replacement
		// replaceVars() returns false (thus an error has occurred), 
		// or when the token list size is zero, 
		// it continues to process next line of input.
		TokenList tokens;
		tokenize(input, tokens);
		if (m_verbose)
		{
			printVerbose(input);
		}

		if (!replaceVars(tokens) || tokens.empty())
		{
			continue;
		}
		
		// Handle built-in commands
		const std::string& cmd = tokens[0];
		if (cmd == "exit")
		{
			exit(tokens);
		}
		else if (cmd == "echo")
		{
			echo(tokens);
		}
		else if (cmd == "setvar")
		{
			setVar(tokens);
		}
        else if (cmd == "changeprompt")
		{
			changePrompt(tokens);
		}
        else if (cmd == "finish")
		{
			finish(tokens);
		}
        else
        {
            doExternalCmd(tokens);
        }
	}
	
	// Outside the loop, it returns exit code m exitCode
	return m_exitCode;
}