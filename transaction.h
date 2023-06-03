#ifndef Transaction_h
#define Transaction_h
#include "Movie.h"
#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Transaction {
  friend ostream &operator<<(ostream &os, const Transaction &t) {
    os << t.customer << " " << t.action << "ed: " << t.movieTitle << " by "
       << t.movieDirector << ", " << t.movieGenre << endl;
    return os;
  }

public:
  Transaction(char genre, string movieTitle, string movieDirector,
              string customerName, char transactionType);

private:
  string movieGenre;
  string movieTitle;
  string movieDirector;
  string customer;
  string action;
};

#endif /* Transaction_h */