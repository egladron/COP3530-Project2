#include "dataset.h"
#include "recipe_graph.h"
#include <iostream>
#include <sstream>

int main() {
    cout << "+==============================================================+" << endl;
    cout << "|                                                              |" << endl;
    cout << "|                    Downloading dataset...                    |" << endl;
    cout << "|                                                              |" << endl;
    cout << "+==============================================================+" << endl;

    datasetDownloader dataset;
    if (dataset.checkAvailability()) {
        cout << "+==============================================================+" << endl;
        cout << "|                                                              |" << endl;
        cout << "|                    Download successful!                      |" << endl;
        cout << "|                                                              |" << endl;
        cout << "+==============================================================+" << endl;
    } else {
        cout << "Error: Cannot download dataset" << endl;
        return 0;
    }

    cout << "|                                                              |" << endl;
    recipeGraph graph;
    cout << "|                                                              |" << endl;

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
    cout << endl;
    int input = 0;
    cout << "Select an option: >";
    while (input > 3 || input < 1) {
        cin >> input;
        cin.ignore();

        if (input == 1 || input == 2) {
            cout << endl;
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
            cout << "Select an option: >";
            int searchInput = 0;
            while (searchInput > 3 || searchInput < 1) {
                cin >> searchInput;
                cin.ignore();
                if (searchInput == 1 && input == 1) {
                    string ingredient;
                    cout << "Please enter an ingredient to search for a recipe: >";
                    cin >> ingredient;
                    cin.ignore();
                    cout << endl;
                    graph.searchDfs(ingredient);
                    graph.printResults();

                } else if (searchInput == 1 && input == 2) {
                    vector<string> ingredients;
                    string line;
                    cout << "Please enter ingredients separated by a space: >";
                    getline(cin, line);
                    cout << endl;
                    stringstream ss(line);
                    string ingredient;
                    while (ss >> ingredient) {
                        ingredients.push_back(ingredient);
                    }
                    graph.searchDfs(ingredients);
                    graph.printResults();

                } else if (searchInput == 2 && input == 1) {
                    string ingredient;
                    cout << "Please enter an ingredient to search for a recipe: >";
                    cin >> ingredient;
                    cin.ignore();
                    cout << endl;
                    graph.searchBfs(ingredient);
                    graph.printResults();

                } else if (searchInput == 2 && input == 2) {
                    vector<string> ingredients;
                    string line;
                    cout << "Please enter ingredients separated by a space: >";
                    getline(cin, line);
                    cout << endl;
                    stringstream ss(line);
                    string ingredient;
                    while (ss >> ingredient) {
                        ingredients.push_back(ingredient);
                    }
                    graph.searchBfs(ingredients);
                    graph.printResults();

                } else if (searchInput == 3) {
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
                    cout << endl;
                    input = 0;
                    cout << "Select an option: >";
                    break;
                } else {
                    cout << endl;
                    cout << "Error, invalid option selected, please choose a valid option from the menu" << endl;
                }
            }
        } else if (input == 3) {
            cout << endl;
            cout << "+==============================================================+" << endl;
            cout << "|                                                              |" << endl;
            cout << "|                     Exiting Program...                       |" << endl;
            cout << "|                                                              |" << endl;
            cout << "+==============================================================+" << endl;
        } else {
            cout << endl;
            cout << "Error, invalid option selected, please choose a valid option from the menu" << endl;
        }
    }

    return 0;
}