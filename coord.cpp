#include "coord.hpp"
#include "doctest.h"

Coord::Coord(int lig, int col){
    if(lig<0 or lig>=TAILLEGRILLE or col<0 or col>=TAILLEGRILLE){
        throw invalid_argument("L'indice de la ligne ou de la colonne est invalide !");
    }else{
        coordonnees.first = lig;
        coordonnees.second = col;
    }
}

pair<int,int> Coord::get_coordonnees() const {
    return coordonnees;
}


std::ostream& operator<< (std::ostream& out, Coord a){
    pair<int,int> c = a.get_coordonnees();
    out << "(" << c.first << "," << c.second << ")";
    return out;
}

bool operator==(Coord c1, Coord c2) {
    pair<int,int> coord2 = c2.get_coordonnees();
    pair<int,int> coord1 = c1.get_coordonnees();
    return (coord1.first == coord2.first and coord1.second == coord2.second);

}

bool operator!=(Coord c1, Coord c2) {
    pair<int,int> coord2 = c2.get_coordonnees();
    pair<int,int> coord1 = c1.get_coordonnees();
    return (coord1.first != coord2.first or coord1.second != coord2.second);

}

TEST_CASE("Constructeur Coord") {
    CHECK_THROWS_AS(Coord(-1,1),invalid_argument);
    CHECK_THROWS_AS(Coord(1,-1),invalid_argument);
    CHECK_THROWS_AS(Coord(-1,-1),invalid_argument);
    //Coord f(TAILLEGRILLE-1,TAILLEGRILLE-1);
    CHECK_THROWS_AS(Coord(TAILLEGRILLE,1),invalid_argument);
    CHECK_THROWS_AS(Coord(1,TAILLEGRILLE),invalid_argument);
    CHECK_THROWS_AS(Coord(TAILLEGRILLE,TAILLEGRILLE),invalid_argument);
}
 
TEST_CASE("Test opérateur Coord == et != ") {
    CHECK(Coord(1,2)==Coord(1,2));
    CHECK(Coord(1,0)!=Coord(2,0));
    CHECK(Coord(3,1)!=Coord(3,2));

}


// Ensemble coord



EnsCoord::EnsCoord(){
    ens = {{}};
}

EnsCoord::EnsCoord(vector<Coord> t){
    ens = t;
}


TEST_CASE("Constructeur Ensemble Coord ") {
    Coord a{1,2};
    Coord b{2,1};
    vector<Coord> test = {a,b};
    CHECK(EnsCoord().get_ens_coordonnees().size()==0);
    
}

vector<Coord> EnsCoord::get_ens_coordonnees() const {
    return ens;
}

int EnsCoord::position(Coord c) const{
    for(int i=0;i< int(ens.size());i++){
        if (ens[i] == c){
            return i;
        }
    } return -1;
}

/**
TEST_CASE("Position coordonnée"){
    Coord a{1,2};
    Coord b{2,1};
    Coord c{3,1};
    EnsCoord test{{a,b,c}};
    CHECK(test.position(a)==0);
    CHECK(test.position(c)==2);
    CHECK(test.position(Coord{4,1})==-1);
}**/

bool EnsCoord::contient(Coord c) const {
    return(position(c)!=-1);
}

TEST_CASE("contient") {
    Coord a{1,2};
    Coord b{2,1};
    Coord c{3,1};
    EnsCoord test{{a,b,c}};
    CHECK(test.contient(a));
    CHECK(test.contient(c));
    CHECK_FALSE(test.contient(Coord{4,1}));
}

void EnsCoord::ajoute(Coord c) {
    if(not contient(c)) {
        ens.push_back(c);
    }
}

TEST_CASE("ajoute") {
    EnsCoord test;
    test.ajoute(Coord{1,2});
    test.ajoute(Coord{1,2});
    CHECK(test.get_ens_coordonnees().size()==1);
}

void EnsCoord::supprime(Coord c) {
    //Attention !! Modifie l'ordre de l'ensemble.
    Coord tmp(0,0);
    if(contient(c)) {
        tmp = ens[position(c)];
        ens[position(c)] = ens[ens.size()-1];
        ens[ens.size()-1] = tmp;
        ens.pop_back();
    } else {
        throw invalid_argument("L'élément n'est pas dans la liste");
    }
}

TEST_CASE("supprime") {
    EnsCoord test;
    test.ajoute(Coord{1,2});
    test.supprime(Coord{1,2});
    CHECK(test.get_ens_coordonnees().size()==0);
    test.ajoute(Coord{2,2});
    CHECK_THROWS_AS(test.supprime(Coord{1,2}), invalid_argument);
} 

bool EnsCoord::estVide() const {
    return ens.size() == 0;
}

TEST_CASE("est vide"){
    EnsCoord test;
    CHECK(test.estVide());
    test.ajoute(Coord{2,2});
    CHECK_FALSE(test.estVide());
}

int EnsCoord::taille() const {
    return ens.size();
}

TEST_CASE("taille "){
    EnsCoord test;
    CHECK(test.taille()==0);
    test.ajoute(Coord{2,2});
    CHECK(test.taille()==1);
}

Coord EnsCoord::ieme(int n) const {
    return ens[n];
}

TEST_CASE("ieme"){
    EnsCoord test;
    test.ajoute(Coord{2,2});
    test.ajoute(Coord{1,1});
    test.ajoute(Coord{1,2});
    test.ajoute(Coord{2,1});
    CHECK(test.ieme(0)==Coord{2,2});
    CHECK(test.ieme(3)==Coord{2,1});
}

std::ostream& operator<< (std::ostream& out, EnsCoord a){
    vector<Coord> c = a.get_ens_coordonnees();
    out << " { ";
    for(int i=0;i<int(c.size());i++){
       out << c[i] << ", "; 
    } out << "}";
    return out;
}

// Fonctions à part entière SKIZOOOOOOO !!

EnsCoord voisines(Coord c) const {
    EnsCoord res;
    int lig = c.get_coordonnees().first;
    int col = c.get_coordonnees().second;
    for(int i = max(lig -1,0); i <= min(lig +1, TAILLEGRILLE-1);i++) {
            for(int j = max(col-1,0); j <= min(col+1,0) ; j++){
                if(Coord(i,j)!=c){
                    res.ajoute(Coord(i,j));
                }
            }
    }

}

TEST_CASE("voisines"){
    Coord a{2,1};
    Coord b{3,4};
    Coord c{0,0};
    EnsCoord res1;
    //penser à l'ordre des vecteurs
    res1.ens = {Coord(1,0), Coord(1,1),Coord(1,2), Coord(2,2), Coord(3,2), Coord(3,1), Coord(3,0), Coord(2,0) }
    EnsCoord res2;
    EnsCoord res3;
    CHECK(test.voisines(a)==res1);
    CHECK(test.voisines(b)==res2);
    CHECK(test.voisines(c)==res3);
}
