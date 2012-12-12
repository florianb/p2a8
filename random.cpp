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
    int random(bool weighted = true);
    int random(int min, int max, bool weighted = true);
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
  
  int Table::random(bool weighted) {
    if (weighted) {
      if ((table.size() - timesUsed) <= 0) {
        timesUsed = 0;
        shuffle();
      }
      timesUsed++;
    
      return table[timesUsed - 1];
    } else {
      return rand();
    }
  }
  
  int Table::random(int min, int max, bool weighted) {
    return (random(weighted) % ((max + 1) - min)) + min;
  }
}