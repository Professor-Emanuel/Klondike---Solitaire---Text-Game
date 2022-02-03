/* PlayerCard.h */
#ifndef PLAYERCARD_H
#define PLAYERCARD_H

#pragma once
#include<iostream>
#ifdef _WIN32
#include<windows.h>
const static int black = 0;
const static int blue = 9;
const static int red = 12;
const static int green = 2;
#elif __linux__
#include "stdlib.h"
#endif
// https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c

class PlayerCard{
    public:
        PlayerCard(void);
        ~PlayerCard();
        PlayerCard(char cardNumber, char cardType);
        void Flip();
        bool getIsCardFaceUp();
        char getCardNumber();
        char getCardType();
        int getKlondikeValue();

    //std::cout is actually an object of type std::ostream
    //we will need to overload the "<<" operator, and use keyword "friend" so we can access PlayerCard's members directly
    //https://www.learncpp.com/cpp-tutorial/93-overloading-the-io-operators/
        friend std::ostream& operator<< (std::ostream & out , PlayerCard& card);

    //we need pointers to aid us in traversing up and down cards in a row
    PlayerCard *parent;
    PlayerCard *child;

    private:
        char cardNumber;
        char cardType;
        bool isCardFaceUp;
};

#endif // PLAYERCARD_H
