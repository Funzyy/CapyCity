#include <iostream>
#include <string>
#include <regex>
#include "CapycitySim.h"
using namespace std;

Building::Building() {
    basePrice = 0;
    label = '0';
    efficiency = 0;
}

int Building::getPrice() const {
    return basePrice;
}

char Building::getLabel() const {
    return label;
}

double Building::getEfficiency() const {
    return efficiency;
}

string Material::getName() const {
    return name;
}

int Material::getPrice() const {
    return price;
}

int WaterPlant::getWaterPrice() {
    for (auto& whichMat : WaterPlant().materials) {
        waterPrice += whichMat.second * whichMat.first.getPrice();
    }
    return waterPrice;
}

int WindPlant::getWindPrice() {
    for (auto& whichMat : WindPlant().materials) {
        windPrice += whichMat.second * whichMat.first.getPrice();
    }
    return windPrice;
}

int SolarPlant::getSolarPrice() {
    for (auto& whichMat : SolarPlant().materials) {
        solarPrice += whichMat.second * whichMat.first.getPrice();
    }
    return solarPrice;
}

void Blueprint::buildBuilding() {
    Building* buildingChoice = buildingMenu();

    if (buildingChoice == nullptr) {
        return;
    }

    int startX{ posX() };
    int startY{ posY() };
    int breite{ buildingWidth() };
    int laenge{ buildingLength() };

    for (int i = startX; i < startX + breite; i++) {
        for (int j = startY; j < startY + laenge; j++) {
            if ((startX + breite) > width || (startY + laenge) > length || Area[j][i] != nullptr) {
                cout << "Flaeche schon belegt oder ausserhalb des Baubereichs!\n\n";
                return buildBuilding();
            }
            else {
                Area[j][i] = buildingChoice;
            }
        }
    }
}

int Blueprint::posX() {
    string startX;

    cout << "X Position eingeben: \n";
    cin >> startX;
    if (regex_match(startX, numberCheck) && stoi(startX) < length) {
        return stoi(startX);
    }
    else {
        cout << "Zahl zwischen 0 und " << (length - 1) << " eingeben\n";
        return posX();
    }

}

int Blueprint::posY() {
    string startY;

    cout << "Y Position eingeben: \n";
    cin >> startY;
    if (regex_match(startY, numberCheck) && stoi(startY) < width) {
        return stoi(startY);
    }
    else {
        cout << "Zahl zwischen 0 und " << (width - 1) << " eingeben\n";
        return posY();
    }

}

int Blueprint::buildingWidth() {
    string breite;

    cout << "Wie breit soll die Flaeche sein: \n";
    cin >> breite;
    if (regex_match(breite, numberCheck) && stoi(breite) > 0 && stoi(breite) <= width) {
        return stoi(breite);
    }
    else {
        cout << "Die Breite muss eine Zahl zwischen 1 und " << width << " sein!\n";
        return buildingWidth();
    }
}

int Blueprint::buildingLength() {
    string laenge;

    cout << "Wie lang soll die Flaeche sein: \n";
    cin >> laenge;
    if (regex_match(laenge, numberCheck) && stoi(laenge) > 0 && stoi(laenge) <= length) {
        return stoi(laenge);
    }
    else {
        cout << "Die Laenge muss eine Zahl zwischen 1 und " << length << " sein!\n";
        return buildingLength();
    }
}

void Blueprint::buildingPlan() {
    int w = 0;
    int i = 0;
    int s = 0;

    for (int x = 0; x < length; x++) {
        for (int y = 0; y < width; y++) {
            if (Area[x][y] == nullptr) {
                cout << "[ ]";
            }
            else {
                cout << "[" << Area[x][y]->getLabel() << "]";
                if (Area[x][y]->getLabel() == 'W') {
                    w++;
                }
                if (Area[x][y]->getLabel() == 'I') {
                    i++;
                }
                if (Area[x][y]->getLabel() == 'S') {
                    s++;
                }
            }
        }
        cout << endl;
    }

    // Wasserkraftwerk
    cout << endl
        << w << " Wassserkraftwerke\n"
        << "Ein einzelnes Wasserkraftwerk kostet: " << WaterPlant().getPrice() << "$\n"
        << "Fuer die Wasserkraftwerke werden benoetigt: ";

    for (auto& whichMat : WaterPlant().materials) {
        cout << "[" << w * whichMat.second << " " << whichMat.first.getName() << "] ";
    }

    cout << endl
        << "Die Gesamtkosten der Wasserkraftwerke betragen:  "
        << w * (WaterPlant().getPrice() + WaterPlant().getWaterPrice()) << "$\n";

    // Windkraftwerk
    cout << endl
        << i << " Windkraftwerke\n"
        << "Ein einzelnes Windkraftwerk kostet: " << WindPlant().getPrice() << "$\n"
        << "Fuer die Windkraftwerk werden benoetigt: ";

    for (auto& whichMat : WindPlant().materials) {
        cout << "[" << i * whichMat.second << " " << whichMat.first.getName() << "] ";
    }

    cout << endl
        << "Die Gesamtkosten der Wasserkraftwerke betragen:  "
        << i * (WindPlant().getPrice() + WindPlant().getWindPrice()) << "$\n";

    // Solarpanel
    cout << endl
        << s << " Solarpanel\n"
        << "Ein einzelnes Solarpanel kostet: " << SolarPlant().getPrice() << "$\n"
        << "Fuer die Solarpanel werden benoetigt: ";

    for (auto& whichMat : SolarPlant().materials) {
        cout << "[" << s * whichMat.second << " " << whichMat.first.getName() << "] ";
    }

    cout << endl
        << "Die Gesamtkosten der Wasserkraftwerke betragen:  "
        << s * (SolarPlant().getPrice() + SolarPlant().getSolarPrice()) << "$\n";

    CapycitySim().menu();
}

