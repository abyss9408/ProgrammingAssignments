/*!************************************************************************
  \file splitter.c

  \author Bryan Ang Wei Ze

  \par DP email: bryanweize.ang\@digipen.edu

  \par Course: CSD2126 Modern C++ Design Patterns

  \par Programming Assignment #1

  \date 14-09-2024
  
  \brief
  This C source file defines a function that splits files into smaller chunks
  and joins split files into a single file, which can be used by both C and C++
  source files.
**************************************************************************/

#include "splitter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define FOUR_K 4096

void generate_output_filename(const char* prefix, int file_count, char* buffer)
{
  sprintf(buffer, "%s%04d", prefix, file_count);
}

SplitResult split_file(const char* input_file, const char* output_prefix, size_t chunk_size)
{
  FILE *input = fopen(input_file, "rb");

  // input file cannot be opened
  if (!input)
  {
    return E_BAD_SOURCE;
  }

  // set read buffer size to FOUR_K if user-specified chunk size exceends that
  size_t buffer_size = chunk_size < FOUR_K ? chunk_size : FOUR_K;
  char* buffer = (char*)malloc(buffer_size);

  // test for failed heap memory allocation
  if (!buffer)
  {
    fclose(input);
    return E_NO_MEMORY;
  }

  int file_count = 0;
  size_t bytes_in_current_chunk = 0;
  FILE *output = NULL;
  char output_filename[256];

  // read input file that needs to be split
  while (!feof(input))
  {
    // number of remaining bytes that needs to be read from input file
    size_t bytes_read = fread(buffer, 1, buffer_size, input);

    // if there are remaining bytes that need to be read
    if (bytes_read > 0)
    {
      size_t bytes_to_write = bytes_read;
      size_t buffer_offset = 0;

      while (bytes_to_write > 0)
      {
        // create a new output file if the previous one is at the chunk size
        if (!output)
        {
          generate_output_filename(output_prefix, ++file_count, output_filename);
          output = fopen(output_filename, "wb");

          // output file cannot be created
          if (!output)
          {
            free(buffer);
            fclose(input);
            return E_BAD_DESTINATION;
          }
          bytes_in_current_chunk = 0;
        }

        // number of bytes that can still be written to current chunk
        size_t bytes_remaining_in_chunk = chunk_size - bytes_in_current_chunk;

        /*
          set the number of bytes written to current chunk depending on how many more bytes
          that can still be written to current chunk
          eg. bytes_remaining_in_chunk = 10000, bytes_to_write(in buffer) = 4096, write 4096 bytes to chunk
          bytes_remaining_in_chunk = 1808, bytes_to_write(in buffer) = 4096, write 1808 bytes to chunk
        */
        size_t bytes_to_write_now = bytes_to_write < bytes_remaining_in_chunk ? bytes_to_write : bytes_remaining_in_chunk;

        // write from read buffer to chunk
        fwrite(buffer + buffer_offset, 1, bytes_to_write_now, output);

        /* update number of bytes in current chunk, buffer offset for the next write and
        remaining number of bytes in read buffer */
        bytes_in_current_chunk += bytes_to_write_now;
        buffer_offset += bytes_to_write_now;
        bytes_to_write -= bytes_to_write_now;

        // current chunk is full
        if (bytes_in_current_chunk == chunk_size)
        {
          fclose(output);
          output = NULL;
        }
      }
    }
  }

  if (output)
  {
    fclose(output);
  }

  free(buffer);
  fclose(input);
  return E_SPLIT_SUCCESS;
}

SplitResult join_files(char **file_chunks, int num_chunks, const char* output_file)
{
  FILE *output = fopen(output_file, "wb");

  // output file cannot be created
  if (!output)
  {
    return E_BAD_DESTINATION;
  }

  char *buffer = (char*)malloc(FOUR_K);

  // test for failed heap memory allocation
  if (!buffer)
  {
    fclose(output);
    return E_NO_MEMORY;
  }

  for (int i = 0; i < num_chunks; ++i)
  {
    FILE *input = fopen(file_chunks[i], "rb");
    if (!input)
    {
      free(buffer);
      fclose(output);
      return E_BAD_SOURCE;
    }

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, FOUR_K, input)) > 0)
    {
      fwrite(buffer, 1, bytes_read, output);
    }
    fclose(input);
  }

  free(buffer);
  fclose(output);
  return E_JOIN_SUCCESS;
}

SplitResult split_join(int argc, char *argv[]) {
  SplitResult rs = E_NO_ACTION;
	
  // user did not provide enough cmd line arguments for the program
  if (argc < 7)
  {
    return rs;
  }

  // parse cmd line arguments and split/join files accordingly
  char *mode = argv[1];
  if (strcmp(mode, "-s") == 0)
  {
    size_t chunk_size = strtoul(argv[2], NULL, 10);
    const char *output_dir = argv[4];
    const char *input_file = argv[6];
    rs = split_file(input_file, output_dir, chunk_size);
  }
  else
  {
    const char *output_file = argv[3];
    int num_chunks = argc - 5;
    char **file_chunks = &argv[5];
    rs = join_files(file_chunks, num_chunks, output_file);
  }

  return rs;
}
