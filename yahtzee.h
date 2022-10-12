#ifndef YAHTZEE_H_INCLUDED
#define YAHTZEE_H_INCLUDED

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
void updateScores(int scoreCard[CATEGORIES][COLS], int category, int dice[DICE]);
void displayScoreCard(int scores[CATEGORIES][COLS]);
void displayUpperSection(int scores[CATEGORIES][COLS]);
void displayLowerSection(int scores[CATEGORIES][COLS]);
//Yahtzee 5
void sortDice(int dice[DICE]);
int sumCategory(int dice[DICE], int category);
int sumUpper(int scoreCard[CATEGORIES][COLS]);
int sumLower(int scoreCard[CATEGORIES][COLS]);
int checkSmStraight(int dice[DICE]);
int checkLgStraight(int dice[DICE]);
int checkYahtzee(int dice[DICE]);
int checkFourKind(int dice[DICE]);
int checkThreeKind(int dice[DICE]);
int checkBonus(int scoreCard[CATEGORIES][COLS]);
int sumChance(int dice[DICE]);
int checkFullHouse(int dice[DICE]);


enum scores{one, two, three, four, five, six, threekind, fourkind, fullhouse, smstraight, lgstraight, yahtzee, chance};

#endif // YAHTZEE_H_INCLUDED
