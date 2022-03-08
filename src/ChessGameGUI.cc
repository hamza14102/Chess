#include "ChessGameGUI.hpp"

#include <iostream>
#include <string>

ChessGameGUI::ChessGameGUI(): game_(ChessGame()), 
                              window_(sf::RenderWindow(sf::VideoMode(1280, 1400), "Chess Game")) {
    
    // Setting Tile Rects
    float ver_offset = 41.f;
    float hor_offset = 41.f;
    float tile_len = 150.f;
    float tile_width = 150.f;
    sf::Vector2<float> size_vect(tile_width, tile_len);
    for (size_t row = 0; row < game_.GetBoard().getLength(); row++) {
        tile_rects.push_back(vector<sf::FloatRect>());
        for (size_t col = 0; col < game_.GetBoard().getWidth(); col++) {
            sf::Vector2<float> pos_vect(col * tile_len + hor_offset, row * tile_width + ver_offset);
            tile_rects.at(row).push_back(sf::FloatRect(pos_vect, size_vect));
        }
    }

    // Loading board texture
    std::string board_path = "./textures/chess-board.png";
    LoadBoardTexture(board_path);

    // Loading button textures
    std::string sp_button_path = "textures/single_player_button.png";
    std::string mp_button_path = "textures/multiplayer_button.png";
    std::string undo_button_texture = "textures/undo-button.png";
    LoadSPButtonTexture(sp_button_path);
    LoadMPButtonTexture(mp_button_path); 
    LoadUndoButtonTexture(undo_button_texture);

    // Loading message font
    std::string font_path = "fonts/times_new_roman.ttf";
    LoadFont(font_path);

    // Loading piece textures
    LoadPieceTextures(Color::white);
    LoadPieceTextures(Color::black); 

}

void ChessGameGUI::LoadSPButtonTexture(std::string button_path) {
    if (!sp_button_texture.loadFromFile(button_path, sf::IntRect(0, 0, 300, 75))) {
        throw std::runtime_error("Cannot load texture from file");
    }
    sp_button.setTexture(sp_button_texture);
}

void ChessGameGUI::LoadMPButtonTexture(std::string button_path) {
    if (!mp_button_texture.loadFromFile(button_path, sf::IntRect(0, 0, 300, 75))) {
        throw std::runtime_error("Cannot load texture from file");
    }
    mp_button.setTexture(mp_button_texture);
}

void ChessGameGUI::LoadUndoButtonTexture(std::string button_path) {
    if(!undo_button_texture.loadFromFile(button_path, sf::IntRect(0,0,512, 512))) {
        throw std::runtime_error("Cannot load texture from file");
    }
    undo_button.setTexture(undo_button_texture);
    float vert_scale_fac = 0.15f;
    float hor_scale_fac = 0.15f;
    undo_button.setScale(sf::Vector2f(vert_scale_fac, hor_scale_fac));
}


void ChessGameGUI::LoadSinglePieceTexture(Piece piece) {
    std::string piece_path = "";
     switch(piece.color) {
        case Color::white:
            switch(piece.type) {
                case Type::Pawn:
                    piece_path = "textures/white/pawn.png";
                    break;
                case Type::Rook:
                    piece_path = "textures/white/rook.png";
                    break;
                case Type::Bishop:
                    piece_path = "textures/white/bishop.png";
                    break;
                case Type::Knight:
                    piece_path = "textures/white/knight.png";
                    break;
                case Type::King:
                    piece_path = "textures/white/king.png";
                    break;
                case Type::Queen:
                    piece_path = "textures/white/queen.png";
                    break;             
                default:
                break;
            }
        break;
        case Color::black:
            switch(piece.type) {
                case Type::Pawn:
                    piece_path = "textures/black/pawn.png";
                    break;
                case Type::Rook:
                    piece_path = "textures/black/rook.png";
                    break;
                case Type::Bishop:
                    piece_path = "textures/black/bishop.png";
                    break;
                case Type::Knight:
                    piece_path = "textures/black/knight.png";
                    break;
                case Type::King:
                    piece_path = "textures/black/king.png";
                    break;
                case Type::Queen:
                    piece_path = "textures/black/queen.png";
                    break;            
                default:
                break;
            }
        default:
        break;
    }

    // Loading Piece texture
    sf::Texture piece_texture;
    int piece_tex_x_len = 512;
    int piece_tex_y_len = 512;
    if (!piece_path.empty()) {
        if (!piece_texture.loadFromFile(piece_path, sf::IntRect(0, 0, piece_tex_x_len, piece_tex_y_len))) {
            throw std::runtime_error("Cannot Load Texture"); 
        }
    }
    
    // Insert loaded texture into piece texture vector
    if (piece.color == Color::white) {
        white_piece_textures.push_back(piece_texture);
    } else {
        black_piece_textures.push_back(piece_texture);
    }
}

