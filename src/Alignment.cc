#include "Alignment.hpp"

#include <stdexcept>
#include <algorithm>

using namespace std;

Alignment::Alignment(string first, string second){
  //capitalize both strings before checking and storing
  transform(first.begin(), first.end(), first.begin(), ::toupper);
  transform(second.begin(), second.end(), second.begin(), ::toupper);

  //ensure strands are valid
  int* location_of_invalid = nullptr;
  if(!Assert_Valid_Strand(first, location_of_invalid) || !Assert_Valid_Strand(second, location_of_invalid) ){
    throw invalid_argument("Contains Invalid Nucleotide");
  }
  first_string_ = first;
  second_string_ = second;

  //Setup rest of the table
  //Examples use strands: TGA, GCA

  //set up an empty table
  /* scores for each node
  ~   ~   ~   ~
  ~   ~   ~   ~
  ~   ~   ~   ~
  ~   ~   ~   ~
  */
  table_ = new Alignment_Node**[first_string_.size()];
  for(int i = 0; i < (int)first_string_.size(); i++) {
    table_[i] = new Alignment_Node*[second_string_.size()];
  }

  //Set up top left node
  /* scores for each node
  0   ~   ~   ~
  ~   ~   ~   ~
  ~   ~   ~   ~
  ~   ~   ~   ~
  */
  table_[0][0] = new Alignment_Node(first_string_[0], second_string_[0], 0, N);

  //set up the first row
  /* scores for each node
  0  -1  -2  -3
  ~   ~   ~   ~
  ~   ~   ~   ~
  ~   ~   ~   ~
  */
  for(uint i = 1; i < first_string_.length(); i++) {
    table_[i][0] = new Alignment_Node(first_string_[i], second_string_[0], skip_score*i, LEFT);
  }

  //set up the first column
  /* scores for each node
  0  -1  -2  -3
  -1  ~   ~   ~
  -2  ~   ~   ~
  -3  ~   ~   ~
  */
  for(uint i = 1; i < second_string_.length(); i++) {
    table_[0][i] = new Alignment_Node(first_string_[0], second_string_[i], skip_score*i, UP);
  }

  //change the rest of the row
  /* scores for each node
   0  -1  -2  -3
  -1  -2   4   3
  -2  -3   3   9
  -3  -4   2   8
  */
  /*
  take node [1][1]
  up score + skip score(-1) = -2
  diagonal score + mismatch score(-3) = -3
  left score + skip score(-1) = -2
  since the max score is -2 we take that score, however there is a tie
  as such we shall assume to always take up over left
  therefore [1][1] has a score of -2 with best direction up
  now take node [3][2]
  up score + skip score(-1) = 2
  diagonal score + match score(5) = 9
  left score + skip score(-1) = 2
  here is max score is diagonal, node [3][2] carries score 9 with best  direction diagonal
  */


  for(uint row = 1; row < first_string_.length(); row++) {
    for(uint col = 1; col < second_string_.length(); col++) {
      int diag_score; // score for the diagonal which depends on a match/mismatch
      if(first_string_[row] == second_string_[col]) {
        diag_score = match_score;
      } else {
        diag_score = missmatch_score;
      }

      int best_score = table_[row][col-1] -> getScore() + skip_score;
      Direction best_direction = UP;

      //check if diagonal is better
      int temp = table_[row-1][col-1] -> getScore() + diag_score;
      if(best_score < temp) {
        best_score = temp;
        best_direction = DIAG;
      }

      //check if left is better
      temp = table_[row-1][col] -> getScore() + skip_score;
      if(best_score < temp) {
        best_score = temp;
        best_direction = LEFT;
      }

      //declare the node
      table_[row][col] = new Alignment_Node(first_string_[row], second_string_[col], best_score, best_direction);
    }
  }
  
  //find genome
  int curr_row = first_string_.size()-1;
  int curr_col = second_string_.size()-1;
  while(table_[curr_row][curr_col] -> getDirection() != N) {
    switch(table_[curr_row][curr_col] -> getDirection()) {
      case UP:
        genome_.insert(genome_.begin(), second_string_[curr_col]);
        curr_col--;
        break;
      case LEFT:
        genome_.insert(genome_.begin(), first_string_[curr_row]);
        curr_row--;
        break;
      case DIAG:
        genome_.insert(genome_.begin(), first_string_[curr_col]); //we default to first stirng for mismatches
        curr_row--;
        curr_col--;
        break;
      default:
        break;
    }
  }
  if (!first_string_.empty()) {
    genome_.insert(genome_.begin(), first_string_[0]);
  }
    
}

string Alignment::getGenome(){
  return genome_;
}

int Alignment::getScore(){
  return alignment_score_;
}

Alignment_Node*** Alignment::getTable() {
  return table_;
}

bool Alignment::Assert_Valid_Strand(string strand, int* location){
  location = nullptr; //ensures the location starts at null
  if (strand.empty()) {
    return false;
  }
  for(int i = 0; i < (int)strand.size(); i++) {
    if(strand[i] != 'A' && strand[i] != 'T' && strand[i] != 'C' && strand[i] != 'G') {
      location = &i;
      return false;
    }
  }
  return true;
}
