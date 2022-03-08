#include "../includes/ChessGame.hpp"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

ChessGame::ChessGame(): board(Board()){}

void ChessGame::Print() {
    for (unsigned int i = 0; i < board.getLength(); i++) {
        for (unsigned int j = 0; j < board.getWidth(); j++) {
            std::cout << board.At(i, j);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool ChessGame::MakeValidMove(Move move) {
    try {
        board.move(move.from, move.to);
    } catch (std::invalid_argument) {
        return false;
    }
    return true;
}

void ChessGame::MakeCPUMove() {
    // generating random moveset locations.
    srand(time(0));
    loc from = {rand() % 8, rand() % 8};
    loc to = {rand() % 8, rand() % 8};
    while (!MakeValidMove({from, to})) {
        from = {rand() % 8, rand() % 8};
        to = {rand() % 8, rand() % 8};
    }
}

void ChessGame::move(Move move) {
    board.move(move.from, move.to);
    recordOfMoves.push_back(move);
}

void ChessGame::undo() {
    board.undo();
    if (!isMultiplayer) {
        board.undo();
    }
}