#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FICRESERVB "data/reservations.bin"
#define FICRESERV "data/reservations.txt"
#define FICJEUB "data/jeu.bin"
#define FICJEU "data/jeu.txt"
#define FICADHB "data/adherents.bin"
#define FICADH "data/adherents.txt"
#define FICEMPB "data/emprunts.bin"
#define FICEMP "data/emprunts.txt"

#define VARCHAR char

/*------------------------------------------------Structures------------------------------------------------*/

typedef enum{
    FAUX,VRAI
}Booleen;

typedef struct{
    int jour;
    int mois;
    int annee;
}Date;

typedef enum{
    construction,
    plateau,
    tuile,
    carte,
    logique
}TypeJeu;

typedef struct{
    char IDjeu[6];
    char nomJeu[40];
    TypeJeu type;
    int nbEx;
}Jeu;

typedef struct maillonJeu{
    Jeu j;
    struct maillonJeu *suiv;
}MaillonJeu, *ListeJeux;

typedef struct{
    int IDemprunt;
    int IDAdherent;
    char IDjeu[6];
    Date dateEmp;
}Emprunt;

typedef struct maillonEmp{
    Emprunt e;
    struct maillonEmp *suiv;
}MaillonEmprunts, *ListeEmprunts;

typedef struct{
    int IDresa;
    int IDadherent;
    char IDjeu[6];
    Date dateRes;
}Reservation;

typedef struct maillonRes{
    Reservation r;
    struct maillonRes *suiv;
}MaillonReservations, *ListeReservations;

typedef enum{
    Mme,Mr
}Sexe;

typedef struct{
    int IDAdherent;
    Sexe civilite;
    char nom[21];
    char prenom[21];
    Date dateInscription;
    int nbEmpCours;
}Adherent;

typedef struct maillonAdh{
    Adherent a;
    struct maillonAdh *suiv;
}MaillonAdherents, *ListeAdherents;

/*------------------------------------------------Divers------------------------------------------------*/
Booleen LAestVide(ListeAdherents LA);
ListeAdherents LAnouvList(void);
Booleen adhPlus1An(Adherent a,Date d);

Booleen LEestVide(ListeEmprunts LE);
ListeEmprunts LEnouvList(void);
Booleen empruntJeuPlus1Mois(ListeEmprunts LE,int numAdh,Date d);

Booleen datePlusAncienne(Date e1, Date e2);

Booleen LJestVide(ListeJeux LJ);
ListeJeux LJnouvList(void);
ListeJeux LJtri(ListeJeux LJ);

Booleen LRestvide(ListeReservations LR);
ListeReservations LRnouvList(void);

void globale(void);
/*------------------------------------------------Saisie------------------------------------------------*/
void saisieNomPrenom(char *nom,char *prenom);
Adherent saisieAdherent(int *prochainNumAdh);
int saisieNumAdh(ListeAdherents LA);
int saisieNumRes(ListeReservations LR,ListeAdherents LA,ListeJeux LJ);
int saisieNnumEmp(ListeEmprunts LE);
char demandeSiNouveau(void);
char demandeON(char *message);
char saisieSexe(void);

Reservation saisieReserv(ListeAdherents *LA,ListeJeux LJ,int *prochainNumAdh);

Jeu saisieJeu(void);
void saisieIDJeu(ListeJeux LJ,char IDjeu[]);
char* RenvoieTypeJeu(Jeu j);

Date saisieDate(char c[]);
Booleen verifDate(Date d);

int choixMenu(void);
/*------------------------------------------------Ajout------------------------------------------------*/
ListeAdherents LAinsererEnTete(ListeAdherents LA,Adherent a);
ListeAdherents LAinserer(ListeAdherents LA,Adherent a);

ListeReservations LRinsererEnTete(ListeReservations LR, Reservation r);
ListeReservations LRinserer(ListeReservations LR, Reservation r);
ListeReservations ajouterReservation(ListeReservations LR,int *prochainNumRes,ListeAdherents *LA,int *prochainNumAdh,ListeJeux LJ);
ListeReservations reservationParEmprunt(ListeReservations LR,int *prochainNumRes,ListeAdherents *LA,int *prochainNumAdh,ListeJeux LJ);

ListeEmprunts LEinsererEnTete(ListeEmprunts LE,Emprunt a);
ListeEmprunts LEinserer(ListeEmprunts LE,Emprunt a);
ListeEmprunts ajouterEmprunt(ListeEmprunts LE, ListeAdherents *LA,int *prochainNumAdh,ListeJeux LJ, int *prochainNumEmp,ListeReservations *LR,int *prochainNumRes);

ListeJeux LJinsererEnTete(ListeJeux LJ,Jeu j);

