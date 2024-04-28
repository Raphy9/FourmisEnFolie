#include "fourmis.hpp"
#include <cmath>
class Place{
    public : 
        //Constructeur
        Place(Coord c);
        //Getters et setters
        Coord get_coord() const;
        bool get_contientSucre() const;
        bool get_contientNid() const;
        bool get_estSurUnePiste() const;
        void poseSucre();
        void enleveSucre();
        void poseNid();
        void poseFourmi(Fourmis f);
        void enleveFourmi();
        void posePheroNid(int intensite);
        void posePheroSucre(int intensite);
        void diminuePheroSucre();
        //Méthodes
        bool estVide();
        bool estPlusProcheNid(Place p1, Place p2);
    private :
        //Attribut
        Coord coord = Coord(0,0);
        int pheroSucre;
        int pheroNid;
        int numFourmi;
        bool contientSucre;
        bool contientNid;
};