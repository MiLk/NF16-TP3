#include "tp3.h"

int main(int argc, char** argv)
{
    task *list = NULL;
    int i = 0;
    FILE* fsource;
    
    printf("\n\nPriorite selon la duree des taches\n\n");
    fsource = fopen("tasks.dat", "r");
    for (i = 0; i < 10; i++)
        list = charger_tache(fsource, list);

    affiche_liste(list);
    while (list != NULL)
    {
        list = execute_tache_FIFO(list);
        list = charger_tache(fsource, list);
    }
    fclose(fsource);
    
    printf("\n\nChangement dynamique de priorite\n\n");
    
    list = NULL;
    fsource = fopen("tasksf.dat", "r");
    for (i = 0; i < 10; i++)
        list = charger_tache_priorite(fsource, list);

    affiche_liste(list);
    while (list != NULL)
    {
        list = execute_tache_FIFO(list);
        MAJ_priorite(list);
        list = charger_tache_priorite(fsource, list);
    }
    fclose(fsource);

#if defined(_WIN32)
            getchar();
#endif
    return (EXIT_SUCCESS);
}

