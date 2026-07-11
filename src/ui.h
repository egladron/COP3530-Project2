
#ifndef COP3530_PROJECT2_UI_H
#define COP3530_PROJECT2_UI_H

#include <string>

using namespace std;

class ui {
public:
    void downloading();
    void downloadSuccessful();
    void mainMenu();
    void searchMenu();
    void exit();
    string toLower(const string& str);
};


#endif //COP3530_PROJECT2_UI_H