/**
 * Declaration
 *
 * I hereby certify that no other part of this submission has been copied from any other sources, including the
 * Internet, books or other student’s work except the ones I have listed below. No part of the code has been
 * written/produced for me by another person or copied from any other source.
 *
 * I hold a copy of this assignment that I can produce if the original is lost or damaged.
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <iostream>
#include <list>
#include <iterator>
#include <stack>
#include <vector>
using namespace std;
class Board {
private:
    list<int> emptyList;
    int boardSize;
    int turn;
    int **grid;
    int count;
    bool linearSearch(vector<int>, int);
    int getRow(int);
    int getCol(int);
public:
    Board(int bs) {
        boardSize = bs;
        grid = new int*[boardSize];
        for (int i = 0; i < boardSize; i++)
            grid[i] = new int[boardSize];

        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++) {
                grid[i][j] = 0;
            }
        turn = 1;

        //put it into the list
        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++)
                emptyList.push_back(i*boardSize+j);

        count = 0;
    }

    virtual ~Board() {
        for (int i = 0; i < boardSize; i++)
            delete[] grid[i];

        delete[] grid;
    }

    Board(Board &cboard) {
        boardSize = cboard.getBoardSize();

        grid = new int*[boardSize];
        for (int i = 0; i < boardSize; i++)
            grid[i] = new int[boardSize];

        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++)
                grid[i][j] = 0;

        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++) {
                grid[i][j] = cboard.getGrid(i, j);
            }
        emptyList = cboard.emptyList;
        turn = cboard.getTurn();
        count = cboard.count;
    }

    int getBoardSize() {
        return boardSize;
    }
    int getGrid(int x, int y) {
        return grid[x][y];
    }
    int getTurn() {
        return turn;
    }

    bool validInput(int, int);
    bool addMove(int playerType, int x, int y);
    int checkWinningStatus(int playerType) {
        //To be implemented
        if(straightLine(playerType))
           return playerType;

        if(checkWin(playerType))
           return playerType;

        return 0;
    }
    void printBoard();
    bool straightLine(int playerType);
    bool isFull();
    bool randomMove(int &x, int &y);
    stack<int> getNeighbours(int playerType, int x, int y);
    bool checkRow(int);
    bool checkCol(int);
    bool checkWin(int playerType);
    void printStack(stack<int> s);
    int heuristics(int playerType);

};
int Board::heuristics(int playerType) {
    int length = 0;

    //check rows should be Blue if blue
    //check rows
    if(playerType == -1) {
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                int k = 0;
                for (int l = 0; j + l < boardSize; l++) {
                    if (grid[i][j + l] == playerType)
                        k++;
                    else {
                        break;
                        k = 0;
                    }
                }

                if (k > length) {
                    length = k;
                }
            }
        }
    }

    //check column should be Red if red
    //check column
    if(playerType == 1) {
        for (int j = 0; j < boardSize; j++) {
            for (int i = 0; i < boardSize; i++) {
                int k = 0;
                for (int l = 0; i + l < boardSize; l++) {
                    if (grid[i + l][j] == playerType)
                        k++;
                    else {
                        break;
                        k = 0;
                    }
                }
                if (k > length)
                    length = k;
            }
        }
    }

    return length;
}
void Board::printStack(stack<int> s){
    while(!s.empty()){
        cout << "(" << s.top() / boardSize << "," << s.top() % boardSize  << ")here..." << endl;
        s.pop();
    }
}
bool Board::linearSearch(vector<int> visited, int target) {
    for (int index = 0; index < visited.size(); index++)
        if (visited[index] == target)
            return true;

    return false;
}
bool Board::checkWin(int playerType) {
    bool win = true;
    vector<int> visited;
    stack<int> trackingStack;
    for (int i = 0; i < boardSize; i++) {
        if (playerType == -1 && grid[i][0] == -1) { //blue = left column
            trackingStack.push(i * boardSize + 0);
        }
        if (playerType == 1 && grid[0][i] == 1) { //red = top row
            trackingStack.push(0 * boardSize + i);
        }
    }

        while (!trackingStack.empty()) {
            int currentNode = trackingStack.top();
            int x = currentNode / boardSize;
            int y = currentNode % boardSize;
            visited.push_back(currentNode);
            //cout << currentNode << " ";
            trackingStack.pop();

            if (playerType == -1) {
                if (y == boardSize - 1) { //blue right column
                    return win;
                }
            }
            if (playerType == 1) {
                if (x == boardSize - 1) { //red last row
                    return win;
                }
            }

            stack<int> neighbours = getNeighbours(playerType, x, y);
            while (!neighbours.empty()) {
                int n = neighbours.top();
                neighbours.pop();
                if (!linearSearch(visited, n))
                    trackingStack.push(n);
                visited.push_back(n);
            }
        }

    return false;
}
bool Board::checkRow(int row) {
    bool win = true;
    for (int i = 0; i < boardSize; i++) {
        if (grid[row][i] != -1) {
            win = false;
        }
    }
        return win;
}
bool Board::checkCol(int col) {
    bool win = true;
    for (int i = 0; i < boardSize; i++) {
        if (grid[i][col] != 1) {
            win = false;
        }
    }
        return win;
}
bool Board::straightLine(int playerType){
    bool win = true;
    for (int i = 0; i < boardSize; i++) {
        if (playerType == -1) {
             if (checkRow(i)) {
                cout << "Wins StraightLine!!!\n";
                return win;
            }
        }
            if (playerType == 1) {
                if (checkCol(i)) {
                    cout << "Wins StraightLine!!!\n";
                    return win;
                }
            }
    }
            return false;
}
bool Board::randomMove(int &x, int &y){
    int random = rand() % emptyList.size();
    list<int>::iterator i = emptyList.begin();
    advance(i, random);
    x = (*i) / boardSize;
    y = (*i) % boardSize;
    emptyList.remove(x*boardSize+y);
    return true;
}
bool Board::isFull(){
    if(count == boardSize * boardSize)
        cout << "Full Board!!" << endl;
        return false;
}
bool Board::validInput(int x, int y) {
    if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) {
        cout << "Move (" << x + 1 << ", " << y + 1 << ") out of range!" << endl;
        return false;
    }
    if (grid[x][y] != 0) {
        cout << "Invalid move. The cell has been occupied. from validInput function" << endl;
        return false;
    }
    return true;
}
bool Board::addMove(int playerType, int x, int y) {
        if (playerType != turn) {
            cout << "It is not the player's turn!" << endl;
            return false;
        }
        if (grid[x][y] != 0) {
            cout << "Invalid move. The cell has been occupied. from add move function" << endl;
            return false;
        }
        grid[x][y] = playerType;
        turn = -1 * turn;
        count++;
        emptyList.remove(x*boardSize+y);
        return true;
    }

void Board::printBoard() {
    cout << "   ";
    for (int j = 0; j < boardSize; j++) {
        if (j < 9)
            cout << j + 1 << "   ";
        else
            cout << j + 1 << "  ";
    }
    cout << endl;

    cout << "   ";
    for (int j = 0; j < boardSize; j++) {
        cout << "----";
    }
    cout << endl;

    for (int i = 0; i < boardSize; i++) {
        for (int k = 0; k < i; k++)
            cout << "  ";

        if (i < 9)
            cout << " " << i + 1 << " ";
        else
            cout << i + 1 << " ";

        for (int j = 0; j < boardSize; j++) {
            if (grid[i][j] == 0) {
                if (j == 0) {
                    cout << "|   |";
                } else {
                    cout << "   |";
                }
            } else if (grid[i][j] == 1) {
                if (j == 0) {
                    cout << "| R |";
                } else {
                    cout << " R |";
                }
            } else {
                if (j == 0) {
                    cout << "| B |";
                } else {
                    cout << " B |";
                }
            }
        }
        cout << endl;
    }

    for (int k = 0; k <= boardSize; k++)
        cout << "  ";

    for (int j = 0; j < boardSize; j++) {
        cout << "----";
    }

    cout << endl;
    cout << endl;
}
stack<int> Board::getNeighbours(int playerType, int x, int y){
    stack<int> neighbours;
    //downleft neighbors
    if(x + 1 < boardSize && y - 1 >= 0 && grid[x+1][y-1] == playerType){
        neighbours.push((x+1)*boardSize+(y-1));
    }
    //down
    if(x + 1 < boardSize && grid[x + 1][y] == playerType){
        neighbours.push((x+1)*boardSize+(y));
    }
    //right neighbors
    if(y + 1 < boardSize && grid[x][y + 1] == playerType){
        neighbours.push(x*boardSize+(y+1));
    }
    //upright neighbors
    if(x - 1 >= 0 && y + 1 < boardSize && grid[x-1][y+1] == playerType){
        neighbours.push((x-1)*boardSize+(y+1));
    }
    //up
    if(x - 1 >= 0  && grid[x-1][y] == playerType){
        neighbours.push((x-1)*boardSize+(y));
    }
    //left neighbors
    if(y - 1 >= 0 && grid[x][y - 1] == playerType){
        neighbours.push(x*boardSize+(y-1));
    }
    return neighbours;
}
#endif /* BOARD_H_ */
