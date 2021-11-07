#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>




//****************** Definition des Listes

//**************** Programme *********************//


typedef struct Programme Prog;
struct Programme {
	int Taille;
	char Nom[255];
	struct Programme* suivant;
};


//****************** Les Pages du Mémoire
typedef struct Pages Page;

struct Pages {
	int num;
	struct Pages * suivant;
	Prog * ProgMemoire;
};
//******************************* Prototypes functions **********************//
int TailleToPages(int a);
Prog *CreerProgramme(int Taille, char Name[255]);
Prog *AjouterProg(Prog *Precedent, Prog *ProgrammeAjouter);
Page *Initialisation(Page * Precedent,int num);
void AfficherProg(Prog *head, Page * headpage);
void AfficherPage(Page *head);
void SupprimerProg(Prog *head,char *nom);
int ViderPage(Page * head,char *nom);
void AfficherPageOccuper(Page *head);
void RechercherProg(Page*Debut,char nom[255]);
void AfficherMemoire(Page * Debut);
int TrouverProg(Prog *head, char *nom);
void color_text(int color);
int extract(int from, int to, char chaine[255],char sousChaine[255]);
//**********************************fonctions*****************************

int TailleToPages(int a){
    int res;
    res = a/100;
    if(a%100!=0){
        res+=1;
    }
    return res;
}


//****************Creation d'un programme
Prog *CreerProgramme(int Taille, char Name[255]) {

    Prog *Resultat = malloc(sizeof(Prog));

    Resultat->Taille = Taille;
  
	strcpy(Resultat->Nom, Name);

    Resultat->suivant = NULL;

    return Resultat;
}

//**********************Ajout d'un programme

Prog *AjouterProg(Prog *Precedent, Prog *ProgrammeAjouter) {
	if(Precedent!=NULL){
        Precedent->suivant = ProgrammeAjouter;
    }
    return ProgrammeAjouter;
}

//***********************Initier les Pages
//********************** N'oublier pas d'affecter le suivant aprés
Page *Initialisation(Page * Precedent,int num){
    Page * PageLibre = malloc(sizeof(Page));
    PageLibre->num = num;
	PageLibre->suivant = NULL;
	PageLibre->ProgMemoire= NULL;
    if(Precedent!=NULL){
        Precedent->suivant = PageLibre;
    }
    return PageLibre;
}

//***************Affichage des Progs**************
void AfficherProg(Prog *head,Page * headpage) {
    Prog *tmp = head;
    while (tmp != NULL) {
        printf("%s : ", tmp->Nom);
        RechercherProg(headpage,tmp->Nom);
        tmp = tmp->suivant;
    }
    printf("\n");
}
//***************Affichage des Pages Libres**************

void AfficherPage(Page *head) {
    int i=1;
    Page *tmp = head;
    while (i<=25) {
        if(tmp->ProgMemoire==NULL){
            printf("%d ", tmp->num);
        }
        tmp = tmp->suivant;
        i=i+1;
    }
    printf("\n");
}

//******************Supprimer****************
void SupprimerProg(Prog *head,char *nom){
    Prog *tmp = head;
    Prog *tmp2 = NULL;
    
    if((strcmp(nom, head->Nom) == 0)){
        tmp = head;
        head = head->suivant;
        free(tmp);
    }
    else {
        while ((strcmp(tmp->Nom, nom)!=0)) {
        
            tmp2=tmp;
            tmp = tmp->suivant;
        }
        if((strcmp(tmp->Nom, nom)==0)) {
            tmp2->suivant = tmp->suivant;
            free(tmp);
        }
        
        //tmp = NULL;
    }
    printf("Ce programme a été bien supprimé.\n\n");
}
//*******************Vider***********************
int ViderPage(Page * head,char *nom){
    int i=1;
    Page * tmp = head;
    int taille = 0;
    while (i<=25) {
        if((tmp->ProgMemoire!=NULL) && (strcmp(tmp->ProgMemoire->Nom, nom)==0)){
            taille=tmp->ProgMemoire->Taille;
            tmp->ProgMemoire=NULL;
        }
        tmp = tmp->suivant;
        i=i+1;
    }
    return taille;
}

