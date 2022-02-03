/* Klondike.h */
#ifndef KLONDIKE_H
#define KLONDIKE_H

#pragma once
#include<iostream>
#include<vector>
#include "StackDeckCards.h"
#include "PlayerCard.h"
#include "TableauPlayerCard.h"

const static int MAIN_TABLEAU_SIZE = 7;

class Klondike{
    public:
        Klondike(void);
        ~Klondike(void);

        void colonizeMainTableau(void);
        void dealFromStackDeck(int numberOfCardsToDeal = 1);

        // methods to print the details of each card: like colour, type(red/blue), number
        void printTheGame(void);
        void printTheTypeOfCards(void);
        void printTheStackDeck(void);

        // method to check if the Foundation is full, if so, the game is completed
        // based on this method we will stop the game
        bool finishedGame();

        // the following functions will aid in moving cards while validating
        // to see if the move is allowed or not, by
        // following the rules of the game
        bool validGenericMove(int from, int to);
        bool validSpecificRowToRowMove(PlayerCard *fromCard, int to);
        bool validSpecificToFoundationMove(int from);

        void theMoveToFoundation(int from);
        void theMoveBetweenRows(int from, int to);
        void theMoveRowToRow(int from, int to);
        void theMoveFromStackDeckToRow(int to);

    private:
        TableauPlayerCard theGameFullDeck;
        TableauPlayerCard wastedGameCards;

        std::vector<TableauPlayerCard> theTableauPlayerCards;
        std::vector<TableauPlayerCard> typeOfCard;//this vector is for the foundation, and when it is going to be full, player will win
};

#endif // KLONDIKE_H
