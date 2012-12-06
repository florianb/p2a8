/**

@file main.cpp

Datei zum Start des Programms, enthält die Hauptfunktion und die Hilfeausgabe, falls
eine falsche Parameterzahl eingegeben wurde.

**/

#include <cstdlib>
#include <iomanip>
#include <cstdio>

#include "lotto.cpp"
  
using namespace std;

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
    
    cout << "Die Standardanzahl an Ziehungen (1.000) wird vorbereitet.";
  }
}