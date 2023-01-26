#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tp3.h"


int isNumber(char s[])
{
    for (int i=0; s[i]!='\0';i++)
    {
        if (isdigit(s[i])==0)
            return 0;
    }
    return 1;
}


/* Cette fonction ne prend aucun param�tre et retourne
un T_Electeur (ou un electeur*, les deux d�signent la m�me chose).
Cette fonction permet de cr�er un electeur. */
T_Electeur creationelecteur(void)
{
    T_Electeur e; //Cr�ation d'un pointeur qui contiendra l'adresse d'un �lecteur

    e = malloc(sizeof(struct electeur)); //e est un pointeur qui contient une adresse consacr�e � contenir un electeur

    return e; // On retourne le pointeur qui contient l'adresse d'un �lecteur
}


//Cette fonction va afficher le nom de chaque electeur pr�sent dans notre liste d'electeur
void afficheliste(T_Electeur maliste)
{
    if (maliste==NULL) // Si maliste pointe vers NULL, alors notre liste est vide. Dans ce cas, il n'y a rien � afficher
    {
        printf("Rien a afficher\n");
    }
    else
    {
    printf("\n********************************************************\n\n");

    while(maliste != NULL) // Tant qu'on a pas atteint la queue de la liste cha�n�e
    {
        printf("%s - ", maliste->nom); // Affichage du nom
        printf("%lu - ", maliste->cin_num); // Affichage du num�ro de carte d'identit�
        printf("%d\n", maliste->choix); // Affichage du choix de l'�lecteur

        maliste = maliste->suivant; // On s'int�resse � l'�l�cteur suivant de notre liste cha�n�e
    }
    // � la sortie de la boucle maliste vaut NULL. Cela signifie que toute la liste a �t� parcourue

    printf("\n********************************************************\n\n");
    }
}

void ajoutelecteur(T_Electeur* maliste, char nom[NBMAX], long cin_num, int choix) // nom, cin_num et choix sont les attributs de l'�l�cteur que l'on va ajouter � la liste maliste
{

    if (presence(*maliste, cin_num)==1) // Si l'�tudiant que l'on souhaite ajouter poss�de un num�ro d'�lecteur qui appartient d�j� � un �lecteur pr�sent dans notre liste
    {
        printf("L'electeur %s-%li-%d est deja inscrit !", nom, cin_num, choix); // Alors on indique que cet �lecteur est d�j� inscrit et la fonction s'arr�te
        return;
    }


    T_Electeur element_a_inserer = creationelecteur(); // Appel de la fonction creationelecteur qui permet de cr�er un �lecteur (ses attributs ne sont pas initialis�s)

    if (element_a_inserer != NULL) // On v�rifie que l'allocation a r�ussi
    {
        strcpy(element_a_inserer->nom, nom); // Initialisation du nom de l'�lecteur cr��
        element_a_inserer->cin_num = cin_num; // Initialisation du num�ro de carte de l'�lecteur cr��
        element_a_inserer->choix = choix; // Initialisation du choix de l'�lecteur cr��
        element_a_inserer->suivant = NULL; // Le pointeur vers un �lecteur suivant de l'electeur cr�� est initialis� � NULL
    }
    else
    {
        printf("La creation d'un nouveau electeur a echoue !");
        return;
    }

    // Si le pointeur maliste pointe vers NULL (c'est � dire si la liste est vide) ou si le nom de l'�l�cteur � ajouter est plus petit (d'un point de vu lexicographique) que le nom du premier �lecteur de notre cha�ne
    if(*maliste == NULL || strcmp(nom, (*maliste)->nom) < 0)
    { // Insertion en t�te de liste
        element_a_inserer->suivant = *maliste; // L'attribut suivant de l'�lecteur cr�� va contenir l'adresse du premier �l�ment de la liste (qui ne va plus �tre le premier �l�ment)
        *maliste = element_a_inserer; // La t�te de notre liste pointe vers l'electeur cr��. Il devient le premier �l�ment de notre liste.
    }
    else
    {
        T_Electeur prev = NULL; // Initialisation de l'�lecteur prev qui, apr�s la boucle, pr�c�dera l'�lecteur � ins�rer
        T_Electeur cur = *maliste; // Initialisation de l'�lecteur cur qui, apr�s la boucle, suivera l'�lecteur � ins�rer
        // Tant qu'on est pas arriv� � la fin de la liste et qu'on a pas trouv� l'endroit o� ins�rer notre nouvel �lecteur
        while(cur != NULL && strcmp(nom, cur->nom) >= 0)
        { // On s'int�resse � l'�l�cteur suivant
            prev = cur;
            cur = cur->suivant;
        }

        // Quand on sort de la boucle, le nom du nouvel �lecteur est plus petit que le nom de l'�l�cteur vers lequel pointe cur. Ou alors, cur vaut NULL et dans ce cas le nom du nouvel �lecteur est le plus grand (et il va �tre ins�r� en fin de liste).
        //Il faut donc ins�rer notre nouvel �lecteur entre l'�lecteur point� par prev et celui point� par cur
        prev->suivant = element_a_inserer; // L'�lecteur suivant celui point� par prev devient notre nouvel �lecteur
        element_a_inserer->suivant = cur; // L'�lement suivant notre nouvel �lecteur devient l'�lecteur point� par cur

    }
}

