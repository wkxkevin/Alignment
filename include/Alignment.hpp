#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

#include "Alignment_Node.hpp"

#include <vector>
#include <string>

using namespace std;

class Alignment {

  const int skip_score = -1;
  const int match_score = 5;
  const int missmatch_score = -3;

  public:
    Alignment(string first, string second);
    string getGenome();
    int getScore();
    Alignment_Node*** getTable();
  private:
    string genome_; //the aligned genome
    int alignment_score_;  // the score obtained at the end, helps for building trees
    Alignment_Node*** table_; //we shall allocate new memory when cuilding the table, this will be the bottom right node

    // we store the string to make sure we can access it when we need
    string first_string_;
    string second_string_;

    //ensures every strand is valid
    bool Assert_Valid_Strand(const string strand, int* location);

};

#endif  // CLICKBAIT_CHANNEL_HPP
