#include <string>
#include <map>
using namespace std;

int width;
int length;
string choice;
regex planMenuCheck("[1-4]");
regex buildingCheck("[1-4]");
regex menuCheck("[1-6]");
regex numberCheck("[[:digit:]]+");

class Building {
public:
	Building();
	Building(int basePrice, char label, double efficiency) :basePrice(basePrice), label(label), efficiency(efficiency) {};

	int getPrice() const;
	char getLabel() const;
	double getEfficiency() const;
	
protected:
	int basePrice;
	char label;
	double efficiency;
};

Building* buildingMenu();

Building*** Area;

Building*** Plan[3];

class Material {
public:
	Material(string name, int price) : name(name), price(price) {}

	string getName() const;
	int getPrice() const;
	
protected:
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
	map<Material, int, MaterialComparator> materials;

	WaterPlant() : Building(100, 'W', 500000.00) {
		materials = map<Material, int, MaterialComparator>({
			{Wood(), 2},
			{Metal(), 2},
			{Plastic(), 1}
			});
	}

	int getWaterPrice();
private:
	int waterPrice = 0;
};

class WindPlant : public Building {
public:
	WindPlant() : Building(50, 'I', 750000.00) {
		materials = map<Material, int, MaterialComparator>({
			{Plastic(), 2},
			{Metal(), 2}
			});
	}
	map<Material, int, MaterialComparator> materials;

	int getWindPrice();

private:
	int windPrice = 0;
};

class SolarPlant : public Building {
public:
	SolarPlant() : Building(250, 'S', 1000000.00) {
		materials = map<Material, int, MaterialComparator>({
		{Plastic(), 3},
		{Metal(), 1}
			});
	}
	map<Material, int, MaterialComparator> materials;

	int getSolarPrice();
private:
	int solarPrice = 0;
};

class CapycitySim {
public:
	void menu();
	void createArea(int argc, char** argv);
	void planMenu();
};

class Blueprint {
public:
	void buildBuilding();
	int posX();
	int posY();
	int buildingWidth();
	int buildingLength();
	void buildingPlan();
	void deleteArea();
	double coutEfficiency();
};

class IdenticalCheck {
public:
	//				a = Plan[0]	b = Plan[1]
	bool operator()(Building*** a, Building*** b) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < length; j++) {
				if (a[i][j] != nullptr && b[i][j] != nullptr) {
					if (a[i][j]->getLabel() != b[i][j]->getLabel()) {
						return false;
					}					
				}
				if ((a[i][j] == nullptr && b[i][j] != nullptr) 
					||(a[i][j] != nullptr && b[i][j] == nullptr) ){
					return false;
				}
			}
		}
		return true;
	}
};