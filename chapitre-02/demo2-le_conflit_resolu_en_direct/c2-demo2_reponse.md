# Démo 2 : Provoquer et résoudre un conflit

## 1. Provoquer le conflit

Deux branches modifient **la même ligne** du même fichier (`salut.txt`). Git ne peut pas choisir seul, il s'arrête et me demande de trancher.

Commandes tapées, dans l'ordre :

```bash
git commit -am "version de la branche"     (sur ma-branche)
git switch main
echo salut tout le monde > salut.txt
git commit -am "version du main"           (sur main)
git merge ma-branche
```

Résultat des deux commits :

```bash
[ma-branche 15c93c3] version de la branche
 1 file changed, 1 insertion(+), 1 deletion(-)

[main de9263b] version du main
 1 file changed, 1 insertion(+), 1 deletion(-)
```

Sortie du `git merge ma-branche` :

```bash
Auto-merging salut.txt
CONFLICT (content): Merge conflict in salut.txt
Automatic merge failed; fix conflicts and then commit the result.
```

Git m'annonce le conflit et laisse la fusion en cours : rien n'est perdu, c'est à moi de terminer.

## 2 Lecture des marqueurs

J'ai ouvert le dossier dans VS Code avec `code .`. Dans `salut.txt`, Git a écrit les deux versions séparées par des marqueurs :

```
<<<<<<< HEAD
salut tout le monde
=======
bonjour la classe
>>>>>>> ma-branche
```

- `<<<<<<< HEAD` : début de **ma version**, celle de `main`, la branche sur laquelle j'étais. Ici : `salut tout le monde`.
- `=======` : séparateur entre les deux versions.
- `>>>>>>> ma-branche` : fin de la version de **l'autre branche**.

## 3 Reconstruction

Dans VS Code, j'ai choisi le contenu final et **supprimé les trois lignes de marqueurs** (`<<<<<<<`, `=======`, `>>>>>>>`), puis enregistré.

Contenu final de `salut.txt` :

```bash
HEAD
salut tout le monde 

bonjour la classe 
ma-branche
```

## 4 Validation
```bash
git add salut.txt
git commit -m "fusion de ma branche"
git log --oneline --graph
git status
```
Le commit de fusion :

```bash
[main 2ae401c] fusion de ma branche
```
Historique :

```bash
*   2ae401c (HEAD -> main) fusion de ma branche
|\
| * 15c93c3 (ma-branche) version de la branche
* | de9263b version du main
|/
* afe1d25 base
```

État du dépôt :

```bash
On branch main
nothing to commit, working tree clean
```

Vérifications :
- Le graphe montre un commit de fusion (`2ae401c`) à **deux parents** : `de9263b` (main) et `15c93c3` (ma-branche). Le `|\` sous la fusion et le `|/` au-dessus de `base` montrent la divergence puis la fusion.
- `git status` est propre : le conflit est bien résolu et il n'y a plus rien en attente.
- Plus aucun marqueur dans le fichier.

## 5 Ce que j'ai retenu

- Un conflit arrive quand deux branches modifient la même ligne : Git ne devine pas, il demande à l'humain de décider.
- Un conflit n'est pas une erreur grave. La fusion reste en attente, aucune donnée n'est perdue, et on la termine en quatre gestes : lire, décider, reconstruire, valider.
- Pour rester calme : lire les marqueurs sans se presser, ne supprimer qu'après avoir décidé, puis vérifier avec `git status` et `git log --graph`.

# Preuve
```bash
C:\Users\Administrator> mkdir demo2

C:\Users\Administrator> cd demo2

C:\Users\Administrator\demo2> git init -b main
Initialized empty Git repository in C:/Users/Administrator/demo2/.git/

C:\Users\Administrator\demo2> echo bonjour le monde > salut.txt

C:\Users\Administrator\demo2> git add .

C:\Users\Administrator\demo2> git commit -m "base"
[main (root-commit) afe1d25] base
 1 file changed, 1 insertion(+)
 create mode 100644 salut.txt

C:\Users\Administrator\demo2> git switch -c ma-branche
Switched to a new branch 'ma-branche'

C:\Users\Administrator\demo2> echo bonjour la classe > salut.txt

C:\Users\Administrator\demo2> git commit -am "version de la branche"
[ma-branche 15c93c3] version de la branche
 1 file changed, 1 insertion(+), 1 deletion(-)

C:\Users\Administrator\demo2> git switch main
Switched to branch 'main'

C:\Users\Administrator\demo2> echo salut tout le monde > salut.txt

C:\Users\Administrator\demo2> git commit -am "version du main"
[main de9263b] version du main
 1 file changed, 1 insertion(+), 1 deletion(-)

C:\Users\Administrator\demo2> git merge ma-branche
Auto-merging salut.txt
CONFLICT (content): Merge conflict in salut.txt
Automatic merge failed; fix conflicts and then commit the result.

C:\Users\Administrator\demo2> code .

C:\Users\Administrator\demo2> git add salut.txt

C:\Users\Administrator\demo2> git commit -m "fusion de ma branche"
[main 2ae401c] fusion de ma branche

C:\Users\Administrator\demo2> git log --oneline --graph
*   2ae401c (HEAD -> main) fusion de ma branche
|\
| * 15c93c3 (ma-branche) version de la branche
* | de9263b version du main
|/
* afe1d25 base

C:\Users\Administrator\demo2> git status
On branch main
nothing to commit, working tree clean
```
