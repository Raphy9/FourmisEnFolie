#include <iostream>
#include <vector>
#include "coord.hpp"

class Fourmis{
    public :
        Fourmis(Coord c, int ind);
        Coord get_coord() const;
        int get_num() const;
        bool get_porteSucre() const ;
        void prendSucre();
        void poseSucre();
        void deplace(Coord c);


    //Raphy92 propose qu'on laisse le commentaire pour dire qu'on fait
    //le choix là d'initialiser à 0 #foliefourmie!! #SKIZOO
    private :
        Coord coord = Coord(0,0);
        int num;
        bool porteSucre;


};