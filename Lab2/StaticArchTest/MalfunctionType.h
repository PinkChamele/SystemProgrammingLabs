#ifndef MALFUNCTIONTYPE_H
#define MALFUNCTIONTYPE_H
#include <string>
#include <vector>

using namespace std;

class MalfunctionType
{
    public:
        void setTypeId(int inTypeId);
        int getTypeId();

        void setModelId(int inModelId);
        int getModelId();

        void addSymptom(string symptom);
        std::vector<string> getSymptoms();

        void addRepairMethod(string repairMethod);
        std::vector<string> getRepairMethods();

        void addComponent(int component);
        std::vector<int> getComponents();

        void setDescription(string inDescription);
        string getDescription();

        bool isFixed();
        void fix();

        void countPrice();
        int getPrice();

        void display();

        MalfunctionType();
        virtual ~MalfunctionType();

    protected:

    private:
        int typeId;
        bool fixed;
        int modelId;
        string description;
        vector<string> symptoms;
        vector<string> repairMethods;
        vector<int> components;
        int price;
};

#endif // MALFUNCTIONTYPE_H
