#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Joueur{
	int numeroMaillot;
	int age; //Calculer automatiquement
    int buts;
    char Id[6]; //Un id unique: généré automatiquement pour identifier chaque joueur. 
    char nom[10]; //Nom et prenom
    char poste; //poste : permet de distinguer les rôles (gardien, défenseur, milieu, attaquant). 
	char statut; //statut (bonus) : indique si le joueur est "titulaire" ou "remplaçant".  
    struct tm* dateNaissance;
	struct tm* dateInscription;
};
struct tm dateNaissance = {0};
int nombre_joueurs = 3,util_exit=0, nombre_id = 3, estInt;

char poste_dispo[4] = {'g', 'd', 'm', 'a'};

//--------------Initialisations--------------
struct Joueur equipe[10] = {
    { .numeroMaillot = 10, .age = 0, .buts = 15, .Id = "0001", .nom = "Wahid", .poste = 'a', .statut = 't', 
      .dateNaissance = &(struct tm){.tm_mday=24, .tm_mon=5-1, .tm_year=1999-1900}, 
      .dateInscription = &(struct tm){.tm_mday=1, .tm_mon=1-1, .tm_year=2023-1900} },

    { .numeroMaillot = 1, .age = 0, .buts = 0, .Id = "0002", .nom = "Sali", .poste = 'g', .statut = 't', 
      .dateNaissance = &(struct tm){.tm_mday=27, .tm_mon=3-1, .tm_year=1986-1900}, 
      .dateInscription = &(struct tm){.tm_mday=1, .tm_mon=1-1, .tm_year=2023-1900} },

    { .numeroMaillot = 4, .age = 0, .buts = 5, .Id = "0003", .nom = "Arbi", .poste = 'd', .statut = 'r', 
      .dateNaissance = &(struct tm){.tm_mday=30, .tm_mon=3-1, .tm_year=1988-1900}, 
      .dateInscription = &(struct tm){.tm_mday=1, .tm_mon=1-1, .tm_year=2023-1900} },
      
