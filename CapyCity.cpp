#include <iostream>
#include <string>
#include <regex>
#include "CapycitySim.h"
#include "vector"
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
    return (waterPrice + WaterPlant().getPrice());
}

int WindPlant::getWindPrice() {
    for (auto& whichMat : WindPlant().materials) {
        windPrice += whichMat.second * whichMat.first.getPrice();
    }
    return (windPrice + WindPlant().getPrice());
}

int SolarPlant::getSolarPrice() {
    for (auto& whichMat : SolarPlant().materials) {
        solarPrice += whichMat.second * whichMat.first.getPrice();
    }
    return (solarPrice + SolarPlant().getPrice());
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
            if ((startX + breite) > length || (startY + laenge) > width || Area[j][i] != nullptr) {
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
    if (regex_match(startX, numberCheck) && stoi(startX) < width) {
        return stoi(startX);
    }
    else {
        cout << "Zahl zwischen 0 und " << (width - 1) << " eingeben\n";
        return posX();
    }
}

int Blueprint::posY() {
    string startY;

    cout << "Y Position eingeben: \n";
    cin >> startY;
    if (regex_match(startY, numberCheck) && stoi(startY) < length) {
        return stoi(startY);
    }
    else {
        cout << "Zahl zwischen 0 und " << (length - 1) << " eingeben\n";
        return posY();
    }
}

int Blueprint::buildingWidth() {
    string breite;

    cout << "Wie breit soll die Flaeche sein: \n";
    cin >> breite;
    if (regex_match(breite, numberCheck) && stoi(breite) > 0 && stoi(breite) <= length) {
        return stoi(breite);
    }
    else {
        cout << "Die Breite muss eine Zahl zwischen 1 und " << length << " sein!\n";
        return buildingWidth();
    }
}

int Blueprint::buildingLength() {
    string laenge;

    cout << "Wie lang soll die Flaeche sein: \n";
    cin >> laenge;
    if (regex_match(laenge, numberCheck) && stoi(laenge) > 0 && stoi(laenge) <= width) {
        return stoi(laenge);
    }
    else {
        cout << "Die Laenge muss eine Zahl zwischen 1 und " << width << " sein!\n";
        return buildingLength();
    }
}

void Blueprint::buildingPlan() {
    int w = 0;
    int i = 0;
    int s = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < length; y++) {
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

    cout << endl << "Der Plan hat die Kennzahl: " <<  Blueprint().coutEfficiency(Plan[currentPlan]) << endl;

    CapycitySim().menu();
}

void Blueprint::deleteArea() {
    int startX{ posX() };
    int startY{ posY() };
    int breite{ buildingWidth() };
    int laenge{ buildingLength() };

    for (int i = startX; i < min(length, startX + breite); i++) {
        for (int j = startY; j < min(width, startY + laenge); j++) {
            Area[j][i] = nullptr;
        }
    }
    CapycitySim().menu();
}

double Blueprint::coutEfficiency(Building*** Area) {
    double index = 0;
    WaterPlant WaterPlant;
    WindPlant WindPlant;
    SolarPlant SolarPlant;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            if (Area[i][j] == nullptr) {
                continue;
            }
            else {
                if (Area[i][j]->getLabel() == 'W') {
                    index += WaterPlant.getEfficiency() / (WaterPlant.getWaterPrice() * (width * length));
                }
                if (Area[i][j]->getLabel() == 'I') {
                    index += WindPlant.getEfficiency() / (WindPlant.getWindPrice() * (width * length));
                }
                if (Area[i][j]->getLabel() == 'S') {
                    index += SolarPlant.getEfficiency() / (SolarPlant.getSolarPrice() * (width * length));
                }
            }
        }
    }
    return index;
}

void Blueprint::sortedCout() {
    sort(Plan.begin(), Plan.end(), [](Building*** a, Building*** b) {
        return Blueprint().coutEfficiency(a) > Blueprint().coutEfficiency(b);
        });
}

void CapycitySim::menu() {
    Blueprint blue;

    cout << endl
        << "    1 - Gebaeude setzen\n"
        << "    2 - Bereich loeschen\n"
        << "    3 - Aktueller Bauplan\n"
        << "    4 - Kennzahl\n"
        << "    5 - Plan Menu\n"
        << "    6 - Alle Plaene in absteigender Folge sortieren und ausgeben\n"
        << "    7 - Exit\n";
    
    cin >> choice;
    
    if (regex_match(choice, menuCheck)) {
        switch (stoi(choice)) {
            case 1:
                blue.buildBuilding();
                break;
            case 2:                
                blue.deleteArea();
                break;
            case 3:                
                blue.buildingPlan();
                break;            
            case 4:
                cout << "Die Kennzahl betraegt: "<< blue.coutEfficiency(Plan[currentPlan]) << endl;
                break;
            case 5:
                planMenu();
                break;
            case 6:
                blue.sortedCout();
                for (int i = 0; i < Plan.size(); i++) {
                    cout << "   Plan " << i + 1 << " Kennzahl " << blue.coutEfficiency(Plan[i]) << endl; 
                }
                break;                
            case 7:                
                cout << "Bye Bye";
                exit(0);
            }
        }
    else {
            cout << "Nur Zahlen von 1 - 7 erlaubt!\n";
            menu();     
    }
};

