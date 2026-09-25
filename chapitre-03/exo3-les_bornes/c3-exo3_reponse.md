# Exercice : Fixez une taille minimale, puis essayez de réduire la fenêtre en dessous. Retirez-la, recommencez, et notez la plus petite taille que le système accepte.
 ## Programme initiale
 ```bash
 #include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;

    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable =  true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    bool running = true;

    while (running) {
        nkentseu::NkEvent* event = nullptr;
        while((event = nkentseu::NkEvents().PollEvent()) !=nullptr){
            // process events
            if(event ->Is<nkentseu::NkWindowCloseEvent>()){
                running=false;
            } 
        }
    }
    return 0;
}
```
## PRemier changement
```bash
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 400;
    cfg.height = 20;

    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable =  true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    bool running = true;

    while (running) {
        nkentseu::NkEvent* event = nullptr;
        while((event = nkentseu::NkEvents().PollEvent()) !=nullptr){
            // process events
            if(event ->Is<nkentseu::NkWindowCloseEvent>()){
                running=false;
            } 
        }
    }
    return 0;
}
```
**Observation:** Apres la compilation et l'execution, j'observe que la fenetre est toujours reduisable en dessous
## Changement 2
```bash
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 100;
    cfg.height = 20;

    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable =  true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    bool running = true;

    while (running) {
        nkentseu::NkEvent* event = nullptr;
        while((event = nkentseu::NkEvents().PollEvent()) !=nullptr){
            // process events
            if(event ->Is<nkentseu::NkWindowCloseEvent>()){
                running=false;
            } 
        }
    }
    return 0;
}
```
**Observation** la taille de la fenetre est encore plus petite que la precedente et on ne peut plus la reduire en dessous

## Changement 3
```bash
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 50;
    cfg.height = 10;

    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable =  true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    bool running = true;

    while (running) {
        nkentseu::NkEvent* event = nullptr;
        while((event = nkentseu::NkEvents().PollEvent()) !=nullptr){
            // process events
            if(event ->Is<nkentseu::NkWindowCloseEvent>()){
                running=false;
            } 
        }
    }
    return 0;
}
```
**Observation** La taille de la fenetre est la meme que la precedente et on ne peut pas effectuer la reduction de la fenetre en dessous . De plus quand je mofifie la taille jusqu'a 1;1 la taille est la meme que pour 50;20

## Conclusion 
**La plus petite taille fixe est de:**
```bash
cfg.width  = 1;
 cfg.height = 1;
```