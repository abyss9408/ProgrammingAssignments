#include "uShell2.h"
#include <iostream>   //std::cin, std::cout
#include <sstream>    //std::istringstream
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void uShell2::exit(TokenList const & tokenList)
{
    m_exit = true;
    if (tokenList.size() > 1)
    {
        m_exitCode = std::stoi(tokenList[1]);
    }
    else
    {
        m_exitCode = 0;
    }
}

void uShell2::changePrompt(TokenList const & tokenList)
{
    if (tokenList.size() < 2)
    {
        m_prompt = "";
        return;
    }

    m_prompt = mergeTokens(tokenList, 1);
}

void uShell2::execute(TokenList const & tokenList, unsigned startParam, unsigned endParam)
{
    if (tokenList.empty())
    {
        return;
    }

    std::vector<char*> args;
    for (unsigned i = startParam; i <= endParam; ++i)
    {
        args.push_back(const_cast<char*>(tokenList[i].c_str()));
    }
    args.push_back(nullptr);

    std::string cmd = tokenList[startParam];

    // if it is an absolute path
    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
    {
        // the file exists
        if (access(cmd.c_str(), F_OK) == 0)
        {
            execvp(cmd.c_str(), args.data());
        }
    }
    else
    {
        const char* path = m_vars["PATH"].c_str();
        if (path)
        {
            std::istringstream pathStream(path);
            std::string dir;
            while (std::getline(pathStream, dir, ':'))
            {
                std::string fullPath = dir + "/" + cmd;
                if (access(fullPath.c_str(), X_OK) == 0)
                {
                    execvp(fullPath.c_str(), args.data());
                }
            }
        }
    }
    
    
    // If we reach here, the command was not found
    std::cout << "Error: " << cmd << " cannot be found" << std::endl;
    _exit(1);  // Use _exit() in child process
}

void uShell2::doExternalCmd(TokenList const & tokenList)
{
    std::cout.flush();
    pid_t pid = fork();
    if (pid == 0) // child process
    {
        execute(tokenList, 0, tokenList.size());
        _exit(127);
    }
    else if (pid > 0) // parent process
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

uShell2::uShell2(bool bFlag)
: uShell(bFlag) {}

int uShell2::run()
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
		
		// Next, it finds whether the token is an internal command. 
		// If so, it activates the internal command. 
		// Otherwise, it does the external command 
		// (that will be done in the following assignments).
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
        else
        {
            doExternalCmd(tokens);
        }
	}
	
	// Outside the loop, it returns exit code m exitCode
	return m_exitCode;
}