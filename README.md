### Esercizio 1

#### Linguaggio richiesto: C

#### Testo

Implementare una libreria che offre i seguenti algoritmi di ordinamento:

- Insertion Sort
- Quicksort

Il codice che implementa ciascun algoritmo deve essere generico. Inoltre, ogni algoritmo deve permettere di specificare (cioè deve accettare in input) il criterio secondo cui ordinare i dati.

#### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni suggerite nel documento Unit Testing.

Il file contiene 20 milioni di record da ordinare.
Ogni record è descritto su una riga e contiene i seguenti campi:

- id: (tipo intero) identificatore univoco del record;
- field1: (tipo stringa) contiene parole estratte dalla divina commedia,
  potete assumere che i valori non contengano spazi o virgole;
- field2: (tipo intero);
- field3: (tipo floating point);

Il formato è un CSV standard: i campi sono separati da virgole; i record sono
separati da `\n`.

Usando ciascuno degli algoritmi implementati, si ordinino i *record* (non è sufficiente ordinare i
singoli campi) contenuti nel file `records.csv` in ordine non decrescente secondo i valori contenuti
nei tre campi "field" (cioè, per ogni algoritmo, è necessario ripetere l'ordinamento tre volte, una
volta per ciascun campo).

Si misurino i tempi di risposta e si produca una breve relazione in cui si riportano i risultati
ottenuti insieme a un loro commento. Nel caso l'ordinamento si  protragga per più di 10 minuti
potete interrompere l'esecuzione e riportare un fallimento dell'operazione. I risultati sono quelli
che vi sareste aspettati? Se sì, perché? Se no, fate delle ipotesi circa il motivo per cui gli
algoritmi non funzionano come vi aspettate, verificatele e riportate quanto scoperto nella
relazione.



### Esercizio 2

#### Linguaggio richiesto: Java

#### Testo

Si consideri il problema di determinare la distanza di edit tra due stringhe (Edit distance): date due stringhe s1 e s2, non necessariamente della stessa lunghezza, determinare il minimo numero di operazioni necessarie per trasformare la stringa s2 in s1. Si assuma che le operazioni disponibili siano: cancellazione e inserimento. Esempi:

- "casa" e "cassa" hanno edit distance pari a 1 (1 cancellazione);
- "casa" e "cara" hanno edit distance pari a 2 (1 cancellazione + 1 inserimento);
- “vinaio” e “vino” hanno edit distance=2 (2 inserimenti);
- "tassa" e "passato" hanno edit distance pari a 4 (3 cancellazioni + 1 inserimento);
- "pioppo" e "pioppo" hanno edit distance pari a 0.

1. Si implementi una versione ricorsiva della funzione edit\_distance basata sulle seguenti osservazioni (indichiamo con $|s|$ la lunghezza di $s$ e con $\mathrm{rest}(s)$ la sottostringa di $s$ ottenuta ignorando il primo carattere di $s$):

- se $|s1|$ = 0, allora $\mathrm{edit\_distance}(s1,s2) = |s2|$;
- se $|s2|$ = 0, allora $\mathrm{edit\_distance}(s1,s2) = |s1|$;
- altrimenti, siano:
  - $d_{\mathrm{no-op}} =
        \begin{cases}
        \mathrm{edit\_distance}(\mathrm{rest}(s1),\mathrm{rest}(s2)) & \mathrm{se\ } s1[0]=s2[0] \\
        \infty & \mathrm{altrimenti}
        \end{cases}$
  - $d_{\mathrm{canc}} = 1+ \mathrm{edit\_distance}(s1,\mathrm{rest}(s2))$
  - $d_{\mathrm{ins}} = 1+ \mathrm{edit\_distance}(\mathrm{rest}(s1),s2)$

Si ha: $\mathrm{edit\_distance}(s1,s2)=\min\{d_{\mathrm{no-op}},d_{\mathrm{canc}},d_{\mathrm{ins}}\}$

1. Si implementi una seconda versione edit\_distance\_dyn della funzione, adottando una strategia di programmazione dinamica. Tale versione deve essere anch'essa ricorsiva (in particolare, essa può essere facilmente ottenuta a partire dall'implementazione richiesta al punto precedente).

*Nota*: Le definizioni sopra riportate non corrispondono al modo usuale di definire la distanza di edit. Sono del tutto sufficienti però per risolvere l'esercizio e sono quelle su cui dovrà essere basato il codice prodotto.

#### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni suggerite nel documento Unit Testing.

#### Uso delle funzioni implementate

Il file `dictionary.txt` contiene l'elenco (di una parte significativa) delle parole italiane. Le parole sono scritte di seguito, ciascuna su una riga.

Il file `correctme.txt` contiene una citazione di John Lennon. La citazione presenta alcuni errori di battitura.

Si implementi un'applicazione che usa la funzione edit\_distance\_dyn per determinare, per ogni parola w in correctme.txt, la lista di parole in dictionary.txt con edit distance minima da w. Si sperimenti il funzionamento dell'applicazione e si riporti in una breve relazione (circa una pagina) i risultati degli esperimenti.



