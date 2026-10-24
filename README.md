# 📋 Récapitulatif du Projet — Module 1

## 🎯 Objectif Principal
Développer et valider le **Module 1 : Liste simplement chaînée**. 
Ce module gère une liste de nœuds contenant des pointeurs génériques (`void *`). Il doit être intégralement testé et validé via `testListHelpers` avant la présentation du Jalon 1.

---

## 🛠️ État des Lieux et Tâches à Réaliser (Module 1)

### 🚨 Priorité Haute — À corriger dans le code existant
- [ ] **`list_insert`** : Ajouter l'allocation dynamique de mémoire (`malloc`) pour le nouveau nœud et effectuer l'insertion en tête.
- [ ] **`list_append`** : Allouer la mémoire du nouveau nœud et corriger le parcours de la liste pour rattacher le maillon en queue.
- [ ] **`list_set_data`** : Implémenter la mise à jour du pointeur de donnée dans le nœud.

### ⏳ Priorité Moyenne — Fonctions restant à implémenter
- [ ] **`list_orderedAppend`** : Écrire la fonction d'insertion ordonnée en utilisant la fonction de comparaison transmise en paramètre (sans ajouter de doublons).
- [ ] **`list_headRemove`** : Implémenter la suppression du premier nœud et la libération de sa mémoire (`free`).
- [ ] **`list_remove`** : Implémenter la recherche et la suppression de la première instance d'une donnée spécifique.
- [ ] **`list_destroy`** : Écrire la libération complète des nœuds de la liste.

### ✅ Déjà Réalisé / Validé (Testé)
- [x] **`list_create`**
- [x] **`list_insert`**

---

## 🔮 Vue d'ensemble des Jalons Suivants (À venir)

- [ ] **Module 2**