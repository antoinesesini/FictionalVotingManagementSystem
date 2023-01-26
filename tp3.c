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


/* Cette fonction ne prend aucun paramètre et retourne
un T_Electeur (ou un electeur*, les deux désignent la même chose).
Cette fonction permet de créer un electeur. */
T_Electeur creationelecteur(void)
{
    T_Electeur e; //Création d'un pointeur qui contiendra l'adresse d'un électeur

    e = malloc(sizeof(struct electeur)); //e est un pointeur qui contient une adresse consacrée à contenir un electeur

    return e; // On retourne le pointeur qui contient l'adresse d'un électeur
}


//Cette fonction va afficher le nom de chaque electeur présent dans notre liste d'electeur
void afficheliste(T_Electeur maliste)
{
    if (maliste==NULL) // Si maliste pointe vers NULL, alors notre liste est vide. Dans ce cas, il n'y a rien à afficher
    {
        printf("Rien a afficher\n");
    }
    else
    {
    printf("\n********************************************************\n\n");

    while(maliste != NULL) // Tant qu'on a pas atteint la queue de la liste chaînée
    {
        printf("%s - ", maliste->nom); // Affichage du nom
        printf("%lu - ", maliste->cin_num); // Affichage du numéro de carte d'identité
        printf("%d\n", maliste->choix); // Affichage du choix de l'électeur

        maliste = maliste->suivant; // On s'intéresse à l'élécteur suivant de notre liste chaînée
    }
    // À la sortie de la boucle maliste vaut NULL. Cela signifie que toute la liste a été parcourue

    printf("\n********************************************************\n\n");
    }
}

void ajoutelecteur(T_Electeur* maliste, char nom[NBMAX], long cin_num, int choix) // nom, cin_num et choix sont les attributs de l'élécteur que l'on va ajouter à la liste maliste
{

    if (presence(*maliste, cin_num)==1) // Si l'étudiant que l'on souhaite ajouter possède un numéro d'électeur qui appartient déjà à un électeur présent dans notre liste
    {
        printf("L'electeur %s-%li-%d est deja inscrit !", nom, cin_num, choix); // Alors on indique que cet électeur est déjà inscrit et la fonction s'arrête
        return;
    }


    T_Electeur element_a_inserer = creationelecteur(); // Appel de la fonction creationelecteur qui permet de créer un électeur (ses attributs ne sont pas initialisés)

    if (element_a_inserer != NULL) // On vérifie que l'allocation a réussi
    {
        strcpy(element_a_inserer->nom, nom); // Initialisation du nom de l'électeur créé
        element_a_inserer->cin_num = cin_num; // Initialisation du numéro de carte de l'électeur créé
        element_a_inserer->choix = choix; // Initialisation du choix de l'électeur créé
        element_a_inserer->suivant = NULL; // Le pointeur vers un électeur suivant de l'electeur créé est initialisé à NULL
    }
    else
    {
        printf("La creation d'un nouveau electeur a echoue !");
        return;
    }

    // Si le pointeur maliste pointe vers NULL (c'est à dire si la liste est vide) ou si le nom de l'élécteur à ajouter est plus petit (d'un point de vu lexicographique) que le nom du premier électeur de notre chaîne
    if(*maliste == NULL || strcmp(nom, (*maliste)->nom) < 0)
    { // Insertion en tête de liste
        element_a_inserer->suivant = *maliste; // L'attribut suivant de l'électeur créé va contenir l'adresse du premier élément de la liste (qui ne va plus être le premier élément)
        *maliste = element_a_inserer; // La tête de notre liste pointe vers l'electeur créé. Il devient le premier élément de notre liste.
    }
    else
    {
        T_Electeur prev = NULL; // Initialisation de l'électeur prev qui, après la boucle, précèdera l'électeur à insérer
        T_Electeur cur = *maliste; // Initialisation de l'électeur cur qui, après la boucle, suivera l'électeur à insérer
        // Tant qu'on est pas arrivé à la fin de la liste et qu'on a pas trouvé l'endroit où insérer notre nouvel électeur
        while(cur != NULL && strcmp(nom, cur->nom) >= 0)
        { // On s'intéresse à l'élécteur suivant
            prev = cur;
            cur = cur->suivant;
        }

        // Quand on sort de la boucle, le nom du nouvel électeur est plus petit que le nom de l'élécteur vers lequel pointe cur. Ou alors, cur vaut NULL et dans ce cas le nom du nouvel électeur est le plus grand (et il va être inséré en fin de liste).
        //Il faut donc insérer notre nouvel électeur entre l'électeur pointé par prev et celui pointé par cur
        prev->suivant = element_a_inserer; // L'électeur suivant celui pointé par prev devient notre nouvel électeur
        element_a_inserer->suivant = cur; // L'élement suivant notre nouvel électeur devient l'électeur pointé par cur

    }
}

