

#ifndef COP3530_PROJECT2_RECIPE_DFS_H
#define COP3530_PROJECT2_RECIPE_DFS_H

#include <vector>
#include <string>

using namespace std;

class recipeGraph;

class recipeDFS {
    //  Houses the graph
    const recipeGraph& graph;

    //  Variables used for benchmarking
    size_t nodesVisited = 0;
    double timeElapsed = 0.0f;

    //  Booleans to keep track of traversed nodes
    vector<bool> visitedIngredients;
    vector<bool> visitedRecipes;

    //  A vector of recipe indices that are matches for the search
    vector<size_t> foundRecipes;

    //  The two recursive functions that perform the dfs
    void dfsIngredient(size_t ingredientIndex, const string& targetIngredient);
    void dfsRecipe(size_t recipeIndex, const string& targetIngredient);
public:
    //  A constructor that loads the graph and sets vectors empty at initialization
    recipeDFS(const recipeGraph& graph);

    //  A search function for a single ingredient and outputs recipe indicies
    vector<size_t> search(const string& ingredient);

    /* A search function for multiple ingredients, requires a vector of
     * ingredient name strings and outputs recipe indices
     */
    vector<size_t> searchMultiple(const vector<string>& ingredients);

    //  Getter functions for the benchmark variables
    size_t getNodesVisited() const;
    double getTimeElapsed() const;

};


#endif //COP3530_PROJECT2_RECIPE_DFS_H