#include "../includes/board.hpp"

Piece& Board::At(int row, int col) { return board[row][col]; }

Board::Board() {
  //  pushing first row for white
  board = vector<vector<Piece>>({{Piece(Type::Rook, Color::white),
                                  Piece(Type::Knight, Color::white),
                                  Piece(Type::Bishop, Color::white),
                                  Piece(Type::King, Color::white),
                                  Piece(Type::Queen, Color::white),
                                  Piece(Type::Bishop, Color::white),
                                  Piece(Type::Knight, Color::white),
                                  Piece(Type::Rook, Color::white)}});
  //  pushing pawns for white
  board.push_back(vector<Piece>());
  for (int i = 0; i < 8; i++) {
    board[1].push_back(Piece(Type::Pawn, Color::white));
  }
  //  pushing empty spaces
  for (int i = 2; i < 6; i++) {
    board.push_back(vector<Piece>());
    for (int j = 0; j < 8; j++) {
      board[i].push_back(Piece(Type::Empty, Color::white));
    }
  }
  //  pushing pawns for black
  board.push_back(vector<Piece>());
  for (int i = 0; i < 8; i++) {
    board[6].push_back(Piece(Type::Pawn, Color::black));
  }
  //  pushing last row for black
  board.push_back({Piece(Type::Rook, Color::black),
                   Piece(Type::Knight, Color::black),
                   Piece(Type::Bishop, Color::black),
                   Piece(Type::King, Color::black),
                   Piece(Type::Queen, Color::black),
                   Piece(Type::Bishop, Color::black),
                   Piece(Type::Knight, Color::black),
                   Piece(Type::Rook, Color::black)});
}