    { .numeroMaillot = 6, .age = 0, .buts = 7, .Id = "0004", .nom = "Dahmoch", .poste = 'm', .statut = 't', 
      .dateNaissance = &(struct tm){.tm_mday=34, .tm_mon=7-1, .tm_year=1999-1900}, 
      .dateInscription = &(struct tm){.tm_mday=1, .tm_mon=3-1, .tm_year=2025-1900} }
};
void initialiserId(struct Joueur* joueur) {
    char id[6];

    //Validation de nouveau ID
    sprintf(id, "%04d", nombre_id + 1);
    strcpy(joueur->Id, id);
    nombre_id++;
    printf("\x1b[1;32mID inisialise: %s\x1b[0m\n", id);
}
void initialiserDate(struct Joueur* joueur){
	int estInt;
	printf("Entrer la date de naissance de joueur\n");
	do{
        printf("Jour:\\> ");
        estInt = scanf("%d",&dateNaissance.tm_mday);
        printf("\n\n");
        if(dateNaissance.tm_mday>30 || dateNaissance.tm_mday<0 || !estInt){
        	printf("Jours non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(dateNaissance.tm_mday>30 || dateNaissance.tm_mday<0 || !estInt);
    do{
        printf("Mois:\\> ");
        estInt = scanf("%d",&dateNaissance.tm_mon);
        printf("\n\n");
        if(dateNaissance.tm_mon>12 || dateNaissance.tm_mon<0 || !estInt){
        	printf("Mois non valide\n");
        	while(getchar()!='\n');      	
		}
    }while(dateNaissance.tm_mon>12 || dateNaissance.tm_mon<0 || !estInt);
    do{
        printf("Annee:\\> ");
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
    printf("\x1b[1;32mDate inisialise\x1b[0m\n");
}
void calculerAge(struct Joueur* joueur){
	time_t temps_0 = time(0);
	struct tm* date_aujourdhui = localtime(&temps_0);
	joueur->age = date_aujourdhui->tm_year - joueur->dateNaissance->tm_year;
    printf("\x1b[1;32mAge calcule\x1b[0m\n");
}
int entrer_choix(int *choix ,int nombre_choix){
    int bon_choix = 0;
    do{
        printf("\n\nChoix:\\> ");
        scanf("%d",choix);
        printf("\n\n");
        for(int i=0;i<nombre_choix;i++){
            if(*choix==i){
                bon_choix=1;
            }
        }
    }while(!bon_choix);
}

//--------------Afficher--------------
void trier_nom() {
    for(int i = 0; i < nombre_joueurs - 1; i++) {
        for(int j = i + 1; j < nombre_joueurs; j++) {
            if(strcmp(equipe[i].nom, equipe[j].nom) > 0) {
                struct Joueur temp = equipe[i];
                equipe[i] = equipe[j];
                equipe[j] = temp;
            }
        }
    }
    printf("\x1b[1;32mTriage par nom fait\x1b[0m\n");
}
void trier_age(){
    for(int i = 0; i < nombre_joueurs - 1; i++) {
        for(int j = i + 1; j < nombre_joueurs; j++) {
            if(equipe[i].age > equipe[j].age) {
                struct Joueur temp = equipe[i];
                equipe[i] = equipe[j];
                equipe[j] = temp;
            }
        }
    }
    printf("\x1b[1;32mTriage par age fait\x1b[0m\n");
}

void afficher_un_joueur(int index_joueur){
	struct Joueur *joueur = &equipe[index_joueur]; //Prendre l'address de joueur
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
    int choix;
    char poste;
    Affichage:
        printf("\t\t\t\t\t\x1b[42m           MENU DE AFFICHAGE           \x1b[0m\n\n");
        printf("\t\t\t\t\t1. Trier les joueurs par Nom.\n");//v
        printf("\t\t\t\t\t2. Trier les joueurs par Age.\n");//v
        printf("\t\t\t\t\t3. Afficher les joueurs par poste.\n");//v
        printf("\t\t\t\t\t0. Menu Principale\n");
        entrer_choix(&choix, 4);
        if(choix==0){
            return;
        } else if(choix==1){
            printf("Triage par nom complete\n");
            trier_nom();
        } else if(choix==2){
            printf("Triage par age complete\n");
            trier_age();
        } else if(choix==3){
            do{
                printf("Poste(g:gardien, d:defenseur, m:milieu, a:attaquant): ");
                scanf(" %c",&poste);
                printf("\n\n");
                if(poste!='g' && poste!='d' && poste!='m' && poste!='a'){
                    printf("Choix non valide\n");
                    while(getchar()!='\n');        	
                }
            }while(poste!='g' && poste!='d' && poste!='m' && poste!='a');
            printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
            if(choix==3){
                for(int i=0;i<nombre_joueurs;i++){
                    if(equipe[i].poste==poste){
                        afficher_un_joueur(i); 
                    }
                }
            }
        }
        getchar();
        getchar();
    goto Affichage;
}

//--------------Ajouter--------------
int ajouter_un_joueur(){
    int nombre_joueurs_avant = nombre_joueurs,estInt, numeroMaillot_unique;
    struct Joueur Njoueur;

    initialiserId(&Njoueur);


    printf("Nom:\\> ");
    scanf(" %[^\n]", &Njoueur.nom);
    printf("\n\n");

    initialiserDate(&Njoueur);
    calculerAge(&Njoueur);

    do{
        numeroMaillot_unique = 1;
        printf("Numero de maillot:\\> ");
        getchar();
        estInt = scanf("%d", &Njoueur.numeroMaillot);
        printf("\n");
        //numeroMaillot unique ?
        for(int i=0;i<nombre_joueurs;i++){
            if(Njoueur.numeroMaillot==equipe[i].numeroMaillot){
                numeroMaillot_unique = 0;
            }
        }
        if(numeroMaillot_unique==0){
            printf("Ce numero de maillot existe deja\n");
        }
    }while(!numeroMaillot_unique || Njoueur.numeroMaillot<0 || !estInt);
    // Njoueur.numeroMaillot = numeroMaillot;
    
    do{
        printf("Poste(g:Gardien, d:Defenseur, m:Milieu, a:Attaquant):\\> ");
        scanf(" %c",&Njoueur.poste);
        printf("\n\n");
        if(Njoueur.poste!='g' && Njoueur.poste!='d' && Njoueur.poste!='m' && Njoueur.poste!='a'){
        	printf("Choix non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(Njoueur.poste!='g' && Njoueur.poste!='d' && Njoueur.poste!='m' && Njoueur.poste!='a');
    
    do{
        printf("Buts:\\> ");
        estInt = scanf("%d",&Njoueur.buts);
        printf("\n\n");
        if(Njoueur.buts<0 || !estInt){
        	printf("Nombre de buts non valide\n");
        	while(getchar()!='\n');
		}
    }while(Njoueur.buts<0 || !estInt);

    do{
        printf("Statut(t:Tutolaire, r:Remplacant):\\> ");
        scanf(" %c",&Njoueur.statut);
        printf("\n\n");
        if(Njoueur.statut!='t' && Njoueur.statut!='r'){
        	printf("Choix non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(Njoueur.statut!='t' && Njoueur.statut!='r');
    
    printf("\n\n");

    equipe[nombre_joueurs] = Njoueur;
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
        printf("\n\nChoix:\\> ");
        scanf("%d",&choix);
        printf("\n\n");
        if(choix!=0 && choix!=1 && choix!=2){
        	printf("Choix non valide\n");
        	while(getchar()!='\n');        	
		}
    }while(choix!=0 && choix!=1 && choix!=2);
    

    if(choix==0){
        return;
    } else if(choix==1){
        printf("1: Ajouter un joueur.\n");
        ajouter_un_joueur();
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
        printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
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

//--------------Modifications--------------
int touve_joueur_par_id(char id[]){
    int index_joueur;
    for(int i=0;i<nombre_joueurs;i++){
        if(strcmp(id, equipe[i].Id)==0){
            return i;
        }
    }
    return -1;
}
void modifier(){
    char id[6], index_joueur, poste;
    int choix, choix_dispo[4] = {0, 1, 2, 3};
    Modifier:
        printf("\t\t\t\t\x1b[42m           MENU DE MODIFICATIONS           \x1b[0m\n\n");
        printf("\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
        for(int i=0;i<nombre_joueurs;i++){
            afficher_un_joueur(i);
        }
        if(index_joueur>-1){
        printf("\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
        afficher_un_joueur(index_joueur);
        system("cls");
        printf("\t\t1. Modifier le poste.\n");//v
        printf("\t\t2. Modifier age. \n");//v
        printf("\t\t3. Modifier le nombre de buts. \n");//v
        printf("\t\t0. Menu Precidente\n\n");
        printf("ID:\\> ");
        scanf("%s",&id);
        index_joueur = touve_joueur_par_id(id);

			entrer_choix(&choix,4);
            if(choix==0){
                goto Modifier;
            } else if(choix==1){
                //Validation de nouveau Poste
                do{
                    printf("Poste de joueur  (g:gardien, d:defenseur, m:milieu, a:attaquant): ");
                    scanf(" %c",&poste);
                    printf("\n\n");
                    if(poste!='g' && poste!='d' && poste!='m' && poste!='a'){
                        printf("Choix non valide\n");
                        while(getchar()!='\n');        	
                    }
                }while(poste!='g' && poste!='d' && poste!='m' && poste!='a');
                equipe[index_joueur].poste = poste;
                printf("Poste modifie avec succes\n");
            } else if(choix==2){

            }
            
        }
        printf("Apuyer Entrer pour continuer\n");
        getchar();
        getchar();
    goto Modifier;

}
void supprimer_un_contact(int IdJoueur){
	printf("Le joueur\n");
	printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
	afficher_un_joueur(IdJoueur);
	for (int i = IdJoueur; i < nombre_joueurs - 1; i++) {
        equipe[i] = equipe[i + 1];
    }
    nombre_joueurs--;
}
void supprimer(){
    char id[6];
    int index_joueur = -1;
    int id_existe = 0;

    printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
    for(int i=0;i<nombre_joueurs;i++){
        afficher_un_joueur(i);
    }

    printf("\nID:\\> ");
    scanf("%s", id);

    for(int i=0; i<nombre_joueurs; i++){
        if(strcmp(id, equipe[i].Id)==0){
            id_existe = 1;
            index_joueur = i;
            break;
        }
    }

    if(id_existe){
        printf("\n\x1b[1;33mLe joueur avec ID = %s existe, vous veulez le supprime ?\x1b[0m\n", id);
        printf("(\x1b[1;32mo\x1b[0m = oui, \x1b[1;31mn\x1b[0m = non)\n");

        char reponse;
        do{
            printf("Reponse:\\> ");
            scanf(" %c", &reponse);
            if(reponse!='o' && reponse!='O' && reponse!='y' && reponse!='Y'){
                printf("\x1b[1;31mErreur: choix non valide (o/n)\x1b[0m\n");
                while(getchar()!='\n');
            }
        }while(reponse!='o' && reponse!='O' && reponse!='y' && reponse!='Y');

        if(reponse=='o' || reponse=='O'){
            supprimer_un_contact(index_joueur);
            printf("\n\x1b[1;32mLe joueur supprime avec succes.\x1b[0m\n");
        } else if(reponse=='n' || reponse=='N'){
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

//--------------Rechercher--------------
void rechercher(){
    char id[6];
    char nom[20];
    int choix, trouve, choix_dispo[3] = {0,1,2};

	printf("\t\t\t\t\t\t\t\x1b[42m           MENU DE RECHERCHE           \x1b[0m\n\n");
	printf("\t\t\t\t\t\t\t1. Recherche par \x1b[1;36mID\x1b[0m\x1b[0m\n");
	printf("\t\t\t\t\t\t\t2. Recherche par \x1b[1;36mNom\x1b[0m\n");
	printf("\t\t\t\t\t\t\t0. Retour au \x1b[1;32mMenu Principal\x1b[0m\n");


	entrer_choix(&choix,3);

    printf("\n");

    if(choix==0){
        return;
    } 
    else if(choix==1){
        printf("ID:\\> ");
        scanf("%s", id);
        trouve = 0;
        for(int i=0;i<nombre_joueurs;i++){
            if(strcmp(id, equipe[i].Id)==0){
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
        printf("Nom:\\> ");
        scanf("%s", nom);
        trouve = 0;
        for(int i=0;i<nombre_joueurs;i++){
            if(strcmp(nom, equipe[i].nom)==0){
                printf("\n\x1b[1;32mLe joueur avec nom = %s est trouve :\x1b[0m\n", nom);
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

//--------------Statistiques--------------
int age_moyen(){
	int s=0;
	for(int i=0;i<nombre_joueurs;i++){
		s = s + equipe[i].age;
	}
	return s/nombre_joueurs;
}

int max_min(int un_si_max_age, int un_si_max_buts){//max_min(1,0)->max age, max_min(2,0)->min age, max_min(2,0)->min age, max_min(0,1)->max buts, max(0,2)->min buts
	int max,min;
	if(un_si_max_age==1){
		for(int i=0;i<nombre_joueurs;i++) {
            max = equipe[i].age;
            for(int j= 0;j<nombre_joueurs;j++) {
                if(max < equipe[j].age) {
                    max= equipe[j].age;
                }
            }
        }
		return max;
	} else if(un_si_max_age==2){
        for(int i=0;i<nombre_joueurs;i++) {
            min = equipe[i].age;
            for(int j=0; j<nombre_joueurs;j++) {
                if(min > equipe[j].age) {
                    min= equipe[j].age;
                }
            }
        }
		return min;
	}

    if(un_si_max_buts==1){
		for(int i = 0; i < nombre_joueurs; i++) {
            max = equipe[i].buts;
            for(int j = i + 1; j < nombre_joueurs; j++) {
                if(max < equipe[j].buts) {
                    max= equipe[j].buts;
                }
            }
        }
		return max;
	} else if(un_si_max_buts==2){
        for(int i = 0; i < nombre_joueurs; i++) {
            min = equipe[i].buts;
            for(int j = i + 1; j < nombre_joueurs; j++) {
                if(min > equipe[j].buts) {
                    min= equipe[j].buts;
                }
            }
        }
		return min;
	}
}

void stat(){
	int choix;
	
	stat:
		system("cls");
		printf("\t\t\t\t\x1b[42m           MENU DE STATISTIQUES           \x1b[0m\n\n");
		printf("\t\t\t\t1. Nombre total de joueurs.\n");//v
		printf("\t\t\t\t2. Age moyen des joueurs.\n");//v
		printf("\t\t\t\t3. les joueurs ayant marque plus de X buts.\n");//v
		printf("\t\t\t\t4. Le top buts.\n");//x
		printf("\t\t\t\t5. le joueur le plus jeune et le plus age.\n");//v
		printf("\t\t\t\t0. Menu Principale\n");

	    
	    entrer_choix(&choix, 6);
	    
		printf("\n");
		if(choix==0){
			return;
		}else if(choix==1){
			printf("On a %d joueurs dans le systeme\n",nombre_joueurs);
		} else if(choix==2){
			printf("Age moyen de joueurs est: %d\n",age_moyen());
		} else if(choix==3){
            int X;
			printf("les joueurs ayant marque plus de %d buts", X);

            do{
                printf("\n\nButs:\\> ");
                estInt = scanf("%d",&X);
                printf("\n\n");
                if(!estInt){
                    printf("Erreur: Nombre de buts doit etre positif\n");
                    while(getchar()!='\n');
                }
            }while(!estInt || X<0);
            printf("Les Joueurs qui ont marque plus de %d buts sont\n\n", X);
            printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
            for(int i=0;i<nombre_joueurs;i++){
                if(equipe[i].buts>=X){
                    afficher_un_joueur(i);
                }
            }
        } else if(choix==4){
			printf("Afficher le meilleur buteur\n");
            printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
            int max_buts = max_min(0,1);
            for(int i=0;i<nombre_joueurs;i++){
                if(equipe[i].buts==max_buts){
                    afficher_un_joueur(i);
                }
            }
		} else if(choix==5){
			printf("Le joueur le plus jeune\n");
            printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
            for(int i=0;i<nombre_joueurs;i++){
                if(equipe[i].age==max_min(2,0)){
                    afficher_un_joueur(i);
                }
            }
            printf("\n\n");
            printf("Le joueur le plus age\n");
            printf("\t\t\t\t\t\x1b[44m%-5s %-10s %-15s %-5s %-5s %-15s %-15s\x1b[0m\n","ID", "Nom", "Numero", "Age", "Buts", "Poste", "Statut");
            for(int i=0;i<nombre_joueurs;i++){
                if(equipe[i].age==max_min(1,0)){
                    afficher_un_joueur(i);
                }
            }
		}
		printf("Apuyer sur Entrer pour continuer\n");
		getchar();
		getchar();
	goto stat;
}
//--------------Presentation--------------
void about(){
	printf("\t\t\t\t\t\x1b[1;34;4m     PROJET DE FIN DE SAS 2025     \x1b[0m\n\n");
	printf("\t\t\t\t\t           \x1b[1;34;4mMohcine OTMANE\x1b[0m          \n\n");
	printf("\t\t\t\t\t           \x1b[1;34;4mHoussni OUCHAD\x1b[0m          \n\n");
	printf("\t\t\t\t\t                           _     \n");
	printf("\t\t\t\t\t  _  _ ___ _  _ __ ___  __| |___ \n");
	printf("\t\t\t\t\t | || / _ \\ || / _/ _ \\/ _` / -_) \n");
	printf("\t\t\t\t\t  \\_, \\___/\\_,_\\__\\___/\\__,_\\___| \n");
	printf("\t\t\t\t\t  |__/                            \x1b[0m\n");
	printf("\t\t\t\t\t               \x1b[1;1;37mYou\x1b[0m\x1b[1;34mCode\x1b[0m          \n\n");
	printf("Clicker Entrer pour revenir au Menu\n");
	getchar();
	getchar();
}


//--------------Stockage---------------

void enregestrer_dans_fichier(FILE *fich){
    //Ouvrir le fichier
    fich = fopen("equipe.txt","r");
    if(fich == NULL){
        printf("Erreur: le fichier ne peut pas etre ouvert");
        return;
    }

    //Ecrire les donnees dans le fichier

    


    //Fermer le fichier
    fclose(fich);
}

void lire_de_fichier(FILE *fich){
    //Ouvrir le fichier
    fich = fopen("equipe.txt","r");
    if(fich == NULL){
        printf("Erreur: le fichier ne peut pas etre ouvert");
        return;
    }

    //Lire les donnees de fichier

    


    //Fermer le fichier
    fclose(fich);

}

int menu(){
	printf("\t\t\t\t\t\x1b[42m           MENU PRINCIPALE           \x1b[0m\n\n");
	printf("\t\t\t\t\t\x1b[1;32m1. Ajouter des joueurs\x1b[0m\n");//v
	printf("\t\t\t\t\t2. Voir tous les joueurs\n");//v
	printf("\t\t\t\t\t3. Modifier un joueur\n");//x
	printf("\t\t\t\t\t\x1b[1;31m4. Supprimer un joueur\x1b[0m\n");//v
	printf("\t\t\t\t\t5. Rechercher un joueur\n");//v
	printf("\t\t\t\t\t6. Statistiques\n");//x
	printf("\t\t\t\t\t7. About\n");
}
int main(){
	int choix;
	for(int i=0;i<nombre_joueurs;i++){
		calculerAge(&equipe[i]);
	}
	do{
		system("cls");
		menu();
		entrer_choix(&choix, 8);
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