#include "simulation.hpp"


void shuffle(vector<Fourmis> &tableau) {

    // Mélange du tableau en utilisant l'algorithme de Fisher-Yates
    for (int i = tableau.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(tableau[i], tableau[j]);
    }
}

void simulation(){
    cout << "Taille tabf"<< TABFOURMI.size()<<endl;
    //Permet de modifier la grille - Simule une itération
    for(int i=0;i<TAILLEGRILLE;i++){
        for(int j=0;j<TAILLEGRILLE;j++){
            Place p = GRILLE.chargePlace(Coord(i,j));
            p.diminuePheroSucre();
        }
    }
    //Permet de changer l'ordre de deplacement des fourmis
    //shuffle(TABFOURMI);

    //On s'occupe de toutes les fourmis.
    for(auto& f : TABFOURMI){

        if(f.get_num()==-1) continue;
        cout << "Fourmis sur la table d'opération " << f.get_coord() << endl;
        bool verif = false;
        Place nidF = GRILLE.get_nid(f.get_col());
        EnsCoord p2 = voisines(f.get_coord());
        vector<Place> p;
        for(int i=0;i<int(p2.taille());i++){
            p.push_back(GRILLE.chargePlace(p2.ieme(i)));
        }
        for(auto& place : p){
        //CONDITION 1 : f tue f2

        if(f.estVivante() and place.get_contientFourmi()){
            Fourmis f2 = chercheFourmis(TABFOURMI, place.get_numFourmi());
            if(f2.get_col()!=f.get_col() and f2.estVivante()){
                cout << "est rentré dans c1" << endl;
                Place p = GRILLE.chargePlace(f.get_coord());
                p.set_num(-1);
                GRILLE.rangePlace(p);
                f2.tue();
                rangeFourmi(TABFOURMI,f2);
                f.deplace(place.get_coord());
                p = GRILLE.chargePlace(f.get_coord());
                p.poseFourmi(f);
                GRILLE.rangePlace(p);
                rangeFourmi(TABFOURMI,f);
                verif = true;
            }
            
        }if(verif) break;
        } if(verif) continue;
        //CONDITION 2 : si la fourmis cherche un sucre et p2 contient un sucre
        for(auto&place : p){
            if(f.estVivante() and f.chercheSucre() and place.get_contientSucre()){
                cout << "est rentré dans c2" << endl;
                f.prendSucre();
                place.set_contientSucre(false);
                place.posePheroSucre(255,f.get_col()); //JE SAIS PAS CMB FAUT METTRE JE RETROUVE PAS
                GRILLE.rangePlace(place);
                rangeFourmi(TABFOURMI,f);
                verif = true;
            } if(verif) break;
        }
        if(verif) continue;
        
        //CONDITION 3 la fourmi a son sucre et et il y a un nid
        for(auto&place : p){
            if( f.estVivante() and f.rentreNid() and place.get_contientNid(f.get_col())){
                cout << "est rentré dans c3" << endl;
                f.poseSucre();
                rangeFourmi(TABFOURMI,f);
                verif = true;
            }if(verif) break;
        } if(verif) continue;

        //CONDITION 4 : 
        for(auto&place : p){
            if( f.estVivante() and f.rentreNid() and place.estVide() and nidF.estPlusProcheNid(place, GRILLE.chargePlace(f.get_coord()))){
                cout << "est rentré dans c4" << endl;
                Place p = GRILLE.chargePlace(f.get_coord());
                p.set_num(-1);
                GRILLE.rangePlace(p);
                f.deplace(place.get_coord());
                p = GRILLE.chargePlace(f.get_coord());
                p.poseFourmi(f);
                p.posePheroSucre(255, f.get_col());
                GRILLE.rangePlace(p);
                rangeFourmi(TABFOURMI,f);
                verif = true;
            } if(verif) break;
        } if(verif) continue;

        //CONDITION 5
       for(auto place :p) {
        if(f.rentreNid() and place.estVide() and nidF.estPlusLoinNid(place,GRILLE.chargePlace(f.get_coord()))){
            cout << "est rentré dans c5" << endl;
            f.deplace(place.get_coord());
            rangeFourmi(TABFOURMI,f);
            verif = true;
        }if(verif) break;
        } if (verif) continue;

        //CONDITION 6
        for(auto place :p) {
        if(f.chercheSucre() and place.estVide() and place.get_estSurUnePiste(f.get_col())){
            cout << "est rentré dans c6" << endl;
            f.deplace(place.get_coord());
            rangeFourmi(TABFOURMI,f);
            verif = true;
        }if(verif) break;
        } if (verif) continue;

        
        //CONDITION 7
        Place place = GRILLE.chargePlace(voisines(f.get_coord()).choixHasard());
        if (f.chercheSucre() and place.estVide()) {
            cout << "est rentré dans c7" << endl;
            Place p = GRILLE.chargePlace(f.get_coord());
            p.set_num(-1);
            GRILLE.rangePlace(p);
            f.deplace(place.get_coord());
            p = GRILLE.chargePlace(f.get_coord());
            p.poseFourmi(f);
            GRILLE.rangePlace(p);
            rangeFourmi(TABFOURMI,f);
            verif = true;
        }
        }


    }
