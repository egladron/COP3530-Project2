

#include "recipe_graph.h"
#include "recipe_DFS.h"
#include "recipe_BFS.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <unordered_map>

string recipeGraph::filterQuotes(const string &str) {
    string result = str;

    if (result.front() == '"') {
        result.erase(0,1);
    }

    if (result.back() == '"') {
        result.erase(result.length() - 1, 1);
    }

    return result;
}

string recipeGraph::filterAttribute(const string &str) {
    if (str.empty()) {
        return str;
    }

    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) {
        return "";
    }

    size_t end = str.find_last_not_of(" \t\n\r");

    return str.substr(start, end - start + 1);
}

vector<string> recipeGraph::parseCSV(const string &line) {
    vector<string> attributes;
    string attr;
    bool quotes = false;

    for (char c : line) {
        if (c == '"') {
            quotes = !quotes;
        } else if (c == ',' && !quotes) {
            attributes.push_back(filterAttribute(attr));
            attr.clear();
        } else {
            attr += c;
        }
    }

    attributes.push_back(filterAttribute(attr));
    return attributes;
}

vector<string> recipeGraph::parseList(const string &list) {
    vector<string> result;

    if (list.length() < 2) {
        return result;
    }

    string items = list.substr(1, list.length() - 2);

    if (items.empty()) {
        return result;
    }

    size_t start = 0;
    for (size_t i = 0; i <= items.length(); i++) {
        if (i == items.length() || items[i] == ',') {
            string item = items.substr(start, i - start);
            result.push_back(filterAttribute(item));
            start = i + 1;
        }
    }
    return result;
}

bool recipeGraph::loadCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    getline(file, line);
    unordered_map<string, size_t> ingredientLookup;
    unordered_map<string, size_t> recipeLookup;
    const int totalLines = 2231150;
    int linesRead = 0;
    int lastPercent = -1;


    while (getline(file, line)) {
        vector<string> attributes = parseCSV(line);


        int percent = (linesRead * 100) / totalLines;
        if (percent != lastPercent) {
            lastPercent = percent;
            printLoading(percent);
        }

        if (attributes.size() < 6) {
            linesRead++;
            continue;
        }

        Recipe recipe;
        recipe.title = filterQuotes(attributes[0]);
        recipe.ingredients = parseList(attributes[1]);
        recipe.directions = parseList(attributes[2]);
        recipe.link = filterQuotes(attributes[3]);
        recipe.nerIngredients = parseList(attributes[5]);

        if (recipeLookup.find(recipe.title) != recipeLookup.end()) {
            linesRead++;
            continue;
        }

        size_t recipeId = recipes.size();
        recipeLookup.emplace(recipe.title, recipeId);

        recipeNode newRecipeNode;
        newRecipeNode.recipeIndex = recipeId;

        for (const string& ingredient : recipe.nerIngredients) {
            size_t ingredientId;
            auto ingredientExists = ingredientLookup.find(ingredient);

            if (ingredientExists == ingredientLookup.end()) {
                ingredientId = ingredientNodes.size();
                ingredientNode newIngredientNode;
                newIngredientNode.name = ingredient;
                ingredientNodes.push_back(newIngredientNode);
                ingredientLookup.emplace(ingredient, ingredientId);
            }   else {
                ingredientId = ingredientExists->second;
            }
            ingredientNodes[ingredientId].neighbors.push_back((recipeId));
            newRecipeNode.neighbors.push_back(ingredientId);
        }
        recipes.push_back(std::move(recipe));
        recipeNodes.push_back(std::move(newRecipeNode));
        linesRead++;
    }
    file.close();
    return true;
}

recipeGraph::recipeGraph() {
    loadCSV("recipes_data.csv");
}

const vector<recipeGraph::Recipe> &recipeGraph::getRecipes() const {
    return recipes;
}

void recipeGraph::printRecipe(const Recipe& recipe) {
    int textSpace = 60;

    cout << "+==============================================================+" << endl;
    uiBox("");
    centerText(recipe.title);
    uiBox("");
    uiBox("Ingredients:");
    for (const auto& i : recipe.ingredients) {
        wrapText(i, "  - ", textSpace);
     }
    uiBox("");
    uiBox("Directions:");
    for (const auto& d : recipe.directions) {
        wrapText(d, "  - ", textSpace);
    }
    uiBox("");
    uiBox("Link:" + recipe.link);
    uiBox("");
    cout << "+==============================================================+" << endl;
}

const vector<recipeGraph::ingredientNode> &recipeGraph::getIngredientNodes() const {
    return ingredientNodes;
}

const vector<recipeGraph::recipeNode> &recipeGraph::getRecipeNodes() const {
    return recipeNodes;
}

