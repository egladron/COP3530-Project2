<H1> What's For Dinner</h1>
A C++ app that helps you search for recipes based on the ingredients you have available to you. Our app searches through
over 2 million recipes to find ones that match the ingredient or ingredients you input into the program. Our 
app can search using both Depth-First Search and Breadth-First Search and shows performance metrics for the respective 
search used.

<h2> Table of Contents </h2>

- [Instructions](#instructions)
  - [Main Menu](#main-menu)
  - [Search Menu](#search-menu)
  - [Search Prompt](#search-prompt)
  - [Search Result](#search-result)
- [Dataset](#dataset)

# Instructions

The first time the program is run, it will download and extract the dataset into the same folder the program is run from.
Each time the program is run, it will first have to construct and populate the bipartite graph from the dataset. The
load bar at the start shows the progress of the graph being built and populated.

## Main Menu:

The main menu will appear showing three options:
- (1) Search by single ingredient
- (2) Search by multiple ingredients
- (3) Exit the program

The user selects an option by pressing its corresponding number and pressing enter to confirm their choice. The 
program will not accept invalid inputs and will continue to ask for an input until a valid one is sent.

The first two options lead to the search menu. The third option closes the program.

## Search Menu:

The search menu has these three options:
- (1) Depth-First Search
- (2) Breadth-First Search
- (3) Return to Main Menu

Similar to the main menu, this menu only accepts an input of integers 1-3. Option 3 returns to the main menu. Options 1
and 2 both continue to the search prompt.

## Search Prompt:

Based on the user's choice in the first menu, they must either enter one ingredient or multiple ingredients separated by
a comma. The input is case-insensitive and will prune whitespace. The program will search the graph for any recipes that
contain the ingredient(s) entered. It will then display these benchmarks for the search:

- The number of recipes found
- The number of nodes traversed while searching
- The amount of time it took to complete the search
- The algorithm used in the search

## Search Result:
With a successful search the program will output:

- The list of ingredients
- The instructions for making the recipe
- A URL link to the recipe from the website it was taken from

Each search only outputs one recipe. If the search resulted in more than one recipe, it will prompt the user if they
would like to view another recipe. The user can select **<big>y</big>** for yes and **<big>n</big>** for no. The user can continue to select
to view another recipe match as long as there are still matches available. If the user selects no or there are no more 
recipe matches, it will return to the main menu.

# Dataset
The dataset was obtained from:

https://www.kaggle.com/datasets/wilmerarltstrmberg/recipe-dataset-over-2m