#include "grilles.hpp"
#include "doctest.h"



//----------CLASSE PLACE-------------



//Constructeurs

Place::Place(Coord c,int nbCol){
    coord = c;
    numFourmi = -1;
    contientNid = false;
    contientSucre = false;
    for(int i=0;i<nbCol;i++){
        pair<float,int> tmp;
        tmp.first = 0;
        tmp.second = i;
        pair<int,int> tmpb;
        tmpb.first =0;
        tmpb.second = i;
        pheroNid.push_back(tmp);
        pheroSucre.push_back(tmpb);
    }
}


//Getters
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

bool Place::get_contientNid(int col) const {
    return pheroNid[col].first==1;
}


bool Place::get_estSurUnePiste(int colonie) const {
    if(numFourmi!=-1){
        int tmp = chercheFourmis(TABFOURMI,numFourmi).get_col();
        return pheroSucre[tmp].first>0;

    } return false;
}
bool Place::get_contientFourmi(){
    return numFourmi!=-1;
}

vector<pair<float,int>> Place::get_pheroNid() const{
    return pheroNid;
}
pair<float,int> Place::get_pheroNid(int col) const {
    return pheroNid[col];
}


pair<int,int> Place::get_pheroSucre(int col) const {
    return pheroSucre[col];
}

bool Place::estVide(){
    return numFourmi==-1 and !contientNid and !contientSucre;
}

int Place::getIndColNid(){
    for(int i=0; i < int(pheroNid.size());i++){
        if(pheroNid[i].first>=float(1)) return i;
    } return -1;
}

//Setters

void Place::poseSucre(){
    contientSucre = true;
}

void Place::poseSucre(Fourmis &f){
    f.poseSucre();
    rangeFourmi(TABFOURMI,f);
    contientSucre = true;
    pheroSucre[f.get_col()].first = 100; //je garde ce que tavais mis heinn hihiihihihiihhi ALEDD
}



void Place::enleveSucre(){
    contientSucre = false;
}

void Place::poseNid(int col){
    contientNid = true;
    pheroNid[col].first = 1;
    pheroNid[col].second = col;
}


void Place::poseFourmi(Fourmis f){
    if (numFourmi == -1) {
        f.deplace(coord);
        numFourmi = f.get_num();
        //f.set_col(col);
    }
}
void Place::enleveFourmi(){
    numFourmi = -1;
}

void Place::posePheroNid(float intensite,int col){
    pheroNid[col].first = intensite;
    pheroNid[col].second = col;

}

void Place::posePheroSucre(int intensite,int col){
    pheroSucre[col].first = intensite;
    pheroSucre[col].second = col;

}

void Place::set_num(int n){
    numFourmi = n;
}

void Place::set_contientSucre(bool b){
    contientSucre = b;
}

