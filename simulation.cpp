#include "simulation.hpp"

void simulation(){
    cout << "Taille tabf"<< TABFOURMI.size()<<endl;
    //Permet de modifier la grille - Simule une itération

    //On s'occupe de toutes les fourmis.
    for(auto& f : TABFOURMI){
        cout << f.get_coord()<< endl;
        Coord p2 = voisines(f.get_coord()).choixHasard();
        Place p = GRILLE.chargePlace(p2);
        Place nidF = GRILLE.get_nid(f.get_col());

        //CONDITION 1 : f tue f2
        if(f.estVivante() and p.get_contientFourmi() and chercheFourmis(TABFOURMI,f.get_num()).get_col()!=f.get_col()){
            cout << "est rentré dans c1" << endl;
            Fourmis tmp = chercheFourmis(TABFOURMI,f.get_num());
            tmp.tue();
            rangeFourmi(TABFOURMI,tmp);
            p.set_num(-1);
            GRILLE.rangePlace(p);
        }
        //CONDITION 2 : si la fourmis cherche un sucre et p2 contient un sucre

        else if(f.chercheSucre() and p.get_contientSucre()){
            cout << "est rentré dans c2" << endl;

            f.prendSucre();
            Place pl = GRILLE.chargePlace(p.get_coord());
            pl.set_contientSucre(false);
            pl.posePheroSucre(100,f.get_col()); //JE SAIS PAS CMB FAUT METTRE JE RETROUVE PAS
            GRILLE.rangePlace(pl);
            rangeFourmi(TABFOURMI,f);
        }
        //CONDITION 3 la fourmi a son sucre et et il y a un nid
        else if(f.rentreNid() and p.get_contientNid(f.get_col())){
            cout << "est rentré dans c3" << endl;
            f.poseSucre();
            rangeFourmi(TABFOURMI,f);
        }

        //CONDITION 4 : 
        
        else if(f.rentreNid() and p.estVide() and nidF.estPlusProcheNid(p, GRILLE.chargePlace(f.get_coord()))){
            cout << "est rentré dans c4" << endl;
            f.deplace(p2);
            p.posePheroSucre(100,f.get_col());
            GRILLE.rangePlace(p);
            rangeFourmi(TABFOURMI,f);
            
        }

        //CONDITION 5
        else if(f.rentreNid() and p.estVide() and nidF.estPlusLoinNid(p,GRILLE.chargePlace(f.get_coord()))){
            cout << "est rentré dans c5" << endl;

            f.deplace(p2);
            rangeFourmi(TABFOURMI,f);
        }

        //CONDITION 6

        else if(f.chercheSucre() and p.estVide() and p.get_estSurUnePiste(f.get_col())){
            cout << "est rentré dans c6" << endl;
            f.deplace(p2);
            rangeFourmi(TABFOURMI,f);
        }
        //CONDITION 7
        else if (f.chercheSucre() and p.estVide()) {
            cout << "est rentré dans c7" << endl;
            Place p = GRILLE.chargePlace(f.get_coord());
            p.set_num(-1);
            GRILLE.rangePlace(p);
            f.deplace(p2);
            p = GRILLE.chargePlace(f.get_coord());
            p.poseFourmi(f);
            GRILLE.rangePlace(p);
            rangeFourmi(TABFOURMI,f);

        }


    }
}