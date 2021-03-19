#include "header.h"

/*------------------------------------------------Divers------------------------------------------------*/

/*
Fonction qui vérifie si la liste est vide.
Renvoie VRAI si c'est le cas, sinon FAUX.
(Même principe pour les autres listes)
*/

Booleen LAestVide(ListeAdherents LA){
    if(LA==NULL)
        return VRAI;
    return FAUX;
}

/*
Fonction qui renvoie une liste vide.
(Même principe pour les autres listes)
*/

ListeAdherents LAnouvList(void){
    return NULL;
}

/*
Fonction verifiant si l'adhérant est inscrit depuis plus d'un an.
Renvoie VRAI si c'est le cas, sinon FAUX.
*/

Booleen adhPlus1An(Adherent a,Date d){
    Date d2;
    d2=a.dateInscription;
    d2.annee++;
    if(d.annee==d2.annee){
        if(d.mois>d2.mois)
            return VRAI;
        if(d.mois==d2.mois && d.jour>d2.jour)
            return VRAI;
    }
    if(d.annee>d2.annee)
        return VRAI;

    return FAUX;
}

Booleen LEestVide(ListeEmprunts LE){
    if(LE==NULL)
        return VRAI;
    return FAUX;
}

ListeEmprunts LEnouvList(void){
    return NULL;
}

/*
Fonction vérifiant si l'emprunt dure plus d'un mois.
Renvoie vrai si c'est le cas,sinon faux.
*/

Booleen empruntJeuPlus1Mois(ListeEmprunts LE,int numAdh,Date d){
    Date d2;
    while(!LEestVide(LE)){
        if(LE->e.IDAdherent==numAdh){
            d2=LE->e.dateEmp;
            d2.mois++;
            if(d2.mois==13){
                d2.mois=1;
                d2.annee++;
            }
            if(d2.mois==1 && d.mois>d2.mois)
                continue;
            if(d.mois==d2.mois)
                if(d.jour>d2.jour)
                    return VRAI;
            if(d.mois>d2.mois)
                return VRAI;
        }
        LE=LE->suiv;
    }
    return FAUX;
}

/*
Fonction verifiant si la date e2 est plus ancienne que la date e1.
Renvoie vrai si c'est le cas, sinon faux.
*/

Booleen datePlusAncienne(Date e1, Date e2){
    if(e1.annee>e2.annee)
        return VRAI;
    if(e1.annee==e2.annee&&e1.mois>e2.mois)
        return VRAI;
    if(e1.annee==e2.annee&&e1.mois==e2.mois&&e1.jour>e2.jour)
        return VRAI;    
    return FAUX;
}


Booleen LJestVide(ListeJeux LJ){
    if(LJ==NULL)
        return VRAI;
    return FAUX;
}

ListeJeux LJnouvList(void){
    return NULL;
}

/*
Fonction triant les jeux par type et par ordre alphabétique.
Renvoie la liste de jeux.
*/

ListeJeux LJtri(ListeJeux LJ){
    ListeJeux trie,max;
    trie=LJnouvList();
    while(!LJestVide(LJ)){
        max=LJrechMax(LJ);
        trie=LJinsererEnTete(trie,max->j);
        LJ=LJsupprimer(LJ,max->j.IDjeu);
    }
    return trie;
}


Booleen LRestvide(ListeReservations LR){
    if(LR==NULL)
        return VRAI;
    return FAUX;
}

ListeReservations LRnouvList(void){
    return NULL;
}

/*------------------------------------------------Saisie------------------------------------------------*/
                /*Toutes les fonctions ici servent à saisir et retourner des information*/

void saisieNomPrenom(char *nom,char *prenom){
    printf("Votre nom: ");
    fgets(nom,20,stdin);
    nom[strlen(nom)-1]='\0';
    printf("Votre prénom: ");
    fgets(prenom,20,stdin);
    prenom[strlen(prenom)-1]='\0';
}

Adherent saisieAdherent(int *prochainNumAdh){
    Adherent a;
    char c;
    c=saisieSexe();
    if(c=='F'||c=='f')
        a.civilite=0;
    else a.civilite=1;
    saisieNomPrenom(a.nom,a.prenom);
    a.dateInscription=saisieDate("Date du jour");
    a.IDAdherent=*prochainNumAdh;
    (*prochainNumAdh)++;
    a.nbEmpCours=0;
    return a;
}

int saisieNumAdh(ListeAdherents LA){
    int numAdh;
    printf("\nSaisir votre numéro d'adhérent(0 pour quitter): ");
    scanf("%d%*c",&numAdh);
    while(!rechAdh(LA,numAdh)){
        if(numAdh==0)
            return 0;
        printf("\nLe numéro d'adhérent n'existe pas!\n");
        printf("Réessayez(0 pour quitter): ");
        scanf("%d%*c",&numAdh);
    }
    return numAdh;
}

int saisieNumRes(ListeReservations LR,ListeAdherents LA,ListeJeux LJ){
    int numRes;
    printf("Entrez le numéro de la réservation(0 pour voir la liste / -1 pour quitter): ");
    scanf("%d%*c",&numRes);
    while(numRes==0){
        afficherListeReservations(LR,LA,LJ);
        printf("Entrez le numéro de la réservation(0 pour voir la liste / -1 pour quitter): ");
        scanf("%d%*c",&numRes);
    }
    return numRes;
}

