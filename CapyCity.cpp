#include <iostream>
#include <string>
#include <regex>
#include <vector>
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

class WaterPlant : public Building {
public:
    WaterPlant() : Building(100, 'W') {
        materials = vector<Material>() = { 
            Wood(),
            Wood(), 
            Metal(), 
            Metal()};
    }
    vector<Material> materials;
};

class WindPlant : public Building {
public:
    WindPlant() : Building(50, 'I') {
        materials = vector<Material>() = {
            Plastic(),
            Plastic(),
            Metal(),
            Metal() };
    }
    vector<Material> materials;
};

class SolarPlant : public Building {
public:
    SolarPlant() : Building(250, 'S') {
        materials = vector<Material>() = {
            Plastic(),
            Plastic(),
            Plastic(),
            Metal() };
    }
    vector<Material> materials;
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

        int mat = 0;
        int mat2 = 0;
        int matCost = 0;
        for (int count = 0; count < w; count++) {
            for (auto& i : WaterPlant().materials) {
                if (i.getName() == "Holz") {
                    mat++;
                    matCost += Wood().getPrice();
                }
                if (i.getName() == "Metall") {
                    mat2++;
                    matCost += Metal().getPrice();
                }
            }
        }
        cout 
            << endl << w << " Wasserkraftwerke\n"
            << "Ein einzelnes Wasserkraftwerk kostet: " << WaterPlant().getPrice() << "$\n"
            << "Fuer die Wasserkraftwerke wird " << mat << " Holz und " << mat2 << " Metall benoetigt\n"
            << "Die Gesamtkosten betragen der Wasserkraftwerke: " << (w * WaterPlant().getPrice()) + matCost << "$\n";

        int allCost = 0;
        allCost += (w * WaterPlant().getPrice()) + matCost;

        mat = 0;
        mat2 = 0;
        matCost = 0;
        for (int count = 0; count < i; count++) {
            for (auto& i : WindPlant().materials) {
                if (i.getName() == "Kunststoff") {
                    mat++;
                    matCost += Plastic().getPrice();
                }
                if (i.getName() == "Metall") {
                    mat2++;
                    matCost += Metal().getPrice();
                }
            }
        }
        cout
            << endl << i << " Windkraftwerke\n"
            << "Ein einzelnes Windkraftwerk kostet: " << WindPlant().getPrice() << "$\n"
            << "Fuer die Windkraftwerke wird " << mat << " Kunststoff und " << mat2 << " Metall benoetigt\n"
            << "Die Gesamtkosten betragen der Windkraftwerke: " << (i * WindPlant().getPrice()) + matCost << "$\n";

        allCost += (i * WindPlant().getPrice()) + matCost;

        mat = 0;
        mat2 = 0;
        matCost = 0;
        for (int count = 0; count < s; count++) {
            for (auto& i : SolarPlant().materials) {
                if (i.getName() == "Kunststoff") {
                    mat++;
                    matCost += Plastic().getPrice();
                }
                if (i.getName() == "Metall") {
                    mat2++;
                    matCost += Metal().getPrice();
                }
            }
        }
        cout
            << endl << s << " Solarpanele\n"
            << "Ein einzelnes Solarpanel kostet: " << SolarPlant().getPrice() << "$\n"
            << "Fuer das Solarpanel wird " << mat << " Kunststoff und " << mat2 << " Metall benoetigt\n"
            << "Die Gesamtkosten der Solarpanele betragen: " << (s * SolarPlant().getPrice()) + matCost << "$\n";

        allCost += (s * SolarPlant().getPrice()) + matCost;
        cout << endl << "Alles zusammen kostet: " << allCost << "$\n";

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