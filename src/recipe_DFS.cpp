

#include "recipe_DFS.h"
#include "recipe_graph.h"
#include <chrono>

recipeDFS::recipeDFS(const recipeGraph &graph): graph(graph), visitedIngredients(graph.getIngredientNodes().size(), false), visitedRecipes(graph.getRecipes().size(), false) {
}

void recipeDFS::dfsIngredient(size_t ingredientIndex, const string& targetIngredient) {
    nodesVisited++;
    if (visitedIngredients[ingredientIndex]) {
        return;
    }

    visitedIngredients[ingredientIndex] = true;

    const auto& ingredientNodes = graph.getIngredientNodes();
    const auto& ingredient = ingredientNodes[ingredientIndex];

    if (ingredient.name == targetIngredient) {
        for (size_t recipeIndex : ingredient.neighbors) {
            nodesVisited++;
            if (!visitedRecipes[recipeIndex]) {
                visitedRecipes[recipeIndex] = true;
                foundRecipes.push_back(recipeIndex);
                dfsRecipe(recipeIndex, targetIngredient);
            }
        }
    } else {
        for (size_t recipeIndex : ingredient.neighbors) {
            nodesVisited++;
            if (!visitedRecipes[recipeIndex]) {
                dfsRecipe(recipeIndex, targetIngredient);
            }
        }
    }
}

void recipeDFS::dfsRecipe(size_t recipeIndex, const string& targetIngredient) {
    nodesVisited++;
    if (visitedRecipes[recipeIndex]) {
        return;
    }

    visitedRecipes[recipeIndex] = true;

    const auto& recipeNodes = graph.getRecipeNodes();
    const auto& recipe = recipeNodes[recipeIndex];

    for (size_t ingredientIndex : recipe.neighbors) {
        dfsIngredient(ingredientIndex, targetIngredient);
    }
}

vector<size_t> recipeDFS::search(const string &ingredient) {
    auto start = chrono::steady_clock::now();

    int ingredientIndex = graph.findIngredientIndex(ingredient);
    if (ingredientIndex != -1) {
        dfsIngredient(ingredientIndex, ingredient);
    }

    auto end = chrono::steady_clock::now();

    timeElapsed = chrono::duration<double>(end - start).count();

    return foundRecipes;
}

vector<size_t> recipeDFS::searchMultiple(const vector<string> &ingredients) {
    auto start = chrono::steady_clock::now();

    vector<size_t> potentialMatches = search(ingredients[0]);
    foundRecipes.clear();

    const auto& ingredientNodes = graph.getIngredientNodes();
    const auto& recipeNodes = graph.getRecipeNodes();

    for (size_t recipeIndex : potentialMatches) {
        bool matchAllIngredients = true;
        const auto& recipeNode = recipeNodes[recipeIndex];

        for (const string& ingredient : ingredients) {
            bool found = false;

            for (size_t ingredientInd : recipeNode.neighbors) {
                if (ingredientNodes[ingredientInd].name == ingredient) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                matchAllIngredients = false;
                break;
            }
        }
        if (matchAllIngredients) {
            foundRecipes.push_back(recipeIndex);
        }
    }
    auto end = chrono::steady_clock::now();
    timeElapsed = chrono::duration<double>(end - start).count();

    return foundRecipes;
}

size_t recipeDFS::getNodesVisited() const {
    return nodesVisited;
}

double recipeDFS::getTimeElapsed() const {
    return timeElapsed;
}
