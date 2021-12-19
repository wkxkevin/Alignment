#ifndef ALIGNMENT_NODE_HPP
#define ALIGNMENT_NODE_HPP

#include <string>
#include <vector>
using namespace std;

enum Direction {UP, LEFT, DIAG, N}; // nil is for the original node and the original node only

class Alignment_Node {
  public:
    Alignment_Node(const char first, const char second, const int score, const Direction dir);
    Direction getDirection();
    int getScore();
  private:
    //the two Nucleotide that are being matched
    char first_nucleotide_;
    char second_nucleotide_;

    //maintains the score of the node(which is the best of the top left 3 scores)
    int node_score_;

    //stores the best direction to go to
    Direction best_direction_;
};

#endif  // CLICKB*AIT_CHANNEL_HPP
