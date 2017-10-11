
#include <iostream>
#include "wim.hpp"

int main(int argc, char *argv[]) {
    // Wim wim("Hello\nWorld\nCruel\nSample");
    Wim wim;
    wim.loadFile("./demo.txt");
    // wim.insertText(1, 5, " Simple");
    // std::cout << wim << std::endl;
    return 0;
}
