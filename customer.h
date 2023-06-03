#ifndef Customer_h
#define Customer_h
#include "transaction.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Customer {
  friend ostream &operator<<(ostream &os, const Customer &c) {
    os << c.getFirstName() << " " << c.getLastName() << " #"
       << c.getCustomerID();
    return os;
  }

public:
  Customer(string firstName, string lastName, int id);

  void addToHistory(Transaction *t);
  void outputHistory();
  string getFirstName() const;
  string getLastName() const;
  int getCustomerID() const;
  void borrowMovie(char genre, int index);
  void returnMovie(char genre, int index);
  bool isCurrentlyBorrowing(char genre, int index);

private:
  int customerID;
  string firstName;
  string lastName;
  vector<Transaction *> history;
  vector<pair<char, int>>
      currentlyBorrowing; // Keeps track of the movies currently being borrowed.
};

#endif /* Customer_h */