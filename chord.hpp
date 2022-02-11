#ifndef CHORD_HPP
#define CHORD_HPP

// Type for the positions around a circle
using ang = signed char;

struct Chord {
  ang red, blue;

  Chord(ang _red, ang _blue) {
    red = _red;
    blue = _blue;
  }

  // c++20 to be able to use Chord as part of a key in std::set
  auto operator<=>(const Chord&) const = default;

  ang min() const {
    return red < blue ? red : blue;
  }

  ang max() const {
    return red < blue ? blue : red;
  }

  bool side(ang a) const {
    return min() < a && a < max();
  }

  bool intersects(Chord c) const {
    return c.side(red) != c.side(blue);
  }
};

#endif
