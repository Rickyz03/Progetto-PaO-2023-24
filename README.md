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
In particolare, la simulazione del sensore di accelerazione genera un grafico a linea, e consente di visualizzare se i valori hanno o meno superato due soglie, inferiore e superiore, se lo hanno fatto allora l'aereo non è ancora pronto (ha un'accelerazione ancora troppo altalenante), altrimenti l'aereo farà presto servizio in aeroporto.
<br/>
Gli altri sensori, pur non indicando direttamente lo stato di sviluppo dell'aereo, consentono comunque la visualizzazione di un grafico, però stavolta di un grafico a barre, il quale rappresenta i valori discreti ottenuti giorno per giorno nel corso di una settimana di test.
<br/>
I grafici sono tutti realizzati attraverso QtCharts.
<br/>
La persistenza dei dati è realizzata tramite file JSON: un determinato file rappresenta i sensori utilizzati in un determinato centro di collaudo, mentre un altro file rappresenta i sensori utilizzati in un altro centro di collaudo.
<hr/>

## Tecnologie usate
* C++
* Qt
* JSON
<hr/>

## Istruzioni
Per compilare AeroSimulator, clonare o scaricare questo repository, digita `qmake` e poi `make`:

```bash
 git clone https://github.com/Rickyz03/Progetto-PaO-2023-24.git
 cd Progetto-PaO-2023-24/AeroSimulator/src
 qmake
 make
```

Assicurare di avere Qt, make e un compilatore C++ installati e disponibili nel tuo percorso.

Per eseguire l'applicazione, digita:

```bash
./AeroSimulator
```

<br/>
Se si dispone di sistema operativo Ubuntu, è inoltre consigliato non utilizzare wayland come gestore delle finestre, per una migliore esperienza nell'uso dell'app. Per utilizzare un altro gestore, occorre mettere la spunta su digita  `qmake` e nella schermata di accesso al sistema.
