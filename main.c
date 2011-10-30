#include "tp3.h"

int main(int argc, char** argv)
{
    task *list = NULL;
    int i = 0;

    FILE* fsource;
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

#if defined(_WIN32)
            getchar();
#endif
    return (EXIT_SUCCESS);
}

