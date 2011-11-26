#include "tp3.h"

int main(int argc, char** argv)
{
    int n, stop = 0, i = 0;
    stop = 0;
    task *list = NULL, *list2 = NULL, *temp_task = NULL;
    FILE* fsource;
    char caract[MAX_NOM + 1];
    int duree;

    while (!stop)
    {
        printf("\nChoisir la fonction a executer. 0 pour stopper.\n");
        printf("1 - cree_tache.\n");
        printf("2 - cree_liste.\n");
        printf("3 - affiche_liste.\n");
        printf("4 - ajoute_tache.\n");
        printf("5 - annule_tache.\n");
        printf("6 - libere_liste.\n");
        printf("7 - execute_tache_FIFO.\n");
        printf("8 - execute_tache_LIFO.\n");
        printf("9 - fusion_listes.\n");
		printf("10 - insere_tache.\n");
        printf("11 - insere_tache_priorite.\n");
        printf("12 - MAJ_priorite.\n");
        printf("13 - Simulation avec priorite selon la duree.\n");
        printf("14 - Simulation avec priorite dynamique.\n");
		printf("15 - Copier la liste principal dans une liste secondaire.\n");
		printf("16 - Generation et fusion de deux listes.\n");
        scanf("%d", &n);
        switch (n)
        {
            case 1:
                printf("Saississez l'identifiant de la tache.\n");
                scanf("%s", caract);
                printf("Saississez la duree de la tache.\n");
                scanf("%d", &duree);
                temp_task = cree_tache(caract,duree);
                printf("Nouvelle Tache courante : %s ( %d sec )\n",temp_task->ID,temp_task->duree);
                break;
            case 2: 
                list = cree_liste(temp_task);
                printf("Nouvelle liste  avec première tache : %s ( %d sec )\n",list->ID,list->duree);
                break;
            case 3:
                affiche_liste(list);
                break;
            case 4: 
                ajoute_tache(list,temp_task);
                printf("La tache courant a ete ajoutee a la liste\n");
                break;
            case 5:
                printf("Saississez l'identifiant de la tachea annuler.\n");
                scanf("%s", caract);
                annule_tache(list,caract);
                printf("La tache a ete annulee.\n");
                break;
            case 6: 
                libere_liste(list);
                printf("La memoire occupee par la liste a ete liberee.\n");
                break;
            case 7: 
                execute_tache_FIFO(list);
                break;
            case 8: 
                execute_tache_LIFO(list);
                break;
            case 9:
				printf("Liste principale\n");
				affiche_liste(list);
				printf("Liste secondaire\n");
				affiche_liste(list2);
				printf("Liste fusionnee\n");
				list = fusion_listes(list,list2);
				affiche_liste(list);
                break;
            case 10: 
                list = insere_tache(list,temp_task);
                printf("La tache courant a ete inseree a la liste en fonction de sa duree\n");
                break;
			case 11: 
                list = insere_tache_priorite(list,temp_task);
                printf("La tache courant a ete inseree a la liste en fonction de sa priorite\n");
                break;
            case 12:
                MAJ_priorite(list);
                printf("Les priorites ont ete mises a jour.\n");
                break;
            case 13:
                printf("\n\nPriorite selon la duree des taches\n\n");
                fsource = fopen("tasks.dat", "r");
                for (i = 0; i < 10; i++)
                    list = charge_tache(fsource, list);

                affiche_liste(list);
                while (list != NULL)
                {
                    list = execute_tache_FIFO(list);
                    list = charge_tache(fsource, list);
                }
                fclose(fsource);
                break;
            case 14:
                printf("\n\nChangement dynamique de priorite\n\n");

                list = NULL;
                fsource = fopen("tasksf.dat", "r");
                for (i = 0; i < 10; i++)
                    list = charge_tache_priorite(fsource, list);

                affiche_liste(list);
                while (list != NULL)
                {
                    list = execute_tache_FIFO(list);
                    MAJ_priorite(list);
                    list = charge_tache_priorite(fsource, list);
                }
                fclose(fsource);
                break;
			case 15:
				list2 = list;
				break;
			case 16: 
				temp_task = cree_tache("a",3);
				list = cree_liste(temp_task);
				temp_task = cree_tache("b",4);
				list = insere_tache(list,temp_task);
				temp_task = cree_tache("g",7);
				list = insere_tache(list,temp_task);
				temp_task = cree_tache("h",9);
				list = insere_tache(list,temp_task);
				printf("Liste principale\n");
				affiche_liste(list);
				temp_task = cree_tache("c",5);
				list2 = cree_liste(temp_task);
				temp_task = cree_tache("d",2);
				list2 = insere_tache(list2,temp_task);
				temp_task = cree_tache("e",12);
				list2 = insere_tache(list2,temp_task);
				temp_task = cree_tache("f",8);
				list2 = insere_tache(list2,temp_task);
				printf("Liste secondaire\n");
				affiche_liste(list2);
				printf("Liste fusionnee\n");
				list = fusion_listes(list,list2);
				affiche_liste(list);
                break;
            default: stop = 1;
                break;
        }
    }

    return (EXIT_SUCCESS);
}

