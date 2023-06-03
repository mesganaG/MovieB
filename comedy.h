#ifndef Comedy_h
#define Comedy_h

#include "movie.h"

class Comedy : public Movie {
public:
  Comedy(int stock, const string &director, const string &title, int year)
      : Movie(stock, title, director, year, 'F') {}

  bool equals(Movie *other) const override {
    return this->type == other->Type() &&
           this->Director() == other->Director() &&
           this->Title() == other->Title() &&
           this->Year() == other->Year();
  }

  bool lessThan(Movie *other) const override {

    if (this->Title() != other->Title()) {
      return this->Title() < other->Title();
    }
  
    if (this->Year() != other->Year()) {
      return this->Year() < other->Year();
    }
    return false;
  }

  bool greaterThan(Movie *other) const override {
    
    if (this->Title() != other->Title()) {
      return this->Title() > other->Title();
    }
    
    if (this->Year() != other->Year()) {
      return this->Year() > other->Year();
    }
    return false;
  }
};
#endif /* Comedy_h */