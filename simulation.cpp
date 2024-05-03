#include "simulation.hpp"

void simulation(){
    //Permet de modifier la grille - Simule une itération

    //On s'occupe de toutes les fourmis.
    for(auto& f : TABFOURMI){
        Coord p2 = voisines(f.get_coord()).choixHasard();
        Place p = GRILLE.get_place(coord_to_ind(p2));

        //CONDITION 1 : f tue f2
        if(f.estVivante() and p.get_contientFourmi() and chercheFourmis(TABFOURMI,p2).get_col()!=f.get_col()){
            Fourmis tmp = chercheFourmis(TABFOURMI,p2);
            tmp.set_estVivante();
            rangeFourmi(TABFOURMI,tmp);
            Place tmpb = GRILLE.chargePlace(p2);
            tmpb.set_num(-1);
            GRILLE.rangePlace(tmpb);
        }
        //CONDITION 2 : si la fourmis cherche un sucre et p2 contient un sucre
        if(f.chercheSucre() and p.get_contientSucre()){
            f.prendSucre();
            Place p = GRILLE.chargePlace(f.get_coord());
            p.set_contientSucre(false);
            p.posePheroSucre(100,f.get_col()); //JE SAIS PAS CMB FAUT METTRE JE RETROUVE PAS
            GRILLE.rangePlace(p);

        }
    }
}