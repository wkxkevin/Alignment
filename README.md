# final-project-rileydavidkevin
final-project-rileydavidkevin created by GitHub Classroom

Use git clone to download the project to your machine.

To use the table implementation, construct an Alignment object with Alignment(string, string), where the strings are the two strands of DNA you wish to compare.
Then, use getGenome() to return the resutling string from the alignment, getScore() to return that string's minimization score, and getTable() to return the constructed alignment table.

To use the tree implementation, construct a GenomeTree object with GenomeTree(string, std), where the strings are the two strands of DNA you wish to compare.
Then, use GenomeStrings() to return a vector of equivelently minimized strings. After, use GetGenomes() to return the vector again. Finally, GetMinimum() returns the lowest minimization score.

Use the following compiler commands to run the test suite (modify for filepaths if necessary):
Test.cc:
"clang++-10 -std=c++20 -Wall -Wextra -Werror -pedantic Alignment_Node.cc Alignment.cc Tree_Node.cc Genome_Tree.cc test.cc -o align"
"./align"

Tree_Test.cc:
"clang++-10 -std=c++20 -Wall -Wextra -Werror -pedantic Alignment_Node.cc Alignment.cc Tree_Node.cc Genome_Tree.cc tree_test.cc -o tree"
"./tree"
