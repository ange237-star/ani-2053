## Construction de l'arbre de NKMath
```
├─────────────────────────────────────────────────────────────┤
│    NKMath                                                   │
├─────────────────────────────────────────────────────────────┤
                        ↑  ↑ ↑ ↑
┌─────────────────────────────────────────────────────────────┐
│   NKContainers                                              │
├─────────────────────────────────────────────────────────────┤
                           ↑ ↑ ↑
┌─────────────────────────────────────────────────────────────┐
│     NKMemory                                                │
├─────────────────────────────────────────────────────────────┤
                        ↑   ↑   
┌─────────────────────────────────────────────────────────────┐
│     NKCore                                                  │
├─────────────────────────────────────────────────────────────┤
                           ↑   
┌─────────────────────────────────────────────────────────────┐
│     NKPlatform                                              │       │
└─────────────────────────────────────────────────────────────┘
```
## preuve de cette arbre

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (5 projects):
  1. NKPlatform [STATIC_LIB] →
  2. NKCore [STATIC_LIB] (depends: NKPlatform) →
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) →
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) →
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)