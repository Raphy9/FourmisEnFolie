int TAILLEGRILLE = 20;
#include <iostream>
#include <vector>
#include <cstdlib> 
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
        EnsCoord();
        EnsCoord(vector<Coord> t);
        vector<Coord> get_ens_coordonnees() const;
        bool contient(Coord c) const;
        void ajoute(Coord c);
        void supprime(Coord c);
        bool estVide() const;
        int taille() const;
        Coord ieme(int n) const;
        Coord choixHasard() const;
        void tri();
    private :
        vector<Coord> ens;
        int position(Coord c) const;
};

EnsCoord voisines(Coord c);

