
#include "affichage.hpp"
#include <iostream>     // pour cout
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>
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
            if(tmp.get_numFourmi()!=-1){
                fic << 21 << " " << 36 << " " << 149 << "    ";
            }
            else if(tmp.get_contientSucre()){
                fic << 255 << " " << 255 << " " << 255 << "    ";

            } else if(tmp.get_contientNid()){
                fic << 254 << " " << 231 << " " << 71 << "    ";

            } else if(tmp.get_pheroNid() and debug){
                fic << 254 << " " << 231 - int(tmp.get_pheroNid())*5  << " " << 71 << "    ";
            } else if(tmp.get_pheroSucre() and debug){
                fic << 255 - int(tmp.get_pheroSucre())*5 << " " << 255 << " "<< 255 << "    ";
            }
        } fic << endl;
    }



}


