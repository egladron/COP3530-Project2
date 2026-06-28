

#include "recipe_graph.h"
#include <algorithm>
#include <fstream>
#include <iostream>
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
    while (getline(file, line)) {
        vector<string> attributes = parseCSV(line);

        if (attributes.size() < 6) {
            continue;
        }

        Recipe recipe;
        recipe.title = filterQuotes(attributes[0]);
        recipe.ingredients = parseList(attributes[1]);
        recipe.directions = parseList(attributes[2]);
        recipe.link = filterQuotes(attributes[3]);
        recipe.nerIngredients = parseList(attributes[5]);

        if (recipeLookup.find(recipe.title) != recipeLookup.end()) {
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
        recipes.push_back(move(recipe));
        recipeNodes.push_back(move(newRecipeNode));
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

void recipeGraph::printRecipe(const Recipe& recipe) const {
    cout << recipe.title << ":" << endl;
    for (auto& ingr : recipe.ingredients) {
        cout << ingr << " ";
    }
    cout << endl;
    for (auto& dir : recipe.directions) {
        cout << dir << " ";
    }
    cout << endl;
    cout << recipe.link << endl;
    for (auto& ingr : recipe.nerIngredients) {
        cout << ingr << " ";
    }
    cout << endl;
}