#include <string>   //std::string
#include <vector>   //std::vector
#include <map>      //std::map
/*! list of strings */
using TokenList = std::vector<std::string>;

/************************************************************************/
/*!
\brief
uShell class. Acts as a command prompt that takes in input and performs
commands based on the input
*/
/************************************************************************/
class uShell
{ 
  protected:
  
  /*! Map of variables to string values */
  std::map<std::string, std::string> m_vars;
  
  /*! String prompt that is displayed at the beginning*/
  std::string m_prompt;
  
  /*! decide whether to echo user input */
  bool m_verbose;
  
  /*! determine whether to exit */
  bool m_exit;
  
  /*! exit code determined during runtime */
  int m_exitCode;
  
  /************************************************************************/
  /*!
  \brief
  Get one line of input from std::cin. Removes the trailing \r if any
  \param input
  The input string to take the user input by reference
  \return
  return false if encountering the EOF
  */
  /************************************************************************/
  bool getInput(std::string & input) const;
  
  /************************************************************************/
  /*!
  \brief
  Print the user input without printing the starting and the trailing spaces.
  \param input
  The input string
  */
  /************************************************************************/
  void printVerbose(std::string const & input);
  
  /************************************************************************/
  /*!
  \brief
  Tokenize the input string into a list of strings which are separated by
  spaces.
  \param input
  The input string given by the user
  \param tokenList
  Token list to fill up, passed by reference to add strings to it
  */
  /************************************************************************/
  void tokenize(std::string const & input, TokenList & tokenList) const;
  
  /************************************************************************/
  /*!
  \brief
  Search and replace all variables in the token list with the value from the map 
  \param tokenList
  Token list that stores the variables to be searched
  \return
  Boolean value to decide whether there is a invalid variable found in the string.
  Returning true means all valid. Otherwise,
  Returning false means there is a invalid variable (abort the search).
  */
  /************************************************************************/
  bool replaceVars(TokenList & tokenList) const;
  
  /************************************************************************/
  /*!
  \brief
  Check whether each character is a number or digit from the given start and 
  end of a character array. 
  \param start
  Pointer to the start of string to search from
  \param end
  Pointer to the end of string, where the search stops 
  \return
  boolean value to represent if the string is valid
  Returning true means each character in the given string is valid. 
  Otherwise, it returns false.
  */
  /************************************************************************/
  bool isValidVarname(char const * start, char const * end) const;
  
  /************************************************************************/
  /*!
  \brief
  Merge all the tokens from a given token list, separated by a space, into one 
  single string.  Move scemantics help in this case.
  \param tokenList
  The token list from which to take the tokens
  \param startPos
  The starting position to start merging from
  \return 
  The merged string
  */
  /************************************************************************/
  std::string mergeTokens(TokenList const & tokenList, 
                          unsigned startPos) const;
  
  /************************************************************************/
  /*!
  \brief
  Echo the user input 
  \param tokenList
  The list of data to read in
  */
  /************************************************************************/
  void echo(TokenList const & tokenList);

  /************************************************************************/
  /*!
  \brief
  Set the value of a variable
  \param tokenList
  The list of tokens from which to get the data value
  */
  /************************************************************************/
  void setVar(TokenList const & tokenList);
  
  
  public:
  
  /************************************************************************/
  /*!
  \brief
  Creates the class object of uShell
  \param bFlag
  boolean value to decide whether to echo input
  */
  /************************************************************************/
  uShell(bool bFlag);
  
  /************************************************************************/
  /*!
  \brief
  Public function for external call. Execute in loops and waits for input.
  \return
  Exit code, of the exit command
  */
  /************************************************************************/
  int run();
};