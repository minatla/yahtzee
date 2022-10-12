#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RULES 1
#define GAMES 2
#define EXIT 3
#define ROLLS 3
#define CATEGORIES 13
#define DICE 5
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define THREEKIND 7
#define FOURKIND 8
#define FULLHOUSE 9
#define SMSTRAIGHT 10
#define LGSTRAIGHT 11
#define YAHTZEE 12
#define CHANCE 13
#define TURNS 13
//Yahtzee 4
#define COLS 2
#define COL 1
#define ZERO 0

void gameRules();
void displayExplicitDice();
void clearScreen();
int displayGameMenu();
void displayRandomDice();
int rollDie();
void initializeDice();
void playGame();
void displayDice(int dice[]);
void resetKeep(int keep[]);
void rollDice(int dice[], int keep[]);
//Yahtzee 4
void initializeScores(int scoreCard[CATEGORIES][COLS]);
int selectCategory();
void selectDice(int dice[DICE], int keep[DICE]);
void updateScores(int scoreCard[CATEGORIES][COLS], int category);
void displayScoreCard(int scores[CATEGORIES][COLS]);
void displayUpperSection(int scores[CATEGORIES][COLS]);
void displayLowerSection(int scores[CATEGORIES][COLS]);

enum scores{one, two, three, four, five, six, threekind, fourkind, fullhouse, smstraight, lgstraight, yahtzee, chance};

int main() {
    /*gameRules();
    clearScreen();
    displayExplicitDice();*/

    int play = 1;
    srand(time(0));

    while(play) {
        int dgm = displayGameMenu();
        switch(dgm) {
            case RULES:
                gameRules();
                break;
            case GAMES:
                clearScreen();
                //displayRandomDice();
                playGame();
                break;
            case EXIT:
                printf("\nThank you for playing!\n");
                play = 0;
                break;
            default:
                printf("Incorrect option, hit enter and try again\n");
                char enter;
                scanf("%c", &enter);
        }
    }
    return 0;
}

// Shows out game rules to player
void gameRules() {
    clearScreen();
    printf("\t\t\t\tLET'S PLAY YAHTZEE!!!\n");
    printf("\nRULES OF THE GAME:\n");
    printf("\t1. The scorecard used for Yahtzee is composed of an upper section and a lower section.\n");
    printf("\t2. A total of 13 scoring combinations are divided amongst the sections.\n");
    printf("\t3. The upper section consists of boxes that are scored by summing the value of the dice matching the faces of \nthe box.\n");
    printf("\t4. If a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12.\n");
    printf("\t5. Once a player has chosen to score a box, it may not be changed and the combination is no longer in play for \nfuture rounds.\n");
    printf("\t6. If the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added \nto the players overall score as a bonus. The lower section contains a number of poker like combinations.\n");
}

// Clears screen on enter
void clearScreen() {
    printf("\n Hit <ENTER> to continue!\n");
    char enter;
    scanf("%c", &enter);
    system("cls");
    //system("clear");
}

// Yahtzee gameboard
void displayExplicitDice() {
    int i;
  printf("\n|"); //first row
    for(i=0;i<39;i++)
    {
        printf("-");
    }
    printf("|\n");
    printf("|\t|\t|\t|\t|\t|\n");
    printf("|   1   |   2   |   3   |   4   |   5   ");
    printf("|\n");
    printf("|\t|\t|\t|\t|\t|\n");
    printf("|"); //last row
    for(i=0;i<39;i++)
    {
        printf("-");
    }
    printf("|\n");

    }

// FIGURE 3 FOR PT2
void displayRandomDice() {
    int numRolls;
    int firstDie;
    int secondDie;
    int thirdDie;
    int fourthDie;
    int fifthDie;

    for(numRolls=0; numRolls<ROLLS; numRolls++) {
        firstDie = rollDie();
        secondDie = rollDie();
        thirdDie = rollDie();
        fourthDie = rollDie();
        fifthDie = rollDie();

        printf("|"); //first row
        for(int i=0;i<39;i++)
        {
            printf("-");
        }
        printf("|\n");
        printf("|\t|\t|\t|\t|\t|\n");
        printf("|   %d   |   %d   |   %d   |   %d   |   %d   ", firstDie, secondDie, thirdDie, fourthDie, fifthDie);
        printf("|\n");
        printf("|\t|\t|\t|\t|\t|\n");
        printf("|"); //last row
        for(int i=0;i<39;i++)
        {
            printf("-");
        }
        printf("|\n");
    }
}