void ChessGameGUI::LoadPieceTextures(Color piece_color) {
    Piece to_load(Type::Empty, Color::white);
    to_load.color = piece_color;
    int piece_type_num = 6; // number of distinct piece types
    for (int i = 0; i < piece_type_num; i++) {
        to_load.type = static_cast<Type>(i);
        LoadSinglePieceTexture(to_load);
    }
}

void ChessGameGUI::LoadFont(std::string font_path) {
    if (!message_font.loadFromFile(font_path)) {
        throw std::runtime_error("Cannot Load Font");
    }
}

void ChessGameGUI::LoadBoardTexture(std::string board_path) {
    if (!board_texture.loadFromFile(board_path)) {
        throw std::runtime_error("Cannot Load Texture"); 
    }
}

void ChessGameGUI::DrawGame() {
    Board& game_board = game_.GetBoard();
    DrawBoard();
    for (size_t row = 0; row < game_board.getLength(); row++) {
        for (size_t col = 0; col < game_board.getWidth(); col++) {
            DrawPiece(row, col, game_board.At(row,col));
        }
    }
}

void ChessGameGUI::DrawBoard() {
    sf::Sprite board_sprite;
    board_sprite.setTexture(board_texture);
    float vert_scale_fac = 0.666f;
    float hor_scale_fac = 0.666f;
    board_sprite.setScale(sf::Vector2f(vert_scale_fac, hor_scale_fac));
    window_.draw(board_sprite);
}

void ChessGameGUI::DrawPiece(int row, int col, Piece piece) {
    // sf::RectangleShape bounding_box(sf::Vector2f(150.f, 150.f));
    // bounding_box.setOutlineThickness(1.f);
    // bounding_box.setOutlineColor(sf::Color::Green);
    if (piece.type != Type::Empty) {
        sf::Sprite piece_sprite;
        sf::Texture piece_texture;
        if (piece.color == Color::white) {
            piece_texture = white_piece_textures.at(piece.type);
        } else {
            piece_texture = black_piece_textures.at(piece.type);
        }
        piece_sprite.setTexture(piece_texture);
        float ver_offset = 41.f;
        float hor_offset = 41.f;
        piece_sprite.setScale(sf::Vector2f(0.26, 0.26));
        float tile_len = 150.f;
        float tile_width = 150.f;
        piece_sprite.setPosition(sf::Vector2f(col * tile_width + ver_offset, row * tile_len + hor_offset));
        // bounding_box.setPosition(sf::Vector2f(col * tile_width + ver_offset, row * tile_len + hor_offset));
        // window.clear(sf::Color::White);
        // window_.draw(bounding_box);
        window_.draw(piece_sprite);
    }
}

loc ChessGameGUI::GetMouseClickLoc(sf::Event& mouse_click_event) {
    int click_x = mouse_click_event.mouseButton.x;
    int click_y =  mouse_click_event.mouseButton.y;
    loc click_loc;
    for (size_t row = 0; row < tile_rects.size(); row++) {
        for (size_t col = 0; col < tile_rects.at(row).size(); col++) {
            if (tile_rects.at(row).at(col).contains(click_x, click_y)) {
                click_loc.x = row;
                click_loc.y = col;
            }
        }
    }
    return click_loc;
}

void ChessGameGUI::DrawText(std::string& text_str, sf::Vector2f& location, sf::Color color) {
    // std::cout << "Printing Error Message" << std::endl;
    if (!text_str.empty()) {
        sf::Text text;
        text.setFont(message_font);
        text.setString(text_str);
        text.setCharacterSize(50);
        text.setFillColor(color);
        text.setPosition(location);
        window_.draw(text);
    }
}

void ChessGameGUI::HighlightTile(loc hlight_loc) {
    sf::FloatRect& to_hlight = tile_rects.at(hlight_loc.x).at(hlight_loc.y);
    sf::Vector2<float> size_vect(to_hlight.width, to_hlight.height);
    sf::Vector2<float> pos_vect(to_hlight.left, to_hlight.top);
    sf::RectangleShape hlight_rect(size_vect);
    hlight_rect.setPosition(pos_vect);
    sf::Color hlight_color(0, 204, 0, 50);
    hlight_rect.setFillColor(hlight_color);
    window_.draw(hlight_rect);
}


void ChessGameGUI::DrawSPButton() {
    sp_button.setPosition(sf::Vector2f(275, 1290));
    window_.draw(sp_button); 
}

