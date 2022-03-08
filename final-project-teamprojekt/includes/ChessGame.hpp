#pragma once

#include "./board.hpp"

struct Move {
    loc from;
    loc to;
    Piece last = {Type::Empty, Color::white};
};
class ChessGame {
    public:
        /*
        *   Makes a Base constructor which sets up the board with the chess pieces set up to initial position.
        */
        ChessGame();
        /*
        *   Prints out the board locally on a terminal window.
        */
        void Print();
        /*
        *   Moves chess piece at location "from" to location "to" -if and only if it is a valid move- otherwise throw error.
        */
        void move(Move move);
        void undo();
        Board& GetBoard() {return board;}
        void MakeCPUMove();
        bool isMultiplayer;
        bool isGameOver() {return !board.isGameActive;}

    private:
        bool MakeValidMove(Move move);
        // Move GetMoveCPU();
        /*
        *   Private member variable to store a chess board for the current game.
        */
        Board board;
        std::vector<Move> recordOfMoves;
};
