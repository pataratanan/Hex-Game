/**
 * Declaration
 *
 * I hereby certify that no other part of this submission has been copied from any other sources, including the
 * Internet, books or other student’s work except the ones I have listed below. No part of the code has been
 * written/produced for me by another person or copied from any other source.
 *
 * I hold a copy of this assignment that I can produce if the original is lost or damaged.
 */
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <queue>

using namespace std;

#include "Board.h"
#include "Player.h"
#include "Cell.h"
#include "HumanPlayer.h"
#include "HexGame.h"
#include "RandomPlayer.h"
#include "BestFirstSearch.h"
#include "MontecarloPlayer.h"

int main() {
    srand(time(0));
    int boardSize = 5;
    cout <<"Input the size of board:" << endl;
    cin >> boardSize;
    if (boardSize < 3)
        boardSize = 3;

    Board *board = new Board(boardSize);
    cout << "Please choose a level to run:" << endl;
    cout << "1. Human vs Human\n";
    cout << "2. Human vs Random\n";
    cout << "3. Random vs Random\n";
    cout << "4. Random vs SmartPlayer\n";
    cout << "5. SmartPlayer vs MonteCarlo\n";
    cout << "6. Random vs MonteCarlo\n";

    int option;
    cin >> option;

    if(option == 1){
        Player *p1 = new HumanPlayer(1, "Human (Red)");
        Player *p2 = new HumanPlayer(-1, "Human (Blue)");
        HexGame game(board, p1, p2);
        game.play();

        delete board;
        delete p1;
        delete p2;
    }
    if(option == 2){
        Player *p1 = new HumanPlayer(1, "Human (Red)");
        Player *p2 = new RandomPlayer(-1, "RandomPlayer (Blue)");
        HexGame game(board, p1, p2);
        game.play();

        delete board;
        delete p1;
        delete p2;
    }
    if(option == 3){
        Player *p1 = new RandomPlayer(1, "RandomPlayer (Red)");
        Player *p2 = new RandomPlayer(-1, "RandomPlayer (Blue)");
        HexGame game(board, p1, p2);
        game.play();

        delete board;
        delete p1;
        delete p2;
    }if(option == 4){
        Player *p1 = new RandomPlayer(1, "RandomPlayer (Red)");
        Player *p2 = new BestFirstSearch(-1, "SmartPlayer (Blue)");
        HexGame game(board, p1, p2);
        game.play();

        delete board;
        delete p1;
        delete p2;
    }if(option == 5){
        Player *p1 = new BestFirstSearch(1, "SmartPlayer (Red)");
        Player *p2 = new MonteCarloPlayer(-1, "MonteCarlo (Blue)");
        HexGame game(board, p1, p2);
        game.play();

        delete board;
        delete p1;
        delete p2;
    }if(option == 6){
        Player *p1 = new RandomPlayer(1, "Random (Red)");
        Player *p2 = new MonteCarloPlayer(-1, "MonteCarlo (Blue)");
        HexGame game(board, p1, p2);
        game.play();

        delete board;
        delete p1;
        delete p2;
    }
    if(option == 7){ //for testing MontecarloPlayer. It's not in an option
        Player *p1 = new MonteCarloPlayer(1, "MonteCarlo (Red)");
        Player *p2 = new MonteCarloPlayer(-1, "MonteCarlo (Blue)");
        HexGame game(board, p1, p2);
        game.play();

        delete board;
        delete p1;
        delete p2;
    }
    //system("pause");
    return 0;
}

