#ifndef Movie_h
#define Movie_h

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
using namespace std;

class Movie {
  friend ostream &operator<<(ostream &out, const Movie &other) {

    out << "Genre/Title: " + other.type<<", " + other.title
       << ", Director: " << other.director
       << ", Released: " << other.year << ", Stock: " << other.stock
       << " Currently being borrowed: " << other.Borrowed();
    return out;
  }

public:
  Movie(int stock, const string &title, const string &director, int year,
        char type) {
    this->stock = stock;
    this->title = title;
    this->director = director;
    this->borrowed = 0;
    this->year = year;
    this->type = type;
  }

  void set_director(const string &director) { this->director = director; }

  void set_title(const string &title) { this->title = title; }

  void set_year(int year) { this->year = year; }

  void set_stock(int stock) { this->stock = stock; }

  void set_borrowed(int num) { this->borrowed = num; }

  string Director() const { return this->director; }

  string Title() const { return this->title; }

  int Year() const { return this->year; }

  int Stock() const { return this->stock; }

  int Borrowed() const { return this->borrowed; }

  char Type() const { return this->type; }

  bool operator==(Movie &other) const { return equals(&other); }

  bool operator<(Movie &other) const { return lessThan(&other); }

  bool operator>(Movie &other) const { return greaterThan(&other); }

  virtual bool equals(Movie *other) const = 0;
  virtual bool lessThan(Movie *other) const = 0;
  virtual bool greaterThan(Movie *other) const = 0;

protected:
  string director;
  string title;
  int year;
  int stock;
  int borrowed = 0;
  char type;
};

#endif /* Movie_h */