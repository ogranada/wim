#ifndef __WIM_INCLUDED__
#define __WIM_INCLUDED__

#include <iostream>
#include <vector>

class Chunk {
    private:
        // PRIVATE METHODS
        friend std::ostream& operator<< (std::ostream& stream, const Chunk chnk);
    public:
        std::string line;
        Chunk();
        Chunk(std::string str);
        Chunk(const Chunk&);
        Chunk* insert(int column, std::string newstr);
};

class Wim {

    private:
        std::vector<Chunk> buffer;

        // PRIVATE METHODS
        friend std::ostream& operator<< (std::ostream& stream, const Wim wim);

    public:
        Wim();
        Wim(std::string);
        ~Wim();

        // PUBLIC METHODS
        bool insertText(int line, int col, std::string newstr);
        void loadFile(std::string filePath);

};

#endif