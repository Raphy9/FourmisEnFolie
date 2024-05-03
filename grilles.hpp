#include "fourmis.hpp"
#include <cmath>
extern int TAILLEGRILLE;
extern vector<Fourmis> TABFOURMI;
class Place{
    public : 
        //Constructeur
        Place(Coord c,int nbCol);
        //Getters et setters
        Coord get_coord() const;
        int get_numFourmi() const;
        bool get_contientSucre() const;
        bool get_contientNid() const;
        bool get_contientNid(int colonie);
        bool get_contientFourmi();
        pair<int,int> get_pheroSucre(int col) const;
        pair<float,int>  get_pheroNid(int col) const;
        int getIndColNid();
        bool get_estSurUnePiste(int colonie) const;
        void set_num(int n);
        void set_contientSucre(bool b);
        void poseSucre();
        void poseSucre(Fourmis &f);
        
        void enleveSucre();
        void poseNid(int col);
        void poseFourmi(Fourmis f);
        void enleveFourmi();
        void posePheroNid(float intensite, int col);
        void posePheroSucre(int intensite,int col);
        void diminuePheroSucre(int col);
        
        
        //Méthodes
        bool estVide();
        bool estPlusProcheNid(Place p1, Place p2);
        bool estPlusLoinNid(Place p1, Place p2);
    private :
        //Attribut
        Coord coord = Coord(0,0);
        vector<pair<int,int>> pheroSucre;
        vector<pair<float,int>> pheroNid; //intensite,colonie
        int numFourmi;
        bool contientSucre;
        bool contientNid;
    };

class Grille{
    public :
        Grille(int taille, int nbCol);
        Place get_place(int ind);
        Place chargePlace(Coord c);
        void rangePlace(Place p);
        void linearisePheroNid(int col);
        vector<Fourmis> listeFourmis;
        Coord coordAlea();
    private :
        vector<Place> listePlace;

};
//Fonctions skizo
int coord_to_ind(Coord c);
void deplaceFourmi(Fourmis f, Place &p1, Place &p2);
void placeNid(Grille &g,EnsCoord c, int col);
void placeSucre(Grille &g,EnsCoord c);
void placeFourmis(Grille &g, vector<Fourmis> f);

Grille initialiseGrille(vector<Fourmis> f, EnsCoord ensSucre, EnsCoord ensNid);
