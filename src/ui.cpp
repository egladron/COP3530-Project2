

#include "ui.h"

#include <iostream>

string ui::toLower(const string &str) {
    string result = str;
    for (char& c : result) {
        c = tolower(static_cast<unsigned char>(c));
    }
    return result;
}

void ui::downloading() {
    cout << "+==============================================================+" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                    Downloading dataset...                    |" << endl;
    cout << "|                                                              |" << endl;
    cout << "+==============================================================+" << endl;
}

void ui::downloadSuccessful() {
    cout << "+==============================================================+" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                    Download successful!                      |" << endl;
    cout << "|                                                              |" << endl;
    cout << "+==============================================================+" << endl;
}

void ui::mainMenu() {
    cout << "+==============================================================+" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                     What's For Dinner                        |" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                                                              |" << endl;
    cout << "+==============================================================+" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                                                              |" << endl;
    cout << "|  (1) Search by Single Ingredient                             |" << endl;
    cout << "|  (2) Search by Multiple Ingredients                          |" << endl;
    cout << "|  (3) Exit                                                    |" << endl;
    cout << "|                                                              |" << endl;
    cout << "+==============================================================+" << endl;
}

void ui::searchMenu() {
    cout << "+==============================================================+" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                    Choose an algorithm:                      |" << endl;
    cout << "|                                                              |" << endl;
    cout << "+==============================================================+" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                                                              |" << endl;
    cout << "|  (1) Depth-First Search                                      |" << endl;
    cout << "|  (2) Breadth-First Search                                    |" << endl;
    cout << "|  (3) Return to Main Menu                                     |" << endl;
    cout << "|                                                              |" << endl;
    cout << "+==============================================================+" << endl;
}

void ui::exit() {
    cout << "+==============================================================+" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                     Exiting Program...                       |" << endl;
    cout << "|                                                              |" << endl;
    cout << "+==============================================================+" << endl;
}
