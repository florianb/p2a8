#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

namespace Random {
  class Table {
  private:
    int timesUsed;
    vector<int> table;
    
    void shuffle();
  public:
    Table(int size);
    int random(bool weighted = true, bool reshuffle = true);
    int random(int min, int max, bool weighted = true, bool reshuffle = true);
  };
  
  void Table::shuffle() {
    random_shuffle(table.begin(), table.end() - 1);
  }
  
  Table::Table(int size) {
    srand(time(NULL));
    
    table.reserve(size);
    timesUsed = 0;
    
    for (int i = 0; i < size; i++) {
      table.push_back(i);
    }
    shuffle();
  }
  
  int Table::random(bool weighted, bool reshuffle) {
    if (weighted) {
      if ((table.size() - timesUsed) <= 0) {
        timesUsed = 0;
        if (reshuffle)
          shuffle();
      }
      timesUsed++;
    
      return table[timesUsed - 1];
    } else {
      return rand();
    }
  }
  
  int Table::random(int min, int max, bool weighted, bool reshuffle) {
    return (random(weighted, reshuffle) % ((max + 1) - min)) + min;
  }
}