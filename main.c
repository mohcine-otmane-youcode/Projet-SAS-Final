#include <stdio.h>
#include <string.h>

struct Date{
    int jour;
    int mois;
    int annee;
};

struct Joueur{
    char Id[4];
    char nom[10];
    int numeroMaillot;
    char poste[10];
    int age;
    int buts;
    struct Date dateInscription;
    char statut[10];
};

int nombre_joueurs = 0;
struct Joueur joueurs[10];//Tableau dynamique


int donnerId(struct Joueur joueur) {
    char id[6];
    id[0] = 'A' + (nombre_joueurs / 10000);
    int partieNumero = nombre_joueurs % 10000;
    for (int i = 4; i >= 1; i--) {
        id[i] = '0' + (partieNumero % 10);
        partieNumero = partieNumero/10;
    }
    id[5] = '\0';

    strcpy(joueur.Id, id);
    return 1;
}



void ajouter_un_joueur(){
    int nombre_joueurs_avant = nombre_joueurs, numeroMaillot;
    printf("1: Ajouter un nouveau joueur.\n");
    struct Joueur Njoueur;
    donnerId(Njoueur);
    printf("Nom de joueur: ");
    scanf("%s", &Njoueur.nom); 
    printf("\n");
    int numeroMaillot_unique;
    do{
        numeroMaillot_unique = 1;
        printf("Numero de maillot de joueur: ");
        scanf("%d", &numeroMaillot);
        //numeroMaillot unique ?
        for(int i=0;i<nombre_joueurs;i++){
            for(int j=0;j<nombre_joueurs && j!=i;j++){
                if(numeroMaillot==joueurs[i].numeroMaillot){
                    numeroMaillot_unique = 0;
                }
            }
        }
        if(numeroMaillot_unique==0){
            printf("Ce numero de maillot existe deja\n");
        }
    }while(!numeroMaillot_unique);
    Njoueur.numeroMaillot = numeroMaillot;
    
    printf("\n");
    printf("Poste de joueur: ");
    scanf("%s", &Njoueur.poste); 
    printf("\n");
    printf("Succes: Le joueur a ete ajoute\n");
    joueurs[nombre_joueurs] = Njoueur;
    nombre_joueurs++;
}

void ajouter(){
    int choix, estInt;
    printf("Ajouter un joueur\n");
    printf("1: Ajouter un nouveau joueur.\n");
    printf("2: Ajouter plusieurs joueurs en une seule operation.\n");
    printf("3: Informations\n");
    do{
        printf("\n\nEntrer un choix->: ");
        estInt = scanf("%d",&choix);
    }while(!estInt || (choix!=1 && choix!=2 && choix!=2));

    if(choix==1){
        ajouter_un_joueur();
        
    } else{
        printf("2: Ajouter plusieurs joueurs en une seule operation.\n");
    }
}

void afficher(){
    printf("Affichage de joueurs\n");
    for(int i=0;i<nombre_joueurs;i++){
        printf("Nom de joueur: %s\n", joueurs[i].nom); 
        printf("Numero de maillot de joueur: %s\n", joueurs[i].numeroMaillot); 
        printf("Poste de joueur: %s\n", joueurs[i].poste); 
    }
}

void modifier(){

}

void supprimer(){

}

void rechercher(){

}

void Stat(){

}

int main(){

    ajouter();
    afficher();

    return 0;
}