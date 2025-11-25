/*!************************************************************************
  \file splitter.h

  \author Bryan Ang Wei Ze

  \par DP email: bryanweize.ang\@digipen.edu

  \par Course: CSD2126 Modern C++ Design Patterns

  \par Programming Assignment #1

  \date 14-09-2024
  
  \brief
  This header file declares a function that splits files into smaller chunks
  and joins split files into a single file, which can be used by both C and C++
  source files.
**************************************************************************/

#ifndef SPLITTER_H
#define SPLITTER_H

#include <stddef.h> // size_t definition

typedef enum {
  E_BAD_SOURCE = 1,
  E_BAD_DESTINATION,
  E_NO_MEMORY,
  E_SMALL_SIZE,
  E_NO_ACTION,
  E_SPLIT_SUCCESS,
  E_JOIN_SUCCESS
} SplitResult;

#ifdef __cplusplus
extern "C"
{
#endif
  /***************************************************************************/
    /*!
    \brief
    Function that splits a large file into smaller chunks and joins them
    back into a file

    \param argc
    Number of cmd line arguments

    \param argv
    Rag array of cmd line arguments

    \return
    Result of spliting file/joining file
    */
  /**************************************************************************/
  SplitResult split_join(int argc, char *argv[]);
#ifdef __cplusplus
}
#endif

#endif // end of #ifndef SPLITTER_H