void Board::move(loc from, loc to) {

    // checking for all basic invalid moves

  if (from.x > 7 || from.x < 0 || to.x > 7 || to.y < 0 ||
      turnColor != board[from.x][from.y].color ||
      board[from.x][from.y].type == Type::Empty ||
      (from.x == to.x && from.y == to.y)) {
    throw std::invalid_argument("Not a valid move");
  }

    // checking valid moves for kill by pawn 
  if (board[from.x][from.y].type == Type::Pawn) {
    if (board[to.x][to.y].type != Type::Empty &&
        board[from.x][from.y].color == Color::white &&
        (std::abs(from.y - to.y) != 1 || to.x - from.x != 1 ||
         board[to.x][to.y].color == Color::white)) {
      throw std::invalid_argument("Not a valid kill move");
    }
    if (board[to.x][to.y].type != Type::Empty &&
        board[from.x][from.y].color == Color::black &&
        (std::abs(from.y - to.y) != 1 || from.x - to.x != 1 ||
         board[to.x][to.y].color == Color::black)) {
      throw std::invalid_argument("Not a valid kill move");
    }

    // checking for valid moves for pawn 
    if (board[to.x][to.y].type == Type::Empty &&
        (board[from.x][from.y].color == Color::white && from.x == 1) &&
        (from.y != to.y || to.x - from.x <= 0 || to.x - from.x > 2 ||
         (to.x - from.x == 2 &&
          board[from.x + 1][from.y].type != Type::Empty))) {
      throw std::invalid_argument("Not a valid move");
    }
    if (board[to.x][to.y].type == Type::Empty &&
        (board[from.x][from.y].color == Color::black && from.x == 6) &&
        (from.y != to.y || from.x - to.x <= 0 || from.x - to.x > 2 ||
         (from.x - to.x == 2 &&
          board[from.x - 1][from.y].type != Type::Empty))) {
      throw std::invalid_argument("Not a valid move");
    }
    if (board[to.x][to.y].type == Type::Empty &&
        (board[from.x][from.y].color == Color::white && from.x != 1) &&
        (from.y != to.y || to.x - from.x <= 0 || to.x - from.x > 1)) {
      throw std::invalid_argument("Not a valid move");
    }
    if (board[to.x][to.y].type == Type::Empty &&
        (board[from.x][from.y].color == Color::black && from.x != 6) &&
        (from.y != to.y || from.x - to.x <= 0 || from.x - to.x > 1)) {
      throw std::invalid_argument("Not a valid move");
    }
    if (board[to.x][to.y].type == Type::King) {
      isGameActive = false;
    }
  }
    // valid moves for Rook 
  if (board[from.x][from.y].type == Type::Rook) {
    if (from.x != to.x && from.y != to.y) {
      throw std::invalid_argument("Not a valid move");
    }
    //checking if there is a piece in the rooks way 
    if (from.x != to.x) {
      int min = from.x < to.x ? from.x : to.x;
      int max = from.x > to.x ? from.x : to.x;
      for (int i = min + 1; i < max; i++) {
        if (board[i][from.y].type != Type::Empty) {
          throw std::invalid_argument("Not a valid move");
        }
      }
    } else { 
      int min = from.y < to.y ? from.y : to.y;
      int max = from.y > to.y ? from.y : to.y;
      for (int i = min + 1; i < max; i++) {
        if (board[from.x][i].type != Type::Empty) {
          throw std::invalid_argument("Not a valid move");
        }
      }
    }
    //cheking for valid kill moves for rook 
    if (board[to.x][to.y].type != Type::Empty &&
        turnColor == board[to.x][to.y].color) {
      throw std::invalid_argument("Not a valid kill move");
    }
    if (board[to.x][to.y].type == Type::King) {
      isGameActive = false;
    }
  }
    // checking valid moves for bishop 
  if (board[from.x][from.y].type == Type::Bishop) {
    if (std::abs(from.x - to.x) != std::abs(from.y - to.y)) {
      throw std::invalid_argument("Not a valid move");
    }
    //checking if there is any piece in bishops way
    int x_inc = from.x - to.x < 0 ? 1 : -1;
    int y_inc = from.y - to.y < 0 ? 1 : -1;
    int x_pos = from.x;
    int y_pos = from.y;
    for (int i = 1; i < std::abs(from.x - to.x); i++) {
      x_pos += x_inc;
      y_pos += y_inc;
      if (board[x_pos][y_pos].type != Type::Empty) {
        throw std::invalid_argument("Not a valid move");
      }
    }
    //checking valid kill move 
    if (board[to.x][to.y].type != Type::Empty &&
        board[to.x][to.y].color == turnColor) {
      throw std::invalid_argument("Not a valid kill move");
    }
    if (board[to.x][to.y].type == Type::King) {
      isGameActive = false;
    }
  }
    //checking valid move for King 
  if (board[from.x][from.y].type == Type::King) {
    if (std::abs(from.x - to.x) > 1 || std::abs(from.y - to.y) > 1) {
      throw std::invalid_argument("Not a valid move");
    }
    //checking valid kill move for the King 
    if (board[to.x][to.y].type != Type::Empty &&
        board[to.x][to.y].color == turnColor) {
      throw std::invalid_argument("Not a valid kill move");
    }
    if (board[to.x][to.y].type == Type::King) {
      isGameActive = false;
    }
  }
    //checking valid moves for the knight 
  if (board[from.x][from.y].type == Type::Knight) {
    if ((std::abs(from.x - to.x) != 2 || std::abs(from.y - to.y) != 1) &&
        (std::abs(from.x - to.x) != 1 || std::abs(from.y - to.y) != 2)) {
      throw std::invalid_argument("Not a valid move");
    }
    //checking valid Knight kill moves 
    if (board[to.x][to.y].type != Type::Empty &&
        board[to.x][to.y].color == turnColor) {
      throw std::invalid_argument("Not a valid kill move");
    }
    if (board[to.x][to.y].type == Type::King) {
      isGameActive = false;
    }
  }
    //checking queen valid moves
  if (board[from.x][from.y].type == Type::Queen) {
    if ((from.x != to.x && from.y != to.y) &&
        (std::abs(from.x - to.x) != std::abs(from.y - to.y))) {
      throw std::invalid_argument("Not a valid move");
    }
    if ((from.x == to.x || from.y == to.y)) {
      if (from.x != to.x) {
        int min = from.x < to.x ? from.x : to.x;
        int max = from.x > to.x ? from.x : to.x;
        for (int i = min + 1; i < max; i++) {
          if (board[i][from.y].type != Type::Empty) {
            throw std::invalid_argument("Not a valid move");
          }
        }
      } else {
        int min = from.y < to.y ? from.y : to.y;
        int max = from.y > to.y ? from.y : to.y;
        for (int i = min + 1; i < max; i++) {
          if (board[from.x][i].type != Type::Empty) {
            throw std::invalid_argument("Not a valid move");
          }
        }
      }
    } else {
      int x_inc = from.x - to.x < 0 ? 1 : -1;
      int y_inc = from.y - to.y < 0 ? 1 : -1;
      int x_pos = from.x;
      int y_pos = from.y;
      for (int i = 1; i < std::abs(from.x - to.x); i++) {
        x_pos += x_inc;
        y_pos += y_inc;
        if (board[x_pos][y_pos].type != Type::Empty) {
          throw std::invalid_argument("Not a valid move");
        }
      }
    }
    //checking queen valid kill moves 
    if (board[to.x][to.y].type != Type::Empty &&
        board[to.x][to.y].color == turnColor) {
      throw std::invalid_argument("Not a valid kill move");
    }
    // game over condition 
    if (board[to.x][to.y].type == Type::King) {
      isGameActive = false;
    }
  }
  
  lastMove lastMove = {{from.x, from.y}, {to.x, to.y}, board[from.x][from.y], board[to.x][to.y]};
  movelist.push(lastMove);
  board[to.x][to.y] = board[from.x][from.y];
  // checking if last move was white 
  board[from.x][from.y] = Piece(Type::Empty, Color::white); 
  // checking if last move was black 
  turnColor =
      board[to.x][to.y].color == Color::white ? Color::black : Color::white;
}

