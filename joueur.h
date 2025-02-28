class joueur {

public:

    joueur(bool noir) {

        _noir = noir;
        
        if(_noir) _couleur = 'N';
        else _couleur = 'G';
    }

    char getCouleur() {

        return _couleur;
    }

private:

    bool _noir;
    char _couleur;
};