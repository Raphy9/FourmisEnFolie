#include "fourmis.hpp"
#include "doctest.h"
//CLASSE FOURMI

// Constructeurs
Fourmis::Fourmis(Coord c, int ind){
    coord = c;
    num = ind;
    porteSucre = false;
    enVie = true;
}

//Getter Setters

Coord Fourmis::get_coord() const {
    return coord;
}
int Fourmis::get_num() const {
    return num;
}

bool Fourmis::chercheSucre(){
    return !porteSucre;
}
bool Fourmis::rentreNid(){
    return porteSucre;
}
bool Fourmis::estVivante(){
    return enVie;
}
bool Fourmis::get_porteSucre() const {
    return porteSucre;
}

void Fourmis::prendSucre(){
    porteSucre = true;
}

void Fourmis::poseSucre(){
    porteSucre = false;

}

void Fourmis::deplace(Coord c){
    coord = c;
}


//Fonctions 
vector<Fourmis> creeTabFourmis(EnsCoord e){
    vector<Fourmis> res = {};
    for(int i=0;i<e.taille();i++){
        res.push_back(Fourmis(e.ieme(i),i));
    } return res;
}

TEST_CASE("Fourmis") {
    
    vector<Coord> coordFourmis = {Coord(1,1)};
    EnsCoord ensCoordFourmis = coordFourmis;
    vector<Fourmis> tabFourmis = creeTabFourmis(ensCoordFourmis);
    Fourmis fourmiTest = tabFourmis[0];

    CHECK(fourmiTest.get_coord() == Coord(1,1));
    CHECK(fourmiTest.get_num() == 0);
    CHECK_FALSE(fourmiTest.get_porteSucre());

    fourmiTest.deplace(Coord(2,2));
    CHECK(fourmiTest.get_coord() == Coord(2,2));

    fourmiTest.prendSucre();
    CHECK(fourmiTest.get_porteSucre());

    CHECK_THROWS_AS(fourmiTest.deplace(Coord(2,-1)), invalid_argument);
    fourmiTest.deplace(Coord(2,3));
    CHECK( (fourmiTest.get_coord()) == Coord(2,3));

    fourmiTest.poseSucre();
    CHECK_FALSE(fourmiTest.get_porteSucre());
    
}
