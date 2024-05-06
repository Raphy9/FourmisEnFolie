
#include "affichage.hpp"
#include <iostream>     // pour cout
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>
#include "doctest.h"
using namespace std;


vector<vector<vector<int>>> COULEUR =  {{{255,0,0},{255,130,130},{255,198,130},{255,168,168}},{{38,128,0},{175,255,125},{90,200,160},{215,255,190}},{{0,170,255},{54,121,155},{125,158,255},{125,212,255}},{{76,0,255},{161,122,253},{191,122,253},{210,192,253}}};



// variable globale permettant de creer des noms de fichiers differents
//11 colonies max cest assez !! {255,153,0}
void affiche(Grille g, vector<Fourmis> tabf, bool debug){ //Code RGB Fourmi col1 : rgb(21, 36, 149)
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
            // début affichage fourmis
            if(tmp.get_contientFourmi() and tmp.get_numFourmi()!=-1){
                int indf = chercheFourmis(tabf,tmp.get_numFourmi()).get_col();
                int intt = chercheFourmis(tabf,tmp.get_numFourmi()).get_type();
                fic << COULEUR[indf][1+1-intt][0] << " " << COULEUR[indf][1+1-intt][1] << " " << COULEUR[indf][1+1-intt][2] << "    ";
            } 
            else if(tmp.get_contientNid()){
                int colonie = tmp.getIndColNid();
                int indn = tmp.get_pheroNid(colonie).second;
                fic << COULEUR[indn][0][0] << " " << COULEUR[indn][0][1] << " " << COULEUR[indn][0][2] << "    ";

            }
            else if(tmp.get_nbSucre()>0){
                fic << 255 - (5- tmp.get_nbSucre())*31 << " " << 255 - (5- tmp.get_nbSucre())*31  << " " << 255 - (5- tmp.get_nbSucre())*31 << "    "; 

            }  
            else if (tmp.get_maxPheroSucre().first >240){
                pair<int,int> ph = tmp.get_maxPheroSucre();
                fic << COULEUR[ph.second][3][0] + ph.first/10 << " " << COULEUR[ph.second][3][1] + ph.first/10 << " " << COULEUR[ph.second][3][2]<<"    ";

            }
            else if(tmp.get_pheroNid(0).first>0 and debug){
                fic << 254 << " " << 200 - (1 -tmp.get_pheroNid(0).first)*100  << " " << 71 << "    ";
            }else{
                fic << 18 << " " << 12 << " " << 60 << "    ";
            }
        } fic << endl;
    } fic.close();
}


