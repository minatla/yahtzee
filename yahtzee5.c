#include "yahtzee.h"

int main()
{
    // while loop control variable
    int play = 1;

    // seed the random function
    srand ((unsigned int) time (NULL));

    // continue to loop until the player quits or the game ends
    while (play)
    {
        switch (displayGameMenu())
        {
            case RULES:
                // call function gameRules
                gameRules();
                break;
            case GAMES:
                // call function clearScreen()
                clearScreen();
                // call function displayRandomDice
//                displayRandomDice();
                // call function play
                playGame();
                break;
            case EXIT:
                printf ("Thank you for playing!\n");
                play = 0;
                break;
            default:
                printf ("Incorrect option, hit enter and try again\n");
                char enter;
                scanf("%c", &enter );
                break;
        }
    }

    // program executed successfully
    return 0;
}

// gameRules function displays the Yahtzee and rules of the game
void gameRules ()
{
	printf ("\t\t\t\tLET'S PLAY YAHTZEE!!! \n\n");
	printf ("RULES OF THE GAME:\n");
    printf ("\t1. The scorecard used for Yahtzee is composed of an upper section and a lower section.\n");
    printf ("\t2. A total of 13 scoring combinations are divided amongst the sections. \n");
    printf ("\t3. The upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\n");
    printf ("\t4. If a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12. \n");
    printf ("\t5. Once a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.\n");
    printf ("\t6. If the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added \n");
    printf ("\tto the players overall score as a bonus. The lower section contains a number of poker like combinations.\n");
}

// function displayExplicitDice displays a hardcoded version of a rolled dice
void displayExplicitDice()
{
    printf("|---------------------------------------|\n");
    printf("|       |       |       |       |       |\n");
    printf("|   1   |   2   |   3   |   4   |   5   |\n");
    printf("|       |       |       |       |       |\n");
    printf("|---------------------------------------|\n");
}

// function displayRandomDice displays a randomly generated dice for three rolls
void displayRandomDice()
{
    // looping variable
    int roll;
    int die1;
    int die2;
    int die3;
    int die4;
    int die5;

    for(roll = 0; roll < ROLLS; roll++)
    {
        die1 = rollDie();
        die2 = rollDie();
        die3 = rollDie();
        die4 = rollDie();
        die5 = rollDie();

        printf("|---------------------------------------|\n");
        printf("|       |       |       |       |       |\n");
        printf("|   %d   |   %d   |   %d   |   %d   |   %d   |\n", die1, die2, die3, die4, die5);
        printf("|       |       |       |       |       |\n");
        printf("|---------------------------------------|\n");
    }
}

// clears the screen
void clearScreen()
{
    printf("\n\t\t\t\tHit <ENTER> to continue!\n");

	char enter;
	scanf("%c", &enter );

	// send the clear screen command Windows
    system("cls");
    // send the clear screen command for UNIX flavor operating systems
//    system("clear");
}

// presents a menu to the player
int displayGameMenu()
{
    int select = 0;

    do
    {
        printf ("\n\n\t\t\t\tLET'S PLAY YAHTZEE!!! \n\n");
        printf ("%d. Display Game Rules\n", RULES);
        printf ("%d. Start a game of Yahtzee\n", GAMES);
        printf ("%d. Exit\n", EXIT);

        scanf ("%d", &select);

    } while ((select < RULES) && (select > EXIT));

    return select;
}

// randomly rolls a die
int rollDie()
{
    int dieValue = 0;

    dieValue = rand () % 6 + 1;

    return dieValue;
}

void initializeDice(int dice[DICE])
{
    int die;

    for(die = 0; die < DICE; die++)
    {
        dice[die] = 0;
    }
}

void playGame()
{
    int roll;
    int turn;
    int dice[DICE];
    int keep[DICE];
    int scoreCard[CATEGORIES][COLS];
    int category;

    // initialize the score card before the game starts
    initializeScores(scoreCard);

    // continue to loop until game is over
    for(turn = 0; turn < TURNS; turn++)
    {
        int current = turn + 1;

        printf("Turn %d of game\n\n", current);

        // for each turn reset the keep[] and dice arrays
        initializeDice(dice);

        // reset the dice the player wants to keep
        resetKeep(keep);

        fflush(stdin);

        // one turn
        for(roll = 0; roll < ROLLS; roll++)
        {
            // roll the dice
            printf("Rolling the dice...\n");
            rollDice(dice, keep);

            // display the current roll
            displayDice(dice);

            // only request dice selection for roll one and two
            if(roll < TWO)
                // prompt the user to select the dice to keep
                selectDice(dice, keep);
        }

        category = selectCategory();
        updateScores(scoreCard, category, dice);
        displayScoreCard(scoreCard);

    }
}

