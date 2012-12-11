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
    //cout << "Mische Zufallszahlen...";
    //cout.flush();
    random_shuffle(table.begin(), table.end() - 1);
    //cout << " fertig.\n";
    
    //cout.flush();
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
  
  int Table::random() {
    if ((table.size() - timesUsed) <= 0) {
      timesUsed = 0;
      shuffle();
    }
    timesUsed++;
    
    return table[timesUsed - 1];
  }
  
  int Table::random(int min, int max) {
    return (random() % ((max + 1) - min)) + min;
  }
}