void AfficherPageOccuper(Page *head) {
    int i=1;
    Page *tmp = head;
    char sousChaine[250];
    printf("les pages occupées sont:\n");
    color_text(6);
    printf("\t _______\n");
    int j=0;
    while (i<=25) {
        if(tmp->ProgMemoire!=NULL){
            
            printf("\t|   %d\t|\n", tmp->num);
            if(strlen(tmp->ProgMemoire->Nom)<=6)
            {
                color_text(2);
                printf("\t|%s\t|\n",tmp->ProgMemoire->Nom);
                color_text(6);
                printf("\t|\t|\n");
                j++;
            }
            else
            {
                color_text(2);
                extract(0,6,tmp->ProgMemoire->Nom,sousChaine);
                printf("\t|%s|\n",sousChaine);
                color_text(6);
                printf("\t|\t|\n");
                j++;
            }
            printf("\t|¯¯¯¯¯¯¯|\n");
        }
        
        tmp = tmp->suivant;
        i=i+1;
    }
    if (j<10){
    printf("\t|%dpages\t|\n",j);
    }
    else{
        printf("\t|%dpages|\n",j);
    }
    printf("\t|_______|\n");
    printf("\n");
}
//****************** Recherche Par Page
void RechercherProg(Page*Debut,char nom[255]){
    int i=1;
    int x=0;
    Page * tmp=Debut;
    while (i<=25) {
        if((tmp->ProgMemoire!=NULL) && (strcmp(tmp->ProgMemoire->Nom, nom)==0)){
            printf("%d\t",tmp->num);
            x=tmp->ProgMemoire->Taille;
        }
        tmp = tmp->suivant;
        i=i+1;
    }
    if (x==0){
        printf("Programme n'existe pas!! \n");
    }
    else{
        printf("\nSa taille est %d",x);
    }
    printf("\n\n");
    
}
//******************* Extract nom
int extract(int from, int to, char chaine[255], char sousChaine[255])
{
  int i=0, j=0;
  //récupérer la longueur de la chaîne
  int length = strlen(chaine);

  if( from > length || from < 0 ){
    printf("L'index 'from' est invalide\n");
    return 1;
  }
  if( to > length ){
    printf("L'index 'to' est invalide\n");
    return 1;
  }
  for( i = from, j = 0; i <= to; i++, j++){
    sousChaine[j] = chaine[i];
  }
  return 0;
}
//****************** Afficher toutes la memoire
void AfficherMemoire(Page * Debut){
        int i,j;
        char sousNom [255];
        Page * tmp = Debut;
        color_text(6);
            printf("\t\t\t\t\t\t*****************************************\n");
            printf("\t\t\t\t\t\t             Memoire Centrale            \n");
            printf("\t\t\t\t\t\t*****************************************\n");
            for (i=1 ; i<=5; i++)
            {
                printf("\t\t\t\t\t\t _______________________________________\n");
                printf("\t\t\t\t\t\t|");
                for (j=1;j<=5;j++)
                {
                    
                    if (tmp->ProgMemoire!=NULL){
                        if (strlen(tmp->ProgMemoire->Nom)>6){
                        extract(0,6,tmp->ProgMemoire->Nom,sousNom);
                        color_text(1);
                        printf("%s",sousNom);
                        color_text(6);
                        printf("|");
                        }
                        else{
                            color_text(1);
                            printf("%s\t",tmp->ProgMemoire->Nom);
                            color_text(6);
                            printf("|");
                        }
                        
                    }
                    else{
                        printf("\t\t|");
                    }
                    tmp=tmp->suivant;
                }
                printf("\n");
                printf("\t\t\t\t\t\t ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
                
            }
            
            printf("\t\t\t\t\t\t----------------------------------------\n");
            printf("\t\t\t\t\t\t----------------------------------------\n");

}
//******************** Etat du memoire
void EtatMemoire(int taille){
    int i;
    color_text(3);
    printf(" _________________________________________________\n");
    printf("|");
    if (taille<2500){
        for (i=1;i<=TailleToPages(2500-taille);i++){
            color_text(1);
            printf("x");
            color_text(3);
            printf("|");
            
        }
    }
    if(taille!=0){
        for (i=1;i<=TailleToPages(taille);i++){
            printf("-|");
        }
    }
    printf("\n ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
    printf("\n\n");
}
//************** Trouver
int TrouverProg(Prog *head, char *nom) {
    int x=0;
    Prog *tmp = head;
    
    while (tmp !=NULL) {
        if(strcmp(tmp->Nom, nom)==0){
            x=1;
        } 
        
        
        tmp = tmp->suivant;
    }
    return x;
}

void color_text(int color)
{
    if(color == -1)
    {
        printf("\x1B[0;39m");
        return;
    }
    printf("\x1B[1;%dm", 30 + color);
}
//****************** Defragmenter memoire
Page * Defragmenter(Page * head,Prog * headProg)
{
    
    if (headProg!=NULL){
        Page * tmpPage=head;
        Prog * tmpProg = headProg;
        int j=0;
        int k = 0;
        while(tmpProg!=NULL)
        {
            int i=j+1;
            k=k+TailleToPages(tmpProg->Taille);
            while(i<=k){
                tmpPage->ProgMemoire=tmpProg;  
                tmpPage=tmpPage->suivant;
                i=i+1;
            }
            j=k;
            tmpProg=tmpProg->suivant;
        }
        
    }
    return head;
    
}
//*******************chercher_par_lettre*************
void chercher(Prog *head, Page*Debut, char nom[255]) {
    Prog *tmppg = head;
    int y,j,z;
    
    z=0;
    while (tmppg !=NULL) {
        y=0;
        for( j=0; j<strlen(nom); j++){
            if( tmppg->Nom[j] == nom[j] )
            { 
                y=1;
            }else {
                y=0;
                break;
            }
        }
        if(y==1){
            int i=1;
            int x=0;
            Page * tmp=Debut;
            z=1;
            printf("\n %s \n",tmppg->Nom);
            printf("\n occupe les pages : \n");
            while (i<=25) {
                if((tmp->ProgMemoire!=NULL) && (strcmp(tmp->ProgMemoire->Nom, tmppg->Nom)==0)) {
                    printf("%d\t",tmp->num);
                    x=tmp->ProgMemoire->Taille;
                }
                tmp = tmp->suivant;
                i=i+1;
            }
            if (x==0){
                printf("Programme n'existe pas!! \n");
            }
            else{
                printf("\nSa taille est %d \n",x);
            }
        }
        tmppg = tmppg->suivant;
    }
    if(z==0)
    {
        printf("Programme n'existe pas!! \n");
    }
}
//*********************************************

int main(void)
{
    //***Initialisation des Variables*********
    
    int choix,TailleProgramme;
    char NomProgramme[255];
    time_t t;
    Prog * PrecedentProg = malloc(sizeof(Prog));
    Prog * ProgAjouter = malloc(sizeof(Prog));
    Prog * DebutProg = malloc(sizeof(Prog));
    PrecedentProg = NULL;
    time(&t);

    //**************L'intialisation des pages ********
    int num;
    Page * Precedent, * DebutPage;
    Precedent = malloc(sizeof(Page));
    DebutPage = malloc(sizeof(Page));
    DebutPage = Initialisation(NULL,1);
    Precedent = DebutPage;
    for(num=2; num <=25; num++) {
        Precedent = Initialisation(Precedent,num);
    }




    //************************* Taille Libres de la mémoires
    //************************* A chaque fois on ajoute un programme x = x-taille/100
    //Lorsqu'on supprime un programme on ajoute x = taille/100 + x
    int TailleLibreMemoire = 2500;
    


    printf("\n\tDate actuelle : %s",ctime(&t));

    printf(" ----------------------------------------------------------- \n");
    printf("|                                                           |\n");
    printf("|                   Memoire centrale                        |\n");
    printf("|                                                           |\n");
    printf(" ----------------------------------------------------------- \n");
                                         

	/*Retourner au menu a chaque fois.*/
	while (choix != 10) {
		/*le Menu.*/
		color_text(-1);
		printf(" ----------------------------------------------------------- \n");
		printf("|                            MENU                           |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 1 |             Charger un nouveau programme              |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 2 |          Terminer l'execution d'un programme          |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 3 |             Afficher tous les programmes              |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 4 |                     Rechercher                        |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 5 |            Afficher tous les pages libres             |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 6 |                 Afficher la Memoire                   |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 7 |             Afficher les pages occupées               |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 8 |               Defragmenter la Memoire                 |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 9 |               Reinitialiser la Memoire                |\n");
		printf(" ----------------------------------------------------------- \n");
		printf("| 10|                        Quitter                        |\n");
		printf(" ----------------------------------------------------------- \n");
        
        
        //********************* La saisie du choix *****************************
        
		printf("\nEntrer votre choix : >>\t");
		scanf("%d", &choix);
		
		
		
		//*********************l'insertion du programme ************************
		
		if (choix == 1) {
		    printf("entrer le nom du prog :\t");
            scanf("%s",&NomProgramme);
            printf("entrer la taille du prog :\t");
            scanf("%d",&TailleProgramme);
            if(TailleProgramme>0)
            {
                if (TailleProgramme<=TailleLibreMemoire){
                    int x = TrouverProg(DebutProg, NomProgramme);
                        if (x==0){
                            Page * TempPage = malloc(sizeof(Page));
                            TempPage = DebutPage;
                            int NbrPages = TailleToPages(TailleProgramme);
                            TailleLibreMemoire= TailleLibreMemoire-NbrPages*100;
                            //****Creer le programme 
                            ProgAjouter = CreerProgramme(TailleProgramme,NomProgramme);
                            //*** Ajouter le programme au liste chainé des programmes
                            AjouterProg(PrecedentProg,ProgAjouter);
                            if(PrecedentProg==NULL){
                                DebutProg= ProgAjouter;
                            }
                            PrecedentProg = ProgAjouter;
                            //*****Affectation des pages 
                            while(NbrPages!=0)
                            {
                                if (TempPage->ProgMemoire==NULL){
                                    TempPage->ProgMemoire = PrecedentProg;
                                    NbrPages = NbrPages-1;
                                }
                                TempPage=TempPage->suivant;
                            }
                            printf("\nProgramme ajouté avec succès.\n");
                        }
                        else{
                            printf("Programme déja ajouté\n\n");
                        }
                }
                else{
                    printf("\n\nStockage disponible insuffisant.\n\n");
                    
                }
                EtatMemoire(TailleLibreMemoire);
            }
            else
            {
                printf("Taille <=0!!\n");
            }
		}
		
		
		//********************* La supression d'un programme *******************
		
		else if(choix ==2){
		    printf("Entrer le nom du prog à terminer:\t");
		    scanf("%s",NomProgramme);
		    int test = TrouverProg(DebutProg, NomProgramme);
            if (test==1)
            {
            		    Prog * tmp;
            		    int x=0;
            		    if (strcmp(DebutProg->Nom,NomProgramme)==0)
            		    {
            		        tmp =DebutProg->suivant;
            		        x=1;
            		    }
            		    TailleProgramme = ViderPage(DebutPage, NomProgramme);
            		    SupprimerProg(DebutProg, NomProgramme);
            		    TailleLibreMemoire=TailleLibreMemoire+TailleToPages(TailleProgramme)*100;
            		    EtatMemoire(TailleLibreMemoire);
            		    if(x==1)
            		    {
            		        DebutProg = tmp;
            		    }
            }
        	else{
            		     printf("Programme n'existe pas!!\n\n");
            	}
		    
		}
		
		
		//********************* L'affichage de tous les programmes *************
		
		else if(choix ==3){
		    if (TailleLibreMemoire!=2500){
		             AfficherProg(DebutProg,DebutPage);
		    }
		    else{
		        printf("Aucun programme n'est ajouté!!\n");
		    }
		}
		
		
		//********************* La recherche ***********************************
		
		else if(choix ==4){
		    printf("Entrez le Nom de programme a rechercher :\t");
		    scanf("%s",NomProgramme);
		    chercher(DebutProg, DebutPage, NomProgramme);
		}
		
		//********************* L'affichage des pages libres *******************
		
		else if(choix ==5){
		    AfficherPage(DebutPage);
		}
		
		//********************* L'affichage de la mémoire **********************
		
		else if(choix ==6){
		    AfficherMemoire(DebutPage);
		    printf("\t\t\t\t\t\tTaille disponible :%d pages.\n",TailleToPages(TailleLibreMemoire));
		}
		
		//********************* L'affichage des Pages occupées *****************
		
		else if(choix ==7){
		    AfficherPageOccuper(DebutPage);
		}
		
		//********************* La Defragmentation de la mémoire ***************
		
		else if(choix==8)
		{
		    if(TailleLibreMemoire!=2500){
    		    int i =1;
    		    Page * tmp = DebutPage;
    		    while (i<=25){
    		        tmp->ProgMemoire=NULL;
    		        tmp=tmp->suivant;
    		        i=i+1;
    		    }
    		    DebutPage = Defragmenter(DebutPage,DebutProg);
    		    printf("Memoire est bien defragmenté.\n");
		    }
		    else{
		        printf("Memoire est déja vide!!\n");
		    }
		}
		
		//********************* La reinitialisation de la mémoire **************
		
		else if(choix==9){
		    if(TailleLibreMemoire!=2500){
    		    Prog * tmp = DebutProg;
    		    while (tmp != NULL) 
    		    {
    		        strcpy(NomProgramme,tmp->Nom);
    		        int test = TrouverProg(DebutProg, NomProgramme);
                     if (test==1)
                    {
                    		    Prog * tmp;
                    		    int x=0;
                    		    if (strcmp(DebutProg->Nom,NomProgramme)==0)
                    		    {
                    		        tmp =DebutProg->suivant;
                    		        x=1;
                    		    }
                    		    TailleProgramme = ViderPage(DebutPage, NomProgramme);
                    		    printf("%s :",NomProgramme);
                    		    SupprimerProg(DebutProg, NomProgramme);
                    		    TailleLibreMemoire=TailleLibreMemoire+TailleToPages(TailleProgramme)*100;
                    		    if(x==1)
                    		    {
                    		        DebutProg = tmp;
                    		    }
                    }
                    tmp = tmp->suivant;
                }
    		    printf("Memoire est reinitialisé\n");
                PrecedentProg = NULL;
		    }
		    else
		    {
		       printf("Memoire est déja vide!!\n"); 
		    }
		}
		
		//********************* Quitter ****************************************
		else if(choix==10){
		    printf("A Bientôt");
		}
		
		else{
		    printf("Verifier votre choix.\n");
		}
	}
}