void displayDice(int dice[DICE])
{
    int die;
    char enter;

    printf("+-------+ +-------+ +-------+ +-------+ +-------+\n");
    printf("|       | |       | |       | |       | |       |\n");

    for(die = 0; die < DICE; die++)
    {
        printf("|   %d   | ", dice[die]);
    }

    printf("\n");
    printf("|       | |       | |       | |       | |       |\n");
    printf("+-------+ +-------+ +-------+ +-------+ +-------+\n");

//    scanf ("%c", &enter);
}

void resetKeep(int keep[DICE])
{
    int die;

    // loop through the five dice
    for(die = 0; die < DICE; die++)
    {
        // set each die to 0 meaning false
        keep[die] = 0;
    }
}

void rollDice(int dice[DICE], int keep[DICE])
{
    int die;

    // loop through the five dice
    for(die = 0; die < DICE; die++)
    {
        // only roll dice that have not been selected to keep
        if(keep[die] == 0)
        {
            dice[die] = rollDie();
        }
    }
}

// Assignment 4 new functions

void initializeScores(int scoreCard[CATEGORIES][COLS])
{
    int row;
    int col;

    for(row = 0; row < CATEGORIES; row++)
    {
        for(col = 0; col < COLS; col++)
        {
            // the first col should be set to values 0 - 12, use the looping variable as the value
            if(col == ZERO)
                scoreCard[row][col] = row;
            else
                scoreCard[row][col] = ZERO;
        }
    }
}

int selectCategory()
{
    int select;

    printf("\n\tSelect category for dice\n");
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
    printf("%d. Chance\n", CHANCE);

    scanf("%d", &select);

    fflush(stdin);

    return select;
}

void selectDice(int dice[DICE], int keep[DICE])
{
    int die = 0;
    char data[20];
    char * value;
    // looping control to force user to select valid die
    int valid = 0;

    // call resetKeep() for each request since users can change their mind for each roll
    resetKeep(keep);

    // prompt the user
    printf("\nSelect dice to keep, enter values 1 through 5 with spaces between numbers\n");

    // read the input
    fgets(data, 20, stdin);

    // parse the string into each value
    // priming read for first value
    value = strtok(data, " ");

    // loop to end of input
    while(value != NULL )
    {
        valid = 0;

        while(!valid)
        {
            switch(*value)
            {
                case '1':
                    printf("die %d selected to keep\n", ONE);
                    keep[0] = 1;
                    valid = 1;
                    break;
                case '2':
                    printf("die %d selected to keep\n", TWO);
                    keep[1] = 1;
                    valid = 1;
                    break;
                case '3':
                    printf("die %d selected to keep\n", THREE);
                    keep[2] = 1;
                    valid = 1;
                    break;
                case '4':
                    printf("die %d selected to keep\n", FOUR);
                    keep[3] = 1;
                    valid = 1;
                    break;
                case '5':
                    printf("die %d selected to keep\n", FIVE);
                    keep[4] = 1;
                    valid = 1;
                    break;
                default:
                    printf("%s invalid option, try again\n", *value);
                    valid = 1;
            }
        }

        value = strtok(NULL, " ");
    }
}

void updateScores(int scoreCard[CATEGORIES][COLS], int category, int dice[DICE]) {

    //printf("%d is category\n", category);
    switch(category) {
        case ONE:
            printf("Scoring Ones...\n");
            scoreCard[one][COL] = sumCategory(dice, category);
            break;
        case TWO:
            printf("Scoring Twos...\n");
            scoreCard[two][COL] = sumCategory(dice, category);
            break;
        case THREE:
            printf("Scoring Threes...\n");
            scoreCard[three][COL] = sumCategory(dice, category);
            break;
        case FOUR:
            printf("Scoring Fours...\n");
            scoreCard[four][COL] = sumCategory(dice, category);
            break;
        case FIVE:
            printf("Scoring Fives...\n");
            scoreCard[five][COL] = sumCategory(dice, category);
            break;
        case SIX:
            printf("Scoring Sixes...\n");
            scoreCard[six][COL] = sumCategory(dice, category);
            break;
        case THREEKIND:
            printf("Scoring Three of a kind...\n");
            scoreCard[threekind][COL] = checkThreeKind(dice);
            break;
        case FOURKIND:
            printf("Scoring Four of a kind...\n");
            scoreCard[fourkind][COL] = checkFourKind(dice);
            break;
        case FULLHOUSE:
            printf("Scoring Full House...\n");
            scoreCard[fullhouse][COL] = checkFullHouse(dice);
            break;
        case SMSTRAIGHT:
            printf("Scoring Small straight...\n");
            scoreCard[smstraight][COL] = checkSmStraight(dice);
            break;
        case LGSTRAIGHT:
            printf("Scoring Large straight...\n");
            scoreCard[lgstraight][COL] = checkLgStraight(dice);
            break;
        case YAHTZEE:
            printf("Scoring Yahtzee...\n");
            scoreCard[yahtzee][COL] = checkYahtzee(dice);
            break;
        case CHANCE:
            printf("Scoring Chance...\n");
            scoreCard[chance][COL] = sumChance(dice);
            break;
        default:
            printf("Invalid option, try again\n");
            break;
    }
}

