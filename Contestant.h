#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "ContactResult.h"

using namespace std;

class Contestant {
    public:
    Contestant(string name = "none", string type = "none");

    string GetName();
    bool GetStatus();
    string GetType();
    int GetVaccineCount();
    vector<string> GetContactedList();

    void SetName(string name);
    void SetStatus(bool status);
    void SetType(string type);
    void SetVaccineCount(int vaccineCount);
    void SetContactedList(vector<string> contactedList);

    void Reset(); //Resets status = angel, type = angel, vaccineCount = 0;
    ContactResult Contact(Contestant player);
    void SetContactResult(ContactResult result);
    bool CheckContact(Contestant player);
    string ToString();
    

    private:
    string name;
    bool status;
    string type;
    int vaccineCount;
    vector<string> contactedList;
};