void CapycitySim::createArea() {
    Area = new Building** [width];
    for (int x = 0; x < width; x++) {
        Area[x] = new Building* [length];
        for (int y = 0; y < length; y++) {
            Area[x][y] = nullptr;
        }
    }
}

Building *buildingMenu() {
    cout << "Welches Gebaeude soll gebaut werden?\n";

    cout << endl
        << "    1 - Wasserkraftwerk\n"
        << "    2 - Windkraftwerk\n"
        << "    3 - Solarpanele\n"
        << "    4 - Zurueck zum Hauptmenue\n";
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
        cout << "   Nur Zahlen von 1 - 4 erlaubt!\n";
        return buildingMenu();
    }
}

void CapycitySim::planMenu() {
    CapycitySim CapyCitySim;

    cout << endl
        << "    1 - Neuen Plan erstellen\n"
        << "    2 - Plan auswaehlen\n"
        << "    3 - Zurueck zum Hauptmenu\n";

    cin >> choice;

    if (regex_match(choice, planMenuCheck)) {
        switch (stoi(choice)) {
        case 1:
            for (int i = 0; i < Plan.size(); i++) {
                if (i == currentPlan) {
                    break;
                }
                if (Blueprint().operator()(Plan[currentPlan], Plan[i]) != false) {
                    cout << "    Plan " << currentPlan + 1 << " identisch mit Plan " << i + 1 << "!\n"
                        << "    Plan " << currentPlan + 1 << " wird geloescht!\n";
                        Plan.pop_back();
                        planCounter -= 1;
                        break;
                    }
            }
            CapycitySim().createArea();
            Plan.push_back(Area);
            planCounter += 1;
            currentPlan = planCounter;
            cout << endl << "Neuen Plan " << currentPlan + 1 <<  " erstellt und als bearbeitenden Plan ausgewaehlt\n";
            break;            
        case 2:
            return CapyCitySim.planChoice();
        default:
            return menu();
        }
    }
    else {
        cout << "   Nur Zahlen von 1 - 3 erlaubt!\n";
        planMenu();
    }
};

void CapycitySim::planChoice() {
    Blueprint blue;

    cout << "    " << Plan.size() << " Plaene verfuegbar\n"
        << "    Momentaner Plan: " << currentPlan + 1 << " Kennzahl: " << blue.coutEfficiency(Plan[currentPlan]) << "\n\n"
        << "    1 - Erster Plan\n"
        << "    2 - Naechster Plan\n"
        << "    3 - Vorheriger Plan\n"
        << "    4 - Letzter Plan\n"
        << "    5 - Auswahl bestaetigen\n";

    cin >> choice;

    if (regex_match(choice, planChoiceCheck)) {
        switch (stoi(choice)) {
        case 1:
            Area = Plan.front();
            currentPlan = 0;
            cout << "    Plan 1" << " Kennzahl: " << blue.coutEfficiency(Plan[currentPlan]) << endl << endl;
            planChoice();
            break;
        case 2:
            if (currentPlan == Plan.size() - 1) {
                currentPlan = 0;
            }
            else {
                currentPlan += 1;
            }
            Area = Plan[currentPlan];
            cout << "    Plan " << currentPlan + 1 << " Kennzahl: " << blue.coutEfficiency(Plan[currentPlan]) << endl << endl;
            planChoice();
            break;
        case 3:
            if (currentPlan == 0){
                currentPlan = Plan.size() - 1;
            }
            else {
                currentPlan -= 1;
            }
            Area = Plan[currentPlan];
            cout << "    Plan " << currentPlan - 1 << " Kennzahl: " << blue.coutEfficiency(Plan[currentPlan]) << endl << endl;
            planChoice();
            break;
        case 4:            
            Area = Plan.back();
            currentPlan = planCounter;
            cout << "    Plan " << Plan.size() << " Kennzahl: " << blue.coutEfficiency(Plan[currentPlan]) << endl << endl;
            planChoice();
            break;
        case 5:
            break;
        }
    }
    else {
        cout << "   Nur Zahlen von 1 - 5 erlaubt!\n\n";
        planChoice();
    }
}

int main(int argc, char** argv) {
    width = stoi(argv[1]);
    length = stoi(argv[2]);

    cout << "    Willkommen in CapyCity!\n";

    CapycitySim().createArea();

    Plan.push_back(Area);
      
    CapycitySim CapycitySim;
    while (true) {
        CapycitySim.menu();
    }
}