void displayScoreCard(int scores[CATEGORIES][COLS])
{
    int total = sumUpper(scores) + checkBonus(scores);
    int grandTotal = total + sumLower(scores);
    printf("\n\tYAHTZEE SCORECARD\n");

    displayUpperSection(scores);
    displayLowerSection(scores);

    printf("+-----------------+-----------+\n");
    printf("| TOTAL (upper)   |     %d     |\n", total);
    printf("+-----------------+-----------+\n");
    printf("| GRAND TOTAL     |     %d     |\n", grandTotal);
    printf("+-----------------+-----------+\n");
}

void displayUpperSection(int scores[CATEGORIES][COLS])
{
    int bonus = checkBonus(scores);
    int totalScore = sumUpper(scores);
    int total = bonus + totalScore;

    printf("+-----------------+-----------+\n");
    printf("| UPPER SECTION   |   SCORE   |\n");
    printf("+-----------------+-----------+\n");
    printf("| ONES            |     %d     |\n", scores[one][COL]);
    printf("+-----------------+-----------+\n");
    printf("| TWOS            |     %d     |\n", scores[two][COL]);
    printf("+-----------------+-----------+\n");
    printf("| THREES          |     %d     |\n", scores[three][COL]);
    printf("+-----------------+-----------+\n");
    printf("| FOURS           |     %d     |\n", scores[four][COL]);
    printf("+-----------------+-----------+\n");
    printf("| FIVES           |     %d     |\n", scores[five][COL]);
    printf("+-----------------+-----------+\n");
    printf("| SIXES           |     %d     |\n", scores[six][COL]);
    printf("+-----------------+-----------+\n");
    printf("| TOTAL SCORE     |     %d     |\n", totalScore);
    printf("+-----------------+-----------+\n");
    printf("| BONUS           |     %d     |\n", bonus);
    printf("+-----------------+-----------+\n");
    printf("| SCORE           |     %d     |\n", total);
    printf("+-----------------+-----------+\n");
}

void displayLowerSection(int scores[CATEGORIES][COLS])
{
     int total = sumLower(scores);

    printf("+-----------------+-----------+\n");
    printf("| LOWER SECTION   |   SCORE   |\n");
    printf("+-----------------+-----------+\n");
    printf("| THREE OF A KIND |     %d     |\n", scores[threekind][COL]);
    printf("+-----------------+-----------+\n");
    printf("| FOUR OF A KIND  |     %d     |\n", scores[fourkind][COL]);
    printf("+-----------------+-----------+\n");
    printf("| FULL HOUSE      |     %d     |\n", scores[fullhouse][COL]);
    printf("+-----------------+-----------+\n");
    printf("| SM STRAIGHT     |     %d     |\n", scores[smstraight][COL]);
    printf("+-----------------+-----------+\n");
    printf("| LG STRAIGHT     |     %d     |\n", scores[lgstraight][COL]);
    printf("+-----------------+-----------+\n");
    printf("| YAHTZEE         |     %d     |\n", scores[yahtzee][COL]);
    printf("+-----------------+-----------+\n");
    printf("| CHANCE          |     %d     |\n", scores[chance][COL]);
    printf("+-----------------+-----------+\n");
    printf("| TOTAL (lower)   |     %d     |\n", total);
}