char demandeSiNouveau(void){
    char c;
    printf("Etes vous nouveau?(o/n): ");
    scanf("%c%*c",&c);
    while(c != 'o' && c !='O' && c !='n' && c !='N'){
        printf("Erreur de saisie\n");
        printf("Etes vous nouveau?(o/n): ");
        scanf("%c%*c",&c);
    }
    return c;
}

char demandeON(char *message){
    char c;
    printf("%s?(o/n): ",message);
    scanf("%c%*c",&c);
    while(c != 'o' && c !='O' && c !='n' && c !='N'){
        printf("Erreur de saisie\n");
        printf("%s?(o/n): ",message);
        scanf("%c%*c",&c);
    }
    return c;
} 

char saisieSexe(void){
    char c;
    printf("Votre sexe(F/H): ");
    scanf("%c%*c",&c);
    while(c!='F'&&c!='f'&&c!='H'&&c!='h'){
        printf("Sexe invalide\n");
        printf("Resaisir(F/H): ");
        scanf("%c%*c",&c);
    }
    return c;
}


Reservation saisieReserv(ListeAdherents *LA,ListeJeux LJ,int *prochainNumAdh){
    Reservation r;
    Adherent a;
    char c;
    saisieIDJeu(LJ,r.IDjeu);
    if(strcmp(r.IDjeu,"q")==0)
            return r;
    c=demandeSiNouveau();
    if(c=='o'||c=='O'){
        a=saisieAdherent(prochainNumAdh);
        afficherAdherent(a);
        *LA=LAinserer(*LA,a);
        r.dateRes=a.dateInscription;
        r.IDadherent=a.IDAdherent;
    }
    else if(c=='n'||c=='N'){
        r.IDadherent=saisieNumAdh(*LA);
        if(r.IDadherent==0)
            return r;
        r.dateRes=saisieDate("Date de réservation");
    }
    return r;
}


Jeu saisieJeu(void){
    Jeu j;
    int type;
    printf("Nom du jeu: ");
    fgets(j.nomJeu,40,stdin);
    j.nomJeu[strlen(j.nomJeu)-1]='\0';
    printf("ID jeu: ");
    scanf("%s%*c",j.IDjeu);
    printf("type (0-4): ");
    scanf("%d%*c",&type);
    switch(type){
        case 0:
            j.type=construction;
        case 1:
            j.type=plateau;
        case 2:
            j.type=tuile;
        case 3:
            j.type=carte;
        case 4:
            j.type=logique;
    }
    printf("Nb exemplaires: ");
    scanf("%d%*c",&j.nbEx);
    return j;
}

void saisieIDJeu(ListeJeux LJ,char IDjeu[]){
    printf("\nSaisir l'identifiant du jeu(0 pour afficher la liste / q pour quitter): ");
    scanf("%s%*c",IDjeu);
    while(positionJeu(LJ,IDjeu)==NULL){
        if(strcmp(IDjeu,"q")==0)
            return;
        if(strcmp(IDjeu,"0")==0)
            afficherListeJeux(LJ);
        else
            printf("\nJeu inexistant\n");
        printf("\nSaisir l'identifiant du jeu(0 pour afficher la liste / q pour quitter): ");
        scanf("%s%*c",IDjeu);
    }
}

char* RenvoieTypeJeu(Jeu j){
    switch(j.type){
        case 0:
            return "construction";
        case 1:
            return "plateau";
        case 2:
            return "tuile";
        case 3:
            return "carte";
        case 4:
            return "logique";
    }
    return NULL;
}


Date saisieDate(char c[]){
    Date d;
    printf("\n%s(jj/mm/aaaa): ",c);
    scanf("%d/%d/%d%*c",&d.jour,&d.mois,&d.annee);
    while(!verifDate(d)){
        printf("Date incorrecte\n");
        printf("Resaisir la date(jj/mm/aaaa): ");
        scanf("%d/%d/%d%*c",&d.jour,&d.mois,&d.annee);
    }
    return d;
}

Booleen verifDate(Date d){
    if(d.jour<1||d.jour>31)
        return FAUX;
    if(d.mois<1||d.mois>12)
        return FAUX;
    return VRAI;
}


int choixMenu(void){
    int choix;
    system("clear");
    printf("\n\tMenu Principal\n\n");
    printf("1\tAfficher la liste jeux disponibles\n");
    printf("2\tAfficher la liste des emprunts en cours\n");
    printf("3\tAfficher la liste des réservations pour un jeu donné\n");
    printf("4\tSaisir un emprunt\n");
    printf("5\tSaisir une réservation\n");
    printf("6\tRetour de jeu\n");
    printf("7\tAnnuler une réservation\n");
    printf("8\tSauvegarder\n");
    printf("9\tQuitter\n\n");
    printf("=> ");
    scanf("%d%*c",&choix);
    return choix;
}

/*------------------------------------------------Ajout------------------------------------------------*/

/*
Fonction d'insertion en tete d'un adhérent dans une liste.
Renvoie la nouvelle liste.
(Même principe pour les autres listes)
*/

ListeAdherents LAinsererEnTete(ListeAdherents LA,Adherent a){
    MaillonAdherents *newA;
    newA=(MaillonAdherents*)malloc(sizeof(MaillonAdherents));
    if(newA==NULL){
        printf("Problème malloc adhérents\n");
        exit(1);
    }
    newA->a=a;
    newA->suiv=LA;
    return newA;
}

/*
Fonction d'insertion d'un adhérent dans une liste selon le critère de tri ici l'identifiant de l'adhérent
Renvoie la nouvelle liste.
(Même principe pour les autres listes)
*/

