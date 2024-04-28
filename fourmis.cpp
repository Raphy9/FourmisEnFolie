#include "fourmis.hpp"


//CLASSE FOURMI

// Constructeurs
Fourmis::Fourmis(Coord c, int ind){
    coord = c;
    num = ind;
    porteSucre = false;
}

//Getter Setters

Coord Fourmis::get_coord() const {
    return coord;
}
int Fourmis::get_num() const {
    return num;
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