//pray for me
int sumCategory(int dice[DICE], int category) {
    int sum;
    int die;

    for(die=0; die<DICE; die++) {
        switch(category)
        {

        case ONE:
            if(dice[die] == ONE)
                sum += ONE;
            break;
        case TWO:
            if(dice[die] == TWO)
                sum += TWO;
            break;
         case THREE:
            if(dice[die] == THREE)
                sum += THREE;
            break;
         case FOUR:
            if(dice[die] == FOUR)
                sum += FOUR;
            break;
        case FIVE:
            if(dice[die] == FIVE)
                sum += FIVE;
            break;
        case SIX:
            if(dice[die] == SIX)
                sum += SIX;
            break;
        }
    }
    return sum;
}

int sumChance(int dice[DICE])
{
    int sum;
    int die;

    for(die=0; die<DICE; die++)
    {
        sum += dice[die];
    }
    return sum;
}

//Large Straight
int checkLgStraight(int dice[DICE]){
    int sum;

    sortDice(dice);

    if(dice[two] == (dice[one]+1) && dice[three] == (dice[two]+1) &&
        dice[four] == (dice[three]+1) && dice[five] == (dice[four]+1))
    {
        sum = 40;
    }
    else
    {
        sum = 0;
    }
    return sum;
}

//Small Straight I FIXED THIS ONE
int checkSmStraight(int dice[DICE]){
    int sum=0;

    sortDice(dice);


    if((dice[two] == (dice[one]+1) && dice[three] == (dice[two]+1) && dice[four] == (dice[three]+1))
       || (dice[five] == (dice[four]+1) && dice[three] == (dice[two]+1) && dice[four] == (dice[three]+1)))
    {
        sum = 30;
    }
    else
    {
        sum = 0;
    }
    return sum;
}

//Check Yahtzee
int checkYahtzee(int dice[DICE])
{
    int sum;

    if(dice[two] == (dice[one]) && dice[three] == (dice[two]) &&
        dice[four] == (dice[three]) && dice[five] == (dice[four]))
    {
        sum = 50;
        return sum;
    }
    else
    {
        sum = 0;
        return sum;
    }
}

//Four of a kind
int checkFourKind(int dice[DICE])
{
    int sum=0;
    int die;
    int count= 0;
    int first = 0;

    sortDice(dice);

    if(dice[0] == dice[1])
    {
        first = 0;
    }
    else if(dice[1] == dice[2])
    {
        first = 1;
    }
    for(die = first; die < 5; die++)
    {
        if(dice[die] == dice[first])
        {
            count++;
        }
    }

    if(count == 4)
    {
        sum = dice[one] + dice[two] + dice[three] + dice[four] + dice[five];
    }
    return sum;
}

//Three of a Kind
int checkThreeKind(int dice[DICE])
{
    int sum;
    int die;
    int count=0;
    int first;
    sortDice(dice);

    if(dice[0] == dice[1])
        first = 0;
    else if(dice[1] == dice[2])
        first = 1;
    else if(dice[2] == dice[3])
        first = 2;

    for(die = first; die < 5; die++)
    {
        if(dice[die] == dice[first])
            count+= 1;
    }

    if(count == 3)
        for(die = 0; die < 5; die++)

        {
            sum += dice[die];

        }
    return sum;
}

//Full House
int checkFullHouse(int dice[DICE])
{
    int sum;
    int die;
    int count;
    int pair;
    int threeOfKind;
    sortDice(dice);

    if((dice[two] == dice[one] && dice[three] == dice[two] && dice[four] == dice[five])
       || (dice[four] == dice[three] && dice[five] == dice[four] && dice[one] == dice[two]))
    {
        sum = 25;
    }
    else
    {
        sum = 0;
    }
    return sum;
}

int sumUpper(int scoreCard[13][2])
{
    int sum = 0;
    int score;

    for(score = 0; score < 6; score++)
    {
        sum += scoreCard[score][COL];
    }
    return sum;
}


int sumLower(int scoreCard[13][2])
{
    int sum = 0;
    int i;

    for(i=6; i<CATEGORIES; i++)
    {
        sum += scoreCard[i][COL];
    }
    return sum;
}


int checkBonus(int scoreCard[CATEGORIES][COLS])
{
    int sum=0;
    int score;
    int upper = sumUpper(scoreCard);

    if(upper >= 63)
    {
        sum = 35;
    }
    else
    {
        sum = 0;
    }
    return sum;
}

void sortDice(int dice[DICE])
{
    int temp;
    int outer;
    int inner;

    for (outer = 0; outer < 5; ++outer)
        {

            for (inner = outer + 1; inner < 5; ++inner)
            {

                if (dice[outer] > dice[inner])
                {

                    temp =  dice[outer];
                    dice[outer] = dice[inner];
                    dice[inner] = temp;

                }

            }

        }
}

