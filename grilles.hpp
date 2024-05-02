#include "fourmis.hpp"
#include <cmath>
extern int TAILLEGRILLE;
class Place{
    public : 
        //Constructeur
        Place(Coord c);
        //Getters et setters
        Coord get_coord() const;
        int get_numFourmi() const;
        bool get_contientSucre() const;
        bool get_contientNid() const;
        bool get_contientNid(int colonie);
        bool get_contientFourmi();
        float get_pheroSucre() const;
        float get_pheroNid() const;
        bool get_estSurUnePiste() const;
        bool get_estSurUnePiste(int colonie) const;
        void set_num(int n);
        void set_contientSucre(bool b);
        void poseSucre();
        void enleveSucre();
        void poseNid();
        void poseFourmi(Fourmis f);
        void enleveFourmi();
        void posePheroNid(float intensite, int col);
        void posePheroSucre(int intensite,int col);
        void diminuePheroSucre();
        
        
        //Méthodes
        bool estVide();
        bool estPlusProcheNid(Place p1, Place p2);
        bool estPlusLoinNid(Place p1, Place p2);
    private :
        //Attribut
        Coord coord = Coord(0,0);
        float pheroSucre;
        float pheroNid;
        int numFourmi;
        bool contientSucre;
        bool contientNid;
        int numCol; //-1 si ya rien, num colonie sinon
    };

class Grille{
    public :
        Grille(int taille);
        Place get_place(int ind);
        Place chargePlace(Coord c);
        void rangePlace(Place p);
        void linearisePheroNid();
        vector<Fourmis> listeFourmis;
    private :
        vector<Place> listePlace;

};
//Fonctions skizo
int coord_to_ind(Coord c);
void deplaceFourmi(Fourmis f, Place &p1, Place &p2);
void placeNid(Grille &g,EnsCoord c);
void placeSucre(Grille &g,EnsCoord c);


Grille initialiseGrille(vector<Fourmis> f, EnsCoord ensSucre, EnsCoord ensNid);
