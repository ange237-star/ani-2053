## Dans fichier NKCanvas.jenga qui se trouve dans kernel/Runtime/NKCanvas de Nkentseu, 
  ## Les dependances directes de NKCanvas sont :
    NKCanvas
    │
    ├──► NKWindow
    ├──► NKFont
    ├──► NKImage
    ├──► NKStream
    ├──► NKTime
    ├──► NKGlad
    ├──► NKThreading
  ## Les dependances de chaque dependances
Niveau 2
│
├── NKThreading ──────────┐
├── NKGlad      ──────────┤
├── NKTime    ────────────┤
├── NKStream ─────────────┤
│         ▲               │
│         │               │
├── NKImage ──────────────┤
│         ▲               │
│         │               │
├── NKFont ───────────────┤
│         ▲               │
│         │               │
├── NKWindow ─────────────┤
│    ▲                    │
│                         │
└─────────────────────────┘
            │
            ▼
      NKCanvas (Niveau 0)

## Le graphe final pour les deux niveaux
NKThreading ──┐
NKGlad  ──────┤
NKTime ───────┤
              │
NKStream ─────┤
       ▲      │
       │      │
NKImage ──────┤
       ▲      │
       │      │
NKFont ───────┤
       ▲      │
       │      │
NKWindow ─────┤
     ─────────┘
     │
     ▼
NKCanvas

## Preuve :
_canvasDeps = ["NKWindow", "NKFont", "NKImage", "NKStream", "NKTime", "NKGlad", "NKThreading"]


nkentseudependson(
        _canvasDeps,
        selfexport="NKCanvas",
        extra_includes=["src"] + ([VULKAN_INCLUDE] if VULKAN_INCLUDE else []),
        extra_defines=_canvasDefines,
    )