//Game Menu
int displayGameMenu() {
    int select = 0;

    do {
        printf("\n\n\t\t\t\t LET'S PLAY YAHTZEE!!!\n");
        printf("%d", RULES);
        printf(". Display Game Rules\n");
        printf("%d", GAMES);
        printf(". Start a game of Yahtzee\n");
        printf("%d", EXIT);
        printf(". Exit\n");
        scanf("%d", &select);
    } while(select != RULES && select != GAMES && select != EXIT);
    return select;
}

int rollDie() {
    int dieValue = 0;
    dieValue = 1 + (rand() % 6);
    return dieValue;
}

void initializeDice() {
    int dice[DICE];
    int die;

    for (die=0; die < DICE; die++) {
        dice[die] = 0;
    }
}

//Option 2 of Game menu
void playGame() {
    int roll;
    int turn;
    int dice[DICE];
    int keep[DICE];
    int scoreCard[CATEGORIES][COLS];
    int category;

    initializeScores(scoreCard);

    for (turn=0; turn < TURNS; turn++)
    {
        int current = turn + 1;

        printf("Turn %d of game\n\n", current);

        initializeDice(dice);

        resetKeep(keep);

        for (roll=0; roll < ROLLS; roll++) {
            printf("Rolling the dice...\n");
            rollDice(dice, keep);
            displayDice(dice);
            if (roll < COLS) {
                selectDice(dice, keep);
            }
        }
        category = selectCategory();
        updateScores(scoreCard, category);
        displayScoreCard(scoreCard);
    }

}

void displayDice(int dice[DICE]) {
    int die;
    char enter;
    int i;

    //shows playGame basically
    for (i=0;i < 5; i++){
        printf("+-------+ ");
    }
    printf("\n");
    printf("|\t| |       | |       | |       | |       |\n");
    for (die=0; die < DICE; die++) {
        //dice[die] = rollDie();
        printf("|   %d   | ", dice[die]);
    }
    printf("\n");
    printf("|\t| |       | |       | |       | |       |\n");
    for (i=0;i < 5; i++){
        printf("+-------+ ");
    }
    printf("\n\n");

    //scanf("%c", &enter);
    system("pause");
}

void resetKeep(int keep[DICE]) {
    int die;

    for (die=0; die < DICE; die++) {
        keep[die] = 0;
    }
}

void rollDice(int dice[DICE], int keep[DICE]) {
    int die;

    for (die=0; die < DICE; die++) {
        if (keep[die] == 0) {
            dice[die] = rollDie();
        }
    }
}

//Yahtzee 4
void initializeScores(int scoreCard[CATEGORIES][COLS]) {
    int row;
    int col;

    for (row = 0; row < CATEGORIES; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            if (col == 0)
            {
                scoreCard[row][col] = row;
            }
            else
            {
                scoreCard[row][col] = 0;
            }
        }
    }

}

int selectCategory() {
    int select;

    printf("\tSelect category for dice\n");
    printf("%d. Ones\n", ONE);
    printf("%d. Twos\n", TWO);
    printf("%d. Threes\n", THREE);
    printf("%d. Fours\n", FOUR);
    printf("%d. Fives\n", FIVE);
    printf("%d. Sixes\n", SIX);
    printf("%d. Three of a kind\n", THREEKIND);
    printf("%d. Four of a kind\n", FOURKIND);
    printf("%d. Full house\n", FULLHOUSE);
    printf("%d. Small straight\n", SMSTRAIGHT);
    printf("%d. Large straight\n", LGSTRAIGHT);
    printf("%d. Yahtzee\n", YAHTZEE);
    printf("%d. Chance\n\n", CHANCE);

    scanf("%d", &select);
    fflush(stdin);

    return select;
}

void selectDice(int dice[DICE], int keep[DICE]) {
    int die = 0;
    char data[10];
    char* value;
    int valid = 0;

    resetKeep(keep);
    printf("Select dice to keep, enter values 1 through 5 with spaces between numbers\n");
    fgets(data, 10, stdin);
    value = strtok(data, " ");

    while (value != NULL)
    {
        valid = 0;

        while (!valid)
        {
            switch(*value)
            {
                case '1':
                    printf("die 1 selected to keep\n");
                    keep[0] = 1;
                    valid = 1;
                    break;
                case '2':
                    printf("die 2 selected to keep\n");
                    keep[1] = 1;
                    valid = 1;
                    break;
                case '3':
                    printf("die 3 selected to keep\n");
                    keep[2] = 1;
                    valid = 1;
                    break;
                case '4':
                    printf("die 4 selected to keep\n");
                    keep[3] = 1;
                    valid = 1;
                    break;
                case '5':
                    printf("die 5 selected to keep\n");
                    keep[4] = 1;
                    valid = 1;
                    break;
                default:
                    printf("Invalid option, try again\n");
                    valid = 1;
                    break;
            }
        }
        value = strtok(NULL, " ");
    }
}

