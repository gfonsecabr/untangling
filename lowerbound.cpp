// Compile with:
// g++ -o lb -Ofast -std=c++20 lowerbound.cpp
// Test de modif
#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>
#include <set>
#include <queue>
#include "matching.hpp"

Matching source(int n) {
  std::vector<Chord> chords;

  for(int i = 1; i < n+2; i += 2) {
    if(i == 2 || i == n+1)
      continue; // These two points do not exist, but the numbering makes calculations easier

    int red1, red2, blue1, blue2;
    if(i % 4 == 3) { // i is blue
      blue1 = i;
      red1 = -(i+3);
      blue2 = -i;
      red2 = i+3;
    }
    else { // i is red
      assert(i % 4 == 1);
      red1 = i;
      blue1 = -(i+3);
      red2 = -i;
      blue2 = i+3;
    }

    chords.push_back(Chord(red1,blue1));
    chords.push_back(Chord(red2,blue2));
  }

  if(chords.size() > n)
    chords.pop_back(); // odd n

  assert(chords.size() == n);

  return Matching(chords);
}

int maxDistance(const Matching &m) {
  std::set<Matching> visited;
  std::queue<std::pair<int,Matching>> fifo;

  fifo.push(std::make_pair(0,m));
  while(!fifo.empty()) {
    auto [d,u] = fifo.front();

    fifo.pop();
    if(visited.count(u) == 0) {
      visited.insert(u);
      std::vector<Matching> flips = u.allFlips();
      if(visited.size() % 1000000 == 0 || flips.empty())
        std::cout << "Visited " << visited.size() << " matchings" << std::endl;
      if(flips.empty())
        return d;
      for(Matching w : flips)
        fifo.push(std::make_pair(d+1,w));
    }
  }

  return -1; // Never reached
}

int calculate(int n) {
  Matching m = source(n);

  return maxDistance(m);
}


int main(int argc, char **argv) {
  std::vector<int> sizes;
  if(argc < 2) {
    for(int i = 2; i <= 20; i++)
      sizes.push_back(i);
  }
  else {
    for(int i = 1; i < argc; i++) {
      sizes.push_back(atoi(argv[i]));
    }
  }

  for(int n : sizes) {
    std::cout << "n = "<< n << std::endl;
    int d = calculate(n);
    std::cout << "d(" << n << ") >= " << d << std::endl;
  }

  return 0;
}