ListeAdherents LAinserer(ListeAdherents LA,Adherent a){
    if(LA==NULL)
        return LAinsererEnTete(LA,a);
    if(LA->a.IDAdherent>a.IDAdherent)
        return LAinsererEnTete(LA,a);
    if(LA->a.IDAdherent==a.IDAdherent){
        printf("L'adhérent %s %s existe déjà!\n",a.nom,a.prenom);
        return LA;
    }
    LA->suiv=LAinserer(LA->suiv,a);
    return LA;
}


ListeReservations LRinsererEnTete(ListeReservations LR,Reservation r){
    MaillonReservations *nouv;
    nouv=(MaillonReservations*)malloc(sizeof(MaillonReservations));
    if(nouv==NULL){
        printf("Problème malloc Reservation\n");
        exit(1);
    }
    nouv->r=r;
    nouv->suiv=LR;
    return nouv;
}

ListeReservations LRinserer(ListeReservations LR, Reservation r){
    if(LRestvide(LR))
        return LRinsererEnTete(LR,r);
    if(LR->r.IDresa>=r.IDresa)
        return LRinsererEnTete(LR,r);
    LR->suiv=LRinserer(LR->suiv,r);
    return LR;
}

/*
Fonction permettant de créer et d'ajouter une réservation dans un tableau de pointeurs.
Renvoie un tableau de pointeurs modifié ou non si quelque chose s'est mal passé.
A noter que les listes sont passées par pointeurs puique il peut arriver d'effectuer des modifications sur celles-ci.
*/

ListeReservations ajouterReservation(ListeReservations LR,int *prochainNumRes,ListeAdherents *LA,int *prochainNumAdh,ListeJeux LJ){
    Reservation r;
    r=saisieReserv(LA,LJ,prochainNumAdh);
    if(strcmp(r.IDjeu,"q")==0||r.IDadherent==0)
            return LR;
    r.IDresa=*prochainNumRes;
    LR=LRinserer(LR,r);
    (*prochainNumRes)++;
    printf("\nVotre demande a bien été prise en compte!\n");
    return LR;
}

/*
Fonction permetant de créer une réservation si, lors d'un emprunt, le jeu choisit n'est plus en stock.
Renvoie le tableau de pointeurs modifié ou non si quelque chose s'est mal passé.
A noter que les listes sont passées par pointeurs puiqu'il peut arriver d'effectuer des modifications sur celles-ci.
*/

ListeReservations reservationParEmprunt(ListeReservations LR,int *prochainNumRes,ListeAdherents *LA,int *prochainNumAdh,ListeJeux LJ){
    Adherent a;
    Reservation r;
    char c;
    c=demandeSiNouveau();
    if(c=='o'||c=='O'){
        a=saisieAdherent(prochainNumAdh);
        *LA=LAinserer(*LA,a);
        r.dateRes=a.dateInscription;
        r.IDadherent=a.IDAdherent;
    }
    else if(c=='n'||c=='N'){
        r.IDadherent=saisieNumAdh(*LA);
        if(r.IDadherent==0)
            return LR;
        r.dateRes=saisieDate("Date de réservation");
    }
    r.IDresa=*prochainNumRes;
    LR=LRinserer(LR,r);
    (*prochainNumRes)++;
    printf("\nVotre demande a bien été prise en compte!\n");
    return LR;
}


ListeEmprunts LEinsererEnTete(ListeEmprunts LE,Emprunt e){
    MaillonEmprunts *newE;
    newE=(MaillonEmprunts*)malloc(sizeof(MaillonEmprunts));
    if (newE==NULL){
        printf("Problème malloc emprunt\n");
        exit(1);
    }
    newE->e=e;
    newE->suiv=LE;
    return newE;
}

ListeEmprunts LEinserer(ListeEmprunts LE,Emprunt e){
    if(LE==NULL)
        return LEinsererEnTete(LE,e);
    if(datePlusAncienne(LE->e.dateEmp,e.dateEmp))
        return LEinsererEnTete(LE,e);
    LE->suiv=LEinserer(LE->suiv,e);
    return LE;
}

/*
Fonction permettant de créer et d'ajouter un emprunt dans une liste d'emprunt.
Renvoie une liste d'emprunts.
A noter que les listes sont passées par pointeurs puiqu'il peut arriver d'effectuer des modifications sur celles-ci.
*/

