#include "simulation.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


vector<Fourmis> TABFOURMI;
Grille GRILLE(TAILLEGRILLE,0);
int compteurFichier = 0;

int donneIndFourmis(vector<Fourmis> tabF) {
    return tabF.size();
}




int main(int argc, char **argv){
    doctest::Context context(argc,argv);
    int res = context.run();
    context.setAsDefaultForAssertsOutOfTestCases();
    if(context.shouldExit()) return res;
    
    
    
    //10 fourmis appartenant a la colonie i a une position aléatoire
    for(int i = 0; i < 2; i++) { //maximum 2 colonie pour pas exploser l'affichage
        for(int k = 0 ; k < 5; k++) {
            bool verif = false;
            while(not verif){
                Coord c = GRILLE.coordAlea();
                if (GRILLE.chargePlace(c).estVide()){
                    verif = true;
                    TABFOURMI.push_back(Fourmis(c,donneIndFourmis(TABFOURMI),i));
                }
            }
            
        }
    }
    
    //Nombre de sucre
    vector<Coord> s;
    for(int i = 0; i < 5 ; i++) {
        bool verif = false;
        while(not verif){
            Coord c = GRILLE.coordAlea();
            if(GRILLE.chargePlace(c).estVide()){
                verif = true;
                 s.push_back(GRILLE.coordAlea());

            }
        }
       
    }
    
    //Nombre de nid
    vector<Coord> n;
    for(int i = 0; i < 2 ; i++) {
        bool verif = false;
        while(not verif){
            Coord c = GRILLE.coordAlea();
            if(GRILLE.chargePlace(c).estVide()){
                n.push_back(GRILLE.coordAlea());
                verif = true;
            }
        }
        
    }
    
    
    //Constructeurs
    EnsCoord ensSucre = s;
    EnsCoord ensNid = n;

   

    GRILLE = initialiseGrille(TABFOURMI,ensSucre,ensNid);
    
    for(auto elem : TABFOURMI) {
        cout << "colonie: "<< elem.get_col() << "numeroFourmi: " << elem.get_num() << endl;
    }
    affiche(GRILLE,TABFOURMI,false);
    //Affichage
    /**
    for(int i=0;i<10;i++){
        affiche(GRILLE,TABFOURMI,false);
        simulation();
        

    }
*/
    
    
    
}