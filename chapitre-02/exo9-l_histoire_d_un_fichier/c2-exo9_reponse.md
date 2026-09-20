# Histoire de NkRectangle.cpp

**Fichier étudié :** `Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp`
**Dépôt :** Nkentseu

## Méthode

Pour reconstituer l'histoire de ce fichier, les commandes suivantes ont été utilisées :git log --follow --oneline -- Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp
git log --follow --diff-filter=A --oneline -- Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp
git log --follow --oneline --stat -- Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp
git log -1 --format=%B
`--follow` permet de suivre le fichier même s'il a été renommé ou déplacé au fil du
temps. `--diff-filter=A` isole le commit où le fichier a été ajouté pour la première
fois. `--stat` donne, pour chaque commit, le nombre de lignes ajoutées et supprimées,
ce qui permet de repérer objectivement les changements les plus importants sans lire
tout le code.

## Création du fichier

PS C:\Nkentseu> git log --follow --oneline --stat -- Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp 
bdda350a style: reformatage clang-format repo-wide (Kernel/Engine/Applications)
 .../Foundation/NKMath/src/NKMath/NkRectangle.cpp   | 686 ++++++++++-----------
 1 file changed, 317 insertions(+), 369 deletions(-)
d557314e update
 {Modules => Kernel}/Foundation/NKMath/src/NKMath/NkRectangle.cpp | 0
 1 file changed, 0 insertions(+), 0 deletions(-)
f1e536a5 refactor 001
 .../Foundation/NKMath/src/NKMath/NkRectangle.cpp   | 492 ++++++++++++++++-----
 1 file changed, 391 insertions(+), 101 deletions(-)
9c49f79f bug fix vulkan opengl dx11 current bug software and dx12
 .../Foundation/NKMath/src/NKMath/NkRectangle.cpp   | 108 +++++++++++++++++++++
 1 file changed, 108 insertions(+)
`--follow` permet de suivre le fichier même s'il a été renommé ou déplacé au fil du
temps. `--diff-filter=A` isole le commit où le fichier a été ajouté pour la première
fois. `--stat` donne, pour chaque commit, le nombre de lignes ajoutées et supprimées.

Le fichier n'a connu que 4 commits au total depuis sa création, ce qui permet une
analyse exhaustive de son histoire plutôt qu'une simple sélection des plus gros
changements parmi beaucoup.

## Création du fichier

- **Commit :** `9c49f79f`
- **Message :** "bug fix vulkan opengl dx11 current bug software and dx12"
- **Lignes ajoutées :** +108 (création complète du fichier)

**Résumé :** Le fichier `NkRectangle.cpp` a été créé dans le cadre d'une série de
corrections de bugs touchant le rendu multi-backend du moteur (Vulkan, OpenGL, DX11,
rendu logiciel et DX12). Le message, bien que peu descriptif sur le contenu précis du
fichier, indique qu'il est né dans un contexte de stabilisation du pipeline de rendu
graphique, où une structure de rectangle a probablement été nécessaire pour gérer des
zones (viewport, clipping, etc.) de manière cohérente entre les différents backends.

## Les trois moments de l'histoire du fichier

Le fichier n'ayant que 4 commits, les 3 moments les plus significatifs couvrent la
quasi-totalité de son histoire (le 4e commit étant un simple déplacement sans
changement de contenu).

[ PREUVE 3 : capture de git log --follow --oneline --stat -- ...NkRectangle.cpp ]

### 1. Création — `9c49f79f`

Lignes modifiées : **+108 / -0**

**Message :** "bug fix vulkan opengl dx11 current bug software and dx12"

**Raison :** Naissance du fichier dans le cadre d'un correctif touchant simultanément
plusieurs backends de rendu. Le rectangle a probablement été introduit comme structure
utilitaire commune pour uniformiser un comportement bugué entre les API graphiques.

### 2. Refonte — `f1e536a5`

Lignes modifiées : **+391 / -101** (492 lignes touchées au total)

**Message :** "refactor 001"

**Raison :** Il s'agit du changement le plus profond en volume net (le fichier a
presque quadruplé en ajouts nets : +290 lignes). Le message "refactor 001" suggère une
restructuration organisée du code, probablement la première d'une série de refontes
planifiées, mais sans détail sur la motivation précise — ce qui est une faiblesse du
message au regard des bonnes pratiques (il dit "quoi" de façon vague, mais pas "pourquoi").

### 3. Reformatage global — `bdda350a`

Lignes modifiées : **+317 / -369** (686 lignes touchées au total, le plus gros volume brut)

**Message :** "style: reformatage clang-format repo-wide (Kernel/Engine/Applications) —
Applique le .clang-format maison a tout l'arbre source C++ : indentation par namespace,
public/private/protected indentes sous class, une ligne vide entre definitions, une
instruction par ligne, accolades attachees, tabs. 1748 fichiers (.h/.cpp/.inl/.mm).
Verifie : NKGptTrain 25/25 et renderdemo 28/28 buildent OK apres reformatage."

