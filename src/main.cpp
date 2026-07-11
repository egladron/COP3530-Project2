#include "dataset.h"
#include "recipe_graph.h"
#include "ui.h"
#include <iostream>
#include <sstream>

int main() {
    ui uiObj;
    uiObj.downloading();

    datasetDownloader dataset;

    if (dataset.checkAvailability()) {
        uiObj.downloadSuccessful();
    } else {
        cout << "Error: Cannot download dataset" << endl;
        return 0;
    }

    cout << "|                                                              |" << endl;
    recipeGraph graph;
    cout << "|                                                              |" << endl;
    uiObj.mainMenu();
    cout << endl;
    int input = 0;
    cout << "Select an option: >";
    while (input > 3 || input < 1) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error, invalid option selected, please choose a valid option from the menu" << endl;
            continue;
        }
        cin.ignore();

        if (input == 1 || input == 2) {
            cout << endl;
            uiObj.searchMenu();
            cout << endl;
            cout << "Select an option: >";
            int searchInput = 0;
            while (searchInput > 3 || searchInput < 1) {
                cin >> searchInput;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error, invalid option selected, please choose a valid option from the menu" << endl;
                    continue;
                }
                cin.ignore();
                if (searchInput == 1 && input == 1) {
                    string ingredient;
                    cout << "Please enter an ingredient to search for a recipe: >";
                    getline(cin, ingredient);
                    cout << endl;
                    graph.searchDfs(uiObj.toLower(ingredient));
                    graph.printResults();
                    uiObj.mainMenu();
                    cout << endl;
                    input = 0;
                    cout << "Select an option: >";
                    break;

                } else if (searchInput == 1 && input == 2) {
                    vector<string> ingredients;
                    string line;
                    cout << "Please enter ingredients separated by a comma: >";
                    getline(cin, line);
                    cout << endl;
                    stringstream ss(line);
                    string ingredient;
                    while (ingredients.size() < 2) {
                        while (getline(ss, ingredient, ',')) {
                            size_t start = ingredient.find_first_not_of(" \t\n\r");
                            size_t end = ingredient.find_last_not_of(" \t\n\r");

                            if (start != string::npos && end != string::npos) {
                                ingredient = ingredient.substr(start, end - start + 1);
                            }

                            if (!ingredient.empty()) {
                                ingredients.push_back(uiObj.toLower(ingredient));
                            }
                        }
                        if (ingredients.size() < 2) {
                            cout << "Error, please enter more than one ingredient: >" << endl;
                            getline(cin, line);
                            ss = stringstream(line);
                            ingredients.clear();
                        }
                    }
                    graph.searchDfs(ingredients);
                    graph.printResults();
                    uiObj.mainMenu();
                    cout << endl;
                    input = 0;
                    cout << "Select an option: >";
                    break;

                } else if (searchInput == 2 && input == 1) {
                    string ingredient;
                    cout << "Please enter an ingredient to search for a recipe: >";
                    getline(cin, ingredient);
                    cout << endl;
                    graph.searchBfs(uiObj.toLower(ingredient));
                    graph.printResults();
                    uiObj.mainMenu();
                    cout << endl;
                    input = 0;
                    cout << "Select an option: >";
                    break;

                } else if (searchInput == 2 && input == 2) {
                    vector<string> ingredients;
                    string line;
                    cout << "Please enter ingredients separated by a comma: >";
                    getline(cin, line);
                    cout << endl;
                    stringstream ss(line);
                    string ingredient;
                    while (ingredients.size() < 2) {
                        while (getline(ss, ingredient, ',')) {
                            size_t start = ingredient.find_first_not_of(" \t\n\r");
                            size_t end = ingredient.find_last_not_of(" \t\n\r");

                            if (start != string::npos && end != string::npos) {
                                ingredient = ingredient.substr(start, end - start + 1);
                            }

                            if (!ingredient.empty()) {
                                ingredients.push_back(uiObj.toLower(ingredient));
                            }
                        }
                        if (ingredients.size() < 2) {
                            cout << "Error, please enter more than one ingredient: >" << endl;
                            getline(cin, line);
                            ss = stringstream(line);
                            ingredients.clear();
                        }
                    }
                    graph.searchBfs(ingredients);
                    graph.printResults();
                    uiObj.mainMenu();
                    cout << endl;
                    input = 0;
                    cout << "Select an option: >";
                    break;

                } else if (searchInput == 3) {
                    uiObj.mainMenu();
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
            uiObj.exit();
        } else {
            cout << endl;
            cout << "Error, invalid option selected, please choose a valid option from the menu" << endl;
        }
    }

    return 0;
}