void ChessGameGUI::DrawMPButton() {
    mp_button.setPosition(sf::Vector2f(675, 1290));
    window_.draw(mp_button);
}

void ChessGameGUI::DrawUndoButton() {
    undo_button.setPosition(sf::Vector2f(1150, 1290));
    window_.draw(undo_button);
}



bool ChessGameGUI::SPButtonClicked(sf::Vector2f& click_coords) {
    return (sp_button.getGlobalBounds().contains(click_coords));
}

bool ChessGameGUI::MPButtonClicked(sf::Vector2f& click_coords) {
    return (mp_button.getGlobalBounds().contains(click_coords));
}

bool ChessGameGUI::UndoButtonClicked(sf::Vector2f& click_coords) {
    return (undo_button.getGlobalBounds().contains(click_coords));
}


void ChessGameGUI::MainGameLoop() {
    // Persistent variables
    loc click_first_loc;
    loc click_sec_loc;
    bool is_game_mode_set = false;
    std::string error_message = "";

    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event))  {
            switch (event.type) {
                case sf::Event::Closed: {
                    window_.close();
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    if (is_game_mode_set) {
                        // Disable clicks if game is over
                        if (!game_.isGameOver()) {
                            sf::Vector2i click_pixel(event.mouseButton.x, event.mouseButton.y);
                            sf::Vector2f click_coords = window_.mapPixelToCoords(click_pixel);
                            if (UndoButtonClicked(click_coords)) {
                                game_.undo();
                            }
                            else if (click_first_loc.isEmpty()) {
                            //saving first click location
                            click_first_loc = GetMouseClickLoc(event);
                            // std::cout << "First click x: " << click_first_loc.x << std::endl;
                            // std::cout << "First click y: " << click_first_loc.y << std::endl;
                            }
                            else if (click_sec_loc.isEmpty()) {
                                //saving second click location
                                click_sec_loc = GetMouseClickLoc(event);
                                // std::cout << "Second click x: " << click_sec_loc.x << std::endl;
                                // std::cout << "Second click y: " << click_sec_loc.y << std::endl;

                                //moving piece
                                try {
                                    Move new_move;
                                    new_move.from = click_first_loc;
                                    new_move.to = click_sec_loc;
                                    game_.move(new_move);
                                } catch (std::invalid_argument) {
                                    // std::cout << "Made Invalid Move" << std::endl;
                                    error_message = "Invalid Move: Try Again";
                                    click_first_loc.Clear();
                                    click_sec_loc.Clear();
                                    break;
                                }
                                
                                if (!game_.isMultiplayer) {
                                    game_.MakeCPUMove();
                                }

                                // clear first and second click location
                                click_first_loc.Clear();
                                click_sec_loc.Clear();

                                // Setting empty error message
                                error_message = "";

                                //loc click_loc = GetMouseClickLoc(event);
                                // std::cout << "Click col: " << click_loc.x << std::endl;
                                // std::cout << "Click row: " << click_loc.y << std::endl;
                            }
                        }
                    } else {
                        sf::Vector2i click_pixel(event.mouseButton.x, event.mouseButton.y);
                        sf::Vector2f click_coords = window_.mapPixelToCoords(click_pixel);
                        if (SPButtonClicked(click_coords)) {
                            // std::cout << "SP Button Clicked" << std::endl;
                            is_game_mode_set = true;
                            game_.isMultiplayer = false;
                        }
                        if (MPButtonClicked(click_coords)) {
                            // std::cout << "MP Button Clicked" << std::endl;
                            is_game_mode_set = true;
                            game_.isMultiplayer = true;
                        }
                    } 
                        break;
                }

                default: {
                    break;
                }  
            }
        }
        window_.clear(sf::Color::White);
        DrawGame();

        // Draw game mode buttons
        if (!is_game_mode_set) {
            DrawSPButton();
            DrawMPButton();
        } else {
            // Write game over message
            if (game_.isGameOver()) {
                error_message = "Game Over";
                sf::Vector2f err_msg_loc(500, 1300);
                sf::Color err_msg_color = sf::Color::Red;
                DrawText(error_message, err_msg_loc, err_msg_color);
            } else {
                // Write error message
                sf::Vector2f err_msg_loc(350, 1300);
                sf::Color err_msg_color = sf::Color::Red;
                DrawText(error_message, err_msg_loc, err_msg_color);
            }

            // Highlight tile
            if (!click_first_loc.isEmpty()) {
                HighlightTile(click_first_loc);
            }

            // Drawing undo button
            DrawUndoButton();
        }
        window_.display();
    }
}