**Raison :** Ce n'est pas un changement fonctionnel mais une uniformisation stylistique
automatique appliquée à tout le dépôt (1748 fichiers en une seule fois) via
clang-format. `NkRectangle.cpp` a été touché non pas pour lui-même, mais parce qu'il
faisait partie de l'arbre source C++ entier. C'est le commit le plus volumineux en
nombre de lignes touchées, mais le moins significatif en termes de contenu réel : le
message précise explicitement qu'une vérification de compilation (25/25 et 28/28
projets) a été faite après coup, preuve du soin apporté malgré l'ampleur du changement.

## Le commit écarté : le renommage

Un cinquième événement mérite d'être mentionné même s'il ne représente aucun changement
de contenu :

- **Commit :** `d557314e` — message : "update"
- **Changement :** 0 insertion(s), 0 suppression(s) — le fichier a simplement été
  déplacé de `Modules/Foundation/NKMath/...` vers `Kernel/Foundation/NKMath/...`

Ce commit illustre une réorganisation architecturale du dépôt (le dossier `Modules` a
été renommé ou restructuré en `Kernel`), sans toucher au code du fichier lui-même.
Le message "update" est cependant peu informatif sur la nature réelle du changement
(un simple renommage de dossier), ce qui est un contre-exemple de bon message de commit.

## Synthèse

L'histoire de `NkRectangle.cpp` suit un schéma clair en trois temps : il naît (`9c49f79f`)
comme sous-produit d'une correction de bugs cross-API touchant le rendu graphique,
ce qui explique pourquoi son message de création ne le nomme pas explicitement.
Il traverse ensuite une réorganisation de dossier sans impact sur son contenu
(`d557314e`), signe d'une restructuration plus large de l'arborescence du moteur.
Il connaît sa vraie croissance fonctionnelle avec `f1e536a5` ("refactor 001"), où son
volume de code presque quadruple — probablement l'ajout de méthodes et de logique
propres à la manipulation de rectangles. Enfin, il subit comme tout le reste du dépôt
un reformatage automatique massif (`bdda350a`), qui ne change rien à sa logique mais
à sa présentation.

On observe aussi une tendance dans la qualité des messages : le message le plus
détaillé et le plus utile est celui du reformatage automatique (`bdda350a`), qui
explique précisément quoi, pourquoi et comment la vérification a été faite — à
l'inverse des messages "refactor 001" et "update", trop vagues pour comprendre sans
lire le diff ce qui a réellement changé dans le fichier.
## Preuve
```bash
PS C:\Nkentseu> git log --follow --oneline -- Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp        
bdda350a style: reformatage clang-format repo-wide (Kernel/Engine/Applications)
d557314e update
f1e536a5 refactor 001
9c49f79f bug fix vulkan opengl dx11 current bug software and dx12
PS C:\Nkentseu> git log --follow --diff-filter=A --oneline -- Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp
9c49f79f bug fix vulkan opengl dx11 current bug software and dx12
PS C:\Nkentseu> git log --follow --oneline --stat -- Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp 
bdda350a style: reformatage clang-format repo-wide (Kernel/Engine/Applications)
 .../Foundation/NKMath/src/NKMath/NkRectangle.cpp   | 686 ++++++++++-----------
 1 file changed, 317 insertions(+), 369 deletions(-)
d557314e update
 {Modules => Kernel}/Foundation/NKMath/src/NKMath/NkRectangle.cpp | 0
 1 file changed, 0 insertions(+), 0 deletions(-)
f1e536a5 refactor 001
 .../Foundation/NKMath/src/NKMath/NkRectangle.cpp   | 492 ++++++++++++++++-----
 1 file changed, 391 insertions(+), 101 deletions(-)
9c49f79f bug fix vulkan opengl dx11 current bug software and dx12
 .../Foundation/NKMath/src/NKMath/NkRectangle.cpp   | 108 +++++++++++++++++++++
 1 file changed, 108 insertions(+)
PS C:\Nkentseu> git log -1 --format=%B bdda350a                                                          
style: reformatage clang-format repo-wide (Kernel/Engine/Applications)

Applique le .clang-format maison a tout l'arbre source C++ :
- indentation par namespace (NamespaceIndentation: All)
- public/private/protected indentes sous class (IndentAccessModifiers)
- une ligne vide entre definitions (SeparateDefinitionBlocks)
- une instruction par ligne, accolades attachees, tabs

1748 fichiers (.h/.cpp/.inl/.mm). Verifie : NKGptTrain 25/25 et renderdemo 28/28 buildent OK apres reformatage.

PS C:\Nkentseu> git log -1 --format=%B f1e536a5
refactor 001

PS C:\Nkentseu> git log -1 --format=%B 9c49f79f
bug fix vulkan opengl dx11 current bug software and dx12
```