#include "fourmis.hpp"
#include "doctest.h"
//CLASSE FOURMI

// Constructeurs
Fourmis::Fourmis(Coord c, int ind,int colo){
    coord = c;
    num = ind;
    col = colo;
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

int Fourmis::get_col() const{
    return col;
}

void Fourmis::set_col(int colo) {
    col = colo;
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

void Fourmis::tue(){
    enVie = false;
}

//Fonctions 
vector<Fourmis> creeTabFourmis(EnsCoord e,vector<int> colo){
    vector<Fourmis> res = {};
    if(e.taille() != int(colo.size())){
        throw invalid_argument("La taille de l'ensemble des coordonnées n'est pas la meme que le vect colo ! ");
    }
    for(int i=0;i<e.taille();i++){
        res.push_back(Fourmis(e.ieme(i),i,colo[i]));
    } return res;
}


Fourmis chercheFourmis(vector<Fourmis> tabf, int ind){
    for (auto& f : tabf){
        if(f.get_num()==ind){
            return f;
        }
    } throw invalid_argument("Cette fourmis n'existe pas");
}


void rangeFourmi(vector<Fourmis> &tabf, Fourmis f){
    for(int i=0;i< int(tabf.size());i++){
        if (f.get_num() == tabf[i].get_num()){
            tabf[i] = f;
            return;
        }
    }
}

TEST_CASE("Fourmis") {
    
    vector<Coord> coordFourmis = {Coord(1,1)};
    EnsCoord ensCoordFourmis = coordFourmis;
    vector<int> tabC {{1}};
    vector<Fourmis> tabFourmis = creeTabFourmis(ensCoordFourmis,tabC);
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
