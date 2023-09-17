//[1] when TodoEntry gains more attributes, move following fn to Controller

#include <fstream>
#include "TodoList.h"

using namespace std;

TodoList::TodoList(string location) {
    this->location = location;
    listSize = 0;
    listHead = NULL;
    listTail = NULL;
}
void TodoList::readFromFile() {
    //todo
    TodoEntry* todo = new TodoEntry("buy pink thigh-highs"), *todo2 = new TodoEntry("touch grass");
    this->addEntry(todo);
    this->addEntry(todo2);
}
void TodoList::writeToFile() {
    /*string binOut = this->encode();
    fstream fs;
    fs.open(location, ios::binary | ios::out);
    if(fs.is_open() == 0) {
        throw invalid_argument("file couldn't be opened");
    }
    else {
        fs.write((char*) &binOut, sizeof(binOut));
    }
    fs.close();
    this->freeList();*/
}
string TodoList::getEntry(int entryId) {
    struct TodoList::TodoNode *listTemp = this->getNodeAt(entryId);
    if(listTemp != NULL)
        return listTemp->todo->content;
    return "";
}
void TodoList::addEntry(TodoEntry* todo) {
    this->listSize += 1;
    if(this->listHead == NULL) {
        this->listHead = (struct TodoList::TodoNode*)malloc(sizeof(struct TodoList::TodoNode));
        this->listTail = this->listHead;
        this->listTail->prev = NULL;
    }
    else {
        this->listTail->next = (struct TodoList::TodoNode*)malloc(sizeof(struct TodoList::TodoNode));
        this->listTail->next->prev = this->listTail;
        this->listTail = this->listTail->next;
    }
    this->listTail->todo = todo;
    this->listTail->next = NULL;
}
//[1]
void TodoList::addEntry(string content) {
    TodoEntry* todo = new TodoEntry(content);
    this->addEntry(todo);
}
void TodoList::modifyEntry(int entryId, TodoEntry* newTodo) {
    TodoEntry* oldTodo;
    struct TodoList::TodoNode *listTemp = this->getNodeAt(entryId);
    if(listTemp != NULL) {
        oldTodo = listTemp->todo;
        listTemp->todo = newTodo;
        delete oldTodo;
    }
}
//[1]
void TodoList::modifyEntry(int entryId, string newContent) {
    struct TodoList::TodoNode *listTemp = this->getNodeAt(entryId);
    if(listTemp != NULL) {
        listTemp->todo->content = newContent;
    }
}
void TodoList::removeEntry(int entryId) {
    struct TodoList::TodoNode *listTemp = this->getNodeAt(entryId);
    if(listTemp != NULL) {
        delete listTemp->todo;
        if(listTemp->prev != NULL)
            listTemp->prev->next = listTemp->next;
        if(listTemp->next != NULL)
            listTemp->next->prev = listTemp->prev;
        free(listTemp);
    }
}
void TodoList::emphasizeEntry(int entryId, int factor) {
    struct TodoList::TodoNode *listStart, *listEnd, *listTemp;
    TodoEntry *tempTodo;
    if(factor == 0)
        return;
    listStart = this->getNodeAt(entryId);
    if(listStart == NULL)
        return;
    listEnd = this->getNodeAt(entryId - factor);
    if(listEnd == NULL)
        return;
    tempTodo = listStart->todo;
    if(factor < 0) {
        listTemp = listStart;
        listStart = listEnd;
        listEnd = listTemp;
    }
    while(listStart != listEnd) {
        listStart->todo = listStart->next->todo;
        listStart = listStart->next;
    }
    listEnd->todo = tempTodo;
}
string TodoList::encode() {
    int i;
    string encoded = "";
    struct TodoList::TodoNode *listTemp = this->listHead;
    if(listTemp == NULL)
        return "";
    while(listTemp != NULL) {
        encoded += (listTemp->todo->encode() + ";");
        listTemp = listTemp->next;
    }
    return encoded;
}
void TodoList::decode(string encoded) {
    int i, lastTodoStart = 0;
    for(i = 0; i < encoded.length(); i++) {
        if(encoded[i] == ';') {
            this->addEntry(new TodoEntry(encoded.substr(lastTodoStart, (i-lastTodoStart))));
            lastTodoStart = i + 1;
        }
    }
}
struct TodoList::TodoNode* TodoList::getNodeAt(int id) {
    int i;
    struct TodoList::TodoNode *listTemp = this->listHead;
    if(listTemp == NULL || id < 0 || id >= this->listSize)
        return NULL;
    //optimize by deciding whether traverse forward from head or backward from tail
    for(i = 0; i < id; i++)
        listTemp = listTemp->next;
    return listTemp;
}
void TodoList::freeList() {
    //todo
}

