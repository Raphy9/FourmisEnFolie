#include "affichage.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

vector<Fourmis> TABFOURMI;
Grille GRILLE(TAILLEGRILLE,0);


int main(int argc, char **argv){
    doctest::Context context(argc,argv);
    int res = context.run();
    context.setAsDefaultForAssertsOutOfTestCases();
    if(context.shouldExit()) return res;
    
    
    //10 fourmis appartenant a la colonie i a une position aléatoire
    for(int i = 0; i < 2; i++) { //maximum 2 colonie pour pas exploser l'affichage
        for(int k = 0 ; k < 10; k++) {
            TABFOURMI.push_back(Fourmis(GRILLE.coordAlea(),i,i));
        }
    }
    
    //Nombre de sucre
    vector<Coord> s;
    for(int i = 0; i < 150 ; i++) {
        s.push_back(GRILLE.coordAlea());
    }
    
    //Nombre de nid
    vector<Coord> n;
    for(int i = 0; i < 2 ; i++) {
        n.push_back(GRILLE.coordAlea());
    }
    
    
    //Constructeurs
    EnsCoord ensSucre = s;
    EnsCoord ensNid = n;

   

    GRILLE = initialiseGrille(TABFOURMI,ensSucre,ensNid);

    //Affichage
    affiche(GRILLE,TABFOURMI,false);
    
    
}