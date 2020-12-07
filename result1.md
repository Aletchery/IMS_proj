# Referencny experiment
## Vysledky:
### Informacie o zariadeniach:
Zariadenie | Pocet | Kapacita | Max rada | Priemerna rada
:--- | :---: | :---: | ---: | ---:
Mlyn:             | 1 | 100 kg | 0 | 0.00
Varný kotol:      | 1 | 800 kg | 15 | 5.85
Scedovacia kad:   | 1 | 800 kg | 0 | 0.00
Odstrediva kad:   | 1 | 800 kg | 0 | 0.00
Mladinova panev:  | 1 | 800 kg | 0 | 0.00
Kvasny tank:      | 5 | 200 kg | 62 | 24.79
Leziacky tank:    | 6 | 600 kg | 8 | 2.85
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
#### Posledna varka: 315. den, 14:46
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
|  Average used capacity = 0.0331617                       |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Varny kotol                                        |
+----------------------------------------------------------+
|  Capacity = 800  (0 used, 800 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 48                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 800                             |
|  Average used capacity = 13.1691                         |
+----------------------------------------------------------+
  Input queue 'Varny kotol.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  42                                            |
|  Outcoming  42                                           |
|  Current length = 0                                      |
|  Maximal length = 16                                     |
|  Average length = 0.110865                               |
|  Minimal time = 15                                       |
|  Maximal time = 5172.61                                  |
|  Average time = 1277.17                                  |
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
|  Capacity = 1000  (0 used, 1000 free)                    |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 81                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 1000                            |
|  Average used capacity = 482.143                         |
+----------------------------------------------------------+
  Input queue 'Kvasny tank.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  74                                            |
|  Outcoming  74                                           |
|  Current length = 0                                      |
|  Maximal length = 63                                     |
|  Average length = 12.8408                                |
|  Minimal time = 12857.6                                  |
|  Maximal time = 180903                                   |
|  Average time = 83958.1                                  |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Leziacky tank                                      |
+----------------------------------------------------------+
|  Capacity = 3600  (0 used, 3600 free)                    |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 27                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 3600                            |
|  Average used capacity = 2702.1                          |
+----------------------------------------------------------+
  Input queue 'Leziacky tank.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  20                                            |
|  Outcoming  20                                           |
|  Current length = 0                                      |
|  Maximal length = 9                                      |
|  Average length = 2.48567                                |
|  Minimal time = 3606.44                                  |
|  Maximal time = 117083                                   |
|  Average time = 60133.3                                  |
+----------------------------------------------------------+

~~~