#include <cstdlib>

#include "random.cpp"

using namespace std;

namespace Lotto {
  class Draw {
  private:
    int numbers[6];
  
  public:
    Draw();
    void drawNumbers(Random::Table &randomTable);
  };
  
  Draw::Draw() {
    for (int i = 0; i < 6; i++) {
      numbers[i] = 0;
    }
  }
  
  void Draw::drawNumbers(Random::Table &randomTable) {
    int currentNumber;
    
    for (int i = 0; i < 6; i++) {
      currentNumber = randomTable.random(1, 49 - i);
      for (int j = 0; j <= i; j++) {
        if (numbers[j] < currentNumber)
          // kann schief gehen..
      }
    }
  }
}