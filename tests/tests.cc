#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include <stdexcept>
#include <board.hpp>
#include <ChessGame.hpp> 



TEST_CASE ("Pawn valid move 2 space", "[pawn]") { 
    ChessGame* game = new ChessGame();
    game->move({{1,1}, {3,1}}); 
    // moves two spaces forward
    REQUIRE(game->GetBoard().At(3,1).type == Type::Pawn);
    REQUIRE(game->GetBoard().At(3,1).color == Color::white);
}

TEST_CASE ("Pawn valid move 1 space", "[pawn]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,1}, {2,1}}); 
    // moves one space forward 
    REQUIRE(game->GetBoard().At(2,1).type == Type::Pawn);
    REQUIRE(game->GetBoard().At(2,1).color == Color::white);
}

TEST_CASE ("Pawn invalid move 2 space", "[pawn]") { 
    ChessGame* game = new ChessGame();
    game->move({{1,1}, {2,1}}); 
    game->move({{6,5}, {5,5}}); 
    //throws error 
    REQUIRE_THROWS(game->move({{2,1}, {4,1}})); 
    // cannot move two spaces after the same pawn has already moved 
    REQUIRE_FALSE(game->GetBoard().At(4,1).type == Type::Pawn);
}

TEST_CASE ("Pawn invalid diagonal 1 space", "[pawn]") { 
    ChessGame* game = new ChessGame(); 
    //throws error 
    REQUIRE_THROWS(game->move({{1,1}, {2,2}})); 
    // cannot move diagonal if pawn is not killing something 
    REQUIRE_FALSE(game->GetBoard().At(2,2).type == Type::Pawn);
}

TEST_CASE ("Knight valid move", "[knight]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{0,1}, {2,0}}); 
    // valid night move, 2 forward and one to the left 
    REQUIRE(game->GetBoard().At(2,0).type == Type::Knight);
    REQUIRE(game->GetBoard().At(2,0).color == Color::white);
}

TEST_CASE ("Knight invalid move", "[knight]") { 
    ChessGame* game = new ChessGame(); 
    //throws error 
    REQUIRE_THROWS(game->move({{0,1}, {1,5}}));
    // invalid movement of knight
    REQUIRE_FALSE(game->GetBoard().At(1,5).type == Type::Knight);
}

TEST_CASE ("Rook valid move", "[Rook]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,0}, {3,0}});
    game->MakeCPUMove();
    game->move({{0,0}, {2,0}}); 
    // rook movement verticle 
    REQUIRE(game->GetBoard().At(2,0).type == Type::Rook);
    REQUIRE(game->GetBoard().At(2,0).color == Color::white);

    game->MakeCPUMove(); 
    game->move({{2,0} , {2, 5}}); 
    // rook horizontal movement
    REQUIRE(game->GetBoard().At(2,5).type == Type::Rook);
    REQUIRE(game->GetBoard().At(2,5).color == Color::white);
}

TEST_CASE ("Rook invalid move", "[Rook]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,0}, {3,0}});
    game->MakeCPUMove();
    //throws error
    REQUIRE_THROWS(game->move({{0,0}, {5,0}})); 
    // rook can't move if there is a piece in its way (verticle)
    REQUIRE_FALSE(game->GetBoard().At(5,0).type == Type::Rook);
    //REQUIRE_FALSE(game->GetBoard().At(5,0).color == Color::white);

    game->MakeCPUMove(); 
    //throws error
    REQUIRE_THROWS(game->move({{0,0} , {0, 5}})); 
    // rook can't move if there is a piece in its way (horizontal)
    REQUIRE_FALSE(game->GetBoard().At(0,5).type == Type::Rook);
    //REQUIRE_FALSE(game->GetBoard().At(0,5).color == Color::white);
}

TEST_CASE ("Bishop valid move", "[bishop]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,3}, {2,3}});
    game->MakeCPUMove();
    game->move({{0,2}, {4,6}}); 
    //bishop movement diagonal 
    REQUIRE(game->GetBoard().At(4,6).type == Type::Bishop);
    REQUIRE(game->GetBoard().At(4,6).color == Color::white);
}

TEST_CASE ("Bishop invalid move", "[bishop]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,1}, {2,1}});
    game->MakeCPUMove();
    //throws error 
    REQUIRE_THROWS(game->move({{0,2}, {4,6}})); 
    //bishop cannot move diagonal if there is a piece in its way 
    REQUIRE_FALSE(game->GetBoard().At(4,6).type == Type::Bishop);
    //REQUIRE_FALSE(game->GetBoard().At(4,6).color == Color::white);
}

TEST_CASE ("All queen valid moves", "[queen]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,4}, {3,4}}); 
    game->move({{6,3}, {5,3}}); 
    game->move({{0,4}, {2,4}}); 
    // verticle movement 
    REQUIRE(game->GetBoard().At(2,4).type == Type::Queen);
    REQUIRE(game->GetBoard().At(2,4).color == Color::white);

    game->move({{5,3}, {4,3}}); 
    game->move({{2,4}, {2,0}}); 
    // horizontal movement  
    REQUIRE(game->GetBoard().At(2,0).type == Type::Queen);
    REQUIRE(game->GetBoard().At(2,0).color == Color::white);

    game->move({{6,2} , {5,2}}); 
    game->move({{2,0}  , {4,2}}); 
    //diagonal movement 
    REQUIRE(game->GetBoard().At(4,2).type == Type::Queen);
    REQUIRE(game->GetBoard().At(4,2).color == Color::white);
}


