# Exercice 8 : Six manières de défaire

Ce fichier présente la résolution des six situations courantes où il est nécessaire d'annuler ou de corriger des actions dans Git.

## 1. Une modification non voulue (répertoire de travail)

* **Situation :** Un fichier suivi a été modifié localement par erreur et la modification ne doit pas être conservée.
* **Provocation :**
  ```bash
  Apres avoir modifier et sauvegarder le fichier, taper
  git status
 ```

* **Annulation / Résolution :**
 ```bash
 git restore fichier1
```

**Vérification :**
```bash
git status
```

## 2. Un add de trop (index / stage)
* **Situation :** Un fichier a été ajouté à l'index avec git add, mais ne doit pas faire partie du prochain commit.

* **Provocation :**
```bash
Apres avoir effectuer une modification et sauvegarder
git add fichier1
git status
```
* **Annulation / Résolution :**
```bash
git reset fichier1
```
* **Vérification :**
```bash
git status
```
## 3. Un commit de trop (non poussé en local)
* **Situation :** Un commit a été créé localement mais ne devait pas l'être avant d'être envoyé sur le serveur.

* **Provocation :**
```bash
Apres avoir modifier et sauvegarder
git add fichier1
git commit -m "Commit par erreur"
git log --oneline -n 3
```
* **Annulation / Résolution :**
```bash
git reset --soft HEAD~1
```
* **Vérification :**
```bash
git log --oneline -n 3
git status
```

## 4. Un commit poussé qu'il faut annuler (déjà partagé)
* **Situation :** Un commit erroné a déjà été poussé sur le dépôt distant (push). Il ne faut pas réécrire l'historique partagé pour éviter de casser le travail des autres collaborateurs.

* **Provocation :**
```bash
Apres avoir modifier, 
git add fichier1
git commit -m "commit a annuler"
git push
```
* **Annulation / Résolution :**
```bash
git revert HEAD
git push
```
* **Vérification :**
```Bash
git log --oneline -n 3
```

## 5. Un travail en cours qu'il faut mettre de côté
* **Situation :** Des modifications sont en cours sur la branche actuelle, mais il faut interrompre le travail (par exemple pour corriger un bug urgent ailleurs) sans commiter du code incomplet.

* **Provocation :**
```bash
Apres avoir modifier et sauvegarder
```
```bash
# 1. Mettre les modifications de côté dans le remisage
git stash
git status
# 2. Récupérer et réappliquer le travail plus tard
git stash pop
```
* **Vérification :**

Après git stash : git status indique que le répertoire de travail est propre.

Après git stash pop : git status montre que les modifications "en cours" sont de nouveau restaurées dans le répertoire de travail et le remisage est vidé.

## 6. Un commit « perdu » à retrouver par le reflog
* **Situation :** Un git reset --hard a été exécuté par erreur, supprimant un ou plusieurs commits importants de la branche courante.

* **Provocation :**
```bash
Apres avoir modifier et sauvegarder
git add fichier1
git commit -m "Commit important"
git log --oneline -n 1
git reset --hard HEAD~1
git log --oneline -n 3
```
* **Récupération :**

```bash
# 1. Consulter l'historique de toutes les actions (reflog)
git reflog

# 2. Repérer l'empreinte du commit perdu (ex: HEAD@{1} ou son hash) et réinitialiser la branche dessus
git reset --hard HEAD@{1}
```
* **Vérification :**
```bash
git log --oneline -n 3
```
## Preuve
```bash
 PS C:\Users\Administrator\document> git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1

no changes added to commit (use "git add" and/or "git commit -a")
PS C:\Users\Administrator\document> git restore fichier1
PS C:\Users\Administrator\document> git status
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean

PS C:\Users\Administrator\document>  git add fichier1
PS C:\Users\Administrator\document> git status
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   fichier1

PS C:\Users\Administrator\document> git reset fichier1
Unstaged changes after reset:
M       fichier1
PS C:\Users\Administrator\document> git status        
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1

no changes added to commit (use "git add" and/or "git commit -a")

PS C:\Users\Administrator\document>  git add fichier1 
PS C:\Users\Administrator\document> git commit -m "commit par erreur"
[main c0019e1] commit par erreur
 1 file changed, 2 insertions(+), 2 deletions(-)
PS C:\Users\Administrator\document> git log --oneline -n 3 
c0019e1 (HEAD -> main) commit par erreur
4fdf003  Modifie le document
0f57c23 ajoute du titre au fichier1
PS C:\Users\Administrator\document> git reset --soft HEAD~1
PS C:\Users\Administrator\document> git log --oneline -n 3 
4fdf003 (HEAD -> main)  Modifie le document
0f57c23 ajoute du titre au fichier1
43e244d ajoute du titre au fichier1

PS C:\Users\Administrator\document>  git add fichier1
PS C:\Users\Administrator\document> git commit -m "commit important"
[main 596ea32] commit important
 1 file changed, 2 insertions(+), 2 deletions(-)
PS C:\Users\Administrator\document> git log --oneline -n 1
596ea32 (HEAD -> main) commit important
PS C:\Users\Administrator\document> git reset --hard HEAD~1
HEAD is now at a2e0063 commit a annuler
PS C:\Users\Administrator\document> git log --oneline -n 3
a2e0063 (HEAD -> main) commit a annuler
b6fc76b commit a annuler
6929895 commit a annuler
PS C:\Users\Administrator\document> git reflog             
a2e0063 (HEAD -> main) HEAD@{0}: reset: moving to HEAD~1
596ea32 HEAD@{1}: commit: commit important
a2e0063 (HEAD -> main) HEAD@{2}: reset: moving to HEAD
a2e0063 (HEAD -> main) HEAD@{3}: commit: commit a annuler
b6fc76b HEAD@{4}: commit: commit a annuler
6929895 HEAD@{5}: commit: commit a annuler
b2ab1c5 HEAD@{6}: pull: updating HEAD
b2ab1c5 HEAD@{7}: commit: commit a annuler
4fdf003 HEAD@{8}: reset: moving to HEAD~1
c0019e1 HEAD@{9}: commit: commit par erreur
4fdf003 HEAD@{10}: reset: moving to HEAD~1
9fc3f4b (origin/main, origin/HEAD) HEAD@{11}: commit: Modifie le haut du ficher1
4fdf003 HEAD@{12}: checkout: moving from main to main
4fdf003 HEAD@{13}: commit: Modifie le document
0f57c23 HEAD@{14}: checkout: moving from main to main
0f57c23 HEAD@{15}: checkout: moving from experimentation to main
63aa5e6 (experimentation) HEAD@{16}: commit: Modifie le document
2ce9bbb HEAD@{17}: checkout: moving from main to experimentation
0f57c23 HEAD@{18}: checkout: moving from main to main
0f57c23 HEAD@{19}: checkout: moving from experimentation to main
2ce9bbb HEAD@{20}: commit: TRoisieme commit sur la branche
PS C:\Users\Administrator\document> git reset --hard 596ea32
HEAD is now at 596ea32 commit important
PS C:\Users\Administrator\document> git log --oneline -n 3 
596ea32 (HEAD -> main) commit important
a2e0063 commit a annuler
b6fc76b commit a annuler
```