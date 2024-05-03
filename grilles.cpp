#include "grilles.hpp"
#include "doctest.h"



//----------CLASSE PLACE-------------



//Constructeurs

Place::Place(Coord c){
    coord = c;
    pheroSucre.first = 0;
    pheroSucre.second = -1;
    pheroNid.first = 0;
    pheroNid.second = -1;
    numFourmi = -1;
    contientNid = false;
    contientSucre = false;
    numCol = -1;
}


//Getters et Setters
Coord Place::get_coord() const {
    return coord;
}
int Place::get_numFourmi() const {
    return numFourmi;
}


bool Place::get_contientSucre() const {
    return contientSucre;
}

bool Place::get_contientNid() const {
    return contientNid;
}



bool Place::get_estSurUnePiste(int colonie) const {
    if(numFourmi!=-1){
        return chercheFourmis(TABFOURMI,numFourmi).get_col() == pheroSucre.second and pheroSucre.first >0;

    } return false;
}
bool Place::get_contientFourmi(){
    return numFourmi!=-1;
}
pair<float,int> Place::get_pheroNid() const {
    return pheroNid;
}


pair<int,int> Place::get_pheroSucre() const {
    return pheroSucre;
}


void Place::poseSucre(){
    contientSucre = true;
    pheroSucre.first = 100; //je garde ce que tavais mis heinn hihiihihihiihhi ALEDD
}

void Place::enleveSucre(){
    contientSucre = false;
}

void Place::poseNid(int col){
    contientNid = true;
    pheroNid.first = 1;
    pheroNid.second = col;
}


void Place::poseFourmi(Fourmis f){
    if (numFourmi == -1) {
        f.deplace(coord);
        numFourmi = f.get_num();
        numCol = f.get_col();
        //f.set_col(col);
    }
}
void Place::enleveFourmi(){
    numFourmi = -1;
    numCol = -1;
}

void Place::posePheroNid(float intensite,int col){
    //Colonie neutre : -1
    //Coder les pheroNid comme des pair pour stocker l'info ? oui.
    pheroNid.first = intensite;
    pheroNid.second = col;

}

void Place::posePheroSucre(int intensite,int col){
    pheroSucre.first = intensite;
    pheroSucre.second = col;

}

void Place::set_num(int n){
    numFourmi = n;
}

void Place::set_contientSucre(bool b){
    contientSucre = b;
}

void Place::diminuePheroSucre(){
    //Diminue par défaut de 1
    pheroSucre.first--;
}

bool Place::estVide(){
    return numFourmi==-1 and !contientNid and !contientSucre;
}

int Place::get_colFourmi() {
    return numCol;
}

//Fonctions 
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
bool Place::estPlusLoinNid(Place p1, Place p2){
    return !estPlusProcheNid(p1,p2);
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

void placeNid(Grille &g,EnsCoord c, int col){
    for(auto& elem : c.get_ens_coordonnees()){
        Place a = g.chargePlace(elem);
        a.poseNid(col); //ICI FAIRE UNE FONCTION QUI ATTRIBUE UN IND DE COL pour l'exemple j'ai mis col passer en param mais ya des soucis fin bref
        g.rangePlace(a); // on pourrais enlever la boucle pour regler le soucis mais on aurait du mal a ttribué correctement les coords au nid 
        // Solution ?? peut etre adapter tout ca avec une paire contenant a la fois l'indice de colonie et les coordonées du nid mais c trop specifique
        // pour valoir le coup. Donc a voir.
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
        tmp.poseFourmi(elem); //, elem.get_col());
        g.rangePlace(tmp);
    }
}



//Fonctions

void Grille::linearisePheroNid(int col) {
    float n;
    vector<Coord> coord;
    for(int i=0;i<TAILLEGRILLE;i++){
        for(int j=0;j<TAILLEGRILLE;j++){
            coord.push_back(Coord(i,j));
        }
    }
    for (Coord& c: coord) {
        float phero = get_place(coord_to_ind(c)).get_pheroNid().first + (1./TAILLEGRILLE);
        n = 0.0;
        EnsCoord voisins = voisines(c);
        for (Coord &cv: voisins.get_ens_coordonnees()) {
            n = max(n, max(phero, get_place(coord_to_ind(cv)).get_pheroNid().first));
        }
        Place p = chargePlace(c);
        p.posePheroNid(n - (1./TAILLEGRILLE), col);
        rangePlace(p);
    }
}

Grille initialiseGrille(vector<Fourmis> f, EnsCoord ensSucre, EnsCoord ensNid, vector<int> tabColonie){
    Grille res = Grille(TAILLEGRILLE);
    placeFourmis(res,f);
    placeSucre(res,ensSucre);
    for(int i = 0; i < int(tabColonie.size()); i++) {
        placeNid(res, ensNid, tabColonie[i]);               //Probleme de semantique ici les deux nids se voit attribué la meme colonie
        res.linearisePheroNid(tabColonie[i]);               // la derniere colonie qui est passée dans la putain de boucle de merde sortez moi de la pls
    }
    return res;
}

Coord Grille::coordAlea() {

    int i = rand()%TAILLEGRILLE;
    int j = rand()%TAILLEGRILLE;

    return Coord(i,j);
}

//Fonctions

void deplaceFourmi(Fourmis f, Place &p1, Place &p2){
    p2.poseFourmi(f); //, f.get_col());
    p1.enleveFourmi();
}


int coord_to_ind(Coord c) {
    return c.get_coordonnees().first*TAILLEGRILLE + c.get_coordonnees().second;
}



// Note : Il faudrait refaire les tests de la grille avec les colonies.

/**
TEST_CASE("Tests la classe Place") {
    Place p(Coord(0,0));

    // Tests poseSucre et get_contientSucre"
    p.poseSucre();
    CHECK(p.get_contientSucre() == true);
    p.enleveSucre();
    CHECK(p.get_contientSucre() == false);

    //Tests poseNid et get_contientNid
    

    //Tests poseFourmi et enleveFourmi
    Fourmis f(Coord(0,0),1,1);
    p.poseFourmi(f);
    CHECK_FALSE(p.estVide());
    p.enleveFourmi();
    CHECK(p.estVide());
    //Tests poseNid et get_contientNid
    p.poseNid();
    CHECK(p.get_contientNid() == true);
    

    //Tests estPlusProcheNid
    Place p1(Coord(1,1));
    Place p2(Coord(2,2));
    CHECK(p.estPlusProcheNid(p1, p2));
    CHECK_THROWS_AS(p1.estPlusProcheNid(p1, p2),invalid_argument);

}
*/

/**
TEST_CASE("Tests de la classe Grille") {
    Grille g(TAILLEGRILLE);
    vector<Fourmis> f = {Fourmis(Coord(0,0), 1,1)};
    EnsCoord ensSucre =  {{Coord(1,1),Coord(2,2)}};
    EnsCoord ensNid = {{Coord(2,2)}};

    //Tests initialiseGrille
    Grille res = initialiseGrille(f, ensSucre, ensNid);
    
    CHECK(res.get_place(coord_to_ind(ensSucre.ieme(0))).get_contientSucre() == true);
    CHECK(res.get_place(coord_to_ind(ensNid.ieme(0))).get_contientNid() == true);
    CHECK_FALSE(res.get_place(coord_to_ind(f[0].get_coord())).estVide());

    // Tests linearisePheroNid"
    //g.linearisePheroNid();
    //CHECK(g.get_place(0).get_pheroNid() == 1/20.0);
    
}
*/
