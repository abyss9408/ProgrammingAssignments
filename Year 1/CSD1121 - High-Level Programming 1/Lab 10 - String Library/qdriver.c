#include <stdio.h>
#include <stdlib.h>

#include "q.h"

/******************************************************************************
 * Memory allocation functions.                                               *
 ******************************************************************************/

void* debug_malloc(size_t size)
{
	printf("Allocating %zu bytes...", size);
	void* result = malloc(size);
	puts(result ? " done." : " failed.");
	return result;
}

void debug_free(void* ptr)
{
	puts("Deallocated data.");
	free(ptr);
}

/******************************************************************************
 * Path testing function.                                                     *
 ******************************************************************************/

void test_folders(
	const char* const parent,
	const char* const separator,
	const char* const folders[], size_t folder_count,
	const char* const folder1[], size_t subfolder1_count,
	const char* const folder2[], size_t subfolder2_count
)
{
	const char* const path = build_path(
		parent,
		separator,
		folders,
		folder_count
	);
	if (!path)
	{
		return;
	}
	describe_string(path);

	const char* const path1 = build_path(
		path,
		separator,
		folder1,
		subfolder1_count
	);
	if (!path1)
	{
		debug_free((void*)path);
		return;
	}
	describe_string(path1);

	find_string(path1, path);
	find_string(path1, folder1[0]);

	compare_string(path,  path1);
	compare_string(path1, path);
	compare_string(path,  path);

	const char* const path2 = build_path(
		path,
		separator,
		folder2,
		subfolder2_count
	);
	if (!path2)
	{
		debug_free((void*)path1);
		debug_free((void*)path);
		return;
	}
	describe_string(path2);

	find_string(path2, path);
	find_string(path2, folder2[0]);

	compare_string(path1, path2);
	compare_string(path2, path1);

	find_string(path1, path2);
	find_string(path2, path1);
	find_string(path1, folder2[0]);
	find_string(path2, folder1[0]);

	debug_free((void*)path2);
	debug_free((void*)path1);
	debug_free((void*)path);
	puts("-------------------------------------------------------------------");
}

/******************************************************************************
 * Main entry point.                                                          *
 ******************************************************************************/

int main(void)
{
	const char* const folders[] = {
		"home",
		"user",
		"files",
		"documents",
		"images"
	};
	const char* const folder1[] = { "20201031" };
	const char* const folder2[] = { "20201201" };

	const size_t folders_count = sizeof(folders) / sizeof(*folders);
	const size_t folder1_count = sizeof(folder1) / sizeof(*folder1);
	const size_t folder2_count = sizeof(folder2) / sizeof(*folder2);

	test_folders(
		"/",
		"/",
		folders, folders_count,
		folder1, folder1_count,
		folder2, folder2_count
	);

	test_folders(
		"c:\\",
		"\\",
		folders, folders_count,
		folder1, folder1_count,
		folder2, folder2_count
	);
}
