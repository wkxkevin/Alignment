#include "Alignment_Node.hpp"

Alignment_Node::Alignment_Node(char first, char second, int score, Direction dir){
  first_nucleotide_ = first;
  second_nucleotide_ = second;
  best_direction_ = dir;
  node_score_ = score;
}

Direction Alignment_Node::getDirection(){
  return best_direction_;
}

int Alignment_Node::getScore() {
  return node_score_;
}
