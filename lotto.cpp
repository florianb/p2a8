/**

@file lotto.cpp

Programmdatei mit Klassen und Methoden zur Erzeugung von Lottoziehungen.

**/

#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "random.cpp"

using namespace std;

namespace Lotto {
  /**
  Klasse zur Aufnahme einer Ziehung
  
  Die Klasse stellt eine programmatische Repräsentation einer Ziehung zur Verfügung, mit einzelnen Methoden
  zur Ausgabe, Abfrage von bestimmten Eigenschaften (bspw. vollständig gerade?) und erneuten Ziehung der
  Zahlen.
  **/
  class Draw {
  private:
    /**
    Container enthält sortiert die gezogenen Zahlen
    **/
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
  
  /**
  Initialisiert den Ziehungscontainer mit 0
  **/
  void Draw::initialize() {
    for (int i = 0; i < 6; i++) {
      numbers[i] = 0;
    }
  }
  
  /**
  Konstruktor, initialisert die Ziehung mit sechs gezogenen Zahlen
  
  @param randomTable Zeiger auf die Zufallstabelle
  **/
  Draw::Draw(Random::Table *randomTable) {
    drawNumbers(randomTable);
  }
  
  /**
  Funktion zieht sechs Zahlen
  
  @param randomTable Zeiger auf die Zufallstabelle
  **/
  void Draw::drawNumbers(Random::Table *randomTable) {
    short int currentNumber;
    short int numberShift;
    
    initialize();
    for (short int i = 0; i < 6; i++) {
      currentNumber = randomTable->random(1, 49 - i);
      for (short int j = 0; j < i; j++) {
        if (numbers[j] <= currentNumber)
          currentNumber++;
      }
      numbers[i] = currentNumber;
      sort(numbers, numbers + i + 1);
    }
  }
  
  /**
  Funktion ermittelt ob alle Zahlen der Ziehung gerade sind
  
  @return Wahr, falls alle Zahlen der Ziehung gerade sind, andernfalls Falsch
  **/
  bool Draw::isEven() {
    for (short int i = 0; i < 6; i++) {
      if (numbers[i] % 2 == 1)
        return false;
    }
    return true;
  }

  /**
  Funktion ermittelt ob alle Zahlen der Ziehung ungerade sind
  
  @return Wahr, falls alle Zahlen der Ziehung ungerade sind, andernfalls Falsch
  **/
  bool Draw::isOdd() {
    for (short int i = 0; i < 6; i++) {
      if (numbers[i] % 2 == 0)
        return false;
    }
    return true;
  }
  
  /**
  Funktion ermittelt ob alle Zahlen der Ziehung Primzahlen sind
  
  @return Wahr, falls alle Zahlen der Ziehung Primzahlen sind, andernfalls Falsch
  **/
  bool Draw::isPrime() {
    for (short int i = 0; i < 6; i++) {
      if (!isPrimeHelper(numbers[i]))
        return false;
    }
    return true;
  }
  
  /**
  Funktion ermittelt ob alle Zahlen der Ziehung keine Primzahlen sind
  
  @return Wahr, falls alle Zahlen der Ziehung keine Primzahlen sind, andernfalls Falsch
  **/
  bool Draw::isNotPrime() {
    for (short int i = 0; i < 6; i++) {
      if (isPrimeHelper(numbers[i]))
        return false;
    }
    return true;
  }
  
  /**
  Funktion ermittelt ob die Ziehung ihre eigene Länge enthält
  
  @return Wahr, falls die Ziehung ihre eigene Länge enthält, andernfalls Falsch
  **/
  bool Draw::containsLength() {
    short int length = getLength();
    for (short int i = 0; i < 6; i++) {
      if(numbers[i] == length)
        return true;
    }
    return false;
  }
  
  /**
  Funktion gibt die Länge, also die Differenz zwischen der niedrigsten und der höchsten Zahl zurück
  
  @return Differenz zwischen der niedrigsten und der höchsten gezogenen Zahl
  **/
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
  
  /**
  Funktion gibt gezogene Zahl mit dem gewünschten Index zurück
  
  @param index Index der Zahl, die zurückgeliefert werden soll
  
  @return Gezogene Zahl mit dem angeforderten Index
  **/
  short int Draw::getNumber(short int index) {
    return numbers[index];
  }
  
  /**
  Überladener Vergleichsoperator, prüft ob zwei identische Ziehungen vorliegen
  
  @param first Erste der zu vergleichenden Ziehungen
  @param second Zweite der zu vergleichenden Ziehungen
  
  @return Wahr, falls die Ziehungen identisch sind, andernfalls Falsch
  **/
  bool operator==(Draw &first, Draw &second) {
    for(short int i = 0; i < 6; i++)
    {
      if(first.getNumber(i) != second.getNumber(i))
        return false;
    }
    return true;
  }
  
  /**
  Überladener Stream-Operator, gibt eine Ziehung als Stringstream aus
  
  @param out Stream-Objekt, dass zur Ausgabe genutzt werden soll
  @param draw Ziehungsobjekt, dass ausgegeben werden soll
  
  @return Stream-Objekt inklusive String-Repräsentation der Ziehung
  **/
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
  
  /**
  Schnelle Hilfsfunktion zur Ermittlung, ob die angebene Zahl eine Primzahl ist
  
  Die Funktion kann nur Zahlen bis 49 gültig überprüfen, 1 ist keine Primzahl.
  
  @param i Zahl, die überprüft werden soll
  
  @return Wahr falls es sich um eine Primzahl handelt, andernfalls Falsch
  **/
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