#include "Controller.h"

using namespace std;

int main() {
    TodoList todoList = TodoList("./data");
    View view = View();
    struct Controller::options options = {false, false};

    Controller c = Controller(&view, &todoList, &options);
    return c.start();
}
