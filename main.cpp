#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

double getValidatedDouble(string message, double min, double max) {
    double value;

    while (true) {
        cout << message;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a numeric value.\n";
            continue;
        }

        if (value < min || value > max) {
            cout << "Value must be between "
                 << min << " and " << max << endl;
            continue;
        }

        break;
    }

    return value;
}

class Appliance {
private:
    string name;
    double powerRating;
    double hoursPerDay;

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

        powerRating = getValidatedDouble(
            "Enter power rating (Watts): ", 0.1, 100000);

        hoursPerDay = getValidatedDouble(
            "Enter usage hours per day (0-24): ", 0, 24);
    }

    double calculateEnergy() const {
        return (powerRating * hoursPerDay) / 1000.0;
    }

    void displayAppliance() const {
        cout << left << setw(20) << name
             << setw(15) << powerRating
             << setw(15) << hoursPerDay
             << setw(15) << calculateEnergy() << endl;
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

double calculateTotalEnergy() {
    double total = 0;
    for (const auto &a : appliances)
        total += a.calculateEnergy();
    return total;
}

void calculateBilling() {
    if (appliances.empty()) {
        cout << "No appliances available.\n";
        return;
    }

    double tariff = getValidatedDouble(
        "Enter electricity tariff per kWh: ", 0.01, 100);

    double totalEnergy = calculateTotalEnergy();
    double totalCost = totalEnergy * tariff;

    cout << fixed << setprecision(2);
    cout << "\nTotal Energy Consumption: "
         << totalEnergy << " kWh/day\n";
    cout << "Total Electricity Cost: "
         << totalCost << endl;

    ofstream billFile("billing_summary.txt");
    billFile << "Total Energy: " << totalEnergy << " kWh/day\n";
    billFile << "Tariff: " << tariff << "\n";
    billFile << "Total Cost: " << totalCost << endl;
    billFile.close();
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

    for (const auto &a : appliances)
        a.displayAppliance();
}

void menu() {
    int choice;

    do {
        cout << "\n=====================================\n";
        cout << "        Electrical Load Monitoring\n";
        cout << "=====================================\n";

        cout << "1. Register appliance\n";
        cout << "2. View all appliances\n";
        cout << "3. Energy summary (kWh/day)\n";
        cout << "4. Billing summary\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid menu choice.\n";
            continue;
        }

        switch (choice) {
            case 1: registerAppliance(); break;
            case 2: viewAppliances(); break;
            case 3:
                cout << "\nTotal Energy Consumption: "
                     << calculateTotalEnergy()
                     << " kWh/day\n";
                break;
            case 4: calculateBilling(); break;
            case 0:
                saveToFile();
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

int main() {
    loadFromFile();
    menu();
    return 0;
}