void updateScores(int scoreCard[CATEGORIES][COLS], int category) {

    //printf("%d is category\n", category);
    switch(category) {
        case ONE:
            printf("Scoring Ones...\n");
            break;
        case TWO:
            printf("Scoring Twos...\n");
            break;
        case THREE:
            printf("Scoring Threes...\n");
            break;
        case FOUR:
            printf("Scoring Fours...\n");
            break;
        case FIVE:
            printf("Scoring Fives...\n");
            break;
        case SIX:
            printf("Scoring Sixes...\n");
            break;
        case THREEKIND:
            printf("Scoring Three of a kind...\n");
            break;
        case FOURKIND:
            printf("Scoring Four of a kind...\n");
            break;
        case FULLHOUSE:
            printf("Scoring Full House...\n");
            break;
        case SMSTRAIGHT:
            printf("Scoring Small straight...\n");
            break;
        case LGSTRAIGHT:
            printf("Scoring Large straight...\n");
            break;
        case YAHTZEE:
            printf("Scoring Yahtzee...\n");
            break;
        case CHANCE:
            printf("Scoring Chance...\n");
            break;
        default:
            printf("Invalid option, try again\n");
            break;
    }
}

void displayScoreCard(int scores[CATEGORIES][COLS]) {
    printf("\n\tYAHTZEE SCORECARD\n");
    printf("+-----------------+-----------+\n"); //17, 11

    displayUpperSection(scores);
    displayLowerSection(scores);

    printf("+-----------------+-----------+\n");
    printf("| TOTAL (upper)   |      %d    |\n", ZERO);
    printf("+-----------------+-----------+\n");
    printf("| GRAND TOTAL     |      %d    |\n", ZERO);
    printf("+-----------------+-----------+\n");
}

void displayUpperSection(int scores[CATEGORIES][COLS]) {
    printf("+-----------------+-----------+\n");
    printf("| UPPER SECTION   |   SCORE   |\n");
    printf("+-----------------+-----------+\n");
    printf("| ONES            |      %d    |\n", scores[one][COL]);
    printf("+-----------------+-----------+\n");
    printf("| TWOS            |      %d    |\n", scores[two][COL]);
    printf("+-----------------+-----------+\n");
    printf("| THREES          |      %d    |\n", scores[three][COL]);
    printf("+-----------------+-----------+\n");
    printf("| FOURS           |      %d    |\n", scores[four][COL]);
    printf("+-----------------+-----------+\n");
    printf("| FIVES           |      %d    |\n", scores[five][COL]);
    printf("+-----------------+-----------+\n");
    printf("| SIXES           |      %d    |\n", scores[six][COL]);
    printf("+-----------------+-----------+\n");
    printf("| TOTAL SCORE     |      %d    |\n", ZERO);
    printf("+-----------------+-----------+\n");
    printf("| BONUS           |      %d    |\n", ZERO);
    printf("+-----------------+-----------+\n");
    printf("| SCORE           |      %d    |\n", ZERO);
    printf("+-----------------+-----------+\n");
}

void displayLowerSection(int scores[CATEGORIES][COLS]) {
    printf("+-----------------+-----------+\n");
    printf("| LOWER SECTION   |   SCORE   |\n");
    printf("+-----------------+-----------+\n");
    printf("| THREE OF A KIND |      %d    |\n", scores[threekind][COL]);
    printf("+-----------------+-----------+\n");
    printf("| FOUR OF A KIND  |      %d    |\n", scores[fourkind][COL]);
    printf("+-----------------+-----------+\n");
    printf("| FULL HOUSE      |      %d    |\n", scores[fullhouse][COL]);
    printf("+-----------------+-----------+\n");
    printf("| SM STRAIGHT     |      %d    |\n", scores[smstraight][COL]);
    printf("+-----------------+-----------+\n");
    printf("| LG STRAIGHT     |      %d    |\n", scores[lgstraight][COL]);
    printf("+-----------------+-----------+\n");
    printf("| YAHTZEE         |      %d    |\n", scores[yahtzee][COL]);
    printf("+-----------------+-----------+\n");
    printf("| CHANCE          |      %d    |\n", scores[chance][COL]);
    printf("+-----------------+-----------+\n");
    printf("| TOTAL (lower)   |      %d    |\n", ZERO);
}
