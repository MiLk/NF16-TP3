#include "tp3.h"

int main(int argc, char** argv)
{
    task *list = NULL;
    int i = 0;
    FILE* fsource;

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

#if defined(_WIN32)
    printf("Appuyez sur une touche pour quitter\n");
    getchar();
#endif
    return (EXIT_SUCCESS);
}

