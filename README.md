# Minesweeper in C

Een Minesweeper-spel voor in de terminal, geschreven in C. Je kiest een moeilijkheidsgraad, onthult velden door een rij en kolom in te geven en probeert alle mijnen te ontwijken.

## Features

- Drie moeilijkheidsgraden (Easy, Normal, Hard)
- Willekeurige mijnplaatsing bij elk spel
- Automatische berekening van het aantal naburige mijnen
- Flood reveal: bij het onthullen van een leeg veld (0) worden alle aangrenzende lege velden en hun buren automatisch onthuld (BFS met wachtrij)
- Winst- en verliesdetectie, met het volledige bord getoond op het einde
- Optie om opnieuw te spelen

## Moeilijkheidsgraden

| Keuze | Niveau | Bordgrootte | Mijnen |
|-------|--------|-------------|--------|
| `E`   | Easy   | 5 × 5       | 5      |
| `N`   | Normal | 10 × 10     | 15     |
| `H`   | Hard   | 15 × 15     | 30     |

## Compileren en uitvoeren

Je hebt een C-compiler nodig (bv. GCC).

```bash
gcc Minesweeper.c -o minesweeper
./minesweeper
```

Op Windows (MinGW):

```bash
gcc Minesweeper.c -o minesweeper.exe
minesweeper.exe
```

## Hoe te spelen

1. Kies bij het opstarten een moeilijkheidsgraad: `E`, `N` of `H`.
2. Geef telkens eerst de **rij** en dan de **kolom** in, gescheiden door een spatie (bv. `3 4`).
3. Een getal op een onthuld veld geeft aan hoeveel mijnen er in de 8 omliggende velden liggen.
4. Een leeg veld onthult automatisch zijn omgeving.
5. Je wint wanneer alle velden zonder mijn onthuld zijn. Je verliest wanneer je een mijn onthult.

### Legende

| Symbool | Betekenis             |
|---------|-----------------------|
| `?`     | Nog niet onthuld veld |
| `*`     | Mijn                  |
| `1`–`8` | Aantal naburige mijnen |
| (leeg)  | Geen mijnen in de buurt |

### Voorbeeld

```
==========WELCOME TO MINESWEEPER==========
Revealed board:
     1    2    3    4    5
 1 | ? || ? || ? || ? || ? |
 2 | ? || ? || ? || ? || ? |
 3 | ? || ? || ? || ? || ? |
 4 | ? || ? || ? || ? || ? |
 5 | ? || ? || ? || ? || ? |

Choose a row and colomn to reveal: first row then colomn (1-5 1-5):
```

## Projectstructuur

```
.
├── Minesweeper.c   # volledige broncode
└── README.md
```

### Overzicht van de functies

| Functie | Beschrijving |
|---------|--------------|
| `main()` | Vraagt de moeilijkheidsgraad en start het spel |
| `game(char difficulty)` | Initialiseert het bord, plaatst mijnen, bevat de hoofd-gameloop en het herstartmechanisme |
| `floodReveal(...)` | Onthult aangrenzende lege velden met een BFS-wachtrij |
| `checkWin(...)` | Controleert of alle niet-mijnvelden onthuld zijn |
| `flashScreen()` | "Wist" het scherm door 50 lege regels te printen |

## Bekende beperkingen

- Bij ongeldige invoer of coördinaten buiten het bord toont het spel een foutmelding, maar vraagt het niet automatisch opnieuw; de invoer wordt daarna toch verwerkt.
- Het eerste veld dat je onthult kan al een mijn zijn.
- Er is geen vlag-functie om mijnen te markeren.
- `main` is gedeclareerd als `void main()`; strikt volgens de C-standaard hoort dit `int main()` te zijn (GCC geeft hiervoor een waarschuwing).

## Mogelijke verbeteringen

- Invoervalidatie met `continue` en het leegmaken van de invoerbuffer
- Veilige eerste zet (mijnen pas plaatsen na de eerste onthulling)
- Vlaggen plaatsen en verwijderen
- Een timer en highscores
- Herstart via een lus in plaats van recursie

## Auteur

Gemaakt als schoolproject door Arne.
