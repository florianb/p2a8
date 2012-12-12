/**

@file main.cpp

Datei zum Start des Programms, enthält die Hauptfunktion und die Hilfeausgabe, falls
eine falsche Parameterzahl eingegeben wurde.

**/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

#include "lotto.cpp"
  
using namespace std;

typedef vector<Lotto::Draw> vectorOfDrawings;

void displayInformation(int numberOfDrawings) {
  cout << "Wir haben genug Ziehungen für " << numberOfDrawings / 52 << " Jahre und "
       << numberOfDrawings % 52 << " Wochen." << endl;
}

void displayNumberStatistics(vectorOfDrawings *drawings) {
  int lessFrequentNumber = 0;
  int mostFrequentNumber = 0;
  int lowestFrequency = numeric_limits<int>::max();
  int highestFrequency = numeric_limits<int>::min();
  int numberCounts[50];
  
  for (short int i = 0; i < 50; i++) {
    numberCounts[i] = 0;
  }
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    for (short int i = 0; i < 6; i++) {
      numberCounts[it->getNumber(i)]++;
    }
  }
  
  cout << "Häufigkeit der gezogenen Zahlen:" << endl;
  for (short int i = 1; i < 50; i++) {
    if (numberCounts[i] < lowestFrequency) {
      lowestFrequency = numberCounts[i];
      lessFrequentNumber = i;
    }
    if (numberCounts[i] > highestFrequency) {
      highestFrequency = numberCounts[i];
      mostFrequentNumber = i;
    }
    cout << setw(2) << i << ": " << numberCounts[i] << endl;
  }
  cout << "Die Zahl " << mostFrequentNumber << " wurde mit " << highestFrequency << " mal am häufigsten gezogen." << endl;
  cout << "Die Zahl " << lessFrequentNumber << " wurde mit " << lowestFrequency << " mal am seltensten gezogen." << endl;
  cout << " Das ist eine Differenz von " << highestFrequency - lowestFrequency << " Ziehungen." << endl;
}

void displayLowestNumberStatistics(vectorOfDrawings *drawings) {
  int numberCounts[50];
  
  for (short int i = 0; i < 50; i++) {
    numberCounts[i] = 0;
  }
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    numberCounts[it->getNumber(0)]++;
  }
  
  cout << "Häufigkeit der niedrigsten gezogenen Zahlen:" << endl;
  for (short int i = 1; i < 50; i++) {
    cout << setw(2) << i << ": " << numberCounts[i] << endl;
  }
}

void displayHighestNumberStatistics(vectorOfDrawings *drawings) {
  int numberCounts[50];
  
  for (short int i = 0; i < 50; i++) {
    numberCounts[i] = 0;
  }
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    numberCounts[it->getNumber(5)]++;
  }
  
  cout << "Häufigkeit der höchsten gezogenen Zahlen:" << endl;
  for (short int i = 1; i < 50; i++) {
    cout << setw(2) << i << ": " << numberCounts[i] << endl;
  }
}

void displayDrawLengthStatistics(vectorOfDrawings *drawings) {
  int numberCounts[49];
  
  for (short int i = 5; i < 49; i++) {
    numberCounts[i] = 0;
  }
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    numberCounts[it->getNumber(5) - it->getNumber(0)]++;
  }
  
  cout << "Häufigkeit der Ziehungslängen:" << endl;
  for (short int i = 6; i < 49; i++) {
    cout << setw(2) << i << ": " << setw(12) << numberCounts[i] << setw(10) << fixed << setprecision(2) << 100.0 * numberCounts[i] / drawings->size() << " %" << endl;
  }
}

void simulate(int numberOfDrawings) {
  vectorOfDrawings drawings;
  Random::Table *table = new Random::Table(10000);
  int fivePercent = numberOfDrawings / 20;
  int onePercent = numberOfDrawings / 100;
  
  drawings.reserve(numberOfDrawings);
  
  for (int i = 0; i < numberOfDrawings; i++) {
    if (i % fivePercent == 0)
      cout << endl << setw(2) << i / fivePercent * 5 << "% gezogen" << flush;
    if (i % onePercent == 0)
      cout << "." << flush;
    drawings.push_back(Lotto::Draw(table));
  }
  cout << endl;
  
  displayInformation(numberOfDrawings);
  displayNumberStatistics(&drawings);
  
  displayLowestNumberStatistics(&drawings);
  displayHighestNumberStatistics(&drawings);
  
  displayDrawLengthStatistics(&drawings);
  
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
