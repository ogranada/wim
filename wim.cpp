
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

Wim::Wim() {
    
}

void Wim::loadFile(std::string filePath) {
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
}

Wim::Wim(std::string str) {
    std::istringstream f(str);
    std::string s;
    while (getline(f, s, '\n')) {
        Chunk chunk = {s};
        this->buffer.push_back(chunk);
    }
}

Wim::~Wim() {
    
}

bool Wim::insertText(int line, int col, std::string str) {
    int cline = 0;
    for(Chunk &chunk: this->buffer) {
        if(cline == line) {
            chunk.insert(col, str);
        }
        cline++;
    }
    return false;
}

std::ostream& operator<< (std::ostream& stream, const Wim wim) {
    bool first = true;
    for(auto const& chunk: wim.buffer) {
        if(!first) {
            stream << "\n";
        } else {
            first = false;
        }
        stream << chunk.line;
    }
    return stream;
}
