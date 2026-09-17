## Creation des fichiers
 ## Apres avoir creer mon depot sur github, j'ai clone ce depot et je l'ai ouvert avec VsCode 
   ## j'ai cree mon premier fichier dans vscode puis j'ai fait un git add fichier1, puis un git commit -m "Ajout du premier fichier", puis un git Push
 PS C:\Users\Administrator\document> git add fichier1
PS C:\Users\Administrator\document> git commit -m "Ajout du premier fichier"     
[main (root-commit) 0d95028] Ajout du premier fichier
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier1
PS C:\Users\Administrator\document> git push
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Writing objects: 100% (3/3), 223 bytes | 223.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
   ## Ajout du deuxiemme fichier 
   PS C:\Users\Administrator\document> git add fichier2
PS C:\Users\Administrator\document> git commit -m "Ajout du deuxieme fichier"
[main 59101c6] Ajout du deuxieme fichier
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier2
PS C:\Users\Administrator\document> git push        
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (2/2), 253 bytes | 253.00 KiB/s, done.
Total 2 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/ange237-star/document.git
   0d95028..59101c6  main -> main
  ## Ajout du troisieme fichier
  PS C:\Users\Administrator\document> git add fichier3
PS C:\Users\Administrator\document> git commit -m "Ajout du troisieme fichier"
[main b91e4ad] Ajout du troisieme fichier
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier3
PS C:\Users\Administrator\document> git push        
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (2/2), 255 bytes | 255.00 KiB/s, done.
Total 2 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/ange237-star/document.git
   59101c6..b91e4ad  main -> main

## Affichage en une ligne de commit
 ## apres avoir taper la commande git log --oneline
 PS C:\Users\Administrator\document> git log --oneline
b91e4ad (HEAD -> main, origin/main) Ajout du troisieme fichier
59101c6 Ajout du deuxieme fichier
0d95028 Ajout du premier fichier

## Affichage de l'historique en graphe
 ## Apres avoir taper la commande git log --oneline --graph --all
 PS C:\Users\Administrator\document> git log --oneline --graph --all
* b91e4ad (HEAD -> main, origin/main) Ajout du troisieme fichier
* 59101c6 Ajout du deuxieme fichier
* 0d95028 Ajout du premier fichier