# Depuis deux répertoires de travail, ou deux clones, modifiez la même ligne d'un même fichier et poussez l'un des deux. Provoquez le refus, puis le conflit, puis résolvez-le. Rendez chaque message affiché.

## Creation d'un deuxieme repertoire de travail
 **J'ai clone mon depot dans un autre dossier en local, en utilant la commande**
 ```
 git clone document document-clone2
 ```
 **Puis j'ai fait :**
 ```
 cd document-clone2
 git status
 git log --oneline -n 3
```
 **Apres cela j'ai constate que j'etais pas sur le main, j'ai fait donc**
```
 git checkout main 
 git pull
 ```
## Modificaton du fichier1 de document et document-clone2
 **Apres avoir echange le titre de document et taper:**
 ```
 git add fichier1
 git commit -m "Modifie le document"
 git push
 ```
 **Apres avoir modifier la meme ligne de document-clone2 mais de titre different et taper:**
 ```
 git add fichier1
 git commit -m "Modifie le document"
 git push
 ```
 **resultat du push**
 ```
 PS C:\Users\Administrator\document-clone2> git push
 To C:/Users/Administrator/document
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs to 'C:/Users/Administrator/document'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```
## Resolution du probleme
**J'ai tape la commande git pull dans document-clone2**
```
PS C:\Users\Administrator\document-clone2> git pull
remote: Enumerating objects: 10, done.
remote: Counting objects: 100% (9/9), done.
remote: Compressing objects: 100% (6/6), done.
remote: Total 6 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
Unpacking objects: 100% (6/6), 615 bytes | 1024 bytes/s, done.
From C:/Users/Administrator/document
   0f57c23..4fdf003  main            -> origin/main
   2ce9bbb..63aa5e6  experimentation -> origin/experimentation
Auto-merging fichier1
CONFLICT (content): Merge conflict in fichier1
Automatic merge failed; fix conflicts and then commit the result.
```
**Puis un message s'est affiche**
<<<<<<< HEAD
# Documentation du cours
=======
# Mes notes du projet personnel
>>>>>>> 4fdf0032e11b1ba01c0d88fa2647348d27f04a5f

**J'ai remplacer le titre documentation du cours du document-clone2 par le meme que document**

 ## Preuve1
```
 C:\Users\Administrator> git clone document document-clone2
Cloning into 'document-clone2'...
done.
C:\Users\Administrator\document-clone2> git log --oneline -n 3
2ce9bbb (HEAD -> experimentation, origin/experimentation, origin/HEAD) TRoisieme commit sur la branche
4712d27 Deuxieme commit sur la branche
1c801c0 Premier commit sur la branche

C:\Users\Administrator\document-clone2> git checkout main
branch 'main' set up to track 'origin/main'.
Switched to a new branch 'main'

C:\Users\Administrator\document-clone2> git status
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```
## Preuve2
```
PS C:\Users\Administrator\document> git checkout main
M       fichier1
Already on 'main'
Your branch is ahead of 'origin/main' by 3 commits.
  (use "git push" to publish your local commits)
PS C:\Users\Administrator\document> git add fichier1 
PS C:\Users\Administrator\document> git commit -m " Modifie le document"
[main 4fdf003]  Modifie le document
 1 file changed, 1 insertion(+), 1 deletion(-)
PS C:\Users\Administrator\document> git push
Enumerating objects: 14, done.
Counting objects: 100% (14/14), done.
Delta compression using up to 4 threads
Compressing objects: 100% (11/11), done.
Writing objects: 100% (12/12), 1.26 KiB | 53.00 KiB/s, done.
Total 12 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), done.
To https://github.com/ange237-star/document.git
   b91e4ad..4fdf003  main -> main
```
## Preuve3
```
PS C:\Users\Administrator\document-clone2> git add ficher1
fatal: pathspec 'ficher1' did not match any files
PS C:\Users\Administrator\document-clone2> git add fichier1
PS C:\Users\Administrator\document-clone2> git commit -m "Modifie le document-clone2"
[main b124bcf] Modifie le document-clone2
 1 file changed, 1 insertion(+), 1 deletion(-)
PS C:\Users\Administrator\document-clone2> git push
To C:/Users/Administrator/document
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs to 'C:/Users/Administrator/document'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
```