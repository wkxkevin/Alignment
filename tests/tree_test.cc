#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Genome_Tree.hpp"
#include "Tree_Node.hpp"

using namespace std;

TEST_CASE("Trivial Solutions") {
    GenomeTree gtalignment("", "");
    REQUIRE(gtalignment.GetMinimum() == 0);

    GenomeTree gtalignment2("A", "C");
    REQUIRE(gtalignment2.GetMinimum() == 2);
    std::vector<std::string> test2 = gtalignment2.GenomeStrings();
    REQUIRE(std::find(begin(test2), end(test2), "AC") != end(test2));
    REQUIRE(std::find(begin(test2), end(test2), "CA") != end(test2));
    REQUIRE(test2.size() == 2);
    REQUIRE(std::find(begin(test2), end(test2), "CC") == end(test2));
    REQUIRE(std::find(begin(test2), end(test2), "AA") == end(test2));

    GenomeTree gtalignment3("G", "G");
    REQUIRE(gtalignment3.GetMinimum() == 1);
    std::vector<std::string> test3 = gtalignment3.GenomeStrings();
    REQUIRE(std::find(begin(test3), end(test3), "G") != end(test3));
    REQUIRE(std::find(begin(test3), end(test3), "C") == end(test3));

}

TEST_CASE("Simple Alignments") {
    GenomeTree gtalignment("TG", "AG");
    std::vector<std::string> test = gtalignment.GenomeStrings();
    REQUIRE(gtalignment.GetMinimum() == 2);
    REQUIRE(test.size() == 2);
    REQUIRE(std::find(begin(test), end(test), "TAG") != end(test));
    REQUIRE(std::find(begin(test), end(test), "ATG") != end(test));

    GenomeTree gtalignment2("TGT", "AGA");
    std::vector<std::string> test2 = gtalignment2.GenomeStrings();
    REQUIRE(gtalignment2.GetMinimum() == 4);
    REQUIRE(test2.size() == 4);
    REQUIRE(std::find(begin(test2), end(test2), "TAGTA") != end(test2));
    REQUIRE(std::find(begin(test2), end(test2), "TAGAT") != end(test2));
    REQUIRE(std::find(begin(test2), end(test2), "ATGTA") != end(test2));
    REQUIRE(std::find(begin(test2), end(test2), "ATGAT") != end(test2));
}

TEST_CASE("Complex Alignments") {
    GenomeTree gtalignment("TTGCT", "AGATT");
    std::vector<std::string> test = gtalignment.GenomeStrings();
    REQUIRE(gtalignment.GetMinimum() == 6);
    REQUIRE(test.size() == 13);
    REQUIRE(std::find(begin(test), end(test), "TTAGCATT") != end(test));
    REQUIRE(std::find(begin(test), end(test), "ATTGATCT") != end(test));

    GenomeTree gtalignment2("CAGTA", "TACGA");
    std::vector<std::string> test2 = gtalignment2.GenomeStrings();
    REQUIRE(gtalignment2.GetMinimum() == 4);
    REQUIRE(test2.size() == 3);
    REQUIRE(std::find(begin(test2), end(test2), "CTACGTA") != end(test2));
    REQUIRE(std::find(begin(test2), end(test2), "TCACGTA") != end(test2));
    REQUIRE(std::find(begin(test2), end(test2), "TACAGTA") != end(test2));
}

TEST_CASE("Triple Alignment") {
    GenomeTree gtalignment("TGC", "AGA");
    std::vector<std::string> test = gtalignment.GenomeStrings();

    std::vector<std::string> triple;
    for (auto str : test) {
        GenomeTree gtalignment2(str, "CCA");
        std::vector<std::string> test2 = gtalignment2.GenomeStrings();
        if (gtalignment2.GetMinimum() == 4) {
            for (auto str2 : test2) {
                bool unique = true;
                for (size_t i = 0; i < triple.size(); i++) {
                    if (triple[i] == str2) {
                        unique = false;
                    }
                }
                if (unique) {
                    triple.push_back(str2);
                }
            }
        }
    }
    REQUIRE(triple.size() == 8);
    REQUIRE(std::find(begin(triple), end(triple), "TACGCA") != end(triple));
    REQUIRE(std::find(begin(triple), end(triple), "ATCGCA") != end(triple));
    REQUIRE(std::find(begin(triple), end(triple), "CATGCA") != end(triple));
}
