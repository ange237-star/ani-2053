# EXERCICE 4: Affichez côte à côte la taille rendue par la fenêtre, celle rendue par la cible de rendu, et le facteur d'échelle. Si votre écran donne 1, trouvez un écran qui donne autre chose, ou changez le réglage d'échelle du système

## Objectif
Afficher côte à côte la taille rendue par la fenêtre, celle rendue par la cible
de rendu, et le facteur d'échelle DPI. Si l'écran donne un facteur de 1,
chercher un écran ou un réglage système qui donne une valeur différente.

## Code utilisé

```cpp
auto afficherComparaison = [&]() {
    auto size = window.GetSize();
    auto displaySize = window.GetDisplaySize();
    float32 scale = window.GetDpiScale();
    logger.Info(
        "Window: {}x{} | Display: {}x{} | DPI Scale: {}",
        size.x, size.y,
        displaySize.x, displaySize.y,
        scale
    );
};
```

Appelé une première fois au démarrage, puis à chaque redimensionnement de la
fenêtre (événement `NkWindowResizeEvent`).

## Résultat observé

```bash
[2026-09-26 21:54:31.633] [INF] [default] [main.cpp:40 in operator()] -> Window: 794x794 | Display: 794x794 | DPI Scale: 794
[2026-09-26 21:54:31.673] [INF] [default] [main.cpp:40 in operator()] -> Window: 794x794 | Display: 794x794 | DPI Scale: 794
[2026-09-26 21:54:50.364] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.364] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.365] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.366] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.366] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.366] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.367] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.367] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.367] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.368] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.368] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.368] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.369] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.369] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.369] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.369] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.369] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.370] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.370] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.370] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.370] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.371] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.371] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767
[2026-09-26 21:54:50.372] [INF] [default] [main.cpp:40 in operator()] -> Window: 767x767 | Display: 767x767 | DPI Scale: 767

```

Les trois valeurs (`Window`, `Display`, `DPI Scale`) affichent systématiquement
**le même nombre**, quelle que soit la valeur : ici `794`, alors qu'un facteur
d'échelle DPI de 794 n'a physiquement aucun sens (les valeurs réalistes sont
proches de 1.0, 1.25, 1.5, 2.0...).

**En réduisant la fenêtre à la souris**, la valeur affichée change bien  Par
exemple, une nouvelle taille de fenêtre entraîne le même nouveau nombre pour
`Window`, `Display` ET `DPI Scale` simultanément, parfois nonn(la taille de la fenêtre peut changer sans que l'échelle DPI change, et inversement).


## Constat

Il n'est pas possible, avec ce résultat, de savoir si l'écran utilisé a
réellement un facteur d'échelle de 1 ou une autre valeur : le chiffre observé
(`794`) ne correspond à aucune des trois grandeurs demandées, ce qui indique
un défaut d'affichage plutôt qu'une vraie mesure du système. 