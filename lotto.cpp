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
    Draw(Random::Table *randomTable);
    
    void drawNumbers(Random::Table *randomTable);
    bool isEven();
    bool isOdd();
    bool isPrime();
    bool isNotPrime();
    bool containsLength();
    short int getLength();
    short int getRank();
    
    friend ostream& operator<<(ostream &out, Draw &draw);
  };
  
  bool isPrimeHelper(short int i);
  
  void Draw::initialize() {
    for (int i = 0; i < 6; i++) {
      numbers[i] = 0;
    }
  }
  
  Draw::Draw(Random::Table *randomTable) {
    initialize();
    drawNumbers(randomTable);
  }
  
  void Draw::drawNumbers(Random::Table *randomTable) {
    short int currentNumber;
    short int numberShift;
    
    for (short int i = 0; i < 6; i++) {
      currentNumber = randomTable->random(1, 49 - i);
      numberShift = 0;
      for (short int j = 0; j <= i; j++) {
        if (numbers[j] <= currentNumber)
          numberShift++;
      }
      numbers[i] = currentNumber + numberShift;
    }
    
    sort(numbers, numbers + 5);
  }
  
  bool Draw::isEven() {
    for (short int i = 0; i < 6; i++) {
      if (i % 2 == 1)
        return false;
    }
    return true;
  }
  
  bool Draw::isOdd() {
    for (short int i = 0; i < 6; i++) {
      if (i % 2 == 0)
        return false;
    }
    return true;
  }
  
  bool Draw::isPrime() {
    for (short int i = 0; i < 6; i++) {
      if (!isPrimeHelper(i))
        return false;
    }
    return true;
  }
  
  bool Draw::isNotPrime() {
    for (short int i = 0; i < 6; i++) {
      if (isPrimeHelper(i))
        return false;
    }
    return true;
  }
  
  short int Draw::getLength() {
    return numbers[5] - numbers[0];
  }
  
  short int Draw::getRank() {
    short int rank = 1;
    
    for (short int i = 0; i < 4; i++) {
      for (short int j = 1;
          (i + j < 5) && (numbers[i + j - 1] == numbers[i + j] + 1);
          j++) {
        if (j > rank)
          rank = j;
      }
    }
    return rank;
  } 
  
  ostream& operator<<(ostream &out, Draw &draw) {
    out << draw.numbers[0];
    for (short int i = 1; i < 6; i++) {
      out << ", " << draw.numbers[i];
    }
    return out;
  }
  
  bool isPrimeHelper(short int i) {
    switch(i) {
      case 2:
      case 3:
      case 5:
      case 7:
      case 11:
      case 13:
      case 17:
      case 19:
      case 23:
      case 29:
      case 31:
      case 37:
      case 41:
      case 43:
      case 47:
        break;
      default:
        return false;
    }
    return true;
  }
}