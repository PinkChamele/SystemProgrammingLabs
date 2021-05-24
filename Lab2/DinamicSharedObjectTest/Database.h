#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>
#include <iostream>
#include "MalfunctionType.h"

using namespace std;

namespace Records {
    const int kMaxMalfunctionTypes = 100;
    const int kFirstMalfunctionTypeNumber = 1000;

    class Database {
        public:
            Database();
            ~Database();

            MalfunctionType& addMalfunctionType(int modelId, string description);
            MalfunctionType& getMalfunctionType(int typeId);
            void displayAll();
        private:
            MalfunctionType mMalfunctionTypes[kMaxMalfunctionTypes];
            int mNextSlot;
            int mNextMalfunctionTypeNumber;
    };
}
#endif
