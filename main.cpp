#include "affichage.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
int main(int argc, char **argv){
    doctest::Context context(argc,argv);
    int res = context.run();
    context.setAsDefaultForAssertsOutOfTestCases();
    if(context.shouldExit()) return res;


    vector<Fourmis> f;
    vector<Coord> s;
    vector<Coord> n = {Coord(3,3)};
    EnsCoord ensSucre = EnsCoord(s);
    EnsCoord ensNid = EnsCoord(n);
    Grille g = initialiseGrille(f,s,n);
    affiche(g,true);
    cout << g.chargePlace(Coord(1,1)).get_pheroNid();

    
}