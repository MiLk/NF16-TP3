#include "tp3.h"

// Fonctions � r�aliser

task * cree_tache(char caract[MAX_NOM + 1], int duree)
{
    task *ptask = (task*) malloc(sizeof (task));
    int i = 0;
	// On copie les caracteres de la chaine un par un
    for (i = 0; i <= MAX_NOM; i++)
        ptask->ID[i] = caract[i];
    ptask->duree = duree;
    ptask->psuivant = NULL;
    return ptask;
}

task * cree_liste(task *tache)
{
    return tache;
}

void affiche_liste(task *list_task)
{
    task *ptask = list_task;
    printf("_______________________\n");
    printf("\nAffichage de la liste :\n");
    while (ptask != NULL)
    {
        printf("Task id : %s - duree : %d\n", ptask->ID, ptask->duree);
        ptask = ptask->psuivant;
    }
    printf("_______________________\n\n");
    return;
}

int ajoute_tache(task *list_task, task *ptache)
{
    task *last = derniere_tache(list_task);
    last->psuivant = ptache;
    return 0;
}

task * annule_tache(task *list_task, char caract[MAX_NOM + 1])
{
    task *prev = recherche_predecesseur_tache(list_task, caract);
    task *tocancel = prev->psuivant;
    prev->psuivant = tocancel->psuivant;
    free(tocancel);
    return list_task;
}

task * libere_liste(task *list_task)
{
    if (list_task != NULL)
    {
        task * next = list_task->psuivant;
        free(list_task);
        return libere_liste(next);
    } else
        return list_task;
}

task * execute_tache_FIFO(task *list_task)
{
    if (list_task != NULL)
    {
		// On recupere le deuxieme element de la liste
        task* next = list_task->psuivant;
		// On execute le premier element
        execution(list_task);
		// On retourne la liste commencant par le deuxieme element
        return next;
    } else
        return list_task;
}

task * execute_tache_LIFO(task *list_task)
{
    if (list_task != NULL)
    {
        task* ptask = avant_derniere_tache(list_task);
        if (ptask->psuivant != NULL)
        {
            execution(ptask->psuivant);
            ptask->psuivant = NULL;
            return list_task;
        } else
        {
            execution(ptask);
            return NULL;
        }
    } else
        return list_task;
}

task * fusion_listes(task *list_task1, task *list_task2)
{
	if(list_task1 == NULL) return list_task2;
	if(list_task2 == NULL) return list_task1;
    task *pt1 = list_task1,*pt2 = list_task2;
    task *ptask = NULL, *pprev = NULL;
    while (!(pt1 == NULL && pt2 == NULL))
    {
		/*
		 * Si la tache 1 est non nulle
		 * ET si le tache 1 est plus courte que la tache 2
		 *		OU que la tache 2 est nulle
		 * On met la tache 1 dans la liste
		 */
        if ((pt1 != NULL) && (pt1->duree < pt2->duree || pt2 == NULL))
        {
			if(ptask == NULL)
				ptask = pt1; // On initialise la liste avec le premier element
			else
				pprev->psuivant = pt1; // On passe l'element suivant de l'element venant d'etre traite a l'emement courant
			pprev = pt1; // On indique l'element venant d'etre traite
			pt1 = pt1->psuivant; // On passe a l'element suivant de la liste 1
        }
		/*
		 * Si la tache 1 est nulle
		 * OU Si la tache 2 est plus courte ou égale à la tache 1
		 *		ET que la tache 2 est non nulle
		 * On met la tache 2 dans la liste
		 */
		else
        {
			if(ptask == NULL)
				ptask = pt2; // On initialise la liste avec le premier element
			else
				pprev->psuivant = pt2; // On passe l'element suivant de l'element venant d'etre traite a l'emement courant
			pprev = pt2; // On indique l'element venant d'etre traite
			pt2 = pt2->psuivant; // On passe a l'element suivant de la liste 2
        }
    }
    return ptask;
}

task * insere_tache_priorite(task *list_task, task *ptache)
{
    task* ptask = list_task;

    ptache->priorite = (int) (ptache->duree / 10);
    if (ptache->priorite > 5)
        ptache->priorite = 5;
    if (ptache->priorite < 1)
        ptache->priorite = 1;

    if (list_task == NULL)
        return cree_liste(ptache);

    while (ptache->priorite > ptask->priorite)
    {
        if (ptask->psuivant == NULL)
        {
            ajoute_tache(ptask, ptache);
            return list_task;
        }
        if (ptask->psuivant->priorite >= ptache->priorite)
        {
            ptache->psuivant = ptask->psuivant;
            ptask->psuivant = ptache;
            return list_task;
        }
        ptask = ptask->psuivant;
    }
	// Duree de la tache a inserer < duree de la premiere tache
    ptache->psuivant = ptask;
    return ptache;
}

int MAJ_priorite(task *list_task)
{
    if (list_task == NULL) return 0;
    if (list_task->priorite > 1)
        list_task->priorite--;

    return MAJ_priorite(list_task->psuivant);
}

// Fonctions suppl�mentaires

task* derniere_tache(task *list_task)
{
    task *ptask = list_task;
    while (ptask->psuivant != NULL)
    {

        ptask = ptask->psuivant;
    }
    return ptask;
}

task* avant_derniere_tache(task *list_task)
{
    task *ptask = list_task;
    while (ptask->psuivant != NULL && ptask->psuivant->psuivant != NULL)
    {

        ptask = ptask->psuivant;
    }
    return ptask;
}

task* recherche_predecesseur_tache(task *list_task, char caract[MAX_NOM + 1])
{
    task *ptask = list_task;
    while (ptask->psuivant != NULL && strcmp(ptask->psuivant->ID, caract))
    {

        ptask = ptask->psuivant;
    }
    return ptask;
}

task * insere_tache(task *list_task, task *toinsert)
{
    task* ptask = list_task;
    if (list_task == NULL)
        return cree_liste(toinsert);
    while (toinsert->duree > ptask->duree)
    {
        if (ptask->psuivant == NULL)
        {
            ajoute_tache(ptask, toinsert);
            return list_task;
        }
        if (ptask->psuivant->duree >= toinsert->duree)
        {
            toinsert->psuivant = ptask->psuivant;
            ptask->psuivant = toinsert;
            return list_task;
        }
        ptask = ptask->psuivant;
    }
	// Duree de la tache a inserer < duree de la premiere tache
    toinsert->psuivant = ptask;
    return toinsert;
}

void execution(task *ptask)
{

    printf("Execution : %s - %d sec - priority %d\n", ptask->ID, ptask->duree, ptask->priorite);
#if defined(_DARWIN_C_SOURCE)
    sleep(ptask->duree);
#elif defined(_WIN32)
    Sleep(ptask->duree * 1000);
#endif
    free(ptask);
}

task * charge_tache(FILE* fsource, task* list)
{
    char nom[MAX_NOM];
    int duree;
    task *ptask = NULL;

    if (fscanf(fsource, "%s\t%d\n", nom, &duree) == EOF) return list;
    ptask = cree_tache(nom, duree);
    printf("Chargement de la tache : %s\n", ptask->ID);

    return insere_tache(list, ptask);
}

task * charge_tache_priorite(FILE* fsource, task* list)
{
    char nom[MAX_NOM];
    int duree;
    task *ptask = NULL;

    if (fscanf(fsource, "%s\t%d\n", nom, &duree) == EOF) return list;
    ptask = cree_tache(nom, duree);
	printf("Chargement avec priorite de la tache : %s\n", ptask->ID);

    return insere_tache_priorite(list, ptask);
}
