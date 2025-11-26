# The Gauntlet

**Corso:** Sviluppo Unreal Engine 5 & C++
**Tipologia:** Esercitazione Finale Individuale

## Obiettivo

Sviluppare un **Game Loop completo** (Menu Principale → Gameplay → Ritorno al Menu) partendo dal template Third Person.
Il focus è sull'**architettura C++**, usando le classi base dell’engine e sistemi di comunicazione avanzata (Interfacce, Delegati).

## Requisiti chiave

* Logica di gioco principalmente in **C++**.
* **Blueprint** usati solo per estendere classi C++ (asset, valori, logiche visive).
* Uso pratico di **Interfacce** e **Delegati** per il disaccoppiamento delle classi.

## Modalità di consegna

* **Repository Git** remota (GitHub, GitLab, ecc.)

  * `.gitignore` configurato per escludere: Binaries, Intermediate, Saved, Build.
* **Drive Condiviso**: Inserire un file/cartella nominato `COGNOME_NOME_TheGauntlet` contenente il link HTTP alla repo pubblica.

## Struttura delle cartelle (Content)

```
_Game/
  ├─ Core/         // GameMode, GameInstance, PlayerController, Interfaces
  ├─ Maps/         // MainMenu, Level_01
  ├─ Blueprints/   // Derivati dalle classi C++
  └─ UI/
```

## Architettura C++ obbligatoria

* `UGameInstance` custom: gestione flusso mappe (Launch, Quit, Load Level)
* `AGameModeBase` custom: regole livello (Win/Lose)
* `APlayerController` custom: gestione cursore e input UI (Menu/Pause)
* `ACharacter` custom: attributi giocatore (salute, inventario chiavi)

## Pattern di comunicazione

* **Interfacce**: per interazioni generiche (es: `IInteractable` con metodo `Interact()`)
* **Delegati**: per comunicazione eventi di stato (es: Multicast Delegate su fine livello o morte del player)

## Specifiche di Gameplay

* **Game Loop**

  1. Avvio: Caricamento mappa MainMenu, mouse visibile, pulsanti "Start" e "Quit".
  2. Gameplay: Su "Start", la GameInstance carica il livello, mouse nascosto.
  3. Obiettivo: Raggiungere il Punto B dal Punto A.
  4. Vittoria: Arrivati a B, segnalazione vittoria, poi ritorno al MainMenu.

* **Ostacoli** (minimo 5, ognuno con logica C++):

  * Porta/chiave (bool check)
  * Oggetto distruttibile (HP/distruzione)
  * Trappola mobile (movimento ciclico con Seno nel Tick)
  * Timer (passaggio temporaneo)
  * Puzzle di gruppo (es: 3 leve, uso TArray)

## Criteri di valutazione

* **Qualità C++ (40%)**: correttezza sintattica, memoria, interfacce/delegati, naming standard (A, U, I, b)
* **Setup progetto (20%)**: repository pulita, .gitignore, cartelle ordinate
* **Funzionalità (30%)**: gioco stabile, ciclo Menu-Gioco-Menu funzionante
* **Integrazione Blueprint (10%)**: blueprint usati correttamente per assemblaggio, non per logiche core

---

Se vuoi aggiungere la parte del link alla repo, puoi semplicemente aggiungere alla fine:

```
## Repository

[Link alla repository GitHub](https://github.com/tuo-user/tuo-repo)
```

Fammi sapere se vuoi una versione inglese, un formato diverso, o qualche personalizzazione!
