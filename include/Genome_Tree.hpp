#ifndef GENOME_TREE_HPP
#define GENOME_TREE_HPP

#include <string>
#include <vector>

#include "Tree_Node.hpp"

// class that contains a tree tracing the DNA alignment of two strings
class GenomeTree {
public:
    // constructor that takes two strings to be aligned
    GenomeTree(std::string first, std::string second);
    
    // output a vector of minimized strings for DNA alignment
    std::vector<std::string> GenomeStrings();
    
    // getters
    std::vector<std::string> GetGenomes() {return genomes_;};
    int GetMinimum() {return minimum_;};
    
    // helper function
    bool AddString(std::string string);
private:
    TreeNode* root_ = nullptr;
    int minimum_;
    std::vector<std::string> genomes_;
};

#endif
