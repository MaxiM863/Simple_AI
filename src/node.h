#include<vector>
#include<cmath>

class node {

public:

    node(node* parent) {

        childs = new std::vector<node*>;
        _parent = parent;
    }

    void deleteN() {

        childs->clear();
        delete childs;
    }

    long getEval(char* debutTreeTop, char largeur, char longueur) {
        
        char* data = buildData(debutTreeTop, largeur, longueur);
        long eval = calculerEval(data, largeur, longueur);
        
        return eval;
    }

    node* getParent() {

        return _parent;
    }

    void addChild(node* child) {

        childs->push_back(child);
    }

    char* getDataMatrix(char* debutTreeTop, char largeur, char longueur) {

        return buildData(debutTreeTop, largeur, longueur);
    }

    std::vector<node*>* getChilds() {

        return childs;
    }

    bool getIfEnded(char* debutTreeTop, char largeur, char longueur) {

        char* data = buildData(debutTreeTop, largeur, longueur);

        return getEnded(data, largeur, longueur);
    }

    void addPlayed(short p, bool d) {

        played = p;
        noire = d;
    }

private:

    char* buildData(char* debutTreeTop, char largeur, char longueur) {

        std::string tmpS(debutTreeTop);
        
        char* data = new char[largeur * longueur];

        for(size_t i = 0; i < tmpS.length(); i++) {

            data[i] = tmpS.at(i);
        }

        getRecursiveChar(this, data);

        return data;
    }

    void getRecursiveChar(node* actual, char* data) {       
        
        if(actual->getParent() != nullptr) {

            char val = 'G';
            if(actual->noire) val = 'N';

            data[actual->played] = val;

            if(actual->getParent()->getParent() != nullptr) {
            
                getRecursiveChar(actual->getParent(), data);
            }
        }
    }

    bool getEnded(char* data, short largeur, short longueur) {

        bool end = true;

        short size = largeur * longueur;

        for(int i = 0; i < size; i++) {

            if(data[i] == '0') {

                end = false;
                break;
            } 
        }

        bool end2 = false;

        long _eval = compterLignes('N', data, largeur, longueur, end2);
        _eval -= compterLignes('G', data, largeur, longueur, end2);

        _eval += compterColonnes('N', data, largeur, longueur, end2);
        _eval -= compterColonnes('G', data, largeur, longueur, end2);

        _eval += compterDiagonale('N', data, largeur, longueur, end2);
        _eval -= compterDiagonale('G', data, largeur, longueur, end2);

        return end || end2;
    }

    long calculerEval(char* data, short largeur, short longueur) {

        long _eval = 0;

        bool end;

        _eval += compterLignes('N', data, largeur, longueur, end);
        _eval -= compterLignes('G', data, largeur, longueur, end);

        _eval += compterColonnes('N', data, largeur, longueur, end);
        _eval -= compterColonnes('G', data, largeur, longueur, end);

        _eval += compterDiagonale('N', data, largeur, longueur, end);
        _eval -= compterDiagonale('G', data, largeur, longueur, end);

        return _eval;
    }

    int calculateScore(int compte) {

        if(compte == 0) return 0;
        else if(compte == 1) return 1;
        else if(compte == 2) return 50;
        else if(compte == 3) return 2500;
        else if(compte == 4) return 75000;
        else if(compte == 5) return 500000;

        return 0;
    }

    int compterLignes(char type, char* data, short largeur, short hauteur, bool& ended) {

        int compte = 0;

        for(int i = 0; i < hauteur; i++) {

            int cntr = 0;

            for(int j = 0; j < largeur; j++) {

                char actual = data[i * largeur + j];

                if(type == actual) cntr++;
                else {

                    compte += calculateScore(cntr);
                    cntr = 0;
                }

                if(cntr == 5) ended = true;
            }            

            if(data[i * largeur + largeur - 1] == type) compte += calculateScore(cntr);
        }

        return compte;    
    }

    int compterColonnes(char type, char* data, short largeur, short hauteur, bool& ended) {

        int compte = 0;

        for(int i = 0; i < largeur; i++) {

            char tmp = type;
            int cntr = 0;

            for(int j = 0; j < hauteur; j++) {

                char actual = data[j * largeur + i];

                if(tmp == actual) cntr++;
                else {

                    compte += calculateScore(cntr);
                    cntr = 0;
                }

                if(cntr == 5) ended = true;
            }            
            
            if(data[(hauteur-1) * largeur + i] == type) compte += calculateScore(cntr);
        }

        return compte;    
    }

    int compterDiagonale(char type, char* data, short largeur, short hauteur, bool& ended) {

        int compte = 0;

        for(int i = largeur-1; i >= 0; i--) {

            char tmp = type;
            int cntr = 0;

            char ligne = 0;

            for(int j = i; j < largeur; j++) {

                char actual = data[ligne * largeur + j];

                if(tmp == actual) cntr++;
                else {

                    compte += calculateScore(cntr);
                    cntr = 0;
                }

                ligne++;

                if(cntr == 5) ended = true;
            }
            
            

            if(data[(largeur-1-i) * largeur + largeur - 1] == type) compte += calculateScore(cntr);
        }

        for(int i = 1; i < hauteur; i++) {

            int cntr = 0;

            char colonne = 0;

            for(int j = i; j < hauteur; j++) {

                char actual = data[j * largeur + colonne];

                if(type == actual) cntr++;
                else {

                    compte += calculateScore(cntr);
                    cntr = 0;
                }

                colonne++;

                if(cntr == 5) ended = true;
            }           

            if(data[(hauteur-1)* largeur + largeur-1-i] == type) compte += calculateScore(cntr);
        }

        for(int i = 0; i < largeur; i++) {

            int cntr = 0;

            int ligne = hauteur-1-i;

            for(char j = 0; j < largeur-i; j++) {

                char actual = data[ligne * largeur + j];

                if(type == actual) cntr++;
                else {

                    compte += calculateScore(cntr);
                    cntr = 0;
                }

                ligne--;

                if(cntr == 5) ended = true;
            }
            
            

            if(data[largeur-1-i] == type) compte += calculateScore(cntr); 
        }

        for(int i = 1; i < largeur; i++) {

            int cntr = 0;

            char ligne = (char)i;

            for(int j = largeur-1; j >= i ; j--) {

                char actual = data[ligne * largeur + j];

                if(type == actual) cntr++;
                else {

                    compte += calculateScore(cntr);
                    cntr = 0;
                }

                ligne++;

                if(cntr == 5) ended = true;
            }

            if(data[(hauteur-1) * largeur + i] == type) compte += calculateScore(cntr); 
        }

        return compte;    
    }

    char getLigne(short i, char largeur) {

        return (char)(i / largeur);
    }

    char getCol(short i, char largeur) {

        return (char)(i % largeur);
    }

private:

    std::vector<node*>* childs;
    node* _parent;

    short played;
    bool noire;
};