// Cette fonction renvoie un entier repr�sentant le nombre d'�l�cteurs pr�sent dans la liste d'�lecteur pass�e en param�tre
int comptelecteur(T_Electeur maliste)
{
    int compteur = 0; // On initialise le nombre d'�l�cteurs dans notre liste � 0
    while(maliste != NULL) // Tant que nous ne sommes pas arriv�s � la fin de notre liste
    {
        compteur++; // On incr�mente de 1 le nombre d'electeur
        maliste = maliste->suivant; // On s'interesse � l'�lecteur suivant
    }
    return compteur; // On retourne le nombre d'�lecteur dans la liste
}


// On consid�re que 2 �lecteurs ne peuvent pas avoir le m�me num�ro de carte d'identit�
// On d�finit alors cette fonction qui retourne 1 si on trouve dans la liste pass�e en param�tre un �lecteur avec le num�ro de carte d'identit� pass� en param�tre, 0 si on ne le trouve pas
int presence(T_Electeur maliste, long numero_recherche)
{
    // Tout pendant qu'on est pas � la fin de la liste et qu'on a pas trouv� un �lecteur avec le num�ro de candidat recherch�
    while(maliste != NULL && maliste->cin_num != numero_recherche)
    {
        maliste = maliste->suivant; // On s'int�resse � l'�lecteur suivant
    }

    if (maliste != NULL) // Si maliste ne pointe pas vers NULL, alors on est sorti de la boucle car on a trouv� un �lecteur avec le num�ro de carte d'identit� recherch�
        return 1; // Dans ce cas on retourne 1
    else // Si maliste == NULL, alors on n'a pas trouv� d'�l�cteur ayant le m�me num�ro de carte d'identit� que celui recherch�
        return 0; // Dans ce cas on retourne 0
}

// Cette fonction retourne 1 si l'�lecteur ayant le num�ro de carte d'identit� recherch� se trouve dans la liste maliste, 0 sinon. De plus, si l'�lecteur se trouve dans la liste, alors les renseignements le concernant son affich�s � l'�cran
int trouvelecteur(T_Electeur maliste, long numero_recherche)
{
    // Tout pendant qu'on est pas � la fin de la liste et qu'on a pas trouv� un �lecteur avec le num�ro de candidat recherch�
    while(maliste != NULL && maliste->cin_num != numero_recherche)
    {
        maliste = maliste->suivant; // On s'int�resse � l'�lecteur suivant
    }

    if (maliste != NULL)
    { // Si maliste ne pointe pas vers NULL, alors on est sorti de la boucle car on a trouv� un �lecteur avec le num�ro de carte d'identit� recherch�
        printf("\n********************************************************\n\n");
        printf("%s - ", maliste->nom); // Affichage du nom
        printf("%lu - ", maliste->cin_num); // Affichage du num�ro de carte d'identit�
        printf("%d\n", maliste->choix); // Affichage du choix de l'�lecteur
        printf("\n********************************************************\n\n");
        return 1; // Dans ce cas on retourne 1
    }
    else
    { // Si maliste == NULL, alors on n'a pas trouv� d'�l�cteur ayant le m�me num�ro de carte d'identit� que celui recherch�
        printf("\n********************************************************\n\n");
        printf("Il n'y a aucun electeur dans votre liste qui porte le numero de carte d'identite %lu !\n", numero_recherche);
        printf("\n********************************************************\n\n");
        return 0; // Dans ce cas, on retourne 0
    }
}


