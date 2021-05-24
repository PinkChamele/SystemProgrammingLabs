#include "MalfunctionType.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

MalfunctionType::MalfunctionType()
{
    typeId = 0;
    modelId = 0;
    description = "Default description";
    price = 0;
}

MalfunctionType::~MalfunctionType()
{
    //dtor
}

void MalfunctionType::setTypeId(int inTypeId) {
    typeId = inTypeId;
}

int MalfunctionType::getTypeId() {
    return typeId;
}

void MalfunctionType::setModelId(int inModelId) {
    modelId = inModelId;
}

int MalfunctionType::getModelId() {
    return modelId;
}

void MalfunctionType::setDescription(string inDescription) {
    description = inDescription;
}

string MalfunctionType::getDescription() {
    return description;
}

void MalfunctionType::addSymptom(string symptom) {
    symptoms.push_back(symptom);
}

vector<string> MalfunctionType::getSymptoms() {
    return symptoms;
}

void MalfunctionType::addRepairMethod(string repairMethod) {
    repairMethods.push_back(repairMethod);
}

vector<string> MalfunctionType::getRepairMethods() {
    return repairMethods;
}

void MalfunctionType::addComponent(int component) {
    components.push_back(component);
}

vector<int> MalfunctionType::getComponents() {
    return components;
}

bool MalfunctionType::isFixed() {
    return fixed;
}

void MalfunctionType::fix() {
    fixed = true;
}

void MalfunctionType::countPrice() {
    switch (modelId) {
        case 1:
            price = 10 * components.size();
            break;
        case 2:
            price = 13 * components.size();
            break;
        default:
            price = 0;
            break;
    }
}

int MalfunctionType::getPrice() {
    return price;
}
void MalfunctionType::display() {
    cout << "-----------Malfunction Type-----------" << endl;
    cout << "TypeId: " << typeId << endl;
    cout << "ModelId " << modelId << endl;
    cout << "Description " << modelId << endl;
    cout << "Is fixed " << fixed << endl;
    cout << "Symptoms: ";
    for (int i = 0; i < symptoms.size(); i++) {
        cout << symptoms[i] << "; ";
    }
    cout << endl;
    cout << "Repair methods: ";
    for (int i = 0; i < repairMethods.size(); i++) {
        cout << repairMethods[i] << "; ";
    }
    cout << endl;
    cout << "Components id: ";
    for (int i = 0; i < components.size(); i++) {
        cout << components[i] << "; ";
    }
    cout << endl;
    cout << "Price $" << price << endl;
}
