/* Klondike.cpp */

#include "Klondike.h"
Klondike::Klondike(void){
    theGameFullDeck = 52;
    wastedGameCards = 52;
    // we need to create a deck object
    // we can do it by using class StackDeckCards
    StackDeckCards theGameDeck = StackDeckCards();
    theGameDeck.shuffleStackDeck();
    theGameDeck.colonizeVector(theGameFullDeck);

    for(int i=0; i<MAIN_TABLEAU_SIZE; i++){
        TableauPlayerCard mainTableauPlayerCards = TableauPlayerCard(20); // I chose here 20 because, Imagine that the biggest column has
        //already 7 card, but no one can impose us from stacking there from K to A and the move everything to the foundation.
        theTableauPlayerCards.push_back(mainTableauPlayerCards); //7 vectors each being a column with cards
    }

    for(int i=0; i<4; i++){
        TableauPlayerCard mainTypeOfCard = TableauPlayerCard(13); // naturally it is 13, because on a foundation
        //column you can have at maximum 13 card piled on each other
        typeOfCard.push_back(mainTypeOfCard); // 4 vectors, because that is the number of foundation columns
    }

    colonizeMainTableau();
}

Klondike::~Klondike(void){}

// each column in the main tableau has a specific number of card at the beginning
// i.e. column 5 has 5 cards with the top=last one fliped=visible, and the rest unfliped
// so the next function will populate each column correspondingly
void Klondike::colonizeMainTableau(){
    for(int i=0; i<MAIN_TABLEAU_SIZE; i++)
    {
        for(int j=0; j<MAIN_TABLEAU_SIZE - i; j++)
            {
            if(j == MAIN_TABLEAU_SIZE - i - 1)
                theGameFullDeck.topPlayerCard().Flip();
            theTableauPlayerCards[j].pushCardOnStack(theGameFullDeck.topPlayerCard());
            theGameFullDeck.popLastCard();
            }
    }
}

void Klondike::dealFromStackDeck(int numberOfCardsToDeal){
    int sizeOfDeck = theGameFullDeck.theSize();
    for(int i = 0 ; i<sizeOfDeck; i++){
        // here we verify if there was a dealt card or not
        // if it was, flip the current top card, push it in the discarded pile
        // and remove it from the deck
        if(theGameFullDeck.topPlayerCard().getIsCardFaceUp()){
            theGameFullDeck.topPlayerCard().Flip();
            wastedGameCards.pushCardOnStack(theGameFullDeck.topPlayerCard());
            theGameFullDeck.popLastCard();
        }
    }

    // this next step is when the deal deck becomes empty
    // when that happens, we need to put back all
    // the cards that are in the wasted pile into the deal deck
    // and remove them from the wasted pile
    if(theGameFullDeck.emptyTableau()){
        for(int i = wastedGameCards.theSize() - 1; i>=0; i--){
            theGameFullDeck.pushCardOnStack(wastedGameCards[i]);
        }
        wastedGameCards.clearTableauOfPlayerCards();
    }

    // this part is responsible of the dealing part
    int index = 0;
    for(int i = 0; i< numberOfCardsToDeal; i++){
        index = theGameFullDeck.theSize() - i - 1;
        if(index >= 0 ){
            theGameFullDeck[index].Flip();
        }
        else
            break;
    }
}

void Klondike::printTheTypeOfCards(){
    std::cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<---------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";

    for(int j = 0; j < typeOfCard.size(); j++){
        switch(j){
            case 0:
                std::cout<<"s :";
                break;
            case 1:
                std::cout<<"c :";
                break;
            case 2:
                std::cout<<"d :";
                break;
            case 3:
                std::cout<<"h :";
                break;
        }
        for(int i = 0; i < typeOfCard[j].theSize(); i++)
        {
            if(&typeOfCard[j][i] != NULL){
                std::cout<<typeOfCard[j][i]<< " ";
            }
            else
            {
                break;
            }
        }
        std::cout<< std::endl;
    }
    std::cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<---------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    std::cout<< std::endl;
}

