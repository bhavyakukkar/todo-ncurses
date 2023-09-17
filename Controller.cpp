#include <fstream>
#include "Controller.h"

using namespace std;


Controller::Controller(View* view, TodoList* todoList, struct Controller::options* options) {
    todoList->readFromFile();
    this->options = options;
    mode = 0;
    this->view = view;
    this->todoList = todoList;
}
void Controller::makeView() {
    this->view->drawFrame();
    this->view->updateList(this->todoList);
    this->view->updateBar(this->mode);
}
int Controller::start() {
    char ch;
    try {
        this->running = true;
        this->makeView();
        while(this->running) {
            ch = this->view->getc();
            this->route(this->mode, ch);
            this->view->updateList(this->todoList);
            this->view->updateBar(this->mode);
        }
    }
    catch(...) {
        return 1;
    }
    this->todoList->writeToFile();
    this->view->close();
    return 0;
}
void Controller::route(int mode, char key) {
    switch(mode) {
        case 0:
            switch(key) {
                case 'k':
                    if(this->options->lookFactors) {
                        this->intBuffer = 0;
                        showInput();
                    }
                    else
                        this->view->changeLook(1);
                    break;
                case 'j':
                    if(this->options->lookFactors) {
                        this->intBuffer = 0;
                        showInput();
                    }
                    else
                        this->view->changeLook(-1);
                    break;
                case 'a':
                    this->strBuffer = "";
                    showInput();
                    this->mode = 1;
                    break;
                case 'm':
                    this->strBuffer = "";
                    showInput();
                    this->mode = 2;
                    break;
                case 'r':
                    this->mode = 3;
                    break;
                case 'e':
                    if(this->options->emphasisFactors) {
                        this->intBuffer = 0;
                        showInput();
                        this->mode = 4;
                    }
                    else {
                        this->todoList->emphasizeEntry(this->view->getLook(), 1);
                        this->view->changeLook(1);
                    }
                    break;
                case 'd':
                    if(this->options->emphasisFactors) {
                        this->intBuffer = 0;
                        showInput();
                        this->mode = 5;
                    }
                    else {
                        this->todoList->emphasizeEntry(this->view->getLook(), -1);
                        this->view->changeLook(-1);
                    }
                    break;
                case 'q':
                    this->running = false;
                    break;
            }
            break;
        case 1:
            switch(key) {
                case '\n': {
                    this->todoList->addEntry(new TodoEntry(this->strBuffer, true));
                    this->strBuffer = "";
                    hideInput();
                    this->mode = 0;
                    break;
                }
                default:
                    this->strBuffer = this->strBuffer + key;
            }
            break;
        case 2:
            switch(key) {
                case '\n': {
                    TodoEntry todo = TodoEntry(this->strBuffer);
                    this->todoList->modifyEntry(this->view->getLook(), &todo);
                    this->strBuffer = "";
                    hideInput();
                    this->mode = 0;
                    break;
                }
                default:
                    this->strBuffer = this->strBuffer + key;
            }
            break;
        case 3:
            switch(key) {
                case '\n':
                    this->todoList->removeEntry(this->view->getLook());
                    this->view->changeLook(1);
                    this->mode = 0;
            }
            break;
        case 4:
            if(key >= '0' && key <= '9')
                this->intBuffer = this->intBuffer*10 + (int)key;
            if(key == '\n') {
                this->todoList->emphasizeEntry(this->view->getLook(), this->intBuffer);
                this->view->changeLook(this->intBuffer);
                this->intBuffer = 0;
                hideInput();
                this->mode = 0;
            }
            break;
        case 5:
            if(key >= '0' && key <= '9')
                this->intBuffer = this->intBuffer*10 + (int)key;
            if(key == '\n') {
                this->todoList->emphasizeEntry(this->view->getLook(), (-1)*this->intBuffer);
                this->view->changeLook(this->intBuffer);
                this->intBuffer = 0;
                hideInput();
                this->mode = 0;
            }
            break;
    }
}
void Controller::showInput() {
    curs_set(1);
    echo();
    nocbreak();
}
void Controller::hideInput() {
    curs_set(0);
    noecho();
    cbreak();
}
