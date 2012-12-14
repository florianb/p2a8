/**

@file main.cpp

Datei zum Start des Programms, enthält die Hauptfunktion, die Ausgabefunktionen der Statistiken und eine Hilfe-Ausgabe, falls
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

/**
Eingabefunktion, nimmt eine Benutzereingabe entgegen und speichert sie in der übergebenen Variable

Die Funktion nimmt eine Referenz auf den Container für die Benutzereingaben entgegen
und speichert die Eingabe darin. Ist die Typprüfung oder das Parsen auf den Typ nicht erfolgreich,
so wird der Nutzer zu einer erneuten Eingabe des Wertes aufgefordert.

@param input Conatiner der die Eingaben aufnehmen soll
**/
template<class T> void input(T &input) {
  bool cin_good = false;
      
  cout.flush();
  cin.clear();
  do {
    cin_good = cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!cin_good) {
      cout << "Die Eingabe konnte nicht verarbeitet werden. Bitte erneut versuchen\n";
      cout.flush();
    }
  } while (!cin_good);
}

/**
Funktion gibt die Anzahl der Jahre und Monate aus, für die Ziehungen vorliegen

@param numberOfDrawings Anzahl der vorliegenden Ziehungen
**/
void displayInformation(int numberOfDrawings) {
  cout << "Wir haben genug Ziehungen für " << numberOfDrawings / 52 << " Jahre und "
       << numberOfDrawings % 52 << " Wochen." << endl;
}

/**
Funktion gibt die Verteilungsstatistik der gezogenen Zahlen aus

@param drawings Ziehungen-Container
**/
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
  cout << "Das ist eine Differenz von " << highestFrequency - lowestFrequency << " Ziehungen." << endl;
}

/**
Funktion gibt die Verteilungsstatistik der niedrigsten gezogenen Zahlen aus

@param drawings Ziehungen-Container
**/
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

/**
Funktion gibt die Verteilungsstatistik der höchsten gezogenen Zahlen aus

@param drawings Ziehungen-Container
**/
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

/**
Funktion gibt die Verteilungsstatistik der Ziehungslängen aus

Unterziehungslänge versteht man die Differenz zwischen der niedrigsten und höchsten Zahl einer
Ziehung

@param drawings Ziehung-Container
**/
void displayDrawLengthStatistics(vectorOfDrawings *drawings) {
  int numberCounts[49];
  
  for (short int i = 5; i < 49; i++) {
    numberCounts[i] = 0;
  }
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    numberCounts[it->getLength()]++;
  }
  
  cout << "Häufigkeit der Ziehungslängen:" << endl;
  for (short int i = 6; i < 49; i++) {
    cout << setw(2) << i << ": " << setw(12) << numberCounts[i] << setw(10) << fixed << setprecision(2) << 100.0 * numberCounts[i] / drawings->size() << " %" << endl;
  }
}

/**
Funktion gibt die Anzahl und den Anteil der Ziehungen aus, die ihre Länge als gezogene Zahl enthalten

@param drawings Ziehungen-Container
**/
void displayContainingLengthStatistics(vectorOfDrawings *drawings) {
  int containingLength = 0;
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    for (short int i = 0; i < 6; i++) {
      if (it->containsLength())
        containingLength++;
    }
  }
  
  cout << containingLength << " Ziehungen enthalten ihre Länge, dass sind " << fixed << setprecision(2) << 100.0 * containingLength / drawings->size() << " %." << endl << flush;
}

/**
Funktion gibt die Verteilungsstatistik der Ziehungsränge (k) aus

Unter Ziehungsrang versteht man die größte Anzahl aufeinander folgender Zahlen pro Ziehung

@param drawings Ziehung-Container
**/
void displayRankStatistics(vectorOfDrawings *drawings) {
  int rankCounts[7];
  
  for (short int i = 1; i < 7; i++) {
    rankCounts[i] = 0;
  }
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    rankCounts[it->getRank()]++;
  }
  
  cout << "Häufigkeit der K-Ränge:" << endl;
  for (short int i = 1; i < 7; i++) {
    cout << setw(2) << i << ": " << setw(12) << rankCounts[i] << setw(10) << fixed << setprecision(2) << 100.0 * rankCounts[i] / drawings->size() << " %" << endl;
  }
}

/**
Funktion gibt die Anzahl und den Anteil der Ziehungen aus, deren gezogenen Zahlen gerade sind

@param drawings Ziehungen-Container
**/
void displayEvenStatistics(vectorOfDrawings *drawings) {
  int evenDrawings = 0;
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    if (it->isEven())
      evenDrawings++;
  }
  cout << "Es gibt " << evenDrawings << " gerade Ziehungen, das sind " << fixed << setprecision(2) << 100.0 * evenDrawings / drawings->size() << " %." << endl;
}

