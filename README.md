# S102


# Programme de Manipulation d'Images en C++

# Description

Un programme en C++ permetttant la manipulation d'images, au format PPM.

# Fonctionnalités supportées :

- Afficher
- Composante rouge
- Niveaux de gris
- Vision deuteranopie
- Vision protanopie
- Vision tritanopie
- Noir et blanc
- Histogramme gris
- Histogramme couleur
- Luminosity up
- Luminosity down
- Contraste up
- Contraste down
- Reglage auto
- Enregistrer
- Annuler modification
- Rogner droite
- Rogner gauche
- Rogner haut
- Rogner bas
- Rotation droite
- Rotation gauche
- Retournement horizontal
- Retournement vertical
- Aggrandissement
- Retrecissement
- Quitter

Pour utiliser la fonction display, il est recommandé d'utiliser un terminal Bash (Replit fonctionne bien)

## Utilisation
1. **Chargement d'une Image**
   - Utilisez le constructeur `Image` pour charger une image à partir d'un fichier PPM.

2. **Affichage des Valeurs de l'Image**
   - La méthode `displayValues()` affiche les valeurs RGB de chaque pixel de l'image.

3. **Affichage de l'Image en Couleurs**
   - La méthode `display()` affiche l'image en couleurs dans la console. Si l'image est trop grande, elle offre la possibilité de continuer ou d'arrêter l'affichage.

4. **Opérations de Transformation des Couleurs**
   - Plusieurs méthodes sont disponibles pour transformer l'image, notamment :
     - `composanteRouge()` : Obtenir l'image avec la composante rouge seule.
     - `niveauxGris()` : Convertir l'image en niveaux de gris.
     - `visionDeuteranopie()`, `visionTritanopie()`, `visionProtanopie()` : Simuler différentes formes de daltonisme.
     - `noirEtBlanc(int seuil)` : Convertir l'image en noir et blanc en fonction d'un seuil.

5. **Opérations sur les Histogrammes**
   - `histogrammeGris()` : Calculer l'histogramme des niveaux de gris.
   - `histogrammeCouleur()` : Calculer l'histogramme des couleurs RGB.

6. **Ajustement de Luminosité et Contraste**
   - Plusieurs méthodes sont fournies pour ajuster la luminosité et le contraste de l'image :
     - `luminosityUp(float luminosityfactor)`, `luminosityDown(float luminosityfactor)`.
     - `contrasteUp(float contrasteFactor)`, `contrasteDown(float contrasteFactor)`.

7. **Réglages Automatiques**
   - La méthode `reglageAuto()` effectue un réglage automatique de l'image en fonction de ses statistiques.

8. **Opérations de Rognage**
   - Plusieurs méthodes de rognage sont disponibles :
     - `rognerD(int nb)`, `rognerG(int nb)`, `rognerH(int nb)`, `rognerB(int nb)`.

9. **Opérations de Rotation**
   - Deux méthodes de rotation sont disponibles :
     - `rotationD()` : Rotation de 90 degrés dans le sens des aiguilles d'une montre.
     - `rotationG()` : Rotation de 90 degrés dans le sens inverse des aiguilles d'une montre.

10. **Opérations de Retournement**
    - Deux méthodes de retournement sont disponibles :
      - `retournementH()` : Retournement horizontal de l'image.
      - `retournementV()` : Retournement vertical de l'image.

11. **Redimensionnement de l'Image**
    - Deux méthodes de redimensionnement sont fournies :
      - `aggrandissement(int facteur)` : Augmente la taille de l'image.
      - `retrecissement(int facteur)` : Diminue la taille de l'image.

12. **Sauvegarde de l'Image Modifiée**
    - La méthode `saveImage()` permet de sauvegarder l'image modifiée dans un fichier PPM.

## Instructions d'Exécution
1. Compilez le programme en utilisant un compilateur C++ : 
   g++ *.cpp *.h
2. Exécutez le programme puis fournissez le nom d'un fichier PPM valide : 
   ./a.out
3. Il est conseillé d'utiliser le fichier imageDeTest.ppm pour tester le programme
