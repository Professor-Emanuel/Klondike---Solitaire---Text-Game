/* the StackDeckCard.h program */
#ifndef STACKDECKCARDS_H
#define STACKDECKCARDS_H

#pragma once
#include "PlayerCard.h"
#include "TableauPlayerCard.h"
#include<ctime>
#include<iostream>

const static int NUMBER_CARD_SIZE = 13;
const static int TYPE_CARD_SIZE = 4;
const static char NUMBERS[] = {'A', '2', '3', '4',
                               '5', '6', '7', '8',
                               '9', 'T', 'J', 'Q',
                               'K'};
const static char TYPES[] = {'s', 'c', 'd', 'h'};

class StackDeckCards{
    public:
        StackDeckCards(void);
        ~StackDeckCards(void);
        void colonizeStackDeck(void);
        void displayStackDeck(void);
        void colonizeVector(TableauPlayerCard &someDeck);
        void shuffleStackDeck(void);

    private:
        PlayerCard someRandomDeck[52];
        int currentIndex;
};

#endif // STACKDECKCARDS_H
