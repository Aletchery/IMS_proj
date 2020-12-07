# Experiment 2: Zdvojnasobenie
## Vysledky:
### Informacie o zariadeniach:
Zariadenie | Pocet | Kapacita | Max rada | Priemerna rada
:--- | :---: | :---: | ---: | ---:
Mlyn:             | 1 | 100 kg | 0 | 0.00
Varný kotol:      | 2 | 800 kg | 12 | 4.67
Scedovacia kad:   | 1 | 800 kg | 4 | 1.67
Odstrediva kad:   | 1 | 800 kg | 0 | 0.00
Mladinova panev:  | 1 | 800 kg | 0 | 0.00
Kvasny tank:      | 10 | 200 kg | 60 | 22.59
Leziacky tank:    | 12 | 600 kg | 6 | 1.63
---
### Vstupne suroviny:
Surovina | Hmotnost
:--- | ---:
Slad:  | 2400 kg
Chmel: | 60.00 kg
---
### Spotrebované suroviny: 
Surovina | Hmotnost
:--- | ---:
Slad:  | 2400 kg
Chmel: | 32.64 kg
Voda:     | 16800 l
Kvasnice: | 81 l
---
### Medziprodukty a odpad: 
Typ | Hmotnost
:--- | ---:
Mlato:                | 2880 kg
Kal:                  | 72 kg
Pokazeny slad:         | 0 kg
Kontaminovane pivo:   | 0 l
---
### Vyrobene pivo:
Typ | Hmotnost
:--- | ---:
Vycap 10:  | 8400 l
Leziak 12: | 7800 l
#### Posledna varka: 189. den, 19:26
---

## Programove statistiky:
~~~
+----------------------------------------------------------+
| STORE Mlyn                                               |
+----------------------------------------------------------+
|  Capacity = 100  (0 used, 100 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 24                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 100                             |
|  Average used capacity = 0.0330491                       |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Varny kotol                                        |
+----------------------------------------------------------+
|  Capacity = 1600  (0 used, 1600 free)                    |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 48                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 1600                            |
|  Average used capacity = 13.1398                         |
+----------------------------------------------------------+
  Input queue 'Varny kotol.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  39                                            |
|  Outcoming  39                                           |
|  Current length = 0                                      |
|  Maximal length = 13                                     |
|  Average length = 0.0447259                              |
|  Minimal time = 5.2721                                   |
|  Maximal time = 1968.34                                  |
|  Average time = 554.876                                  |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Scedovacia Kad                                     |
+----------------------------------------------------------+
|  Capacity = 800  (0 used, 800 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 24                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 800                             |
|  Average used capacity = 8.33333                         |
+----------------------------------------------------------+
  Input queue 'Scedovacia Kad.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  22                                            |
|  Outcoming  22                                           |
|  Current length = 0                                      |
|  Maximal length = 5                                      |
|  Average length = 0.0215501                              |
|  Minimal time = 64.1963                                  |
|  Maximal time = 968.888                                  |
|  Average time = 473.946                                  |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Odstrediva Kad                                     |
+----------------------------------------------------------+
|  Capacity = 800  (0 used, 800 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 24                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 680                             |
|  Average used capacity = 3.03571                         |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Mladinova panev                                    |
+----------------------------------------------------------+
|  Capacity = 800  (0 used, 800 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 24                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 680                             |
|  Average used capacity = 5.05952                         |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Kvasny tank                                        |
+----------------------------------------------------------+
|  Capacity = 2000  (0 used, 2000 free)                    |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 81                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 2000                            |
|  Average used capacity = 482.143                         |
+----------------------------------------------------------+
  Input queue 'Kvasny tank.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  62                                            |
|  Outcoming  62                                           |
|  Current length = 0                                      |
|  Maximal length = 61                                     |
|  Average length = 6.20905                                |
|  Minimal time = 13157                                    |
|  Maximal time = 96600                                    |
|  Average time = 48454.6                                  |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Leziacky tank                                      |
+----------------------------------------------------------+
|  Capacity = 7200  (0 used, 7200 free)                    |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 27                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 7200                            |
|  Average used capacity = 2674.4                          |
+----------------------------------------------------------+
  Input queue 'Leziacky tank.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  14                                            |
|  Outcoming  14                                           |
|  Current length = 0                                      |
|  Maximal length = 7                                      |
|  Average length = 0.765956                               |
|  Minimal time = 6950.71                                  |
|  Maximal time = 44768.1                                  |
|  Average time = 26471.5                                  |
+----------------------------------------------------------+

~~~