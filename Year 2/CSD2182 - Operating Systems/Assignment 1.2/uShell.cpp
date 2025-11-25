/* Start Header
 *****************************************************************/
 /*!
 \file uShell.cpp
 \author Bryan Ang Wei Ze, bryanweize.ang, 2301397
 \par bryanweize.ang@digipen.edu
 \date Sept 15 2024
 \brief
 Copyright (C) 2024 DigiPen Institute of Technology.
 Reproduction or disclosure of this file or its contents without the
 prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /* End Header
 *******************************************************************/
#include <iostream>   //std::cin, std::cout
#include <sstream>    //std::istringstream
#include <cstdlib>    //std::getenv
#include <cctype>     //isalpha, isdigit
#include "uShell.h"

/************************************************************************/
/*!
\brief
Echo the user input 
\param tokenList
The list of data to read in
*/
/************************************************************************/
void uShell::echo(TokenList const & tokenList)
{
	// there are no tokens or only one token in tokenList
	if (tokenList.size() < 2)
	{
		return;
	}
	
	for (size_t i = 1; i < tokenList.size(); ++i)
	{
		std::cout << tokenList[i];

		// add a space after each token except the last
		if (i != tokenList.size() - 1)
		{
			std::cout << ' ';
		}
	}
	std::cout << std::endl;
}

/************************************************************************/
/*!
\brief
Set the value of a variable
\param tokenList
The list of tokens from which to get the data value
*/
/************************************************************************/ 
void uShell::setVar(TokenList const & tokenList)
{
	if (tokenList.size() < 2)
	{
		return;
	}
	// Otherwise it has to check if the variable name is proper by ensuring 
	// that the first letter is an alphabet
	std::string var = tokenList[1];

	if (!isalpha(var[0]))
	{
		return;
	}
	
	
	// and also continue to loop through the rest of the characters of this variable 
	// to check whether the variable name is valid by using isValidVarname(). 
	if (!isValidVarname(var.c_str() + 1, var.c_str() + var.size()))
	{
		return;
	}

	// If there are more variables at the back,
	// it merges them all together (using mergeTokens())
	// and sets it to the mapped variable.
	// Otherwise, it just initializes to an empty string.
	std::string val = mergeTokens(tokenList, 2);
	m_vars[var] = val;
}

/************************************************************************/
/*!
\brief
Public function for external call. Execute in loops and waits for input.
\return
Exit code, of the exit command
*/
/************************************************************************/
int uShell::run()
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
		TokenList tokenList;
		tokenize(input, tokenList);
		if (m_verbose)
		{
			printVerbose(input);
		}
		if (!replaceVars(tokenList) || tokenList.empty())
		{
			continue;
		}
		
		// Next, it finds whether the token is an internal command. 
		// If so, it activates the internal command. 
		// Otherwise, it does the external command 
		// (that will be done in the following assignments).
		const std::string& cmd = tokenList[0];
		if (cmd == "exit")
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
		else if (cmd == "echo")
		{
			echo(tokenList);
		}
		else if (cmd == "setvar")
		{
			setVar(tokenList);
		}
	}
	
	// Outside the loop, it returns exit code m exitCode
	return m_exitCode;
}