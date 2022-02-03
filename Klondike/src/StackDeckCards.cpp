/* the StockDeckCard.cpp program */

#include "StackDeckCards.h"

StackDeckCards::StackDeckCards(){
    currentIndex = 0;
    // I am using time(0) here because it is the most
    // simplest way to get a different value between two executions
    // of the program, so srand will be initialized with different values because of time(0)
    // thus generating different sequences of random numbers each launch of the program.
    // http://www.cplusplus.com/reference/cstdlib/srand/
    // https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
    srand((unsigned)time(0));
    colonizeStackDeck();
}

StackDeckCards::~StackDeckCards(){}

void StackDeckCards::colonizeStackDeck(){
    int index = 0;
    for(int i=0; i<TYPE_CARD_SIZE; i++){
        for(int j=0; j<NUMBER_CARD_SIZE; j++){
            someRandomDeck[index] = PlayerCard(NUMBERS[j], TYPES[i]);
            index++;
        }
    }
}

void StackDeckCards::shuffleStackDeck(){
    int max = NUMBER_CARD_SIZE * TYPE_CARD_SIZE;
    for(int i=0; i<max-1; i++)
    {
        int randomNumber = rand() % 52 ;
        std::swap(someRandomDeck[i], someRandomDeck[randomNumber]);
    }
}

void StackDeckCards::displayStackDeck(void){
    int max = NUMBER_CARD_SIZE * TYPE_CARD_SIZE;
    for(int i=0; i<max; i++)
    {
        if(i%13 == 0){
            std::cout<< '\n' << 'n';
        }
        std::cout<< someRandomDeck[i] << " ";
    }
}

void StackDeckCards::colonizeVector(TableauPlayerCard &someDeck){
    int max = NUMBER_CARD_SIZE * TYPE_CARD_SIZE;
    someDeck.clearTableauOfPlayerCards();
    for(int i=0; i<max; i++){
        someDeck.pushValueOfCopyCard(someRandomDeck[i]);
    }
}
