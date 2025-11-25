#include "uShell.h"
#include <iostream>
#include <sstream>
#include <fstream>

uShell::uShell(bool bFlag)
: m_prompt("uShell"), m_verbose(bFlag), m_exit(false), m_exitCode(0)
{
    m_vars["PATH"] = std::getenv("PATH");
}

bool uShell::getInput(std::string & input) const
{
    std::getline(std::cin, input);

    if (input.empty())
    {
        return false;
    }
    
    if (input.back() == '\r')
    {
        input.pop_back();
    }
    else if (input.back() == '\n')
    {
        input.pop_back();
        input.pop_back();
    }

    return true;
}

void uShell::printVerbose(std::string const & input)
{
    size_t start{}, end{};

    start = input.find_first_not_of(" \t");
    end = input.find_last_not_of(" \t");

    if (start != std::string::npos && end != std::string::npos)
    {
        std::cout << input.substr(start, end-start+1);
    }
    
    std::cout << std::endl;
}

void uShell::tokenize(std::string const & input, TokenList & tokenList) const
{
    std::istringstream token_input(input);
    std::string token;
    
    while (token_input >> token)
    {
        tokenList.push_back(token);
    }
}

bool uShell::replaceVars(TokenList & tokenList) const
{
    std::size_t index{};

    for (std::string& token : tokenList)
    {
        /*
            In each iteration, checks each token for comment.
            if the current token has a comment sign, it removes all the following tokens including the current one
            and terminates the loop.
        */
        if (token[0] == '#')
        {
            tokenList.erase(tokenList.begin() + index, tokenList.end());
            return true;
        }

        // checks if each token has a variable within
        size_t token_pos{};
        std::string var;
        
        // look for '$' signs in token
        while ((token_pos = token.find_first_of('$', token_pos)) != std::string::npos)
        {
            //std::cout << token.find('{', token_pos+1) <<'\n';
            // there is a '{' after a '$' sign
            if (token.find('{', token_pos+1) != std::string::npos)
            {
                // token_pos now refers to position of '{' sign
                token_pos = token.find('{', token_pos+1);

                // '}' is found in token
                if (token.find_first_of('}', token_pos) != std::string::npos)
                {
                    // validates variable name
                    if (isValidVarname(token.c_str() + token_pos + 1, token.c_str() + token.find_first_of('}', token_pos)))
                    {
                        // extract variable name between '{' and '}'
                        var = token.substr(token_pos+1, token.find_first_of('}', token_pos)-token_pos-1);

                        // variable is defined
                        if (m_vars.find(var) != m_vars.end())
                        {
                            // replace variable with value associated with it
                            token.replace(token_pos - 1, token.find_first_of('}', token_pos) - (token_pos - 1) + 1, m_vars.find(var)->second);
                        }
                        else
                        {
                            std::cerr << "Error: " << var << " is not a defined variable.\n";
                            return false;
                        }
                    }
                }
                else
                {
                    // exit loop as '{' is not found in token
                    break;
                }
            }
            
            
            // exit when there is no more dollar sign
            if (token_pos == std::string::npos)
            {
                break;
            }
        }

        ++index; 
    }
    
    return true;
}

bool uShell::isValidVarname(char const * start, char const * end) const
{
    while (start != end)
    {
        // character is not an alphabet or digit
       if (!std::isdigit(*start) && !std::isalpha(*start))
       {
            return false;
       }
       
       ++start;
    }
    
    return true;
}

std::string uShell::mergeTokens(TokenList const & tokenList, unsigned startPos) const
{
    std::string merged_tokens;

    for (size_t i = startPos; i < tokenList.size(); ++i)
    {
        merged_tokens += tokenList[i] + ' ';
    }
    merged_tokens.pop_back();
    return merged_tokens;
}