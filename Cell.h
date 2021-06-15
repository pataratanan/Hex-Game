/**
 * Declaration
 *
 * I hereby certify that no other part of this submission has been copied from any other sources, including the
 * Internet, books or other student’s work except the ones I have listed below. No part of the code has been
 * written/produced for me by another person or copied from any other source.
 *
 * I hold a copy of this assignment that I can produce if the original is lost or damaged.
 */

#ifndef CELL_H_
#define CELL_H_

struct Cell {
    int x;
    int y;
    double heuristic;

    Cell(int xx, int yy, double hh):x(xx), y(yy), heuristic(hh) {}

    bool operator<(const Cell& c) const {
        return heuristic < c.heuristic;
    }
};

#endif /* CELL_H_ */
