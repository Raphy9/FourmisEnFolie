
#include "affichage.hpp"
#include <iostream>     // pour cout
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>
#include "doctest.h"
using namespace std;
// variable globale permettant de creer des noms de fichiers differents
int compteurFichier = 0;
void affiche(Grille g,bool debug){
    //Code RGB Fourmi col1 : rgb(21, 36, 149)
    ostringstream filename;
    // creation d'un nouveau nom de fichier de la forme img347.ppm
    filename << "img" << setfill('0') << setw(3) << compteurFichier << ".ppm";
    compteurFichier++;
    cout << "Ecriture dans le fichier : " << filename.str() << endl;
    // ouverture du fichier
    ofstream fic(filename.str(), ios::out | ios::trunc);
    // ecriture de l'entete
    fic << "P3" << endl
        << TAILLEGRILLE << " " << TAILLEGRILLE << " " << endl
        << 255 << " " << endl;
    //Ecriture pixel
    for(int i=0;i<TAILLEGRILLE;i++){
        for(int j=0;j<TAILLEGRILLE;j++){
            Place tmp = g.chargePlace(Coord(i,j));
            /**if(tmp.get_numFourmi()!=-1){
                fic << 21 << " " << 36 << " " << 149 << "    ";  //NE PAS FAIRE CA T ZINZIN si ya pas de fourmis on ira dans le cas qu'est tout en bas
            }*/
            // début affichage fourmis
            // COND A MODIFIER pour 2 colonie differentes
            if(tmp.get_colFourmi() == 0) { // Ne pas mettre de else
                //cout << tmp.get_colFourmi() << endl;
                fic << 158 << " " << 250 << " " << 250 << "    "; // bleu clair cyan je sais pas trop
            } else if (tmp.get_colFourmi() == 1) {
                //cout << tmp.get_colFourmi() << endl;
                fic << 243 << " " << 97 << " " << 255 << "    "; // rose
            }
            // fin 
            if(tmp.get_contientNid() and tmp.get_pheroNid().second == 0){ //Bleu Foncé
                fic << 10 << " " << 94 << " " << 218 << "    ";
            } else if(tmp.get_contientNid() and tmp.get_pheroNid().second == 1){ //Rouge
                fic << 255 << " " << 0 << " " << 0 << "    ";
            }
            else if(tmp.get_contientSucre()){
                fic << 255 << " " << 255 << " " << 255 << "    "; // blanc

            }  else if(tmp.get_pheroNid().first>0 and debug){
                fic << 254 << " " << 200 - (1 -tmp.get_pheroNid().first)*100  << " " << 71 << "    ";
            } else if(tmp.get_pheroSucre().first>0 and debug){
                fic << 210 << " " << 210  << " "<< 210 << "    ";
            }else{
                fic << 18 << " " << 12 << " " << 60 << "    ";
            }
        } fic << endl;
    } fic.close();



}


