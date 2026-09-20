# Exercice — Fusionner ou rejouer

## Objectif
Réaliser la même intégration de deux manières différentes (fusion et rebase),
comparer les deux graphes d'historique obtenus, et dire lequel est préférable à lire.

## Mise en placemkdir depot_essai
```bash
cd depot_essai
git init
echo "Ligne de base" > fichier.txt
git add fichier.txt
git commit -m "commit initial"
git checkout -b feacture
echo "Ajout feacture 1" >> fichier.txt
git commit -am "Feacture - etape 1"
echo "Ajout feacture 2" >> fichier.txt
git commit -am "Feacture - etape 2"
git checkout master
echo "Correctif sur main" >> fichier.txt
git commit -am "Correctif sur main"
```

Deux clones ont ensuite été créés à partir de ce dépôt, pour tester les deux méthodes
d'intégration séparément sans qu'elles s'influencent :cd ..
```bash
git clone depot_essai depot_essai_merge
git clone depot_essai depot_essai_rebase## Intégration n°1 — par fusion (merge)cd depot_essai_merge
git checkout feacture
git checkout master
git merge feacture
git log --oneline --graph --all
```
## Integration par Fusion (merge)
```bash
cd depot_essai_merge
git checkout feacture
git checkout master
git merge feacture
git log --oneline --graph --all
```
**Resultat obtenu dans le terminal**
* 9d0f436 (HEAD -> master, origin/master, origin/HEAD) Correctif sur main
| * 2a40aaf (origin/feacture) Feacture - etape 2
| * 6e14f9a Feacture - etape 1
|/
* 23110f3 commit initial

## Integration: en rejouant(rebase)
```bash
cd depot_essai_rebase
git checkout feacture
git rebase master
```
**un conflit est survenu pendant le rebase, sur le second commit rejoue, car les deux branches modifaient la meme zone du fichier:**
Auto-merging fichier.txt
CONFLICT (content): Merge conflict in fichier.txt
error: could not apply 2a40aaf... Feacture - etape 2
**Resolution du conflit dans fichier.txt, puis :**
```bash
git add fichier.txt
git rebase --continue
```
```bash
git checkout master
git merge feacture
```
```bash
git log --oneline --graph --all
```
## Graphe final obtenu
feb5e58 (HEAD -> master, feacture) Feacture - etape 2
b3e43e5 Feacture - etape 1
9d0f436 (origin/master, origin/HEAD) Correctif sur main
| * 2a40aaf (origin/feacture) Feacture - etape 2
| * 6e14f9a Feacture - etape 1
|/
23110f3 commit initial

(Les anciens commits `2a40aaf` et `6e14f9a`, encore visibles via `origin/feacture`,
sont les commits originaux avant rejeu — ils ne font plus partie de l'historique actif
de `feacture`/`master`, qui pointent maintenant sur les nouveaux hash `b3e43e5` et
`feb5e58` créés par le rebase.)

## Comparaison des deux graphes

**Avec merge :** l'historique garde visible la fourche entre les deux branches, avec
un commit de fusion supplémentaire reliant les deux lignes. On voit clairement que le
travail a été fait en parallèle avant d'être réuni.

**Avec rebase :** l'historique final est une ligne droite unique et linéaire. Les
commits de `feacture` ont été réécrits (nouveaux hash `b3e43e5` et `feb5e58`) comme
s'ils avaient été faits directement après `Correctif sur main`. Aucune branche
n'est visible dans le résultat final, et le merge final n'a été qu'un simple
fast-forward sans commit de fusion.

Un point important observé pendant l'exercice : le rebase n'a pas évité le conflit —
il l'a simplement déplacé et traité commit par commit, un conflit apparaissant
précisément sur le second commit rejoué, là où le contenu se chevauchait avec
`Correctif sur main`.

## Quel graphe je préfère lire, et pourquoi

