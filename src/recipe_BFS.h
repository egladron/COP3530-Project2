
#ifndef COP3530_PROJECT2_RECIPE_BFS_H
#define COP3530_PROJECT2_RECIPE_BFS_H

#include <vector>
#include <string>
#include <queue>

using namespace std;
class recipeGraph;

class recipeBFS {
	const recipeGraph& graph;

	size_t nodesVisited = 0;
	double timeElapsed = 0.0f;

	vector<bool> visitedIngredients;
	vector<bool> visitedRecipes;

	vector<size_t> foundRecipes;

public:

	recipeBFS(const recipeGraph& graph);
	vector<size_t> search(const string& ingredient);
	vector<size_t> searchMultiple(const vector<string>& ingredients);

	size_t getNodesVisited() const;
	double getTimeElapsed() const;
};


#endif //COP3530_PROJECT2_RECIPE_BFS_H