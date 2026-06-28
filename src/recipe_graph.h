

#ifndef COP3530_PROJECT2_RECIPE_GRAPH_H
#define COP3530_PROJECT2_RECIPE_GRAPH_H

#include <string>
#include <vector>

using namespace std;

class recipeGraph {

    //  Recipe houses wanted data from the CSV file
    struct Recipe {
        string title;
        vector<string> ingredients;
        vector<string> nerIngredients;
        vector<string> directions;
        string link;

    };

    /*  searchResult houses the data outputted by DFS and BFS search algorithms along with data from the
     *  performance of the search algorithm used
     */
    struct searchResult {
        vector<Recipe> recipes;
        size_t nodesVisited;
        double timeElapsed;
        string algorithmUsed;
    };

    struct ingredientNode {
        string name;
        vector<size_t> neighbors;
    };

    struct recipeNode {
        size_t recipeIndex;
        vector<size_t> neighbors;
    };



    /*  The bipartite graph with:
     *  One container of recipe structs with all the data a recipe holds
     *  One container of recipe nodes containing indices for the recipes vector and indices of related ingredients
     *  One container of ingredient nodes containing an ingredient name and indices of related recipes
     */
    vector<Recipe> recipes;
    vector<recipeNode> recipeNodes;
    vector<ingredientNode> ingredientNodes;

    /*  bfs() and dfs() run their respective algorithms return a struct searchResult that contains recipes found,
     *  nodes visited, how long the search took, and which algorithm was performed
     *
     *  The algorithms themselves are found in recipe_BFS and recipe_DFS
     */
    searchResult bfs(const string& ingredient) const;
    searchResult dfs(const string& ingredient) const;

    //  This section of helper functions assist in parsing the CSV file
    string filterQuotes(const string& str);
    string filterAttribute(const string& str);
    vector<string> parseCSV(const string& line);
    vector<string> parseList(const string& list);

    //  Reads the CSV file
    bool loadCSV(const string& filename);

public:
    recipeGraph();
    void printRecipe(const Recipe& recipe) const;
    const vector<Recipe>& getRecipes() const;
};


#endif //COP3530_PROJECT2_RECIPE_GRAPH_H