#include "View.h"
#include "Util.h"

using namespace std;

View::View() {
    look = 0;
    listLastLine = 1;
    screen = initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(this->screen, 1);
    start_color();
    use_default_colors();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    height = getmaxy(screen);
    width = getmaxx(screen);
}
void View::drawFrame() {
    int i;

    for(i = 0; i < this->height-2; i++) {
        mvaddch(1+i, 0, '┃');
        mvaddch(1+i, this->width-1, '┃');
    }
    for(i = 0; i < this->width-2; i++) {
        mvaddch(0, 1+i, '━');
        mvaddch(this->height-3, 1+i, '━');
        mvaddch(this->height-1, 1+i, '━');
    }
    mvaddch(0, 0, '┏'); mvaddch(0, this->width-1, '┓');
    mvaddch(this->height-3, 0, '┣'); mvaddch(this->height-3, this->width-1, '┫');
    mvaddch(this->height-1, 0, '┗'); try { mvaddch(this->height-1, this->width-1, '┛'); } catch(int x) {} //writing to last char (bottom right) throws error after writing
}
void View::updateList(TodoList* todoList) {
    int line = 1, entry, pen, ch, y, x;
    string content;
    bool color;
    this->size = todoList->listSize;
    for(entry = 0; entry < this->size; entry++) {
        content = todoList->getEntry(entry);
        color = (entry != this->look) ? 0 : A_REVERSE;
        //mvaddstr(line, 2, " > ", color | A_BOLD);
        mvaddstr(line, 2, " > ");
        pen = 5;
        for(ch = 0; ch < content.length(); ch++) {
            if(pen > this->width-3) {
                line++;
                //mvaddstr(line, 2, "   ", color);
                mvaddstr(line, 2, "   ");
                pen = 5;
            }
            //mvaddch(line, pen, content[ch], color);
            mvaddch(line, pen, content[ch]);
            pen++;
        }
        while(pen <= this->width-3) {
            //mvaddch(line, pen, ' ', color);
            mvaddch(line, pen, ' ');
            pen++;
        }
        line++;
    }
    if(line < this->listLastLine)
        for(y = line; y < this->listLastLine; y++)
            for(x = 2; x < this->width-2; x++)
                mvaddch(y, x, ' ');
    this->listLastLine = line;
    refresh();
}
void View::updateBar(int mode) {
    int x;
    for(x = 2; x < this->width-2; x++)
        mvaddch(this->height-2, x, ' ');
    //mvaddstr(this->height-2, 2, View->modes[mode], color_pair(2) | A_BOLD);
    mvaddstr(this->height-2, 2, this->modes[mode].c_str());
    refresh();
}
void View::close() {
    keypad(this->screen, 0);
    endwin();
}
int View::getLook() {
    return this->look;
}
void View::changeLook(int factor) {
    this->look = Util::moveBy(this->look, factor, this->size-1);
}
char View::getc() {
    return wgetch(this->screen);
}
