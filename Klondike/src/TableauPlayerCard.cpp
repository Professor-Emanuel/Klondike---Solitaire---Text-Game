/* the TableauPlayerCard.cpp program */

#include "TableauPlayerCard.h"
TableauPlayerCard::TableauPlayerCard(void){}

TableauPlayerCard::TableauPlayerCard(int maximumAllowedSize){
    actualMaximumAllowedSize = maximumAllowedSize;
    actualSize = 0;
    playerCards.resize(maximumAllowedSize);
}

TableauPlayerCard::~TableauPlayerCard(void){}

// we want to introduce cards in the stack/vector
// but we shouldn't be allowed to add more cards than it should
// be, following the rules of the game
// so the next method is to verify if we still have space where to add a card
bool TableauPlayerCard::pushCardOnStack(PlayerCard &card){
    if(actualSize < actualMaximumAllowedSize){
        playerCards[actualSize] = &card;
        actualSize++;
        return true;
    }
    return false;
}

// same thing as the above method, but we do not reference the parameter
bool TableauPlayerCard::pushValueOfCopyCard(PlayerCard card){
    if(actualSize < actualMaximumAllowedSize){
        playerCards[actualSize] = new PlayerCard(card);
        actualSize++;
        return true;
    }
    return false;
}

void TableauPlayerCard::clearTableauOfPlayerCards(){
    for(int i=0; i<actualSize; i++)
        playerCards[i] = NULL;

    actualSize = 0;
}

// this method is to verify if there are any cards in the deck
bool TableauPlayerCard::emptyTableau(){
    if(actualSize == 0)
        return true;
    return false;
}

// this method returns card at last index
PlayerCard& TableauPlayerCard::topPlayerCard(void){
    if(actualSize > 0)
        return *playerCards[actualSize-1];
}

// this method is to verify if a card exist and remove it at a specified index
// by removing at a specific index means making the element of the vector
// at that index: NULL
bool TableauPlayerCard::removePlayerCardAtIndex(int index){
    if(index >= 0 && index < actualMaximumAllowedSize){
        playerCards[index] = NULL;
        actualSize--;
        return true;
    }
    return false;
}

int TableauPlayerCard::theSize(){
    return actualSize;
}

// this method is to verify and remove the card at the last index
bool TableauPlayerCard::popLastCard(){
    if(actualSize > 0){
        playerCards[actualSize - 1] = NULL;
        actualSize--;
        return true;
    }
    return false;
}

// method to overload operator []
// we want to check for index out of bound
PlayerCard& TableauPlayerCard::operator[](int index){
    if(index >=0 && index <= actualSize)
        return *playerCards[index];
}

void TableauPlayerCard::moveBetween(TableauPlayerCard &from, TableauPlayerCard &to){
    to.pushCardOnStack(from.topPlayerCard());
    from.popLastCard();
}
