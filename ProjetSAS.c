#include <stdio.h>

#include <string.h>
#include <ctype.h>

#define MAX_CARACTERE 2000
#define MAX_MOTS 200
#define MAX_LONGUEUR 200
#define MAX_POS 100

struct Word{
    char valeur[MAX_LONGUEUR];
    int occurences;
    int longueur;
    int position[MAX_POS];
    int nbposition;
};

struct Word Dc[MAX_MOTS];
int nbMots = 0;

void nettoyerMot(char *mot){
    int i,j=0;
    char temp[MAX_LONGUEUR];

    for(i=0 ; mot[i] != '\0'; i++){
        if(isalpha(mot[i])){
            temp[j++] = tolower(mot[i]);
        }
    }
    temp[j] = '\0';
    strcpy(mot,temp);
}

void AddWord(char *mot , int position){
    int i;
    for(i = 0 ; i < nbMots ; i++){
        if(strcmp(Dc[i].valeur ,mot)==0){
            Dc[i].occurences++;
            Dc[i].position[Dc[i].nbposition++]= position;
            return;
        }
    }
    strcpy(Dc[nbMots].valeur ,mot);
    Dc[nbMots].occurences = 1;
    Dc[nbMots].longueur = strlen(mot);
    Dc[nbMots].position[0] = position;
    Dc[nbMots].nbposition = 1;
    nbMots++;
}

void analyserText(char *texte){
    char *token;
    int position=1;
    token = strtok(texte , " \t\n");
    while (token!=NULL){
        nettoyerMot(token);
        if(strlen(token) > 0){
            AddWord(token,position);
            position++;
        }
        token=strtok(NULL," \t\n");
    }
}

