#include "coord.hpp"
int TAILLEGRILLE = 20;

//---------CLASSE COORDONNÉE--------------

//Constructeurs
Coord::Coord(int lig, int col){
    if(lig<0 or lig>=TAILLEGRILLE or col<0 or col>=TAILLEGRILLE){
        throw invalid_argument("L'indice de la ligne ou de la colonne est invalide !");
    }else{
        coordonnees.first = lig;
        coordonnees.second = col;
    }
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

//Getter - Setters ?
pair<int,int> Coord::get_coordonnees() const {
    return coordonnees;
}


//Surcharges 
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


/**
TEST_CASE("Test opérateur Coord == et != ") {
    CHECK(Coord(1,2)==Coord(1,2));
    CHECK(Coord(1,0)!=Coord(2,0));
    CHECK(Coord(3,1)!=Coord(3,2));

}*/


// --------CLASSE ENSEMBLE COORDONNÉES--------------


//Constructeurs
EnsCoord::EnsCoord(){
    ens = {{}};
}

EnsCoord::EnsCoord(vector<Coord> t){
    ens = t;
    int n = ens.size();
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            Coord a = ens[j];
            Coord b = ens[min_idx];
            if (a.get_coordonnees().first < b.get_coordonnees().first or 
                (a.get_coordonnees().first == b.get_coordonnees().first and 
                 a.get_coordonnees().second < b.get_coordonnees().second)) {
                min_idx = j;
            }
        }
        swap(ens[min_idx], ens[i]);
    }
}


TEST_CASE("Constructeur Ensemble Coord ") {
    Coord a{1,2};
    Coord b{2,1};
    vector<Coord> test = {a,b};
    CHECK(EnsCoord().get_ens_coordonnees().size()==0);
    
}

//Getter et Setters?
vector<Coord> EnsCoord::get_ens_coordonnees() const {
    return ens;
}

//Opérateurs

std::ostream& operator<< (std::ostream& out, EnsCoord a){
    a.tri();
    vector<Coord> c = a.get_ens_coordonnees();
    out << " { ";
    for(int i=0;i<int(c.size());i++){
       out << c[i] << ", "; 
    } out << "}";
    return out;
}

bool operator== (EnsCoord a,EnsCoord b){
    a.tri();
    b.tri();
    if(a.taille()!=b.taille()) return false;
    for(int i=0;i<a.taille();i++){
        if(a.ieme(i)!=b.ieme(i)) return false;
    } return true;
}

//Méthodes
void EnsCoord::tri() {
    int n = ens.size();
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            Coord a = ens[j];
            Coord b = ens[min_idx];
            if (a.get_coordonnees().first < b.get_coordonnees().first or 
                (a.get_coordonnees().first == b.get_coordonnees().first and 
                 a.get_coordonnees().second < b.get_coordonnees().second)) {
                min_idx = j;
            }
        }
        swap(ens[min_idx], ens[i]);
    }
}

TEST_CASE("Test tri"){
    vector<Coord> tmp = {Coord {3,2}, Coord {2,3}};
    vector<Coord> res = {Coord {2,3}, Coord {3,2}};
    EnsCoord test = tmp;
    EnsCoord test1 = res;
    test.tri();
    CHECK(test == test1);
}

int EnsCoord::position(Coord c) const{
    for(int i=0;i< int(ens.size());i++){
        if (ens[i] == c){
            return i;
        }
    } return -1;
}

/** Non réalisables car méthode privée
TEST_CASE("Position coordonnée"){
    Coord a{1,2};
    Coord b{2,1};
    Coord c{3,1};
    CHECK(EnsCoord{{a,b,c}}.position(a)==0);
    CHECK(EnsCoord{{a,b,c}}.position(c)==2);
    CHECK(EnsCoord{{a,b,c}}.position(Coord{4,1})==-1);
}*/

bool EnsCoord::contient(Coord c) const {
    return(position(c)!=-1);
}

TEST_CASE("Contient") {
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
    } tri();
}

TEST_CASE("ajoute") {
    EnsCoord test;
    test.ajoute(Coord{1,2});
    test.ajoute(Coord{1,2});
    CHECK(test.get_ens_coordonnees().size()==1);
}

void EnsCoord::supprime(Coord c) {
    Coord tmp(0,0);
    if(contient(c)) {
        tmp = ens[position(c)];
        ens[position(c)] = ens[ens.size()-1];
        ens[ens.size()-1] = tmp;
        ens.pop_back();
        tri();
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

TEST_CASE("taille"){
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
    CHECK(test.ieme(0)==Coord{1,1});
    CHECK(test.ieme(3)==Coord{2,2});
}

Coord EnsCoord::choixHasard() const {
    if(estVide()){
        throw invalid_argument("remplis stp");
    }
    int a = rand()%(taille());
    cout << a << endl;
    return ieme(a);
}



TEST_CASE("CHOIX HASARD"){
    EnsCoord test;
    EnsCoord t2;
    test.ajoute(Coord{2,2});
    CHECK(test.choixHasard()==Coord{2,2});
    CHECK_THROWS_AS(t2.choixHasard(),invalid_argument);

}





// ----------------Fonctions à part entière SKIZOOOOOOO !!---------------------

EnsCoord voisines(Coord c){
    EnsCoord res;
    int lig = c.get_coordonnees().first;
    int col = c.get_coordonnees().second;
    int imin = max(lig-1,0);
    int imax = min(lig+1,TAILLEGRILLE-1);
    int jmin = max(col-1,0);
    int jmax = min(col+1,TAILLEGRILLE - 1); 
    for(int i = imin; i <= imax;i++) {
            for(int j = jmin; j <= jmax ; j++){
                if(Coord(i,j)!=Coord(lig,col)){
                    res.ajoute(Coord(i,j));
                }
            }
    } return res;

}


TEST_CASE("voisines"){
    Coord a{2,1};
    Coord b{3,19};
    Coord c{0,0};
    //penser à l'ordre des vecteurs
    vector<Coord> tmp1 = {Coord(1,0), Coord(1,1),Coord(1,2), Coord(2,2), Coord(3,2), Coord(3,1), Coord(3,0), Coord(2,0) };
    EnsCoord res1 = tmp1;
    vector<Coord> tmp2 = {Coord(2, 18), Coord(2, 19), Coord(3, 18), Coord(4, 18), Coord(4, 19) };
    EnsCoord res2 = tmp2;
vector<Coord> tmp3 = {Coord(0, 1), Coord(1, 0), Coord(1, 1) };
    EnsCoord res3 = tmp3;
    CHECK(voisines(a)==res1);
    CHECK(voisines(b)==res2);
    CHECK(voisines(c)==res3);
}