void Blueprint::deleteArea() {
    int startX{ posX() };
    int startY{ posY() };
    int breite{ buildingWidth() };
    int laenge{ buildingLength() };

    for (int i = startX; i < min(width, startX + breite); i++) {
        for (int j = startY; j < min(length, startY + laenge); j++) {
            Area[j][i] = nullptr;
        }
    }
    CapycitySim().menu();
}

void CapycitySim::menu() {
    cout << endl
        << "1 - Gebaeude setzen\n"
        << "2 - Bereich loeschen\n"
        << "3 - Aktueller Bauplan\n"
        << "4 - Plan auswaehlen\n"
        << "5 - Exit\n";
    
    cin >> choice;
    
    if (regex_match(choice, menuCheck)) {
        switch (stoi(choice)) {
        case 1:
            //Gebäude setzen    
                Blueprint().buildBuilding();
                break;
            case 2:
                //Bereich löschen
                Blueprint().deleteArea();
                break;
            case 3:
                //Print Blauplan
                Blueprint().buildingPlan();
                break;
            case 4:
                planMenu();
                break;
            case 5:
                //Beenden des Programms
                cout << "Bye Bye";
                exit(0);
            }
        }
    else {
            cout << "Nur Zahlen von 1 - 5 erlaubt!\n";
            menu();     
    }
};

void CapycitySim::createArea(int argc, char** argv) {
    Area = new Building** [length];
    for (int x = 0; x < length; x++) {
        Area[x] = new Building * [width];
        for (int y = 0; y < length; y++) {
            Area[x][y] = nullptr;
        }
    }
}

Building *buildingMenu() {
    cout << "Welches Gebaeude soll gebaut werden?";

    cout << endl
        << "1 - Wasserkraftwerk\n"
        << "2 - Windkraftwerk\n"
        << "3 - Solarpanele\n"
        << "4 - Zurueck zum Hauptmenue\n";
    cin >> choice;

    if (regex_match(choice, buildingCheck)) {
        switch (stoi(choice)) {
        case 1:
            return new WaterPlant();
            break;
        case 2:
            return new WindPlant();
            break;
        case 3:
            return new SolarPlant();
            break;
        default:
            return nullptr;
        }
    }
    else {
        cout << "Nur Zahlen von 1 - 4 erlaubt!\n";
        return buildingMenu();
    }
}

void CapycitySim::planMenu() {
    cout << endl
        << "3 Plaene verfuegbar: \n\n"
        << "1 - Plan 1\n"
        << "2 - Plan 2\n"
        << "3 - Plan 3\n";

    cin >> choice;

    if (regex_match(choice, planMenuCheck)) {
        switch (stoi(choice)) {
        case 1:
            Area = Plan[0];
            break;
        case 2:
            Area = Plan[1];
            break;
        case 3:
            Area = Plan[2];
            break;
        }
    }
    else {
        cout << "Nur Zahlen von 1 - 3 erlaubt!\n";
        planMenu();
    }
};

int main(int argc, char** argv) {
    length = stoi(argv[1]);
    width = stoi(argv[2]);

    cout << "Willkommen in CapyCity!\n";

    CapycitySim().createArea(argc, argv);

    for (int iterate = 0; iterate < 3; iterate++) {
        Plan[iterate] = Area;
        CapycitySim().createArea(argc, argv);    }

    Area = Plan[0];

    CapycitySim CapycitySim;
    while (true) {
        CapycitySim.menu();
    }
}