void Klondike::printTheStackDeck(){
    std::cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-----------  Klondike  ----------->>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    std::cout<<"<The Deck: ";
    for(unsigned int j = 0; j < theGameFullDeck.theSize(); j++){
        if(theGameFullDeck[j].getIsCardFaceUp())
        {
            std::cout<< theGameFullDeck[j] << " ";
        }
    }
    std::cout<< "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<---------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
}

void Klondike::printTheGame(){
    printTheStackDeck();
    printTheTypeOfCards();

    std::cout<<"< 6 > \t < 5 > \t < 4 > \t < 3 > \t < 2 > \t < 1 > \t < 0 > \n";
    std::cout<<"< - > \t < - > \t < - > \t < - > \t < - > \t < - > \t < - > \n";

    int theMaximumNumberOfColumns = theTableauPlayerCards.size();
    int theMaximumNumberOfRows = 0;

    for(int i = 0; i < theMaximumNumberOfColumns; i++){
        if(theTableauPlayerCards[i].theSize() > theMaximumNumberOfRows){
            theMaximumNumberOfRows = theTableauPlayerCards[i].theSize();
        }
    }

    for(int i = 0 ; i < theMaximumNumberOfRows; i++)
        {
            for(int j = theMaximumNumberOfColumns - 1; j>= 0; j--)
            {
            if( i >= theTableauPlayerCards[j].theSize()){
                std::cout<< " \t ";
                continue;
            }

            if(theTableauPlayerCards[j][i].getIsCardFaceUp())
                std::cout<< "  " << theTableauPlayerCards[j][i] << " \t ";
            else
                std::cout<< "  " << (char)254 << " \t "; //these line is to print full squares
                // for when the cards are unflipped
            }
            std::cout<<std::endl;
        }
    std::cout<<std::endl;
}

