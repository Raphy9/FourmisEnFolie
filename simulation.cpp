#include "simulation.hpp"

void simulation(){
    //Permet de modifier la grille - Simule une itération

    //On s'occupe de toutes les fourmis.
    for(auto& f : TABFOURMI){
        Coord p2 = voisines(f.get_coord()).choixHasard();
        Place p = GRILLE.get_place(coord_to_ind(p2));

        //CONDITION 1 : f tue f2
        if(f.estVivante() and p.get_contientFourmi() and chercheFourmis(TABFOURMI,p2).get_col()!=f.get_col()){
            cout << "est rentré dans c1" << endl;
            Fourmis tmp = chercheFourmis(TABFOURMI,p2);
            tmp.tue();
            rangeFourmi(TABFOURMI,tmp);
            p.set_num(-1);
            GRILLE.rangePlace(p);
            return;
        }
        //CONDITION 2 : si la fourmis cherche un sucre et p2 contient un sucre

        if(f.chercheSucre() and p.get_contientSucre()){
            cout << "est rentré dans c2" << endl;

            f.prendSucre();
            Place p = GRILLE.chargePlace(f.get_coord());
            p.set_contientSucre(false);
            p.posePheroSucre(100,f.get_col()); //JE SAIS PAS CMB FAUT METTRE JE RETROUVE PAS
            GRILLE.rangePlace(p);
            rangeFourmi(TABFOURMI,f);
            return;
        }
        //CONDITION 3 la fourmi a son sucre et et il y a un nid
        if(f.rentreNid() and p.get_contientNid(f.get_col())){
            cout << "est rentré dans c3" << endl;

            f.poseSucre();
            rangeFourmi(TABFOURMI,f);
            return;
        }

        //CONDITION 4 : 
        Place nidF = GRILLE.get_nid(f.get_col());
        if(f.rentreNid() and p.estVide() and nidF.estPlusProcheNid(p, GRILLE.chargePlace(f.get_coord()))){
            cout << "est rentré dans c4" << endl;

            f.deplace(p2);
            p.posePheroSucre(100,f.get_col());
            GRILLE.rangePlace(p);
            rangeFourmi(TABFOURMI,f);
            return;
            
        }

        //CONDITION 5
        if(f.rentreNid() and p.estVide() and nidF.estPlusLoinNid(p,GRILLE.chargePlace(f.get_coord()))){
            cout << "est rentré dans c5" << endl;

            f.deplace(p2);
            rangeFourmi(TABFOURMI,f);
            return;
        }

        //CONDITION 6

        if(f.chercheSucre() and p.estVide() and p.get_estSurUnePiste(f.get_col())){
            cout << "est rentré dans c6" << endl;

            f.deplace(p2);
            rangeFourmi(TABFOURMI,f);
            return;
        }
        //CONDITION 7
        if(f.chercheSucre() and p.estVide()){
            cout << "est rentré dans c7" << endl;

            f.deplace(p2);
            rangeFourmi(TABFOURMI,f);
            return;
        }


    }
}