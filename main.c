#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tp3.h"

int main()
{
    int choice1,choice2;
    int sortie=0;

    char strnom[NBMAX];
    long int cin_num;
    int choix;
    T_Electeur liste_electorale=NULL;
    T_Electeur liste_electoraleG=NULL;
    T_Electeur liste_electoraleB=NULL;
    T_Electeur liste_electoraleD=NULL;
    T_Electeur liste_electoraleGD=NULL;
    float coef;
    char s[256];

    while(sortie==0)//tant que la sortie n'est pas demandée par l'activation de 9, on répète le switch
    {
    printf("***********************************************************************************************************************\n");
    printf("                                                           MENU\n");
    printf("***********************************************************************************************************************\n\n");
    printf("1....................................................Ajout d'electeurs.................................................\n");
    printf("2.................................................Suppression d'electeurs..............................................\n");
    printf("3.................................................Recherche d'un electeur..............................................\n");
    printf("4.............................................Afficher la liste des electeurs..........................................\n");
    printf("5..............................................Calculer le nombre d'electeurs..........................................\n");
    printf("6.............................................Separation en trois sous listes..........................................\n");
    printf("7........................................Calcul des pourcentages pour le 2eme tour.....................................\n");
    printf("8....................................................Liberer les listes................................................\n");
    printf("9.........................................................Quitter......................................................\n");
    printf("\n***********************************************************************************************************************\n\n");


    scanf("%s", s);

    while(isNumber(s) != 1)
    {
        printf("Vous devez entrez un entier ! Recommencez !\n");
        scanf("%s", s);
    }
    choice1 = atoi(s);

    while(choice1 < 1 || choice1 > 9)
    {
        printf("Vous devez entrez un chiffre entre 1 et 9 ! Recommencez \n");
        scanf("%d", &choice1);
    }


    switch(choice1) //on agit selon le choice1
    {
        case 1 :
                printf("\n***********************************************************************************************************************\n\n");
                printf("\n-------------------------------\n");

                printf("Un nom ?\n");
                scanf("%s", strnom);
                while(strlen(strnom) > NBMAX)
                {
                    printf("Le nom doit faire au maximum %d caracteres ! Recommencez !\n", NBMAX);
                    scanf("%s", strnom);
                }
                while(isNumber(strnom) == 1)
                {
                    printf("Le nom doit etre une chaine de caractere ! Recommencez !\n");
                    scanf("%s", strnom);
                }

                // Cette boucle transforme le nom en chaîne de caractère majuscule
                for(int i = 0 ; strnom[i] != '\0' ; i++)
                {
                    strnom[i] = toupper(strnom[i]);
                }

                printf("Un numero de carte d'identite ?\n");
                scanf("%s",s);
                while( isNumber(s)!=1 )
                {
                    printf("Le numero de carte d'identite doit etre un entier !\n");
                    scanf("%s",s);
                }

                cin_num=atoi(s);

                printf("Un choix entre 1 et 5 ?\n");
                scanf("%s", s);

                while( isNumber(s) != 1)
                {
                    printf("Le choix doit etre un entier ! Recommencez !\n");
                    scanf("%s", s);
                }
                choix = atoi(s);

                while(choix < 1 || choix > 5)
                {
                    printf("Le choix doit etre compris entre 1 et 5 ! Recommencez !\n");
                    scanf("%d",&choix);
                }

                ajoutelecteur(&liste_electorale, strnom, cin_num, choix);

                printf("-------------------------------\n");
                printf("\n\n***********************************************************************************************************************\n\n");
                break;
        case 2 :
                printf("\n***********************************************************************************************************************\n\n");
                printf("\n-------------------------------\n");
                // Suppression de l'electeur dans la liste principale
                printf("Un numero de carte d'identite ?\n");
                scanf("%d",&cin_num);
                Supprimelecteur(&liste_electorale, cin_num);
                // Suppression de l'electeur dans les listes secondaires si elles existes
                if (presence(liste_electoraleG, cin_num))  Supprimelecteur(&liste_electoraleG, cin_num);
                else if (presence(liste_electoraleB, cin_num))  Supprimelecteur(&liste_electoraleB, cin_num);
                else if (presence(liste_electoraleD, cin_num))  Supprimelecteur(&liste_electoraleD, cin_num);

                if (presence(liste_electoraleGD, cin_num))  Supprimelecteur(&liste_electoraleGD, cin_num);

                printf("\n-------------------------------\n");
                printf("\n\n***********************************************************************************************************************\n\n");
                break;
        case 3 :
                printf("\n***********************************************************************************************************************\n\n");
                printf("\n-------------------------------\n");

                printf("Un numero de carte d'identite ?\n");
                scanf("%d",&cin_num);
                trouvelecteur(liste_electorale, cin_num);

                printf("\n-------------------------------\n");
                printf("\n\n***********************************************************************************************************************\n\n");
                break;
        case 4 :
                printf("\n***********************************************************************************************************************\n\n");

                afficheliste(liste_electorale);

                printf("\n***********************************************************************************************************************\n\n");
                break;
        case 5 :
                printf("\n***********************************************************************************************************************\n\n");
                printf("\n-------------------------------\n");

                if (comptelecteur(liste_electorale) == 0)
                {
                    printf("Il n'y a aucun electeur d'inscrit sur la liste electorale.\n");
                }
                else if(comptelecteur(liste_electorale) == 1)
                {
                    printf("1 electeur est actuellement inscrit sur la liste electorale.\n");
                }
                else
                {
                    printf("%d electeurs sont actuellement inscrits sur la liste electorale.\n", comptelecteur(liste_electorale));
                }

                printf("-------------------------------\n");
                printf("\n***********************************************************************************************************************\n\n");
                break;
        case 6 :
                printf("\n***********************************************************************************************************************\n\n");
                decoupeliste(liste_electorale, &liste_electoraleG, &liste_electoraleD, &liste_electoraleB);

                if(liste_electorale != NULL) // Si la liste électorale est un pointeur sur NULL, alors les sous-listes valent et on ne va donc pas les trier, les afficher, ni les fusionner
                {
                    printf("\n****************ACTIONS EFFECTUEES CI DESSOUS*************\n\n");
                    printf(".....................Tri des 3 sous-listes................\n");
                    printf("...................Affichage des sous-listes..............\n");
                    printf("...........Fusion des sous-liste droite et gauche.........\n");
                    printf("\n**********************************************************\n");

                    if (liste_electoraleG == NULL)
                    {
                        printf("La sous-liste des electeurs de gauche n'existe pas. Impossible de la trier !\n");
                    }
                    else
                    {
                        triliste(liste_electoraleG);
                        printf("La sous-liste des electeurs de gauche a bien ete triee !\n");
                    }

                    if (liste_electoraleB == NULL)
                    {
                        printf("La sous-liste des electeurs votant blanc n'existe pas. Impossible de la trier !\n");
                    }
                    else
                    {
                        triliste(liste_electoraleB);
                        printf("La sous-liste des electeurs votant blanc a bien ete triee !\n");
                    }

                    if (liste_electoraleD == NULL)
                    {
                        printf("La sous-liste des electeurs de droite n'existe pas. Impossible de la trier !\n");
                    }
                    else
                    {
                        triliste(liste_electoraleD);
                        printf("La sous-liste des electeurs de droite a bien ete triee !\n");
                    }

                    printf("\n>>>>Liste de gauche : ");
                    afficheliste(liste_electoraleG);
                    printf("\n>>>>Liste blanc : ");
                    afficheliste(liste_electoraleB);
                    printf("\n>>>>Liste de droite : ");
                    afficheliste(liste_electoraleD);

                    liste_electoraleGD=fusionlistes(liste_electoraleG, liste_electoraleD);
                    printf("\n\n>>>>Fusion droite-gauche : ");
                    afficheliste(liste_electoraleGD);
                }

                printf("\n***********************************************************************************************************************\n\n");
                break;
        case 7 :
                printf("\n***********************************************************************************************************************\n\n");
                printf("\n-------------------------------\n");

                coef=(float)compteGD(liste_electoraleGD)/comptelecteur(liste_electoraleGD);
                if (liste_electoraleGD != NULL)  // Dans ce cas là on affiche les pourcentages
                {
                    printf("Voici les pourcentages : \n");
                    printf("Pour la gauche : %.2f\n", coef*100);
                    printf("Pour la droite : %.2f", (1-coef)*100);
                    printf("\n-------------------------------\n");
                    printf("\n***********************************************************************************************************************\n\n");
                }
                break;
        case 8 :
                printf("\n***********************************************************************************************************************\n\n");
                printf("\n----------------------------------------------------------------------------------------------\n");
                printf("Liberer La liste principale : taper 1 / Les sous-listes : taper 2 / Toutes les listes : taper 3 \n");
                scanf("%s", s);
                while(isNumber(s) != 1)
                {
                    printf("Vous devez entrez un entier ! Recommencez !\n");
                    scanf("%s", s);
                }
                choice2 = atoi(s);

                while(choice2<1 || choice2>3)
                {
                    printf("Vous devez tapez 1 pour liberer la liste principale, 2 pour les sous-listes ou 3 pour toutes les listes. Recommencez !\n");
                    scanf("%d",&choice2);
                }
                if (choice2==1)
                {
                    if (liste_electorale == NULL)
                    {
                        printf("La liste principale n'existe pas !\n");
                    }
                    else
                    {
                        liste_electorale=liberer(liste_electorale);
                        printf("Liste principale liberee\n");
                    }
                }
                if (choice2==2)
                {
                    if (liste_electoraleG == NULL && liste_electoraleB == NULL && liste_electoraleD == NULL && liste_electoraleGD == NULL)
                    {
                        printf("Aucune des sous-listes n'existe !\n");
                    }
                    else
                    {
                        liste_electoraleG=liberer(liste_electoraleG);
                        liste_electoraleB=liberer(liste_electoraleB);
                        liste_electoraleD=liberer(liste_electoraleD);
                        liste_electoraleGD=liberer(liste_electoraleGD);
                        printf("Sous-listes liberees");
                    }

                }
                if (choice2==3)
                {
                    if (liste_electorale == NULL && liste_electoraleG == NULL && liste_electoraleB == NULL && liste_electoraleD == NULL && liste_electoraleGD == NULL)
                    {
                        printf("Aucune listes n'existe !\n");
                    }
                    else
                    {
                        liste_electorale=liberer(liste_electorale);
                        liste_electoraleG=liberer(liste_electoraleG);
                        liste_electoraleB=liberer(liste_electoraleB);
                        liste_electoraleD=liberer(liste_electoraleD);
                        liste_electoraleGD=liberer(liste_electoraleGD);
                        printf("Toutes les listes ont ete liberees");
                    }
                }
                printf("\n----------------------------------------------------------------------------------------------\n");
                printf("\n***********************************************************************************************************************\n\n");
                break;
        default :
                 sortie=1;
                 break;
    }
    }
    return 0;
}
