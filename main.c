#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Joueur{
	int numeroMaillot;
	int age;
    int buts;
    char Id[6];
    char nom[10];
    char poste;
	char statut;
    struct tm* dateNaissance;
	struct tm* dateInscription;
};
struct tm dateNaissance = {0};
int nombre_joueurs = 3,util_exit=0, nombre_id_historiques = 0;

char historique_id[10][6] = {"0001","0002","0003"};//id supprime ne doit pas etre reutilise

struct Joueur joueurs[10] = {
    { .numeroMaillot = 10, .age = 0, .buts = 15, .Id = "0001", .nom = "Wahid", .poste = 'a', .statut = 't', 
      .dateNaissance = &(struct tm){.tm_mday=24, .tm_mon=5-1, .tm_year=1987-1900}, 
      .dateInscription = &(struct tm){.tm_mday=1, .tm_mon=1-1, .tm_year=2023-1900} },

    { .numeroMaillot = 1, .age = 0, .buts = 0, .Id = "0002", .nom = "Sali", .poste = 'g', .statut = 't', 
      .dateNaissance = &(struct tm){.tm_mday=27, .tm_mon=3-1, .tm_year=1986-1900}, 
      .dateInscription = &(struct tm){.tm_mday=1, .tm_mon=1-1, .tm_year=2023-1900} },

    { .numeroMaillot = 4, .age = 0, .buts = 5, .Id = "0003", .nom = "Arbi", .poste = 'd', .statut = 'r', 
      .dateNaissance = &(struct tm){.tm_mday=30, .tm_mon=3-1, .tm_year=1986-1900}, 
      .dateInscription = &(struct tm){.tm_mday=1, .tm_mon=1-1, .tm_year=2023-1900} }
};

void initialiserId(struct Joueur* joueur) {
    char id[6];
    sprintf(id, "%04d", nombre_id_historiques + 1);
    strcpy(joueur->Id, id);
    strcpy(historique_id[nombre_id_historiques], id);
    nombre_id_historiques++;
}


