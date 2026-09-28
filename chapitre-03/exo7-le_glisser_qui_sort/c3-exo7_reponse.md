# Exercice 7: Faites un glisser qui commence dans la fenêtre et continue à l'extérieur, une fois sans capture, une fois avec. Décrivez la différence du point de vue de l'utilisateur.

## Mon programme
 ```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    // A CHANGER ENTRE LES DEUX ESSAIS 
     bool useCapture = false;   

    bool dragging = false;

    std::cout << " Essai " << (useCapture ? "AVEC" : "SANS")
              << " capture de la souris " << std::endl;

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    window.Close();
                }
                else if(kp->GetKey()== NkKey::NK_C){
                    useCapture = !useCapture;
                    std::cout <<" /n Mode : " << (useCapture ?  "Active" : "Desactive") <<std::endl;
                }
            }
            
            // --- Debut du glisser : appui bouton gauche ---
            else if (auto* mp = ev->As<NkMouseButtonPressEvent>()) {
                if (mp->GetButton() == NkMouseButton::NK_MB_LEFT) {
                    dragging = true;
                    if (useCapture) {
                        window.CaptureMouse(true);
                    }
                    std::cout << "[APPUI] bouton gauche a ("
                              << mp->GetX() << ", " << mp->GetY() << ")" << std::endl;
                }
            }
            // Pendant le glisser : mouvements 
            else if (auto* mm = ev->As<NkMouseMoveEvent>()) {
                if (dragging) {
                    std::cout << "[GLISSE] client=(" << mm->GetX() << ", " << mm->GetY()
                              << ")  ecran=(" << mm->GetScreenX() << ", "
                              << mm->GetScreenY() << ")" << std::endl;
                }
            }
            // Fin du glisser : relachement bouton gauche
            else if (auto* mr = ev->As<NkMouseButtonReleaseEvent>()) {
                if (mr->GetButton() == NkMouseButton::NK_MB_LEFT) {
                    std::cout << "[RELACHE] bouton gauche a ("
                              << mr->GetX() << ", " << mr->GetY() << ")" << std::endl;
                    dragging = false;
                    if (useCapture) {
                        window.CaptureMouse(false);
                    }
                }
            }
          
        }
    }

    return 0;
}
 ```