Je préfère le graphe obtenu par **rebase**, car il est immédiatement lisible du haut
en bas sans avoir à interpréter une fourche ni un commit de fusion : chaque ligne
représente un changement réel et unique, dans un ordre chronologique simple à suivre
avec `git log`. Le merge, bien qu'il conserve une trace plus fidèle du déroulement
réel du travail en parallèle, ajoute un commit "de service" (le commit de fusion) qui
n'apporte aucune information de contenu et complique légèrement la lecture linéaire
de l'historique.

## Explication

`merge` crée un nouveau commit à deux parents, préservant fidèlement l'historique réel :
on voit que deux lignes de travail distinctes ont existé avant de se rejoindre.
`rebase` réécrit l'historique en donnant l'illusion que le travail de la branche a été
fait après coup, en ligne droite — c'est plus lisible visuellement, mais cela masque
le fait que le travail a été fait en parallèle, et cela change les hash des commits
rejoués (ce qui est risqué sur une branche déjà partagée/poussée avec d'autres
personnes, car cela réécrit l'historique qu'elles pourraient déjà avoir récupéré).

Ce test a aussi montré que les deux méthodes peuvent produire un conflit à résoudre :
la différence n'est pas "l'une évite les conflits et l'autre non", mais plutôt la
forme finale de l'historique une fois l'intégration terminée.