bool Klondike::validGenericMove(int from, int to){
    // the is no point in making a move if from == to
    if(from == to && from != 7){
        return false;
    }

    PlayerCard *toPlayerCard;
    PlayerCard *fromPlayerCard;

    // case when we want to move from the waste pile
    if(from == 7){
        if(!theGameFullDeck.emptyTableau()){ // if there are cards in the deck
            if(!theGameFullDeck.topPlayerCard().getIsCardFaceUp()){ // if card is unfliped
                return false;
            }
            else
            {// if the card if fliped (we can see it)
                fromPlayerCard = &theGameFullDeck.topPlayerCard();
            }

        }
        else
        { // if the deck is empty
            return false;
        }

    }
    else
    {
        if(!theTableauPlayerCards[from].emptyTableau()) // the condition means the "from" column has cards on it
            fromPlayerCard = &theTableauPlayerCards[from].topPlayerCard();
        else
            return false;
    }

    if(!theTableauPlayerCards[to].emptyTableau()) // the condition means the "to" column has cards on it
        toPlayerCard = &theTableauPlayerCards[to].topPlayerCard();
    // if a column is empty, we can only move the KING there
    if(theTableauPlayerCards[to].emptyTableau()){
        //check now to see if in "fromPlayerCard" is a KING
        if(fromPlayerCard->getCardNumber() == 'K')
            return true;
        else
        {
            return false;
        }
    }
    else
    {
        if(fromPlayerCard->getKlondikeValue() == toPlayerCard->getKlondikeValue()-1){
            int theToColor = 0;
            int theFromColor = 0;
            if(toPlayerCard->getCardType() == 'h' || toPlayerCard->getCardType() == 'd')
                theToColor = 0;
            else
                theToColor = 1;

            if(fromPlayerCard->getCardType() == 'h' || fromPlayerCard->getCardType() == 'd')
                theFromColor = 0;
            else
                theFromColor = 1;

            if(theFromColor == theToColor)
                return false;
            else
                return true;
        }
    }
    return false;
}
bool Klondike::validSpecificToFoundationMove(int from){
    PlayerCard *fromPlayerCard;
    if(from == 7){// move from deck to foundation
        if(!theGameFullDeck.emptyTableau()){//if the deck is not empty
            if(!theGameFullDeck.topPlayerCard().getIsCardFaceUp()){ // check if the card is visible
                return false;
            }
            else
            {// case when the card is visible
                fromPlayerCard = &theGameFullDeck.topPlayerCard();
            }
        }
        else
        {// case when the deck is empty
            return false;
        }
    }
    else
    {// move from main tableau to foundation
        if(!theTableauPlayerCards[from].emptyTableau()){
            //case when the specified column is not empty
            fromPlayerCard = &theTableauPlayerCards[from].topPlayerCard();
        }
        else
            return false;
    }

    // code the type of card as integers, so it will be easy to decide on which list should I
    //put the card if the proper card is selected to go in the foundation block
    char typeOfPlayerCard = fromPlayerCard->getCardType();
    int theMovingIndex = 0;
    switch (typeOfPlayerCard)
    {
    case 's':
        theMovingIndex = 0;
        break;
    case 'c':
        theMovingIndex = 1;
        break;
    case 'd':
        theMovingIndex = 2;
        break;
    case 'h':
        theMovingIndex = 3;
        break;
    }
    // in this case we are testing to see if we can move to foundation
    // card on the foundation are in ascending order, so naturally the check is with +1
    // typeofCard is a list that should contain 0nly one type of card in ascending order
    if(fromPlayerCard->getKlondikeValue() == typeOfCard[theMovingIndex].theSize() + 1){
        if(!typeOfCard[theMovingIndex].theSize() == 0){
            if(fromPlayerCard->parent != NULL)
                fromPlayerCard->parent->child = NULL;
            // make the parent of what you want to move, the top card on the proper foundation column
            fromPlayerCard -> parent = &typeOfCard[theMovingIndex].topPlayerCard();
            //on that foundation column make the child of top card to be the thing you wanna move
            typeOfCard[theMovingIndex].topPlayerCard().child = fromPlayerCard;
            fromPlayerCard->child = NULL;
    }

    if(from != 7){
        TableauPlayerCard::moveBetween(theTableauPlayerCards[from],  typeOfCard[theMovingIndex]);
        // after moving the cards from the specified column
        // we need to check if we still have remaining
        // cards there, if so, we need to flip thus make the top one visible
        if(!theTableauPlayerCards[from].emptyTableau()){
            if(!theTableauPlayerCards[from].topPlayerCard().getIsCardFaceUp())
                theTableauPlayerCards[from].topPlayerCard().Flip();
        }
    }
    else
    {
        typeOfCard[theMovingIndex].pushCardOnStack(theGameFullDeck.topPlayerCard());
        theGameFullDeck.popLastCard();
    }
    }
    return false;
}

void Klondike::theMoveToFoundation(int from){
    validSpecificToFoundationMove(from);//this function covers also all the moves to foundation
}

void Klondike::theMoveBetweenRows(int from, int to){
    if(validGenericMove(from, to)){
        if(!theTableauPlayerCards[to].emptyTableau())
            theTableauPlayerCards[to].topPlayerCard().child = &theTableauPlayerCards[from].topPlayerCard();

        //check the number of "from card", if it is not 13=K, then it can have a parent
        // and make that parent to be the top card of "to column card"
        if(theTableauPlayerCards[from].topPlayerCard().getCardNumber() != 'K')
            theTableauPlayerCards[from].topPlayerCard().parent = &theTableauPlayerCards[to].topPlayerCard();
        TableauPlayerCard::moveBetween(theTableauPlayerCards[from], theTableauPlayerCards[to]);
        // we need to check the "from column" if it is not empty
        // than we need to flip the new top card
        if(!theTableauPlayerCards[from].emptyTableau())
            if(!theTableauPlayerCards[from].topPlayerCard().getIsCardFaceUp())
                theTableauPlayerCards[from].topPlayerCard().Flip();
    }
}