ListeEmprunts  ajouterEmprunt(ListeEmprunts LE, ListeAdherents *LA,int *prochainNumAdh,ListeJeux LJ, int *prochainNumEmp,ListeReservations *LR,int *prochainNumRes){
    Emprunt e;
    Adherent a;
    ListeAdherents posA;
    char c;
    Date d;

    d=saisieDate("Date du jour");
    saisieIDJeu(LJ,e.IDjeu);
    if(strcmp(e.IDjeu,"q")==0)
            return LE;
    LJ=positionJeu(LJ,e.IDjeu);
    if (LJ->j.nbEx==0){
        printf("\nLe jeu n'est plus en stock\n");
        printf("\nVoulez vous le réserver?(o/n): ");
        scanf("%c%*c",&c);
        if(c=='o'||c=='O'){
            system("clear");
            printf("\n\tCréation d'une réservation\n\n");
            *LR=reservationParEmprunt(*LR,prochainNumRes,LA,prochainNumAdh,LJ);
        }
        return LE;
    }
    c=demandeSiNouveau();
    if(c=='o'||c=='O'){    // Nouvel adhérent
        system("clear");
        printf("\tCréation d'un adhérent\n");
        
        c=saisieSexe();
        if(c=='F'||c=='f')
            a.civilite=0;
        else if(c=='H'||c=='h')
            a.civilite=1;
        saisieNomPrenom(a.nom,a.prenom);
        a.IDAdherent=*prochainNumAdh;
        (*prochainNumAdh)++;
        a.nbEmpCours=1;

        afficherAdherent(a);
        *LA=LAinserer(*LA,a);
        e.IDAdherent=a.IDAdherent;
    }
    else if(c=='n'||c=='N'){     // adhérent existant
        e.IDAdherent=saisieNumAdh(*LA);
        if(e.IDAdherent==0)
            return LE;
        posA=positionAdherent(*LA,e.IDAdherent);
        if(adhPlus1An(posA->a,d)){
            printf("Vous devez renouveler votre abonnement pour pouvoir emprunter de nouveau!\n");
            printf("\nVoulez vous le renouveler maintenant(o/n): ");
            scanf("%c%*c",&c);
            if(c=='o'||c=='O'){
                printf("Paiement en cours\n");
                system("sleep 2");
                printf("Paiement effectue, abonnement renouvele\n");
                posA->a.dateInscription=d;
            }
            else
                return LE;
        }
        if(posA->a.nbEmpCours==3){
            printf("Vous ne pouvez pas emprunter plus de 3 jeux\n");
            return LE;
        }
        if(empruntJeuPlus1Mois(LE,e.IDAdherent,d)){
            printf("Emprunt impossible.\nDurée maximale dépassée, vous devez rendre les jeux empruntés il y a plus d'un mois.\n");
            return LE;
        }
        posA->a.nbEmpCours++;
    }
    LJ->j.nbEx--;
    e.dateEmp=d;
    e.IDemprunt=*prochainNumEmp;
    (*prochainNumEmp)++;
    LE=LEinserer(LE,e);
    printf("\nVotre demande a bien été prise en compte!\n");
    return LE;
}


ListeJeux LJinsererEnTete(ListeJeux LJ,Jeu j){
    MaillonJeu *nouvJeu;
    nouvJeu=LJnouvList(); //peut etre inutile
    nouvJeu=(MaillonJeu*)malloc(sizeof(MaillonJeu));
    if(nouvJeu==NULL){
        printf("Problème malloc jeu\n");
        exit(1);
    }
    nouvJeu->j=j;
    nouvJeu->suiv=LJ;
    return nouvJeu;
}

/*------------------------------------------------Suppression------------------------------------------------*/

/*
Fonction permettant de supprimer le premier element d'une liste.
Renvoie une liste.
*/

ListeAdherents LAsupprimerEnTete(ListeAdherents LA){
    MaillonAdherents *Liste;
    if(LA==NULL){
        printf("Opération interdite\n");
        exit(1);
    }
    Liste=LA->suiv;
    free(LA);
    return Liste;
}

/*
Fonction permettant de supprimer un adhérent en fonction d'un identifiant.
Renvoie une liste.
*/

ListeAdherents LAsupprimer(ListeAdherents LA,int ID){
    if(LA==NULL)
        return LA;
    if(LA->a.IDAdherent>ID)
        return LA;
    if(LA->a.IDAdherent==ID)
        return LAsupprimerEnTete(LA);
    LA->suiv=LAsupprimer(LA->suiv,ID);
    return LA;
}

/*
Fonction supprimant la liste d'adhérent.
Renvoie une liste vide;
*/

ListeAdherents supprimeListeAdherents(ListeAdherents LA){
    while(LA != NULL)
        LA=LAsupprimerEnTete(LA);
    return LA;
}

/*
Fonction permettant de choisir une réservation à supprimer. Celle-ci est ensuite enlevée du tableau. 
Renvoie un tableau de pointeurs.
*/

ListeReservations LRsupprimerEnTete(ListeReservations LR){
    ListeReservations nouv;
    if(LRestvide(LR)){
        printf("Operation interdite\n");
        exit(1);
    }
    nouv=LR->suiv;
    free(LR);
    return nouv;
}

ListeReservations LRsupprimer(ListeReservations LR, int numRes){
    if(LRestvide(LR))
        return LR;
    if(numRes==LR->r.IDresa)
        return LRsupprimerEnTete(LR);
    LR->suiv=LRsupprimer(LR->suiv,numRes);
    return LR;
}

ListeReservations supprimerReserv(ListeReservations LR,ListeAdherents LA, ListeJeux LJ){
    char c;
    int numRes;
    c=demandeON("Etes vous sur de vouloir supprimer une réservation");
    if (c=='O' || c=='o'){
        numRes=saisieNumRes(LR,LA,LJ);
        if(numRes==-1)
            return LR;
        LR=LRsupprimer(LR,numRes);
        printf("\n Réservation bien supprimée\n\n");
    }
    return LR;
}

ListeReservations supprimeListeReservations(ListeReservations LR){
    while(!LRestvide(LR))
        LR=LRsupprimerEnTete(LR);
    return LR;
}


ListeEmprunts LEsupprimerEnTete(ListeEmprunts LE){
    MaillonEmprunts *Liste;
    if(LE==NULL){
        printf("Opération interdite\n");
        exit(1);
    }
    Liste=LE->suiv;
    free(LE);
    return Liste;
}