### Esercizio 3

#### Linguaggio richiesto: C

#### Testo

Si implementi una libreria per la struttura dati Hash Map, tenendo conto delle seguenti indicazioni:

- Una Hash Map rappresenta un insieme di associazioni del tipo `<K,V>`, dove K è una chiave e V è il valore ad essa associato;
- in una Hash Map, non possono esservi chiavi ripetute;
- l'implementazione sfrutta un meccanismo di hashing;
- L'implementazione deve offrire le seguenti operazioni:
  - creazione di una Hash Map vuota;
  - distruzione di una Hash Map (con conseguente deallocazione della memoria associata);
  - verifica se una  Hash Map è vuota;
  - recupero del numero di associazioni presenti in una Hash Map;
  - cancellazione di tutte le associazioni di una Hash Map;
  - verifica se la chiave specificata è presente in una Hash Map;
  - inserimento in una Hash Map di un'associazione di tipo `<K,V>`;
  - recupero da una Hash Map dell'eventuale valore, associato alla chiave specificata
  - cancellazione da una Hash Map dell'eventuale associazione con una chiave specificata
  - recupero dell'insieme delle chiavi presenti in una Hash Map
- Il codice che implementa la Hash Map deve essere generico (nel senso che deve consentire di inserire associazioni `<K,V>` di cui non è noto a tempo di compilazione né il tipo della chiave K, né quello del valore V) e non deve assumere alcuna cardinalità massima per l'insieme di associazioni che possono essere ospitate nella Hash Map.

#### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni suggerite nel documento Unit Testing.

#### Uso delle funzioni implementate

Si esegua quanto segue e si scriva una breve relazione riguardante i risultati ottenuti:

- si carichi il contenuto del file in un oggetto di tipo Hash Map; si misurino i tempi di caricamento;
- si carichi il contenuto del file in un array allocato staticamente (`hashes.txt` contiene $6\,321\,078$ coppie di interi) ordinato per chiave (la decisione a proposito di quando e come effettuare l'ordinamento è lasciata allo studente e deve essere presa seguendo un criterio di economia dei tempi di esecuzione); si misurino i tempi di caricamento;
- si estraggano a caso $10\,000\,000$ numeri interi tra $0$ e $10\,000\,000$ e li si memorizzi in un array `keys`;
- si misuri il tempo necessario per recuperare i valori associati alle chiavi contenute nell'array `keys` usando la Hash Map;
- si misuri il tempo necessario a recuperare i valori associati alle chiavi contenute nell'array `keys` usando una ricerca binaria sull'array ordinato;
- si controlli che il numero di chiavi reperite con successo sia identico nei due casi presi in considerazione.




### Esercizio 4

#### Linguaggio richiesto: C o Java

#### Testo

Si consideri un grafo connesso con $N$ nodi e $N-1$ archi bidirezionali pesati con un peso intero $W$. Ci si pone il problema di trovare un algoritmo efficiente per rispondere a $Q$ distinte interrogazioni.

Una interrogazione consiste in un nuovo arco pesato $q$. L'algoritmo deve rispondere `YES` se $q$ permette di ridurre il peso complessivo del grafo, `NO` altrimenti. L'arco $q$ soddisfa questa condizione se esiste un arco $e$ tale per cui sia possibile sostituire $q$ a $e$ lasciando il grafo connesso e diminuendone il peso complessivo. L'esecuzione della singola interrogazione non deve modificare il grafo (i.e., il grafo di partenza è sempre lo stesso).

I file di input iniziano con una linea contenente il numero $N$ di nodi del grafo a cui seguono $N-1$ linee contenenti gli archi. Ogni linea che specifica un arco contiene `3` interi separati da spazi: il nodo sorgente, il nodo destinazione e il peso dell'arco.

I file continuano con una linea contenente il numero $Q$ di interrogazioni a cui rispondere. Seguono $Q$ linee contenenti le interrogazioni. Ogni interrogazione è nello stesso formato usato per descrivere gli archi.

L'output del programma deve consistere in esattamente $Q$ linee contenenti `YES` o `NO` a seconda che la risposta alla corrispondente interrogazione sia positiva (l'arco oggetto dell'interrogazione riduce il peso del grafo) o negativa (viceversa).

Potete assumere quanto segue:

- $1 \leq N \leq 100\,000$
- $1 \leq Q \leq 100\,000$
- i nodi sono interi che assumono valori nel range $[1, 100\,000]$
- per ogni arco $(u,v,w): u \neq v \wedge w \in [1, 1\,000\,000\,000]$.

### Esempio:

#### Input:
```
6
1 2 2
1 3 3
3 4 5
3 5 4
2 6 4
4
1 4 4
4 5 6
2 3 8
1 6 3
```

#### Output atteso:

```
YES
NO
NO
YES
```
