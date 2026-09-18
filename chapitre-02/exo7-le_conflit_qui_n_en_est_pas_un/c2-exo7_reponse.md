# Modification du fichier Nkentseu.jenga 
 ## Apres avoir ajouter la deux lignes suivant au debut et a la fin du fichier
  **NOTE: HarmonyOS requires a C++17 compiler (e.g. clang++ 14+), so we can use lambdas and auto.**
  **#TODO: ajouter un test de rendu (OpenGL ES 3.2) pour valider le bring-up complet de l'API graphique HarmonyOS.**
   
   ## Commande : git add -p
   **J'ai tape la commande git add -p Nkentseu.jenga, puis git commit -m "Ajoute une note dans le NKentseu.jenga** 
  **Preuve** 
   PS C:\Nkentseu> git add -p Nkentseu.jenga
diff --git a/Nkentseu.jenga b/Nkentseu.jenga
index e8176e95..7221a3d9 100644
--- a/Nkentseu.jenga
+++ b/Nkentseu.jenga
@@ -1,6 +1,7 @@
 #!/usr/bin/env python3

 # -*- coding: utf-8 -*-
+ # NOTE: HarmonyOS requires a C++17 compiler (e.g. clang++ 14+), so we can use lambdas and auto.

 r"""

(1/2) Stage this hunk [y,n,q,a,d,k,K,j,J,g,/,e,p,P,?]? y
@@ -1726,3 +1727,8 @@ with workspace("Nkentseu", location="."):
     # contient pas son outil.
     with include("Applications/UnkenyEditor/UnkenyEditor.jenga"):
         pass
+
+# À la fin du fichier, avec les autres include
+with include("Applications/MonEssai/MonEssai.jenga"):
+    pass
+# TODO: ajouter un test de rendu (OpenGL ES 3.2) pour valider le bring-up complet de l'API graphique HarmonyOS.
(2/2) Stage this hunk [y,n,q,a,d,K,J,g,/,e,p,P,?]? n

PS C:\Nkentseu> git commit -m "Ajoute une note dans le Nkentseu.jenga"
[main 9aaf9b48] Ajoute une note dans le Nkentseu.jenga
 1 file changed, 1 insertion(+)
   **Puis git add -p Nkentseu.jenga, git commit -m "Ajoute TODO dans le Nkentseu.jenga**
  **Preuve**
   PS C:\Nkentseu> git add -p Nkentseu.jenga
diff --git a/Nkentseu.jenga b/Nkentseu.jenga
index bfafcec1..7221a3d9 100644
--- a/Nkentseu.jenga
+++ b/Nkentseu.jenga
@@ -1727,3 +1727,8 @@ with workspace("Nkentseu", location="."):
     # contient pas son outil.
     with include("Applications/UnkenyEditor/UnkenyEditor.jenga"):
         pass
+
+# À la fin du fichier, avec les autres include
+with include("Applications/MonEssai/MonEssai.jenga"):
+    pass
+# TODO: ajouter un test de rendu (OpenGL ES 3.2) pour valider le bring-up complet de l'API graphique HarmonyOS.
(1/1) Stage this hunk [y,n,q,a,d,e,p,P,?]? y

PS C:\Nkentseu> git commit -m "Ajoute TODO dans le Nkentseu.jenga"
[main d8d40ead] Ajoute TODO dans le Nkentseu.jenga
 1 file changed, 5 insertions(+)
   ## Pour afficher l'historique des commits faits j'ai tape git log --oneline -n 2
 **Preuve**
 PS C:\Nkentseu> git log --oneline -n 2   
d8d40ead (HEAD -> main) Ajoute TODO dans le Nkentseu.jenga
9aaf9b48 Ajoute une note dans le Nkentseu.jenga