// Cette fonction renvoie un entier représentant le nombre d'élécteurs présent dans la liste d'électeur passée en paramètre
int comptelecteur(T_Electeur maliste)
{
    int compteur = 0; // On initialise le nombre d'élécteurs dans notre liste à 0
    while(maliste != NULL) // Tant que nous ne sommes pas arrivés à la fin de notre liste
    {
        compteur++; // On incrémente de 1 le nombre d'electeur
        maliste = maliste->suivant; // On s'interesse à l'électeur suivant
    }
    return compteur; // On retourne le nombre d'électeur dans la liste
}


// On considère que 2 électeurs ne peuvent pas avoir le même numéro de carte d'identité
// On définit alors cette fonction qui retourne 1 si on trouve dans la liste passée en paramètre un électeur avec le numéro de carte d'identité passé en paramètre, 0 si on ne le trouve pas
int presence(T_Electeur maliste, long numero_recherche)
{
    // Tout pendant qu'on est pas à la fin de la liste et qu'on a pas trouvé un électeur avec le numéro de candidat recherché
    while(maliste != NULL && maliste->cin_num != numero_recherche)
    {
        maliste = maliste->suivant; // On s'intéresse à l'électeur suivant
    }

    if (maliste != NULL) // Si maliste ne pointe pas vers NULL, alors on est sorti de la boucle car on a trouvé un électeur avec le numéro de carte d'identité recherché
        return 1; // Dans ce cas on retourne 1
    else // Si maliste == NULL, alors on n'a pas trouvé d'élécteur ayant le même numéro de carte d'identité que celui recherché
        return 0; // Dans ce cas on retourne 0
}

