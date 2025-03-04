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

#define WIDTH 800
#define HEIGHT 600

int** dataBoard;
bool isPicked = false;
int xPicked;
int yPicked;

void printDepart();
configuration lireConfiguration();
bool estNoir(configuration* config);
void recursifNiveau(clock_t horloge, tree& arbre, bool noire, bool arbreMax, configuration conf, int& niveaux,bool& succes, long& countNodes);
void drawBoard(SDL_Renderer* renderer);
void drawCircle(int x, int y, int radius, SDL_Renderer*);
void playTurn(int player);


int main(void) {

    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer *renderer;

    dataBoard = new int*[10];
    for(int i = 0; i < 10; i++) {

        dataBoard[i] = new int[10];

        for(int j = 0; j < 10; j++) {

            dataBoard[i][j] = 0;
        }
    } 

    bool done = false;

    int playerTurn = 0;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        500,                               // width, in pixels
        500,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                
                xPicked = event.button.x;
                yPicked = event.button.y;

                isPicked = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Do game logic, present a frame, etc.        

        playTurn(playerTurn);        

        drawBoard(renderer);


        /////////////////////////////////////////
        SDL_RenderPresent(renderer);
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    /*

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
        myfile.close();
        
        arbre.deleteTree();

        return 0;
    }*/

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

void drawCircle(int xx, int yy, int radius, SDL_Renderer* renderer) {
        
    for(int i = 0; i < 360; i ++) {

        int xc = xx;
        int yc = yy;

        float r = i/360.0f*2*3.14159f;                                 
        int x = xc + radius * cos(r);
        int y = yc + radius * sin(r);
        SDL_RenderPoint(renderer, x, y);
	}
}

void playTurn(int player)
{
    if(player == 0) {


        if(player == 1) player = 0;
        else player = 1;
    }
    else {

        if(isPicked) {

            

            isPicked = false;
        }
    }

    
}

void drawBoard(SDL_Renderer *renderer)
{
    
    for(int i = 0;  i < 10; i++) {

        for(int j = 0; j < 10; j++) {

            SDL_FRect rect;
            rect.h = 50;
            rect.w = 50;
            rect.x = j * 50;
            rect.y = i * 50;

            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            SDL_RenderRect(renderer, &rect);

            if(dataBoard[i][j] == 1) {

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                drawCircle(i*50+25, j*50+25, 15, renderer);
            }
            else if(dataBoard[i][j] == 2) {

                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                drawCircle(i*50+25, j*50+25, 15, renderer);
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