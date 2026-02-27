#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class Appliance {
private:
    string name;
    double powerRating;   // in Watts
    double hoursPerDay;   // in Hours

public:
    Appliance() {
        name = "";
        powerRating = 0;
        hoursPerDay = 0;
    }

    void inputAppliance() {
        cin.ignore();

        cout << "Enter appliance name: ";
        getline(cin, name);

        while (name.empty()) {
            cout << "Name cannot be empty. Enter again: ";
            getline(cin, name);
        }

        cout << "Enter power rating (Watts): ";
        cin >> powerRating;
        while (powerRating <= 0) {
            cout << "Power rating must be greater than 0. Enter again: ";
            cin >> powerRating;
        }

        cout << "Enter usage hours per day (0-24): ";
        cin >> hoursPerDay;
        while (hoursPerDay < 0 || hoursPerDay > 24) {
            cout << "Hours must be between 0 and 24. Enter again: ";
            cin >> hoursPerDay;
        }
    }

    void displayAppliance() const {
        cout << left << setw(20) << name
             << setw(15) << powerRating
             << setw(15) << hoursPerDay
             << setw(15) << calculateEnergy() << endl;
    }

    double calculateEnergy() const {
        return (powerRating * hoursPerDay) / 1000.0;
    }

    string getName() const { return name; }
    double getPower() const { return powerRating; }
    double getHours() const { return hoursPerDay; }

    void setData(string n, double p, double h) {
        name = n;
        powerRating = p;
        hoursPerDay = h;
    }
};

vector<Appliance> appliances;

void loadFromFile() {
    ifstream file("appliances.txt");
    if (!file) return;

    string name;
    double power, hours;

    while (getline(file, name, ',') &&
           file >> power &&
           file.ignore() &&
           file >> hours) {

        Appliance a;
        a.setData(name, power, hours);
        appliances.push_back(a);
        file.ignore();
    }

    file.close();
}

void saveToFile() {
    ofstream file("appliances.txt");

    for (const auto &a : appliances) {
        file << a.getName() << ","
             << a.getPower() << ","
             << a.getHours() << endl;
    }

    file.close();
}

void registerAppliance() {
    Appliance a;
    a.inputAppliance();
    appliances.push_back(a);
    cout << "Appliance registered successfully.\n";
}

void viewAppliances() {
    if (appliances.empty()) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << left << setw(20) << "Name"
         << setw(15) << "Power(W)"
         << setw(15) << "Hours"
         << setw(15) << "Energy(kWh)" << endl;

    for (const auto &a : appliances) {
        a.displayAppliance();
    }
}

void searchAppliance() {
    cin.ignore();
    string searchName;
    cout << "Enter appliance name to search: ";
    getline(cin, searchName);

    for (const auto &a : appliances) {
        if (a.getName() == searchName) {
            cout << "\nAppliance Found:\n";
            a.displayAppliance();
            return;
        }
    }

    cout << "Appliance not found.\n";
}

double calculateTotalEnergy() {
    double total = 0;
    for (const auto &a : appliances) {
        total += a.calculateEnergy();
    }
    return total;
}

void calculateBilling() {
    if (appliances.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    double tariff;
    cout << "Enter electricity tariff per kWh: ";
    cin >> tariff;

    while (tariff <= 0) {
        cout << "Tariff must be positive. Enter again: ";
        cin >> tariff;
    }

    double totalEnergy = calculateTotalEnergy();
    double totalCost = totalEnergy * tariff;

    cout << fixed << setprecision(2);
    cout << "\nTotal Energy Consumption: " << totalEnergy << " kWh/day\n";
    cout << "Total Electricity Cost: " << totalCost << endl;

    ofstream billFile("billing_summary.txt");
    billFile << "Total Energy: " << totalEnergy << " kWh/day\n";
    billFile << "Tariff: " << tariff << "\n";
    billFile << "Total Cost: " << totalCost << endl;
    billFile.close();
}

void menu() {
    int choice;

    do {
        cout << "\n=====================================\n";
        cout << "        Electrical Load Monitoring\n";
        cout << "=====================================\n";

        cout << "1. Register appliance\n";
        cout << "2. View all appliances\n";
        cout << "3. Search appliance by name\n";
        cout << "4. Energy summary (kWh/day)\n";
        cout << "5. Billing summary (save to file)\n";
        cout << "0. Exit\n";
        cout << "\nChoose: ";

        cin >> choice;

        switch (choice) {
            case 1:
                registerAppliance();
                break;
            case 2:
                viewAppliances();
                break;
            case 3:
                searchAppliance();
                break;
            case 4:
                cout << "\nTotal Energy Consumption: "
                     << calculateTotalEnergy()
                     << " kWh/day\n";
                break;
            case 5:
                calculateBilling();
                break;
            case 0:
                saveToFile();
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}

int main() {
    loadFromFile();
    menu();
    return 0;
}