void Klondike::theMoveRowToRow(int from, int to){
    if(from == 7){
        theMoveFromStackDeckToRow(to);
        return;
    }
    else
    {
        if(theTableauPlayerCards[from].theSize() == 0)
            return;
    }

    PlayerCard *fromPlayerCard;
    fromPlayerCard = &theTableauPlayerCards[from].topPlayerCard();
    if(fromPlayerCard->parent == NULL)
        theMoveBetweenRows(from, to);
    else
    {
        int position = theTableauPlayerCards[from].theSize() - 1;
        bool checkParentExistence = true;
        bool found = false;
        while(checkParentExistence && !found){
            if(validSpecificRowToRowMove(fromPlayerCard, to))
                found = true;
            else
            {
                if(fromPlayerCard->parent == NULL)
                    checkParentExistence = NULL;
                else
                {
                    fromPlayerCard = fromPlayerCard->parent;
                    position--;
                }

            }

        }

        if(found){
            bool itHasChildren = true;
            if(fromPlayerCard->parent != NULL)
                fromPlayerCard->parent->child = NULL;

            while(itHasChildren){
                if(!theTableauPlayerCards[to].emptyTableau()){
                    fromPlayerCard->parent = &theTableauPlayerCards[to].topPlayerCard();
                    theTableauPlayerCards[to].topPlayerCard().child = fromPlayerCard;
                }
                // now put the card in the "to column" and remove it from the "from column"
                theTableauPlayerCards[to].pushCardOnStack(*fromPlayerCard);
                theTableauPlayerCards[from].removePlayerCardAtIndex(position);
                fromPlayerCard = fromPlayerCard->child;
                position++;

                if(fromPlayerCard == NULL)
                    itHasChildren = false;
            }
        }

        if(!theTableauPlayerCards[from].emptyTableau())
            if(!theTableauPlayerCards[from].topPlayerCard().getIsCardFaceUp())
                theTableauPlayerCards[from].topPlayerCard().Flip();
    }
}

void Klondike::theMoveFromStackDeckToRow(int to){
    if(validGenericMove(7, to)){
        if(!theTableauPlayerCards[to].emptyTableau())
            theTableauPlayerCards[to].topPlayerCard().child = &theGameFullDeck.topPlayerCard();

        //check the number of "from card", if it is not 13=K, then it can have a parent
        // and make that parent to be the top card of "to column card"
        if(theGameFullDeck.topPlayerCard().getCardNumber() != 'K')
            theGameFullDeck.topPlayerCard().parent = &theTableauPlayerCards[to].topPlayerCard();

        // put the top card from deck to the "to column"
        // and remove the top deck card from that stack
        theTableauPlayerCards[to].pushCardOnStack(theGameFullDeck.topPlayerCard());
        theGameFullDeck.popLastCard();
    }
}

bool Klondike::validSpecificRowToRowMove(PlayerCard *fromPlayerCard, int to){
    PlayerCard *toPlayerCard;
    if(!theTableauPlayerCards[to].emptyTableau())
        toPlayerCard = &theTableauPlayerCards[to].topPlayerCard();
    // only the KING can be moved in an empty spot!
    if(theTableauPlayerCards[to].emptyTableau()){
        if(fromPlayerCard->getCardNumber() == 'K')
            return true;
        else
            return false;
    }
    else if(fromPlayerCard->getKlondikeValue() == toPlayerCard->getKlondikeValue() - 1){
            int theToColor = 0;
            int theFromColor = 0;
            if(toPlayerCard->getCardType() == 'h' || toPlayerCard->getCardType() == 'd')
                theToColor = 0;
            else
                theToColor = 1;

            if(fromPlayerCard->getCardType() == 'h' || fromPlayerCard->getCardType() == 'd')
                theFromColor = 0;
            else
                theFromColor = 1;

            if(theFromColor == theToColor)
                return false;
            else
                return true;
        }
    return false;
}

bool Klondike::finishedGame(){
    int i = 0;
    while(i < typeOfCard.size()){
        if(typeOfCard[i].theSize() < 13)
            return false;
    i++;
    }
    return true;
}