void initialiserDate(struct Joueur* joueur){
	int estInt;
	printf("Entrer la date de naissance de joueur\n");
	do{
        printf("Jour: ");
        estInt = scanf("%d",&dateNaissance.tm_mday);
        printf("\n\n");
        if(dateNaissance.tm_mday>30 || dateNaissance.tm_mday<0 || !estInt){
        	printf("Jours non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(dateNaissance.tm_mday>30 || dateNaissance.tm_mday<0 || !estInt);
    do{
        printf("Mois: ");
        estInt = scanf("%d",&dateNaissance.tm_mon);
        printf("\n\n");
        if(dateNaissance.tm_mon>12 || dateNaissance.tm_mon<0 || !estInt){
        	printf("Mois non valide\n");
        	while(getchar()!='\n');      	
		}
    }while(dateNaissance.tm_mon>12 || dateNaissance.tm_mon<0 || !estInt);
    do{
        printf("Annee: ");
        estInt = scanf("%d",&dateNaissance.tm_year);
        printf("\n\n");
        if(dateNaissance.tm_year<1980){
        	printf("Annee non valide\n");
        	while(getchar()!='\n');    	
		}
    }while(dateNaissance.tm_year<1980 || dateNaissance.tm_year<0 || !estInt);
    dateNaissance.tm_year -= 1900;
    dateNaissance.tm_mon -= 1;
    joueur->dateNaissance = &dateNaissance;
}

void calculerAge(struct Joueur* joueur){
	time_t temps_0 = time(0);
	struct tm* date_aujourdhui = localtime(&temps_0);
	joueur->age = date_aujourdhui->tm_year - joueur->dateNaissance->tm_year;
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

int char_valide(char poste,char poste_dispo[],int nombre_poste){
	int valide = 0;
	for(int i=0;i<nombre_poste;i++){
		if(poste==poste_dispo[i]){
			valide = 1;
		}
	}
	return valide;
}





void trier_nom() {
    for(int i = 0; i < nombre_joueurs - 1; i++) {
        for(int j = i + 1; j < nombre_joueurs; j++) {
            if(strcmp(joueurs[i].nom, joueurs[j].nom) > 0) {
                struct Joueur min = joueurs[i];
                joueurs[i] = joueurs[j];
                joueurs[j] = min;
            }
        }
    }
}

void afficher_un_joueur(int IdJoueur){
	struct Joueur *joueur = &joueurs[IdJoueur];
	char postes[20], statuts[20];
    switch(joueur->poste){
        case 'g': strcpy(postes, "Gardien"); break;
        case 'd': strcpy(postes, "Defenseur"); break;
        case 'm': strcpy(postes, "Milieu"); break;
        case 'a': strcpy(postes, "Attaquant"); break;
        default: strcpy(postes, "Inconnu"); break;
    }
    switch(joueur->statut){
        case 't': strcpy(statuts, "Titulaire"); break;
        case 'r': strcpy(statuts, "Remplacant"); break;
        default: strcpy(statuts, "Inconnu"); break;
    }

	printf("\t\t\t\t\t%-5s %-10s %-15d %-5d %-5d %-15s %-15s\n\n",joueur->Id,joueur->nom,joueur->numeroMaillot,joueur->age,joueur->buts,postes,statuts);

}

void afficher(){
	printf("\t\t\t\t\t\t\t\x1b[42m           MENU DE AFFICHAGE           \x1b[0m\n\n");
	printf("\t\t\t\t\t\t\t1. Trier les joueurs par Nom.\n");
	printf("\t\t\t\t\t\t\t2. Trier les joueurs par Age.\n");
	printf("\t\t\t\t\t\t\t2. Afficher les joueurs par poste.\n");
	printf("\t\t\t\t\t\t\t0. Menu Principale\n");
	// trier_nom();
	printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
    if(nombre_joueurs>0){
    	for(int i=0;i<nombre_joueurs;i++){
        	afficher_un_joueur(i); 
    	}
	} else {
		printf("Pas de joueurs disponibles\n");
	}
	getchar();
	getchar();
}

void modifier(){
	
}
int ajouter_un_joueur(){
    int nombre_joueurs_avant = nombre_joueurs,estInt, numeroMaillot_unique;
    char poste_dispo[4] = {'g', 'd', 'm', 'a'};
    struct Joueur Njoueur;

    initialiserId(&Njoueur);
	printf("Nom de joueur: ");
    scanf(" %s", &Njoueur.nom);
    printf("\n");
    initialiserDate(&Njoueur);
    calculerAge(&Njoueur);

    do{
        numeroMaillot_unique = 1;
        printf("Numero de maillot de joueur: ");
        getchar();
        estInt = scanf("%d", &Njoueur.numeroMaillot);
        printf("\n");
        //numeroMaillot unique ?
        for(int i=0;i<nombre_joueurs;i++){
            if(Njoueur.numeroMaillot==joueurs[i].numeroMaillot){
                numeroMaillot_unique = 0;
            }
        }
        if(numeroMaillot_unique==0){
            printf("Ce numero de maillot existe deja\n");
        }
    }while(!numeroMaillot_unique || Njoueur.numeroMaillot<0 || !estInt);
    // Njoueur.numeroMaillot = numeroMaillot;
    
    printf("Poste de joueur  (g:gardien, d:defenseur, m:milieu, a:attaquant): ");
    scanf("%c", &Njoueur.poste);
    do{
        printf("\n\nChoix->: ");
        scanf("%c",&Njoueur.poste);
        printf("\n\n");
        if(!char_valide(Njoueur.poste,poste_dispo,4)){
        	printf("Choix non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(!char_valide(Njoueur.poste,poste_dispo,4));
    
    do{
        printf("Nombre de buts de joueur: ");
        scanf("%d",&Njoueur.buts);
        printf("\n\n");
        if(Njoueur.buts<0){
        	printf("Nombre de buts non valide\n");
        	while(getchar()!='\n');
		}
    }while(Njoueur.buts<0);
    
    printf("\n\n");

    joueurs[nombre_joueurs] = Njoueur;
	printf("\n\x1b[1;32mJoueur ajoute avec succes\x1b[0m\n");
	printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
	afficher_un_joueur(nombre_joueurs);
    
    nombre_joueurs++;
}
void ajouter(){
	int choix, choix_dispo[3] = {0,1,2};
	Ajouter:
	system("cls");
	printf("\t\t\t\t\t\t\t\x1b[42m           MENU DE AJOUTE           \x1b[0m\n\n");
	printf("\t\t\t\t\t\t\t\x1b[1;32m1. Ajouter un nouveau joueur.\x1b[0m\n");
	printf("\t\t\t\t\t\t\t2. Ajouter plusieurs joueurs en une seule operation.\n");
	printf("\t\t\t\t\t\t\t0. Menu Principale\n");
        
    do{
        printf("\n\nChoix->: ");
        scanf("%d",&choix);
        printf("\n\n");
        if(!choix_valide(choix,choix_dispo,3)){
        	printf("Choix non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(!choix_valide(choix,choix_dispo,3));
    

    if(choix==0){
        return;
    } else if(choix==1){
        printf("1: Ajouter un joueur.\n");
        ajouter_un_joueur();
        printf("Le joueur\n\n");
        afficher_un_joueur(nombre_joueurs-1);
        printf("\n\nEst ajoute avec succes\n");
        printf("Appuier sur Entrer pour continuer\n");
        getchar();
        getchar();
    } else{
    	printf("2: Ajouter plusieurs joueurs en une seule operation.\n");
        for(int i=0;i<4;i++){
        	printf("Il vous reste %d joueurs a entrer\n",4-i);
        	ajouter_un_joueur();
		}
		printf("Les joueurs\n\n");
		for(int i=0;i<4;i++){
	        afficher_un_joueur(nombre_joueurs-i-1);
		}
	    printf("\n\nOnt ete ajoutes avec succes\n\n");
        printf("Appuier sur Entrer pour continuer\n");
        getchar();
        getchar();
	}
	goto Ajouter;
}
void supprimer_un_contact(int IdJoueur){
	printf("Le joueur\n");
	printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
	afficher_un_joueur(IdJoueur);
	for (int i = IdJoueur; i < nombre_joueurs - 1; i++) {
        joueurs[i] = joueurs[i + 1];
    }
    nombre_joueurs--;
}
void supprimer(){
    char id[6];
    int index_joueur = -1;
    int id_existe = 0;

    afficher();

    printf("\nID du joueur: ");
    scanf("%s", id);

    for(int i=0; i<nombre_joueurs; i++){
        if(strcmp(id, joueurs[i].Id)==0){
            id_existe = 1;
            index_joueur = i;
            break;
        }
    }

    if(id_existe){
        printf("\n\x1b[1;33mLe joueur avec ID = %s existe, vous veulez le supprime ?\x1b[0m\n", id);
        printf("(\x1b[1;32mo\x1b[0m = oui, \x1b[1;31mn\x1b[0m = non)\n");

        char oui_non;
        char choix_dispo[4] = {'o','n','O','N'};

        do{
            printf("Choix -> ");
            scanf(" %c", &oui_non);
            if(!char_valide(oui_non, choix_dispo, 4)){
                printf("\x1b[1;31mErreur: choix non valide (o/n)\x1b[0m\n");
                while(getchar()!='\n');
            }
        }while(!char_valide(oui_non, choix_dispo, 4));

        if(oui_non=='o' || oui_non=='O'){
            supprimer_un_contact(index_joueur);
            printf("\n\x1b[1;32mLe joueur supprime avec succes.\x1b[0m\n");
        } else {
            printf("\n\x1b[1;34mLe joueur pas supprime.\x1b[0m\n");
            return;
        }
    } else {
        printf("\n\x1b[1;31mJoueur pas trouve.\x1b[0m\n");
    }

    printf("\nAppuyer sur Entrer pour continuer...");
    while(getchar()!='\n');
    getchar();
}
void rechercher(){
    char id[6];
    char nom[20];
    int choix, trouve, choix_dispo[3] = {0,1,2};

	printf("\t\t\t\t\t\t\t\x1b[42m           MENU DE RECHERCHE           \x1b[0m\n\n");
	printf("\t\t\t\t\t\t\t1. Recherche par \x1b[1;36mID\x1b[0m\x1b[0m\n");
	printf("\t\t\t\t\t\t\t2. Recherche par \x1b[1;36mNom\x1b[0m\n");
	printf("\t\t\t\t\t\t\t0. Retour au \x1b[1;32mMenu Principal\x1b[0m\n");

    do{
        printf("\nChoix -> ");
        scanf("%d",&choix);
        if(!choix_valide(choix,choix_dispo,3)){
            printf("\x1b[1;31mErreur: entrer soit 0, 1 ou 2\x1b[0m\n");
            while(getchar()!='\n');
        }
    }while(!choix_valide(choix,choix_dispo,3));

    printf("\n");

    if(choix==0){
        return;
    } 
    else if(choix==1){
        printf("ID du joueur cherche: ");
        scanf("%s", id);
        trouve = 0;
        for(int i=0;i<nombre_joueurs;i++){
            if(strcmp(id, joueurs[i].Id)==0){
                printf("\n\x1b[1;32mLe joueur avec ID = %s est trouve :\x1b[0m\n", id);
				printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
                afficher_un_joueur(i);
                trouve = 1;
                break;
            }
        }
        if(!trouve){
            printf("\n\x1b[1;31mJoueur pas trouve.\x1b[0m\n");
        }
    } 
    else if(choix==2){
        printf("Nom du joueur à chercher: ");
        scanf("%s", nom);
        trouve = 0;
        for(int i=0;i<nombre_joueurs;i++){
            if(strcmp(nom, joueurs[i].nom)==0){
                printf("\n\x1b[1;32mLe joueur avec nom = %s est trouvé :\x1b[0m\n", nom);
                afficher_un_joueur(i);
                trouve = 1;
            }
        }
        if(!trouve){
            printf("\n\x1b[1;31mJoueur pas trouve.\x1b[0m\n");
        }
    }

    printf("\nAppuyer sur Entrer pour continuer...");
    while(getchar()!='\n');
    getchar();
}
int age_moyen(){
	int s=0;
	for(int i=0;i<nombre_joueurs;i++){
		s = s + joueurs[i].age;
	}
	return s/nombre_joueurs;
}

// int max_min(int zerosimax){
// 	int max,min;
// 	if(zerosimax==0){
// 		for(int i=0;)
// 		return max;
// 	} else{

// 		return min;
// 	}
// }

void stat(){
	int choix, choix_dispo[6] = {0,1,2,3,4,5};
	
	stat:
		system("cls");
		printf("\t\t\t\t\t\t\t\x1b[42m           MENU DE STATISTIQUES           \x1b[0m\n\n");
		printf("\t\t\t\t\t\t\t\x1b[1;32m1. Nombre total de joueurs.\x1b[0m\n");//v
		printf("\t\t\t\t\t\t\t2. Age moyen des joueurs.\n");//v
		printf("\t\t\t\t\t\t\t3. les joueurs ayant marque plus de X buts.\n");//x
		printf("\t\t\t\t\t\t\t\x1b[1;31m4. Le top buts.\x1b[0m\n");//x
		printf("\t\t\t\t\t\t\t5. le joueur le plus jeune et le plus age.\n");//x
		printf("\t\t\t\t\t\t\t0. Menu Principale\n");


		do{
	        printf("\n\nChoix->: ");
	        scanf("%d",&choix);
	        printf("\n\n");
	        if(!choix_valide(choix,choix_dispo,6)){
	        	printf("Erreur: entrer soit 0,1,2,3,4 ou 5\n");
	        	while(getchar()!='\n');
			}
	    }while(!choix_valide(choix,choix_dispo,6));
		printf("\n");
		if(choix==0){
			return;
		}else if(choix==1){
			printf("On a %d joueurs dans le systeme\n",nombre_joueurs);
		} else if(choix==2){
			printf("Age moyen de joueurs est: %d\n",age_moyen());
		} else if(choix==3){
			printf("Age moyen de joueurs est: %d\n",age_moyen());
		} else if(choix==4){
			printf("Age moyen de joueurs est: %d\n",age_moyen());
		} else if(choix==5){
			printf("Age moyen de joueurs est: %d\n",age_moyen());
		}
		printf("Apuier sur Entrer pour continuer\n");
		getchar();
		getchar();
	goto stat;
}

void about(){
	printf("\t\t\t\t\t\t\t\x1b[1;34;4m     PROJET DE FIN DE SAS 2025     \x1b[0m\n\n");
	printf("\t\t\t\t\t\t\t           \x1b[1;34;4mMohcine OTMANE\x1b[0m          \n\n");
	printf("\t\t\t\t\t\t\t           \x1b[1;34;4mHoussni OUCHAD\x1b[0m          \n\n");
	printf("\t\t\t\t\t\t\t                           _     \n");
	printf("\t\t\t\t\t\t\t  _  _ ___ _  _ __ ___  __| |___ \n");
	printf("\t\t\t\t\t\t\t | || / _ \\ || / _/ _ \\/ _` / -_) \n");
	printf("\t\t\t\t\t\t\t  \\_, \\___/\\_,_\\__\\___/\\__,_\\___| \n");
	printf("\t\t\t\t\t\t\t  |__/                            \x1b[0m\n");
	printf("\t\t\t\t\t\t\t               \x1b[1;1;37mYou\x1b[0m\x1b[1;34mCode\x1b[0m          \n\n");
	printf("Clicker Entrer pour revenir au Menu\n");
	getchar();
	getchar();
}
int menu(){
	int choix, choix_dispo[7] = {1,2,3,4,5,6,7};
	
	printf("\t\t\t\t\t\t\t\x1b[42m           MENU PRINCIPALE           \x1b[0m\n\n");
	printf("\t\t\t\t\t\t\t\x1b[1;32m1. Ajouter des joueurs\x1b[0m\n");//v
	printf("\t\t\t\t\t\t\t2. Voir tous les joueurs\n");//v
	printf("\t\t\t\t\t\t\t3. Modifier un joueur\n");//x
	printf("\t\t\t\t\t\t\t\x1b[1;31m4. Supprimer un joueur\x1b[0m\n");//v
	printf("\t\t\t\t\t\t\t5. Rechercher un joueur\n");//v
	printf("\t\t\t\t\t\t\t6. Statistiques\n");//x
	printf("\t\t\t\t\t\t\t7. About\n");


	do{
        printf("\n\nChoix->: ");
        scanf("%d",&choix);
        printf("\n\n");
        if(!choix_valide(choix,choix_dispo,7)){
        	printf("Choix non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(!choix_valide(choix,choix_dispo,7));
    printf("le choix est: %d\n",choix);
	return choix;
}

int main(){
	int choix = 0;
	for(int i=0;i<nombre_joueurs;i++){
		calculerAge(&joueurs[i]);
	}
	do{
		system("cls");
		choix = menu();
		switch(choix){
			case 1:
				system("cls");
				ajouter();
				break;
			case 2:
				system("cls");
				afficher();
				break;
			case 3:
				system("cls");
				modifier();
				break;
			case 4:
				supprimer();
				system("cls");
				break;
			case 5:
				system("cls");
				rechercher();
				break;
			case 6:
				system("cls");
				stat();
				break;
			case 7:
				system("cls");
				about();
				break;
			default:
				system("cls");
				menu();
				break;
		}
		
	}while(!util_exit);

    return 0;
}