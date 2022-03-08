#pragma once

#include <vector>
#include <iostream>
#include <stack>

using namespace std;

        
/*
*   Enum class to store the type of the chess piece or to store if it is empty.
*/
enum Type {Pawn, Rook, Bishop, Knight, King, Queen, Empty};
/*
*   Enum class to store the color of the piece as white or black.
*/
enum Color {white, black};

/*
*   A simple struct to store an row and col based location as a single parameter.
*/
struct loc {
    int x = -1;
    int y = -1;
    
    void Clear() {
        x = -1;
        y = -1;
    }
    
    bool isEmpty() {
        return (x == -1 && y == -1);
    }
};

/*
*   Struct to store a piece with a type and color on the chess board.
*/
struct Piece {
    //  type of the piece (pawn, bishop, rook, etc.) or if it is empty
    Type type;
    //  color (either black or white)
    Color color;
    //  base constructor for piece
    Piece(Type set_type, Color set_color) {
        type = set_type;
        color = set_color;
    };
};

struct lastMove {
    loc from = {0,0};
    loc to = {0,0};
    Piece fromP = {Type::Rook, Color::white};
    Piece toP = {Type::Rook, Color::white};
};

/*
*   Board Class
*/
class Board {
    public:
        /*
        *   Base constructor for board that sets up the board with the startup chess pieces.
        *   That is white and black lineup on the opposite sides with all pieces in game.
        */
        Board();
        /*
        *   stores the board as a 2D vector of pieces to keep track of all the pieces.
        */
        vector<vector<Piece>> board;
        //  getter function for the Board class to get a piece at location (x, y).
        Piece& At(int row, int col);
        /*
        *   Makes the piece at location "from" move to location "to" -only and only if it is a valid move-
        */
        void move(loc from, loc to);
        //  getter for the length;
        unsigned int getLength() {return length;}
        //  getter for the width;
        unsigned int getWidth() {return width;}
        //to see if the game is over
        bool isGameActive = true;
        // undo the last move;
        void undo();
    private:
    unsigned int length = 8;
    unsigned int width = 8;
    Color turnColor = Color::white;
    /*
    *   Stores the white pieces that have been knocked out to help with the point tracking and score displaying system.
    */
    vector<Piece> white_out;
    /*
    *   Stores the black pieces that have been knocked out to help with the point tracking and score displaying system.
    */
    vector<Piece> black_out;
    /*
    *   Stores the black pieces that have been knocked out to help with the point tracking and score displaying system.
    */
    stack<lastMove> movelist;
};


//  operator overloaded to help compare two chess pieces
bool operator==(const Piece& lhs, const Piece& rhs);

//  operator overloaded to help print the pieces on the output stream.
ostream& operator<<(ostream& os, const Piece& piece);