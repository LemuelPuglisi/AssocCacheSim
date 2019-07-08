# Simulatore Cache Associativa

![Anteprima](/Images/simulator.jpg)

### Introduzione alla memoria cache 

La memoria cache è una memoria piccola e molto veloce che si interpone tra il processore e la memoria principale. 
Le proprietà di località spaziale e temporale dei programmi permettono alla cache di portare un effettivo vantaggio prestazionale. 
Si assuma che per velocità si intenda il reciproco del tempo di accesso a memoria. La velocità di trasferimento dati tra la cache ed il processore risulta essere radicalmente maggiore rispetto ai trasferimenti in memoria principale.  

### Memoria cache con indirizzamento associativo

L'indirizzamento associativo è un indirizzamento flessibile: ogni blocco di memoria è caricabile in qualsiasi posizione di cache. L'indirizzo di memoria centrale sarà diviso in due campi, ovvero spiazzamento, per identificare la parola, ed etichetta, per identificare il blocco. 
Il criterio di caricamento del blocco dalla memoria principale alla cache corrisponde ad una relazione binaria (o funzione a più valori). 
Ogni blocco trasferito dalla memoria principale alla memoria cache va posizionato nella prima posizione libera. Si ha conflitto solo quando la cache è piena: subentra qui l'algoritmo di sostituizione LRU. 

### Algoritmo Least recently used (LRU)

L' algoritmo consiste nel sostituire il blocco che da più tempo risulta essere inutilizzato. Per fare ciò è necessario che il controllore di cache tenga traccia dell'utilizzo di tutti i blocchi in cache con appositi contatori. Durante l'esecuzione, i criteri di incremento dei contatori sono i seguenti:

- Se c'è hit, il contatore lru della posizione interessata va azzerato, vanno incrementati di uno tutti i contatori dei blocchi inferiori.

- Se c'è miss e la cache non è piena, si carica il nuovo blocco dalla memoria principale, si azzera il contatore lru di quest'ultimo e si incrementano tutti gli altri contatori.

- Se c'è miss e la cache è piena, si seleziona il blocco con il valore lru maggiore, si sostituisce con il blocco prelevato in memoria, si azzera l' lru e si incrementano i contatori di tutti gli altri blocchi. 

## Utilizzare il simulatore

Le seguenti istruzioni forniranno una guida completa per l'installazione e l'utilizzo del simulatore.

### Prerequisiti

Il simulatore necessita di un compilatore C++, come, ad esempio, g++ (Linux) :  

```
$ sudo apt install g++
```

O un qualsiasi altro compilatore c++ nel caso di Windows (MingW). 


### Installazione

Scaricare il contenuto della repository tramite il tasto download, o in alternativa, se si dispone di git, clonare la repository con il seguente comando: 

```
git clone https://github.com/LemuelPuglisi/Assoc_cache_Sim..git
```

Una volta scaricato il contenuto, l'eseguibile risulta essere compatibile con distro debian-based [ test eseguiti : Ubuntu 19.04]

La compilazione avviene nel seguente modo: 

```
g++ handler.cpp -o cacheAssoc 
```
Si compili anche il generatore di memoria principale e loads: 

```
g++ Utils/hexaRAM.cpp -o memGen 
```
Il simulatore è pronto per l'esecuzione, sono stati forniti degli input di prova nella cartella Utils/samples/

Esempio di esecuzione: 

```
./cacheAssoc Utils/samples/nice_sample.txt -t 400 
```


## Parametri d'utilizzo

### Generazione della memoria principale 

È disponibile un tool, Utils/memGen, per generare degli input contenenti i parametri necessari al funzionamento del simulatore.

Eseguire il tool per creare un input personalizzato, attraverso la compilazione di parametri: 

```
./Utils/memGen  
```

![memGen](/Images/memGen.jpg)

L'esecuzione genererà un file di input contenente i parametri principali [ blocchi in memoria, blocchi in cache, parole per blocco, caricamenti del processore ], una matrice blocchi x parole rappresentante la memoria principale ed una quantità indicata di richieste alla cache con indirizzi casuali appartenenti alla memoria.

### Esecuzione del simulatore

L'esecuzione del simulatore richiede 2-3 parametri: 

  - File di input: generato tramite memGen o uno tra i samples. 
  - Flow mode: -q (Quick result), -b ( break points), -t (time between steps)
  - Nel caso si selezioni la modalità time between steps, è bene specificare i millisecondi p tra uno step e l'altro ( 200ms <= p <= 1000ms).

## Sviluppo

* [C++](https://isocpp.org/) - Il linguaggio di programmazione utilizzato.

## Autore

* **Lemuel Puglisi** - *Progetto Architettura degli Elaboratori* - [Sito Personale](https://lemuelpuglisi.github.io)

## Licenza

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
