#include "affichage.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

vector<Fourmis> TABFOURMI;
vector<int> TABCOLONIE;

int main(int argc, char **argv){
    doctest::Context context(argc,argv);
    int res = context.run();
    context.setAsDefaultForAssertsOutOfTestCases();
    if(context.shouldExit()) return res;

    Grille g(TAILLEGRILLE);
    
    //10 fourmis appartenant a la colonie i a une position aléatoire
    for(int i = 0; i < 2; i++) { //maximum 2 colonie pour pas exploser l'affichage
        for(int k = 0 ; k < 10; k++) {
            TABFOURMI.push_back(Fourmis(g.coordAlea(),i,i));
        }
    }
    
    //Nombre de sucre
    vector<Coord> s;
    for(int i = 0; i < 250 ; i++) {
        s.push_back(g.coordAlea());
    }

    //Nombre de nid
    vector<Coord> n;
    for(int i = 0; i < 2 ; i++) {
        n.push_back(g.coordAlea());
        TABCOLONIE.push_back(i);
    }
    //for(auto elem : n) cout << elem << endl;

    //Constructeurs
    EnsCoord ensSucre = s;
    EnsCoord ensNid = n;
    g = initialiseGrille(TABFOURMI,ensSucre,ensNid,TABCOLONIE);

    //Affichage
    affiche(g,false);
    //cout << g.chargePlace(Coord(1,1)).get_pheroNid();

    
}