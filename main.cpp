#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
//Need file includes

#include "Contestant.h"
#include "ContactResult.h"
using namespace std;

//Unfortunate Global Variable
 stringstream Log;
 int round = 0;
 ofstream writeFile;
 ifstream readFile;
/********************************* UTILITY **********************************
 *                                                                          *
 *                                                                          *
 * *************************************************************************/
int DuplicateNameChecker(string name, vector<Contestant> &listOfParticipants) {
    for(int i = 0; i < listOfParticipants.size(); ++i) {
        if (name == listOfParticipants.at(i).GetName()) {
            return i;
        }
    }
    return -1;
}    
string AddInputValidator(string input, string option, vector<Contestant> &listOfParticipants) {
    if (option == "name") {
        while(DuplicateNameChecker(input, listOfParticipants) >= 0) {
            cout << "Name already exist. Choose a new name" << endl;
            cin >> input;
        }
    }
    else if (option == "type") {
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

    cout << "List of Players" << endl;
    for(int i = 0; i < listOfParticipants.size(); ++i) {
        cout << i << " : " << listOfParticipants.at(i).GetName() << endl;
    }
}
bool IndexValidator(int index, vector<Contestant> &listOfParticipants) {
    bool result = true;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        result = false;
    }
    else if (index < 0 || index >= listOfParticipants.size()) {
        cout << "Invalid Number. Please enter a number between 0 and " << listOfParticipants.size() - 1 << endl;
        result = false;
    }
    return result;
}
void PrintMenu() {
    cout << "*****************************" << endl;
    cout << "* Here are the menu options *" << endl;
    cout << "*****************************" << endl;
    //Set up
    cout << endl;
    cout << "Game Set Up" << endl;
    cout << "===========" << endl;
    cout << "menu - print the menu" << endl;
    cout << "add - Adds a new player" << endl;
    cout << "remove - Remove a player" << endl;
    cout << "restart - Restart the game (Keep current users)" << endl;
    cout << "clearAll - Clears all data" << endl;
    cout << "log - Prints out game summary" << endl;
    cout << "import - Set up game from text file" << endl;

    //Game Play
    cout << endl;
    cout << "Game Play" << endl;
    cout << "=========" << endl;
    cout << "print - Print everyone's status" << endl;
    cout << "contact - Two players connect" << endl;
    cout << "check - Player checks their status(one per round)" << endl;
    cout << "next - Goes to next round. Reset check status" << endl;

    //Other
    cout << endl;
    cout << "Other Options" << endl;
    cout << "=============" << endl;
    cout << "setType - Manually set type(demon, sinner, angel)" << endl;
    cout << "setVaccine - Manually set vaccince count" << endl;
    cout << "quit - Exits the game" << endl;
    cout << endl;

}
/********************************* SET UP ***********************************
 *                                                                          *
 *                                                                          *
 * *************************************************************************/                                         

