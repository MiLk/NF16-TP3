#include "tp3.h"

// Fonctions � r�aliser

task * cree_tache(char caract[MAX_NOM + 1], int duree)
{
    task *ptask = (task*) malloc(sizeof (task));
    int i = 0;
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
        task* next = list_task->psuivant;
        execution(list_task);
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
    task* pt1 = list_task1;
    task* pt2 = list_task2;
    task* ptask = NULL;
    task* pnext = ptask;
    while (pt1->psuivant != NULL && pt2->psuivant != NULL)
    {

        if ((pt1 != NULL) && (pt1->duree < pt2->duree || pt2 == NULL))
        {
            pnext->psuivant = pt1;
            pt1 = pt1->psuivant;
            pnext = pnext->psuivant;
        } else
        {
            pnext->psuivant = pt2;
            pnext = pnext->psuivant;
        }
    }
    pnext->psuivant = NULL;

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
    printf("Chargement : %s\n", ptask->ID);

    return insere_tache(list, ptask);
}

task * charge_tache_priorite(FILE* fsource, task* list)
{
    char nom[256];
    int duree;
    task *ptask = NULL;

    if (fscanf(fsource, "%s\t%d\n", nom, &duree) == EOF) return list;
    ptask = cree_tache(nom, duree);
    return insere_tache_priorite(list, ptask);
}
