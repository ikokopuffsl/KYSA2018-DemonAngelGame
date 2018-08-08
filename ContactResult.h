#pragma once
#include <string>

using namespace std;

class ContactResult {
    public:
    ContactResult(string type, int count);

    string GetType();
    int GetCount();

    private:
    string contactResultType;
    int contactResultVaccineCount;
};