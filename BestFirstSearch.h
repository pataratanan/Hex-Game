/**
 * Declaration
 *
 * I hereby certify that no other part of this submission has been copied from any other sources, including the
 * Internet, books or other student’s work except the ones I have listed below. No part of the code has been
 * written/produced for me by another person or copied from any other source.
 *
 * I hold a copy of this assignment that I can produce if the original is lost or damaged.
 */

#ifndef INC_20310367_BESTFIRSTSEARCH_H
#define INC_20310367_BESTFIRSTSEARCH_H
class BestFirstSearch: public Player {
public:
    BestFirstSearch(int t, string name = "SmartPlayer"):
            Player(t,name){
    }
    bool getMove(Board*, int&, int&);
};

//this function is for smartplayer
bool BestFirstSearch::getMove(Board* board, int& x, int& y) {

    int boardSize = board->getBoardSize();
    int playerType = board->getTurn();
    priority_queue<Cell> moves;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            //x = i;
            //y = j; //right one
            Board tempBoard(*board);
            if (tempBoard.validInput(i, j)) {
                tempBoard.addMove(playerType, i, j);
                Cell c(i, j, tempBoard.heuristics(playerType));
                    moves.push(c);
            }
        }
    }

    if (moves.size() > 0) {
        x = moves.top().x;
        y = moves.top().y;
    } else {
        cout << "Can't find a new replacement" << endl;
    }

    cout << "Heuristic = " << moves.top().heuristic << " at ("
         << (x + 1) << "," << (y + 1) << ")" << endl;

    return true;
}
#endif //INC_20310367_BESTFIRSTSEARCH_H