/**
Funktion gibt die Anzahl und den Anteil der Ziehungen aus, deren gezogenen Zahlen ungerade sind

@param drawings Ziehungen-Container
**/
void displayOddStatistics(vectorOfDrawings *drawings) {
  int oddDrawings = 0;
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    if (it->isOdd())
      oddDrawings++;
  }
  cout << "Es gibt " << oddDrawings << " ungerade Ziehungen, das sind " << fixed << setprecision(2) << 100.0 * oddDrawings / drawings->size() << " %." << endl;
}

/**
Funktion gibt die Anzahl und den Anteil der Ziehungen aus, deren gezogenen Zahlen Primzahlen sind

@param drawings Ziehungen-Container
**/
void displayPrimeStatistics(vectorOfDrawings *drawings) {
  int primeDrawings = 0;
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    if (it->isPrime())
      primeDrawings++;
  }
  cout << "Es gibt " << primeDrawings << " Ziehungen, die komplett aus Primzahlen bestehen. Das sind " << fixed << setprecision(2) << 100.0 * primeDrawings / drawings->size() << " %." << endl;
}


/**
Funktion gibt die Anzahl und den Anteil der Ziehungen aus, deren gezogenen Zahlen keine Primzahlen sind

@param drawings Ziehungen-Container
**/
void displayNotPrimeStatistics(vectorOfDrawings *drawings) {
  int notPrimeDrawings = 0;
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    if (it->isNotPrime())
      notPrimeDrawings++;
  }
  cout << "Es gibt " << notPrimeDrawings << " Ziehungen, in denen keine Primzahlen vorkommen. Das sind " << fixed << setprecision(2) << 100.0 * notPrimeDrawings / drawings->size() << " %." << endl;
}


/**
Funktion lässt den Nutzer einen Lotto-Tip abgeben und gibt anschließend eine Trefferstatistik aus

Die Funktion prüft außerdem, ob der Nutzer versehentlich doppelte Eingaben tätigt.

@param drawings Ziehungen-Container
**/
void checkTip(vectorOfDrawings *drawings) {
  short int tip[6] = {0, 0, 0, 0, 0, 0};
  int hits[7] = {0, 0, 0, 0, 0, 0};
  
  short int hitCount;
  
  bool invalidInput = true;
  
  for (short int i = 0; i < 6; i++) {
    do {
      invalidInput = false;
      cout << "Bitte geben Sie die " << i + 1 << ". Zahl (1-49) ein:" << endl << flush;
      input(tip[i]);
      if (tip[i] < 1 || 49 < tip[i]) {
        invalidInput = true;
        cout << "Ihre Eingabe von " << tip[i] << " liegt leider nicht zwischen 0 und 50." << endl << flush;
      }
      for (short int j = i; j > 0; j--) {
        if (tip[i] == tip[j - 1]) {
          invalidInput = true;
          cout << "Ihre Eingabe von " << tip[i] << " ist leider bereits vergeben." << endl << flush;
        }
      }
    } while (invalidInput);
  }
  sort(tip, tip + 6);
  cout << "Ihr Tip lautet: " << tip[0] << ", " << tip[1] << ", " << tip[2] << ", " << tip[3] << ", " << tip[4] << ", " << tip[5] << endl;
  
  for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
    hitCount = 0;
    for (short int i = 0; i < 6; i++) {
      for (short int j = 0; j < 6; j++) {
        if (it->getNumber(j) == tip[i])
          hitCount++;
      }
    }
    if (hitCount)
      hits[hitCount]++;
  }
  
  for (short int i = 1; i < 7; i++) {
    cout << "Sie haben " << hits[i] << " mal " << i << " Treffer." << endl << flush;
  }
}


/**
Funktion gibt so lange Lotto-Tips ab, bis 6 richtige Zahlen getippt wurden

@param drawings Ziehungen-Container
@param table Zufallstabelle die verwendet werden soll
**/
void tipSix(vectorOfDrawings *drawings, Random::Table *table) {
  bool tippedSix = false;
  int tips = 1;
  Lotto::Draw tip(table);
  cout << "Tippe auf 6 richtige.." << flush;
  do {
    for (vectorOfDrawings::iterator it = drawings->begin(); it != drawings->end(); ++it) {
      if (tips % 10000 == 0)
        cout << "." << flush;
      if (*it == tip) {
        tippedSix = true;
        cout << endl << "6 richtige (" << tip << ") nach " << tips << " Versuchen getippt." << endl << flush;
      }
      tip.drawNumbers(table);
      tips++;
    }
  } while (!tippedSix);
}

