#include <iostream>
#include <vector>
#include <cstdlib> 
#include "doctest.h"
using namespace std;


class Coord {
    public : 
        Coord(int lig, int col);
        pair<int,int> get_coordonnees() const;

    private:
        pair<int,int> coordonnees;

};

class EnsCoord {
    public :
        //Constructeurs
        EnsCoord();
        EnsCoord(vector<Coord> t);
        //Getters et setters
        vector<Coord> get_ens_coordonnees() const;
        bool contient(Coord c) const;
        void ajoute(Coord c);
        void supprime(Coord c);
        bool estVide() const;
        int taille() const;
        Coord ieme(int n) const;
        //Fonctions
        Coord choixHasard() const;
        void tri();
    private :
        vector<Coord> ens;
        int position(Coord c) const;
};

EnsCoord voisines(Coord c);
std::ostream& operator<< (std::ostream& out, Coord a);
bool operator==(Coord c1, Coord c2);
bool operator!=(Coord c1, Coord c2);

