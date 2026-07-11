#include "recipe_BFS.h"
#include "recipe_graph.h"
#include <chrono>

recipeBFS::recipeBFS(const recipeGraph& graph)
    : graph(graph),
    visitedIngredients(graph.getIngredientNodes().size(), false),
    visitedRecipes(graph.getRecipes().size(), false) {
}

vector<size_t> recipeBFS::search(const string& ingredient) {
    auto start = chrono::steady_clock::now();

    foundRecipes.clear();
    nodesVisited = 0;

    int ingredientIndex = graph.findIngredientIndex(ingredient);

    if (ingredientIndex != -1) {
        queue<size_t> recipeQueue;

        const auto& ingredientNodes = graph.getIngredientNodes();

        nodesVisited++;
        visitedIngredients[ingredientIndex] = true;

        for (size_t recipeIndex : ingredientNodes[ingredientIndex].neighbors) {
            recipeQueue.push(recipeIndex);
        }

        while (!recipeQueue.empty()) {
            size_t currentRecipe = recipeQueue.front();
            recipeQueue.pop();

            nodesVisited++;

            if (!visitedRecipes[currentRecipe]) {
                visitedRecipes[currentRecipe] = true;
                foundRecipes.push_back(currentRecipe);
            }
        }
    }

    auto end = chrono::steady_clock::now();
    timeElapsed = chrono::duration<double>(end - start).count();

    return foundRecipes;
}

vector<size_t> recipeBFS::searchMultiple(const vector<string>& ingredients) {
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

size_t recipeBFS::getNodesVisited() const {
    return nodesVisited;
}

double recipeBFS::getTimeElapsed() const {
    return timeElapsed;
}