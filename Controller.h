#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "TodoList.h"
#include "View.h"

using namespace std;

class Controller {
public:
    struct options {
        bool lookFactors;
        bool emphasisFactors;
    };
    Controller(View*, TodoList*, struct options*);
    int start();
private:
    int mode;
    bool running;
    struct options* options;
    View* view;
    TodoList* todoList;
    string strBuffer;
    int intBuffer;
    void makeView();
    void route(int, char);
    void showInput();
    void hideInput();
};

#endif
