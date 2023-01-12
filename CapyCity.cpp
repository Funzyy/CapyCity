#include <iostream>
#include <string>
#include <regex>
using namespace std;

void menu();
enum building { Empty = 0, Water = 1, Wind = 2, Solar = 3 };
void buildingPlan();
void deleteArea();
void buildBuilding();
int posX();
int posY();
int buildingWidth();
int buildingLength();

int length;
int width;
regex menuCheck("[1-4]");
regex numberCheck("[[:digit:]]+");

building** Area;

int main(int argc, char **argv) {
    
    length = stoi(argv[1]);
    width = stoi(argv[2]);

    cout << "Willkommen in CapyCity!\n";

    Area = new building * [length];
    for (int x = 0; x < length; x++) {
        Area[x] = new building[width];
        for (int y = 0; y < length; y++) {
            Area[x][y] = building::Empty;
        }
    }

    while (true) {
        menu();
    }
}

void menu(){
    string choice;

    cout << endl
        << "1 - Gebaeude setzen\n"
        << "2 - Bereich loeschen\n"
        << "3 - Aktueller Bauplan\n"
        << "4 - Exit\n";

    cin >> choice;

    if (regex_match(choice, menuCheck)) {
        switch (stoi(choice)) {
        case 1:
            //Gebäude setzen    
            buildBuilding();
            break;
        case 2:
            //Bereich löschen
            deleteArea();
            break;
        case 3:
            //Print Blauplan
            buildingPlan();
            break;

        case 4:
            //Beenden des Programms
            cout << "Bye Bye";
            exit(0);
        }
    }
    else {
        cout << "Nur Zahlen von 1 - 4 erlaubt!\n";
        menu();
    } 
}

building buildingMenu() {
    string buildingChoice;

    cout << "Welches Gebaeude soll gebaut werden?";

    cout << endl
        << "1 - Wasserkraftwerk\n"
        << "2 - Windkraftwerk\n"
        << "3 - Solarpanele\n"
        << "4 - Zurueck zum Hauptmenue\n";
    cin >> buildingChoice;

    if (regex_match(buildingChoice, menuCheck)) {
        switch (stoi(buildingChoice)) {
        case 1:
            return Water;
            break;
        case 2:
            return Wind;
            break;
        case 3:
            return Solar;
            break;
        case 4:
            menu();
        }
    }
    else {
        cout << "Nur Zahlen von 1 - 4 erlaubt!\n";
        buildingMenu();
    }
}

void buildBuilding() {
    building buildingChoice = buildingMenu();

    int startX{ posX() };
    int startY{ posY() };
    int breite{ buildingWidth() };
    int laenge{ buildingLength() };

    for (int i = startX; i < startX + breite; i++) {
        for (int j = startY; j < startY + laenge; j++) {
            if ((startX + breite) > width || (startY + laenge) > length || Area[j][i] != Empty) {
                cout << "Flaeche schon belegt oder ausserhalb des Baubereichs!\n\n";
                return buildBuilding();
            }
            else {
                Area[j][i] = buildingChoice;
            }
        }
    }
}

int posX() {
    string startX;

    cout << "X Position eingeben: \n";
    cin >> startX;
    if (regex_match(startX, numberCheck) && stoi(startX)<length) {
        return stoi(startX);
    }
    else {
        cout << "Zahl zwischen 0 und " << (length - 1) << " eingeben\n";
        posX();
    }
}

int posY() {
    string startY;

    cout << "Y Position eingeben: \n";
    cin >> startY;
    if (regex_match(startY, numberCheck) && stoi(startY) < width) {
        return stoi(startY);
    }
    else {
        cout << "Zahl zwischen 0 und " << (width - 1) << " eingeben\n";
        posY();
    }
}

int buildingWidth() {
    string breite;

    cout << "Wie breit soll die Flaeche sein: \n";
    cin >> breite;
    if (regex_match(breite, numberCheck) && stoi(breite) > 0 && stoi(breite) <= width) {
        return stoi(breite);
    }
    else {
        cout << "Die Breite muss eine Zahl zwischen 1 und " << width << " sein!\n";
        buildingWidth();
    }
}

int buildingLength() {
    string laenge;

    cout << "Wie lang soll die Flaeche sein: \n";
    cin >> laenge;
    if (regex_match(laenge, numberCheck) && stoi(laenge) > 0 && stoi(laenge) <= length) {
        return stoi(laenge);
    }
    else {
        cout << "Die Laenge muss eine Zahl zwischen 1 und " << length << " sein!\n";
        buildingLength();
    }
}

void buildingPlan() {
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < width; y++) {
            cout << Area[x][y];
        }
        cout << endl;
    }
    menu();
}

void deleteArea() {
    int startX{ posX() };
    int startY{ posY() };
    int breite{ buildingWidth() };
    int laenge{ buildingLength() };

    for (int i = startX; i < startX + breite; i++) {
        for (int j = startY; j < startY + laenge; j++) {
            Area[j][i] = Empty;
        }
    }
    menu();
}