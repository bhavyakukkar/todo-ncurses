#ifndef VIEW_H
#define VIEW_H

#include <curses.h>
#include "TodoList.h"

using namespace std;

class View {
public:
    View();
    void drawFrame();
    void updateList(TodoList*);
    void updateBar(int);
    int getLook();
    void changeLook(int);
    char getc();
    void close();
private:
    int look, listLastLine, height, width, size;
    WINDOW* screen;
    string modes[6] = {"view", "add: ", "modify to: ", "remove? ", "emphasize by: ", "deemphasize by: "};
};

#endif 
