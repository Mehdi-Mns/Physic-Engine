# Physics Engine

## Présentation du projet

Physics Engine est un moteur physique 3D développé **from scratch** en C++ pour simuler les interactions de particules et objets dans un environnement 3D, à la manière des jeux vidéo ou simulateurs physiques.  

Le moteur permet de gérer :

- Les positions, vitesses et accélérations des objets, avec mise à jour à chaque cycle de simulation (tick).  
- Des forces variées : gravité, attraction/répulsion entre particules, collisions dans un espace limité et forces de ressort entre objets.  
- La simulation de mouvements et interactions complexes entre plusieurs objets en temps réel.  
- L’intégration graphique simple avec OpenGL pour visualiser les particules et leurs interactions via FreeGLUT, GLU, GLM et des objets personnalisés.

Le projet inclut également un système de forces modulable (drag, magnétisme, ressorts fixes ou entre particules) et un rendu OpenGL de base pour les visualiser.

---

## Fonctionnalités principales

- Moteur physique 3D entièrement personnalisé en C++.  
- Gestion des collisions simples et des bounding boxes (AABB).  
- Forces : gravité, magnétisme fixe ou dynamique, drag, ressorts entre particules ou vers des points fixes.  
- Support du rendu graphique en OpenGL (FreeGLUT, GLEW).  
- Gestion interactive via la souris et le clavier pour manipuler les particules et la caméra.  
- Différents scénarios de démonstration : particules aléatoires, magnétisme, ressorts/tetraèdres, collisions dans un espace limité.

---

## Prérequis

- **Visual Studio 2022** (le projet a été initialement développé sous VS2019, mais fonctionne sous VS2022).  
- **Windows 10 ou 11**.  
- Bibliothèques incluses dans le dépôt :  
  - **FreeGLUT**  
  - **GLM**  
  - **GLEW** (si nécessaire)  
- Les fichiers DLL nécessaires doivent être placés dans **C:\Windows\System32** ou ajoutés au **PATH**.

---

## Installation et compilation

1. **Cloner le dépôt**  
   ```bash
   git clone <URL_DU_DEPOT>
   ```

2. **Ouvrir la solution dans Visual Studio**  
   - Double-cliquez sur `Physic Engine.sln` pour ouvrir la solution dans Visual Studio 2022.

3. **Vérifier les dépendances**  
   - Les bibliothèques FreeGLUT, GLM et GLEW sont incluses dans le dossier `External Libraries/`.  
   - Dans Visual Studio, faites un clic droit sur le projet → **Propriétés** → **VC++ Directories** :  
     - **Include Directories** : pour chaque lib, ajoutez le chemin vers `External Libraries/include`.  
     - **Library Directories** : pour chaque lib, ajoutez le chemin vers `External Libraries/lib`.  
   - Dans **Linker → Input → Additional Dependencies**, ajoutez les fichiers `.lib` nécessaires dans la bonne configuration :  
     - `freeglut.lib`  
     - `glew32.lib`

4. **DLL**  
   - Copiez les fichiers `*.dll` requis dans :  
     - `C:\Windows\System32`  
     - **ou** dans le dossier contenant l’exécutable généré (`Debug/` ou `Release/`).  
   - Par exemple : `freeglut.dll`, `glew32.dll`.

5. **Compiler et exécuter**  
   - Sélectionnez **Debug** ou **Release** et compilez le projet.  
   - Exécutez `Physics-engine.exe` depuis Visual Studio ou le dossier `Debug/`.

---

## Contrôles clavier et souris

**Clavier :**  

- `1 → 4` : changer de scène de démonstration  
- `Espace` : pause / reprise  
- `g` : activer / désactiver la gravité  
- `u` : activer / désactiver la suppression de particules  
- `f` : créer une fontaine de particules (dans la scène 1)  
- `p` : créer des particules avec drag (dans la scène 1)  
- `m` : changer la charge de la particule centrale (dans la scène 2)  
- `a/d/D` : ajuster le damping  
- `k/K` : ajuster la raideur des ressorts (dans la scène 3)  
- `e` : changer le type d’intégration (Euler / semi-implicite)  
- `c` : activer / désactiver les collisions  

**Souris :**  

- Clic gauche + drag : rotation de la caméra  
- Clic droit + drag : déplacement de la particule centrale (dans certaines scènes)

---

## Structure du projet

- **Quantum/** : moteur physique, classes de particules, forces et gestion du monde.  
- **App/** : interface graphique et utilitaires OpenGL (GxWorld, GxParticle, GxUpdater).  
- **External Libraries/** : bibliothèques externes (FreeGLUT, GLM, GLU…).  
- **Physics-engine.cpp** : point d’entrée, création des scènes et logique OpenGL.  

---

## Exemple de scène

- **Scene 1** : particules aléatoires avec gravité et collisions simples.  
- **Scene 2** : particules avec magnétisme et particule centrale manipulable.  
- **Scene 3** : systèmes de ressorts et structures tétraédriques.  
- **Scene 4** : collisions avec boîte limitée.

---

## Notes

- Le moteur physique est **flexible et extensible**.  
- La séparation entre physique (`QmWorld`) et rendu (`GxWorld`) permet d’ajouter facilement de nouveaux types de forces ou de particules.  
- Pour déboguer, assurez-vous que les DLL sont accessibles et que les chemins d’includes et libs sont corrects.
- Certaines fonctionnalités n'ont pas été entierement finies comme la collision dans la box.

## Licence
- Projet pedagogique – usage libre pour consultation, tests et apprentissage.