# Modification du fichier1 et affichage
 ## Apres avoir ecrire 3 ligne dans le fichier fichier1, et sauvegarder j'ai fait un git status puis un git add fichier1, ensuite git status, puis git commit -m "Modification du premier ficher" enfin un git status.

## Modification
 PS C:\Users\Administrator\document> git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1

no changes added to commit (use "git add" and/or "git commit -a")
## git add
PS C:\Users\Administrator\document> git add fichier1
PS C:\Users\Administrator\document> git status      
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   fichier1

## git commit
PS C:\Users\Administrator\document> git commit -m "Modification du premier fichier"
[main f27d346] Modification du premier fichier
 1 file changed, 3 insertions(+)
PS C:\Users\Administrator\document> git status
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean