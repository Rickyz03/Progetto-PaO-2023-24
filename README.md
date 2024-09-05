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

## Istruzioni per l'esecuzione su Docker
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
