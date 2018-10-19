#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define Vmax 300 //*100 pour rendre le poids en entier
#define Pmax 600
#define n 100

int F_recursif(int nbObjets,int volume, int poids);
int F_dynamique();
int maximum(int elem1,int elem2);
void genererTableauObjets();
int rechercheSuiteObjets();
void genererTableauObjetsEssai();
int maxValeursObjets();
void lebererTableau();
void allouerTableau(int i,int j,int k);
void genererTableauAlea(int nbObjets);


int tabs[n][Vmax+1][Pmax+1];
int ***tab;//n*(vmax+1)*(Pmax+1)

typedef struct objet objet;
struct objet
{
    int poids;
    int volume;
    int valeur;
};
objet* tabObjets;//[n];
int maxValeur;
int main()
{
    clock_t debut,fin;
    float temps;
    //genererTableauObjets();
    genererTableauAlea(n);
    //genererTableauObjets();

    //printf("max = %d",(-1)*maxValeur);
    printf("************** Algorithme récursif *****************\n");
    debut = clock();
    printf("\t\tGain == %d\n\n",F_recursif(n-1,Vmax,Pmax));
    fin = clock();
    temps = (float)(fin - debut)/CLOCKS_PER_SEC;
    printf("temps exe recursif = %f\n\n\n",temps);
    printf("************** Algorithme programmation dynamique *****************\n");
    debut = clock();
    allouerTableau(n,Vmax+1,Pmax+1);
    printf("\t\tGain == %d\n\n\n",F_dynamique());
    fin = clock();
    temps = (float)(fin - debut)/CLOCKS_PER_SEC;
    printf("temps exe programmation dynamique = %f\n\n\n",temps);
    printf("Voulez vous visualiser la liste des objets choisis ? o/n :");
    char c;
    c = getchar();
    if(c == 'o')
    {
        printf("La liste des objets choisis sont les objets dont les numeros les suivants : ");
        rechercheSuiteObjets();
        printf("\n\n\n");
    }
    lebererTableau();
    return 0;
}

//Générer un tableau jeu d'essai présenté durant le TP
void genererTableauObjetsEssai()
{
    objet o;
    //objet 1
    o.poids = 3;
    o.valeur = 2;
    o.volume = 3;
    tabObjets[0] = o;
    //objet 2
    o.poids = 2;
    o.valeur = 1;
    o.volume = 2;
    tabObjets[1] = o;
    //objet 3
    o.poids = 2;
    o.valeur = 3;
    o.volume = 2;
    tabObjets[2] = o;
}

//Générer le tableau du TP
void genererTableauObjets()
{
    objet o;
    //objet 1
    o.poids = 20;
    o.valeur = 6;
    o.volume = 10;
    tabObjets[0] = o;
    //objet 2
    o.poids = 30;
    o.valeur = 8;
    o.volume = 15;
    tabObjets[1] = o;
    //objet 3
    o.poids = 50;
    o.valeur = 14;
    o.volume = 25;
    tabObjets[2] = o;
    //objet 4
    o.poids = 20;
    o.valeur = 6;
    o.volume = 10;
    tabObjets[3] = o;
    //objet 5
    o.poids = 40;
    o.valeur = 13;
    o.volume = 20;
    tabObjets[4] = o;
    //objet 6
    o.poids = 60;
    o.valeur = 17;
    o.volume = 30;
    tabObjets[5] = o;
    //objet 7
    o.poids = 30;
    o.valeur = 10;
    o.volume = 15;
    tabObjets[6] = o;
    //objet 8
    o.poids = 10;
    o.valeur = 4;
    o.volume = 5;
    tabObjets[7] = o;
    //objet 9
    o.poids = 14;
    o.valeur = 5;
    o.volume = 7;
    tabObjets[8] = o;
    //objet 10
    o.poids = 36;
    o.valeur = 11;
    o.volume = 18;
    tabObjets[9] = o;
    //objet 11
    o.poids = 72;
    o.valeur = 26;
    o.volume = 36;
    tabObjets[10] = o;
    //objet 12
    o.poids = 86;
    o.valeur = 35;
    o.volume = 43;
    tabObjets[11] = o;
    //objet 13
    o.poids = 5;
    o.valeur = 2;
    o.volume = 3;
    tabObjets[12] = o;
    //objet 14
    o.poids = 3;
    o.valeur = 1;
    o.volume = 2;
    tabObjets[13] = o;
    //objet 15
    o.poids = 7;
    o.valeur = 2;
    o.volume = 4;
    tabObjets[14] = o;
    //objet 16
    o.poids = 23;
    o.valeur = 7;
    o.volume = 12;
    tabObjets[15] = o;
    //objet 17
    o.poids = 49;
    o.valeur = 15;
    o.volume = 25;
    tabObjets[16] = o;
    //objet 18
    o.poids = 57;
    o.valeur = 17;
    o.volume = 29;
    tabObjets[17] = o;
    //objet 19
    o.poids = 69;
    o.valeur = 30;
    o.volume = 35;
    tabObjets[18] = o;
    //objet 20
    o.poids = 12;
    o.valeur = 3;
    o.volume = 6;
    tabObjets[19] = o;

}

