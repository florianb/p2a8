#include <cstdlib>
#include <sstream>
#include <algorithm>

#include "random.cpp"

using namespace std;

namespace Lotto {
  class Draw {
  private:
    short int numbers[6];
    
    void initialize();
  
  public:
    Draw();
    Draw(Random::Table &randomTable);
    
    void drawNumbers(Random::Table &randomTable);
    bool isEven();
    bool isPrime();
    bool containsLength();
    short int getLength();
    short int getRank();
    
    friend ostream& operator<<(ostream &out, Draw &draw);
  };
  
  void Draw::initialize() {
    for (int i = 0; i < 6; i++) {
      numbers[i] = 0;
    }
  }
  
  Draw::Draw() {
    initialize();
  }
  
  Draw::Draw(Random::Table &randomTable) {
    initialize();
    drawNumbers(randomTable);
  }
  
  void Draw::drawNumbers(Random::Table &randomTable) {
    short int currentNumber;
    short int numberShift;
    
    for (short int i = 0; i < 6; i++) {
      currentNumber = randomTable.random(1, 49 - i);
      numberShift = 0;
      for (short int j = 0; j <= i; j++) {
        if (numbers[j] <= currentNumber)
          numberShift++;
      }
      numbers[i] = currentNumber + numberShift;
    }
    
    sort(numbers, numbers + 5);
  }
  
  ostream& operator<<(ostream &out, Draw &draw) {
    out << draw.numbers[0];
    for (short int i = 1; i < 6; i++) {
      out << ", " << draw.numbers[i];
    }
    return out;
  }
}