void AddPlayer(vector<Contestant> &listOfParticipants) {
    string type = "";
    string name = "";

    cout << "Enter name (One Word)" << endl;
    cin >> name;
    name = AddInputValidator(name, "name", listOfParticipants);
    cout << "Enter type (demon, sinner, angel)" << endl;
    cin >> type;
    type = AddInputValidator(type, "type", listOfParticipants);

    listOfParticipants.push_back(Contestant(name, type));

    cout << name << " successfully added" << endl;
    Log << "Player Added: " << name << " " << type << endl << endl;
}
void RemovePlayer(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;
    
    int index = -1; 

    PrintNames(listOfParticipants);

    cout << "Who would you like to remove? Please enter the ID of player (0 - " << listOfParticipants.size() - 1 << ")" << endl;
    cin >> index;

    if(!IndexValidator(index, listOfParticipants)) return;
    
    cout << listOfParticipants.at(index).GetName() << " successfully removed" << endl;
    Log << "Player Removed: " << listOfParticipants.at(index).GetName() << endl << endl;
    listOfParticipants.erase(listOfParticipants.begin() + index);

}
void Restart(vector<Contestant> &listOfParticipants) {
    round = 0;
    for(int i = 0; i < listOfParticipants.size(); ++i) {
        listOfParticipants.at(i).Reset();
    }
    cout << "Reset Successful" << endl;
    Log.str("");
    Log << "Game Restart (Current players stats all reset)" << endl << endl;
    Log << "Game Started" << endl << endl;
    Log << "************************************" << endl;
    Log << "* Round - " << ++round << "                        *" << endl;
    Log << "************************************" << endl << endl;
}
void ClearAll(vector<Contestant> &listOfParticipants) {
    round = 0;
    listOfParticipants.clear();
    Log.str("");
    cout << "Clear All Successful" << endl;
    Log << "Everything removed (Players and Stats)" << endl << endl;
    Log << "Game Started" << endl << endl;
    Log << "************************************" << endl;
    Log << "* Round - " << ++round << "                        *" << endl;
    Log << "************************************" << endl << endl;
}
void ExportToText(vector<Contestant> &listOfParticipants) {
    //cout << "Export To Text Successful. Please check your folder for ExportText.txt" << endl;
    //Log << "Game Data Exported" << endl;
    stringstream temp;
    vector<string> contactedList;

    // writeFile.open("ExportText.txt", ios::app);
    writeFile.open("ExportText.txt");
    for(int i = 0; i < listOfParticipants.size(); ++i) {
        writeFile << setw(2) << i << setw(2) << ": " << listOfParticipants.at(i).ToString();

        contactedList = listOfParticipants.at(i).GetContactedList();
        for(int j = 0; j < contactedList.size(); ++j) {
            writeFile << " " << contactedList.at(j);
        }
        writeFile << " done-1" << endl;
    }
    writeFile.close();
    //cout << "Finish export" << endl;
}
void ImportFromText(vector<Contestant> &listOfParticipants) {
    cout << "Imported data successfully!" << endl;
    Log << "Game Data Imported" << endl;

    string statusString = "";
    bool status = false;
    string name = "";
    string type = "";
    int vaccineCount = 0;
    vector<string>contactedList;
    string contacted = "";


    readFile.open("ExportText.txt");
    while(!readFile.eof()) {
        contactedList.clear();
        readFile >> contacted;
        readFile >> name;
        readFile >> type;
        readFile >> vaccineCount;
        readFile >> statusString;
        (statusString == "false") ? status = false : status = true;
        while(contacted != "done-1") {
            readFile >> contacted;
            contactedList.push_back(contacted);
        }
        Contestant mContestant(name, type);
        mContestant.SetVaccineCount(vaccineCount);
        mContestant.SetStatus(status);
        mContestant.SetContactedList(contactedList);
        listOfParticipants.push_back(mContestant);
    }
    readFile.close();
}
void LogHelper() {
    //Not needed
}
void LogActivity() {
    //cout << "Log Activity Successful. Please check your folder for LogActivity.txt" << endl;
    cout << Log.str();
}

/********************************* Game Play ********************************
 *                                                                          *
 *                                                                          *
 * *************************************************************************/   
void PrintEveryoneStatus(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;
    
    cout << left << setw(4) << "ID" << setw(20) << "Name: " << setw(10) << "Type" << setw(10) << "Vaccine" << setw(10) << "Checked" << endl;
    cout << left << setw(4) << "==" << setw(20) << "======" << setw(10) << "====" << setw(10) << "=======" << setw(10) << "=======" << endl;
    for(int i = 0; i < listOfParticipants.size(); ++i) {
        cout << setw(2) << i << setw(2) << ":" << listOfParticipants.at(i).ToString();
    }
}

void Contact(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;

    PrintNames(listOfParticipants);

    int indexA = -1;
    int indexB = -1;

    cout << "Enter the ID of 2 players (Example: 1 3)" << endl;
    cin >> indexA >> indexB;

    if(!IndexValidator(indexA, listOfParticipants) || !IndexValidator(indexB, listOfParticipants)) return;
    
    if(listOfParticipants.at(indexA).CheckContact(listOfParticipants.at(indexB))) {
        cout << "Already contacted, cannot contact until new game" << endl;
        return;
    }

    string statusA = listOfParticipants.at(indexA).GetType();
    string statusB = listOfParticipants.at(indexB).GetType();
    int vaccineCountA = listOfParticipants.at(indexA).GetVaccineCount();
    int vaccineCountB = listOfParticipants.at(indexB).GetVaccineCount();

    ContactResult playerAResult = listOfParticipants.at(indexA).Contact(listOfParticipants.at(indexB));
    ContactResult playerBResult = listOfParticipants.at(indexB).Contact(listOfParticipants.at(indexA));
        
    listOfParticipants.at(indexA).SetContactResult(playerAResult);
    listOfParticipants.at(indexB).SetContactResult(playerBResult);

    cout << listOfParticipants.at(indexA).GetName() << " and " << listOfParticipants.at(indexB).GetName() << " have made contact" << endl;
    Log << "Contact: " << listOfParticipants.at(indexA).GetName() << "(" << statusA << " - " << vaccineCountA << ") and "
        << listOfParticipants.at(indexB).GetName() << "(" << statusB << " - " << vaccineCountB << ") have made contact" << endl;
    Log << "Contact Result: " << listOfParticipants.at(indexA).GetName() << " is a(n) " << listOfParticipants.at(indexA).GetType() << endl;
    Log << "Contact Result: " << listOfParticipants.at(indexB).GetName() << " is a(n) " << listOfParticipants.at(indexB).GetType() << endl;
    Log << endl;

}

