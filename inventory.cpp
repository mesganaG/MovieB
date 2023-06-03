#include "inventory.h"
#include <algorithm>

void Inventory::addComedy(int stock, const string &director,
                          const string &title, int releaseYear) {
  auto *f = new Comedy(stock, director, title, releaseYear);
  for (auto &movie : comedies) {
    if (f == movie) {
      movie->set_stock(
          f->Stock() +
          movie->Stock()); // If we add the same movie twice, just increase
                              // its stock instead of adding a new movie.
      return;
    }
  }
  comedies.push_back(f);
}

void Inventory::addDrama(int stock, const string &director, const string &title,
                         int releaseYear) {
  auto *d = new Drama(stock, director, title, releaseYear);
  for (auto &movie : dramas) {
    if (d == movie) {
      movie->set_stock(
          d->Stock() +
          movie->Stock()); // If we add the same movie twice, just increase
                              // its stock instead of adding a new movie.
      return;
    }
  }
  dramas.push_back(d);
}

void Inventory::addClassic(int stock, const string &director,
                           const string &title,
                           const string &majorActorFirstName,
                           const string &majorActorLastName, int releaseMonth,
                           int releaseYear) {
  auto *c = new Classic(stock, director, title, majorActorFirstName,
                       majorActorLastName, releaseYear, releaseMonth);
  for (auto &movie : classics) {
    if (c == movie) {
      movie->set_stock(
          c->Stock() +
          movie->Stock()); // If we add the same movie twice, just increase
                              // its stock instead of adding a new movie.
      return;
    }
  }
  classics.push_back(c);
}

bool Inventory::borrowMovie(const string &type, int index) {
  if (type == "F") {
    int stock = comedies[index]->Stock();
    if (stock - 1 < 0) {
      cerr << "Out of stock, can't borrow " << comedies[index]->Title()
           << endl;
      return false;
    }
    comedies[index]->set_stock(stock - 1);
    comedies[index]->set_borrowed(comedies[index]->Borrowed() + 1);
    return true;
  }
  if (type == "D") {
    int stock = dramas[index]->Stock();
    if (stock - 1 < 0) {
      cerr << "Out of stock, can't borrow " << dramas[index]->Title()
           << endl;
      return false;
    }
    dramas[index]->set_stock(stock - 1);
    dramas[index]->set_borrowed(dramas[index]->Borrowed() + 1);
    return true;
  }
  if (type == "C") {
    int stock = classics[index]->Stock();
    if (stock - 1 < 0) {
      cerr << "Out of stock, can't borrow " << classics[index]->Title()
           << endl;
      return false;
    }
    classics[index]->set_stock(stock - 1);
    classics[index]->set_borrowed(classics[index]->Borrowed() + 1);
    return true;
  }
  cerr << "Invalid Type: " << type << endl;
  return false;
}

void Inventory::returnMovie(const string &type, int index) {
  if (type == "F") {
    int stock = comedies[index]->Stock();
    comedies[index]->set_stock(stock + 1);
    comedies[index]->set_borrowed(comedies[index]->Borrowed() - 1);
  } else if (type == "D") {
    int stock = dramas[index]->Stock();
    dramas[index]->set_stock(stock + 1);
    dramas[index]->set_borrowed(dramas[index]->Borrowed() - 1);
  } else if (type == "C") {
    int stock = classics[index]->Stock();
    classics[index]->set_stock(stock + 1);
    classics[index]->set_borrowed(classics[index]->Borrowed() - 1);
  } else {
    cerr << "Invalid Type: " << type << endl;
  }
}

// Index of comedy movie in vector.
int Inventory::indexOfComedy(const string &title, int releaseYear) {
  for (int i = 0; i < comedies.size(); i++) {
    if (comedies[i]->Title() == title &&
        comedies[i]->Year() == releaseYear) {
      return i;
    }
  }
  return -1; // Not found
}

// Index of drama movie in vector.
int Inventory::indexOfDrama(const string &director, const string &title) {
  for (int i = 0; i < dramas.size(); i++) {
    if (dramas[i]->Director() == director &&
        dramas[i]->Title() == title) {
      return i;
    }
  }
  return -1; // Not found
}

// Index of classic movie in vector.
int Inventory::indexOfClassic(const int &releaseMonth, const int &releaseYear,
                              const string &majorActorFirstName,
                              const string &majorActorLastName) {
  for (int i = 0; i < classics.size(); i++) {
    if (classics[i]->getMajorActorFirstName() == majorActorFirstName &&
        classics[i]->getMajorActorLastName() == majorActorLastName &&
        classics[i]->getMonth() == releaseMonth &&
        classics[i]->Year() == releaseYear) {
      return i;
    }
  }
  return -1; // Not found.
}

const Classic *Inventory::getClassicMovie(const int &index) {
  if (index > classics.size() || index < 0) {
    cerr << "Index exceeds Classic Movie shelf size: " << index << endl;
    return nullptr;
  }
  return classics[index];
}

const Comedy *Inventory::getComedyMovie(const int &index) {
  if (index > comedies.size() || index < 0) {
    cerr << "Index exceeds Comedy Movie shelf size: " << index << endl;
    return nullptr;
  }
  return comedies[index];
}

const Drama *Inventory::getDramaMovie(const int &index) {
  if (index > dramas.size() || index < 0) {
    cerr << "Index exceeds Drama Movie shelf size: " << index << endl;
    return nullptr;
  }
  return dramas[index];
}

bool Inventory::sortComedy(Comedy *f1, Comedy *f2) { return f1->lessThan(f2); }

bool Inventory::sortDrama(Drama *d1, Drama *d2) { return d1->lessThan(d2); }

bool Inventory::sortClassic(Classic *c1, Classic *c2) {
  return c1->lessThan(c2);
}

void Inventory::sortShelves() {
  sort(comedies.begin(), comedies.end(), sortComedy);
  sort(dramas.begin(), dramas.end(), sortDrama);
  sort(classics.begin(), classics.end(), sortClassic);
}