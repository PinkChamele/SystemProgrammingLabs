#include <iostream>
#include <string>
#include <vector>
#include "UsetInterface.h"
#include "Database.h"

using namespace std;

int main(int argc, char** argv)
{
    Records::Database malfunctionDB;
    bool isDone = false;

    while (!isDone) {
        int selection = displayMenu();
        switch(selection) {
            case 1:
                doAddMalfunction(malfunctionDB);
                break;
            case 2:
                doFixMalfunction(malfunctionDB);
                break;
            case 3:
                malfunctionDB.displayAll();
                break;
            case 0:
                isDone = true;
                break;
            default:
                cerr << "Unknown command" << endl;
        }
    }
    return 0;
}
