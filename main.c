#include <stdio.h>
#include <string.h>
#include <time.h>

//struct Date{
//    int jour;
//    int mois;
//    int annee;
//};

struct Joueur{
    char Id[4];
    char nom[10];
    int numeroMaillot;
    char poste[10];
    time_t dateNaissance;
    int buts;
//    struct Date dateInscription;
    char statut[10];
};

int nombre_joueurs = 0, choix, estInt;;
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


int age_joueur(time_t dateNaissance, time_t time_now){
	return time_now-dateNaissance;
}

int choix_valide(int choix, int choix_dispo[], int nombre_choix){
	int valide = 0;
	for(int i=0;i<nombre_choix;i++){
		if(choix==choix_dispo[i]){
			valide = 1;
		}
	}
	return valide;
}


int menu(){
	int choix, choix_dispo[7] = {1,2,3,4,5,6,7};
	printf("\t\t\t\t=============PROJET DE FIN DE SAS=============\n\n");
	printf("\t\t\t\t\t========Mohcine OTMANE======\n");
	printf("\t\t\t\t\t========Houssni OUCHAD======\n\n");
	printf("1. Ajouter des joueurs\n");
	printf("2. Voir tout les joueurs\n");
	printf("3. Modifier un joueur \n");
	printf("4. Supprimer un joueur \n");
	printf("5. Rechercher un joueur \n");
	printf("6. Statistiques\n");
	printf("7. About\n");
	do{
        printf("\n\nChoix->: ");
        scanf("%d",&choix);
        printf("\n\n");
        if(!choix_valide(choix,choix_dispo,7)){
        	printf("Choix non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(!choix_valide(choix,choix_dispo,2));
	return choix;
}


int ajouter_un_joueur(){
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
        getchar();
        estInt = scanf("%d", &numeroMaillot);
        printf("\n");
        //numeroMaillot unique ?
        for(int i=0;i<nombre_joueurs;i++){
            if(numeroMaillot==joueurs[i].numeroMaillot){
                numeroMaillot_unique = 0;
            }
        }
        if(numeroMaillot_unique==0){
            printf("Ce numero de maillot existe deja\n");
        }
    }while(!numeroMaillot_unique || numeroMaillot<0 || !estInt);
    Njoueur.numeroMaillot = numeroMaillot;
    
    printf("Poste de joueur: ");
    scanf("%s", &Njoueur.poste); 
    printf("\n");
    printf("Succes: Le joueur a ete ajoute\n");
    joueurs[nombre_joueurs] = Njoueur;
    nombre_joueurs++;
}

void ajouter(){
	int choix_dispo[2] = {1,2};
    printf("Ajouter un joueur\n");
    printf("1: Ajouter un nouveau joueur.\n");
    printf("2: Ajouter plusieurs joueurs en une seule operation.\n");
        
    do{
        printf("\n\nChoix->: ");
        scanf("%d",&choix);
        printf("\n\n");
        if(!choix_valide(choix,choix_dispo,2)){
        	printf("Choix non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(!choix_valide(choix,choix_dispo,2));
    

    if(choix==1){
        ajouter_un_joueur();
    } else{
        printf("2: Ajouter plusieurs joueurs en une seule operation.\n");
        for(int i=0;i<4;i++){
        	ajouter_un_joueur();
		}
    }
}


void Afficher_un_joueur(int IdJoueur){
	printf("Nom de joueur: %s\n", joueurs[IdJoueur].nom); 
    printf("Numero de maillot de joueur: %s\n", joueurs[IdJoueur].numeroMaillot); 
    printf("Poste de joueur: %s\n", joueurs[IdJoueur].poste); 
}


void afficher(){
    if(nombre_joueurs>0){
    	printf("Les joueurs disponibles\n");
    	for(int i=0;i<nombre_joueurs;i++){
        	Afficher_un_joueur(i); 
    	}
	} else {
		printf("Pas de joueurs disponibles\n");
	}
}

void modifier(){

}

void supprimer(){
	afficher();
	
}

void rechercher(){
	char id[5], estInt;
	printf("MENU DE RECHERCHE\n");
	printf("1. Recherche par ID\n");
	printf("2. Rcharche par nom\n");
	do{
        printf("\n\nChoix->: ");
        scanf("%d",&choix);
        printf("\n\n");
        if(!choix_valide(choix,choix_dispo,2)){
        	printf("Choix non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(!choix_valide(choix,choix_dispo,2));
    
	printf("\n");
	
	do{
		printf("ID de joueur a chercher: ");
	}while(id[0]>'Z' || id[1]>'9'|| id[2]>'9'|| id[3]>'9'|| id[4]>'9');
	printf("\n");
	for(int i=0;i<nombre_joueurs;i++){
    	if(id==joueurs[i].Id){
    		printf("Le joueur avec ID = %s est trouve\n",id);
    		Afficher_un_joueur(i);
		}
    }
}

void Stat(){

}

void about(){
	printf("\t\t\t\t=============PROJET DE FIN DE SAS 2025=============\n\n");
	printf("\t\t\t\t=============YouCode=============\n\n");
	printf("\t\t\t\t\t========Realise par: Mohcine OTMANE======\n");
	printf("\t\t\t\t\t========Formateur: Houssni OUCHAD======\n\n");
	printf("Clicker Entrer pour revenir au Menu\n");
	getchar();
	getchar();
}

int main(){
	int choix, util_exit=0;
	do{
		choix = menu();
		switch(choix){
			case 1:
				ajouter();
			case 2:
				afficher();
			case 3:
				modifier();
			case 4:
				supprimer();
			case 5:
				rechercher();
			case 6:
				stat();
			case 7:
				about();
		}
		
	}while(!util_exit);

    return 0;
}