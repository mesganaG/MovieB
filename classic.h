#ifndef Classic_h
#define Classic_h
#include "movie.h"
#include <cassert>

class Classic : public Movie {
public:
  Classic(int stock, string const &director, string const &title,
          const string &majorActorFirstName, const string &majorActorLastName,
          int year, int month)
      : Movie(stock, title, director, year, 'C') {
    this->majorActorFirstName = majorActorFirstName;
    this->majorActorLastName = majorActorLastName;
    this->month = month;
  }

  string getMajorActorFirstName() const { return this->majorActorFirstName; }

  string getMajorActorLastName() const { return this->majorActorLastName; }

  int getMonth() const { return month; }

  bool equals(Movie *other) const override {
    assert(other != nullptr);
    if (other->Type() != this->Type()) {
      return false;
    }
    auto *that = dynamic_cast<Classic *>(other);
    return this->Director() == that->Director() &&
           this->Title() == that->Title() &&
           this->Year() == that->Year() &&
           this->month == that->getMonth() &&
           this->getMajorActorFirstName() == that->getMajorActorFirstName() &&
           this->getMajorActorLastName() == that->getMajorActorLastName();
  }

  bool lessThan(Movie *other) const override {
    assert(other != nullptr);
    auto *that = dynamic_cast<Classic *>(other);
    // Lets sort by release year, release month, first name, then last name.
    if (this->Year() != that->Year()) {
      return this->Year() < other->Year();
    }
    if (this->getMonth() != that->getMonth()) {
      return this->getMonth() < that->getMonth();
    }
    if (this->getMajorActorFirstName() != that->getMajorActorFirstName()) {
      return this->getMajorActorFirstName() < that->getMajorActorFirstName();
    }
    if (this->getMajorActorLastName() != that->getMajorActorLastName()) {
      return this->getMajorActorLastName() < that->getMajorActorLastName();
    }
    return false;
  }

  bool greaterThan(Movie *other) const override {
    assert(other != nullptr);
    auto *that = dynamic_cast<Classic *>(other);
    // Lets sort by release year, release month, first name, then last name.
    if (this->Year() != that->Year()) {
      return this->Year() > other->Year();
    }
    if (this->getMonth() != that->getMonth()) {
      return this->getMonth() > that->getMonth();
    }
    if (this->getMajorActorFirstName() != that->getMajorActorFirstName()) {
      return this->getMajorActorFirstName() > that->getMajorActorFirstName();
    }
    if (this->getMajorActorLastName() != that->getMajorActorLastName()) {
      return this->getMajorActorLastName() > that->getMajorActorLastName();
    }
    return false;
  }

private:
  string majorActorFirstName;
  string majorActorLastName;
  int month;
};
#endif /* Classic_h */