/**
 * Declaration
 *
 * I hereby certify that no other part of this submission has been copied from any other sources, including the
 * Internet, books or other student’s work except the ones I have listed below. No part of the code has been
 * written/produced for me by another person or copied from any other source.
 *
 * I hold a copy of this assignment that I can produce if the original is lost or damaged.
 */

#ifndef PLAYER_H_
#define PLAYER_H_
class Player {
protected:
    int type;
    string name; //e.g computer player or human player
public:
    Player(int t, string i) :
            type(t), name(i) {
    }

    string getPlayerName() {
        return name;
    }

    int getType() {
        return type;
    }

    virtual bool getMove(Board *board, int &x, int &y) = 0;

    virtual ~Player() {
    }
};

#endif /* PLAYER_H_ */