int recipeGraph::findIngredientIndex(const string &name) const {
    for (size_t i = 0; i < ingredientNodes.size(); i++) {
        if (ingredientNodes[i].name == name) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

recipeGraph::searchResult recipeGraph::dfs(const string &ingredient) {
    searchResult results;
    recipeDFS dfsSearch(*this);

    vector<size_t> recipeIndices = dfsSearch.search(ingredient);

    for (size_t indices : recipeIndices) {
        results.recipes.push_back(recipes[indices]);
    }

    results.nodesVisited = dfsSearch.getNodesVisited();
    results.timeElapsed = dfsSearch.getTimeElapsed();
    results.algorithmUsed = "DFS";

    return results;
}

recipeGraph::searchResult recipeGraph::dfs(const vector<string> &ingredients) {
    searchResult results;
    recipeDFS dfsSearch(*this);

    vector<size_t> recipeIndices = dfsSearch.searchMultiple(ingredients);

    for (size_t indices : recipeIndices) {
        results.recipes.push_back(recipes[indices]);
    }

    results.nodesVisited = dfsSearch.getNodesVisited();
    results.timeElapsed = dfsSearch.getTimeElapsed();
    results.algorithmUsed = "DFS";

    return results;
}

void recipeGraph::searchDfs(const string &ingredient) {
    result = dfs(ingredient);
}

void recipeGraph::searchDfs(const vector<string> &ingredients) {
    result = dfs(ingredients);
}

void recipeGraph::printResults() {
    cout << "+==============================================================+" << endl;
    uiBox("");

    uiBox("Recipes found: " + to_string(result.recipes.size()));
    uiBox("Nodes visited: " + to_string(result.nodesVisited));
    stringstream ss;
    ss << fixed << setprecision(3) << (result.timeElapsed * 1000) << " ms";
    uiBox("Time elapsed: " + ss.str());
    uiBox("Algorithm used: " + result.algorithmUsed);
    uiBox("");
    cout << "+==============================================================+" << endl;
    uiBox("");
    centerText("Try this recipe:");
    uiBox("");
    cout << "+==============================================================+" << endl;
    uiBox("");

    string input = "";
    random_device rd;
    mt19937 gen(rd());
    vector<Recipe> recipeList = result.recipes;
    while (!recipeList.empty() && input != "n") {
        uniform_int_distribution<int> dist(0, recipeList.size() - 1);
        int randnum = dist(gen);
        printRecipe(recipeList[randnum]);
        recipeList.erase(recipeList.begin() + randnum);
        uiBox("");
        if (!recipeList.empty()) {
            if (recipeList.size() > 1) {
                centerText(to_string(recipeList.size()) + " other recipes remaining");
            } else {
                centerText(to_string(recipeList.size()) + " other recipe remaining");
            }
            uiBox("");
            centerText("Would you like another recipe?");
            centerText("(y) Yes    (n) No");
            cin >> input;
            while (input != "y" && input != "n") {
                cout << "Invalid input. Please input y for another recipe or n to exit." << endl;
                cin >> input;
            }
        } else {
            cout << "No more recipes match" << endl;
        }
    }
}

void recipeGraph::printLoading(int percent) {
    if (percent == 0) {
        cout << "| Loading 2 million recipes... [";
    } else if (percent != 0 && percent != 100 && percent % 25 == 0) {
        cout << percent << "%";
    } else if (percent != 0 && percent != 100 && percent % 5 == 0) {
        cout << "=";
    } else if (percent == 99) {
        cout << "100%] |" << endl;
    }
}

void recipeGraph::uiBox(const string &text) {
    int width = 64;
    string line = "|  " + text;
    int pad = width - line.length() - 1;
    if (pad < 0) {
        pad = 0;
    }
    line += string(pad, ' ') + "|";
    cout << line <<  endl;
}

void recipeGraph::centerText(const string &text) {
    int width = 64;
    int spaces = width - text.length() - 2;
    cout << "|" << string(spaces / 2, ' ') << text << string(spaces - (spaces / 2), ' ') << "|" << endl;
}

void recipeGraph::wrapText(const string &text, const string &prefix, int width) {
    string remaining = text;
    string currentPrefix = prefix;

    while (!remaining.empty()) {
        string line = currentPrefix + remaining;

        if (line.length() <= width) {
            uiBox(line);
            break;
        } else {
            int maxLength = width - currentPrefix.length();
            int lineBreak = maxLength;

            if (lineBreak > 0 && lineBreak < remaining.length()) {
                size_t space = remaining.rfind(' ', lineBreak);
                if (space != string::npos && space > 0) {
                    lineBreak = space;
                }
            }

            string substring = remaining.substr(0, lineBreak);
            uiBox(currentPrefix + substring);

            remaining = remaining.substr(lineBreak);
            if (!remaining.empty() && remaining[0] == ' ') {
                remaining = remaining.substr(1);
            }

            if (currentPrefix == "  - ") {
                currentPrefix = "    ";
            }

        }
    }
}

recipeGraph::searchResult recipeGraph::bfs(const string &ingredient) const {
    searchResult result{};
    return result;
}

recipeGraph::searchResult recipeGraph::bfs(const vector<string> &ingredients) const {
    searchResult result{};
    return result;
}

void recipeGraph::searchBfs(const string &ingredient) {
    return;
}

void recipeGraph::searchBfs(const vector<string> &ingredients) {
    return;
}
