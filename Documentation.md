\#Jetpack Menace

Příkazy v menu:
- start [gameName]
	- Vytvoří novou hru s názvem gameName
- load [gameName]
	- Pokusí se načíst hru s názvem gameName
- help
	- Vypíše všechny příkazy
- quit
	- Ukončí režim menu

Ovládání hry:
- 'w' - pohyb nahoru
- 's' - pohyb dolu
- 'a' - pohyb doleva
- 'd' - pohyb doprava

- 'q' - ukončí hru
- 'x' - uloží stav hry

- O = Hráč
- E = AI
	- Pozor, pokud se tě nezalekne a neuteče, může tu ublížit
- R = Brnění
	- Seber ho a zvyš si brnění
- ~ = Láva
	- Radši do ní nestoupej
- @ = Bouřka
	- Zamotá se ti hlava a spadneš na zem
- Y = Strom
	- Neprojdeš
- \# = Pevná stěna 
	- Stěna, kterou se nedá prolétnout.
- | = Průchozí stěna
	- Stěna, kterou když hráč prolétne načte se další chunk

Jetpack Menace je sandbox hra, ve které hráč lítá prostorem kde se vznáší objekty, 
zastrašuje nepřátele a snaží se přežít. Na jeho cestě ho mohou potkat nejen nepřátelé, 
ale také nebezpečné přírodní jevy jako je láva nebo bouře. Hráči se nad hrací plochou 
zobrazuje počet zabití a stav brnění. Při vstupy do lávy, vlétnutí do bouřky, nebo 
konfrontaci s nepřátelem se budou probíhat různé interakce (kolize), jejichž důsledkem 
může být snížení hráčova brnění nebo posun hráče. Pokud hráčovo brnění klesne až na 
nulu, hra pro hráče končí. 
Hra je i multiplayer a běží dokud je alespoň jeden z hráčů naživu.

```
> Enter a command ["help" for command info]:
help
> Help:
    > start [gameName]
    > load  [gameName]
    > help
    > quit
> Enter a command ["help" for command info]:
start prvniHra

-- ostream clears

Kills: 0
Armor: 45
##############################################################
|          @~               @      ~      Y      R           |
|    E     ~    ~          R         Y~       Y              |
|                            Y             ~  @              |
|          Y                   Y   @        @E               |
|       Y          ~R                     E                  |
|         Y   @      R                     Y     @           |
|       @   @  Y           E@      R               ~~Y       |
|  @       Y    ~        @                          E        |
|       ~  ~     ~     ~            Y   R    RRY            R|
|           Y          Y                    E     Y          |
|     YR                 E     ~    R   R~       Y         R |
|     ~        R                                            ~|
|                           R            @                   |
|   ~       ~  ~                Y        ~R                  |
|      E              @   O            R  Y               R  |
|                  ~                               R        E|
|R  R     R  ~                    Y     ~       @~~  Y      R|
|           E              ~    R~  REE           R     ~    |
|                                  R           E        ~    |
|  Y         ~    Y       R  R O                   ~         |
##############################################################

```

Hráč se narodí uprostřed mapy a kolem něj se vygeneruje zbytek mapy. Mapa se dá také načíst
ze souboru. Láva ubírá hráči brnění. Vlétnutí do bouře způsobí, že hráč ztratí kontrolu nad Jetpackem 
a spadne na zem. Pád také ubírá brnění. Hráč si může zvýšit brnění sbíráním R na mapě, které se čas 
od času přemístí. Hráč také může narazit na nepřítele E. Pokud ale bude jeho brnění dva a více krát 
silnější než nepřítelovo, nepřítel se zalekne a zmizí. Pokud ne, proběhne souboj. Stromy slouží pouze 
jako módní doplněk. Pokud se hráč chvíli nehýbe, působí na něj gravitace a začne pomalu slétávat dolů.
