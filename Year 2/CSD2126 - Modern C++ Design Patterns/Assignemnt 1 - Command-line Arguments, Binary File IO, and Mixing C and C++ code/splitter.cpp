/*!************************************************************************
  \file splitter.cpp

  \author Bryan Ang Wei Ze

  \par DP email: bryanweize.ang\@digipen.edu

  \par Course: CSD2126 Modern C++ Design Patterns

  \par Programming Assignment #1

  \date 14-09-2024
  
  \brief
  This C++ source file defines a function that splits files into smaller chunks
  and joins split files into a single file, which can be used by both C and C++
  source files.
**************************************************************************/

#include "splitter.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <sstream>
#include <vector>

constexpr int FOUR_K {4096};

std::string generate_output_filename(const std::string& prefix, int file_count)
{
    std::ostringstream oss;
    oss << prefix << std::setw(4) << std::setfill('0') << file_count;
    return oss.str();
}

SplitResult split_file(const std::string& input_file, const std::string& output_prefix, size_t chunk_size)
{
  // input file cannot be opened
  std::ifstream input(input_file, std::ios::binary);
  if (!input)
  {
    return E_BAD_SOURCE;
  }
  
  // set read buffer size to FOUR_K if user-specified chunk size exceends that
  size_t buffer_size = std::min(chunk_size, static_cast<size_t>(FOUR_K));
  char* buffer{nullptr};
  
  // test for failed heap memory allocation
  try
  {
    buffer = new char[buffer_size];
  }
  catch (const std::exception& e)
  {
    return E_NO_MEMORY;
  }
  
  int file_count = 0;
  size_t bytes_in_current_chunk = 0;
  std::ofstream output;

  // read input file that needs to be split
  while (input)
  {
    input.read(buffer, buffer_size);

    // number of remaining bytes that needs to be read from input file
    std::streamsize bytes_read = input.gcount();

    // if there are remaining bytes that need to be read
    if (bytes_read > 0)
    {
      size_t bytes_to_write = bytes_read;
      size_t buffer_offset = 0;

      while (bytes_to_write > 0)
      {
        // create a new output file if the previous one size is reached the chunk size
        if (!output.is_open())
        {
          std::string output_file = generate_output_filename(output_prefix, ++file_count);
          output.open(output_file, std::ios::binary);

          // output file cannot be created
          if (!output)
          {
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
        size_t bytes_to_write_now = std::min(bytes_remaining_in_chunk, bytes_to_write);

        // write from read buffer to chunk
        output.write(buffer + buffer_offset, bytes_to_write_now);

        /* update number of bytes in current chunk, buffer offset for the next write and
        remaining number of bytes in read buffer */
        bytes_in_current_chunk += bytes_to_write_now;
        buffer_offset += bytes_to_write_now;
        bytes_to_write -= bytes_to_write_now;

        // current chunk is full
        if (bytes_in_current_chunk == chunk_size)
        {
          output.close();
        }
      }
    }
  }

  if (output.is_open())
  {
    output.close();
  }

  delete[] buffer;
  return E_SPLIT_SUCCESS;
}

SplitResult join_files(const std::vector<std::string>& file_chunks, const std::string& output_file)
{
  std::ofstream output(output_file, std::ios::binary);
  char* buffer{nullptr};

  // output file cannot be created
  if (!output)
  {
    return E_BAD_DESTINATION;
  }

  // test for failed heap memory allocation
  try
  {
    buffer = new char[FOUR_K];
  }
  catch (const std::exception& e)
  {
    return E_NO_MEMORY;
  }

  for (const std::string& chunk: file_chunks)
  {
    std::ifstream input(chunk, std::ios::binary);

    while (input)
    {
      input.read(buffer, FOUR_K);
      std::streamsize bytes_read = input.gcount();
      if (bytes_read > 0)
      {
        output.write(buffer, bytes_read);
      }
    }
    input.close();
  }

  delete[] buffer;
  output.close();
  return E_JOIN_SUCCESS;
}

SplitResult split_join(int argc, char *argv[])
{
  SplitResult rs = E_NO_ACTION;

  // user did not provide enough cmd line arguments for the program
  if (argc < 7)
  {
    return rs;
  }
  
  size_t chunk_size = 0;
  std::vector<std::string> file_chunks;
  std::string output_dir;
  std::string input_file;
  std::string mode;

  // parse cmd line arguments and split/join files accordingly
  mode = argv[1];
  if (mode == "-s")
  {
    chunk_size = std::stoull(argv[2]);
    output_dir = argv[4];
    input_file = argv[6];
    rs = split_file(input_file, output_dir, chunk_size);
  }
  else
  {
    output_dir = argv[3];
    for (int i = 5; i < argc; ++i)
    {
      file_chunks.push_back(argv[i]);
    }
    rs = join_files(file_chunks, output_dir);
  }

  return rs;
}