#include <string>   //std::string
#include <vector>   //std::vector
#include <map>      //std::map
#include "uShell2.h" 

/************************************************************************/
/*!
\brief
uShell2 class. Acts as a command prompt that takes in input and performs
commands based on the input. 
*/
/************************************************************************/
class uShell3 : public uShell2
{ 
  protected:

  /************************************************************************/
  /*!
  \brief
  Process info for background processes.
  */
  /************************************************************************/
  struct ProcessInfo
  {
    /*! The process ID given by OS */
    int PID;
    
    /*! The state of the process, whether it is active */
    bool bActive;
    
    /************************************************************************/
    /*!
    \brief
    Default constructor 
    */
    /************************************************************************/
    ProcessInfo();
    
    /************************************************************************/
    /*!
    \brief
    Value constructor, set process id and current state
    \param id
    The process ID given by the OS
    \param state
    The state of the process to set
    */
    /************************************************************************/
    ProcessInfo(int id, bool state);
  };
  
  /************************************************************************/
  /*!
  \brief
  Process info for piping commands.
  */
  /************************************************************************/
  struct PipeInfo
  {
    /*! File descriptor array. The first is READ/IN descriptor, the 
        second WRTIE/OUT descriptor */
    int descriptor[2];
    
    /*! The position of the pipe token "|" within the token list */
    unsigned posInToken;
    
    /*! Const value for READ/IN descriptor */
    static const int IN_DESCRIPTOR = 0;
    
    /*! Const value for WRITE/OUT descriptor */
    static const int OUT_DESCRIPTOR = 1;
  };
  
  /*! Store the list of background processes */
  std::vector<ProcessInfo> m_bgProcessList;

  /*!
  \brief
  Determine whether the command exists or not.
  \param tokenList
  The list of tokens to get the command and arguments from
  \param startParam
  The starting token to parse data from the list
  \param endParam
  The last token to parse data from the list
  \param cmdPath
  The path of the command
  \param argumentArray
  The argument list for command
  */
  /************************************************************************/
  bool exist (TokenList const & tokenList, 
                        unsigned startParam, 
						unsigned endParam);
 

  /************************************************************************/
  /*!
  \brief
  Calls an external command using the passed in parameters.
  \param tokenList
  The list of tokens to get the data value from
  */
  /************************************************************************/
  void doExternalCmd(TokenList const & tokenList);

  /************************************************************************/
  /*!
  \brief
  Finish command: wait for a background process to finish
  \param tokenList
  The list of data to read in, the process ID to wait for
  */
  /************************************************************************/
  void finish(TokenList const & tokenList);
  

  public:
  /************************************************************************/
  /*!
  \brief
  Creates the class object of uShell3
  \param bFlag
  boolean value to decide whether to echo input
  */
  /************************************************************************/
  uShell3(bool bFlag);
  
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