void Place::diminuePheroSucre(int col){
    pheroSucre[col].first--;
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

TEST_CASE("Modification de l'état de la place") {
    Coord b(1, 2);
    Place p2(b, 3);
    p2.poseSucre();
    CHECK(p2.get_contientSucre());
    p2.enleveSucre();
    CHECK_FALSE(p2.get_contientSucre());
    p2.poseNid(0);
    CHECK(p2.get_contientNid(0));
}

TEST_CASE("Phéromones") {
    Coord c(1, 2);
    Place p3(c, 3);
    p3.posePheroNid(0.5, 0);
    p3.posePheroNid(0.5, 1);
    CHECK(p3.get_pheroNid(0).first == 0.5);
    CHECK(p3.get_pheroNid(1).first == 0.5);
    p3.diminuePheroSucre(0);
    p3.diminuePheroSucre(1);
    CHECK(p3.get_pheroSucre(0).first == -1); //parce que c'est 0 par défaut
    CHECK(p3.get_pheroSucre(1).first == -1);
}

TEST_CASE("Est plus proche est plus loin") {
    Coord d(1, 2);
    Place p4(d, 3);
    p4.poseNid(0);
    Place p5(Coord(2, 3), 3), p6(Coord(4, 5), 3);
    CHECK(p4.estPlusProcheNid(p5, p6));
    CHECK_FALSE(p4.estPlusLoinNid(p5, p6));
    Place p7(d, 3), p8(d, 3);
    CHECK_THROWS_AS(p7.estPlusProcheNid(p7, p8), invalid_argument);
}

TEST_CASE("Est vide tests") {
    Coord e(1, 2);
    Place p9(e, 3);

    // Cas où la place est initialement vide
    CHECK(p9.estVide() == true);

    // Cas où une fourmi est présente
    p9.set_num(1);
    CHECK(p9.estVide() == false);
    p9.enleveFourmi();

    // Cas où du sucre est présent
    p9.poseSucre();
    CHECK(p9.estVide() == false);
    p9.enleveSucre();

    // Cas où un nid est présent
    p9.poseNid(0);
    CHECK(p9.estVide() == false);

    // Cas où des phéromones de nid sont présentes
    p9.posePheroNid(1.0, 0);
    CHECK(p9.estVide() == false);

    // Cas où des phéromones de sucre sont présentes
    p9.posePheroSucre(100, 0);
    CHECK(p9.estVide() == false);
    p9.diminuePheroSucre(0);
    CHECK(p9.estVide() == false);

}


//CLASSE GRILLE

// Constructeurs
Grille::Grille(int taille, int nbCol){
    for(int i = 0; i < taille; i++) {
        for(int j = 0; j < taille; j++) {
            listePlace.push_back(Place(Coord(i,j),nbCol));
        }
    }
}



// Getters Setters

Place Grille::chargePlace(Coord c) {
    for(auto& elem : listePlace){
        if(elem.get_coord()==c){
            return elem;
        }
    } throw invalid_argument("place inexistante");
}


TEST_CASE("Charge Place"){
    Grille g(5,3);
    Coord a = g.chargePlace(Coord(3,3)).get_coord();
    CHECK( a == Coord(3,3));
    CHECK(g.chargePlace(Coord(0,0)).get_pheroNid().size()==3);
}


void Grille::rangePlace(Place p) {
    for(int i=0;i<int(listePlace.size());i++){
        if(listePlace[i].get_coord() == p.get_coord()){
            listePlace[i] = p;
            return;
        }
    } throw invalid_argument("Cette place n'existe pas !!");
}

TEST_CASE("Tests rangePlace"){
    Grille g(5,3);
    Place p = g.chargePlace(Coord(1,2));
    p.set_contientSucre(true);
    g.rangePlace(p);
    CHECK(g.chargePlace(Coord(1,2)).get_contientSucre());
    p.set_num(2);
    CHECK(g.chargePlace(Coord(1,2)).get_numFourmi()!=2);
    g.rangePlace(p);
    CHECK(g.chargePlace(Coord(1,2)).get_numFourmi()==2);

}





void Grille::placeFourmis(vector<Fourmis> f){
    for(auto& elem : f){
        cout << "heheheheh" << endl;
        Coord a = elem.get_coord();
        Place tmp = chargePlace(a);
        tmp.poseFourmi(elem); 
        //rangePlace(tmp);
    }
}

TEST_CASE("Place fourmis"){
    vector<Fourmis> f;
    f.push_back(Fourmis(Coord(1,2),0,1));
    Grille g(5,3);
    g.placeFourmis(f);
    CHECK(1==1);
    //CHECK(g.chargePlace(Coord(1,2)).get_contientFourmi());
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
    for(int i=0;i<TAILLEGRILLE;i++){
        for (Coord& c: coord) {
            if(!chargePlace(c).get_contientNid()){
                float phero = chargePlace(c).get_pheroNid(col).first + (1./TAILLEGRILLE);
                n = 0.0;
                EnsCoord voisins = voisines(c);
                for (Coord &cv: voisins.get_ens_coordonnees()) {
                    n = max(n, max(phero, chargePlace(cv).get_pheroNid(col).first));
                }
                Place p = chargePlace(c);
                p.posePheroNid(n - (1./TAILLEGRILLE), col);
                rangePlace(p);
            }
        }
    }
}

Place Grille::get_nid(int col){
    for(auto& elem :listePlace){
        if (elem.get_contientNid(col)) return elem;
    } throw invalid_argument("Nom de colonie invalide");
}

TEST_CASE("Test de la fonction get_nid") {
    Grille grille(20, 2); 

    // Nid valide
    Place tmp = grille.chargePlace(Coord(5,5));
    tmp.poseNid(0);
    grille.rangePlace(tmp);
    Place res = grille.get_nid(0);
    CHECK(res.get_coord() == tmp.get_coord());


    // Nid invalide
    CHECK_THROWS_AS(grille.get_nid(3), invalid_argument);
}

Grille initialiseGrille(vector<Fourmis> f, EnsCoord ensSucre, EnsCoord ensNid){
    Grille res = Grille(TAILLEGRILLE, ensNid.taille());
    for(auto& f : f){
        Place tmp = res.chargePlace(f.get_coord());
        tmp.poseFourmi(f);
        res.rangePlace(tmp);
        
    }
    for(int i=0; i<ensSucre.taille();i++){
        Place tmp = res.chargePlace(ensSucre.ieme(i));
        tmp.poseSucre();
        res.rangePlace(tmp);
    }
    for(int i = 0; i < ensNid.taille(); i++) {
        Place a = res.chargePlace(ensNid.ieme(i));
        a.poseNid(i);
        res.rangePlace(a); 
        res.linearisePheroNid(i);
        vector<pair<float,int>> t = res.chargePlace(ensNid.ieme(i)).get_pheroNid();
        /**
        for(auto& elem : t){
            cout << "pheros col"<< endl ;
            cout << elem.first << " " << elem.second << endl;
        } cout << "-------" << endl; */
        
    }
    cout << "Nombre de fourmis : " << f.size() << endl;
    cout << "Nombre de sucre : " << ensSucre.taille() << endl;
    cout << "Nombre de nid/colonie : " << ensNid.taille() << endl;
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


// TEST DE LA CLASSE PLACE

TEST_CASE("Getter Setter") {
    Coord a(1, 2);
    Place p1(a, 3);
    CHECK(p1.get_coord() == a);
    CHECK_FALSE(p1.get_contientNid());
    CHECK_FALSE(p1.get_contientSucre());
    for (int i = 0; i < 3; ++i) {
        CHECK(p1.get_pheroNid(i).first == 0);
        CHECK(p1.get_pheroNid(i).second == i);
        CHECK(p1.get_pheroSucre(i).first == 0);
        CHECK(p1.get_pheroSucre(i).second == i);
    }
    Fourmis f = Fourmis(Coord(1,1), 5, 0);
    p1.poseFourmi(f);
    CHECK(p1.get_numFourmi() == 5);
}







TEST_CASE("Test de la fonction coordAlea") {
    Grille grille(20, 2); // Supposons 2 colonies
    Coord res = grille.coordAlea();
    CHECK(res.get_coordonnees().first >= 0);
    CHECK(res.get_coordonnees().first < 20);
    CHECK(res.get_coordonnees().second >= 0);
    CHECK(res.get_coordonnees().second < 20);
}

TEST_CASE("Test de la fonction deplaceFourmi") {
    Grille grille(20, 2); 
    Fourmis f(Coord(0,0),3,0);
    Place p1 = grille.chargePlace(Coord(0,0));
    Place p2 = grille.chargePlace(Coord(1,1));
    deplaceFourmi(f, p1, p2);
    CHECK(p1.get_contientFourmi() == false);
    CHECK(p2.get_contientFourmi() == true);
}

TEST_CASE("Test de la fonction coord_to_ind") {
    Coord c(3, 4);
    int ind = coord_to_ind(c);
    CHECK(ind == 3*TAILLEGRILLE+4);
}


