#pragma once
#include <iostream>
#include <string>
using namespace std;
class Exeptions
{
    protected:
        std::string text;
    public:
        Exeptions(std::string text) { this->text = text; }
        virtual string showMessage()const = 0;
};

class loadFileExeption : public Exeptions {
    string file;
public:
    loadFileExeption(std::string text, string file) : Exeptions(text), file(file) {}
    std::string showMessage() const override {
        return text + " File: " + file;
    }
};
class saveFileExeption : public Exeptions {
    string file;
public:
    saveFileExeption(std::string text, string file) : Exeptions(text), file(file) {}
    std::string showMessage() const override {
        return text + " File: " + file;
    }
};