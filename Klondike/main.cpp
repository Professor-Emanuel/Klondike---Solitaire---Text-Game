/* the main program */

#include<iostream>
#include "Klondike.h"
// I am not going to put: using namespace std; as it may cause problems
// I need methods to move cards from one column to another:
// from DISCARD - TABLEAU / TABLEAU - FOUNDATION / TABLEAU - TABLEAU

// methods to handle moves
void handleTheMovingPart(Klondike &game);
void handleTheMovingPartToFoundation(Klondike &game);

// after each move we need to update, clean and print the new output
void clearTheDisplay();

int main(int argc, char **argv){
    Klondike game = Klondike();

    game.printTheGame();

    // variable to control the game
    bool run = true;
    do{
        char option = ' ';
        std::cout<<std::endl<<std::endl;
        std::cout<<"<<<<<<<<<<<<<<<<<-----------  Press 0 to move cards between rows.  ----------->>>>>>>>>>>>>>";
        std::cout<<"\n<<<<<<<<<<<<<<<<<-----------   Press 1 to Move to Foundation.      ----------->>>>>>>>>>>>>>";
        std::cout<<"\n<<<<<<<<<<<<<<<<<-----------     Press 2 to deal a new card.       ----------->>>>>>>>>>>>>>";
        std::cout<<"\n<<<<<<<<<<<<<<<<<-----------     Press 3 to quit the game.         ----------->>>>>>>>>>>>>>";
        std::cout<<"\n<<<<<<<<<<<<<<<<<-----------        Enter your option:             ----------->>>>>>>>>>>>>>";
        std::cin>>option;

        // we need to know the ASCII codes: 48 (is for 0) and the last is 57 (is for 9)

        if(game.finishedGame()){
            clearTheDisplay();
            std::cout<<"\n\n\n\t\t\t You completed the game!\n\n";
            std::cout<<"\n\n\n\t\t\t\t Congratulation!\n\n";
            std::cin.get();
            run = false;
        }
        else
        {
            switch ((int)option)
            {
            case 51:
                run = false;
                break;
            case 50:
                game.dealFromStackDeck(1);// here you can also put 3; klondike rules allow it.
                break;
            case 49:
                handleTheMovingPartToFoundation(game);
                break;
            case 48:
                handleTheMovingPart(game);
                break;
            default:
                std::cout<<"\nWrong option. You should read carefully!";
                std::cin.ignore(80,'\n'); //ignore till 80 characters are reached or new line
                break;
            }

            clearTheDisplay();
            game.printTheGame();
        }
    }while(run);

    return 0;
}

void handleTheMovingPart(Klondike &game){
    char from = '0';
    char to = '0';
    std::cout<<"From :"; std::cin>>from;
    std::cout<<"To :";   std::cin>>to;

    // the tableau will have columns 0 through 6, and the stock will be 7
    if( ( (int)from >= 48 && (int)from <= 55) && ( (int)to >= 48 && (int)to <=54) )
    {
        game.theMoveRowToRow( (int)from - 48, (int)to - 48);
    }
    else
    {
        std::cout<< "This was an invalid move!";
        std::cin.get();
        std::cin.get();
    }
}
void handleTheMovingPartToFoundation(Klondike &game){
    char from = 0;
    std::cout<<std::endl<<std::endl;
    std::cout<< "From :"; std::cin>>from;

    if( (int)from >=48 && (int)from <= 55)
    {
        game.theMoveToFoundation((int)from - 48);
    }
    else
    {
        std::cout<< "This was an invalid move!";
        std::cin.get();
        std::cin.get();
    }
}

void clearTheDisplay(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #endif
}
