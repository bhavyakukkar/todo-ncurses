#include "Util.h"

int Util::moveBy(int cur, int by, int max) {
    return ((cur - by) < 0) ? 0 : (((cur - by) > max) ? max : (cur - by) );
}
