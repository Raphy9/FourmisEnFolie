#include <iostream>
#include <vector>
#include "coord.hpp"
#include "doctest.h"
class Fourmis{
    public :
        //Constructeur
        Fourmis(Coord c, int ind, int colo,int type);
        
        //Getters et setters
        Coord get_coord() const;
        int get_num() const;
        int get_type() const;
        bool get_porteSucre() const ;
        int get_col() const ;
        void set_col(int colo);
        void prendSucre();
        void poseSucre();
        void deplace(Coord c);
        bool chercheSucre();
        bool rentreNid();
        bool estVivante();
        void tue();
        


    //Raphy92 propose qu'on laisse le commentaire pour dire qu'on fait
    //le choix là d'initialiser à 0 #foliefourmie!! #SKIZOO
    private :
        Coord coord = Coord(0,0);
        int num;
        bool porteSucre;
        bool enVie;
        int col;
        int typeF;


};

Fourmis chercheFourmis(vector<Fourmis> tabf, int ind);
void rangeFourmi(vector<Fourmis> &tabf, Fourmis f);