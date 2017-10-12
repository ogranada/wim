
#include <iostream>
#include "wim.hpp"

int main(int argc, char *argv[]) {
    // Wim wim;
    // wim.loadFile("./_demo.txt");
    Wim wim("Hello\nWorld\nCruel\nSample");
    wim.insertText(1, 5, " Simple");
    std::cout << wim << std::endl;
    wim.save("/tmp/demo.txt");
    return 0;
}
