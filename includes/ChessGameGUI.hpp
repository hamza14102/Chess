#ifndef CHESSGAMEGUI_HPP
#define CHESSGAMEGUI_HPP

#include <SFML/Graphics.hpp>
#include "ChessGame.hpp"

class ChessGameGUI {
    public:
        ChessGameGUI();
        void MainGameLoop();
        void DrawGame();
    private:
        void HighlightTile(loc hlight_loc);
        void LoadSinglePieceTexture(Piece piece);
        void LoadPieceTextures(Color piece_color);
        void LoadSPButtonTexture(std::string button_path);
        void LoadMPButtonTexture(std::string button_path);
        void LoadUndoButtonTexture(std::string button_path);
        void LoadBoardTexture(std::string board_path);
        void LoadFont(std::string font_path);
        void DrawBoard();
        void DrawPiece(int row, int col, Piece piece);
        void DrawText(std::string& text, sf::Vector2f& location, sf::Color color);
        void DrawSPButton();
        void DrawMPButton();
        void DrawUndoButton();
        loc GetMouseClickLoc(sf::Event& mouse_click_event);
        bool SPButtonClicked(sf::Vector2f& click_coords); 
        bool MPButtonClicked(sf::Vector2f& click_coords); 
        bool UndoButtonClicked(sf::Vector2f& click_coords);
        ChessGame game_;
        sf::RenderWindow window_;
        vector<vector<sf::FloatRect>> tile_rects;
        sf::Texture board_texture;
        sf::Sprite sp_button;
        sf::Texture sp_button_texture;
        sf::Sprite mp_button;
        sf::Texture mp_button_texture;
        sf::Font message_font;
        sf::Texture undo_button_texture;
        sf::Sprite undo_button;
        vector<sf::Texture> white_piece_textures;
        vector<sf::Texture> black_piece_textures;
        //const unsigned int board_pixel_len = 1920;
        //const unsigned int board_pixel_width = 1920;
};

#endif