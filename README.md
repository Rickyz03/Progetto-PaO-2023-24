# AeroSimulator
![Logo](./AeroSimulator/src/Assets/Icona.svg)
<br/>
Repository per il codice sorgente del progetto del corso di Programmazione ad oggetti, laurea triennale in Informatica all'Università di Padova, A.A. 2023/2024.

<hr/>

## Funzionalità
AeroSimulator è un'applicazione che consente la creazione, modifica, cancellazione, ricerca, salvataggio e simulazione di sensori.
<br/>
Questi sensori appartengono ad un centro di collaudo per aeroplani, si tratta di sensori di 4 tipi: sensori di distanza percorsa, di tempo di volo, di velocità e di accelerazione.
<br/>
In particolare, la simulazione del sensore di accelerazione genera un grafico a linea, e consente di visualizzare se i valori hanno o meno superato due soglie, inferiore e superiore: se lo hanno fatto allora l'aereo non è ancora pronto (ha un'accelerazione ancora troppo altalenante), altrimenti l'aereo farà presto servizio in aeroporto.
<br/>
Gli altri sensori, pur non indicando direttamente lo stato di sviluppo dell'aereo, consentono comunque la visualizzazione di un grafico, però stavolta di un grafico a barre, il quale rappresenta i valori discreti ottenuti giorno per giorno nel corso di una settimana di test e misurazioni.
<br/>
I grafici sono tutti realizzati attraverso QtCharts.
<br/>
La persistenza dei dati è realizzata tramite file JSON: un singolo file rappresenta i sensori utilizzati in un determinato centro di collaudo.

<hr/>

## Tecnologie usate
* C++
* Qt
* JSON

<hr/>

## Dipendenze
* Un compilatore g++ per C++
* Qt almeno versione 5

<hr/>

## Istruzioni per la compilazione locale
Per compilare AeroSimulator:

```bash
 git clone https://github.com/Rickyz03/Progetto-PaO-2023-24.git
 cd Progetto-PaO-2023-24/AeroSimulator/src
 qmake
 make
```

Assicurati di avere Qt, make e un compilatore C++ installati e disponibili nel tuo percorso.

Per eseguire l'applicazione, digita:

```bash
 ./AeroSimulator
```

Se disponi di Ubuntu come sistema operativo, consiglio di non utilizzare wayland come gestore delle finestre, per una migliore esperienza nell'uso dell'app. Per utilizzare un altro gestore, in basso a destra nella schermata di accesso al sistema clicca sul tasto delle opzioni e metti la spunta su `Ubuntu on Xorg`; poi, accedi normalmente.

<hr/>

## Istruzioni per l'esecuzione su Docker per Linux
Per eseguire AeroSimulator su Docker, occorre avere il deamon Docker installato e attivo.  
Una volta soddisfatta la nuova dipendenza, per creare l'immagine segui le istruzioni:

```bash
 git clone https://github.com/Rickyz03/Progetto-PaO-2023-24.git
 cd Progetto-PaO-2023-24
 sudo docker build -t aerosimulator .
```

Per eseguire l'app in un container dell'immagine appena creata:
```bash
 xhost +local:docker
 sudo docker run -e DISPLAY=$DISPLAY \
                -v /tmp/.X11-unix:/tmp/.X11-unix \
                -v /dev/dri:/dev/dri \
                --device /dev/snd \
                aerosimulator
```

<hr/>

## Istruzioni per l'esecuzione su Docker per Windows
Per eseguire AeroSimulator su Docker su Windows, occorre avere Docker Desktop installato e attivo.  
Una volta soddisfatta la dipendenza, per creare l'immagine segui le istruzioni:

```bash
 git clone https://github.com/Rickyz03/Progetto-PaO-2023-24.git
 cd Progetto-PaO-2023-24
 docker build -t aerosimulator .
```

### Installazione e configurazione del server X11 (VcXsrv)

Prima di eseguire l'applicazione, è necessario installare un server X11 per Windows. Ti consigliamo VcXsrv:

1. **Scarica VcXsrv** dal sito ufficiale: [https://sourceforge.net/projects/vcxsrv/](https://sourceforge.net/projects/vcxsrv/)
2. **Installa VcXsrv** seguendo la procedura guidata standard
3. **Avvia XLaunch** (dovrebbe essere disponibile nel menu Start dopo l'installazione)
4. **Configura XLaunch** seguendo questi passaggi:
   - **Display settings**: Seleziona "Multiple windows" e lascia il Display number a -1
   - **Client startup**: Seleziona "Start no client"
   - **Extra settings**: 
     - ✅ Spunta "Clipboard"
     - ✅ Spunta "Primary Selection" 
     - ✅ Spunta "Native opengl"
     - ✅ **IMPORTANTE**: Spunta "Disable access control" (necessario per Docker)
   - Clicca "Avanti" e poi "Fine"

5. **Verifica che VcXsrv sia in esecuzione**: Dovresti vedere l'icona di VcXsrv nella system tray (area di notifica)

### Esecuzione dell'applicazione

Dopo aver configurato e avviato VcXsrv:

```bash
 docker run -e DISPLAY=host.docker.internal:0.0 --add-host=host.docker.internal:host-gateway aerosimulator
```

**Nota per Windows:** Assicurati che il tuo X11 server sia configurato per accettare connessioni da client esterni e che Windows Firewall non blocchi le connessioni.
