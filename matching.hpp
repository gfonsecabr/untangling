#ifndef MATCHING_HPP
#define MATCHING_HPP

#include <sstream>
#include <vector>
#include "chord.hpp"


class Matching {
  std::vector<Chord> chords;
public:

  Matching(std::vector<Chord> _chords) {
    chords = _chords;
    std::sort(chords.begin(), chords.end());
    chords.shrink_to_fit();
  }

  // c++20 to be able to use Matching as key in std::set
  auto operator<=>(const Matching&) const = default;

  Matching flip(Chord s1, Chord s2) const {
    Matching m = *this;
    for(Chord &c : m.chords) {
      if(c.red == s1.red)
        c.blue = s2.blue;
      else if (c.red == s2.red)
        c.blue = s1.blue;
    }

    return m;
  }

  std::vector<Matching> allFlips() const {
    std::vector<Matching> ret;

    for(auto i = chords.begin(); i != chords.end(); ++i) {
      for(auto j = i; ++j != chords.end();) {
        if(i->intersects(*j))
          ret.push_back(flip(*i,*j));
      }
    }
    return ret;
  }

  std::string str() const {
    std::stringstream ss;
    for(Chord c : chords)
      ss << (int)c.red << "=>" << (int)c.blue << " ";

    std::string s = ss.str();
    s.pop_back();
    return s;
  }
};

#endif
