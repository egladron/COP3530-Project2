

#ifndef COP3530_PROJECT2_RECIPE_GRAPH_H
#define COP3530_PROJECT2_RECIPE_GRAPH_H

#include <string>
#include <vector>

using namespace std;

class recipeDFS;

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

    //  Node structs used for traversal in the algorithms
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
     *  Each are overloaded to support single ingredients or multiple ingredients
     *
     *  The algorithms themselves are found in recipe_BFS and recipe_DFS files
     */
    searchResult bfs(const string& ingredient) const;
    searchResult bfs(const vector<string>& ingredients) const;
    searchResult dfs(const string& ingredient);
    searchResult dfs(const vector<string>& ingredients);

    //  The results of the search will be stored here
    searchResult result{};

    //  This section of helper functions assist in parsing the CSV file
    string filterQuotes(const string& str);
    string filterAttribute(const string& str);
    vector<string> parseCSV(const string& line);
    vector<string> parseList(const string& list);

    //  Reads the CSV file
    bool loadCSV(const string& filename);

    void printLoading(int percent);

public:
    //  Constructor, automatically loads the recipes_data.csv file and populates the graph
    recipeGraph();

    //  A helper function for printing individual recipes (Could be moved to private)
    void printRecipe(const Recipe& recipe) const;

    /*  The main printing function for printing search benchmark and for printing matching recipes out to main
     *  Contains an interactive loop to continue printing recipes one-by-one so long as
     *  there are still matching recipes to print
     *
     *  Requires a search to be performed in order to populate searchResult result and have the function work
     */
    void printResults();

    //  Various getter functions
    const vector<Recipe>& getRecipes() const;
    const vector<ingredientNode>& getIngredientNodes() const;
    const vector<recipeNode>& getRecipeNodes() const;
    int findIngredientIndex(const string& name) const;

    //  The main search functions with overloading depending on the number of ingredients being searched
    void searchBfs(const string& ingredient);
    void searchBfs(const vector<string>& ingredients);
    void searchDfs(const string& ingredient);
    void searchDfs(const vector<string>& ingredients);
};


#endif //COP3530_PROJECT2_RECIPE_GRAPH_H