// Cette fonction retourne 1 si l'électeur ayant le numéro de carte d'identité recherché se trouve dans la liste maliste, 0 sinon. De plus, si l'électeur se trouve dans la liste, alors les renseignements le concernant son affichés à l'écran
int trouvelecteur(T_Electeur maliste, long numero_recherche)
{
    // Tout pendant qu'on est pas à la fin de la liste et qu'on a pas trouvé un électeur avec le numéro de candidat recherché
    while(maliste != NULL && maliste->cin_num != numero_recherche)
    {
        maliste = maliste->suivant; // On s'intéresse à l'électeur suivant
    }

    if (maliste != NULL)
    { // Si maliste ne pointe pas vers NULL, alors on est sorti de la boucle car on a trouvé un électeur avec le numéro de carte d'identité recherché
        printf("\n********************************************************\n\n");
        printf("%s - ", maliste->nom); // Affichage du nom
        printf("%lu - ", maliste->cin_num); // Affichage du numéro de carte d'identité
        printf("%d\n", maliste->choix); // Affichage du choix de l'électeur
        printf("\n********************************************************\n\n");
        return 1; // Dans ce cas on retourne 1
    }
    else
    { // Si maliste == NULL, alors on n'a pas trouvé d'élécteur ayant le même numéro de carte d'identité que celui recherché
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
        if((*maliste)->cin_num == numero_recherche) // Suppression du premier électeur
        {
            T_Electeur prev = *maliste; // prev permet de ne pas perdre l'électeur en tête de liste
            *maliste = (*maliste)->suivant; // L'électeur en tête de liste devient l'électeur suivant celui qui était en tête de liste
            free(prev); // prev contient l'adresse d'un objet électeur. L'espace en mémoire consacré à contenir cet objet va être libéré
            printf("L'electeur a bien ete supprime !\n");
        }

        else // Suppression au milieu ou en fin de liste
        {
            T_Electeur prev = NULL, cur = *maliste; // Initialisation de l'électeur prev qui, après la boucle, précèdera l'électeur à supprime
            // Initialisation de l'électeur cur qui, après la boucle, sera l'électeur à supprimer

            while(cur != NULL && cur->cin_num != numero_recherche) // Tant qu'on est pas arrivé à la fin de la liste et qu'on a pas trouvé l'électeur à supprimer
            {
                prev = cur; // On s'intéresse à l'électeur suivant
                cur = cur->suivant;
            }


            if (cur != NULL) // Si cur ne vaut pas NULL, alors on est sorti de la boucle car la condition cur->cin_num != numero_recherche n'était plus respecté. L'électeur à supprimer a donc été trouvé
            {
                prev->suivant = cur->suivant; // L'élément avant celui à supprimer doit pointer vers celui qui se trouve après celui qu'on va supprimer

                free(cur); // cur contient l'adresse de l'électeur à supprimer. La place en mémoire consacrée à contenir cet électeur va être libéré
                printf("L'electeur a bien ete supprime !\n");
            }

            else // Si on est sorti de la boucle car cur vaut NULL. Cela signifie qu'on a parcouru toute la liste et qu'aucun électeur ne possède le numéro de carte recherché.
            { // Ainsi dans notre liste, il n'y a pas d'électeur dont le numéro est celui recherché
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
     while(maliste != NULL) // Tant que nous ne sommes pas arrivés à la fin de notre liste
        {
        if (maliste->choix == 1 || maliste->choix == 3) // Si le choix de l'électeur que nous sommes en train de traiter est 1 ou 3
                ajoutelecteur(liste_gauche, maliste->nom, maliste->cin_num, maliste->choix); // Alors on ajoute cet électeur à la liste des électeurs de gauche
        if (maliste->choix == 2 || maliste->choix == 4) // Si le choix de l'électeur que nous sommes en train de traiter est 2 ou 4
                ajoutelecteur(liste_droite, maliste->nom, maliste->cin_num, maliste->choix); // Alors on ajoute cet électeur à la liste des électeurs de droite
        if (maliste->choix==5) // Si le choix de l'électeur que nous sommes en train de traiter est 5
                ajoutelecteur(liste_blanc, maliste->nom, maliste->cin_num, maliste->choix); // Alors on ajoute cet électeur à la liste des électeurs votant blanc
        maliste = maliste->suivant; // On s'intéresse à l'électeur suivant
        }
     printf("La liste a bien ete separee en 3 listes.\n"); // On affiche un message une fois que toute notre liste a été séparée en sous-listes
    }
}

// Choix du tri : tri à bulle
void triliste(T_Electeur maliste)
{
    if (maliste!=NULL) // Si maliste est un pointeur dont la valeur n'est pas NULL, alors nous trions notre liste. Sinon, il n'y a pas de liste à trier et nous ne faisons aucune action
    {
     T_Electeur parcours = NULL;
     T_Electeur suiv = NULL;
     char nom[NBMAX];
     long cin_num = 0;
     int choix = 0;

     for(int i = comptelecteur(maliste)-1 ; i >= 1  ; i -= 1) // On réalise n-1 fois cette boucle. i prend successivement les valeurs ,n-1, n-2... jusqu'à 1
     {
        parcours = maliste; // À chaque nouvel itération de i, l'électeur parcours prend pour valeur le premier électeur de notre liste
        suiv = maliste->suivant; // L'électeur suiv prend pour valeur le deuxième électeur de notre liste
        for(int j = 0 ; j < i ; j++) // On incrémente j de 1 à chaque boucle et on s'arrête quand on rencontre la limite posée par i qui se ressert à chaque itération sur i. j prend successivement les valeurs 1, 2... jusqu'à i
        {
            if(suiv->cin_num < parcours->cin_num)//si le cin_num de l'électeur suivant est inferieur à celui de l'électeur parcours, on les échange
            {
                strcpy(nom, parcours->nom); // On stock dans nom la valeur de l'électeur parcours
                cin_num = parcours->cin_num; // On stock dans cin_num la valeur cin_num de l'électeur parcours
                choix = parcours->choix; // On stock dans choix le choix de l'électeur parcours

                // On échange les attributs des deux électeurs parcours et suivant
                strcpy(parcours->nom, suiv->nom);
                parcours->cin_num = suiv->cin_num;
                parcours->choix = suiv->choix;

                strcpy(suiv->nom, nom);
                suiv->cin_num = cin_num;
                suiv->choix = choix;
            }
            parcours = parcours->suivant; // L'électeur parcours devient l'électeur suiv
            suiv = suiv->suivant; // L'électeur suiv devient l'électeur suivant l'électeur suiv
            // En procédant ainsi par échange successif de deux électeurs côte à côte, on fait remonter l'élécteur ayant le plus grand cin_num dans la liste
        }
     }
    }
}

T_Electeur fusionlistes(T_Electeur liste_gauche, T_Electeur liste_droite)
{
    T_Electeur nouvelle_liste = NULL; // Initialisation de la liste qui contiendra les électeurs de gauche et les électeurs de droite

    while(liste_droite != NULL) // Tant que nous ne sommes pas à la fin de la liste des électeurs de droite
    {
        ajoutelecteur(&nouvelle_liste, liste_droite->nom, liste_droite->cin_num, liste_droite->choix); // On ajoute l'électeur que nous sommes en train de traiter à la liste des électeurs de gauche et de droite
        liste_droite = liste_droite->suivant; // On s'intéresse à l'électeur suivant dans la liste liste_droite
    }

    while(liste_gauche != NULL) // Tant que nous ne sommes pas à la fin de la liste des électeurs de gauche
    {
        ajoutelecteur(&nouvelle_liste, liste_gauche->nom, liste_gauche->cin_num, liste_gauche->choix); // On ajoute l'électeur que nous sommes en train de traiter à la liste des électeurs de gauche et de droite
        liste_gauche = liste_gauche->suivant; // On s'intéresse à l'électeur suivant dans la liste liste_gauche
    }

    triliste(nouvelle_liste); // Une fois que nous avons construit la liste des électeurs de droite et de gauche, nous trions cette liste selon les numéros de carte d'identité grâce à la fonction triliste définie précedemment
    return nouvelle_liste; // On retourne la liste des électeurs de gauche et de droite
}

int compteGD(T_Electeur liste_fusionee)
{
    if (liste_fusionee == NULL)
    {
        printf("Impossible d'afficher les pourcentages ! La liste de fusion des electeurs de droite et de gauche n'a pas ete creee !\n");
    }
    else
    {
        int compteur = 0; // On initialise la variable qui contiendra le nombre d'électeur de gauche à 0

        while(liste_fusionee != NULL) // Tant que nous ne sommes pas arrivé à la fin de notre liste
        {
            if(liste_fusionee->choix == 1 || liste_fusionee->choix == 3) // Si l'électeur que nous sommes en train de traiter à voter à gauche
            {
                compteur++; // Alors la variable nous indiquant le nombre d'électeurs de gauche est incrémentée de 1
            }
            liste_fusionee = liste_fusionee->suivant; // On s'intéresse à l'électeur suivant
        }

    return compteur; // À l'issue de la boucle, nous avons parcouru toute la liste. On retourne donc compteur qui contient le nombre d'électeur de gauche de notre liste
    }
}

T_Electeur liberer(T_Electeur maliste)
{
    T_Electeur tampon = maliste;
    T_Electeur tamponnext;
    while(tampon != NULL) // Tant que nous ne sommes pas arrivé à la fin de notre liste
    {
        tamponnext = tampon->suivant; // On stock l'électeur suivant celui que l'on va supprimer
        free(tampon); // On supprime l'électeur à supprimer
        tampon = tamponnext; // L'électeur à supprimer devient l'électeur suivant que nous avions stocker dans la variable tamponnext
    }
    return NULL; // On retourne NULL pour qu'on puisse fixer à NULL la valeur des pointeurs dont on supprime la liste. On utilise alors la syntaxe liste_a_liberer = liberer(liste_a_liberer);
}