void Supprimelecteur(T_Electeur* maliste, long numero_recherche)
{
    if (*maliste == NULL) // Si le pointeur vers notre liste a la valeur NULL
    {
        printf("La liste est vide ! Aucun element ne peut lui etre supprime !\n");
    }
    else
    {
        if((*maliste)->cin_num == numero_recherche) // Suppression du premier �lecteur
        {
            T_Electeur prev = *maliste; // prev permet de ne pas perdre l'�lecteur en t�te de liste
            *maliste = (*maliste)->suivant; // L'�lecteur en t�te de liste devient l'�lecteur suivant celui qui �tait en t�te de liste
            free(prev); // prev contient l'adresse d'un objet �lecteur. L'espace en m�moire consacr� � contenir cet objet va �tre lib�r�
            printf("L'electeur a bien ete supprime !\n");
        }

        else // Suppression au milieu ou en fin de liste
        {
            T_Electeur prev = NULL, cur = *maliste; // Initialisation de l'�lecteur prev qui, apr�s la boucle, pr�c�dera l'�lecteur � supprime
            // Initialisation de l'�lecteur cur qui, apr�s la boucle, sera l'�lecteur � supprimer

            while(cur != NULL && cur->cin_num != numero_recherche) // Tant qu'on est pas arriv� � la fin de la liste et qu'on a pas trouv� l'�lecteur � supprimer
            {
                prev = cur; // On s'int�resse � l'�lecteur suivant
                cur = cur->suivant;
            }


            if (cur != NULL) // Si cur ne vaut pas NULL, alors on est sorti de la boucle car la condition cur->cin_num != numero_recherche n'�tait plus respect�. L'�lecteur � supprimer a donc �t� trouv�
            {
                prev->suivant = cur->suivant; // L'�l�ment avant celui � supprimer doit pointer vers celui qui se trouve apr�s celui qu'on va supprimer

                free(cur); // cur contient l'adresse de l'�lecteur � supprimer. La place en m�moire consacr�e � contenir cet �lecteur va �tre lib�r�
                printf("L'electeur a bien ete supprime !\n");
            }

            else // Si on est sorti de la boucle car cur vaut NULL. Cela signifie qu'on a parcouru toute la liste et qu'aucun �lecteur ne poss�de le num�ro de carte recherch�.
            { // Ainsi dans notre liste, il n'y a pas d'�lecteur dont le num�ro est celui recherch�
                printf("\n********************************************************\n\n");
                printf("Il n'y a aucun electeur dans votre liste qui porte le numero de carte d'identite %lu !\n", numero_recherche);
                printf("\n********************************************************\n\n");
            }
        }
    }
}

void decoupeliste(T_Electeur maliste, T_Electeur* liste_gauche, T_Electeur* liste_droite, T_Electeur* liste_blanc)
{
    if (maliste == NULL)
    {
        printf("Cette liste ne peut etre decoupee car vide\n");
    }
    else
    {
     while(maliste != NULL) // Tant que nous ne sommes pas arriv�s � la fin de notre liste
        {
        if (maliste->choix == 1 || maliste->choix == 3) // Si le choix de l'�lecteur que nous sommes en train de traiter est 1 ou 3
                ajoutelecteur(liste_gauche, maliste->nom, maliste->cin_num, maliste->choix); // Alors on ajoute cet �lecteur � la liste des �lecteurs de gauche
        if (maliste->choix == 2 || maliste->choix == 4) // Si le choix de l'�lecteur que nous sommes en train de traiter est 2 ou 4
                ajoutelecteur(liste_droite, maliste->nom, maliste->cin_num, maliste->choix); // Alors on ajoute cet �lecteur � la liste des �lecteurs de droite
        if (maliste->choix==5) // Si le choix de l'�lecteur que nous sommes en train de traiter est 5
                ajoutelecteur(liste_blanc, maliste->nom, maliste->cin_num, maliste->choix); // Alors on ajoute cet �lecteur � la liste des �lecteurs votant blanc
        maliste = maliste->suivant; // On s'int�resse � l'�lecteur suivant
        }
     printf("La liste a bien ete separee en 3 listes.\n"); // On affiche un message une fois que toute notre liste a �t� s�par�e en sous-listes
    }
}

