#include "customer.h"
#include <algorithm>
using namespace std;

Customer::Customer(string firstName, string lastName, int id) {
  this->firstName = move(firstName);
  this->lastName = move(lastName);
  this->customerID = id;
}

void Customer::addToHistory(Transaction *t) { history.push_back(t); }

void Customer::outputHistory() {
  cout << "History of transactions for " << this->getFirstName() << " "
       << this->getLastName() << " #" << this->getCustomerID() << ":" << endl;
  if (history.empty()) {
    cout << "History is empty" << endl;
    return;
  }
  for (auto *t : this->history) {
    cout << *t;
  }
}

string Customer::getFirstName() const { return this->firstName; }

string Customer::getLastName() const { return this->lastName; }

int Customer::getCustomerID() const { return this->customerID; }

void Customer::borrowMovie(char genre, int index) {
  currentlyBorrowing.emplace_back(make_pair(genre, index));
}

void Customer::returnMovie(char genre, int index) {
  for (int i = 0; i < currentlyBorrowing.size(); i++) {
    if (currentlyBorrowing[i].first == genre &&
        currentlyBorrowing[i].second == index) {
      currentlyBorrowing.erase(currentlyBorrowing.begin() + i);
      return;
    }
  }
}

bool Customer::isCurrentlyBorrowing(char genre, int index) {
  return count(currentlyBorrowing.begin(), currentlyBorrowing.end(),
               make_pair(genre, index)) != 0;
}