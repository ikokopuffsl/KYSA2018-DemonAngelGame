#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
//Need file includes

#include "Contestant.h"
#include "ContactResult.h"
using namespace std;

/********************************* UTILITY **********************************
 *                                                                          *
 *                                                                          *
 * *************************************************************************/
int DuplicateChecker(string name, vector<Contestant> &listOfParticipants) {
    for(int i = 0; i < listOfParticipants.size(); ++i) {
        if (name == listOfParticipants.at(i).GetName()) {
            return i;
        }
    }
    return -1;
}    
string InputValidator(string input, string option, vector<Contestant> &listOfParticipants) {
    if (option == "name") {
        while(DuplicateChecker(input, listOfParticipants) >= 0) {
            cout << "Name already exist. Choose a new name" << endl;
            cin >> input;
        }
    }
    else if (option == "status") {
        while(input != "demon" && input != "sinner" && input != "angel") {
            cout << "Invalid Option. Choose demon, sinner, or angel" << endl;
            cin >> input;
        }
    }
    return input;
} 

bool InvalidSize(vector<Contestant> &listOfParticipants) {
    if (listOfParticipants.empty()) {
        cout << "There are no contestants. Please use the add option" << endl;
        return true;
    }
    return false;
}

void PrintNames(vector<Contestant> &listOfParticipants) {
    for(int i = 0; i < listOfParticipants.size(); ++i) {
        cout << "i: " << listOfParticipants.at(i).GetName() << endl;
    }
}
void PrintMenu() {
    cout << "Here are the menu options" << endl;

    //Set up
    cout << endl;
    cout << "\t\t\tGame Set Up" << endl;
    cout << "menu - print the menu" << endl;
    cout << "add - Adds a new player" << endl;
    cout << "remove - Remove a player" << endl;
    cout << "restart - Restart the game (Keep current users)" << endl;
    cout << "clearAll - Clears all data" << endl;
    cout << "export - Export data to text file" << endl;
    cout << "log - Logs all appropriate user input" << endl;

    //Game Play
    cout << endl;
    cout << "\t\t\tGame Play" << endl;
    cout << "print - Print everyone's status" << endl;
    cout << "printInd - Print individual's status" << endl; //Possibly not needed
    cout << "contact - Two players connect" << endl;
    cout << "check - Player checks their status(one per round)" << endl;
    cout << "next - Goes to next round. Reset check status" << endl;

    //Other
    cout << endl;
    cout << "\t\t\tOther Options" << endl;
    cout << "setType - Manually set type(demon, sinner, angel)" << endl;
    cout << "setVaccine - Manually set vaccince count" << endl;

}
/********************************* SET UP ***********************************
 *                                                                          *
 *                                                                          *
 * *************************************************************************/                                         

void AddPlayer(vector<Contestant> &listOfParticipants) {
    string status = "";
    string name = "";

    cout << "Enter name" << endl;
    cin >> name;
    name = InputValidator(name, "name", listOfParticipants);
    cout << "Enter status (demon, sinner, angel)" << endl;
    cin >> status;
    status = InputValidator(status, "type", listOfParticipants);

    listOfParticipants.push_back(Contestant(name, status));

    cout << name << " successfully added" << endl;
}
void RemovePlayer(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;
    
    string name = ""; 

    PrintNames(listOfParticipants);

    cout << "Who would you like to remove?" << endl;
    cin >> name;

    int index = DuplicateChecker(name, listOfParticipants);

    if (index >= 0) {
        listOfParticipants.erase(listOfParticipants.begin() + index);
        cout << name << " successfully removed" << endl;
    }
    else {
        cout << name << " does not exist" << endl;
    }
}
void Restart(vector<Contestant> &listOfParticipants) {
    for(int i = 0; i < listOfParticipants.size(); ++i) {
        listOfParticipants.at(i).Reset();
    }
    cout << "Reset Successful" << endl;
}
void ClearAll(vector<Contestant> &listOfParticipants) {
    listOfParticipants.clear();
    cout << "Clear All Successful" << endl;
}
void ExportToText(vector<Contestant> &listOfParticipants) {


    cout << "Export To Text Successful. Please check your folder for ExportText.txt" << endl;
}
void LogHelper() {

}
void LogActivity() {

    cout << "Log Activity Successful. Please check your folder for LogActivity.txt" << endl;
}

/********************************* Game Play ********************************
 *                                                                          *
 *                                                                          *
 * *************************************************************************/   
void PrintEveryoneStatus(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;
    
    cout << left << setw(20) << "Name: " << setw(10) << "Type" << setw(10) << "Vaccine" << setw(10) << "Checked" << endl;
    cout << left << setw(20) << "======" << setw(10) << "====" << setw(10) << "=======" << setw(10) << "=======" << endl;
    for(int i = 0; i < listOfParticipants.size(); ++i) {
        cout << listOfParticipants.at(i).ToString();
    }
}

void PrintIndividualStatus(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;
    string name;

    cout << "Enter name of player you wish to check" << endl;
    cin >> name;

    int playerIndex = DuplicateChecker(name, listOfParticipants);

    if (playerIndex < 0) {
        cout << name << " does not exist. Or there are no contestants." << endl;
    }
    else {
        cout << left << setw(20) << "Name: " << setw(10) << "Type" << setw(10) << "Vaccine" << setw(10) << "Checked" << endl;
        cout << left << setw(20) << "======" << setw(10) << "====" << setw(10) << "=======" << setw(10) << "=======" << endl;
        cout << listOfParticipants.at(playerIndex).ToString();
    }
}

