/**

@file random.cpp

Programmdatei mit Klassen und Methoden zur Erzeugung von Zufallszahlen.

**/

#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

namespace Random {
  /**
  Klasse zur Speicherung einer gewichteten Zufallstabelle
  **/
  class Table {
  private:
    /**
    Anzahl der abgefragten Zufallszahlen, dient zur Ermittlung des Reshuffle-Zeitpunktes
    **/
    int timesUsed;
    
    /**
    Zufallszahlen-Container
    **/
    vector<int> table;
    
    void shuffle();
  public:
    Table(int size);
    int random(bool weighted = true, bool reshuffle = true);
    int random(int min, int max, bool weighted = true, bool reshuffle = true);
  };
  
  /**
  Funktion zur Durchmischung der Zufallszahlentabelle
  **/
  void Table::shuffle() {
    random_shuffle(table.begin(), table.end() - 1);
  }
  
  /**
  Konstruktor erstellt eine Zufallszahlentabelle mit der gewünschten Größe
  
  @param size Anzahl ageforderter Zufallszahlen in der Tabelle
  **/
  Table::Table(int size) {
    srand(time(NULL));
    
    table.reserve(size);
    timesUsed = 0;
    
    for (int i = 0; i < size; i++) {
      table.push_back(i);
    }
    shuffle();
  }
  
  /**
  Funktion liefert eine Zufallszahl
  
  Die Funktion liefert eine Zufallszahl aus der Tabelle. Übersteigt die abgefragte
  Anzahl an Zufallszahlen die enthaltene Anzahl an Zufallszahlen wird standardmäßig
  eine erneute Durchmischung der Tabelle angestoßen.
  
  Die Durchmischung kann unterbunden werden, ebenso kann eine native Zufallszahl
  ermittelt werden, die nicht aus der Tabelle stammt.
  
  @param weighted Gibt an, ob eine Zufallszahl aus der gewichteten Tabelle entnommen werden soll (Standardmäßig JA)
  @param reshuffle Gibt an, ob die Tabelle nach entnahme einer Tabelle neu gemischt werden soll (Standardmäßig JA)
  
  @return Zufallszahl (wie random())
  **/
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
  
  /**
  Funktion liefert ganzzahlige Zufallszahl in einem bestimmten Intervall
  
  @param min Minimum des Intervalls, zugleich kleinste mögliche Zahl
  @param max Maximum des Intervalls, zugleich größte möglich Zahl
  
  @return Ermittelte Zufallszahl
  **/
  int Table::random(int min, int max, bool weighted, bool reshuffle) {
    return (random(weighted, reshuffle) % ((max + 1) - min)) + min;
  }
}