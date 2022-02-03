/* PlayerCard.cpp */

#include "PlayerCard.h"

PlayerCard::PlayerCard(void){}

PlayerCard::PlayerCard(char number, char type){
    cardNumber = number;
    cardType = type;
    isCardFaceUp = false;
    child = NULL;
    parent = NULL;
}
// an equivalent way of writing this is:
// PlayerCard::PlayerCard(char number, char type):cardNumber(number), cardType(type), isCardFaceUp(false), child(NULL), parent(NULL){}


PlayerCard::~PlayerCard(void){}

void PlayerCard::Flip(){
    isCardFaceUp = !isCardFaceUp;
}
bool PlayerCard::getIsCardFaceUp(){
    return isCardFaceUp;
}

char PlayerCard::getCardNumber(){
    return cardNumber;
}

char PlayerCard::getCardType(){
    return cardType;
}

// this method is specific to this game
// I want to use the integer values of: A, T, J, Q and K
int PlayerCard::getKlondikeValue(){
    if(cardNumber == 'A')
        return 1;
    else if(cardNumber == 'T')
            return 10;
    else if(cardNumber == 'J')
            return 11;
    else if(cardNumber == 'Q')
            return 12;
    else if(cardNumber == 'K')
            return 13;
    else{
        char card[] = {cardNumber, '\0'};
        return atoi(card);
    }
}

// in this part of the code we do the operator << overload
// and also set color blue for "clubs=c, and spades=s"
// color red for "dimonds=d and hearts=h"
// https://docs.microsoft.com/en-us/windows/console/getstdhandle
// blue, red, green are static const defined in PlayerCard.h
// linux: https://www.daniweb.com/programming/software-development/threads/266484/how-to-print-text-into-a-different-color-in-terminal
std::ostream &operator<< (std::ostream &out, PlayerCard &card){
    #ifdef _WIN32
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if(card.cardType == 'c' || card.cardType == 's')
            SetConsoleTextAttribute(handle, blue);
        else
            SetConsoleTextAttribute(handle, red);
        out<< card.cardType << card.cardNumber;
        SetConsoleTextAttribute(handle, green);
    #elif __linux__
        if(card.cardType == 'c' || card.cardType == 's')
            out<<"\033[22;34m";//blue
        else
            out<<"\033[22;31m";//red
        out<< card.cardType << card.cardNumber;
        out<<"\033[22;30m";//black
    #endif
        return out;
}
