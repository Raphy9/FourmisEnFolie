#include "grilles.hpp"


//Fonctions

void deplaceFourmi(Fourmis f, Place &p1, Place &p2){
    p2.poseFourmi(f);
    p1.enleveFourmi();
}


int coord_to_ind(Coord c) {
    return c.get_coordonnees().first + c.get_coordonnees().second;
}

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

float Place::get_pheroNid() const {
    return pheroNid;
}



void Place::poseSucre(){
    contientSucre = true;
    pheroSucre = 1;
}

void Place::enleveSucre(){
    contientSucre = false;
}

void Place::poseNid(){
    contientNid = true;
    pheroNid = 1;
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





//CLASSE GRILLE

// Constructeurs
Grille::Grille(int taille){
    for(int i = 0; i < taille; i++) {
        for(int j = 0; j < taille; j++) {
            listePlace.push_back(Place(Coord(i,j)));
        }
    }
}

// Getters Setters

Place Grille::chargePlace(Coord c) {
    return listePlace[coord_to_ind(c)];
}

void Grille::rangePlace(Place p) {
    listePlace[coord_to_ind(p.get_coord())] = p;
}

Place Grille::get_place(int ind){
    return listePlace[ind];
}


//Fonctions
void placeNid(Grille &g,EnsCoord c){
    for(auto& elem : c.get_ens_coordonnees()){
        Place a = g.chargePlace(elem);
        a.poseNid();
        g.rangePlace(a);
    }
}

void placeSucre(Grille &g,EnsCoord c){
    for(auto& elem : c.get_ens_coordonnees()){
        Place a = g.chargePlace(elem);
        a.poseSucre();
        g.rangePlace(a);
    }
}

void placeFourmis(Grille &g, vector<Fourmis> f){
    for(auto& elem : f){
        Coord a = elem.get_coord();
        Place tmp = g.get_place(coord_to_ind(a));
        tmp.poseFourmi(elem);
        g.rangePlace(tmp);
    }
}

Grille initialiseGrille(vector<Fourmis> f, EnsCoord ensSucre, EnsCoord ensNid){
    Grille res = Grille(20); //mettre variable globale si possible
    placeFourmis(res,f);
    placeSucre(res,ensSucre);
    placeNid(res, ensNid);
    //penser à linéariser (tache pour raph à 4h du matin)
    return res;



}


void Grille::linearisePheroNid() {
    vector<Coord> res;
    for(int i=0;i< int(listePlace.size());i++){
        res.push_back(listePlace[i].get_coord());
    }
    for (auto& c: res) {
        float phero = chargePlace(c).get_pheroNid() + 1/TAILLEGRILLE;
        float n;
        for (Coord &cv: voisines(c).get_ens_coordonnees()) {
            n = max(phero, chargePlace(cv).get_pheroNid());
        }
        Place p = chargePlace(c);
        p.posePheroNid(n - 1/TAILLEGRILLE);
        rangePlace(p);
    }
}