/**
Funktion gibt das grafische Auswahlmenü für den Nutzer aus
**/
void printMenu() {
  cout << "Bitte waehlen:" << endl
      << "(1) Information" << endl
      << "(2) Haeufigkeitsverteilung" << endl
      << "(3) Verteilung der Minima" << endl
      << "(4) Verteilung der Maxima" << endl
      << "(5) Verteilung der Ziehungslaengen" << endl
      << "(6) Anzahl Ziehungen, die ihre Laenge enthalten" << endl
      << "(7) Anzahl gerade Ziehungen" << endl
      << "(8) Anzahl ungerade Ziehungen" << endl
      << "(9) Anzahl Primziehungen" << endl
      << "(10) Anzahl Nichtprimziehungen" << endl
      << "(11) Verteilung der k-Ziehungen" << endl
      << "(12) Tippen" << endl
      << "(13) Automatisch Tippen" << endl
      << "(14) Neue Ziehungen" << endl
      << "(15) Beenden" << endl << endl
      << "Ihre Wahl:" << endl << flush;
}

/**
Funktion führt abhängig von den Parametern die gewünschte Funktion der Simulation aus
**/
void menuAction(int userInput, int numberOfDrawings, vectorOfDrawings *drawings, Random::Table *table) {
  cout << endl;
  if (userInput == 1)
    displayInformation(numberOfDrawings);
  if (userInput == 2)
    displayNumberStatistics(drawings);
  if (userInput == 3)
    displayLowestNumberStatistics(drawings);
  if (userInput == 4)
    displayHighestNumberStatistics(drawings);
  if (userInput == 5)
    displayDrawLengthStatistics(drawings);
  if (userInput == 6)
    displayContainingLengthStatistics(drawings);
  if (userInput == 7)
    displayEvenStatistics(drawings);
  if (userInput == 8)
    displayOddStatistics(drawings);
  if (userInput == 9)
    displayPrimeStatistics(drawings);
  if (userInput == 10)
    displayNotPrimeStatistics(drawings);
  if (userInput == 11)
    displayRankStatistics(drawings);
  if (userInput == 12)
    checkTip(drawings);
  if (userInput == 13)
    tipSix(drawings, table);
  cout << endl;
}

/**
Funktion simuliert die Ziehung der gewünschten Lottozahlen und nimmt die Benutzereingabe entgegen

Die Funktion simuliert die gewünschte Anzahl an Lottoziehungen und legt diese im Arbeitsspeicher ab. Im Anschluss
wird der Nutzer zur Auswahl der gewünschten Funktion aufgefordert. Der Nutzer kann sich entscheiden eine erneute Ziehung
vornehmen zu lassen, diese wird dann durchgeführt.

@param numberOfDrawings Initial gewünschte Anzahl an Ziehungen
**/
void simulate(int numberOfDrawings) {
  vectorOfDrawings drawings;
  Random::Table *table = new Random::Table(10000);
  int fivePercent = 0;
  int onePercent = 0;
  int userInput = 0;
  
  do {
    drawings.clear();
    drawings.reserve(numberOfDrawings);
    fivePercent = numberOfDrawings / 20;
    onePercent = numberOfDrawings / 100;
    
    for (int i = 0; i < numberOfDrawings; i++) {
      if (fivePercent && i % fivePercent == 0)
        cout << endl << setw(2) << i / fivePercent * 5 << "% gezogen" << flush;
      if (onePercent && i % onePercent == 0)
        cout << "." << flush;
      drawings.push_back(Lotto::Draw(table));
    }
    cout << endl;
    
    do {
      do {
        printMenu();
        input(userInput);
        if (userInput < 1 || 15 < userInput) {
          cout << "Ihre Eingabe liegt außerhalb des gültigen Bereichs, versuchen Sie es erneut." << endl;
        }
      } while (userInput < 1 || 15 < userInput);
      if (userInput < 14)
        menuAction(userInput, numberOfDrawings, &drawings, table);
    } while (userInput < 14);
    if (userInput == 14) {
      do {
        cout << "Geben die Anzahl zu tätigender Ziehungen ein (mindestens 1):" << endl << flush;
        input(userInput);
        if (userInput < 1)
          cout << "Die eingegebene Zahl ist zu niedrig, versuchen Sie es erneut." << endl << endl << flush;
      } while (userInput < 1);
      numberOfDrawings = userInput;
    } 
  } while (userInput != 15);
  cout << "Adieu.." << endl << flush;
  delete table;
}



/**
Hauptfunktion überprüft, ob ein Kommandozeilenparameter übergeben wurde

Wurde ein Kommandozeilenparameter (n) übergeben, versucht die Routine den Wert
als Zahl einzulesen, schlägt dies fehl wird ein Standardert (1000)
angenommen.
Startet außerdem die Hauptroutine zur Simulationsausführung mit der gewünschten Anzahl an Ziehungen.

@param argumentCounter Anzahl übergebener Kommandozeilenparameter
@param argumentValues Feld mit Zeigern auf CStrings, die die Kommandozeilenparameter enthalten
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
