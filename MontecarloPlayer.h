/**
 * Declaration
 *
 * I hereby certify that no other part of this submission has been copied from any other sources, including the
 * Internet, books or other student’s work except the ones I have listed below. No part of the code has been
 * written/produced for me by another person or copied from any other source.
 *
 * I hold a copy of this assignment that I can produce if the original is lost or damaged.
 */
#include <iomanip>
#include "Cell.h"
#ifndef MONTECARLOPLAYER_H_
#define MONTECARLOPLAYER_H_

class MonteCarloPlayer: public Player {
public:
    MonteCarloPlayer(int t, string name = "MonteCarlo Player") :
            Player(t, name) {
    }
    bool getMove(Board*, int &, int &);
    double expansion(int playerType, Board* board);
    double simulation(Board* board);
};

bool MonteCarloPlayer::getMove(Board* board, int &x, int &y) {
        int playerType = board->getTurn();
        int boardSize = board->getBoardSize();

        priority_queue<Cell> moves;
        cout << "Utilities of Moves" << endl;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                int x = i;
                int y = j;
                if(board->getGrid(i,j) != 0)
                    continue;
                Board tempBoard(*board);
                tempBoard.addMove(playerType, x, y);
                    double utility = simulation(&tempBoard);
                    Cell c(i, j, utility);
                    if(tempBoard.isFull()&&tempBoard.checkWin(playerType) == true){
                       return true;
                    }
                moves.push(c);
            }
        }
    if (moves.size() > 0) {
        x = moves.top().x;
        y = moves.top().y;
    } else {
        cout << "Can't find a new replacement" << endl;
    }

        return true;
    }

    double MonteCarloPlayer::simulation(Board *board) {
        double times = 100.0;
        double winning = 0.0;

        for (int i = 0; i < times; i++) {
            Board tempBoard(*board);
            int playerType = tempBoard.getTurn();
            winning += expansion(-1 * playerType, &tempBoard);
        }
        return (double(winning) / (double) times);
    }

    double MonteCarloPlayer::expansion(int playerType, Board *board) {
        playerType = board->getTurn();
        int boardSize = board->getBoardSize();
        if (board->checkWin(type) == true) {
            return 1.0;
        }else if (board->checkWin(-type) == 0) {
            return 0.0;
        }

        vector<int> emptyCells;
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if (board->getGrid(i, j) == 0)
                    emptyCells.push_back(i * boardSize + j);
                return expansion(-1 * playerType, board);
            }
        }

        int index = emptyCells[rand() % emptyCells.size()];
        int x = index / boardSize;
        int y = index % boardSize;
        board->addMove(playerType, x, y);
    }

#endif /* MONTECARLOPLAYER_H_ */
