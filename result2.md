# Experiment 1: Optimalne mnozstvo
## Vysledky:
### Informacie o zariadeniach:
Zariadenie | Pocet | Kapacita | Max rada | Priemerna rada
:--- | :---: | :---: | ---: | ---:
Mlyn:             | 1 | 100 kg | 0 | 0.00
Varný kotol:      | 1 | 800 kg | 15 | 5.24
Scedovacia kad:   | 1 | 800 kg | 0 | 0.00
Odstrediva kad:   | 1 | 800 kg | 0 | 0.00
Mladinova panev:  | 1 | 800 kg | 0 | 0.00
Kvasny tank:      | 5 | 200 kg | 62 | 23.05
Leziacky tank:    | 6 | 600 kg | 17 | 7.65
---
### Vstupne suroviny:
Surovina | Hmotnost
:--- | ---:
Slad:  | 12000 kg
Chmel: | 120.00 kg
---
### Spotrebované suroviny: 
Surovina | Hmotnost
:--- | ---:
Slad:  | 6200 kg
Chmel: | 84.32 kg
Voda:     | 43400 l
Kvasnice: | 210 l
---
### Medziprodukty a odpad: 
Typ | Hmotnost
:--- | ---:
Mlato:                | 7440 kg
Kal:                  | 186 kg
Pokazeny slad:         | 0 kg
Kontaminovane pivo:   | 0 l
---
### Vyrobene pivo:
Typ | Hmotnost
:--- | ---:
Vycap 10:  | 10200 l
Leziak 12: | 8400 l
#### Posledna varka: 321. den, 16:41
---

## Programove statistiky:
~~~
+----------------------------------------------------------+
| STORE Mlyn                                               |
+----------------------------------------------------------+
|  Capacity = 100  (0 used, 100 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 62                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 100                             |
|  Average used capacity = 0.0842703                       |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Varny kotol                                        |
+----------------------------------------------------------+
|  Capacity = 800  (0 used, 800 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 124                        |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 800                             |
|  Average used capacity = 34.051                          |
+----------------------------------------------------------+
  Input queue 'Varny kotol.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  112                                           |
|  Outcoming  112                                          |
|  Current length = 0                                      |
|  Maximal length = 16                                     |
|  Average length = 0.261919                               |
|  Minimal time = 15                                       |
|  Maximal time = 5172.61                                  |
|  Average time = 1131.49                                  |
|  Standard deviation = 1311.28                            |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Scedovacia Kad                                     |
+----------------------------------------------------------+
|  Capacity = 800  (0 used, 800 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 62                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 800                             |
|  Average used capacity = 21.5278                         |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Odstrediva Kad                                     |
+----------------------------------------------------------+
|  Capacity = 800  (0 used, 800 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 62                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 680                             |
|  Average used capacity = 7.84226                         |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Mladinova panev                                    |
+----------------------------------------------------------+
|  Capacity = 800  (0 used, 800 free)                      |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 62                         |
|  Minimal used capacity = 0                               |
|  Maximal used capacity = 680                             |
|  Average used capacity = 13.0704                         |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Kvasny tank                                        |
+----------------------------------------------------------+
|  Capacity = 1000  (1000 used, 0 free)                    |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 170                        |
|  Minimal used capacity = 200                             |
|  Maximal used capacity = 1000                            |
|  Average used capacity = 995.583                         |
+----------------------------------------------------------+
  Input queue 'Kvasny tank.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  198                                           |
|  Outcoming  158                                          |
|  Current length = 40                                     |
|  Maximal length = 63                                     |
|  Average length = 26.3122                                |
|  Minimal time = 4.07049                                  |
|  Maximal time = 180903                                   |
|  Average time = 76102.9                                  |
|  Standard deviation = 45870.1                            |
+----------------------------------------------------------+

+----------------------------------------------------------+
| STORE Leziacky tank                                      |
+----------------------------------------------------------+
|  Capacity = 3600  (3600 used, 0 free)                    |
|  Time interval = 0 - 483840                              |
|  Number of Enter operations = 37                         |
|  Minimal used capacity = 600                             |
|  Maximal used capacity = 3600                            |
|  Average used capacity = 3310.38                         |
+----------------------------------------------------------+
  Input queue 'Leziacky tank.Q'
+----------------------------------------------------------+
| QUEUE Q                                                  |
+----------------------------------------------------------+
|  Time interval = 0 - 483840                              |
|  Incoming  48                                            |
|  Outcoming  30                                           |
|  Current length = 18                                     |
|  Maximal length = 18                                     |
|  Average length = 7.89831                                |
|  Minimal time = 3606.44                                  |
|  Maximal time = 157831                                   |
|  Average time = 82515.9                                  |
+----------------------------------------------------------+

~~~