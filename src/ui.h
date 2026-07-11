
#ifndef COP3530_PROJECT2_UI_H
#define COP3530_PROJECT2_UI_H

#include <string>

using namespace std;

//  This class handles large repeated sections of the menu ui to reduce clutter in main()
class ui {
public:
    void downloading();
    void downloadSuccessful();
    void mainMenu();
    void searchMenu();
    void exit();

    //  A helper function to make inputs case-insensitive
    string toLower(const string& str);
};


#endif //COP3530_PROJECT2_UI_H