//solution descendente : Algorithme récusrsif
int F_recursif(int nbObjets,int volume, int poids)
{
    if(nbObjets<0) return 0;
    if((volume<tabObjets[nbObjets].volume)||(poids<tabObjets[nbObjets].poids)) return F_recursif(nbObjets-1,volume,poids);
    else return maximum(F_recursif(nbObjets-1,volume,poids),(F_recursif(nbObjets-1,volume-tabObjets[nbObjets].volume,poids-tabObjets[nbObjets].poids)+tabObjets[nbObjets].valeur));
}

//Solution dynamique
int F_dynamique()
{
    int i = 0;
    int j;//représente le volume
    int k;//représente le poids
    int val;
    for(j=0;j<=Vmax;j++)
    {
        for(k=0;k<=Pmax;k++)
        {
            if((j<tabObjets[i].volume)||(k<tabObjets[i].poids))
            {
                tab[i][j][k] = 0;
            }
            else
            {
                tab[i][j][k] = tabObjets[i].valeur;
            }
        }
    }
    for(i=1;i<n;i++)
    {
        for(j=0;j<=Vmax;j++)
        {
            for(k=0;k<=Pmax;k++)
            {
                if((j<tabObjets[i].volume)||(k<tabObjets[i].poids))
                {
                    tab[i][j][k] = tab[i-1][j][k];
                }
                else
                {
                    val = tab[i-1][j-tabObjets[i].volume][k-tabObjets[i].poids]+tabObjets[i].valeur;
                    tab[i][j][k] = maximum(tab[i-1][j][k],val);

                }
            }
        }
    }
    return tab[n-1][Vmax][Pmax];
}

//retourne le max
int maximum(int elem1,int elem2)
{
    if(elem1>elem2) return elem1;
    else return elem2;
}

//Afficher la suite de objets choisis
int rechercheSuiteObjets()
{

    int i = n-1;
    int j = Vmax;
    int k = Pmax;
    //printf("gain %d\n",tab[i][j][k]);
    //rechercher le volume minimale qui correspond au gain maximal
    while(tab[i][j][k]==tab[i][j-1][k])
    {
        j--;

    }
    //rechercher le poids minimale qui correspond au gain maximal
    while(tab[i][j][k] == tab[i][j][k-1])
    {
        k--;
    }
    while((j>0)&&(k>0))
    {
        while((i>0)&&(tab[i-1][j][k] == tab[i][j][k]))
        {
            i--;
        }
        j -= tabObjets[i].volume;
        k -= tabObjets[i].poids;
        if((j>=0)&&(k>=0))
        {
            printf("%d, ",i+1);
        }
        i--;
    }
}


//Retourne le valeur maximale des valeurs des objets contenus dans le taleau
int maxValeursObjets()
{
    int max;
    int i;
    for(i=1;i<n;i++)
    {
        max=maximum(tabObjets[i-1].valeur,tabObjets[i].valeur);
    }
    return max;
}
void lebererTableau()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<Vmax;j++)
        {
            free(tab[i][j]);
        }
        free(tab[i]);
    }
    free(tab);
}

//Allocation d'un tableau 3D (i*j*k)
void allouerTableau(int i,int j,int k)
{
    tab = (int***)malloc(sizeof(int**)*n);
    if(tab == NULL)
    {
        printf("Allocation Impossible");
        exit(1);
    }
    for(i=0;i<n;i++)
    {
        tab[i]=(int**)malloc(sizeof(int*)*(Vmax+1));
        for(j=0;j<=Vmax;j++)
        {
            tab[i][j]=(int*)malloc(sizeof(int)*(Pmax+1));
        }
    }
}

//generer un tableau rempli alétoirement
void genererTableauAlea(int nbObjets)
{
    static int cpt = 0;
    int poidsMin,poidsMax,volumeMin,volumeMax,i,valeurMin,valeurMax;
    tabObjets = (objet*)malloc(sizeof(objet)*n);
    if(tabObjets==NULL)
    {
        printf("Allocation Impossible");
        exit(2);
    }
    printf("Donnez poidsMin (Un entier): ");
    scanf("%d",&poidsMin);
    printf("Donnez poidsMax (Un entier): ");
    scanf("%d",&poidsMax);
    printf("Donnez volumeMin (Un entier): ");
    scanf("%d",&volumeMin);
    printf("Donnez volumeMax (Un entier): ");
    scanf("%d",&volumeMax);
    printf("Donnez valeurMin (Un entier): ");
    scanf("%d",&valeurMin);
     printf("Donnez valeurMax (Un entier): ");
    scanf("%d",&valeurMax);

    srand((unsigned int)time((time_t *)NULL)+cpt);
    //génération de n poids aléatoitre enre poidsMin et poidsMax
    for(i=0;i<nbObjets;i++)
    {
        tabObjets[i].poids =(int) (((double)(poidsMax-poidsMin)*(double)rand())/(double)(RAND_MAX))+poidsMin;
    }
    srand((unsigned int)time((time_t *)NULL)+cpt+1);
    //génération de n volume aléatoitre enre volumeMin et volumeMax
    for(i=0;i<nbObjets;i++)
    {
        tabObjets[i].volume = (int) (((double)(volumeMax-volumeMin)*(double)rand())/(double)(RAND_MAX))+volumeMin;
    }
    srand((unsigned int)time((time_t *)NULL)+cpt+2);
    //génération de n volume aléatoitre enre volumeMin et volumeMax
    for(i=0;i<nbObjets;i++)
    {
        tabObjets[i].valeur =(int) (((double)(valeurMax-valeurMin)*(double)rand())/(double)(RAND_MAX))+valeurMin;
    }
    cpt +=3;

}
