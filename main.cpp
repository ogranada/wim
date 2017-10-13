
#include <iostream>
#include "wim.hpp"

int main(int argc, char *argv[]) {
    // Wim wim;
    // wim.loadFile("./_demo.txt");
    WimContent wim("Hello\nWorld\nCruel\nSample");
    // wim.insertText(1, 5, " Simple"); // TODO: deprecate...

    WimCursor wc1(0, 5);
    wc1.setContent(wim);
    wc1.insertText(" Test");

    WimCursor wc2;
    wc2.setRow(1);
    wc2.setColumn(5);

    std::cout << wim << std::endl;
    wim.save("/tmp/demo.txt");
    return 0;
}
