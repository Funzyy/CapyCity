#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
using namespace std;

int length;
int width;
regex menuCheck("[1-4]");
regex numberCheck("[[:digit:]]+");

void menu();

class Building {
public:
    Building() {
        basePrice = 0;
        label = '0';        
    }

    Building(
        int basePrice,char label):basePrice(basePrice),label(label){}

    int getPrice() const {
        return basePrice;
    }

    char getLabel() const {
        return label;
    }

protected:
    int basePrice;
    char label;
    string name;
};

class Material {
public:
    Material(string name, int price) : name(name), price(price) {}
    string getName() const {
        return name;
    }
    int getPrice() const {
        return price;
    }
private:
    string name;
    int price;
};

class Wood : public Material {
public:
    Wood() : Material("Holz", 25) {}
};

class Metal : public Material {
public:
    Metal() : Material("Metall", 15) {}
};

class Plastic : public Material {
public:
    Plastic() : Material("Kunststoff", 5) {}
};

struct MaterialComparator {
    bool operator()(const Material& m1, const Material& m2) const {
        return m1.getName() < m2.getName();
    }
};

class WaterPlant : public Building {
public:
    WaterPlant() : Building(100, 'W') {
        materials = map<Material, int, MaterialComparator>({
            {Wood(), 2},
            {Metal(), 2},
            {Plastic(), 1}
            });
    }
    map<Material, int, MaterialComparator> materials;
};

class WindPlant : public Building {
public:
    WindPlant() : Building(50, 'I') {
        materials = map<Material, int, MaterialComparator>({
            {Plastic(), 2},
            {Metal(), 2}
            });
    }
    map<Material, int, MaterialComparator> materials;
};

class SolarPlant : public Building {
public:
    SolarPlant() : Building(250, 'S') {
        materials = map<Material, int, MaterialComparator>({
        {Plastic(), 3},
        {Metal(), 1}
            });
    }
    map<Material, int, MaterialComparator> materials;
};

Building *buildingMenu();

Building*** Area;

int main(int argc, char **argv) {
    
    length = stoi(argv[1]);
    width = stoi(argv[2]);

    cout << "Willkommen in CapyCity!\n";

    Area = new Building** [length];
    for (int x = 0; x < length; x++) {
        Area[x] = new Building*[width];
        for (int y = 0; y < length; y++) {
            Area[x][y] = nullptr;
        }
    }

    while (true) {
        menu();
    }
}

class CapycitySim {
public:
    void buildBuilding() {
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

    int posX() {
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

    int posY() {
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

    int buildingWidth() {
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

    int buildingLength() {
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

    void buildingPlan() {
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
                    if (Area[x][y]-> getLabel() == 'W') {
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
        int matCost = 0;

        cout << endl 
            << w << " Wassserkraftwerke\n"
            << "Ein einzelnes Wasserkraftwerk kostet: " << WaterPlant().getPrice() << "$\n"
            << "Fuer die Wasserkraftwerke werden benoetigt: ";

            for (auto& whichMat : WaterPlant().materials) {
                cout << "[" << w * whichMat.second << " " << whichMat.first.getName() << "] ";
                matCost += whichMat.second * whichMat.first.getPrice();
            }            

        cout << endl 
            << "Die Gesamtkosten der Wasserkraftwerke betragen:  " 
            << w * (WaterPlant().getPrice() + matCost) << "$\n";


        // Windkraftwerk
        matCost = 0;

        cout << endl
            << i << " Windkraftwerke\n"
            << "Ein einzelnes Windkraftwerk kostet: " << WindPlant().getPrice() << "$\n"
            << "Fuer die Windkraftwerk werden benoetigt: ";

        for (auto& whichMat : WindPlant().materials) {
            cout << "[" << i * whichMat.second << " " << whichMat.first.getName() << "] ";
            matCost += whichMat.second * whichMat.first.getPrice();
        }

        cout << endl
            << "Die Gesamtkosten der Wasserkraftwerke betragen:  "
            << i * (WindPlant().getPrice() + matCost) << "$\n";

        // Solarpanel
        matCost = 0;

        cout << endl
            << s << " Solarpanel\n"
            << "Ein einzelnes Solarpanel kostet: " << SolarPlant().getPrice() << "$\n"
            << "Fuer die Solarpanel werden benoetigt: ";

        for (auto& whichMat : SolarPlant().materials) {
            cout << "[" << s * whichMat.second << " " << whichMat.first.getName() << "] ";
            matCost += whichMat.second * whichMat.first.getPrice();
        }

        cout << endl
            << "Die Gesamtkosten der Wasserkraftwerke betragen:  "
            << s * (SolarPlant().getPrice() + matCost) << "$\n";

        menu();
    }

    void deleteArea() {
        int startX{ posX() };
        int startY{ posY() };
        int breite{ buildingWidth() };
        int laenge{ buildingLength() };

        for (int i = startX; i < min(width , startX + breite); i++) {
            for (int j = startY; j < min(length, startY + laenge); j++) {
                Area[j][i] = nullptr;                
            }
        }
        menu();
    }
};

void menu(){
    string choice;

    CapycitySim CapycitySim;

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
            CapycitySim.buildBuilding();
            break;
        case 2:
            //Bereich löschen
            CapycitySim.deleteArea();
            break;
        case 3:
            //Print Blauplan
            CapycitySim.buildingPlan();
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

Building *buildingMenu() {
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