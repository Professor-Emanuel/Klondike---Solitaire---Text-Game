/* the TableauPlayerCard.h program */
#ifndef TABLEAUPLAYERCARD_H
#define TABLEAUPLAYERCARD_H

#pragma once
#include "PlayerCard.h"
#include<vector>

class TableauPlayerCard{
    public: //int maximumAllowedSize
        TableauPlayerCard();
        TableauPlayerCard(int maximumAllowedSize);
        ~TableauPlayerCard(void);
        // we need to overload the subscript operator [] for objects of type PlayerCard
        // https://www.geeksforgeeks.org/overloading-subscript-or-array-index-operator-in-c/
        PlayerCard& operator[](int index);
        PlayerCard& topPlayerCard(void);

        bool pushCardOnStack(PlayerCard &card);
        bool pushValueOfCopyCard(PlayerCard card);
        bool emptyTableau();
        bool removePlayerCardAtIndex(int index);
        bool popLastCard();

        int theSize();
        void clearTableauOfPlayerCards();
        static void moveBetween(TableauPlayerCard &from, TableauPlayerCard &to);

    private:
        int actualMaximumAllowedSize;
        int actualSize;
        std::vector<PlayerCard*> playerCards;
};

#endif // TABLEAUPLAYERCARD_H
