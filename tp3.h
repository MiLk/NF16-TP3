#ifndef TP3_H
#define	TP3_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// En fonction de l'OS les librairies sont différentes
#if defined(_DARWIN_C_SOURCE)
#include "unistd.h"
#elif defined(_WIN32)
#include "windows.h"
#endif

/**
 * Longueur maximale de l'identifiant de tâche
 */
#define MAX_NOM 10 

/**
 * \struct task
 * \brief Tâche à accomplir par le processeur
 */
typedef struct task {
    /** Identifiant (nom) unique de la tache */
    char ID[MAX_NOM + 1];
    /** Durée de la tâche (en période processeur) */
    int duree;
    /** Priorité de la tâche */
    int priorite;
    /** Pointeur à la tâche suivante */
    struct task *psuivant;
} task;

/**
 * Fonction 1 :
 * Crée une tâche avec l'identifiant et la durée précisée.
 * @param caract Identifiant de la tâche.
 * @param duree Durée de la tâche.
 * @return Pointeur de type task sur une tâche d’identifiant “caract” et de durée “durée”.
 */
task * cree_tache(char caract[MAX_NOM + 1], int duree);

/**
 * Fonction 2 :
 * Initialise une liste à partir d'un pointeur de tâche.
 * @param tache Tâche permettant l'initialisation.
 * @return Pointeur sur la première tâche de la liste.
 */
task * cree_liste(task *tache);

/**
 * Fonction 3 :
 * Affiche la liste des tâches de la liste spécifiée.
 * @param list_task Pointeur sur la première tâche de la liste de tâches.
 */
void affiche_liste(task *list_task);

/**
 * Fonction 4 :
 * Ajoute une nouvelle tâche à la fin de la liste des tâches.
 * @param list_task Pointeur sur le début de la liste de tâches.
 * @param ptache Nouvelle tâche.
 * @return
 */
int ajoute_tache(task *list_task, task *ptache);

/**
 * Fonction 5 :
 * Annule l'exécution d'une tâche avant qu'elle ne soit traitée.
 * @param list_task Liste de tâches.
 * @param caract Identifiant de la tâche.
 * @return Pointeur sur la première tâche de la liste.
 */
task * annule_tache(task *list_task, char caract[MAX_NOM + 1]);

/**
 * Fonction 6 :
 * Libère l'espace mémoire allouée pour les différents éléments de la liste des tâches.
 * @param list_task Liste des tâches.
 * @return Pointeur sur la première tâche de la liste.
 */
task * libere_liste(task *list_task);

/**
 * Fonction 7 + 9 :
 * Exécute une tâche de la liste des tâches selon le mode FIFO.
 * @param list_task Liste des tâches à traiter.
 * @return Nouvelle liste des tâches.
 */
task * execute_tache_FIFO(task *list_task);

/**
 * Fonction 8 :
 * Exécute une tâche de la liste des tâches selon le mode LIFO.
 * @param list_task Liste des tâches à traiter.
 * @return Nouvelle liste des tâches.
 */
task * execute_tache_LIFO(task *list_task);

/**
 * Fonction 10 :
 * Retourne une liste de tâches, résultat de la fusion des 2 listes passées en paramètres.
 * @param list_task1
 * @param list_task2
 * @return 
 */
task * fusion_listes(task *list_task1, task *list_task2);

/**
 * Fonction 11 :
 * Insère une tâche dans la liste par ordre croissant de priorité.
 * @param list_task
 * @param ptache
 * @return 
 */
task * insere_tache_priorite(task *list_task, task *ptache);

/**
 * Fonction 12
 * Baisse les priorités de tous les éléments de la liste de 1.
 * @param list_task
 * @return 
 */
int MAJ_priorite(task *list_task);


/**
 * Retourne la dernière tâche d'une liste de tâches.
 * @param list_task Liste de tâches
 * @return Dernière tâche
 */
task* derniere_tache(task *list_task);

/**
 * Retourne l'avant-dernière tâche d'une liste de tâches.
 * @param list_task
 * @return Avant-dernière tâche de la liste de tâches.
 */
task* avant_derniere_tache(task *list_task);

/**
 * Renvoit le précédesseur de la tâche dont l'indentificateur est spécifié.
 * @param list_task Liste des tâches.
 * @param caract Identificateur.
 * @return Prédécesseur
 */
task* recherche_predecesseur_tache(task *list_task, char caract[MAX_NOM + 1]);

/**
 * Insère une tache dans la liste par ordre croissant des durées.
 * @param list_task
 * @param toinsert
 * @return 
 */
task * insere_tache(task *list_task, task *toinsert);

/**
 * Simule l'exécution d'une tâche.
 * @param ptask
 */
void execution(task *ptask);

/**
 * Charge une tâche dans la liste depuis un fichier.
 * @param file
 * @param list_task
 * @return Liste des tâches.
 */
task * charge_tache(FILE* file, task* list_task);

/**
 * Charge une tâche dans la liste depuis un fichier en utilisant les priorités.
 * @param file
 * @param list_task
 * @return Liste des tâches.
 */
task * charge_tache_priorite(FILE* file, task* list_task);

#endif	/* TP3_H */

