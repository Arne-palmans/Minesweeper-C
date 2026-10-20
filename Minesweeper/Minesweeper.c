#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

void floodReveal(int rows, int cols, int board[rows][cols], int revealed[rows][cols], int startrow, int startcol);

void flashScreen();
int checkWin(int rows, int cols, int board[rows][cols], int revealed[rows][cols], int mines);

void game(char difficulty){
    srand(time(0)); //initialiseer random nummer generator
    uint8_t rows = 0;
    uint8_t colomns = 0;
    uint8_t mines = 0;
    switch (difficulty) //stel bordgrootte en aantal mijnen in op basis van moeilijkheidsgraad
        {
        case 'E':
            rows = 5;
            colomns = 5;
            mines = 5;
            break;
        case 'N':
            
            rows = 10;
            colomns = 10;
            mines = 15;
            break;
        case 'H':
            rows = 15;
            colomns = 15;
            mines = 30;
            break;
        default:
            break;
        }
    int board[rows][colomns]; //maak bord array aan

    for (int i = 0; i < rows; i++) //zet alle velden op 0
    {
        for (int j = 0; j < colomns; j++)
        {
            board[i][j] = 0; 
        }
    }

    //plaats mijnen
    for (int m = 0; m < mines; m++) //herhaal voor aantal mijnen
    {
        int rowm = rand() % rows; //kies random rij
        int colomnm = rand() % colomns; //kies random colomn
        if (board[rowm][colomnm] == -1) //als er al een mijn ligt dan kies opnieuw
        {
            m--;
        }
        else
        {
            board[rowm][colomnm] = -1; //plaats mijn op locatie (rowm,colomnm)

            //update buren nummers
            for (int i = -1; i <= 1; i++) 
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (
                        rowm + i >= 0 //controleer of de rij niet boven het bord ligt
                        && rowm + i < rows //controleer of de rij niet onder het bord ligt
                        && colomnm + j >= 0 //controleer of de colomn niet links van het bord ligt
                        && colomnm + j < colomns //controleer of de colomn niet rechts van het bord ligt
                        && board[rowm + i][colomnm + j] != -1 //controleer of er geen mijn ligt op de buur
                        ) 
                    {
                        board[rowm + i][colomnm + j]++; //verhoog buur met 1
                    }
                }
            }
        }
    }
    flashScreen();//wissen van het scherm

    //print leeg bord
    printf("==========WELCOME TO MINESWEEPER==========\nRevealed board:\n");
    for (int i = 0; i < rows; i++)
        {
            if (i == 0){
                printf("   ");
                for (int col = 0; col < colomns; col++) {
                    printf("  %d  ", col + 1); //print kolom nummers bovenaan
                }
                printf("\n");
            }
            
            for (int j = 0; j < colomns; j++)
            {
                if (j == 0){
                    printf(" %d ", i + 1); //print rij nummers links
                }
                printf("| ? |");
            }
            printf("\n");
        }

    int revealrow, revealcolomn; //maak variabelen voor onthulde rij en kolom aan
    int gameover = 0; //maak gameover aan

    int revealed[rows][colomns]; //array om onthulde velden bij te houden
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colomns; j++)
        {
            revealed[i][j] = 0; //initialiseer alle velden als niet onthuld
        }
    }


    //hoofd game loop
    while (1) 
    {
    printf("\nChoose a row and colomn to reveal: first row then colomn (1-%d 1-%d): ", rows, colomns);

    if (scanf("%d %d", &revealrow, &revealcolomn) != 2) { //controleer of invoer geldig is door te kijken of er twee getallen zijn ingevoerd
        printf("Invalid input. Please enter two numbers.\n");
        
    }
    revealrow = revealrow - 1; 
    revealcolomn = revealcolomn - 1;
    if (revealrow < 0 || revealrow >= rows || revealcolomn < 0 || revealcolomn >= colomns) {
        printf("Coordinates out of bounds, try again.\n");
    }

     if (board[revealrow][revealcolomn] == -1) { //als mijn is onthuld game over = 1
        revealed[revealrow][revealcolomn] = 1;
        gameover = 1;
        flashScreen();
    } else if (board[revealrow][revealcolomn] == 0) { //als 0 is onthuld start flood reveal
        floodReveal(rows, colomns, board, revealed, revealrow, revealcolomn);
        flashScreen();
    } else {
        revealed[revealrow][revealcolomn] = 1; //anders onthul alleen dat veld
        flashScreen();
    }

    if (gameover == 0) //als game niet over is
    { 
        if (checkWin(rows, colomns, board, revealed, mines)) { //controleer of speler gewonnen heeft
            flashScreen();
            printf("Congratulations! You win!\n");
            printf("Final board:\n");
            printf("   ");
            for (int col = 0; col < colomns; col++) {
                printf("  %d  ", col + 1); //print kolom nummers bovenaan
            }
            printf("\n");
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < colomns; j++)
                {
                    if (j == 0){
                        printf(" %d ", i + 1); //print rij nummers links
                    }
                    if (board[i][j] == -1)
                    {
                        printf("| * |");
                    }
                    else if (board[i][j] == 0)
                    {
                        printf("|   |");
                    }
                    else
                    {
                        printf("| %d |", board[i][j]);
                    }
                }
                printf("\n");
            }
            printf("\nwould you like to play again? (Y/N): ");
            char playagain;
            scanf(" %c", &playagain);
            if (playagain == 'Y' || playagain == 'y')
            {
                game(difficulty);
            }
            else
            {
                printf("Thanks for playing!\n");
                exit(0);
            }
        } \
         //print het bord met onthulde velden
        else {
            printf("Revealed board:\n");
            printf("   ");
            for (int col = 0; col < colomns; col++) {
                printf("  %d  ", col + 1); //print kolom nummers bovenaan
            }
            printf("\n");
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < colomns; j++)
                {
                    if (j == 0){
                        printf(" %d ", i + 1); //print rij nummers links
                    }
                    if (revealed[i][j]) //als revealed waar is dan toon waarde
                    {
                        if (board[i][j] == -1)
                        {
                            printf("| * |");
                        }
                        else if (board[i][j] == 0)
                        {
                            printf("|   |");
                        }
                        else
                        {
                            printf("| %d |", board[i][j]);
                        }
                    }
                    else
                    {
                        printf("| ? |");
                    }
                }
                printf("\n");
            }
        }
    }
    else { //als game over is
        flashScreen();
        printf("Game Over! You hit a mine.\n");
        printf("Final board:\n"); //laat het volledige bord zien
        printf("   ");
        for (int col = 0; col < colomns; col++) {
            printf("  %d  ", col + 1); //print kolom nummers bovenaan
        }
        printf("\n");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < colomns; j++)
            {
                if (j == 0){
                    printf(" %d ", i + 1); //print rij nummers links
                }
                if (board[i][j] == -1) 
                {
                    printf("| * |");
                }
                else
                {
                    printf("| %d |", board[i][j]);
                }
            }
            printf("\n");
        }
        printf("\nwould you like to play again? (Y/N): ");
        char playagain;
        scanf(" %c", &playagain);
        if (playagain == 'Y' || playagain == 'y')
        {
            game(difficulty);
        }
        else
        {
            printf("Thanks for playing!\n");
            exit(0);
        }
        
    }
    }
}
int checkWin(int rows, int cols, int board[rows][cols], int revealed[rows][cols], int mines) //controleer of speler gewonnen heeft
{
    int revealedNonMines = 0; //aantal onthulde niet mijnen
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (revealed[i][j] && board[i][j] != -1) //als veld onthuld is en geen mijn is verhoog teller
            {
                revealedNonMines++;
            }
        }
    }
    return revealedNonMines == (rows * cols - mines); //als aantal onthulde niet mijnen gelijk is aan totaal aantal niet mijnen dan heeft de speler gewonnen
}

