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
    int random();
    int random(int min, int max);
  };
  
  void Table::shuffle() {
    random_shuffle(table.begin(), table.end());
  }
  
  Table::Table(int size) {
    table.resize(size);
    timesUsed = 0;
    
    for (int i = 0; i < size; i++) {
      table.push_back(i);
    }
  }
  
  int Table::random() {
    if (!(table.size() % timesUsed) && timesUsed) {
      timesUsed = 0;
      shuffle();
    }
    else
    {
      timesUsed++;
    }
    
    return table.at(timesUsed);
  }
  
  int Table::random(int min, int max) {
    return (random() % (max - min)) + min;
  }
}