# Démo 3 : Détruire un travail avec `reset --hard`, puis le retrouver avec le reflog

## 1. Préparer un travail à détruire

Je crée un dépôt avec un commit de base, puis un commit « Travail important » que je vais détruire.

```bash
C:\Users\Administrator> mkdir demo3

C:\Users\Administrator> cd demo3

C:\Users\Administrator\demo3> git init -b main
Initialized empty Git repository in C:/Users/Administrator/demo3/.git/

C:\Users\Administrator\demo3> echo version1 > travail.txt

C:\Users\Administrator\demo3>git add .

C:\Users\Administrator\demo3> git commit -m "base"
[main (root-commit) 99726d3] base
 1 file changed, 1 insertion(+)
 create mode 100644 travail.txt

C:\Users\Administrator\demo3> echo travail important > important.txt

C:\Users\Administrator\demo3> git add .

C:\Users\Administrator\demo3> git commit -m "travail important"
[main d1a653b] travail important
 1 file changed, 1 insertion(+)
 create mode 100644 important.txt

```

Historique avant la destruction (`git log --oneline`) :

```bash
C:\Users\Administrator\demo3>git log --oneline
d1a653b (HEAD -> main) travail important
99726d3 base
```

## 2. Détruire volontairement

```bash
git reset --hard HEAD~1
```
`--hard` déplace la branche vers le commit précédent **et** remet le dossier de travail dans cet état : le fichier du commit détruit disparaît aussi du disque.

## 3. Constater la perte

```
git log --oneline
dir
```

```bash
C:\Users\Administrator\demo3> git reset --hard HEAD~1
HEAD is now at 99726d3 base
```
Le travail n'est plus visible dans l'historique et le fichier n'est plus dans le dossier.

## 4. Retrouver le travail avec le reflog

```bash
git reflog
```
```bash
 C:\Users\Administrator\demo3> git reflog
99726d3 (HEAD -> main) HEAD@{0}: reset: moving to HEAD~1
d1a653b HEAD@{1}: commit: travail important
99726d3 (HEAD -> main) HEAD@{2}: commit (initial): base
```

Le reflog est le journal de tous les déplacements de `HEAD` sur ma machine. Le commit n'a pas été supprimé : il n'est simplement plus atteint par aucune branche, mais Git l'a gardé et le reflog en donne l'adresse.

## 5. Restaurer

```bash
git reset --hard <hash-du-commit-retrouvé>
```
Vérification :

```bash
git log --oneline
git reflog
```


## 6. Ce que j'ai retenu

- `git reset --hard` semble tout détruire, mais tant que le travail a été **commité**, il reste récupérable via `git reflog`.
- Le reflog est local (propre à ma machine) et n'est pas conservé indéfiniment : les entrées expirent après un certain temps (90 jours par défaut pour les commits encore atteignables, 30 jours pour les autres) et sont nettoyées par `git gc`.
- **Limite importante** : les modifications **jamais commitées** sont perdues pour de bon avec `reset --hard`. Le reflog ne sauve que ce qui a été commité.
- Bonne pratique : commiter (ou `git stash`) avant toute opération risquée.

# Preuve
```bash
C:\Users\Administrator> mkdir demo3

C:\Users\Administrator> cd demo3

C:\Users\Administrator\demo3> git init -b main
Initialized empty Git repository in C:/Users/Administrator/demo3/.git/

C:\Users\Administrator\demo3> echo version1 > travail.txt

C:\Users\Administrator\demo3>git add .

C:\Users\Administrator\demo3> git commit -m "base"
[main (root-commit) 99726d3] base
 1 file changed, 1 insertion(+)
 create mode 100644 travail.txt

C:\Users\Administrator\demo3> echo travail important > important.txt

C:\Users\Administrator\demo3> git add .

C:\Users\Administrator\demo3> git commit -m "travail important"
[main d1a653b] travail important
 1 file changed, 1 insertion(+)
 create mode 100644 important.txt

C:\Users\Administrator\demo3>git log --oneline
d1a653b (HEAD -> main) travail important
99726d3 base

C:\Users\Administrator\demo3> git reset --hard HEAD~1
HEAD is now at 99726d3 base

C:\Users\Administrator\demo3>git log --oneline
99726d3 (HEAD -> main) base

C:\Users\Administrator\demo3> git reflog
99726d3 (HEAD -> main) HEAD@{0}: reset: moving to HEAD~1
d1a653b HEAD@{1}: commit: travail important
99726d3 (HEAD -> main) HEAD@{2}: commit (initial): base

C:\Users\Administrator\demo3> git reset --hard d1a653b
HEAD is now at d1a653b travail important

C:\Users\Administrator\demo3>git log --oneline
d1a653b (HEAD -> main) travail important
99726d3 base

```