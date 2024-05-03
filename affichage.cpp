
#include "affichage.hpp"
#include <iostream>     // pour cout
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>
#include "doctest.h"
using namespace std;



// variable globale permettant de creer des noms de fichiers differents
//11 colonies max cest assez !! {255,153,0}
vector<vector<vector<int>>> COULEUR = {{{255,0,0},{255,80,80},{255,168,168}},{{255,150,0},{255,255,99},{255,255,176}},{{100,255,0},{155,255,90},{205,255,172}},{{0,255,200},{115,254,224},{191,255,241}},{{0,175,255},{111,208,252},{178,230,254}},{{0,0,255},{97,97,255},{178,178,254}},{{255,0,150}, {252,93,187},{254,169,220}}};
//Logique : plus foncé : nid, moyen clair : fourmis, clair : pheromones
//Chaque colonie possède sa propre couleur
void affiche(Grille g, vector<Fourmis> tabf, bool debug){
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
            // début affichage fourmis
            // COND A MODIFIER pour 2 colonie differentes
            if(tmp.get_contientFourmi() and tmp.get_numFourmi()!=-1){
                int indf = chercheFourmis(tabf,tmp.get_numFourmi()).get_col();
                fic << COULEUR[indf][1][0] << " " << COULEUR[indf][1][1] << " " << COULEUR[indf][1][2] << "    ";

            } 
            else if(tmp.get_contientNid()){
                int colonie = tmp.getIndColNid();
                int indn = tmp.get_pheroNid(colonie).second;
                fic << COULEUR[indn][0][0] << " " << COULEUR[indn][0][1] << " " << COULEUR[indn][0][2] << "    ";

            }
            else if(tmp.get_contientSucre()){
                fic << 255 << " " << 255 << " " << 255 << "    "; // blanc

            }  
            else if(tmp.get_pheroNid(0).first>0 and debug){
                fic << 254 << " " << 200 - (1 -tmp.get_pheroNid(0).first)*100  << " " << 71 << "    ";
            } 
            else if(tmp.get_pheroSucre(0).first>0 and debug){
                fic << 210 << " " << 210  << " "<< 210 << "    ";
            }else{
                fic << 18 << " " << 12 << " " << 60 << "    ";
            }
        } fic << endl;
    } fic.close();



}


