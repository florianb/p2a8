#include <cstdlib>
#include <sstream>
#include <iomanip>
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
    short int getNumber(short int index);
    
    friend bool operator==(Draw &first, Draw &second);
    
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
      currentNumber = randomTable->random(1, 49 - i, false);
      for (short int j = 0; j < i; j++) {
        if (numbers[j] <= currentNumber)
          currentNumber++;
      }
      numbers[i] = currentNumber;
      sort(numbers, numbers + i + 1);
    }
  }
  
  bool Draw::isEven() {
    for (short int i = 0; i < 6; i++) {
      if (numbers[i] % 2 == 1)
        return false;
    }
    return true;
  }
  
  bool Draw::isOdd() {
    for (short int i = 0; i < 6; i++) {
      if (numbers[i] % 2 == 0)
        return false;
    }
    return true;
  }
  
  bool Draw::isPrime() {
    for (short int i = 0; i < 6; i++) {
      if (!isPrimeHelper(numbers[i]))
        return false;
    }
    return true;
  }
  
  bool Draw::isNotPrime() {
    for (short int i = 0; i < 6; i++) {
      if (isPrimeHelper(numbers[i]))
        return false;
    }
    return true;
  }
  
  bool Draw::containsLength() {
    short int length = getLength();
    for (short int i = 0; i < 6; i++) {
      if(numbers[i] == length)
        return true;
    }
    return false;
  }
  
  short int Draw::getLength() {
    return numbers[5] - numbers[0];
  }
  
  short int Draw::getRank() {
    short int rank = 0;
    
    for (short int i = 0; i < 5; i++) {
      for (short int j = 1;
          (i + j < 6) && numbers[i + j] == (numbers[i + j - 1] + 1);
          j++) {
        if (j > rank)
          rank = j;
      }
    }
    return rank + 1;
  }
  
  short int Draw::getNumber(short int index) {
    return numbers[index];
  }
  
  bool operator==(Draw &first, Draw &second) {
    for(short int i = 0; i < 6; i++)
    {
      if(first.getNumber(i) != second.getNumber(i))
        return false;
    }
    return true;
  }
  
  ostream& operator<<(ostream &out, Draw &draw) {
    out << setw(2) << draw.numbers[0];
    for (short int i = 1; i < 6; i++) {
      out << ", " << setw(2) << draw.numbers[i];
    }
    
    out << ", length: " << setw(2) << draw.getLength();
    out << ", rank: " << draw.getRank();
    
    if (draw.isEven())
      out << ", Even";
    if (draw.isOdd())
      out << ", Odd";
    if (draw.isPrime())
      out << ", Prime";
    if (draw.isNotPrime())
      out << ", No Prime";
    if (draw.containsLength())
      out << ", contains Length";
    
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