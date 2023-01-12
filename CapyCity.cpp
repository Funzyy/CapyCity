#include <iostream>
#include <string>
using namespace std;

void menu();
enum building { Empty = 0, Water = 1, Wind = 2, Solar = 3 };
void buildingPlan();
void deleteArea();
void buildBuilding();

int length;
int width;

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
    int choice;

    cout << endl
        << "1 - Gebaeude setzen\n"
        << "2 - Bereich loeschen\n"
        << "3 - Aktueller Bauplan\n"
        << "4 - Exit\n";

    cin >> choice;

    switch (choice) {
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


building buildingMenu() {
    int buildingChoice;

    cout << "Welches Gebaeude soll gebaut werden?";

    cout << endl
        << "1 - Wasserkraftwerk\n"
        << "2 - Windkraftwerk\n"
        << "3 - Solarpanele\n"
        << "4 - Zurueck zum Hauptmenue\n";
    cin >> buildingChoice;

    switch (buildingChoice) {
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

void buildBuilding() {
    building buildingChoice = buildingMenu();

    int startX;
    int startY;
    int breite;
    int laenge;

    while (true) {
        cout << "X Position eingeben: \n";
        cin >> startX;
        if (startX >= 0 && startX < length) {
            break;
        }
        else {
            cout << "Zahl zwischen 0 und " << (length - 1) << " eingeben" << endl;
        }
    }

    while (true) {
        cout << "Y Position eingeben: \n";
        cin >> startY;
        if (startY >= 0 && startY < width) {
            break;
        }
        else {
            cout << "Zahl zwischen 0 und " << (width - 1) << " eingeben" << endl;
        }
    }

    while (true) {
        cout << "Wie breit soll das Gebaeude sein: \n";
        cin >> breite;
        if (breite > 0 && breite <= width) {
            break;
        }
        else {
            cout << "Breite kann nicht 0 oder groesser als das Baufeld sein!\n";
        }
    }

    while (true) {
        cout << "Wie lang soll das Gebaeude sein: \n";
        cin >> laenge;
        if (laenge > 0 && laenge <= length) {
            break;
        }
        else {
            cout << "Laenge kann nicht 0 oder groesser als das Baufeld sein!\n";
        }
    }

    for (int i = startX; i < startX + breite; i++) {
        for (int j = startY; j < laenge; j++) {
            if (Area[i][j] != Empty) {
                cout << "Flaeche schon belegt oder ausserhalb des Baubereichs!\n";
                return buildBuilding();
            }
        }
    }

    for (int i = startX; i < startX + breite; i++) {
        for (int j = startY; j < laenge; j++) {
            Area[i][j] = buildingChoice;
        }
    }

}

void buildingPlan() {
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < width; y++) {
            cout << Area[x][y];
        }
        cout << endl;
    }
}

void deleteArea() {
    int startX;
    int startY;
    int breite;
    int laenge;

    while (true) {
        cout << "X Position eingeben: \n";
        cin >> startX;
        if (0 <= startX && startX < length) {
            break;
        }
        else {
            cout << "Zahl zwischen 0 und " << (length - 1) << " eingeben" << endl;
        }
    }

    while (true) {
        cout << "Y Position eingeben: \n";
        cin >> startY;
        if (0 <= startY && startY < width) {
            break;
        }
        else {
            cout << "Zahl zwischen 0 und " << (width - 1) << " eingeben" << endl;
        }
    }


    cout << "Wie breit soll die gelöschte Fläche sein: \n";
    cin >> breite;

    cout << "Wie lang soll die gelöschte Fläche sein: \n";
    cin >> laenge;

    for (int i = startX; i < startX + breite; i++) {
        for (int j = startY; j < laenge; j++) {
            Area[i][j] = Empty;
        }
    }

}