## Analyse
**Apres avoir taper la commande jenga build et jenga run**
  **Quand le useCapture est active , lorsque ma fenetre s'ouvre et une fois que j'appuie sur le bouton gauche a l'interieur de la fenetre et quand le garde enfoncer et que je sors de la fenetre puis continue a bouger les positions de X et Y se lisent dans le terminal**
  ```bash
  PS C:\Users\Administrator\Chute\FirstWindow> jenga r

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Window.exe
     C:\Users\Administrator\Chute\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

 Essai SANS capture de la souris 
 /n Mode : Active
[APPUI] bouton gauche a (514, 397)
[GLISSE] client=(513, 397)  ecran=(1076, 662)
[GLISSE] client=(519, 395)  ecran=(1082, 660)
[GLISSE] client=(554, 383)  ecran=(1117, 648)
[GLISSE] client=(591, 374)  ecran=(1154, 639)
[GLISSE] client=(600, 373)  ecran=(1163, 638)
[GLISSE] client=(618, 373)  ecran=(1181, 638)
[GLISSE] client=(630, 373)  ecran=(1193, 638)
[GLISSE] client=(596, 439)  ecran=(1159, 704)
[GLISSE] client=(577, 455)  ecran=(1140, 720)
[GLISSE] client=(573, 458)  ecran=(1136, 723)
[GLISSE] client=(608, 370)  ecran=(1171, 635)
[GLISSE] client=(609, 368)  ecran=(1172, 633)
[GLISSE] client=(611, 366)  ecran=(1174, 631)
[GLISSE] client=(613, 363)  ecran=(1176, 628)
[GLISSE] client=(614, 362)  ecran=(1177, 627)
[GLISSE] client=(612, 361)  ecran=(1175, 626)
[GLISSE] client=(606, 361)  ecran=(1169, 626)
[GLISSE] client=(583, 368)  ecran=(1146, 633)
[GLISSE] client=(546, 406)  ecran=(1109, 671)
[GLISSE] client=(697, 467)  ecran=(1260, 732)
[GLISSE] client=(724, 471)  ecran=(1287, 736)
[GLISSE] client=(924, 489)  ecran=(1487, 754)
[GLISSE] client=(949, 491)  ecran=(1512, 756)
[GLISSE] client=(951, 491)  ecran=(1514, 756)
[GLISSE] client=(1029, 483)  ecran=(1592, 748)
[GLISSE] client=(1050, 482)  ecran=(1613, 747)
[GLISSE] client=(1052, 482)  ecran=(1615, 747)
[GLISSE] client=(1058, 481)  ecran=(1621, 746)
[GLISSE] client=(1075, 492)  ecran=(1638, 757)
[GLISSE] client=(1076, 493)  ecran=(1639, 758)
[GLISSE] client=(1051, 485)  ecran=(1614, 750)
[GLISSE] client=(1050, 485)  ecran=(1613, 750)
[GLISSE] client=(1054, 485)  ecran=(1617, 750)
[GLISSE] client=(1087, 494)  ecran=(1650, 759)
[GLISSE] client=(1089, 494)  ecran=(1652, 759)
[GLISSE] client=(1092, 495)  ecran=(1655, 760)
[GLISSE] client=(1099, 497)  ecran=(1662, 762)
[GLISSE] client=(1109, 497)  ecran=(1672, 762)
[GLISSE] client=(1112, 495)  ecran=(1675, 760)
[GLISSE] client=(1116, 490)  ecran=(1679, 755)
[GLISSE] client=(1128, 473)  ecran=(1691, 738)
[GLISSE] client=(1127, 473)  ecran=(1690, 738)
[GLISSE] client=(1126, 473)  ecran=(1689, 738)
[GLISSE] client=(1124, 472)  ecran=(1687, 737)
[GLISSE] client=(1123, 471)  ecran=(1686, 736)
[GLISSE] client=(1120, 465)  ecran=(1683, 730)
[GLISSE] client=(1110, 452)  ecran=(1673, 717)
[GLISSE] client=(1052, 390)  ecran=(1615, 655)
[GLISSE] client=(1032, 409)  ecran=(1595, 674)
[GLISSE] client=(1054, 370)  ecran=(1617, 635)
[GLISSE] client=(1106, 440)  ecran=(1669, 705)
[GLISSE] client=(1119, 439)  ecran=(1682, 704)
[GLISSE] client=(1124, 436)  ecran=(1687, 701)
[GLISSE] client=(1131, 429)  ecran=(1694, 694)
[GLISSE] client=(1133, 422)  ecran=(1696, 687)
[GLISSE] client=(1139, 403)  ecran=(1702, 668)
[GLISSE] client=(944, 313)  ecran=(1507, 578)
[GLISSE] client=(925, 202)  ecran=(1488, 467)
[GLISSE] client=(945, 148)  ecran=(1508, 413)
[GLISSE] client=(946, 146)  ecran=(1509, 411)
[GLISSE] client=(795, 185)  ecran=(1358, 450)
[GLISSE] client=(793, 185)  ecran=(1356, 450)
[GLISSE] client=(787, 185)  ecran=(1350, 450)
[GLISSE] client=(769, 184)  ecran=(1332, 449)
[GLISSE] client=(751, 181)  ecran=(1314, 446)
[GLISSE] client=(737, 178)  ecran=(1300, 443)
[GLISSE] client=(724, 175)  ecran=(1287, 440)
[GLISSE] client=(712, 172)  ecran=(1275, 437)
[GLISSE] client=(701, 170)  ecran=(1264, 435)
[GLISSE] client=(695, 167)  ecran=(1258, 432)
[GLISSE] client=(706, 140)  ecran=(1269, 405)
[GLISSE] client=(748, 116)  ecran=(1311, 381)
[GLISSE] client=(911, 42)  ecran=(1474, 307)
[GLISSE] client=(913, 41)  ecran=(1476, 306)
[GLISSE] client=(917, 40)  ecran=(1480, 305)
[GLISSE] client=(918, 40)  ecran=(1481, 305)
[GLISSE] client=(918, 39)  ecran=(1481, 304)
[GLISSE] client=(919, 39)  ecran=(1482, 304)
[GLISSE] client=(920, 39)  ecran=(1483, 304)
[GLISSE] client=(921, 38)  ecran=(1484, 303)
[GLISSE] client=(922, 38)  ecran=(1485, 303)
[GLISSE] client=(923, 38)  ecran=(1486, 303)
[GLISSE] client=(924, 39)  ecran=(1487, 304)
[GLISSE] client=(884, 4)  ecran=(1447, 269)
[GLISSE] client=(882, 4)  ecran=(1445, 269)
[RELACHE] bouton gauche a (882, 4)
  ```

  **Apres avoir appuyer sur la touche `c` . Quand useCapture est desactive, lorsque j'appuie et je garde enfoncer le bouton gauche de ma souris a l'interieur de ma fenetre , les positions de X et Y se s'affichent dans le terminal de maniere continue lorsque je deplace la souris mais quand je sors de la fenetre les positions arretent de s'afficher lors du deplacement de la souris a l'extieur.**
  ```bash
   /n Mode : Desactive
[APPUI] bouton gauche a (615, 139)
[GLISSE] client=(611, 142)  ecran=(1174, 407)
[GLISSE] client=(610, 142)  ecran=(1173, 407)
[GLISSE] client=(610, 141)  ecran=(1173, 406)
[GLISSE] client=(516, 136)  ecran=(1079, 401)
[GLISSE] client=(608, 145)  ecran=(1171, 410)
[GLISSE] client=(521, 110)  ecran=(1084, 375)
[GLISSE] client=(464, 152)  ecran=(1027, 417)
[GLISSE] client=(470, 158)  ecran=(1033, 423)
[GLISSE] client=(490, 170)  ecran=(1053, 435)
[GLISSE] client=(519, 179)  ecran=(1082, 444)
[GLISSE] client=(551, 184)  ecran=(1114, 449)
[GLISSE] client=(565, 184)  ecran=(1128, 449)
[GLISSE] client=(583, 184)  ecran=(1146, 449)
[GLISSE] client=(667, 118)  ecran=(1230, 383)
[GLISSE] client=(663, 113)  ecran=(1226, 378)
[GLISSE] client=(707, 166)  ecran=(1270, 431)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (32.37s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ```
  