bool operator==(const Piece& lhs, const Piece& rhs) {
  return lhs.type == rhs.type && lhs.color == rhs.color;
}

ostream& operator<<(ostream& os, const Piece& piece) {
  if (piece.color == Color::white) {
    if (piece.type == Type::Pawn) {
      os << "\033[47;30m|P|\033[0m";
    } else if (piece.type == Type::Bishop) {
      os << "\033[47;30m|B|\033[0m";
    } else if (piece.type == Type::Rook) {
      os << "\033[47;30m|R|\033[0m";
    } else if (piece.type == Type::Knight) {
      os << "\033[47;30m|K|\033[0m";
    } else if (piece.type == Type::King) {
      os << "\033[47;30m|*|\033[0m";
    } else if (piece.type == Type::Queen) {
      os << "\033[47;30m|Q|\033[0m";
    } else {
      os << "| |";
    }
  } else {
    if (piece.type == Type::Pawn) {
      os << "\033[40;37m|P|\033[0m";
    } else if (piece.type == Type::Bishop) {
      os << "\033[40;37m|B|\033[0m";
    } else if (piece.type == Type::Rook) {
      os << "\033[40;37m|R|\033[0m";
    } else if (piece.type == Type::Knight) {
      os << "\033[40;37m|K|\033[0m";
    } else if (piece.type == Type::King) {
      os << "\033[40;37m|*|\033[0m";
    } else if (piece.type == Type::Queen) {
      os << "\033[40;37m|Q|\033[0m";
    } else {
      os << "\033[40;370m| |\033[0m";
    }
  }
  return os;
}


void Board::undo() {
  // undo funciton which can take back the move that was made 
  if (!movelist.empty()) {
    turnColor = turnColor == Color::white ? Color::black : Color::white;
    board[movelist.top().from.x][movelist.top().from.y] = movelist.top().fromP;
    board[movelist.top().to.x][movelist.top().to.y] = movelist.top().toP;
    movelist.pop();
  }
}