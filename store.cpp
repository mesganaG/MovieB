#include "store.h"

Store::Store() { movies = new Inventory(); }

void Store::fillInventory(const string &fileName) {
  string line;
  ifstream inFile(fileName);
  if (!inFile.is_open()) {
    cerr << "file not found";
  }
  while (!inFile.eof()) {
    getline(inFile, line);
    if (line.empty()) {
      break;
    }
    istringstream parser(line);
    string element;
    vector<string> tokens;
    while (getline(parser, element, ',')) {
      if (element[0] == ' ') { // Trim.
        element.erase(0, 1);
      }
      tokens.push_back(element);
    }
    string genre = tokens[0];
    if (genre == "F" || genre == "D") {
      int stock = stoi(tokens[1]);
      string director = tokens[2];
      string title = tokens[3];
      int year = stoi(tokens[4]);
      if (genre == "F") {
        movies->addComedy(stock, director, title, year);
      } else if (genre == "D") {
        movies->addDrama(stock, director, title, year);
      }
    } else if (genre == "C") {
      istringstream iss(tokens[4]);
      int stock = stoi(tokens[1]);
      string director = tokens[2];
      string title = tokens[3];
      string majorActorFirstName;
      string majorActorLastName;
      string releaseMonth;
      string releaseYear;
      iss >> majorActorFirstName >> majorActorLastName >> releaseMonth >>
          releaseYear;
      movies->addClassic(stock, director, title, majorActorFirstName,
                         majorActorLastName, stoi(releaseMonth),
                         stoi(releaseYear));
    } else {
      cerr << "Invalid Movie Type found: " << tokens[0] << endl;
    }
  }
  movies->sortShelves();
  inFile.close();
}

void Store::fillStoreWithCustomers(const string &fileName) {
  string line;
  ifstream inFile;
  inFile.open(fileName);
  if (!inFile.is_open()) {
    cerr << "file not found";
  }
  while (getline(inFile, line)) {
    istringstream parser(line);
    int customerID;
    string firstName;
    string lastName;
    parser >> customerID;
    if (customerID < 10000 && customerID > 999 &&
        !(customers.indexOf(customerID) != -1)) {
      parser >> firstName >> lastName;
      Customer *customer = new Customer(firstName, lastName, customerID);
      customers.put(customerID, customer);
    } else {
      cerr << "Invalid customer ID: " << customerID << endl;
    }
  }
  inFile.close();
}

