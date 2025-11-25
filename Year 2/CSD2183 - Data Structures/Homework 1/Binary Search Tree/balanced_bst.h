#ifndef BALANCED_BST_H
#define BALANCED_BST_H

#include <functional>
#include <vector>

class BalancedBST {
public:
  // Constructor that builds a balanced BST from a vector of keys
  BalancedBST(const std::vector<double> &keys);

  // Destructor to clean up the tree
  ~BalancedBST();

  // Method to print the structure of the tree
  void printTreeStructure() const;

private:
  struct Node {
    double key;
    Node *left;
    Node *right;
    Node *parent;
    Node(double k);
  };

  Node *root;
  size_t size;

  // Helper method to print the structure of the subtree rooted at `node`
  void printTreeStructure(const Node *node,
                          const std::function<int(const Node *)> &height) const;

  // Helper method to delete a subtree
  void deleteSubtree(Node *node);
};

#endif // BALANCED_BST_H