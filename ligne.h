enum sens {

    horizontale,
    verticale,
    diagonale,
    ponctuel
};

class ligne {

public:

    ligne(short point) {

        _begin = point;
        _fin = point;
        _ligneSens = ponctuel;
        _score = 1;
    }

    bool is_juxtapose(short point, char largeur) {

        bool juxta = false;

        int ligneC = getLigne(_begin, largeur);
        int colC = getCol(_begin, largeur);

        int ligneD = getLigne(point, largeur);
        int colD = getCol(point, largeur);

        int ligneE = getLigne(_fin, largeur);
        int colE = getCol(_fin, largeur);
        
        bool pLigne = partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD, colD);

        if(!pLigne) {

            if(_ligneSens == ponctuel) {           

                if(ligneD == ligneC && colD+1 == colC) {

                    _ligneSens = horizontale;
                    _fin = point;
                    _score = 2;
                    juxta = true;
                }
                else if(ligneD == ligneC && colD-1 == colC) {

                    _ligneSens = horizontale;
                    _fin = point;
                    _score = 2;
                    juxta = true;
                }
                else if(ligneD+1 == ligneC && colD == colC) {

                    _ligneSens = verticale;
                    _fin = point;
                    _score = 2;
                    juxta = true;
                }
                else if(ligneD-1 == ligneC && colD == colC) {

                    _ligneSens = verticale;
                    _fin = point;
                    _score = 2;
                    juxta = true;
                }
                else if(ligneD+1 == ligneC && colD+1 == colC) {

                    _ligneSens = diagonale;
                    _fin = point;
                    _score = 2;
                    juxta = true;
                }
                else if(ligneD-1 == ligneC && colD-1 == colC) {

                    _ligneSens = diagonale;
                    _fin = point;
                    _score = 2;
                    juxta = true;
                }
                else if(ligneD+1 == ligneC && colD-1 == colC) {

                    _ligneSens = diagonale;
                    _fin = point;
                    _score = 2;
                    juxta = true;
                }
                else if(ligneD-1 == ligneC && colD+1 == colC) {

                    _ligneSens = diagonale;
                    _fin = point;
                    _score = 2;
                    juxta = true;
                }
            }
            else if(_ligneSens == horizontale) {

                if(ligneD == ligneC && colD+1 == colC) {

                    _begin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD == ligneC && colD-1 == colC) {

                    _begin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD == ligneE && colD-1 == colE) {

                    _fin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD == ligneE && colD+1 == colE) {

                    _fin = point;
                    _score++;
                    juxta = true;
                }
            }
            else if(_ligneSens == verticale) {

                if(ligneD+1 == ligneC && colD == colC) {

                    _begin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD-1 == ligneC && colD == colC) {

                    _begin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD-1 == ligneE && colD == colE) {

                    _fin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD+1 == ligneE && colD == colE) {

                    _fin = point;
                    _score++;
                    juxta = true;
                }
            }
            else if(_ligneSens == diagonale) {

                if(ligneD+1 == ligneC && colD+1 == colC) {

                    _begin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD-1 == ligneC && colD-1 == colC) {

                    _begin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD-1 == ligneE && colD-1 == colE) {

                    _fin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD+1 == ligneE && colD+1 == colE) {

                    _fin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD+1 == ligneC && colD-1 == colC) {

                    _begin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD-1 == ligneC && colD+1 == colC) {

                    _begin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD-1 == ligneE && colD+1 == colE) {

                    _fin = point;
                    _score++;
                    juxta = true;
                }
                else if(ligneD+1 == ligneE && colD-1 == colE) {

                    _fin = point;
                    _score++;
                    juxta = true;
                }
            }
        }

        if(!juxta && !pLigne) return true;

