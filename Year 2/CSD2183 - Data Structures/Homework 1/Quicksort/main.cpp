#include <iostream>
#include <vector>
#include "quicksort.h"
#include "median_functions.h"
#include "import_numbers_from_file.h"

using namespace std;

void print_vector(const std::vector<int> &v) {
  for (const auto &key : v) {
    cout << key << " ";
  }
  cout << '\n';
}

bool check_substring(const std::string &filename, const std::string &prefix) {
  return (filename.substr(0, prefix.size()) == prefix);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return EXIT_FAILURE;
  }
  const std::string prefix_find_median = "find_median";
  const std::string prefix_find_group_medians = "find_group_medians";
  const std::string prefix_find_median_of_medians = "find_median_of_medians";
  const std::string prefix_partition = "partition";
  const std::string prefix_quicksort = "quicksort";

  // Data import
  string filename = argv[1];
  vector<int> a = importNumbersFromFile(filename);

  // Set k to a value of 5 or higher
  int k = 5;
  
  // We aim to test all the functions find_median, find_group_medians, 
  // find_median_of_medians,partition and quicksort
  // The names of the test file should always start with the name of the function (e.g. find_median_test_0.dat)
  if (check_substring(filename, prefix_find_median)) {
    int median = find_median(a, 0, a.size() - 1);
    cout << median << '\n';
  }
  else if (check_substring(filename, prefix_find_group_medians)) {
    std::vector<int> group_medians = find_group_medians(a, 0, a.size() - 1, k);
    print_vector(group_medians);
  }
  else if (check_substring(filename, prefix_find_median_of_medians)) {
    int median_of_medians = find_median_of_medians(a, 0, a.size() - 1, k);
    cout << median_of_medians << '\n';
  }
  else if (check_substring(filename, prefix_partition)) {
    int pivot_index = partition(a, 0, a.size() - 1, k);
    cout << pivot_index << '\n';
  }
  else if (check_substring(filename, prefix_quicksort)) {
    quicksort(a, 0, a.size() - 1, k);
    print_vector(a);
  }
  else {
    cerr << "Invalid filename" << endl;
    return EXIT_FAILURE;
  }
  return 0;
}