void Store::processTransactions(const string &fileName) {
  ifstream inFile(fileName);
  string line;
  if (!inFile) {
    cerr << "File not found" << endl;
  }

  while (!inFile.eof()) {
    getline(inFile, line);
    if (line.empty()) {
      break;
    }

    istringstream parse(line);
    string command;
    parse >> command;

    if (command == "B") {
      string iDasString;
      string media;
      string genre;
      parse >> iDasString;
      parse >> media;
      int customerID = stoi(iDasString);
      if (media == "D") { // If our media type is a DVD (only valid media type
                          // in this assignment)
        parse >> genre;
        if (genre == "F") { // If our genre is a comedy... do this
          int year;
          string title;
          string currToken;
          vector<string> tokens;
          while (getline(parse, currToken, ',')) {
            if (currToken[0] == ' ') {
              currToken.erase(0, 1); // Space trimmer.
            }
            tokens.push_back(currToken);
          }
          title = tokens[0];
          year = stoi(tokens[1]);
          int index = movies->indexOfComedy(title, year);
          if (index == -1) {
            cerr << "Comedy Movie not found: " << title << " " << year << endl;
          } else {
            if (customers.indexOf(customerID) != -1) {
              bool borrowed = movies->borrowMovie(genre, index);
              if (borrowed) { // Only adds transaction if movie is successfully
                              // borrowed.
                const auto *c = movies->getComedyMovie(index);
                Transaction *t = new Transaction(
                    'F', c->Title(), c->Director(),
                    customers.get(customerID)->getFirstName() + " " +
                        customers.get(customerID)->getLastName(),
                    'B');
                customers.get(customerID)->borrowMovie('F', index);
                customers.get(customerID)
                    ->addToHistory(t); // Add transaction to customer history.
              }
            } else {
              cerr << "Customer not found : " << customerID << endl;
            }
          }
        } else if (genre == "D") { // If our genre is a drama... do this
          string director;
          string title;
          string currToken;
          vector<string> tokens;
          while (getline(parse, currToken, ',')) {
            if (currToken[0] == ' ') {
              currToken.erase(0, 1); // Space trimmer.
            }
            tokens.push_back(currToken);
          }
          director = tokens[0];
          title = tokens[1];
          int index = movies->indexOfDrama(director, title);
          if (index == -1) {
            cerr << "Drama Movie not found: " << director << " " << title
                 << endl;
          } else {
            if (customers.indexOf(customerID) != -1) {
              bool borrowed = movies->borrowMovie(genre, index);
              if (borrowed) { // Only adds transaction if movie is successfully
                              // borrowed.
                const auto *d = movies->getDramaMovie(index);
                Transaction *t = new Transaction(
                    'D', d->Title(), d->Director(),
                    customers.get(customerID)->getFirstName() + " " +
                        customers.get(customerID)->getLastName(),
                    'B');
                customers.get(customerID)->borrowMovie('D', index);
                customers.get(customerID)
                    ->addToHistory(t); // Add transaction to customer history.
              }
            } else {
              cerr << "Customer not found : " << customerID << endl;
            }
          }
        } else if (genre == "C") { // If our genre is a comedy... do this
          string majorActorFirstName;
          string majorActorLastName;
          int month;
          int year;
          parse >> month >> year;
          parse >> majorActorFirstName >> majorActorLastName;
          int index = movies->indexOfClassic(month, year, majorActorFirstName,
                                             majorActorLastName);
          if (index == -1) {
            cerr << "Classic Movie not found: " << month << " " << year << " "
                 << majorActorFirstName << " " << majorActorLastName << endl;
          } else {
            if (customers.indexOf(customerID) != -1) {
              bool borrowed = movies->borrowMovie(genre, index);
              if (borrowed) { // Only adds transaction if movie is successfully
                              // borrowed.
                const auto *c = movies->getClassicMovie(index);
                Transaction *t = new Transaction(
                    'C', c->Title(), c->Director(),
                    customers.get(customerID)->getFirstName() + " " +
                        customers.get(customerID)->getLastName(),
                    'B');
                customers.get(customerID)->borrowMovie('C', index);
                customers.get(customerID)
                    ->addToHistory(t); // Add transaction to customer history.
              }
            } else {
              cerr << "Customer not found : " << customerID << endl;
            }
          }
        } else {
          cerr << "Invalid genre: " << genre << endl;
        }
      } else {
        cerr << "Invalid media type: " << media << endl;
      }
    } else if (command == "H") {
      int customerID;
      parse >> customerID;
      customers.get(customerID)->outputHistory();
      cout << endl;
    } else if (command == "I") {
      cout << *movies << endl;
    } else if (command == "R") {
      string iDasString;
      string media;
      string genre;
      parse >> iDasString;
      parse >> media;
      int customerID = stoi(iDasString);
      if (media == "D") { // If our media type is a DVD (only valid media type
                          // in this assignment)
        parse >> genre;
        if (genre == "F") { // If our genre is a comedy... do this
          int year;
          string title;
          string currToken;
          vector<string> tokens;
          while (getline(parse, currToken, ',')) {
            if (currToken[0] == ' ') {
              currToken.erase(0, 1); // Space trimmer.
            }
            tokens.push_back(currToken);
          }
          title = tokens[0];
          year = stoi(tokens[1]);
          int index = movies->indexOfComedy(title, year);
          if (index == -1) {
            cerr << "Comedy Movie not found: " << title << " " << year << endl;
          } else {
            const auto *c = movies->getComedyMovie(index);
            if (customers.indexOf(customerID) != -1) {
              if (customers.get(customerID)->isCurrentlyBorrowing('F', index)) {
                movies->returnMovie(genre, index);
                Transaction *t = new Transaction(
                    'F', c->Title(), c->Director(),
                    customers.get(customerID)->getFirstName() + " " +
                        customers.get(customerID)->getLastName(),
                    'R');
                customers.get(customerID)->returnMovie('F', index);
                customers.get(customerID)
                    ->addToHistory(t); // Add transaction to customer history.
              } else {
                cerr << customers.get(customerID)->getFirstName() << " "
                     << customers.get(customerID)->getLastName()
                     << " tried to return a comedy movie they never borrowed: "
                     << c->Title() << "by " << c->Director() << endl;
              }
            } else {
              cerr << "Customer not found : " << customerID << endl;
            }
          }
        } else if (genre == "D") { // If our genre is a drama... do this
          string director;
          string title;
          string currToken;
          vector<string> tokens;
          while (getline(parse, currToken, ',')) {
            if (currToken[0] == ' ') {
              currToken.erase(0, 1); // Space trimmer.
            }
            tokens.push_back(currToken);
          }
          director = tokens[0];
          title = tokens[1];
          int index = movies->indexOfDrama(director, title);
          if (index == -1) {
            cerr << "Drama Movie not found: " << director << " " << title
                 << endl;
          } else {
            const auto *d = movies->getDramaMovie(index);
            if (customers.indexOf(customerID) != -1) {
              if (customers.get(customerID)->isCurrentlyBorrowing('D', index)) {
                movies->returnMovie(genre, index);
                Transaction *t = new Transaction(
                    'D', d->Title(), d->Director(),
                    customers.get(customerID)->getFirstName() + " " +
                        customers.get(customerID)->getLastName(),
                    'R');
                customers.get(customerID)->returnMovie('D', index);
                customers.get(customerID)
                    ->addToHistory(t); // Add transaction to customer history.
              } else {
                cerr << customers.get(customerID)->getFirstName() << " "
                     << customers.get(customerID)->getLastName()
                     << " tried to return a drama movie they never borrowed: "
                     << d->Title() << "by " << d->Director() << endl;
              }
            } else {
              cerr << "Customer not found : " << customerID << endl;
            }
          }
        } else if (genre == "C") { // If our genre is a comedy... do this
          string majorActorFirstName;
          string majorActorLastName;
          int month;
          int year;
          parse >> month >> year;
          parse >> majorActorFirstName >> majorActorLastName;
          int index = movies->indexOfClassic(month, year, majorActorFirstName,
                                             majorActorLastName);
          if (index == -1) {
            cerr << "Classic Movie not found: " << month << " " << year << " "
                 << majorActorFirstName << " " << majorActorLastName << endl;
          } else {
            const auto *c = movies->getClassicMovie(index);
            if (customers.indexOf(customerID) != -1) {
              if (customers.get(customerID)->isCurrentlyBorrowing('C', index)) {
                movies->returnMovie(genre, index);
                Transaction *t = new Transaction(
                    'C', c->Title(), c->Director(),
                    customers.get(customerID)->getFirstName() + " " +
                        customers.get(customerID)->getLastName(),
                    'R');
                customers.get(customerID)->returnMovie('D', index);
                customers.get(customerID)
                    ->addToHistory(t); // Add transaction to customer history.
              } else {
                cerr << customers.get(customerID)->getFirstName() << " "
                     << customers.get(customerID)->getLastName()
                     << " tried to return a classic movie they never borrowed: "
                     << c->Title() << "by " << c->Director() << endl;
              }
            } else {
              cerr << "Customer not found : " << customerID << endl;
            }
          }
        } else {
          cerr << "Invalid movie type " << genre << endl;
        }
      } else {
        cerr << "Invalid media type: " << media << endl;
      }
    } else {
      cerr << "Invalid command:  " << command << endl;
    }
  }
}