/*------------------------------------------------Suppression------------------------------------------------*/
ListeAdherents LAsupprimerEnTete(ListeAdherents LA);
ListeAdherents LAsupprimer(ListeAdherents LA,int ID);
ListeAdherents supprimeListeAdherents(ListeAdherents LA);


ListeReservations LRsupprimerEnTete(ListeReservations LR);
ListeReservations LRsupprimer(ListeReservations LR, int numRes);
ListeReservations supprimerReserv(ListeReservations LR,ListeAdherents LA, ListeJeux LJ);
ListeReservations supprimeListeReservations(ListeReservations RE);

ListeEmprunts LEsupprimerEnTete(ListeEmprunts LE);
ListeEmprunts LEsupprimer(ListeEmprunts LE,int ID);
ListeEmprunts supprimeListeEmprunts(ListeEmprunts LE);

ListeJeux LJsupprimerEnTete(ListeJeux LJ);
ListeJeux LJsupprimer(ListeJeux LJ,char ID[]);
ListeJeux supprimeListeJeux(ListeJeux LJ);

ListeJeux retourJeu(ListeJeux LJ,ListeReservations *LR,int *prochainNumRes,ListeEmprunts *LE,int *prochainNumEmp,ListeAdherents *LA);
/*------------------------------------------------Recherche------------------------------------------------*/
Booleen rechAdh(ListeAdherents LA,int numAdh);
ListeAdherents positionAdherent(ListeAdherents LA,int numAdh);

ListeReservations positionReserv(ListeReservations LR,int numRes);
ListeReservations rechReservParIDjeu(ListeReservations LR,char idJeu[]);

ListeEmprunts positionEmprunt(ListeEmprunts LE,int noEmp);

ListeJeux positionJeu(ListeJeux LJ,char jeu[]);
ListeJeux LJrechMax(ListeJeux LJ);
/*------------------------------------------------Affichage------------------------------------------------*/
char* RenvoieSexe(Adherent a);
void afficherAdherent(Adherent a);
void afficherListeAdherents(ListeAdherents LA);

void afficherReserv(ListeReservations LR,ListeAdherents LA, ListeJeux LJ);
void afficherListeReservations(ListeReservations LR,ListeAdherents LA,ListeJeux LJ);
void afficheReservJeu(ListeReservations LR,ListeAdherents LA, ListeJeux LJ, char IDjeu[]);

void afficherEmprunt(ListeEmprunts LE,ListeAdherents LA,ListeJeux LJ);
void afficherListeEmprunts(ListeEmprunts LE,ListeAdherents LA,ListeJeux LJ);
void afficherEmpruntsAdh(ListeEmprunts LE,ListeAdherents LA,ListeJeux LJ,int numAdh);

void afficherJeux(ListeJeux LJ);
void afficherJeuxDispo(ListeJeux LJ);
void afficherListeJeux(ListeJeux LJ);

void afficheDate(Date d);
/*------------------------------------------------Chargement------------------------------------------------*/
Adherent lireAdherents(FILE *flot);
ListeAdherents LAchargFic(char nomFic[],int *prochainNumAdh);

Reservation lireReserv(FILE *flot);
ListeReservations LRchargFic(char nomFic[],int *prochainNumRes);

Emprunt lireEmprunt(FILE *flot);
ListeEmprunts LEchargFic(char nomFic[],int *prochainNumEmp);

Jeu lireJeu(FILE *flot);
ListeJeux LJchargFic(char nomFic[]);
/*------------------------------------------------Sauvegarde------------------------------------------------*/
void sauvAdherents(ListeAdherents LA,FILE *flot);
void sauvAdherentsB(ListeAdherents LA,FILE *flot);
void LAsauvFic(ListeAdherents LA,int prochainNumAdh,char nomFic[],char nomFicB[]);

void sauvEmprunts(ListeEmprunts LE,ListeJeux LJ,ListeAdherents LA,FILE *flot);
void sauvEmpruntsB(ListeEmprunts LE,FILE *flot);
void LEsauvFic(ListeEmprunts LE,ListeJeux LJ,ListeAdherents LA,char nomFic[],char nomFicB[],int prochainNumEmp);

void sauvJeu(ListeJeux LE,FILE *flot);
void sauvJeuB(ListeJeux LE,FILE *flot);
void LJsauvFic(ListeJeux LE,char nomFic[],char nomFicB[]);

void sauvReserv(ListeReservations LR,ListeAdherents LA,ListeJeux LJ,FILE *flot);
void sauvReservB(ListeReservations LR, int prochainNumRes, FILE *flot);
void LRsauvFic(ListeReservations LR,ListeJeux LJ,ListeAdherents LA,char nomFic[],char nomFicB[],int prochainNumRes);
