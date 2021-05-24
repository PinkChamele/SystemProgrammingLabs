#include <iostream>
#include <stdexcept>
#include <string>

#include "UsetInterface.h"
#include "Database.h"

using namespace std;

int displayMenu() {
    int selection;

    cout << endl;
    cout << "Malfunction Database" << endl;
    cout << "------------" << endl;
    cout << "1) Add malfunction" << endl;
    cout << "2) Fix malfunction" << endl;
    cout << "3) List all malfunctions" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "->";

    cin >> selection;

    return selection;
}

void doAddMalfunction (Records::Database& inDB) {
    string description;
    int modelId;

    cout << "Enter description: ";
    cin >> description;
    cout << "Enter modelId: ";
    cin >> modelId;

    try {
        inDB.addMalfunctionType(modelId, description);
    } catch (std::exception ex) {
        cerr << "Unable to add malfunction" << endl;
    }
}

void doFixMalfunction (Records::Database& inDB) {
    int malfunctionNumber;

    cout << "Enter malfunction number: ";
    cin >> malfunctionNumber;

    try {
        MalfunctionType& malfunction = inDB.getMalfunctionType(malfunctionNumber);
        malfunction.fix();
        cout << "Malfunction " << malfunctionNumber << " is fixed";
    } catch (std::exception ex) {
        cerr << "Unable to fix malfunction" << std::endl;
    }
}
