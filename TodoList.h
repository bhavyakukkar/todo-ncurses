#ifndef TODOLIST_H
#define TODOLIST_H

#include "TodoEntry.h"

using namespace std;

class TodoList {
public:
    TodoList(string);
    struct TodoNode {
        TodoEntry* todo;
        struct TodoNode *next, *prev;
    };
    void readFromFile();
    void writeToFile();
    string getEntry(int);
    void addEntry(TodoEntry*);
    void addEntry(string);
    void removeEntry(int);
    void modifyEntry(int, TodoEntry*);
    void modifyEntry(int, string);
    void emphasizeEntry(int, int);
    int listSize;
private:
    string location;
    struct TodoNode *listHead, *listTail;
    struct TodoNode* getNodeAt(int);
    void freeList();
    string encode();
    void decode(string);
};

#endif
