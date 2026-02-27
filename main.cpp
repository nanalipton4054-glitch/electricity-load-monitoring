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
            cout << "Invalid input.\n";
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
    void inputAppliance() {
        cin.ignore();
        cout << "Enter appliance name: ";
        getline(cin, name);

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
}

void saveToFile() {
    ofstream file("appliances.txt");
    for (const auto &a : appliances) {
        file << a.getName() << ","
             << a.getPower() << ","
             << a.getHours() << endl;
    }
}

double calculateTotalEnergy() {
    double total = 0;
    for (const auto &a : appliances)
        total += a.calculateEnergy();
    return total;
}

void deleteAppliance() {
    cin.ignore();
    string name;

    cout << "Enter appliance name to delete: ";
    getline(cin, name);

    for (auto it = appliances.begin();
         it != appliances.end(); ++it) {

        if (it->getName() == name) {
            appliances.erase(it);
            cout << "Appliance deleted successfully.\n";
            return;
        }
    }

    cout << "Appliance not found.\n";
}

void viewReport() {
    double daily = calculateTotalEnergy();
    double monthly = daily * 30;
    double yearly = daily * 365;

    cout << fixed << setprecision(2);
    cout << "\nEnergy Report\n";
    cout << "Daily:   " << daily << " kWh\n";
    cout << "Monthly: " << monthly << " kWh\n";
    cout << "Yearly:  " << yearly << " kWh\n";
}

void registerAppliance() {
    Appliance a;
    a.inputAppliance();
    appliances.push_back(a);
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
        cout << "\n=== Electrical Load Monitoring ===\n";
        cout << "1. Register appliance\n";
        cout << "2. View appliances\n";
        cout << "3. Delete appliance\n";
        cout << "4. Energy report (daily/monthly/yearly)\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: registerAppliance(); break;
            case 2: viewAppliances(); break;
            case 3: deleteAppliance(); break;
            case 4: viewReport(); break;
            case 0:
                saveToFile();
                cout << "Exiting...\n";
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
