#include "simulation.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

//pour convertir en gif : convert -scale 300 -delay 10 img*.ppm movie.gif


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
    srand(time(0));
    
    
    //10 fourmis appartenant a la colonie i a une position aléatoire
    for(int i = 0; i < 2; i++) { //maximum 2 colonie pour pas exploser l'affichage
        for(int k = 0 ; k < 8; k++) {
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
    for(int i = 0; i < 20 ; i++) {
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
    vector<pair<float,int>> t1 = GRILLE.chargePlace(Coord(1,1)).get_pheroNid();
    vector<pair<float,int>> t2 = GRILLE.chargePlace(Coord(5,5)).get_pheroNid();
    /**
    cout << "T1" << GRILLE.chargePlace(Coord(1,1)).get_contientNid(0) << endl;
    cout << "T2" << GRILLE.chargePlace(Coord(5,5)).get_contientNid(1) << endl;
    for(int i=0; i<int(t1.size());i++){
        cout << "T1 " << t1[i].first  << " " << t1[i].second << endl;
        cout << "T2 " << t2[i].first  << " " << t2[i].second << endl;

    }*/



    /**
    for(auto elem : TABFOURMI) {
        cout << "colonie: "<< elem.get_col() << "numeroFourmi: " << elem.get_num() << endl;
    }*/
    //affiche(GRILLE,TABFOURMI,true);
    //Affichage

    
    for(int i=0;i<500;i++){
        cout << i << "eme iteration" << endl;
        affiche(GRILLE,TABFOURMI,true);
        simulation();
        

    }
    

   
    
    
}