void saisiTxt(){
    int i, j;
    char str[MAX_CARACTERE];
    char original[MAX_CARACTERE];

    printf("Saisir un text : ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    strcpy(original, str);  


    char t[MAX_CARACTERE];
    strcpy(t, str);

    printf("\n--- Texte clair ---\n");
    for(i = 0; t[i] != '\0'; i++){
        if(isalpha(t[i])) 
            printf("%c", tolower(t[i]));
        else if(t[i] == ' ' || t[i] == '\t' || t[i] == '\n')
            printf(" ");
    }
    printf("\n\n");

    analyserText(str);
}





void afficherMots(){
    int i,j;
    if(nbMots == 0){
        printf("\nDictionnaire vide. Analysez d'abord un texte (option 1).\n");
        return;
    }
    printf("\n--- AFFICHER TOUS LES MOTS ---\n");
    for(i = 0; i < nbMots; i++){
        printf("%-15s | Occurrences: %3d | Longueur: %2d | Positions: ",
               Dc[i].valeur,
               Dc[i].occurences,
               Dc[i].longueur);
        for(j = 0; j < Dc[i].nbposition; j++)
            printf("%d ", Dc[i].position[j]);
        printf("\n");
    }
}


void RechercherMot() {
    char motRecherche[50];
    int i, j;
    
    printf("\nEntrez le mot à rechercher : ");
    fgets(motRecherche, sizeof(motRecherche), stdin);
    motRecherche[strcspn(motRecherche, "\n")] = '\0';


    for(i = 0; motRecherche[i]; i++)
        motRecherche[i] = tolower(motRecherche[i]);

    int mode;
    printf("Mode de recherche (1=Exactement, 2=Partiellement) : ");
    scanf("%d", &mode);
    getchar();

    printf("\nRésultats de recherche :\n");
    int trouve = 0;

    for(i = 0; i < nbMots; i++) {
        if((mode == 1 && strcmp(Dc[i].valeur, motRecherche) == 0) ||
           (mode == 2 && strstr(Dc[i].valeur, motRecherche) != NULL)) {
            trouve = 1;
            printf("Mot : %-10s | Occurrences : %d | Positions : ",
                   Dc[i].valeur, Dc[i].occurences);
            for(j = 0; j < Dc[i].nbposition; j++)
                printf("%d ", Dc[i].position[j]);
            printf("\n"); 
        }
    }

    if(!trouve) 
        printf("Aucun mot trouvé.\n");
}



void TriAlph() {
    int i, j;
    struct Word t;
    for (i = 0; i < nbMots - 1; i++) {
        for (j = i + 1; j < nbMots; j++) {
            if (strcmp(Dc[i].valeur, Dc[j].valeur) > 0) {
                t= Dc[i];
                Dc[i] = Dc[j];
                Dc[j] = t;
            }
        }
    }
    printf("\nTri par ordre alphabétique terminé !\n");
}

void TriFrec() {
    int i, j;
    struct Word t;
    for (i = 0; i < nbMots - 1; i++) {
        for (j = i + 1; j < nbMots; j++) {
            if (Dc[i].occurences < Dc[j].occurences) {
                t = Dc[i];
                Dc[i] = Dc[j];
                Dc[j] = t;
            }
        }
    }
    printf("\nTri par fréquence terminé !\n");
}

void TriLongueur() {
    int i, j;
    struct Word t;
    for (i = 0; i < nbMots - 1; i++) {
        for (j = i + 1; j < nbMots; j++) {
            if (Dc[i].longueur > Dc[j].longueur) {
                t = Dc[i];
                Dc[i] = Dc[j];
                Dc[j] = t;
            }
        }
    }
    printf("\nTri par longueur terminé !\n");
}



void displayStatistics() {
    if (nbMots == 0) {
        printf("\nDictionnaire vide. Analysez d'abord un texte.\n");
        return;
    }

    int i;
    int t_o = 0;
    int s_L = 0;
    int m_p_lg = 0;
    int m_p_p = 0;
    int m_p_f = 0;

    for (i = 0; i < nbMots; i++) {
        t_o += Dc[i].occurences;
        s_L += Dc[i].longueur;

        if (Dc[i].longueur > Dc[m_p_lg
		].longueur)
            m_p_lg = i;

        if (Dc[i].longueur < Dc[m_p_p].longueur)
            m_p_p = i;

        if (Dc[i].occurences > Dc[m_p_f].occurences)
            m_p_f = i;
    }

double l_M = (double)s_L / t_o;
    double d_L = (double)nbMots / t_o * 100;

    printf("\n===== STATISTIQUES GLOBALES =====\n");
    printf("Nombre total de mots          : %d\n", t_o);
    printf("Nombre de mots uniques        : %d\n", nbMots);
    printf("Diversite lexicale            : %.2f%%\n", d_L);
    printf("Longueur moyenne des mots     : %.2f lettres\n", l_M);
    printf("Mot le plus frequent          : %s (%d fois)\n",
           Dc[m_p_f].valeur, Dc[m_p_f].occurences);
    printf("Mot le plus court             : %s (%d lettres)\n",
           Dc[m_p_p].valeur, Dc[m_p_p].longueur);
    printf("Mot le plus long              : %s (%d lettres)\n",
           Dc[m_p_lg].valeur, Dc[m_p_lg].longueur);
}

int Palindrome(char pil[50]) {
    int len = strlen(pil);
    int i;
    for (i = 0; i < len / 2; i++) {
        if (pil[i] != pil[len - 1 - i]) {
            return 0; 
        }
    }
    return 1;
}
void PalindromeMenu() {
    if (nbMots == 0) {
        printf("\nDictionnaire vide. Analysez d'abord un texte.\n");
        return;
    }

    printf("\n--- Palindromes ---\n");
    int found = 0;
    for (int i = 0; i < nbMots; i++) {
        if (Palindrome(Dc[i].valeur)) {
            printf("%s\n", Dc[i].valeur);
            found = 1;
        }
    }

    if (!found) {
        printf("Aucun palindrome trouvé.\n");
    }
}

void T(char tab[]){
	int i,j;
	int len = strlen(tab);
	char t;
for (i = 0; i < len - 1; i++) {
    for (j = i + 1; j < len; j++) {
        if (tab[i] > tab[j]) {
            t = tab[i];
            tab[i] = tab[j];
            tab[j] = t;
        }
    }
}

	
}
void Anagramme(struct Word wd[], int nbMots){
    if (nbMots == 0) {
        printf("\nDictionnaire vide. Analysez d'abord un texte.\n");
        return;
    }
    int i, j;
    char cd[50], xd[50];
    int found = 0;
    printf("\n--- Liste des anagrammes ---\n");
    for (i = 0; i < nbMots; i++) {
        for (j = i + 1; j < nbMots; j++) {
            if (strlen(wd[i].valeur) == strlen(wd[j].valeur)) {  
                strcpy(cd, wd[i].valeur);
                strcpy(xd, wd[j].valeur);
                T(cd);
                T(xd);
                if (strcmp(cd, xd) == 0) {
                    printf("%s <-> %s\n", wd[i].valeur, wd[j].valeur);
                    found = 1;
                }
            }
        }
    }

    if (!found) {
        printf("Aucun anagramme trouve.\n");
    }
}


	void Nuage(){
	    if (nbMots == 0) {
	        printf("\nDictionnaire vide. Analysez d'abord un texte.\n");
	        return;
	    }
	        printf("\n--- Nuage de mots ---\n");
	
	    for (int i = 0; i < nbMots; i++) {
	        printf("%s ", Dc[i].valeur);
	        for (int j = 0; j < Dc[i].occurences; j++)
	            printf("*");
	        printf("\n");
	    }
	}

int main()
{
    char choix , sousChoix;
    do{
        printf("\n=== MENU PRINCIPALE ===\n");
        printf("\n1.Saisir texte & analyser");
        printf("\n2.Afficher mots");
        printf("\n3.Chercher mot");
        printf("\n4.Trier mots (alphabet / frequence / longueur)");
        printf("\n5.Stats globales (total mots, uniques, longueur moyenne )");
        printf("\n6.Analyses (palindromes, anagrammes, nuage de mots)");
        printf("\n0.Quitter");
        printf("\nVotre choix : ");
        scanf(" %c",&choix);
        getchar();

        switch(choix){
            case '1':saisiTxt();break;
            case '2':afficherMots();break;
            case '3':RechercherMot();break;

            case '4':
                do{
                    printf("\n1. Alphabet");
                    printf("\n2. Frequence");
                    printf("\n3. Longueur");
                    printf("\n0. Retour au MenuP");
                    printf("\nVotre choix : ");
                    scanf(" %c",&sousChoix);
                    getchar();

                    switch(sousChoix){
                        case '1': TriAlph();break;
                        case '2': TriFrec();break;
                        case '3': TriLongueur();break;
                        case '0':break;
                        default :printf("\nChoix invalide !!");
                    }
                }while(sousChoix != '0');
                break;
            case '5':displayStatistics();break;
            case '6':
                do{
                    printf("\n1. Palindromes");
                    printf("\n2. Anagrammes");
                    printf("\n3. Nuage de mots");
                    printf("\n0. Retour au MenuP");
                    printf("\nVotre choix : ");
                    scanf(" %c",&sousChoix);
                    getchar();

                    switch(sousChoix){
                        case '1': PalindromeMenu();break;
                        case '2': Anagramme(Dc, nbMots);break;
                        case '3': Nuage()	;break;
                        case '0':break;
                        default :printf("\nChoix invalide !!");
                    }
                }while(sousChoix != '0');
                break;
            case '0':printf("\nOk au revoir !\n");break;
            default :printf("\nChoix invalide !!");
        }
    }while(choix != '0');

    return 0;
} 