ListeEmprunts LEsupprimer(ListeEmprunts LE,int ID){
    if(LE==NULL)
        return LE;
    if(LE->e.IDemprunt==ID)
        return LEsupprimerEnTete(LE);
    LE->suiv=LEsupprimer(LE->suiv,ID);
    return LE;
}

ListeEmprunts supprimeListeEmprunts(ListeEmprunts LE){
    while(LE != NULL)
        LE=LEsupprimerEnTete(LE);
    return LE;
}


ListeJeux LJsupprimerEnTete(ListeJeux LJ){
    MaillonJeu *temp;
    if(LJ==NULL){
        printf("Opération interdite\n");
        exit(1);
    }
    temp=LJ->suiv;
    free(LJ);
    return temp;
}

ListeJeux LJsupprimer(ListeJeux LJ,char ID[]){
    if(LJ==NULL)
        return LJ;
    if(strcmp(LJ->j.IDjeu,ID)==0)
        return LJsupprimerEnTete(LJ);
    LJ->suiv=LJsupprimer(LJ->suiv,ID);
    return LJ;
}

ListeJeux supprimeListeJeux(ListeJeux LJ){
    while(LJ != NULL)
        LJ=LJsupprimerEnTete(LJ);
    return LJ;
}

/*
Fonction permettant de retourner un jeu après l'avoir emprunté. Si le jeu est réservé, la réservation deviendra automatiquement un emprunt.
Renvoie un tableau de pointeurs.
A noter que les listes sont passées par pointeurs puiqu'il peut arriver d'effectuer des modifications sur celles-ci.
*/

ListeJeux retourJeu(ListeJeux LJ,ListeReservations *LR,int *prochainNumRes,ListeEmprunts *LE,int *prochainNumEmp,ListeAdherents *LA){
    int numAdh,numEmp;
    char IDjeu[6];
    Emprunt e;
    ListeAdherents posA;
    ListeEmprunts posE;
    ListeJeux posJ;
    ListeReservations posR;
    numAdh=saisieNumAdh(*LA);
    if(numAdh==0)
        return LJ;
    afficherEmpruntsAdh(*LE,*LA,LJ,numAdh);
    posA=positionAdherent(*LA,numAdh);
    if(LAestVide(posA)||posA->a.nbEmpCours==0)
        return LJ;
    printf("\nEntrez l'ID de l'emprunt(0 pour quitter) : ");
    scanf("%d%*c",&numEmp);
    posE=positionEmprunt(*LE,numEmp);
    while(posE==NULL || posA->a.IDAdherent!=posE->e.IDAdherent){
        if(numEmp==0)
            return LJ;
        printf("L'identifiant est incorrect\n");
        printf("Resaisir (0 pour quitter): ");
        scanf("%d%*c",&numEmp);
        posE=positionEmprunt(*LE,numEmp);
    }
    strcpy(IDjeu,posE->e.IDjeu);
    *LE=LEsupprimer(*LE,numEmp);
    posA->a.nbEmpCours--;
    posR=rechReservParIDjeu(*LR,IDjeu);
    if(LRestvide(posR)){
        if(LJestVide(LJ))
            return LJ;
        posJ=positionJeu(LJ,IDjeu);
        posJ->j.nbEx++;
        printf("\nLe jeu %s a bien été retourné\n",posJ->j.nomJeu);
        return LJ;
    }
    e.IDAdherent=posR->r.IDadherent;
    e.IDemprunt=*prochainNumEmp;
    (*prochainNumEmp)++;
    e.dateEmp=saisieDate("Date du jour");
    strcpy(e.IDjeu,IDjeu);
    *LE=LEinserer(*LE,e);
    *LR=LRsupprimer(*LR,posR->r.IDresa);
    posA=positionAdherent(*LA,e.IDAdherent);
    posA->a.nbEmpCours++;
    return LJ;
}

/*------------------------------------------------Recherche------------------------------------------------*/

/*
Fonction permettant de vérifier si un adhérent existe dans la liste.
Renvoie VRAI si l'adhérent existe, FAUX sinon.
*/

Booleen rechAdh(ListeAdherents LA,int numAdh){
    while(!LAestVide(LA)){
        if(LA->a.IDAdherent==numAdh)
            return VRAI;
        LA=LA->suiv;
    }
    return FAUX;
}

/*
Fonction permettant de renvoyer la position d'un adhérent.
Renvoie le pointeur du maillon de l'adhérent.
(Même fonctionnement pour les fonctions "position...")
*/

ListeAdherents positionAdherent(ListeAdherents LA,int numAdh){
    while(!LAestVide(LA)){
        if(LA->a.IDAdherent==numAdh)
            return LA;
        LA=LA->suiv;
    }
    return NULL;
}


ListeReservations positionReserv(ListeReservations LR,int numRes){
    while(!LRestvide(LR)){
        if(LR->r.IDresa==numRes)
            return LR;
        LR=LR->suiv;
    }
    return NULL;
}

ListeReservations rechReservParIDjeu(ListeReservations LR,char idJeu[]){
    while(!LRestvide(LR)){
        if(strcmp(LR->r.IDjeu,idJeu)==0)
            return LR;
        LR=LR->suiv;
    }
    return NULL;
}


ListeEmprunts positionEmprunt(ListeEmprunts LE,int noEmp){
    while(!LEestVide(LE)){
        if(LE->e.IDemprunt==noEmp)
            return LE;
        LE=LE->suiv;
    }
    return NULL;
}


ListeJeux positionJeu(ListeJeux LJ,char jeu[]){
    while(!LJestVide(LJ)){
        if(strcmp(LJ->j.IDjeu,jeu)==0)
            return LJ;
        LJ=LJ->suiv;
    }
    return NULL;
}

