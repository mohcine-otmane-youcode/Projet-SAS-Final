#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Joueur{
    char Id[6];
    char nom[10];
    int numeroMaillot;
    char poste;
    struct tm* dateNaissance;
    int age;
    int buts;
    struct tm* dateInscription;
    char statut[10];
};
struct tm dateNaissance = {0};
int nombre_joueurs = 0,util_exit=0;
struct Joueur joueurs[10];//Tableau doit etre dynamique

void initialiserId(struct Joueur* joueur) {
    char id[6] = "A0001";
    
	int id_unique;
	//Id unique ? (Car l'utilisateur va supprimer des joueurs)
    do{
        id_unique = 1;
        for(int i=0;i<nombre_joueurs;i++){
            id_unique = strcmp(id, joueurs[i].Id);
            if(!id_unique) break;
        }
        if(!id_unique){
            id[0] = 'A' + (nombre_joueurs / 10000);
		    int partieNumero = nombre_joueurs % 10000;
		    for (int i = 4; i >= 1; i--) {
		    	if(i!=4){// Id doit commencer par A0001
		    		id[i] = '0' + (partieNumero % 10);
				}else{
					id[i] = '1' + (partieNumero % 10);
				}
				partieNumero = partieNumero/10;
		        
		    }
		    id[5] = '\0';
        }
    }while(!id_unique);
    strcpy(joueur->Id, id);
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
	//Calculer l'age de joueur
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


int menu(){
	int choix, choix_dispo[7] = {1,2,3,4,5,6,7};
	printf("\t\t\t\t=============PROJET DE FIN DE SAS 2025=============\n\n");
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
    }while(!choix_valide(choix,choix_dispo,7));
    printf("le choix est: %d\n",choix);
	return choix;
}


int ajouter_un_joueur(){
    int nombre_joueurs_avant = nombre_joueurs, numeroMaillot,estInt;
    char poste_dispo[4] = {'g', 'd', 'm', 'a'};
    struct Joueur Njoueur;
    
    initialiserId(&Njoueur);

	printf("Nom de joueur: ");
    scanf(" %s", &Njoueur.nom);
    printf("\n");
    
    initialiserDate(&Njoueur);
    calculerAge(&Njoueur);
    
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
    
    printf("\n");
    printf("Succes: Le joueur a ete ajoute\n");
    joueurs[nombre_joueurs] = Njoueur;
    
    nombre_joueurs++;
}

void afficher_un_joueur(int IdJoueur){
	printf("ID de joueur: %s\n", joueurs[IdJoueur].Id);
	printf("Nom de joueur: %s\n", joueurs[IdJoueur].nom);
	printf("Date de naissance de joueur: %d-%d-%d\n", joueurs[IdJoueur].dateNaissance->tm_mday, joueurs[IdJoueur].dateNaissance->tm_mon+1, joueurs[IdJoueur].dateNaissance->tm_year+1900);
    printf("Age de joueur: %d\n", joueurs[IdJoueur].age);
    printf("Numero de maillot de joueur: %d\n", joueurs[IdJoueur].numeroMaillot);
    printf("Numere de buts de joueur: %d\n", joueurs[IdJoueur].buts);
	switch(joueurs[IdJoueur].poste){
    	case 'g':
    		printf("Poste de joueur: Gardien\n");
    		break;
    	case 'd':
    		printf("Poste de joueur: Defenseur\n");
    		break;
    	case 'm':
    		printf("Poste de joueur: Milieu\n");
    		break;
    	case 'a':
    		printf("Poste de joueur: Attaquant\n");
    		break;    		
	}
    
}

void ajouter(){
	int choix, choix_dispo[3] = {0,1,2};
	Ajouter:
	system("cls");
    printf("Ajouter un joueur\n");
    printf("1: Ajouter un nouveau joueur.\n");
    printf("2: Ajouter plusieurs joueurs en une seule operation.\n");
    printf("0. Menu Principale\n");
        
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





void afficher(){
    if(nombre_joueurs>0){
    	printf("Les joueurs disponibles\n");
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


void supprimer(){
	char id[6], index, oui_non,id_existe;
	afficher();
	printf("ID de joueur a supprimer: ");
	scanf("%s", &id);
	for(int i=0;i<nombre_joueurs;i++){
		if(strcmp(id,joueurs[i].Id)==0){
			id_existe = 1;
			index = i;
			break;
		}
	}
	if(id_existe){
		printf("Le joueur avec ID = %s existe, il va etre supprimer\n", id);
		printf("Supprimer?: o=oui n=non\n");
		scanf("%c", &oui_non);
	}
}

void rechercher(){
	char id[6];
	int choix, choix_dispo[3] = {0,1,2};
	printf("MENU DE RECHERCHE\n");
	printf("1. Recherche par ID\n");
	printf("2. Rcharche par nom\n");
	printf("0. Menu Principale\n");
	do{
        printf("\n\nChoix->: ");
        scanf("%d",&choix);
        printf("Choix = %d",choix);
        printf("\n\n");
        if(!choix_valide(choix,choix_dispo,3)){
        	printf("Erreur: entrer soit 0,1 ou 2\n");
        	while(getchar()!='\n');        	
		}
    }while(!choix_valide(choix,choix_dispo,3));
	printf("\n");
	
	if(choix==0){
		return;
	} else if(choix==1){
		printf("ID de joueur a chercher: ");
		scanf("%d",&id);
		for(int i=0;i<nombre_joueurs;i++){
			if(strcmp(id,joueurs[i].Id)==0){
				printf("Le joureur avec ID = %s est trouve\n",id);
				afficher_un_joueur(i);
				break;
			}
		}
		printf("\n");
	} else if(choix==2){
		printf("Rcharche par nom\n");
	}
	printf("Apuier Entrer pour continuer\n");
	getchar();
	getchar();
}


int age_moyen(){
	int s=0;
	for(int i=0;i<nombre_joueurs;i++){
		s = s + joueurs[i].age;
	}
	return s/nombre_joueurs;
}

void stat(){
	int choix, choix_dispo[6] = {0,1,2,3,4,5};
	stat:
		system("cls");
		printf("Statistiques\n\n");
		printf("1: Afficher le nombre total de joueurs dans l’équipe.\n");
		printf("2: Afficher l’âge moyen des joueurs.\n");
		printf("3: Afficher les joueurs ayant marqué plus de X buts (X introduit par l’utilisateur).\n");
		printf("4: Afficher le meilleur buteur (joueur avec le maximum de buts).\n");
		printf("5: Afficher le joueur le plus jeune et le plus âgé.\n");
		printf("0: Menu Principale\n\n");
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
		}
		printf("Apuier sur Entrer pour continuer\n");
		getchar();
		getchar();
	goto stat;
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
	int choix = 0;
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