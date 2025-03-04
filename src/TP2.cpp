#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>

#include "SDL3/SDL.h"

#include"configuration.h"
#include"joueur.h"
#include"tree.h"

using namespace std;

void printDepart();
configuration lireConfiguration();
bool estNoir(configuration* config);
void recursifNiveau(clock_t horloge, tree& arbre, bool noire, bool arbreMax, configuration conf, int& niveaux,bool& succes, long& countNodes);

int main(void) {

    printDepart();

    clock_t horloge;    

    bool loop = true;

    while(loop) {   

        horloge = clock();

        configuration conf = lireConfiguration();     
        
        char* debutD = new char[conf.getSize()+1];

        for(int i = 0; i < conf.getSize(); i++) {

            debutD[i] = conf.getData(i);
        }

        debutD[conf.getSize()] = '\0';

        tree arbre(debutD, conf.getLargeur(), (char)(conf.getSize()/conf.getLargeur()));

        if(arbre.getEnded(debutD, conf.getLargeur(), (char)(conf.getSize()/ conf.getLargeur()))){

            cout << 0 << endl;
            return 0;
        }
        
        joueur bot2(estNoir(&conf));

        int niveaux = 1;
        long countNodes = 0;
        bool succes = true;
        
        recursifNiveau(horloge, arbre, bot2.getCouleur() == 'N', bot2.getCouleur() == 'N', conf, --niveaux, succes, countNodes);        

        node* best = arbre.getBestEval(bot2.getCouleur() == 'N', niveaux);

        if(best->getParent() != nullptr) {
        
            while(best->getParent()->getParent() != nullptr) {

                best = best->getParent();
            }
        }
        
        conf.setData(best->getDataMatrix(debutD, conf.getLargeur(), (char)(conf.getSize()/conf.getLargeur())));

        conf.printString();

        /*ofstream myfile;
        myfile.open ("example.txt", ios::app);
        myfile << "# Niveaux: " << niveaux << endl;
        myfile << "# noeuds: " << arbre.getNodesNbr() << endl;
        clock_t jjj = clock();
        myfile << (int)(jjj-horloge)/1000 << endl;
        myfile << conf.getString();
        myfile << "_____________________" << endl;
        myfile.close();*/
        
        arbre.deleteTree();

        return 0;
    }

    return 0;
}

void recursifNiveau(clock_t horloge, tree& arbre, bool noire, bool arbreMax, configuration conf, int& niveau, bool& succes, long& countNodes) {

    int nbrNBR = conf.getSize();

    if(nbrNBR < 50) {

        clock_t tmpT = clock();

        clock_t time = (tmpT - horloge) * 1000 / CLOCKS_PER_SEC;

        if(time < (long)((float)conf.getTime() * 0.45f)) {
        
            arbre.ajouterNiveau(noire, arbre.getDebutTop(), conf.getLargeur(), (short)(conf.getSize()/conf.getLargeur()), 
                countNodes, succes, 4000000, conf.getTime(), horloge);
            
            node* tmpN = arbre.getBestEval(arbreMax, niveau);
            
            if(succes && !tmpN->getIfEnded(arbre.getDebutTop(), conf.getLargeur(), (char)(conf.getSize()/conf.getLargeur())))
                recursifNiveau(horloge, arbre, !noire, arbreMax, conf, ++niveau, succes, countNodes);
        }
    }
    else {

        noire = !noire;

        while(succes) { 
            
            clock_t tmpT = clock();

            clock_t time = (tmpT - horloge) * 1000 / CLOCKS_PER_SEC;

            if(time < (long)((float)conf.getTime() * 0.45f)) {
            
                noire = !noire;

                arbre.ajouterNiveau(noire, arbre.getDebutTop(), conf.getLargeur(), (short)(conf.getSize()/conf.getLargeur()), 
                    countNodes, succes, 4000000, conf.getTime(), horloge);
                
                niveau++;
            }
        }        
    }
}

void printDepart() {

    cout << "Maxim Thibodeau, THIM14067706, thibodeau.maxim@courrier.uqam.ca" << endl;
    cout << "PRET" << endl;
}

configuration lireConfiguration() {

    int tampon;    
    int ligne, col;
    int time;

    configuration conf(0,0);

    std::cin >> tampon;

    if(false) {

        std::cin >> tampon;
    }
    else {

        ligne = tampon;
        std::cin >> col;

        char* dataLigne = new char[col];

        conf.setLH((char)col, (char)ligne);

        for(char i = 0 ; i < ligne; i++) {
                            
            string tmpS;
            std::cin >> tmpS;

            for(size_t j = 0; j < tmpS.length(); j++) dataLigne[j] = tmpS.at(j);            

            conf.setData(dataLigne, i);
        }

        delete dataLigne;

        std::cin >> time;

        conf.setTime(time);

    }
    
    return conf;
}

bool estNoir(configuration* config) {

    int countNoir = 0;
    int countGris = 0;

    for(int i = 0; i < config->getSize(); i++) {

        if(config->getData(i) == 'N') countNoir++;
        else if(config->getData(i) == 'G') countGris++;
    }

    return countGris >= countNoir;
}