/*
Fonction permettant de rechercher le jeu le plus "grand" selon les critères de tri: par type de jeu et ensuite par ordre alphabétique.
Renvoie le pointeur du maillon le plus "grand".
*/

ListeJeux LJrechMax(ListeJeux LJ){
    MaillonJeu *max;
    max=LJ;
    while(LJ!=NULL){
        if(LJ->j.type>max->j.type)
            max=LJ;
        if(LJ->j.type==max->j.type && strcmp(LJ->j.nomJeu,max->j.nomJeu)>0)
            max=LJ;
        LJ=LJ->suiv;
    }
    return max;
}

/*------------------------------------------------Affichage------------------------------------------------*/
                            /*Fonctions permettant d'afficher certaines données*/

char* RenvoieSexe(Adherent a){
    if(a.civilite==0)
        return "Mme";
    if(a.civilite==1)
        return "Mr";
    return NULL;
}

void afficherAdherent(Adherent a){
    printf("\n");
    printf("ID: %d\n",a.IDAdherent);
    printf("Informations: %s %s %s\n",RenvoieSexe(a),a.nom,a.prenom);
    printf("Date d'inscription: ");
    afficheDate(a.dateInscription);
    printf("\nNombre d'emprunts: %d\n",a.nbEmpCours);
    printf("\n");
}

void afficherListeAdherents(ListeAdherents LA){
    if(LAestVide(LA)){
        printf("Aucun adherents.\n\n");
        return;
    }
    while(!LAestVide(LA)){
        afficherAdherent(LA->a);
        LA=LA->suiv;
    }
}


void afficherReserv(ListeReservations LR,ListeAdherents LA, ListeJeux LJ){
        ListeAdherents posA;
        ListeJeux posJ;
        printf("\nNuméro de réservation: %d\n",LR->r.IDresa);
        posA=positionAdherent(LA,LR->r.IDadherent);
        printf("Adhérent: %s %s %s\n",RenvoieSexe(posA->a),posA->a.nom,posA->a.prenom);
        posJ=positionJeu(LJ,LR->r.IDjeu);
        printf("Nom du jeu: %s\n",posJ->j.nomJeu);
        printf("Date de réservation: %02d/%02d/%04d\n\n",LR->r.dateRes.jour,LR->r.dateRes.mois,LR->r.dateRes.annee);
}

void afficherListeReservations(ListeReservations LR,ListeAdherents LA,ListeJeux LJ){
    if(LRestvide(LR)){
        printf("Aucune Reservation\n");
        return;
    }
    while(!LRestvide(LR)){
        afficherReserv(LR,LA,LJ);
        LR=LR->suiv;
    }
}

void afficheReservJeu(ListeReservations LR,ListeAdherents LA, ListeJeux LJ, char IDjeu[]){
    int a=0;
    if(LRestvide(LR)){
        printf("Aucune Réservation pour ce jeu\n");
        return;
    }
    while(!LRestvide(LR)){
        if(strcmp(LR->r.IDjeu,IDjeu)==0){
            afficherReserv(LR,LA,LJ);
            a++;
        }
        LR=LR->suiv;
    }
    if(a==0)
        printf("Aucune Reservation pour ce jeu\n");
}


void afficherEmprunt(ListeEmprunts LE,ListeAdherents LA,ListeJeux LJ){
    printf("\nID : %d\n",LE->e.IDemprunt);
    LJ=positionJeu(LJ,LE->e.IDjeu);
    printf("Jeu : %s\n",LJ->j.nomJeu);
    LA=positionAdherent(LA,LE->e.IDAdherent);
    printf("Nom de l'emprunteur: %s %s %s\n",RenvoieSexe(LA->a),LA->a.nom,LA->a.prenom);
    printf("Date d'emprunt: %02d/%02d/%04d\n",LE->e.dateEmp.jour,LE->e.dateEmp.mois,LE->e.dateEmp.annee);
}

void afficherListeEmprunts(ListeEmprunts LE,ListeAdherents LA,ListeJeux LJ){
    if(LEestVide(LE)){
        printf("Aucun emprunts en cours\n");
        return;
    }
    while(!LEestVide(LE)){
        afficherEmprunt(LE,LA,LJ);
        LE=LE->suiv;
    }
}

void afficherEmpruntsAdh(ListeEmprunts LE,ListeAdherents LA,ListeJeux LJ,int numAdh){
    LA=positionAdherent(LA,numAdh);
    if(LEestVide(LE)||LA->a.nbEmpCours==0){
        printf("Aucun emprunt en cours pour cet adhérent\n");
        return;
    }
    while(!LEestVide(LE)){
        if(LA->a.IDAdherent==LE->e.IDAdherent)
            afficherEmprunt(LE,LA,LJ);
        LE=LE->suiv;
    }
}


void afficherJeux(ListeJeux LJ){
    printf("\nNom du jeu: %s\n",LJ->j.nomJeu);
    printf("ID: %s\n",LJ->j.IDjeu);
    printf("Type de jeu: %s\n",RenvoieTypeJeu(LJ->j));
    printf("Nombre d'exemplaires: %d\n",LJ->j.nbEx);
}

void afficherJeuxDispo(ListeJeux LJ){
    if(LJ==NULL){
        printf("Aucun Jeu\n");
        return;
    }
    while(!LJestVide(LJ)){
        if(LJ->j.nbEx!=0)
            afficherJeux(LJ);
        LJ=LJ->suiv;
    }
}