        return juxta;
    }

    char getSize() {

        return _score;
    }

    char getScore() {

        return _score;
    }

    void concatener(ligne cLigne, int largeur) {

        int ligneC = getLigne(cLigne._begin, largeur);
        int colC = getCol(cLigne._begin, largeur);

        int ligneD1 = getLigne(_begin, largeur);
        int colD1 = getCol(_begin, largeur);

        int ligneD2 = getLigne(_fin, largeur);
        int colD2 = getCol(_fin, largeur);

        int ligneE = getLigne(cLigne._fin, largeur);
        int colE = getCol(cLigne._fin, largeur);
        
        if(_ligneSens == ponctuel) {
            
            if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1 + 1, colD1)) {

                _begin += largeur;
                _score++;
                _ligneSens = verticale;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1, colD1 + 1)) {

                _begin += 1;
                _score++;
                _ligneSens = horizontale;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1-1, colD1)) {

                _begin -= largeur;
                _score++;
                _ligneSens = verticale;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1, colD1 - 1)) {

                _begin -= 1;
                _score++;
                _ligneSens = horizontale;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1+1, colD1 + 1)) {

                _begin += (largeur + 1);
                _score++;
                _ligneSens = diagonale;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1+1, colD1 - 1)) {

                _begin += (largeur-1);
                _score++;
                _ligneSens = diagonale;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1-1, colD1 + 1)) {

                _begin -= (largeur - 1);
                _score++;
                _ligneSens = diagonale;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1-1, colD1 - 1)) {

                _begin -= (largeur + 1);
                _score++;
                _ligneSens = diagonale;
            }
        }
        else if(_ligneSens == horizontale) {

            if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1, colD1 - 1)) {

                _begin -= 1;
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1, colD1 + 1)) {

                _begin += 1;
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD2, colD2 + 1)) {

                _fin += 1;
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD2, colD2 - 1)) {

                _fin -= 1;
                _score++;
            }
        }
        else if(_ligneSens == verticale) {

            if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1 - 1, colD1)) {

                _begin -= largeur;
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1 + 1, colD1)) {

                _begin += largeur;
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD2 + 1, colD2)) {

                _fin += largeur;
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD2 - 1, colD2)) {

                _fin -= largeur;
                _score++;
            }
        }
        else if(_ligneSens == diagonale) {

            if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1 - 1, colD1 - 1)) {

                _begin -= (largeur + 1);
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1 + 1, colD1 + 1)) {

                _begin += (largeur + 1);
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1 + 1, colD1 - 1)) {

                _begin += (largeur - 1);
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD1 - 1, colD1 + 1)) {

                _begin -= (largeur - 1);
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD2 - 1, colD2 - 1)) {

                _fin -= (largeur + 1);
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD2 + 1, colD2 + 1)) {

                _fin += (largeur + 1);
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD2 + 1, colD2 - 1)) {

                _fin += (largeur - 1);
                _score++;
            }
            else if(partieDeLaLigne(ligneC, colC, ligneE, colE, ligneD2 - 1, colD2 + 1)) {

                _fin -= (largeur - 1);
                _score++;
            }
        }
    }

private:

    bool partieDeLaLigne(int DL, int DC, int FL, int FC, int PL, int PC) {

        bool test = false;
        
        if(_ligneSens == ponctuel) {

            if(DL == PL && DC == PC) test = true;
        }
        else if(_ligneSens == horizontale && FL == PL) {

            int direction = FC - DC;

            for(int i = 0; i <= abs(direction); i++) {

                if(PC == DC + abs(direction)/direction * i) {

                    test = true;
                    break;
                } 
            }
        }
        else if(_ligneSens == verticale && FC == PC) {

            int direction = FL - DL;

            for(int i = 0; i <= abs(direction); i++) {

                if(PL == DL + abs(direction)/direction * i) {

                    test = true;
                    break;
                } 
            }
        }
        else if(_ligneSens == diagonale) {

            int direction1 = FC - DC;
            int direction2 = FL - DL;

            for(int i = 0; i <= abs(direction1); i++) {

                if(PC == DC + abs(direction1)/direction1 * i) {

                    if(PL == DL + abs(direction2)/direction2 * i) {

                        test = true;
                        break;
                    }
                } 
            }
        }
    
        return test;
    }

    char getLigne(short i, char largeur) {

        return i / largeur;
    }

    char getCol(short i, char largeur) {

        return i % largeur;
    }

private:

    short _begin;
    short _fin;

    sens _ligneSens;

    char _score;
};