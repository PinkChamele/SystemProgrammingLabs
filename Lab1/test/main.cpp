#include <iostream>
#include <string>
#include <vector>
#include "MalfunctionType.h"

using namespace std;

int main(int argc, char** argv)
{
    MalfunctionType stackBasedMalfunctionType;
    stackBasedMalfunctionType.setModelId(1);
    stackBasedMalfunctionType.addComponent(0);
    stackBasedMalfunctionType.countPrice();
    
    MalfunctionType* heapBasedMalfunctionType;
    heapBasedMalfunctionType->setModelId(2);
    heapBasedMalfunctionType->addComponent(0);
    heapBasedMalfunctionType->countPrice();
    delete myTicket2;
    return 0;
}
