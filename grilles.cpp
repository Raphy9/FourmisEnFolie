#include "grilles.hpp"

//----------CLASSE PLACE-------------
//Constructeurs

Place::Place(Coord c){
    coord = c;
    pheroSucre = 0;
    pheroNid = 0;
    numFourmi = -1;
    contientNid = false;
    contientSucre = false;
}


//Getters et Setters
Coord Place::get_coord() const {
    return coord;
}

bool Place::get_contientSucre() const {
    return contientSucre;
}

bool Place::get_contientNid() const {
    return contientNid;
}

bool Place::get_estSurUnePiste() const {
    return pheroSucre>0;
}


void Place::poseSucre(){
    contientSucre = true;
}

void Place::enleveSucre(){
    contientSucre = false;
}

void Place::poseNid(){
    contientNid = true;
}


void Place::poseFourmi(Fourmis f){
    f.deplace(coord);
    numFourmi = f.get_num();
}
void Place::enleveFourmi(){
    numFourmi = -1;
}

void Place::posePheroNid(int intensite){
    pheroNid = intensite;
}

void Place::posePheroSucre(int intensite){
    pheroSucre = intensite;

}

void Place::diminuePheroSucre(){
    //Diminue par défaut à 1
    pheroSucre--;
}

bool Place::estVide(){
    return numFourmi==-1 and !contientNid and !contientSucre;
}

bool Place::estPlusProcheNid(Place p1, Place p2){
    if(contientNid){
        pair<int,int> c1 = p1.get_coord().get_coordonnees();
        pair<int,int> c2 = p2.get_coord().get_coordonnees();
        return sqrt( pow(c1.first - coord.get_coordonnees().first,2) + pow(c1.second - coord.get_coordonnees().second,2)) 
        <= sqrt( pow(c2.first - coord.get_coordonnees().first,2) + pow(c2.second - coord.get_coordonnees().second,2));
    } else{
        throw invalid_argument("Il n'y a pas de nid ici ptn");
    }
}

//Fonctions

void DeplaceFourmi(Fourmis f, Place &p1, Place &p2){
    p2.poseFourmi(f);
    p1.enleveFourmi();
}

