#ifndef Drama_h
#define Drama_h

#include "movie.h"

class Drama : public Movie {
public:
  Drama(int stock, const string &director, const string &title, int year)
      : Movie(stock, title, director, year, 'D') {}

  bool equals(Movie *other) const override {
    return this->type == other->Type() &&
           this->Director() == other->Director() &&
           this->Title() == other->Title() &&
           this->Year() == other->Year();
  }

  bool lessThan(Movie *other) const override {
    // In drama, we first sort by director
    if (this->Director() != other->Director()) {
      return this->Director() < other->Director();
    }
    // Then sort by title
    if (this->Title() != other->Title()) {
      return this->Title() < other->Title();
    }
    // If somehow it still doesn't pass, just return false, they're probably the
    // same.
    return false;
  }

  bool greaterThan(Movie *other) const override {
    // In drama, we first sort by director
    if (this->Director() != other->Director()) {
      return this->Director() > other->Director();
    }
    // Then sort by title
    if (this->Title() != other->Title()) {
      return this->Title() > other->Title();
    }
    // If somehow it still doesn't pass, just return false, they're probably the
    // same.
    return false;
  }
};

#endif /* Drama_h */