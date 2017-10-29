
#include <iostream>
#include "wim.hpp"

int main(int argc, char *argv[]) {
    // Wim wim;
    // wim.loadFile("./_demo.txt");
    WimContent wim("Hello\nWorld\nCruel\nSample");
    // wim.insertText(1, 5, " Simple"); // TODO: deprecate...
    int ROW = 0;
    int COL = 5;
    WimCursor wc1(ROW, COL);
    wc1.setContent(&wim);
    wc1.insertText(" Test\nNew Line\nOther Line\n\n\n");

    WimCursor wc2;
    wc2.setRow(1);
    wc2.setColumn(5);

    WimCursor wc3(10, 10);
    wc3.setContent(&wim);
    wc3.insertText("Final Line");
    std::cout << "----------------------" << std::endl;

    std::cout << wim << std::endl;
    wim.save("/tmp/demo.txt");
    return 0;
}
