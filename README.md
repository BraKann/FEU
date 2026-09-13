# Projet ASD2 : Aerial Image Project

## Contexte

Projet réalisé dans le cadre du cours d'Algorithmique et Structures de Données 2 (Licence Informatique, Université de Nantes). Objectif : simuler la propagation d'un feu de forêt à partir d'images aériennes, en traitant des questions de représentation, d'analyse et de simulation d'images.

## Technologies utilisées

- **C++** (compilation avec g++, sans dépendance à un IDE)
- **Format d'image AIP** (format propre au projet) en lecture, et **SVG** en écriture pour la visualisation
- **Git** pour le travail collaboratif en binôme

## Démarche

1. **Représentation des images (SDC Image)** : implémentation d'une structure de données concrète pour une image (matrice de couleurs), à partir d'une interface (SDA) déjà spécifiée, avec un choix de codage (tableau 2D ou tableau 1D linéarisé) motivé par la complexité temporelle visée.
2. **Analyse des images (SDC Analyst)** : partitionnement d'une image en zones de même couleur (composantes connexes), avec une structure de données et des algorithmes optimisés en complexité.
3. **Simulation du feu (SDA/SDC FireSimulator)** : conception d'une interface et de sa structure de données pour faire évoluer une image dans le temps (t = 0, 1, 2...), avec propagation aléatoire du feu dans une zone de forêt et extinction selon un principe d'antériorité (les zones où le feu dure depuis le plus longtemps s'éteignent en premier).
4. **Validation** : compilation stricte imposée (`g++ Color.cpp Image.cpp Analyst.cpp testeval.cpp -o testeval`), interfaces publiques non modifiables pour permettre une évaluation automatisée, et mesure du temps d'exécution.

## Compétences 

- **Conception d'interfaces (SDA)** : spécifier des méthodes publiques claires, avec préconditions, indépendamment de leur implémentation
- **Choix de structures de données (SDC)** : sélectionner une représentation mémoire en fonction de la complexité algorithmique visée, et savoir la justifier et la documenter
- **Analyse de complexité** : évaluation des algorithmes en ordre de grandeur pour chaque méthode publique
- **Partitionnement d'image / composantes connexes** : algorithmique de parcours sur une grille de pixels
- **Modélisation d'un système dynamique** : simulation d'un phénomène évoluant dans le temps avec des règles de propagation et d'extinction
- **Développement C++ rigoureux** : code commenté, indenté, découpé en méthodes élémentaires, compilation sans warning
- **Méthodologie de développement** : réflexion avant codage, tests progressifs, usage d'assertions pour vérifier les préconditions
- **Travail collaboratif** : organisation en binôme avec un dépôt Git partagé