void Contact(vector<Contestant> &listOfParticipants) {
    string playerA = "";
    string playerB = "";

    cout << "Enter name of player first player" << endl;
    cin >> playerA;
    cout << "Enter name of second player" << endl;
    cin >> playerB;

    int indexA = DuplicateChecker(playerA, listOfParticipants);
    int indexB = DuplicateChecker(playerB, listOfParticipants);

    if (indexA >= 0 && indexB >= 0) { 
        ContactResult playerAResult = listOfParticipants.at(indexA).Contact(listOfParticipants.at(indexB));
        ContactResult playerBResult = listOfParticipants.at(indexB).Contact(listOfParticipants.at(indexA));
        
        listOfParticipants.at(indexA).SetContactResult(playerAResult);
        listOfParticipants.at(indexB).SetContactResult(playerBResult);
    }
    else {
        cout << playerA << " or " << playerB << " does not exist." << endl;
    }
}

void CheckStatus(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;

    string name = "";
    
    cout << "Enter name of player who wants to check their status" << endl;
    cin >> name;

    int playerIndex = DuplicateChecker(name, listOfParticipants);

    if (playerIndex >= 0) {
        if (listOfParticipants.at(playerIndex).GetStatus()) {
            cout << name << " has already checked their status this round. Please wait until the next round" << endl;
        }
        else {
            listOfParticipants.at(playerIndex).SetStatus(true);
            cout << left << setw(20) << "Name: " << setw(10) << "Type" << setw(10) << "Vaccine" << endl;
            cout << left << setw(20) << "======" << setw(10) << "====" << setw(10) << "=======" << endl;
            cout << left << setw(20) << name << setw(10) << listOfParticipants.at(playerIndex).GetType() << setw(10) << listOfParticipants.at(playerIndex).GetVaccineCount();
        }
    }
    else {
        cout << name << " does not exist." << endl;
    }

}

void NextRound(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;

    cout << "Starting Next Round" << endl;
    for (int i = 0; i < listOfParticipants.size(); ++i) {
        listOfParticipants.at(i).SetStatus(false);
    }
    cout << "All players status have been reset" << endl;
}

/********************************* Other ************************************
 *                                                                          *
 *                                                                          *
 * *************************************************************************/   

void SetType(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;

    string name = "";
    string status = "";

    cout << "What player's type would you like to set?" << endl;    
    cin >> name;
    cout << "Enter status (demon, sinner, angel)" << endl;
    cin >> status;
    status = InputValidator(status, "status", listOfParticipants);

    int playerIndex = DuplicateChecker(name, listOfParticipants);

    if (playerIndex >= 0) {
        cout << name << " successfully set from " << listOfParticipants.at(playerIndex).GetType()
            << " to " << status << endl;
        listOfParticipants.at(playerIndex).SetType(status);
    }
    else {
        cout << name << " does not exist." << endl;
    }
}

void SetVaccineCount(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;

    string name = "";
    int vaccineCount = -1;

    cout << "What player's vaccine count would you like to set?" << endl;    
    cin >> name;
    cout << "Enter new vaccine count" << endl;
    cin >> vaccineCount;

    int playerIndex = DuplicateChecker(name, listOfParticipants);

    if (playerIndex >= 0) {
        cout << name << " successfully set from " << listOfParticipants.at(playerIndex).GetVaccineCount()
            << " to " << vaccineCount << endl;
        listOfParticipants.at(playerIndex).SetVaccineCount(vaccineCount);
    }
    else {
        cout << name << " does not exist." << endl;
    }
}

int main() {
    vector<Contestant> listOfParticipants;
    string userOption = "";

    cout << "******************************" << endl;
    cout << "*";
    PrintMenu();

    do {
        cout << endl;
        cout << "Please enter an option" << endl << endl;
        cin >> userOption;
        cin.ignore(1000, '\n'); //If there is excess input I want to ignore all of it

        if(userOption == "menu") {
            PrintMenu();
        }
        else if(userOption == "add") {
            AddPlayer(listOfParticipants);
        }
        else if(userOption == "remove") {
            RemovePlayer(listOfParticipants);
        }
        else if(userOption == "restart") {
            Restart(listOfParticipants);
        }
        else if(userOption == "clearAll") {
            ClearAll(listOfParticipants);
        }
        else if(userOption == "export") {
            ExportToText(listOfParticipants);
        }
        else if(userOption == "log") {
            LogActivity();
        }
        else if(userOption == "print") {
            PrintEveryoneStatus(listOfParticipants);
        }
        else if(userOption == "printInd") {
            PrintIndividualStatus(listOfParticipants);
        }
        else if(userOption == "contact") {
            Contact(listOfParticipants);
        }
        else if(userOption == "check") {
            CheckStatus(listOfParticipants);
        }
        else if(userOption == "next") {
            NextRound(listOfParticipants);
        }
        else if(userOption == "setType") {
            SetType(listOfParticipants);
        }
        else if(userOption == "setVaccine") {
            SetVaccineCount(listOfParticipants);
        }
        else if(userOption == "quit") {
            cout << "Are you sure you want to quit? (yes or no)" << endl;
            cin >> userOption;
            if (userOption == "yes") {
                userOption = "quit";
            }
        }
        else {
            cout << "Invalid Input. Here is the menu." << endl;
            PrintMenu();
        }

    } while (userOption != "quit");

    cout << "Thanks for playing! Goodbye!" << endl;

    system("pause");

    return 0;
}