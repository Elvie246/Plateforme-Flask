# Prérequis

# Guide d'installation et de configuration

Ce guide explique comment installer et configurer l'environnement de développement pour la plateforme de diffusion de contenu statique basée sur le cloud.


## Étapes d'installation

## 1. Cloner le dépôt
````bash
git clone https://github.com/Elvie246/plateforme-Flask.git
````

## 2. Installer les dépendances
````bash
pip install -r requirements.txt
````

## 3. Créer un répertoire pour le projet :
````bash
mkdir nom_du_fichier
````

## 4. Pour changer de branche :
````bash
git checkout nom de la branche
````

# Bonnes pratiques 
## 1. Toujours verifier que l'on se situe sur la bonne brache avant de poussez le projet et/ou faire un commit
````bash
git branch
````
# Pour travailler sur la branche feature 
## 1. Pour commencer un feature 
````bash
git flow feature start nom_de_la_tâche
````
## 2. Pour terminer  un feature 
````bash
git flow feature finish nom_de_la_tâche
````