void CheckStatus(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;

    int index = -1;

    PrintNames(listOfParticipants);
    
    cout << "Enter the ID of player who wants to check their status" << endl;
    cin >> index;

    if(!IndexValidator(index, listOfParticipants)) return;

    if (listOfParticipants.at(index).GetStatus()) {
        cout << listOfParticipants.at(index).GetName() << " has already checked their status this round. Please wait until the next round" << endl;
    }
    else {
        listOfParticipants.at(index).SetStatus(true);
        cout << left << setw(20) << "Name: " << setw(10) << "Type" << setw(10) << "Vaccine" << endl;
        cout << left << setw(20) << "======" << setw(10) << "====" << setw(10) << "=======" << endl;
        cout << left << setw(20) << listOfParticipants.at(index).GetName() << setw(10) << listOfParticipants.at(index).GetType() << setw(10) << listOfParticipants.at(index).GetVaccineCount();
        Log << "CheckStatus: " << listOfParticipants.at(index).GetName() << " checked their status. " << endl << endl;
    }
}

void NextRound(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;
    
    cout << "Starting Next Round" << endl;
    for (int i = 0; i < listOfParticipants.size(); ++i) {
        listOfParticipants.at(i).SetStatus(false);
    }
    cout << "All players status have been reset" << endl;
    Log << "************************************" << endl;
    Log << "NextRound: Round - " << ++round << "               *" << endl;
    Log << "************************************" << endl << endl;
}

/********************************* Other ************************************
 *                                                                          *
 *                                                                          *
 * *************************************************************************/   

void SetType(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;

    int index = -1;
    string status = "";

    PrintNames(listOfParticipants);

    cout << "Please enter ID of player" << endl;    
    cin >> index;
    cout << "Please enter type (demon, sinner, angel)" << endl;
    cin >> status;
    status = AddInputValidator(status, "status", listOfParticipants);

    if(!IndexValidator(index, listOfParticipants)) return;

    cout << listOfParticipants.at(index).GetName() << " successfully set from " << listOfParticipants.at(index).GetType()
        << " to " << status << endl;
    listOfParticipants.at(index).SetType(status);
    Log << "SetType: " << listOfParticipants.at(index).GetName() << " successfully set from " << listOfParticipants.at(index).GetType()
        << " to " << status << endl << endl;
}

void SetVaccineCount(vector<Contestant> &listOfParticipants) {
    if(InvalidSize(listOfParticipants)) return;

    int index = -1;
    int vaccineCount = -1;

    PrintNames(listOfParticipants);

    cout << "Please enter ID of player" << endl;    
    cin >> index;
    cout << "Enter new vaccine count" << endl;
    cin >> vaccineCount;

    if(!IndexValidator(index, listOfParticipants)) return;

    cout << listOfParticipants.at(index).GetName() << " successfully set from " << listOfParticipants.at(index).GetVaccineCount()
        << " to " << vaccineCount << endl;
    listOfParticipants.at(index).SetVaccineCount(vaccineCount);
    Log << "SetVaccineCount: " << listOfParticipants.at(index).GetName() << " successfully set from " << listOfParticipants.at(index).GetVaccineCount()
        << " to " << vaccineCount << endl << endl;
}

int main() {
    vector<Contestant> listOfParticipants;
    string userOption = "";
   


    cout << "\t\t\t\t\t********************************************" << endl;
    cout << "\t\t\t\t\t* Welcome to the Demon and Angel Simulator *" << endl;
    cout << "\t\t\t\t\t********************************************" << endl;
    Log << endl;
    Log << "Game Started" << endl << endl;
    Log << "************************************" << endl;
    Log << "* Round - " << ++round << "                        *" << endl;
    Log << "************************************" << endl << endl;
    do {
        cout << endl;
        cout << endl << endl << endl << endl << endl << endl;
        PrintMenu();
        cout << "**************************" << endl;
        cout << "* Please enter an option *" << endl;
        cout << "**************************" << endl;
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
        else if(userOption == "log") {
            LogActivity();
        }
        else if(userOption == "import") {
            cout << "Not working yet" << endl;
            //ImportFromText(listOfParticipants);
        }     
        else if(userOption == "print") {
            PrintEveryoneStatus(listOfParticipants);
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
        }
        ExportToText(listOfParticipants);

    } while (userOption != "quit");

    cout << "Thanks for playing! Goodbye!" << endl;

    system("pause");

    return 0;
}