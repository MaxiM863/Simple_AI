#include<iostream>
#include"node.h"


class tree {

public:

    tree(char* debutDataTop, short largeur, short longueur) {

        _top = new node(nullptr);

        debutData = debutDataTop;

        _largeur = largeur;
        _longueur = longueur;
    }

    void deleteTree() {

        deleteT(_top);
    }

    node* getTop() {

        return _top;
    }

    char* getDebutTop() {

        return debutData;
    }

    int maxNiveaux() {

        int niveaux = 0;

        trouverMaxNiveau(_top, 0, niveaux);

        return niveaux;
    }

    node* getBestEval(bool noire, int niveau) {

        long alpha = -999999;
        long beta = 999999;

        long evalV = 0;

        node* best = minmax(_top, evalV, noire, alpha, beta, niveau, debutData, _longueur, _largeur);

        return best;
    }

    void ajouterNiveau(bool noire, char* debutTree, short largeur, short longueur,long& count, 
        bool& succesNiveau, long maxNodes, clock_t maxTime, clock_t horloge) {

        long ct = count;

        recursifFeuilles(_top, noire, debutTree, largeur, longueur, ct, succesNiveau, maxNodes, maxTime, horloge);

        count = ct;
    }

    long getNodesNbr() {

        return countNodes(_top);
    }

    bool getEnded(char* debutTop, short largeur, short longueur) {

        return _top->getIfEnded(debutTop, (char)largeur, (char)longueur);
    }

private:

    long countNodes(node* actual) {

        long tmp = 0;

        for(size_t i = 0; i < actual->getChilds()->size(); i++) {

            tmp += countNodes(actual->getChilds()->at(i)) + 1;
        }

        return tmp;
    }

    node* minmax(node* actual, long& evalV, bool noire, long alpha, long beta, int niveaux, char* debutTree, short longueur, short largeur) {

        node* ret = actual;
        
        if(niveaux != 0 && !actual->getIfEnded(debutTree, (char)largeur, (char)longueur)) {

            if(noire) {

                long maxEval = -999999;
                long tmpE = 0;            

                for(size_t i = 0 ; i < actual->getChilds()->size(); i++) {

                    long eval;
                    
                    node* tmpN = minmax(actual->getChilds()->at(i), eval, !noire, alpha, beta, niveaux-1, debutTree, longueur, largeur);

                    if(eval > maxEval) {

                        ret = tmpN;
                        tmpE = std::max(eval, maxEval);
                    } 

                    maxEval = std::max(eval, maxEval);

                    alpha = std::max(alpha, eval);

                    if(maxEval > beta) break;
                }              
                
                evalV = tmpE;
                return ret;
            }
            else {

                long minEval = 999999;
                long tmpE = 0;

                for(size_t i = 0 ; i < actual->getChilds()->size(); i++) {

                    long eval;
                    
                    node* tmpN = minmax(actual->getChilds()->at(i), eval, !noire, alpha, beta, niveaux-1, debutTree, longueur, largeur);

                    if(eval < minEval) {
                        
                        ret = tmpN;
                        tmpE = std::min(eval, minEval);
                    }

                    minEval = std::min(eval, minEval);

                    beta = std::min(beta, eval);

                    if(minEval < alpha) break;
                }                
                
                evalV = tmpE;
                return ret;
            }
        }
        else {

            evalV = actual->getEval(debutData, (char)largeur, (char)longueur);
            return ret;
        }
    }

    void trouverMaxNiveau(node* actual, int count, int& maxCount) {        

        if(actual->getChilds()->size() != 0) {
            
            if(maxCount < count) maxCount = count;
            
            for (size_t i = 0; i < actual->getChilds()->size(); i++) {
             
                trouverMaxNiveau(actual->getChilds()->at(i), count + 1, maxCount);
            }
        }
    }

    void recursifGetFeuille(node* actual, node& target) {

        if(actual->getChilds()->size() != 0) {

            recursifGetFeuille(actual->getChilds()->at(0), target);
        }
        else {

            target = *actual;
        }
    }

    void recursifFeuilles(node* actual, bool noire, char* debutTree, short largeur, short longueur, long& count, 
        bool& succesNiveau, long maxNodes, clock_t maxTime, clock_t horloge) {

        if(succesNiveau) {

            if(actual->getChilds()->size() == 0) {

                //long ttt = (clock() - horloge)*2000/CLOCKS_PER_SEC;

                if(count < maxNodes) {

                    long cc = count;

                    addChilds(actual, noire, debutTree, largeur, longueur, cc);

                    count = cc;
                }
                else succesNiveau = false;
            }
            else {              
                    
                for(size_t i =0; i < actual->getChilds()->size(); i++) {

                    recursifFeuilles(actual->getChilds()->at(i), noire, debutTree, largeur, longueur, count, succesNiveau, maxNodes, maxTime, horloge);
                }            
            }
        }
    }

    void addChilds(node* actual, bool noire, char* debutTree, short largeur, short longueur, long& count) {

        int ll = _largeur * _longueur;
        char* data = actual->getDataMatrix(debutTree, (char)largeur, (char)longueur);

        for(int i = 0; i < ll; i++) {

            if(data[i] == '0') {

                count++;

                node* newNode = new node(actual);
                
                newNode->addPlayed((short)i, noire); 
                
                actual->addChild(newNode);     
            }
        }
    }

    void deleteT(node* actual) {

        for (size_t i = 0; i < actual->getChilds()->size(); i++) {

            deleteT(actual->getChilds()->at(i));
        }

        actual->deleteN();
    }

private:

    node* _top;

    short _largeur;
    short _longueur;

    char* debutData;
};