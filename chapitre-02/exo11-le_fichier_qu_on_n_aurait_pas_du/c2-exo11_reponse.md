# Exo 11 : Le fichier qu'on n'aurait pas dû

## Énoncé

Committer volontairement un fichier de 10 Mo dans un dépôt d'essai, le retirer au commit suivant, mesurer la taille de `.git`, puis conclure.

## Commandes exécutées (Windows, cmd)

```bash
git init depot_essai
cd depot_essai
git add README.md
git commit -m "commit initial"
git count-objects -vH                      :: mesure 1

powershell -c "$b=New-Object byte[] 10485760; (New-Object Random).NextBytes($b); [IO.File]::WriteAllBytes('gros.bin',$b)"
git add gros.bin
git commit -m "Ajout volontaire d'un fichier de 10 Mo"

git rm gros.bin
git commit -m "Retrait de gros.bin"

git show HEAD~1:gros.bin > test.bin && dir test.bin   
del test.bin
git count-objects -vH                      
```

Le fichier `gros.bin` est généré avec des octets aléatoires : il est incompressible, donc Git ne peut pas le réduire.

## Mesures

| Étape | Objets (`count`) | Taille (`size`) |
|---|---|---|
| Après le commit initial (README seul) | 15 | 1,30 Kio |
| Après ajout puis retrait de `gros.bin` | 19 | 10,00 Mio |

Vérification : `git show HEAD~1:gros.bin > test.bin` recrée un fichier de **10 485 760 octets** (10 × 1024 × 1024), identique à l'original. Le fichier supprimé est donc toujours intact dans l'historique.

Entre les deux mesures, 4 objets ont été ajoutés : le contenu de `gros.bin`, un arbre et un commit pour l'ajout, puis un commit pour le retrait.

## Conclusion

- Supprimer un fichier dans un nouveau commit **ne réduit pas** la taille de `.git`. Elle est passée de 1,30 Kio à 10 Mio et y est restée après le retrait.
- Git conserve **tout l'historique**. Le fichier a disparu du dossier de travail, mais son contenu reste stocké dans le commit précédent et se récupère avec `git show HEAD~1:gros.bin`.
- Toute personne qui clone le dépôt télécharge ces 10 Mo, même si le fichier n'existe plus dans la dernière version.
- Pour vraiment retirer le fichier, il faut **réécrire l'historique** . Cela change les hashes des commits concernés : c'est une opération lourde, à éviter sur un dépôt partagé.

# Preuve
```bash
C:\Users\Administrator\depot_essai> echo "Depot d'essai" >> README.md

C:\Users\Administrator\depot_essai> git add README.md

C:\Users\Administrator\depot_essai> git commit -m "commit initial"
[master dc5cb2a] commit initial
 1 file changed, 1 insertion(+)
 create mode 100644 README.md

C:\Users\Administrator\depot_essai> git count-objects -vH
count: 15
size: 1.30 KiB
in-pack: 0
packs: 0
size-pack: 0 bytes
prune-packable: 0
garbage: 0
size-garbage: 0 bytes

C:\Users\Administrator\depot_essai> Powershell -c "$b=New-Object byte[] 10485760; (New-Object Random).NextBytes($b); [IO.File]::WriteAllBytes('gros.bin',$b)"

C:\Users\Administrator\depot_essai> git add gros.bin

C:\Users\Administrator\depot_essai> git commit -m "Ajout volontaire d'un fichier de 10 Mo"
[master 4529bd3] Ajout volontaire d'un fichier de 10 Mo
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 gros.bin

C:\Users\Administrator\depot_essai> git rm gros.bin
rm 'gros.bin'

C:\Users\Administrator\depot_essai> git commit -m "Retrait de gros.bin"
[master 59b8da7] Retrait de gros.bin
 1 file changed, 0 insertions(+), 0 deletions(-)
 delete mode 100644 gros.bin

C:\Users\Administrator\depot_essai> git show HEAD~1:gros.bin > test.bin && dir test.bin
 Volume in drive C has no label.
 Volume Serial Number is D866-F636

 Directory of C:\Users\Administrator\depot_essai

09/21/2026  07:38 AM        10,485,760 test.bin
               1 File(s)     10,485,760 bytes
               0 Dir(s)  262,524,121,088 bytes free

C:\Users\Administrator\depot_essai> del test.bin

C:\Users\Administrator\depot_essai> git count-objects -vH
count: 19
size: 10.00 MiB
in-pack: 0
packs: 0
size-pack: 0 bytes
prune-packable: 0
garbage: 0
size-garbage: 0 bytes
```