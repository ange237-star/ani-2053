#  Règles Git du Projet

 Document de référence pour l'équipe de 4 étudiants.

## 1 Nommage des branches

| Type de branche | Format | Exemple |
|---|---|---|
| Fonctionnalité | `feature/<description-courte>` | `feature/page-connexion` |
| Correction de bug | `fix/<description-courte>` | `fix/erreur-calcul-total` |
| Documentation | `docs/<description-courte>` | `docs/ajout-readme` |
| Expérimental | `wip/<description-courte>` | `wip/test-api-rest` |

- **Règle** : toujours créer une branche à partir de `main`.
- **Règle** : utiliser des tirets (`-`) entre les mots, pas d'espaces ni de majuscules.
- **Règle** : supprimer la branche après merge.

---

## 2  Contenu d'un commit

- **Format du message** : `type: description courte` (max 50 caractères)
  - Exemples : `feat: ajout du formulaire de login`, `fix: correction overflow CSS`
- **Types autorisés** : `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`
- **Un commit = une seule modification logique.** Pas de "fourre-tout".
- **Ne jamais commiter** : fichiers de configuration locaux, mots de passe, clés API, fichiers `.env`.

---

## 3.  Qui relit quoi (Code Review)

- Chaque **Pull Request (PR)** doit être relue par **au moins 1 autre membre** du groupe avant merge.
- **Règle de répartition** : on ne relit pas son propre code. Rotation équitable entre les 4 membres.
- Le reviewer doit :
  - Vérifier que le code compile / fonctionne.
  - Vérifier la lisibilité et le respect des conventions.
  - Approuver (`Approve`) ou demander des changements (`Request changes`).
- **Aucun merge sur `main` sans approbation.**

---

## 4 Ce qui est interdit

-  **Push direct sur `main`** (toujours passer par une branche + PR).
-  **Force push** (`git push --force`) sur une branche partagée.
-  **Commits avec messages vagues** du type "fix", "update", "aaa".
-  **Commits contenant des données sensibles** (mots de passe, tokens).
-  **Merge sans review** d'au moins un autre membre.
-  **Travailler directement sur `main`** localement.

---

## 5 Que faire quand quelqu'un casse la branche principale

1. **Ne pas paniquer.** `main` est cassée, mais c'est réparable.
2. **Identifier le commit problématique** avec `git log` ou via l'historique de la PR.
3. **Revenir à un état stable** :
```bash
   git checkout main
   git revert <hash-du-commit-problématique>
   git push origin main
```
   → `git revert` crée un nouveau commit qui annule les changements, sans réécrire l'historique.
4. **Notifier l'équipe** (message dans le chat du groupe) en expliquant ce qui s'est passé.
5. **La personne responsable** corrige le bug sur une branche `fix/...` et soumet une PR normale.
6. **Rappel bienveillant** des règles lors du prochain point d'équipe. Pas de blame, on apprend.

---

##  Résumé en une phrase

 **Une branche par fonctionnalité, un message clair par commit, une review avant chaque merge, et on se parle quand ça casse.**