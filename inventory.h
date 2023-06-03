#ifndef Inventory_h
#define Inventory_h
#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "hashTable.h"
#include "movie.h"
#include <utility>
using namespace std;

class Inventory {
  // Prints out all three genres' movie shelves.
  friend ostream &operator<<(ostream &os, const Inventory &inv) {
    os << "Comedy Shelf: " << endl;
    for (auto **comedy : inv.comedies) {
      os << *comedy << endl;
    }
    os << "Drama Shelf: " << endl;
    for (auto **drama : inv.dramas) {
      os << *drama << endl;
    }
    os << "Classic Shelf: " << endl;
    for (auto **classic : inv.classics) {
      os << *classic << endl;
    }
    return os;
  }

public:
  friend class Store;

  void addComedy(int stock, const string &director, const string &title,
                 int releaseYear);

  void addDrama(int stock, const string &director, const string &title,
                int releaseYear);

  void addClassic(int stock, const string &director, const string &title,
                  const string &majorActorFirstName,
                  const string &majorActorLastName, int releaseMonth,
                  int releaseYear);

  bool borrowMovie(const string &type, int index);

  void returnMovie(const string &type, int index);

  // Index of comedy movie in vector.
  int indexOfComedy(const string &title, int releaseYear);

  // Index of drama movie in vector.
  int indexOfDrama(const string &director, const string &title);

  // Index of classic movie in vector.
  int indexOfClassic(const int &releaseMonth, const int &releaseYear,
                     const string &majorActorFirstName,
                     const string &majorActorLastName);

  const Classic *getClassicMovie(const int &index); // peek

  const Comedy *getComedyMovie(const int &index);

  const Drama *getDramaMovie(const int &index);

  void sortShelves();

private:
  vector<Comedy *> comedies;
  vector<Drama *> dramas;
  vector<Classic *> classics;
  static bool sortComedy(Comedy *f1, Comedy *f2);

  static bool sortDrama(Drama *d1, Drama *d2);

  static bool sortClassic(Classic *c1, Classic *c2);
};

#endif /* Inventory_h */