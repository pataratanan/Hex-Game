/**
 * Declaration
 *
 * I hereby certify that no other part of this submission has been copied from any other sources, including the
 * Internet, books or other student’s work except the ones I have listed below. No part of the code has been
 * written/produced for me by another person or copied from any other source.
 *
 * I hold a copy of this assignment that I can produce if the original is lost or damaged.
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

using namespace std;

class HumanPlayer: public Player {
public:
    HumanPlayer(int t, string name = "Human") :
            Player(t, name) {
    }
    bool getMove(Board*, int&, int&);
};

bool HumanPlayer::getMove(Board *board, int &x, int &y) {
    bool flag = false;
    int bs = board->getBoardSize();

    while (!flag) {
        cout << "Input row and column (x, y) between 1 to " << bs << " for "
             << name << " player:" << endl;
        int row, col;
        cin >> row >> col;
        x = row - 1;
        y = col - 1;
        flag = board->validInput(x, y);
        if (flag == false)
            cout << "Invalid input! Please input again." << endl;
    }

    return true;
}

#endif
