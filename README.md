# Simulatore Cache Associativa

// Documentazione

## Utilizzare il simulatore

Tramite le seguenti istruzioni sarai in grado di installare ed utilizzare il simulatore. 


### Prerequisiti

Il simulatore necessita di un compilatore C++, come, ad esempio, g++ (Linux) :  

```
$ sudo apt install g++
```

O un qualsiasi altro compilatore c++ nel caso di Windows (MingW). 


### Installazione

Scaricare il contenuto della repository tramite il tasto download, o in alternativa, se si dispone di git, clonale la repository con il seguente comando: 

```
git clone https://github.com/LemuelPuglisi/Assoc_cache_Sim..git
```

Una volta scaricato il contenuto, l'eseguibile risulta essere utilizzabile in distro linux, [ test eseguiti : Ubuntu 19.04]
Se si dispone di distro non compatibili o sistemi operativi di basso rango (Windows), allora potrete compilare direttamente l'handler con i comando che segue: 

```
g++ handler.cpp -o cacheAssoc 
```

Seguendo il ragionamento precedente, in caso di necessità ricompilate anche il generatore di input: 

```
g++ Utils/hexaRAM.cpp -o memGen 
```

Adesso il vostro simulatore è pronto all'uso!  

## Running the tests

// descrivere l'utilizzo

## Sviluppo

Il simulatore è stato sviluppato negli stessi giorni in cui Cristo è morto e risorto.

## Built With

* [C++](https://isocpp.org/) - Il linguaggio di programmazione utilizzato.

## Authors

* **Lemuel Puglisi** - *Progetto Architettura degli Elaboratori* - [Charlemagne](https://lemuelpuglisi.github.io)


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
