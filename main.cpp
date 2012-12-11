/**

@file main.cpp

Datei zum Start des Programms, enthält die Hauptfunktion und die Hilfeausgabe, falls
eine falsche Parameterzahl eingegeben wurde.

**/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>

#include "lotto.cpp"
  
using namespace std;

typedef vector<Lotto::Draw> vectorOfDrawings;

void simulate(int numberOfDrawings) {
  vectorOfDrawings drawings;
  Random::Table *table = new Random::Table(1000000);
  int fivePercent = numberOfDrawings / 20;
  int onePercent = numberOfDrawings / 100;
  
  drawings.reserve(numberOfDrawings);
  
  for (int i = 0; i < numberOfDrawings; i++) {
    if (i % fivePercent == 0)
      cout << endl << setw(2) << i / fivePercent * 5 << "% gezogen";
    if (i % onePercent == 0)
      cout << ".";
    drawings.push_back(Lotto::Draw(table));
  }
  
  /**
  for (vectorOfDrawings::iterator it = drawings.begin(); it != drawings.end(); ++it) {
    cout << *it << "\n";
  }**/
  
  delete table;
}



/**
Hauptfunktion überprüft, ob ein Kommandozeilenparameter übergeben wurde

Wurde ein Kommandozeilenparameter (n) übergeben, versucht die Routine den Wert
als Zahl einzulesen, schlägt dies fehl wird ein Standardert (50)
angenommen.
Startet außerdem die Hauptroutine zur Simulationsausführung.
**/
int main(int argumentCounter, char* argumentValues[]) {
  int numberOfDrawings = 0;
  
  if (argumentCounter == 2)
    numberOfDrawings = atoi(argumentValues[1]);
  
  if (numberOfDrawings < 1) {
    numberOfDrawings = 1000;
    
    cout << "Die Standardanzahl an Ziehungen (" << numberOfDrawings << ") wird vorbereitet.";
  }
  
  simulate(numberOfDrawings);
}
