#include "TodoEntry.h"
using namespace std;

TodoEntry::TodoEntry(string content, bool isPlain) {
    this->content = content;
}
TodoEntry::TodoEntry(string encoded) {
    content = TodoEntry::decode(encoded);
}
string TodoEntry::encode() {
    //encoding/encrypting algorithm here
    return this->content;
}
string TodoEntry::decode(string encoded) {
    //decoding/decrypting algorithm here
    return encoded;
}
