
#include "wim.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>



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
        this->filePath = &filePath;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void WimContent::save(std::string newFilePath) {
    std::string targetFilePath;
    if(newFilePath.compare("") != 0) {
        targetFilePath = newFilePath;
    } else {
        if(this->filePath == NULL) {
            NotSpecifiedPathException ex;
            throw ex;
        } else {
            targetFilePath = *(this->filePath);
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
    for(auto const& chunk: wim.getBuffer()) {
        if(!first) {
            stream << "\n";
        } else {
            first = false;
        }
        stream << chunk.line;
    }
    return stream;
}


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

WimContent WimCursor::getContent() {
    return content;
}

void WimCursor::setContent(WimContent contentInstance) {
    content = contentInstance;
}

bool WimCursor::insertText(std::string newtext) {
    try {
        std::cout << ":::" << *content.getLine(row) << std::endl;
        content.getLine(row)->insert(column, newtext);
        std::cout << ":::" << *content.getLine(row) << std::endl;
        return true;
    } catch(std::exception  &e) {
        return false;
    }
}

