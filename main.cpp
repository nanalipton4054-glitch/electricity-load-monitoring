#include <iostream>
#include <iomanip>
using namespace std;

class Appliance {
private:
    string name;
    double powerRating;   // Watts
    double hoursPerDay;   // Hours

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
        cout << "\nAppliance Details\n";
        cout << "Name: " << name << endl;
        cout << "Power: " << powerRating << " W\n";
        cout << "Hours per day: " << hoursPerDay << endl;
        cout << "Energy consumption: " 
             << calculateEnergy() << " kWh/day\n";
    }
};

int main() {
    Appliance a;
    a.inputAppliance();
    a.displayAppliance();
    return 0;
}