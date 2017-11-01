#include "wim.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define print(x) std::cout << x << std::endl

// #pragma region Chunk

Chunk::Chunk(){
}

Chunk::Chunk(std::string str){
    this->line = str;
}

Chunk::Chunk(const Chunk &chnk){
    this->line = chnk.line;
}

std::ostream& operator<< (std::ostream& stream, const Chunk chnk) {
    stream << chnk.line;
    return stream;
}

Chunk* Chunk::insert(int column, std::string newstr) {
    this->line.insert(column, newstr.c_str());
    return this;
}


// #pragma endregion


// #pragma region WimContent
WimContent::WimContent() {
    
}

void WimContent::loadFile(std::string filePath) {
    try {
        std::ifstream sourceFile;
        std::string str;
        sourceFile.open(filePath);
        int c = 0;
        while(!sourceFile.eof()) {
            getline(sourceFile, str);
            Chunk chunk = {str};
            this->buffer.push_back(chunk);
            c++;
        }
        sourceFile.close();
        this->filePath = filePath;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void WimContent::save(std::string newFilePath) {
    std::string targetFilePath;
    if(newFilePath.compare("") != 0) {
        targetFilePath = newFilePath;
    } else {
        if(this->filePath.empty()) {
            NotSpecifiedPathException ex;
            throw ex;
        } else {
            targetFilePath = this->filePath;
        }
    }
    std::ofstream file;
    file.open(targetFilePath);
    bool first = true;
    for(auto const& chunk: this->getBuffer()) {
        if(!first) {
            file << "\n";
        } else {
            first = false;
        }
        file << chunk.line;
    }
    file.close();
}

WimContent::WimContent(std::string str) {
    std::istringstream f(str);
    std::string s;
    while (getline(f, s, '\n')) {
        Chunk chunk = {s};
        this->buffer.push_back(chunk);
    }
}

WimContent::~WimContent() {
    
}


/*
bool WimContent::insertText(unsigned long line, unsigned long col, std::string str) {
    int cline = 0;
    for(Chunk &chunk: this->buffer) {
        if(cline == line) {
            chunk.insert(col, str);
        }
        cline++;
    }
    return false;
}
*/

std::vector<Chunk> WimContent::getBuffer() const {
    return buffer;
}

Chunk * WimContent::getLine(unsigned long line) {
    return &buffer[line];
}

std::ostream& operator<< (std::ostream& stream, const WimContent wim) {
    bool first = true;
    #if __DEBUG__
    int c = 0;
    #endif
    for(auto const& chunk: wim.getBuffer()) {
        if(!first) {
            stream << "\n";
        } else {
            first = false;
        }
        #if __DEBUG__
        stream << c++ << " " << chunk.line;
        #else
        stream << chunk.line;
        #endif
    }
    return stream;
}

// #pragma endregion


// #pragma region WimCursor

WimCursor::WimCursor(){
    row = 0;
    column = 0;
}

WimCursor::WimCursor(unsigned long rowNumber, unsigned long columnNumber) {
    row = rowNumber;
    column = columnNumber;
}

WimCursor::~WimCursor() {}

unsigned long WimCursor::getRow() {
    return row;
}

void WimCursor::setRow(unsigned long rowNumber) {
    row = rowNumber;
}

unsigned long WimCursor::getColumn(){
    return column;
}

void WimCursor::setColumn(unsigned long columnNumber){
    column = columnNumber;
}

WimContent *WimCursor::getContent() {
    return content;
}

WimCursor::WimCursor(WimContent *contentInstance) {
    content = contentInstance;
}

void WimCursor::setContent(WimContent *contentInstance) {
    content = contentInstance;
}

void split(std::vector<std::string> &vect, std::string text, const char *separator) {
    std::string token = "";
    for(char c: text) {
        if(c != '\n') {
            token += c;
        } else {
            vect.push_back(token);
            token = "";
        }
    }
}

unsigned int WimContent::getLinesCount() {
    return buffer.size();
}

bool WimCursor::insertText(std::string newtext) {
    print(row);
    print(newtext);
    try {
        std::size_t found = newtext.find_first_of("\n");
        if (found == std::string::npos) { // Not have new line instances.
            if((*content).getLinesCount() >= row){
                (*content).getLine(row)->insert(column, newtext);
            } else {
                // TODO: fix insertin in not existent lines.
            }
        } else {
            std::vector<std::string> lines;
            split(lines, newtext, "\n");
            (*content).getLine(row)->insert(column, lines[0]);
            for(int i = 1; i < lines.size(); i++) {
                (*content).insertLine(row+i, lines[i]);
            }
        }
        return true;
    } catch(std::exception  &e) {
        return false;
    }
}

void WimContent::insertLine(unsigned long row, Chunk chnk) {
    std::vector<Chunk>::iterator it = buffer.begin();
    if(row < buffer.size()){
        it += row;
        buffer.insert(it, chnk);
    }
}


// #pragma endregion
