#include "header.h"

void globale(void){
        /*Création des listes et du tebleau de pointeurs*/
    char id[6];
    ListeAdherents LA;
    ListeJeux LJ;
    ListeEmprunts LE;
    ListeReservations LR;
    int prochainNumRes,prochainNumAdh,prochainNumEmp,choix;

        /*Initialisation des listes*/
    LR=LRnouvList();
    LA=LAnouvList();
    LJ=LJnouvList();
    LE=LEnouvList();

        /*Chargement des listes*/
    LR=LRchargFic(FICRESERVB,&prochainNumRes);
    LE=LEchargFic(FICEMPB,&prochainNumEmp);
    LA=LAchargFic(FICADHB,&prochainNumAdh);
    LJ=LJchargFic(FICJEUB);

    choix=choixMenu();
    while(choix!=9){
        switch (choix)
        {
        case 1:                          /*Cas 1 : Afficher les jeux disponibles*/
            system("clear");
            afficherJeuxDispo(LJ);          
            break;
        case 2:                          /*Cas 2 : Afficher la liste des emprunts en cours*/
            system("clear");
            printf("\n\tListe des emprunts en cours\n\n");
            afficherListeEmprunts(LE,LA,LJ);
            break;
        case 3:                         /*Cas 3 : Afficher la liste des réservations pour un jeu donné*/
            system("clear");
            printf("\n\tListe des réservations pour un jeu donné\n\n");
            if(!LRestvide(LR)){
                saisieIDJeu(LJ,id);
                if(strcmp(id,"q")==0)
                    break;
                system("clear");
                printf("\n\tListe des réservations pour un jeu donné\n\n");
                afficheReservJeu(LR,LA,LJ,id);
            }
            else
                printf("Aucune réservation\n");
            break;
        case 4:                         /*Cas 4 : Création d'un emprunt*/
            system("clear");
            printf("\tCréation d'un emprunt\n");
            LE=ajouterEmprunt(LE,&LA,&prochainNumAdh,LJ,&prochainNumEmp,&LR,&prochainNumRes);
            break;
        case 5:                         /*Cas 5 : Création d'une réservation*/
            system("clear");
            printf("\n\tCreation d'une reservation\n\n");
            LR=ajouterReservation(LR,&prochainNumRes,&LA,&prochainNumAdh,LJ);
            break;
        case 6:                         /*Cas 6 : Retour d'un jeu*/
            system("clear");
            printf("\n\tRetour de jeu\n\n");
            if(!LEestVide(LE))
                LJ=retourJeu(LJ,&LR,&prochainNumRes,&LE,&prochainNumEmp,&LA);
            else
                printf("Aucun emprunt en cours\n");
            break;
        case 7:                         /*Cas 7 : Annulation d'une réservation*/
            system("clear");
            printf("\n\tAnnulation d'une réservation\n\n");
            if(LRestvide(LR))
                printf("Aucune réservation\n");
            else
                LR=supprimerReserv(LR,LA,LJ);
            break;  
        case 8:                         /*Cas 8 : Sauvegarde des fichiers*/
            system("clear");
            printf("\n\tSauvegarde des fichiers\n\n");
            LRsauvFic(LR,LJ,LA,FICRESERV,FICRESERVB,prochainNumRes);
            LAsauvFic(LA,prochainNumAdh,FICADH,FICADHB);
            LJsauvFic(LJ,FICJEU,FICJEUB);
            LEsauvFic(LE,LJ,LA,FICEMP,FICEMPB,prochainNumEmp);
            printf("\nFichiers sauvegardés\n");
            break;

            /*Fonctionnalités facultatives*/

        case 10:                        /*Cas 10 : Affiche la liste des adhérents*/
            system("clear");
            afficherListeAdherents(LA);
            break;
        case 11:                        /*Cas 11 : Création d'un adhérent*/
            system("clear");
            LA=LAinserer(LA,saisieAdherent(&prochainNumAdh));
            break;
        case 12:                        /*Cas 12 : Création d'un jeu*/
            system("clear");
            LJ=LJinsererEnTete(LJ,saisieJeu());
            break;
        case 13:                        /*Cas 13 : Afficher toutes les réservations*/       
            system("clear");  
            afficherListeReservations(LR,LA,LJ);
            break;
        case 14:                        /*Cas 14 : Afficher la liste de jeux*/
            system("clear");
            afficherListeJeux(LJ);
            break;
        default:
            printf("Erreur aucune fonctionnalité correspondante\n");
            break;
        }
        printf("\nTaper la touche entrée pour continuer...\n");
        getchar();
        choix=choixMenu();
        system("clear");
    }
        /*Sauvegarde des fichiers*/
    LRsauvFic(LR,LJ,LA,FICRESERV,FICRESERVB,prochainNumRes);
    LAsauvFic(LA,prochainNumAdh,FICADH,FICADHB);
    LJsauvFic(LJ,FICJEU,FICJEUB);
    LEsauvFic(LE,LJ,LA,FICEMP,FICEMPB,prochainNumEmp);

        /*Suppression des listes*/
    LR=supprimeListeReservations(LR);
    LA=supprimeListeAdherents(LA);
    LJ=supprimeListeJeux(LJ);
    LE=supprimeListeEmprunts(LE);
    
    system("clear");
    printf("Au revoir et à bientot dans notre ludothèque\n");
}

int main(void){
    globale();
    return 0;
}