#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <string>
#include <vector>

class TreeNode {
    public:
        // recursive constructor for a node
        TreeNode(int value, std::string genome, std::string first, std::string second);
    
        // recursive function that sets parent nodes to have child's minimation value
        int minimize();
        
        // Creates a vector of minimized genome strings for genome tree
        std::vector<std::string> GenomeString();
    private: 
        // in the formate of [down, right, diag]
        TreeNode* children[3] = {nullptr, nullptr, nullptr};
    
        // minimization value, signals how "good" the path is
        int node_value_ = 0;
    
        // string 
        std::string node_genome_;
    
        // signals a complete branch
        bool minimized = false;
};

#endif
