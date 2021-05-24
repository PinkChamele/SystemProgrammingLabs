#include <string>
#include <vector>
#include <stdexcept>

#include "Database.h"

using namespace std;

namespace Records {

    Database::Database() {
        mNextSlot = 0;
        mNextMalfunctionTypeNumber = kFirstMalfunctionTypeNumber;
    }

    Database::~Database() {
    }

    MalfunctionType& Database::addMalfunctionType(int modelId, string description) {
        if(mNextSlot >= kMaxMalfunctionTypes) {
            cerr << "" << endl;
            throw exception();
        }

        MalfunctionType& malfunctionType = mMalfunctionTypes[mNextSlot++];
        malfunctionType.setModelId(modelId);
        malfunctionType.setDescription(description);
        malfunctionType.setTypeId(mNextMalfunctionTypeNumber++);

        return malfunctionType;
    }

    MalfunctionType& Database::getMalfunctionType(int typeId) {
        for (int i = 0; i < mNextSlot; i++) {
            if (mMalfunctionTypes[i].getTypeId() == typeId) {
                return mMalfunctionTypes[i];
            }
        }

        cerr << "No such malfunctionType with typeId " << typeId << endl;
        throw exception();
    }

    void Database::displayAll() {
        for (int i = 0; i < mNextSlot; i++) {
            mMalfunctionTypes[i].display();
        }
    }
}
