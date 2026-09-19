# Creation d'une branche
  **Pour creer la branche j'ai tape la commande git branch experimentation**
  **Puis j'ai fait un git checkout experimentation**
  **Ensuite j'ai modifie mon fichier nomme fichier2 pou la premiere fois, j'ai sauvegarde et j'ai fait un git add fichier2, git commit -m "Premier commit sur la branche"**
  **J'ai fait deux autres modification et deux autres commit sur la branche**
**Preuve**
```
PS C:\Users\Administrator\document> git branch experimentation

PS C:\Users\Administrator\document> git checkout experimentation
M       fichier2
Switched to branch 'experimentation'
PS C:\Users\Administrator\document> git add fichier2
PS C:\Users\Administrator\document> git commit -m "Premier commit sur la branche"
[experimentation 1c801c0] Premier commit sur la branche
 1 file changed, 7 insertions(+)
PS C:\Users\Administrator\document> git add fichier2
PS C:\Users\Administrator\document> git commit -m "Deuxieme commit sur la branche" 
[experimentation 4712d27] Deuxieme commit sur la branche
 1 file changed, 3 insertions(+), 1 deletion(-)
PS C:\Users\Administrator\document> git add fichier2
PS C:\Users\Administrator\document> git commit -m "TRoisieme commit sur la branche"
[experimentation 2ce9bbb] TRoisieme commit sur la branche
 1 file changed, 2 insertions(+)
```
## La place que le dépôt a gagnée sur le disque
 **J'ai tape la commande suivante pour avoir la taille en otect: Get-ChildItem .git -Recurse | Measure-Object -property Length -sum**
 **Resultat**
 ```
 PS C:\Users\Administrator\document> Get-ChildItem .git -Recurse | Measure-Object -property Length -sum         
                                                                             

Count    : 54
Average  :
Sum      : 36388 
Maximum  :
Minimum  :
Property : Length
```
# La branche, mesurée

## Mesures
- Taille de .git sur `main` (avant les 3 commits) : 36 193 octets
- Taille de .git sur `experimentation` (après les 3 commits) : 36 388 octets
- Différence : 195 octets (~0,19 Ko)

## Explication

La création de la branche elle-même n'a pratiquement aucun coût en espace disque : 
une branche n'est qu'un pointeur, un petit fichier texte contenant un hash de commit, 
stocké dans .git/refs/heads/. Elle ne duplique ni le contenu du dépôt ni son historique.

L'augmentation observée (195 octets) provient uniquement des trois commits effectués 
sur la branche `experimentation` : chaque commit crée de nouveaux objets Git (blob du 
contenu modifié, arbre représentant l'état du répertoire, et objet commit contenant le 
message et le pointeur vers le commit parent). Ce sont ces objets qui occupent l'espace 
supplémentaire, pas la branche en tant que telle.

Le chiffre reste très faible ici car les modifications faites dans les 3 commits étaient 
de petits ajouts de texte. Sur un vrai projet avec des fichiers plus volumineux, l'écart 
serait proportionnellement plus important, mais le principe resterait le même : c'est le 
contenu des commits qui pèse, pas l'existence de la branche.

**Preuve**
```
PS C:\Users\Administrator\document> git checkout main
Already on 'main'
Your branch is ahead of 'origin/main' by 3 commits.
  (use "git push" to publish your local commits)
PS C:\Users\Administrator\document> Get-ChildItem .git -Recurse | Measure-Object -property Length -sum

Count    : 54
Average  :
Sum      : 36193
Maximum  :
Minimum  :
Property : Length



PS C:\Users\Administrator\document> git checkout experimentation                                               
Switched to branch 'experimentation'
PS C:\Users\Administrator\document> Get-ChildItem .git -Recurse | Measure-Object -property Length -sum


Count    : 54
Average  :
Sum      : 36388
Maximum  :
Minimum  :
Property : Length
```
## Historique des commits
```
PS C:\Users\Administrator\document> git log --oneline --all --graph
* 2ce9bbb (experimentation) TRoisieme commit sur la branche
* 4712d27 Deuxieme commit sur la branche
* 1c801c0 Premier commit sur la branche
* 0f57c23 (HEAD -> main) ajoute du titre au fichier1
* 43e244d ajoute du titre au fichier1
* f27d346 Modification du premier fichier
* b91e4ad (origin/main) Ajout du troisieme fichier
* 59101c6 Ajout du deuxieme fichier
```