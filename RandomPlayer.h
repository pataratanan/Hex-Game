/**
 * Declaration
 *
 * I hereby certify that no other part of this submission has been copied from any other sources, including the
 * Internet, books or other student’s work except the ones I have listed below. No part of the code has been
 * written/produced for me by another person or copied from any other source.
 *
 * I hold a copy of this assignment that I can produce if the original is lost or damaged.
 */

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_
#include <iostream>
using namespace std;

class RandomPlayer: public Player{
public:
    RandomPlayer(int t, string name = "Computer"):
    Player(t,name){
    }
    bool getMove(Board*, int&, int&);
};

bool RandomPlayer::getMove(Board* board, int &x, int &y) {
    bool flag = false;

    while(!flag) {
        board->randomMove(x, y);
        flag = board->validInput(x, y);
        if (flag == false)
            cout << "Invalid input! Please input again." << endl;
    }
    return true;
}
#endif