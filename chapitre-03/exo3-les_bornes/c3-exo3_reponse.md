# Exercice — Les bornes

## Objectif
Fixer une taille minimale de fenêtre, essayer de la réduire en dessous, retirer
la contrainte et recommencer, pour noter la plus petite taille que le système
accepte réellement dans chaque cas.

## Méthode

Le code déclare la fenêtre avec :
```cpp
cfg.width  = 800;
cfg.height = 600;
```
et affiche la taille au démarrage, puis à chaque événement `NkWindowResizeEvent`
pendant que la fenêtre est réduite manuellement à la souris :
```cpp
math::NkVec2T size = window.GetSize();
std::cout << "\nla taille : (" << size.height << "H, " << size.width << "W)";
```

## Observation préliminaire — écart entre taille programmée et taille réelle

**La taille indiquée dans le code (`cfg.width = 800`, `cfg.height = 600`) ne
correspond pas à la taille annoncée par `window.GetSize()` au démarrage** :

- Code : 800 (largeur) x 600 (hauteur)
- Terminal, au démarrage ("au depart") : **794 (largeur) x 583 (hauteur)**

L'écart (environ 6 px en largeur, 17 px en hauteur) correspond très probablement
à la différence entre la **taille totale de la fenêtre** (ce que `cfg.width` /
`cfg.height` configurent, bordures et barre de titre comprises) et la **taille
de la zone client** (la surface utilisable à l'intérieur, sans les bordures ni
la barre de titre), que `GetSize()` semble renvoyer. La barre de titre de
Windows mesure environ 30 px, ce qui colle avec l'écart observé en hauteur.

## Test 1 — 

Configuration : `cfg.width = 800`, `cfg.height = 600`, `minWidth= 200`/`minHeight= 200`


```bash
la taille : (583H, 794W) au depart
la taille : (583H, 794W) redimensionn├⌐t
la taille : (583H, 910W) redimensionn├⌐t
la taille : (583H, 910W) redimensionn├⌐t
la taille : (583H, 910W) redimensionn├⌐t
```

Résultat : la hauteur et la largeur ont varie au cours de l'excution jusqu'a de stabiliser. La fenêtre s'est stabilisée à
**178(Largeur) x 144(Hauteur)** sans redescendre plus bas que sa hauteur de
départ lors de cet essai.

## Test 2 — nouvelle vérification du plancher minimal 


```bash
la taille : ( 144H , 178 W ) au depart
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
```

Résultat : la fenêtre n'a  pas été réduite et est rester a 
**178 (largeur) x 144 (hauteur)**, un plancher stable confirmé par la
répétition de la même valeur sur plusieurs événements de redimensionnement
consécutifs.

## Constat

- La taille réellement affichée par `GetSize()` au lancement diffère de la
  taille programmée dans `cfg` — probablement parce que l'une mesure la
  fenêtre entière (bordures incluses) et l'autre la zone client interne.
-Apres avoir tester, la fenêtre ne descend pas en dessous d'environ
  **178 x 144**.

  ## PREUVE
 ```bash
 la taille : (583H, 794W) au depart
la taille : (583H, 794W) redimensionn├⌐t
la taille : (583H, 910W) redimensionn├⌐t
la taille : (583H, 910W) redimensionn├⌐t
la taille : (583H, 910W) redimensionn├⌐t
 la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 567 W ) redimentionn├⌐t
la taille : ( 583H , 567 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 583H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 192 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
la taille : ( 144H , 178 W ) redimentionn├⌐t  
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (86.20s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (86.20s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (86.20s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (86.20s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\Administrator\Chute\FirstWindow>
PS C:\Users\Administrator\Chute\FirstWindow> jenga build

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Window [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Window                                                         Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Window\Window.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 1m6.2s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           1m6.3s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\Users\Administrator\Chute\FirstWindow> jenga r    

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Window.exe
     C:\Users\Administrator\Chute\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


la taille : ( 144H , 178 W ) au depart
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
la taille : ( 144H , 178 W ) redimentionn├⌐t
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (28.22s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━