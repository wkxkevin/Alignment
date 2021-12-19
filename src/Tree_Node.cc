#include "Tree_Node.hpp"

// Constructor for each node. Creates child nodes if more characters are left.
TreeNode::TreeNode(int value, std::string genome, std::string first, std::string second) {
    node_value_ = value;
    node_genome_ = genome;
    // Creates "down" node
    if (!first.empty()) {
        children[0] = new TreeNode(node_value_ + 1, node_genome_ + first.at(0), first.substr(1), second);
        if (!second.empty()) {
            // Creates "diagonal" node, either with match or mismatch
            if (first.at(0) == second.at(0)) {
                children[2] = new TreeNode(node_value_, node_genome_ + first.at(0), first.substr(1), second.substr(1));
            } else {
                children[2] = new TreeNode(node_value_ + 3, node_genome_ + first.at(0) + second.at(0), first.substr(1), second.substr(1));
            }
        }
    } else {
        // Creates a leaf node
        if (second.empty()) {
            minimized = true;
        }
    }
    // Creates "right" node
    if (!second.empty()) {
        children[1] = new TreeNode(node_value_ + 1, node_genome_ + second.at(0), first, second.substr(1));
    }
}

// Recusive function that sets all parent nodes to have the lowest minimization value of their child nodes
int TreeNode::minimize() {
    // Base case for leaf node
    if (children[0] == nullptr && children[1] == nullptr && children[2] == nullptr) {
        return node_value_;
    }
    // Finds non-null children and returns the lowest value
    int down_value = 999999;
    int right_value = 999999;
    int diag_value = 999999;
    if (children[0] != nullptr) {
        down_value = children[0]->minimize();
    }
    if (children[1] != nullptr) {
        right_value = children[1]->minimize();
    }
    if (children[2] != nullptr) {
        diag_value = children[2]->minimize();
    }
    if (down_value <= right_value && down_value <= diag_value) {
        minimized = true;
        node_value_ = down_value;
        return down_value;
    }
    if (right_value <= diag_value && right_value <= down_value) {
        minimized = true;
        node_value_ = right_value;
        return right_value;
    }
    // Establishes node's data
    minimized = true;
    node_value_ = diag_value;
    return diag_value;
}

// generates all the genome strings from the subset of optimizated child nodes
std::vector<std::string> TreeNode::GenomeString() {
    std::vector<std::string> output;
    // Base case for leaf node with full string
    if (children[0] == nullptr && children[1] == nullptr && children[2] == nullptr) {
        output.push_back(node_genome_);
    } else {
        // Returns all strings with minimized values
        if (children[0] != nullptr && node_value_ == children[0]->node_value_) {
            std::vector<std::string> A = children[0]->GenomeString();
            output.insert(output.end(), A.begin(), A.end());
        }
        if (children[1] != nullptr && node_value_ == children[1]->node_value_) {
            std::vector<std::string> B = children[1]->GenomeString();
            output.insert(output.end(), B.begin(), B.end());
        }
        if (children[2] != nullptr && node_value_ == children[2]->node_value_) {
            std::vector<std::string> C = children[2]->GenomeString();
            output.insert(output.end(), C.begin(), C.end());
        }
    }
    return output;
}
