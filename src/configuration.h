#include<string>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>

class configuration {

public:

    configuration(char largeur, char hauteur) {

        _data = new char[largeur * hauteur];
        _largeur = largeur;
        _hauteur = hauteur;   
    }
    
    configuration(const configuration &config) {

        _largeur = config._largeur;
        _hauteur = config._hauteur;
        short size = (short)(_largeur * _hauteur);
        _data = new char[size];        
        for(int i = 0; i < _largeur * _hauteur; i++) _data[i] = config._data[i]; /// memcpy        
        _time = config._time;        
    }

    void setLH(char l, char h) {

        _hauteur = h;
        _largeur = l;

        delete[] _data;
        
        _data = new char[h*l];
    }

    void deleteC() {

        delete[] _data;
    }

    char getData(char ligne, char col) {

        int p = (int)(ligne * _largeur + col);

        return _data[p];
    }

    char getData(int pos) {

        return _data[pos];
    }

    char getLargeur() {

        return _largeur;
    }

    char getLigne(int i) {

        return (char)(i / (int)_largeur);
    }

    char getCol(int i) {

        return (char)(i % (int)_largeur);
    }

    int getSize() {

        return _largeur * _hauteur;
    }

    void setData(char* data, char ligne) {

        for(int i = 0; i < _largeur; i++) {

            _data[ligne * _largeur + i] = data[i];
        }
    }

    void setData(char data, int pos) {

        _data[pos] = data;
    }

    void setData(char* data) {

        _data = data;
    }

    void setTime(int time) {

        _time = time;
    }

    clock_t getTime() {

        return _time;
    }

    void printString() {

        std::cout << _hauteur + 0;
        std::cout << " ";
        std::cout << _largeur + 0;
        std::cout << std::endl;

        for(char j = 0; j < _hauteur; j++) {

            std::string tmpS = "";
            
            for(char i = 0; i < _largeur; i++) {

                tmpS += _data[j * _largeur + i];
            }

            std::cout << tmpS << std::endl;
        }

        printf("%li", (long int)(_time));

        std::cout << std::endl;
    }

    std::string getString() {

        std::string val = std::to_string(_largeur) + " " + std::to_string(_hauteur);

        val += '\n';

        for(int j =0; j < _hauteur; j++) {

            for(int i = 0; i < _largeur; i++) {

                val += _data[j*_largeur + i];
            }

            val += '\n';
        }

        val += std::to_string(_time);

        val += "\n";

        return val;
    }

private:

    char _largeur;
    char _hauteur;
    clock_t _time;
    char* _data;
};