## Preuve
```bash
C:\Users\Administrator> mkdir depot_essai

C:\Users\Administrator> cd depot_essai

C:\Users\Administrator\depot_essai> git init
Initialized empty Git repository in C:/Users/Administrator/depot_essai/.git/

C:\Users\Administrator\depot_essai> echo "Ligne de base" > fichier.txt

C:\Users\Administrator\depot_essai> git add fichier.txt

C:\Users\Administrator\depot_essai> git commit -m "commit initial"
[master (root-commit) 23110f3] commit initial
 1 file changed, 1 insertion(+)
 create mode 100644 fichier.txt

C:\Users\Administrator\depot_essai> git checkout -b feacture
Switched to a new branch 'feacture'

C:\Users\Administrator\depot_essai> echo "Ajout feacture 1" >> fichier.txt

C:\Users\Administrator\depot_essai> git commit -am "Feacture - etape 1"
[feacture 6e14f9a] Feacture - etape 1
 1 file changed, 1 insertion(+)

C:\Users\Administrator\depot_essai> echo "Ajout feacture 2" >> fichier.txt

C:\Users\Administrator\depot_essai> git commit -am "Feacture - etape 2"
[feacture 2a40aaf] Feacture - etape 2
 1 file changed, 1 insertion(+)

C:\Users\Administrator\depot_essai> git checkout main
error: pathspec 'main' did not match any file(s) known to git

C:\Users\Administrator\depot_essai> git branch
* feacture
  master

C:\Users\Administrator\depot_essai> git checkout master
Switched to branch 'master'

C:\Users\Administrator\depot_essai> echo "Correctif sur main" >> fichier.txt

C:\Users\Administrator\depot_essai> git commit -am "Correctif sur main"
[master 9d0f436] Correctif sur main
 1 file changed, 1 insertion(+)

C:\Users\Administrator\depot_essai> cd ..

C:\Users\Administrator> git clone depot_essai depot_essai_merge
Cloning into 'depot_essai_merge'...
done.

C:\Users\Administrator> cd depot_essai_merge

C:\Users\Administrator\depot_essai_merge> git checkout master
Already on 'master'
Your branch is up to date with 'origin/master'.

C:\Users\Administrator\depot_essai_merge> git merge feacture
merge: feacture - not something we can merge

Did you mean this?
        origin/feacture

C:\Users\Administrator\depot_essai_merge> git log --oneline --graph --all
* 9d0f436 (HEAD -> master, origin/master, origin/HEAD) Correctif sur main
| * 2a40aaf (origin/feacture) Feacture - etape 2
| * 6e14f9a Feacture - etape 1
|/
* 23110f3 commit initial

C:\Users\Administrator\depot_essai_merge> cd ..

C:\Users\Administrator> git clone depot_essai depot_essai_rebase
Cloning into 'depot_essai_rebase'...
done.

C:\Users\Administrator> cd depot_essai_rebase

C:\Users\Administrator\depot_essai_rebase> git checkout feacture
branch 'feacture' set up to track 'origin/feacture'.
Switched to a new branch 'feacture'

C:\Users\Administrator\depot_essai_rebase> git rebase master
Auto-merging fichier.txt
CONFLICT (content): Merge conflict in fichier.txt
error: could not apply 6e14f9a... Feacture - etape 1
hint: Resolve all conflicts manually, mark them as resolved with
hint: "git add/rm <conflicted_files>", then run "git rebase --continue".
hint: You can instead skip this commit: run "git rebase --skip".
hint: To abort and get back to the state before "git rebase", run "git rebase --abort".
hint: Disable this message with "git config set advice.mergeConflict false"
Could not apply 6e14f9a... # Feacture - etape 1

C:\Users\Administrator\depot_essai_rebase> git checkout master
fichier.txt: needs merge
error: you need to resolve your current index first

C:\Users\Administrator\depot_essai_rebase> git merge feacture
error: Merging is not possible because you have unmerged files.
hint: Fix them up in the work tree, and then use 'git add/rm <file>'
hint: as appropriate to mark resolution and make a commit.
fatal: Exiting because of an unresolved conflict.

C:\Users\Administrator\depot_essai_rebase> cd ..

C:\Users\Administrator> cd depot_essai

C:\Users\Administrator\depot_essai> git log --oneline --all --graph
* 9d0f436 (HEAD -> master) Correctif sur main
| * 2a40aaf (feacture) Feacture - etape 2
| * 6e14f9a Feacture - etape 1
|/
* 23110f3 commit initial

C:\Users\Administrator\depot_essai> cd ..

C:\Users\Administrator> cd depot_essai_rebase

C:\Users\Administrator\depot_essai_rebase> code fichier.txt

C:\Users\Administrator\depot_essai_rebase> git add fichier.txt

C:\Users\Administrator\depot_essai_rebase> git rebase --continue
[detached HEAD b3e43e5] Feacture - etape 1
 1 file changed, 4 insertions(+)
Auto-merging fichier.txt
CONFLICT (content): Merge conflict in fichier.txt
error: could not apply 2a40aaf... Feacture - etape 2
hint: Resolve all conflicts manually, mark them as resolved with
hint: "git add/rm <conflicted_files>", then run "git rebase --continue".
hint: You can instead skip this commit: run "git rebase --skip".
hint: To abort and get back to the state before "git rebase", run "git rebase --abort".
hint: Disable this message with "git config set advice.mergeConflict false"
Could not apply 2a40aaf... # Feacture - etape 2

C:\Users\Administrator\depot_essai_rebase> git add fichier.txt

C:\Users\Administrator\depot_essai_rebase> git rebase --continue
[detached HEAD feb5e58] Feacture - etape 2
 1 file changed, 4 insertions(+)
Successfully rebased and updated refs/heads/feacture.

C:\Users\Administrator\depot_essai_rebase> git checkout master
Switched to branch 'master'
Your branch is up to date with 'origin/master'.

C:\Users\Administrator\depot_essai_rebase> git merge feacture
Updating 9d0f436..feb5e58
Fast-forward
 fichier.txt | 8 ++++++++
 1 file changed, 8 insertions(+)

C:\Users\Administrator\depot_essai_rebase> git log --oneline --graph --all
* feb5e58 (HEAD -> master, feacture) Feacture - etape 2
* b3e43e5 Feacture - etape 1
* 9d0f436 (origin/master, origin/HEAD) Correctif sur main
| * 2a40aaf (origin/feacture) Feacture - etape 2
| * 6e14f9a Feacture - etape 1
|/
* 23110f3 commit initial
```