void afficherListeJeux(ListeJeux LJ){
    if(LJ==NULL){
        printf("Aucun Jeu\n");
        return;
    }
    while(!LJestVide(LJ)){
        afficherJeux(LJ);
        LJ=LJ->suiv;
    }
}


void afficheDate(Date d){
    printf("%02d/",d.jour);
    printf("%02d/",d.mois);
    printf("%04d",d.annee);
}

      /*------------------------------------------------Chargement------------------------------------------------*/
/*Fonctions permettant de charger des informations dans les listes et dans le tableau de pointeurs à partir des fichiers*/

Adherent lireAdherents(FILE *flot){
    Adherent a;
    fread(&a,sizeof(Adherent),1,flot);
    return a;
}

ListeAdherents LAchargFic(char nomFic[],int *prochainNumAdh){
    FILE *flot;
    ListeAdherents LA;
    Adherent a;
    LA=LAnouvList();
    flot=fopen(nomFic,"rb");
    if(flot==NULL){
        printf("Problème d'ouverture du fichier %s en lecture\n",nomFic);
        exit(1);
    }
    fread(prochainNumAdh,sizeof(int),1,flot);
    if(feof(flot)){
        *prochainNumAdh=1;
        fclose(flot);
        return LA;
    }
    a=lireAdherents(flot);
    while(!feof(flot)){
        LA=LAinserer(LA,a);
        a=lireAdherents(flot);
    }
    fclose(flot);
    return LA;
}


Reservation lireReserv(FILE *flot){
    Reservation r;
    fread(&r,sizeof(Reservation),1,flot);
    return r;
}

ListeReservations LRchargFic(char nomFic[],int *prochainNumRes){
    FILE *flot;
    ListeReservations LR;
    Reservation r;
    LR=LRnouvList();
    flot=fopen(nomFic,"rb");
    if(flot==NULL){
        printf("Problème d'ouverture du fichier %s en lecture\n",nomFic);
        exit(1);
    }
    fread(prochainNumRes,sizeof(int),1,flot);
    if(feof(flot)){
        *prochainNumRes=1;fclose(flot);
        return LR;
    }
    r=lireReserv(flot);
    while(!feof(flot)){
        LR=LRinserer(LR,r);
        r=lireReserv(flot);
    }
    fclose(flot);
    return LR;
}


Emprunt lireEmprunt(FILE *flot){
    Emprunt e;
    fread(&e,sizeof(Emprunt),1,flot);
    return e;
}

ListeEmprunts LEchargFic(char nomFic[],int *prochainNumEmp){
    FILE *flot;
    ListeEmprunts LE;
    Emprunt e;
    LE=LEnouvList();
    flot=fopen(nomFic,"rb");
    if(flot==NULL){
        printf("Problème d'ouverture du fichier %s en lecture\n",nomFic);
        exit(1);
    }
    fread(prochainNumEmp,sizeof(int),1,flot);
    if(feof(flot)){
        *prochainNumEmp=1;
        fclose(flot);
        return LE;
    }
    e=lireEmprunt(flot);
    while(!feof(flot)){
        LE=LEinserer(LE,e);
        e=lireEmprunt(flot);
    }
    fclose(flot);
    return LE;
}


Jeu lireJeu(FILE *flot){
    Jeu j;
    fread(&j,sizeof(Jeu),1,flot);
    return j;
}

ListeJeux LJchargFic(char nomFic[]){
    FILE *flot;
    ListeJeux LJ;
    Jeu j;
    LJ=LJnouvList();
    flot=fopen(nomFic,"rb");
    if(flot==NULL){
        printf("Problème d'ouverture du fichier %s en lecture\n",nomFic);
        exit(1);
    }
    j=lireJeu(flot);
    while(!feof(flot)){
        LJ=LJinsererEnTete(LJ,j);
        j=lireJeu(flot);
    }
    fclose(flot);
    LJ=LJtri(LJ);
    return LJ;
}

/*------------------------------------------------Sauvegarde------------------------------------------------*/
                /*Fonctions permettant de sauvegarder dans des fichiers binaires et textuels*/

void sauvAdherents(ListeAdherents LA,FILE *flot){
    fprintf(flot,"ID: %d\n",LA->a.IDAdherent);
    fprintf(flot,"Informations: %s %s %s\n",RenvoieSexe(LA->a),LA->a.nom,LA->a.prenom);
    fprintf(flot,"Date d'inscription: %02d/%02d/%04d\n",LA->a.dateInscription.jour,LA->a.dateInscription.mois,LA->a.dateInscription.annee);
    fprintf(flot,"Nombre de réservations: %d\n\n",LA->a.nbEmpCours);
}

void sauvAdherentsB(ListeAdherents LA,FILE *flot){
    fwrite(&LA->a,sizeof(Adherent),1,flot);
}

void LAsauvFic(ListeAdherents LA,int prochainNumAdh,char nomFic[],char nomFicB[]){
    FILE *flotB,*flot;
    flot=fopen(nomFic,"w");
    if(flot==NULL){
        printf("Problème d'ouverture du fichier %s en écriture\n",nomFic);
        exit(1);
    }
    flotB=fopen(nomFicB,"wb");
    if(flotB==NULL){
        printf("Problème d'ouverture du fichier %s en écriture\n",nomFicB);
        fclose(flot);
        exit(1);
    }
    fwrite(&prochainNumAdh,sizeof(int),1,flotB);
    while(!LAestVide(LA)){
        sauvAdherents(LA,flot);
        sauvAdherentsB(LA,flotB);
        LA=LA->suiv;
    }
    fclose(flot);
    fclose(flotB);
    return;
}


