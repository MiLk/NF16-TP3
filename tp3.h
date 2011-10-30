#ifndef TP3_H
#define	TP3_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#if defined(_DARWIN_C_SOURCE)
#include "unistd.h"
#elif defined(_WIN32)
#include "windows.h"
#endif

#define MAX_NOM 100

typedef struct task {
    char ID[MAX_NOM + 1];
    int duree;
    int priorite;
    struct task *psuivant;
} task;

/**
 * Créer une tache avec l'identifiant et la durée prévisée.
 * @param caract Identifiant de la tâche
 * @param duree Durée de la tâche
 * @return Pointeur de tâche
 */
task * cree_tache(char caract[MAX_NOM + 1], int duree);

/**
 * Initialise une liste à partir d'un pointeur de tâche.
 * @param tache Tâche permettant l'initialisation.
 * @return Pointeur sur la première tâche de la liste.
 */
task * cree_liste(task *tache);

/**
 * Affiche la liste des tâches de la liste spécifiée.
 * @param list_task Liste de tâches.
 */
void affiche_liste(task *list_task);

/**
 * Ajoute une nouvelle tâche à la liste
 * @param list_task Liste de tâche
 * @param ptache Nouvelle tâche
 * @return 
 */
int ajoute_tache(task *list_task, task *ptache);

/**
 * Annule l'execution d'une tâche.
 * @param list_task Liste de tâches.
 * @param caract Identifiant de la tâche.
 * @return Pointeur sur la première tâche de la liste.
 */
task * annule_tache(task *list_task, char caract[MAX_NOM + 1]);

/**
 * Libère l'espace mémoire allouée pour les différents éléments de la liste des tâches.
 * @param list_task Liste des tâches.
 * @return Pointeur sur la première tâche de la liste.
 */
task * libere_liste(task *list_task);

/**
 * Execute la liste des tâches selon le mode FIFO.
 * @param list_task
 * @return nouvelle liste des tâches
 */
task * execute_tache_FIFO(task *list_task);

/**
 * Execute la liste des tâches selon le mode LIFO.
 * @param list_task
 * @return nouvelle liste des tâches
 */
task * execute_tache_LIFO(task *list_task);

/**
 * Retourne une liste de tâches, résultat de la fusion des 2 listes passées en paramètres
 * @param list_task1
 * @param list_task2
 * @return 
 */
task * fusion_listes(task *list_task1, task *list_task2);

/**
 * Insere une tache dans la liste par ordre croissant de priorite
 * @param list_task
 * @param ptache
 * @return 
 */
task * insere_tache_priorite(task *list_task, task *ptache);

/**
 * Baisse les priorites de tous les elements de la liste de 1
 * @param list_task
 * @return 
 */
int MAJ_priorite(task *list_task);


/**
 * Retourne la dernière tâche d'une listede tâches.
 * @param list_task Liste de tâches
 * @return Dernière tâche
 */
task* derniere_tache(task *list_task);

/**
 * Retourne l'avant-dernière tâche d'une listede tâches.
 * @param list_task
 * @return 
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
 * Insere une tache dans la liste par ordre croissant des durees
 * @param list_task
 * @param toinsert
 * @return 
 */
task * inserer_tache(task *list_task, task *toinsert);

/**
 * Simule l'execution d'une tache
 * @param ptask
 */
void execution(task *ptask);

/**
 * Charge une tache dans la liste depuis un fichier
 * @param file
 * @param list_task
 * @return 
 */
task * charger_tache(FILE* file, task* list_task);

/**
 * Charge une tache dans la liste depuis un fichier en utilisant les priorites
 * @param file
 * @param list_task
 * @return 
 */
task * charger_tache_priorite(FILE* file, task* list_task);

#endif	/* TP3_H */

