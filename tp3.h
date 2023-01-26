#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#define NBMAX 100

//Définition des structures

struct electeur
{
    char nom[NBMAX]; //Chaîne de caractère de NBMAX caractère maximum
    long cin_num;
    int choix;
    struct electeur* suivant; //suivant va contenir l'adresse d'un electeur : c'est un pointeur sur un electeur
};
typedef struct electeur* T_Electeur; //T_Electeur est un pointeur sur un electeur


// Prototypes des fonctions demandées

T_Electeur creationelecteur(void);
void afficheliste(T_Electeur);
void ajoutelecteur(T_Electeur* maliste, char nom[NBMAX], long cin_num, int choix);
int comptelecteur(T_Electeur maliste);
int trouvelecteur(T_Electeur maliste, long numero_recherche);
void Supprimelecteur(T_Electeur* maliste, long numero_recherche);
void decoupeliste(T_Electeur maliste, T_Electeur* liste_gauche, T_Electeur* liste_droite, T_Electeur* liste_blanc);
void triliste(T_Electeur maliste);
T_Electeur fusionlistes(T_Electeur liste_gauche, T_Electeur liste_droite);
int compteGD(T_Electeur liste_fusionee);
T_Electeur libereliste(T_Electeur maliste);


// Protoypes des fonctions rajoutées
int presence(T_Electeur maliste, long numero_recherche);
int isNumber(char s[]);


#endif // FONCTIONS_H_INCLUDED