void sauvReserv(ListeReservations LR,ListeAdherents LA,ListeJeux LJ,FILE *flot){
    if(LRestvide(LR)){
        fprintf(flot,"Aucune Réservation\n");
        return;
    }
    fprintf(flot,"Numéro de réservation: %d\n",LR->r.IDresa);
    LA=positionAdherent(LA,LR->r.IDadherent);
    fprintf(flot,"Nom de l'adhérent: %s %s %s\n",RenvoieSexe(LA->a),LA->a.nom,LA->a.prenom);
    LJ=positionJeu(LJ,LR->r.IDjeu);
    fprintf(flot,"Nom du jeu : %s\n",LJ->j.nomJeu);
    fprintf(flot,"Date de réservation: %02d/%02d/%04d\n\n",LR->r.dateRes.jour,LR->r.dateRes.mois,LR->r.dateRes.annee);
}

void sauvReservB(ListeReservations LR,int prochainNumRes,FILE *flot){
    fwrite(&LR->r,sizeof(Reservation),1,flot);
}

void LRsauvFic(ListeReservations LR,ListeJeux LJ,ListeAdherents LA,char nomFic[],char nomFicB[],int prochainNumRes){
    FILE *flotB,*flot;
    flot=fopen(nomFic,"w");
    if(flot==NULL){
        printf("Problème d'ouverture du fichier %s en écriture\n",nomFic);
        exit(1);
    }
    flotB=fopen(nomFicB,"wb");
    if(flotB==NULL){
        printf("Problème d'ouverture du fichier %s en écriture\n",nomFicB);
        fclose(flot);
        exit(1);
    }
    fwrite(&prochainNumRes,sizeof(int),1,flotB);
    while(!LRestvide(LR)){
        sauvReserv(LR,LA,LJ,flot);
        sauvReservB(LR,prochainNumRes,flotB);
        LR=LR->suiv;
    }
    fclose(flot);
    fclose(flotB);
}


void sauvEmprunts(ListeEmprunts LE,ListeJeux LJ,ListeAdherents LA,FILE *flot){
    fprintf(flot,"Numéro de l'emprunt: %d\n",LE->e.IDemprunt);
    LA=positionAdherent(LA,LE->e.IDAdherent);
    fprintf(flot,"Nom de l'adhérent: %s %s %s\n",RenvoieSexe(LA->a),LA->a.nom,LA->a.prenom);
    fprintf(flot,"Numéro de l'adhérent: %d\n",LE->e.IDAdherent);
    LJ=positionJeu(LJ,LE->e.IDjeu);
    fprintf(flot,"Nom du jeu : %s\n",LJ->j.nomJeu);
    fprintf(flot,"Date d'emprunt: %02d/%02d/%04d\n\n",LE->e.dateEmp.jour,LE->e.dateEmp.mois,LE->e.dateEmp.annee);
}

void sauvEmpruntsB(ListeEmprunts LE,FILE *flot){
    fwrite(&LE->e,sizeof(Emprunt),1,flot);
}

void LEsauvFic(ListeEmprunts LE,ListeJeux LJ,ListeAdherents LA,char nomFic[],char nomFicB[],int prochainNumEmp){
    FILE *flotB,*flot;
    flot=fopen(nomFic,"w");
    if(flot==NULL){
        printf("Problème d'ouverture du fichier %s en écriture\n",nomFic);
        exit(1);
    }
    flotB=fopen(nomFicB,"wb");
    if(flotB==NULL){
        printf("Problème d'ouverture du fichier %s en écriture\n",nomFicB);
        fclose(flot);
        exit(1);
    }
    fwrite(&prochainNumEmp,sizeof(int),1,flotB);
    while(!LEestVide(LE)){
        sauvEmprunts(LE,LJ,LA,flot);
        sauvEmpruntsB(LE,flotB);
        LE=LE->suiv;
    }
    fclose(flot);
    fclose(flotB);
}


void sauvJeu(ListeJeux LJ,FILE *flot){
    fprintf(flot,"Nom du jeu: %s\n",LJ->j.nomJeu);
    fprintf(flot,"Identifiant du jeu: %s\n",LJ->j.IDjeu);
    fprintf(flot,"Type de jeu: %s\n",RenvoieTypeJeu(LJ->j));
    fprintf(flot,"Nombre d'exemplaires: %d\n\n",LJ->j.nbEx);
}

void sauvJeuB(ListeJeux LJ,FILE *flot){
    fwrite(&LJ->j,sizeof(Jeu),1,flot);
}

void LJsauvFic(ListeJeux LJ,char nomFic[],char nomFicB[]){
    FILE *flotB,*flot;
    flot=fopen(nomFic,"w");
    if(flot==NULL){
        printf("Problème d'ouverture du fichier %s en écriture\n",nomFic);
        exit(1);
    }
    flotB=fopen(nomFicB,"wb");
    if(flotB==NULL){
        printf("Problème d'ouverture du fichier %s en écriture\n",nomFicB);
        fclose(flot);
        exit(1);
    }
    while(!LJestVide(LJ)){
        sauvJeu(LJ,flot);
        sauvJeuB(LJ,flotB);
        LJ=LJ->suiv;
    }
    fclose(flot);
    fclose(flotB);
    return;
}
