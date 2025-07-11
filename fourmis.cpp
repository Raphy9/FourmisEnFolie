#include "fourmis.hpp"
#include "doctest.h"
//CLASSE FOURMI

// Constructeurs
Fourmis::Fourmis(Coord c, int ind,int colo,int type){
    coord = c;
    num = ind;
    col = colo;
    porteSucre = false;
    enVie = true;
    typeF = type;
}

//Getter Setters

Coord Fourmis::get_coord() const {
    return coord;
}
int Fourmis::get_num() const {
    return num;
}

int Fourmis::get_type() const{
    return typeF;
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




Fourmis chercheFourmis(vector<Fourmis> tabf, int ind){
    for (auto& f : tabf){
        if(f.get_num()==ind){
            return f;
        }
    } throw invalid_argument("Cette fourmis n'existe pas");
}

TEST_CASE("Cherche fourmis"){
    Fourmis a(Coord(2,1),0,0,0);
    Fourmis b(Coord(2,2),1,1,0);
    vector<Fourmis> test = {a,b};
    CHECK(chercheFourmis(test,0).get_coord() == a.get_coord());
    CHECK(chercheFourmis(test,1).get_coord() == b.get_coord());
    CHECK_THROWS_AS(chercheFourmis(test,2),invalid_argument);

}


void rangeFourmi(vector<Fourmis> &tabf, Fourmis f){
    for(int i=0;i< int(tabf.size());i++){
        if (f.get_num() == tabf[i].get_num()){
            tabf[i] = f;
            return;
        }
    }
}

TEST_CASE("Range fourmi"){
    Fourmis a(Coord(2,1),0,0,0);
    Fourmis b(Coord(2,2),1,1,0);
    vector<Fourmis> test = {a,b};
    a.set_col(2);
    b.tue();
    rangeFourmi(test,a);
    rangeFourmi(test,b);
    CHECK(a.get_col()==chercheFourmis(test,a.get_num()).get_col());
    CHECK(b.estVivante()==chercheFourmis(test,b.get_num()).estVivante());

}

TEST_CASE("Fourmis") {
    
    vector<Coord> coordFourmis = {Coord(1,1)};
    EnsCoord ensCoordFourmis = coordFourmis;
    vector<int> tabC {{1}};
    vector<Fourmis> tabFourmis;
    for(int i=0;i<ensCoordFourmis.taille();i++){
        tabFourmis.push_back(Fourmis(ensCoordFourmis.ieme(i),i,0,0));
    }
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
