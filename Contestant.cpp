#include "Contestant.h"

Contestant::Contestant(string name, string type) {
    this->name = name;
    this->type = type;
    vaccineCount = 0;
    status = false;
}

string Contestant::GetName() {
    return name;
}

bool Contestant::GetStatus() {
    return status;
}

string Contestant::GetType() {
    return type;
}

int Contestant::GetVaccineCount() {
    return vaccineCount;
}

void Contestant::Contestant::SetName(string name) {
    this->name = name;
}

void Contestant::Contestant::SetStatus(bool status) {
    this->status = status;
}

void Contestant::SetType(string type) {
    this->type = type;
}

void Contestant::SetVaccineCount(int vaccineCount) {
    this->vaccineCount = vaccineCount;
}

void Contestant::Reset() {
    status = false;
    type = "angel";
    vaccineCount = 0;
}

ContactResult Contestant::Contact(Contestant player) {
    string resultType = type;
    int resultCount = vaccineCount;
    if(type == "sinner" && player.GetType() == "angel") {
        if(player.GetVaccineCount() > 0) {
            resultType = "angel";
        }
    }
    else if(type == "angel" && (player.GetType() == "sinner" || player.GetType() == "demon")) {
        if(vaccineCount >= 2) {
            resultCount = vaccineCount - 2; //New vaccince count
            resultType = "angel";
        }
        else {
            resultCount = 0;
            resultType = "sinner";
        }
    }
    else if(type == "angel" && player.GetType() == "angel") {
        resultCount = vaccineCount + 1;
    }

    ContactResult result(resultType, resultCount);

    contactedList.push_back(player.GetName());

    return result;
}

void Contestant::SetContactResult(ContactResult result) {
    type = result.GetType();
    vaccineCount = result.GetCount();
}

bool Contestant::CheckContact(Contestant player) {
    bool result = false;
    for(int i = 0; i < contactedList.size(); ++i) {
        if(player.GetName() == contactedList.at(i)) {
            result = true;
        }
    }
    return result;
}
string Contestant::ToString() {
    string stringStatus = "true";
    if (status == false) {
        stringStatus = "false";
    }
    ostringstream oSS;
    oSS << left << setw(20) << name << setw(10) << type << setw(10) << vaccineCount << setw(10) << stringStatus << endl;
    return oSS.str();
}