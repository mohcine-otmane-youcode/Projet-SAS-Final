#include <stdio.h>



struct Joueur{
    char Id[4];
    char nom[10];
    int numeroMaillot;
    char poste[10];
    int age;
    int buts;
};

int nombre_joueurs = 0;
struct Joueur joueurs[nombre_joueurs];

void ajouter(){
    int choix;
    printf("Ajouter un joueur\n");
    printf("1: Ajouter un nouveau joueur.\n");
    printf("2: Ajouter plusieurs joueurs en une seule opération.\n");
    do{
        estInt = scanf("%d",&choix);
    }while(!estInt || (choix!=1 && choix!=2));

    if(choix==1){
        printf("1: Ajouter un nouveau joueur.\n");
        struct Joueur Njoueur;
        printf("Nom de joueur: ");
        scanf("%d", &Njoueur.nom); 
        printf("\n");
        
    } else{
        printf("2: Ajouter plusieurs joueurs en une seule opération.\n");
    }
}

void afficher(){

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




    return0
}