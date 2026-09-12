## le nombre de fichiers .h et .cpp est :
4335
## le nombre de ligne de code des fichiers .h et .cpp est :
1905063
## comparaison
| Métrique | Document | Votre machine | Écart |
| --- | --- | --- | --- |
| **Fichiers** (.cpp + .h) | 2 641 | 4 335 | **+1 694** (+64%) |
| **Lignes de code** | 1 193 385 | 1 905 063 | **+711 678** (+60%) |

## ces nombres differents par ce qu'il contient  les fichiers test, et des dossiers build car le cours dit cherchez toujours a inclure le dossiers build 

## la preuve qui affirme cette reponse est :
# Pour les fichiers source (.cpp et .h), en excluant Build/
(Get-ChildItem -Recurse -Include *.cpp,*.h -Exclude Build | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count

# Pour les lignes de code total
(Get-ChildItem -Recurse -Include *.cpp,*.h | Where-Object { $_.FullName -notmatch '\\Build\\' } | Get-Content | Measure-Object -Line).Lines

# Pour les Fichiers avec 'test' dans le chemin
(Get-ChildItem -Recurse -Include *.cpp,*.h | Where-Object { $_.FullName -match 'test' }).Count
