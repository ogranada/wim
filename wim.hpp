#ifndef __WIM_INCLUDED__
#define __WIM_INCLUDED__

#include <iostream>
#include <vector>

class NotSpecifiedPathException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Not specified path for file.";
  }
};


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

class WimContent {

    private:
        std::string *filePath = NULL;
        std::vector<Chunk> buffer;

        // PRIVATE METHODS
        friend std::ostream& operator<< (std::ostream& stream, const WimContent wim);

    public:
        WimContent();
        WimContent(std::string);
        ~WimContent();

        // PUBLIC METHODS
        std::vector<Chunk> getBuffer() const;
        Chunk * getLine(unsigned long);
        // bool insertText(unsigned long line, unsigned long col, std::string newstr);
        void loadFile(std::string filePath);
        void save(std::string newFilePath = "");

};

class WimCursor {
private:
    unsigned long row;
    unsigned long column;
    WimContent content;
public:
    WimCursor();
    WimCursor(WimContent);
    WimCursor(unsigned long, unsigned long);
    ~WimCursor();
    unsigned long getRow();
    void setRow(unsigned long);
    unsigned long getColumn();
    void setColumn(unsigned long);
    WimContent getContent();
    void setContent(WimContent);
    bool insertText(std::string newtext);
};

#endif