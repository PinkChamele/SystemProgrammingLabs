#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "Database.h"
#include <string>
#include <vector>

using namespace std;

int displayMenu();
void doAddMalfunction (Records::Database& inDB);
void doFixMalfunction (Records::Database& inDB);
#endif
