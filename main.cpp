#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

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

        cout << "Enter power rating (Watts): ";
        cin >> powerRating;

        while (powerRating <= 0) {
            cout << "Power rating must be greater than 0: ";
            cin >> powerRating;
        }

        cout << "Enter usage hours per day (0-24): ";
        cin >> hoursPerDay;

        while (hoursPerDay < 0 || hoursPerDay > 24) {
            cout << "Hours must be between 0 and 24: ";
            cin >> hoursPerDay;
        }
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
};

vector<Appliance> appliances;

double calculateTotalEnergy() {
    double total = 0;
    for (const auto& a : appliances) {
        total += a.calculateEnergy();
    }
    return total;
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
         << setw(15) << "Energy(kWh)\n";

    for (const auto& a : appliances) {
        a.displayAppliance();
    }
}

void searchAppliance() {
    cin.ignore();
    string searchName;

    cout << "Enter appliance name to search: ";
    getline(cin, searchName);

    for (const auto& a : appliances) {
        if (a.getName() == searchName) {
            cout << "\nAppliance Found:\n";
            a.displayAppliance();
            return;
        }
    }

    cout << "Appliance not found.\n";
}

void menu() {
    int choice;

    do {
        cout << "\nElectrical Load Monitoring\n";
        cout << "1. Register appliance\n";
        cout << "2. View all appliances\n";
        cout << "3. Search appliance\n";
        cout << "4. Energy summary\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        cin >> choice;

        switch (choice) {
            case 1: registerAppliance(); break;
            case 2: viewAppliances(); break;
            case 3: searchAppliance(); break;
            case 4:
                cout << "Total Energy Consumption: "
                     << calculateTotalEnergy()
                     << " kWh/day\n";
                break;
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
