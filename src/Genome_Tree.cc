#include "Genome_Tree.hpp"

//constructs the genome tree using two recusion functions
GenomeTree::GenomeTree(std::string first, std::string second) {
    root_ = new TreeNode(0, "", first, second);
    minimum_ = root_->minimize();
}

// outputs all possible genomes and stores them in genomes_
std::vector<std::string> GenomeTree::GenomeStrings() {
    std::vector<std::string> raw = root_->GenomeString();
    for (auto str : raw) {
        AddString(str);
    }
    return genomes_;
}

// helper function to test uniqueness for GenomeStrings
bool GenomeTree::AddString(std::string string) {
    for (size_t i = 0; i < genomes_.size(); i++) {
        if (genomes_[i] == string) {
            return false;
        }
    }
    genomes_.push_back(string);
    return true;
}
