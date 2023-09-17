#ifndef TODOENTRY_H
#define TODOENTRY_H

#include <string>
using namespace std;

class TodoEntry {
public:
    TodoEntry(string);
    TodoEntry(string, bool);
    string content;
    string encode();
private:
    static string decode(string);
};

#endif
