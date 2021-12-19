#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Alignment.hpp"

using namespace std;

TEST_CASE("Alignment::getGenome", "[getGenome]") {
  Alignment a("TGA", "GCA");
  REQUIRE(a.getGenome() != "TGA");
  REQUIRE(a.getGenome() != "GCA");
  REQUIRE(a.getGenome() == "TGCA");
  
  Alignment a2("T", "a");
  REQUIRE(a2.getGenome() == "T");

  Alignment a3("A", "a");
  REQUIRE(a3.getGenome() == "A");

  Alignment a4("tagagt", "tgacag");
  REQUIRE(a4.getGenome() == "TAAGCATT");

  Alignment a5("CACGGTTGCGCGTCCGTATCAAGATCCTCTTAATAAGCCCCCGTCACTGT", "TGGTTGTAGAGCCCAGGACGGGTTGGCCAGATGTGCGACTATATCGCTTA");
  REQUIRE(a5.getGenome() == "CACACGGTCTACCACTGTCAGTGACGGGGTGGCACCTTACCGTGATTAGCCCCTGGCCCCCGTCAGCTGGA");
}

TEST_CASE("Alignment::Assert_Valid_Strand", "[Assert_Valid_Strand]") {
  string strand = "ATGCTAGC";
  Alignment a("ATGC", "GTAC");
  REQUIRE(a.Assert_Valid_Strand(strand, nullptr));

  strand = "123";
  REQUIRE(!a.Assert_Valid_Strand(strand, nullptr));

    strand = "";
  REQUIRE(!a.Assert_Valid_Strand(strand, nullptr));
}