TEST_CASE ("All queen invalid moves", "[queen]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,4}, {3,4}}); 
    game->MakeCPUMove(); 
    //throws error
    REQUIRE_THROWS(game->move({{0,4}, {4,4}}));
     // verticle movement with a piece in the way is not possible 
    REQUIRE_FALSE(game->GetBoard().At(4,4).type == Type::Queen);
    //REQUIRE_FALSE(game->GetBoard().At(4,3).color == Color::white);

    //throws error
    REQUIRE_THROWS(game->move({{0,4}, {0,5}})); 
    // horizontal movement with a piece in the way is not possible 
    REQUIRE_FALSE(game->GetBoard().At(0,5).type == Type::Queen);
    //REQUIRE_FALSE(game->GetBoard().At(0,5).color == Color::white);

    //throws error 
    REQUIRE_THROWS(game->move({{0,4} , {1,5}})); 
    //diagonal movement with a piece on the place to move is not possible 
    REQUIRE_FALSE(game->GetBoard().At(1,5).type == Type::Queen);
    //REQUIRE_FALSE(game->GetBoard().At(1,4).color == Color::white);
}

TEST_CASE ("Valid king movements", "[king]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,3} , {2,3}});
    game->MakeCPUMove();
    game->move({{0,3} , {1,3}}); // moving forward 
    REQUIRE(game->GetBoard().At(1,3).type == Type::King);
    REQUIRE(game->GetBoard().At(1,3).color == Color::white); 

    game->MakeCPUMove(); 
    game->move({{1,3} , {2,4}}); // moving diagonal 
    REQUIRE(game->GetBoard().At(2,4).type == Type::King);
    REQUIRE(game->GetBoard().At(2,4).color == Color::white); 
}

TEST_CASE ("Invalid king movements", "[king]") { 
    ChessGame* game = new ChessGame(); 
    // throws error
    REQUIRE_THROWS(game->move({{0,3} , {1,3}})); 
    // can't move forward if there is a piece that already exists 
    REQUIRE_FALSE(game->GetBoard().At(1,3).type == Type::King);
    //REQUIRE(game->GetBoard().At(1,4).color == Color::white); 

    game->MakeCPUMove(); 
    // throws error 
    REQUIRE_THROWS(game->move({{0,3} , {1,2}})); 
    // cant move diagonal 
    REQUIRE_FALSE(game->GetBoard().At(1,2).type == Type::King);
    //REQUIRE(game->GetBoard().At(2,3).color == Color::white); 
}

TEST_CASE ("Valid kill move by pawn" , "[kill_move_pawn") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,3} , {3,3}}); 
    game->move({{6,4}, {4,4}});
    game->move({{3,3} , {4,4}}); // kill pawn 
    REQUIRE(game->GetBoard().At(4,4).type == Type::Pawn);
    REQUIRE(game->GetBoard().At(4,4).color == Color::white); 
}

TEST_CASE ("Valid kill move by knight" , "[Kill_move_knight]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,3} , {2,3}}); 
    game->move({{6,3}, {5,3}});
    game->move({{0,1} , {2,2}});
    game->move({{7,4} , {3,0}});  
    game->move({{2,2} , {3,0}});
    // kill queen
    REQUIRE(game->GetBoard().At(3,0).type == Type::Knight);
    REQUIRE(game->GetBoard().At(3,0).color == Color::white); 
}

TEST_CASE ("Valid Kill move by bishop", "[kill_move_bishop]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,7} , {2,7}}); 
    game->move({{6,3} , {5,3}}); 
    game->move({{1,1} , {2,1}}); 
    game->move({{7,2} , {2,7}}); 
    // kill pawn 
    REQUIRE(game->GetBoard().At(2,7).type == Type::Bishop);
    REQUIRE(game->GetBoard().At(2,7).color == Color::black); 
}

TEST_CASE ("Valid kill move by rook", "[kill_move_rook]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,0} , {3,0}}); 
    game->move({{6,3} , {5,3}}); 
    game->move({{0,0} , {2,0}}); 
    game->move({{7,2} , {2,7}});
    game->move({{2,0} , {2,7}}); // kill bishop 
    REQUIRE(game->GetBoard().At(2,7).type == Type::Rook);
    REQUIRE(game->GetBoard().At(2,7).color == Color::white); 
}

TEST_CASE ("Valid kill move by queen" , "[kill_by_queen]") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,3} , {2,3}}); 
    game->move({{6,0}, {4,0}}); 
    game->move({{0,4} , {4,0}});
    // kill pawn 
    REQUIRE(game->GetBoard().At(4,0).type == Type::Queen);
    REQUIRE(game->GetBoard().At(4,0).color == Color::white); 
}

TEST_CASE ("Game over coniditon" , "[game_over") { 
    ChessGame* game = new ChessGame(); 
    game->move({{1,1} , {3,1}});
    game->move({{6,3} , {4,3}}); 
    game->move({{1,2} , {2,2}}); 
    game->move({{7,4} , {3,0}}); 
    game->move({{1,7} , {2,7}}); 
    game->move({{3,0} , {0,3}});
    // king is dead 
    REQUIRE(game->GetBoard().At(0,3).type == Type::Queen);
    REQUIRE(game->GetBoard().At(0,3).color == Color::black); 
}






