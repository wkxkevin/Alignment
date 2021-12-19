#include "Alignment.hpp"

#include <iostream>

using namespace std;

int main() {
  Alignment first ("agttaB", "AgTT");
  cout << first.getFirst() << endl;
  cout << first.getSecond() << endl;
}