//features:
void floodReveal(int rows, int cols, int board[rows][cols], int revealed[rows][cols], int startrow, int startcol) //onthul alle aangrenzende nullen en hun buren
{
    int queuesize = rows * cols; //maximale grootte van de wachtrij
    int queuerow[queuesize]; //queue voor rijen
    int queuecol[queuesize];  //queue voor kolommen
    int head = 0; //lezen
    int tail = 0; //schrijven

    if (revealed[startrow][startcol]) return; //als startpositie al onthuld is dan stop
    revealed[startrow][startcol] = 1; //markeer startpositie als onthuld
    queuerow[tail] = startrow; //voeg startrij toe aan wachtrij
    queuecol[tail] = startcol; //voeg startkolom toe aan wachtrij
    tail++; //verplaats staart naar voren

    while (head < tail)//zolang er items in de wachtrij zijn
    {
        int floodrow = queuerow[head]; //haal rij uit wachtrij
        int floodcolom = queuecol[head]; //haal kolom uit wachtrij
        head++; //verplaats hoofd naar voren
        if (board[floodrow][floodcolom] == 0)//als het een 0 is dan onthul buren
        {
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++) 
                {
                    int nextrow = floodrow + k, nextcol = floodcolom + l; //nextrow = nieuwe rij, nextcol = nieuwe kolom
                    if (nextrow >= 0 //controleer of nieuwe rij niet boven bord ligt
                        && nextrow < rows && nextcol >= 0 //controleer of nieuwe kolom niet links van bord ligt
                        && nextcol < cols //controleer of nieuwe kolom niet rechts van bord ligt
                        && !revealed[nextrow][nextcol] //controleer of buur nog niet onthuld is
                        ) 
                    {
                        revealed[nextrow][nextcol] = 1; //markeer buur als onthuld
                        if (board[nextrow][nextcol] == 0) //als buur ook 0 is dan voeg toe aan wachtrij
                        {
                            queuerow[tail] = nextrow; queuecol[tail] = nextcol; tail++;
                        }
                    }
                }
            }
        }
    }
}
void flashScreen(){ //wissen van het scherm
    for (int i = 0; i < 50; i++){
        printf("\n");
    }
}
//main functie
void main(){
    char difficulty;
    printf("Welcome to minesweeper:\nChoose your difficulty\nEasy = E, Normal = N, Hard = H\n");
    scanf("%c", &difficulty);
    game(difficulty); //start het spel met gekozen moeilijkheidsgraad
    return;
}