// Choix du tri : tri � bulle
void triliste(T_Electeur maliste)
{
    if (maliste!=NULL) // Si maliste est un pointeur dont la valeur n'est pas NULL, alors nous trions notre liste. Sinon, il n'y a pas de liste � trier et nous ne faisons aucune action
    {
     T_Electeur parcours = NULL;
     T_Electeur suiv = NULL;
     char nom[NBMAX];
     long cin_num = 0;
     int choix = 0;

     for(int i = comptelecteur(maliste)-1 ; i >= 1  ; i -= 1) // On r�alise n-1 fois cette boucle. i prend successivement les valeurs ,n-1, n-2... jusqu'� 1
     {
        parcours = maliste; // � chaque nouvel it�ration de i, l'�lecteur parcours prend pour valeur le premier �lecteur de notre liste
        suiv = maliste->suivant; // L'�lecteur suiv prend pour valeur le deuxi�me �lecteur de notre liste
        for(int j = 0 ; j < i ; j++) // On incr�mente j de 1 � chaque boucle et on s'arr�te quand on rencontre la limite pos�e par i qui se ressert � chaque it�ration sur i. j prend successivement les valeurs 1, 2... jusqu'� i
        {
            if(suiv->cin_num < parcours->cin_num)//si le cin_num de l'�lecteur suivant est inferieur � celui de l'�lecteur parcours, on les �change
            {
                strcpy(nom, parcours->nom); // On stock dans nom la valeur de l'�lecteur parcours
                cin_num = parcours->cin_num; // On stock dans cin_num la valeur cin_num de l'�lecteur parcours
                choix = parcours->choix; // On stock dans choix le choix de l'�lecteur parcours

                // On �change les attributs des deux �lecteurs parcours et suivant
                strcpy(parcours->nom, suiv->nom);
                parcours->cin_num = suiv->cin_num;
                parcours->choix = suiv->choix;

                strcpy(suiv->nom, nom);
                suiv->cin_num = cin_num;
                suiv->choix = choix;
            }
            parcours = parcours->suivant; // L'�lecteur parcours devient l'�lecteur suiv
            suiv = suiv->suivant; // L'�lecteur suiv devient l'�lecteur suivant l'�lecteur suiv
            // En proc�dant ainsi par �change successif de deux �lecteurs c�te � c�te, on fait remonter l'�l�cteur ayant le plus grand cin_num dans la liste
        }
     }
    }
}

T_Electeur fusionlistes(T_Electeur liste_gauche, T_Electeur liste_droite)
{
    T_Electeur nouvelle_liste = NULL; // Initialisation de la liste qui contiendra les �lecteurs de gauche et les �lecteurs de droite

    while(liste_droite != NULL) // Tant que nous ne sommes pas � la fin de la liste des �lecteurs de droite
    {
        ajoutelecteur(&nouvelle_liste, liste_droite->nom, liste_droite->cin_num, liste_droite->choix); // On ajoute l'�lecteur que nous sommes en train de traiter � la liste des �lecteurs de gauche et de droite
        liste_droite = liste_droite->suivant; // On s'int�resse � l'�lecteur suivant dans la liste liste_droite
    }

    while(liste_gauche != NULL) // Tant que nous ne sommes pas � la fin de la liste des �lecteurs de gauche
    {
        ajoutelecteur(&nouvelle_liste, liste_gauche->nom, liste_gauche->cin_num, liste_gauche->choix); // On ajoute l'�lecteur que nous sommes en train de traiter � la liste des �lecteurs de gauche et de droite
        liste_gauche = liste_gauche->suivant; // On s'int�resse � l'�lecteur suivant dans la liste liste_gauche
    }

    triliste(nouvelle_liste); // Une fois que nous avons construit la liste des �lecteurs de droite et de gauche, nous trions cette liste selon les num�ros de carte d'identit� gr�ce � la fonction triliste d�finie pr�cedemment
    return nouvelle_liste; // On retourne la liste des �lecteurs de gauche et de droite
}

int compteGD(T_Electeur liste_fusionee)
{
    if (liste_fusionee == NULL)
    {
        printf("Impossible d'afficher les pourcentages ! La liste de fusion des electeurs de droite et de gauche n'a pas ete creee !\n");
    }
    else
    {
        int compteur = 0; // On initialise la variable qui contiendra le nombre d'�lecteur de gauche � 0

        while(liste_fusionee != NULL) // Tant que nous ne sommes pas arriv� � la fin de notre liste
        {
            if(liste_fusionee->choix == 1 || liste_fusionee->choix == 3) // Si l'�lecteur que nous sommes en train de traiter � voter � gauche
            {
                compteur++; // Alors la variable nous indiquant le nombre d'�lecteurs de gauche est incr�ment�e de 1
            }
            liste_fusionee = liste_fusionee->suivant; // On s'int�resse � l'�lecteur suivant
        }

    return compteur; // � l'issue de la boucle, nous avons parcouru toute la liste. On retourne donc compteur qui contient le nombre d'�lecteur de gauche de notre liste
    }
}

T_Electeur liberer(T_Electeur maliste)
{
    T_Electeur tampon = maliste;
    T_Electeur tamponnext;
    while(tampon != NULL) // Tant que nous ne sommes pas arriv� � la fin de notre liste
    {
        tamponnext = tampon->suivant; // On stock l'�lecteur suivant celui que l'on va supprimer
        free(tampon); // On supprime l'�lecteur � supprimer
        tampon = tamponnext; // L'�lecteur � supprimer devient l'�lecteur suivant que nous avions stocker dans la variable tamponnext
    }
    return NULL; // On retourne NULL pour qu'on puisse fixer � NULL la valeur des pointeurs dont on supprime la liste. On utilise alors la syntaxe liste_a_liberer = liberer(liste_a_liberer);
}

