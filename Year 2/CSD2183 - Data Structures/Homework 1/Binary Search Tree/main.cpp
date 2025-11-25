#include "balanced_bst.h"
#include "import_numbers_from_file.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return EXIT_FAILURE;
  }

  // Data import
  std::string filename = argv[1];
  std::vector<double> a = importNumbersFromFile(filename);

  // Create balanced BST with the imported elements
  BalancedBST bst(a);

  // Output
  std::cout << "Elements inserted into the BST:" << std::endl;
  bst.printTreeStructure();

  return 0;
}
