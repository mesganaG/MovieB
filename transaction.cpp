#include "transaction.h"

Transaction::Transaction(char genre, string movieTitle, string movieDirector,
                         string customerName, char transactionType) {
  if (genre == 'F') {
    this->movieGenre = "Comedy";
  } else if (genre == 'D') {
    this->movieGenre = "Drama";
  } else if (genre == 'C') {
    this->movieGenre = "Classic";
  } else {
    cout << "Invalid genre for transaction: " << genre << endl;
  }

  if (transactionType == 'B') {
    this->action = "borrow";
  } else if (transactionType == 'R') {
    this->action = "return";
  } else {
    cout << "Invalid transaction type for transaction: " << transactionType
         << endl;
  }
  this->movieTitle = move(movieTitle);
  this->movieDirector = move(movieDirector);
  this->customer = move(customerName);
}