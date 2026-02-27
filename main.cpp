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
};

double calculateTotalEnergy(const vector<Appliance>& appliances) {
    double total = 0;
    for (const auto& a : appliances) {
        total += a.calculateEnergy();
    }
    return total;
}

int main() {
    vector<Appliance> appliances;
    int count;

    cout << "How many appliances do you want to register? ";
    cin >> count;

    for (int i = 0; i < count; i++) {
        Appliance a;
        a.inputAppliance();
        appliances.push_back(a);
    }

    cout << "\nRegistered Appliances\n";
    cout << left << setw(20) << "Name"
         << setw(15) << "Power(W)"
         << setw(15) << "Hours"
         << setw(15) << "Energy(kWh)\n";

    for (const auto& a : appliances) {
        a.displayAppliance();
    }

    cout << "\nTotal Energy Consumption: "
         << calculateTotalEnergy(appliances)
         << " kWh/day\n";

    return 0;
}
