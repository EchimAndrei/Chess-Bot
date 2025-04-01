#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <iostream>

// This is a project that implements a chess game using the SFML library.
// This is a test.

enum class ChessPiece {
    KingWhite, QueenWhite, BishopWhite, KnightWhite, RookWhite, PawnWhite,
    KingBlack, QueenBlack, BishopBlack, KnightBlack, RookBlack, PawnBlack,
    Count
};

std::ostream &operator<<(std::ostream &os, const ChessPiece &piece) {
    switch (piece) {
    case ChessPiece::KingWhite:   os << "KingWhite"; break;
    case ChessPiece::QueenWhite:  os << "QueenWhite"; break;
    case ChessPiece::BishopWhite: os << "BishopWhite"; break;
    case ChessPiece::KnightWhite: os << "KnightWhite"; break;
    case ChessPiece::RookWhite:   os << "RookWhite"; break;
    case ChessPiece::PawnWhite:   os << "PawnWhite"; break;
    case ChessPiece::KingBlack:   os << "KingBlack"; break;
    case ChessPiece::QueenBlack:  os << "QueenBlack"; break;
    case ChessPiece::BishopBlack: os << "BishopBlack"; break;
    case ChessPiece::KnightBlack: os << "KnightBlack"; break;
    case ChessPiece::RookBlack:   os << "RookBlack"; break;
    case ChessPiece::PawnBlack:   os << "PawnBlack"; break;
    case ChessPiece::Count:       os << "Invalid"; break;
    default:                      os << "Unknown"; break;
    }
    return os;
}

// Define the initial positions of each piece on the board
std::array<std::array<ChessPiece, 8>, 8> clean_board = { {
    {ChessPiece::RookBlack, ChessPiece::KnightBlack, ChessPiece::BishopBlack, ChessPiece::QueenBlack, ChessPiece::KingBlack, ChessPiece::BishopBlack, ChessPiece::KnightBlack, ChessPiece::RookBlack},
    {ChessPiece::PawnBlack, ChessPiece::PawnBlack, ChessPiece::PawnBlack, ChessPiece::PawnBlack, ChessPiece::PawnBlack, ChessPiece::PawnBlack, ChessPiece::PawnBlack, ChessPiece::PawnBlack},
    {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
    {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
    {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
    {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
    {ChessPiece::PawnWhite, ChessPiece::PawnWhite, ChessPiece::PawnWhite, ChessPiece::PawnWhite, ChessPiece::PawnWhite, ChessPiece::PawnWhite, ChessPiece::PawnWhite, ChessPiece::PawnWhite},
    {ChessPiece::RookWhite, ChessPiece::KnightWhite, ChessPiece::BishopWhite, ChessPiece::QueenWhite, ChessPiece::KingWhite, ChessPiece::BishopWhite, ChessPiece::KnightWhite, ChessPiece::RookWhite}
} };
// std::array<std::array<ChessPiece, 8>, 8> clean_board = { {
//     {ChessPiece::KingBlack, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
//     {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::RookWhite},
//     {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
//     {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
//     {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
//     {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
//     {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count},
//     {ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::KingWhite, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count, ChessPiece::Count}
// } };
std::array<std::array<ChessPiece, 8>, 8> board = clean_board;


class ChessBoard {
public:
    ChessBoard() {
        loadTextures();
        setupSprites();
        loadBackground();
    }

    sf::Sprite &getPieceSprite(ChessPiece piece) {
        return sprites[static_cast<int>(piece)];
    }

    sf::Sprite &getBackgroundSprite() {
        return backgroundSprite;
    }

    sf::Sprite &getNotationSprite() {
        return notationSprite;
    }

    void removePieceAt(int x, int y) {
        board[x][y] = ChessPiece::Count;
    }

    void movePiece(int startX, int startY, int endX, int endY) {
        board[endX][endY] = board[startX][startY];
        board[startX][startY] = ChessPiece::Count;
    }

private:
    std::array<sf::Texture, static_cast<int>(ChessPiece::Count)> textures;
    std::array<sf::Sprite, static_cast<int>(ChessPiece::Count)> sprites;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture notationTexture;
    sf::Sprite notationSprite;

    void loadTextures() {
        textures[static_cast<int>(ChessPiece::KingWhite)].loadFromFile("pieces/wk.png");
        textures[static_cast<int>(ChessPiece::QueenWhite)].loadFromFile("pieces/wq.png");
        textures[static_cast<int>(ChessPiece::BishopWhite)].loadFromFile("pieces/wb.png");
        textures[static_cast<int>(ChessPiece::KnightWhite)].loadFromFile("pieces/wn.png");
        textures[static_cast<int>(ChessPiece::RookWhite)].loadFromFile("pieces/wr.png");
        textures[static_cast<int>(ChessPiece::PawnWhite)].loadFromFile("pieces/wp.png");
        textures[static_cast<int>(ChessPiece::KingBlack)].loadFromFile("pieces/bk.png");
        textures[static_cast<int>(ChessPiece::QueenBlack)].loadFromFile("pieces/bq.png");
        textures[static_cast<int>(ChessPiece::BishopBlack)].loadFromFile("pieces/bb.png");
        textures[static_cast<int>(ChessPiece::KnightBlack)].loadFromFile("pieces/bn.png");
        textures[static_cast<int>(ChessPiece::RookBlack)].loadFromFile("pieces/br.png");
        textures[static_cast<int>(ChessPiece::PawnBlack)].loadFromFile("pieces/bp.png");
    }

    void setupSprites() {
        // Scaling factor to convert 150x150 to 100x100
        float scaleX = 100.0f / 150.0f;
        float scaleY = 100.0f / 150.0f;

        for (int i = 0; i < static_cast<int>(ChessPiece::Count); ++i) {
            sprites[i].setTexture(textures[i]);
            sprites[i].setScale(scaleX, scaleY);
        }
    }

    void loadBackground() {
        if (!backgroundTexture.loadFromFile("board.png")) {
            exit(1); // Exit if the image cannot be loaded
        }

        backgroundSprite.setTexture(backgroundTexture);

        // Get the original size of the texture
        sf::Vector2u textureSize = backgroundTexture.getSize();

        // Calculate the scale factors
        float scaleX = 800.0f / textureSize.x;
        float scaleY = 800.0f / textureSize.y;

        // Set the scale of the sprite
        backgroundSprite.setScale(scaleX, scaleY);


        // Load notation.png
        if (!notationTexture.loadFromFile("notation.png")) {
            exit(1); // Exit if the image cannot be loaded
        }

        // Get the original size of the texture
        textureSize = notationTexture.getSize();

        // Calculate the scale factors
        scaleX = 800.0f / textureSize.x;
        scaleY = 800.0f / textureSize.y;

        notationSprite.setTexture(notationTexture);

        // Set the scale of the notation sprite to match the background
        notationSprite.setScale(scaleX, scaleY);

    }
};

// void draw_pieces(sf::RenderWindow &window, ChessBoard &chessBoard) {
//     // Iterate through the board and draw each piece
//     for (int row = 0; row < 8; ++row) {
//         for (int col = 0; col < 8; ++col) {
//             ChessPiece piece = board[row][col];
//             if (piece != ChessPiece::Count) {
//                 sf::Sprite pieceSprite = chessBoard.getPieceSprite(piece);
//                 pieceSprite.setPosition(100 * col, 100 * row);
//                 window.draw(pieceSprite);
//             }
//         }
//     }
// }

void draw_pieces(sf::RenderWindow &window, ChessBoard &chessBoard, int startX, int startY, int isDragging) {
    // Iterate through the board and draw each piece
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (!(isDragging && row == startX && col == startY)) {
                ChessPiece piece = board[row][col];
                if (piece != ChessPiece::Count) {
                    sf::Sprite pieceSprite = chessBoard.getPieceSprite(piece);
                    pieceSprite.setPosition(100 * col, 100 * row);
                    window.draw(pieceSprite);
                }
            }
        }
    }
}

bool isCellSelected(const std::vector<std::pair<int, int>> &selectedCells, int x, int y) {
    for (const auto &cell : selectedCells) {
        if (cell.first == x && cell.second == y) {
            return true;
        }
    }
    return false;
}

struct Move {
    int x, y;

    bool operator==(const Move &other) const {
        return x == other.x && y == other.y;
    }
};

struct LastMove {
    ChessPiece piece;
    int newX, newY;
    int oldX, oldY;
};

bool isAlly(ChessPiece piece, int w) {
    std::vector<ChessPiece> whitePieces = {
        ChessPiece::KingWhite, ChessPiece::QueenWhite, ChessPiece::RookWhite,
        ChessPiece::BishopWhite, ChessPiece::KnightWhite, ChessPiece::PawnWhite
    };

    std::vector<ChessPiece> blackPieces = {
        ChessPiece::KingBlack, ChessPiece::QueenBlack, ChessPiece::RookBlack,
        ChessPiece::BishopBlack, ChessPiece::KnightBlack, ChessPiece::PawnBlack
    };
    if (w == 1) {
        return std::find(whitePieces.begin(), whitePieces.end(), piece) != whitePieces.end();
    } else {
        return std::find(blackPieces.begin(), blackPieces.end(), piece) != blackPieces.end();
    }
}

bool isEnPassant(Move move, ChessPiece piece, LastMove last_move) {
    // Verifică dacă ultima mutare a fost făcută de un pion negru care a avansat două pătrate

    if (piece == ChessPiece::PawnWhite && move.x == 2) {
        if (last_move.piece == ChessPiece::PawnBlack && last_move.oldY == 1 && last_move.newY == 3) {
            if (last_move.oldX == move.y)
                return true;
        }
    }

    if (piece == ChessPiece::PawnBlack && move.x == 5) {
        if (last_move.piece == ChessPiece::PawnWhite && last_move.oldY == 6 && last_move.newY == 4) {
            if (last_move.oldX == move.y)
                return true;
        }
    }
    return false;
}

std::vector<Move> get_moves(ChessPiece piece, int x, int y, int movedKingW, int movedKingB, int rookbl, int rookbr, int rookwl, int rookwr, LastMove last_move, std::array<std::array<ChessPiece, 8>, 8> board) {
    std::vector<Move> moves;
    int i, j;
    switch (piece) {
    case ChessPiece::PawnWhite:
        if (x == 6 && board[x - 2][y] == ChessPiece::Count
            && board[x - 1][y] == ChessPiece::Count)
            if (x - 2 >= 0)
                moves.push_back({ x - 2, y });
        if (board[x - 1][y] == ChessPiece::Count)
            if (x - 1 >= 0)
                moves.push_back({ x - 1, y });
        if (board[x - 1][y - 1] != ChessPiece::Count && !isAlly(board[x - 1][y - 1], 1))
            if (x - 1 >= 0 && y - 1 >= 0)
                moves.push_back({ x - 1, y - 1 });
        if (board[x - 1][y + 1] != ChessPiece::Count && !isAlly(board[x - 1][y + 1], 1))
            if (x - 1 >= 0)
                moves.push_back({ x - 1, y + 1 });
        // ENPESANT
        if (x == 3 && last_move.piece == ChessPiece::PawnBlack
            && last_move.oldY == 1 && last_move.newY == 3
            && ((last_move.oldX == y - 1 && last_move.newX == y - 1)
                || (last_move.oldX == y + 1 && last_move.newX == y + 1))
            )
            if (x - 1 >= 0)
                moves.push_back({ x - 1, last_move.newX });


        break;

    case ChessPiece::PawnBlack:
        if (x == 1 && board[x + 2][y] == ChessPiece::Count
            && board[x + 1][y] == ChessPiece::Count)
            if (x + 2 <= 7)
                moves.push_back({ x + 2, y });
        if (board[x + 1][y] == ChessPiece::Count)

            if (x + 1 <= 7)
                moves.push_back({ x + 1, y });
        if (board[x + 1][y - 1] != ChessPiece::Count && !isAlly(board[x + 1][y - 1], 0))
            if (x + 1 <= 7)
                moves.push_back({ x + 1, y - 1 });
        if (board[x + 1][y + 1] != ChessPiece::Count && !isAlly(board[x + 1][y + 1], 0))
            if (x + 1 <= 7)
                moves.push_back({ x + 1, y + 1 });

        // std::cout << last_move.oldX << last_move.oldY << std::endl;
        if (x == 4 && last_move.piece == ChessPiece::PawnWhite
            && last_move.oldY == 6 && last_move.newY == 4
            && ((last_move.oldX == y - 1 && last_move.newX == y - 1)
                || (last_move.oldX == y + 1 && last_move.newX == y + 1))
            ) {
            if (x + 1 <= 7)
                moves.push_back({ x + 1, last_move.newX });
        }
        break;

    case ChessPiece::BishopBlack:
        i = x - 1;
        j = y + 1;
        while (i >= 0 && j >= 0 && j <= 7 && i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
            j++;
        }
        i = x - 1;
        j = y - 1;
        while (i >= 0 && j >= 0 && j <= 7 && i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
            j--;
        }

        i = x + 1;
        j = y + 1;
        while (i >= 0 && j >= 0 && j <= 7 && i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
            j++;
        }
        i = x + 1;
        j = y - 1;
        while (i >= 0 && j >= 0 && j <= 7 && i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
            j--;
        }
        break;
    case ChessPiece::BishopWhite:
        i = x - 1;
        j = y + 1;
        while (i >= 0 && j >= 0 && j <= 7 && i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
            j++;
        }
        i = x - 1;
        j = y - 1;
        while (i >= 0 && j >= 0 && j <= 7 && i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
            j--;
        }

        i = x + 1;
        j = y + 1;
        while (i >= 0 && j >= 0 && j <= 7 && i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
            j++;
        }
        i = x + 1;
        j = y - 1;
        while (i >= 0 && j >= 0 && j <= 7 && i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
            j--;
        }
        break;

    case ChessPiece::RookWhite:
        i = x - 1;
        j = y;
        while (i >= 0) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
        }
        i = x + 1;
        while (i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
        }
        i = x;
        j = y - 1;
        while (j >= 0) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            j--;
        }
        j = y + 1;
        while (j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            j++;
        }
        break;
    case ChessPiece::RookBlack:
        i = x - 1;
        j = y;
        while (i >= 0) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
        }
        i = x + 1;
        while (i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
        }
        i = x;
        j = y - 1;
        while (j >= 0) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            j--;
        }
        j = y + 1;
        while (j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            j++;
        }
        break;

    case ChessPiece::KnightWhite:
        if (board[x - 1][y - 2] == ChessPiece::Count || !isAlly(board[x - 1][y - 2], 1))
            if (x - 1 >= 0 && y - 2 >= 0)
                moves.push_back({ x - 1, y - 2 });
        if (board[x - 1][y + 2] == ChessPiece::Count || !isAlly(board[x - 1][y + 2], 1))
            if (x - 1 >= 0 && y + 2 <= 7)
                moves.push_back({ x - 1, y + 2 });
        if (board[x + 1][y - 2] == ChessPiece::Count || !isAlly(board[x + 1][y - 2], 1))
            if (x + 1 <= 7 && y - 2 >= 0)
                moves.push_back({ x + 1, y - 2 });
        if (board[x + 1][y + 2] == ChessPiece::Count || !isAlly(board[x + 1][y + 2], 1))
            if (x + 1 <= 7 && y + 2 <= 7)
                moves.push_back({ x + 1, y + 2 });

        if (board[x - 2][y - 1] == ChessPiece::Count || !isAlly(board[x - 2][y - 1], 1))
            if (x - 2 >= 0 && y - 1 >= 0)
                moves.push_back({ x - 2, y - 1 });
        if (board[x - 2][y + 1] == ChessPiece::Count || !isAlly(board[x - 2][y + 1], 1))
            if (x - 2 >= 0 && y + 1 <= 7)
                moves.push_back({ x - 2, y + 1 });
        if (board[x + 2][y - 1] == ChessPiece::Count || !isAlly(board[x + 2][y - 1], 1))
            if (x + 2 <= 7 && y - 1 >= 0)
                moves.push_back({ x + 2, y - 1 });
        if (board[x + 2][y + 1] == ChessPiece::Count || !isAlly(board[x + 2][y + 1], 1))
            if (x + 2 <= 7 && y + 1 <= 7)
                moves.push_back({ x + 2, y + 1 });
        break;

    case ChessPiece::KnightBlack:
        if (board[x - 1][y - 2] == ChessPiece::Count || !isAlly(board[x - 1][y - 2], 0))
            if (x - 1 >= 0 && y - 2 >= 0)
                moves.push_back({ x - 1, y - 2 });
        if (board[x - 1][y + 2] == ChessPiece::Count || !isAlly(board[x - 1][y + 2], 0))
            if (x - 1 >= 0 && y + 2 <= 7)
                moves.push_back({ x - 1, y + 2 });
        if (board[x + 1][y - 2] == ChessPiece::Count || !isAlly(board[x + 1][y - 2], 0))
            if (x + 1 <= 7 && y - 2 >= 0)
                moves.push_back({ x + 1, y - 2 });
        if (board[x + 1][y + 2] == ChessPiece::Count || !isAlly(board[x + 1][y + 2], 0))
            if (x + 1 <= 7 && y + 2 <= 7)
                moves.push_back({ x + 1, y + 2 });

        if (board[x - 2][y - 1] == ChessPiece::Count || !isAlly(board[x - 2][y - 1], 0))
            if (x - 2 >= 0 && y - 1 >= 0)
                moves.push_back({ x - 2, y - 1 });
        if (board[x - 2][y + 1] == ChessPiece::Count || !isAlly(board[x - 2][y + 1], 0))
            if (x - 2 >= 0 && y + 1 <= 7)
                moves.push_back({ x - 2, y + 1 });
        if (board[x + 2][y - 1] == ChessPiece::Count || !isAlly(board[x + 2][y - 1], 0))
            if (x + 2 <= 7 && y - 1 >= 0)
                moves.push_back({ x + 2, y - 1 });
        if (board[x + 2][y + 1] == ChessPiece::Count || !isAlly(board[x + 2][y + 1], 0))
            if (x + 2 <= 7 && y + 1 <= 7)
                moves.push_back({ x + 2, y + 1 });
        break;

    case ChessPiece::KingWhite:
        for (int i = y - 1; i <= y + 1; i++) {
            if (board[x - 1][i] == ChessPiece::Count || !isAlly(board[x - 1][i], 1))
                if (x - 1 >= 0 && i >= 0 && i <= 7)
                    moves.push_back({ x - 1, i });
            if (board[x + 1][i] == ChessPiece::Count || !isAlly(board[x + 1][i], 1))
                if (x + 1 <= 7 && i >= 0 && i <= 7)
                    moves.push_back({ x + 1, i });
        }
        if (board[x][y - 1] == ChessPiece::Count || !isAlly(board[x][y - 1], 1))
            if (y - 1 >= 0)
                moves.push_back({ x, y - 1 });
        if (board[x][y + 1] == ChessPiece::Count || !isAlly(board[x][y + 1], 1))
            if (y + 1 <= 7)
                moves.push_back({ x, y + 1 });

        if (movedKingW == 0 && board[x][y + 1] == ChessPiece::Count
            && board[x][y + 2] == ChessPiece::Count && rookwr == 0 && x == 7 && y == 4 && board[7][7] == ChessPiece::RookWhite)
            if (y + 2 <= 7)
                moves.push_back({ x, y + 2 });

        if (movedKingW == 0 && board[x][y - 1] == ChessPiece::Count
            && board[x][y - 2] == ChessPiece::Count
            && board[x][y - 3] == ChessPiece::Count && rookwl == 0 && x == 7 && y == 4 && board[7][0] == ChessPiece::RookWhite)
            if (y - 2 >= 0)
                moves.push_back({ x, y - 2 });
        break;

    case ChessPiece::KingBlack:
        for (int i = y - 1; i <= y + 1; i++) {
            if (board[x - 1][i] == ChessPiece::Count || !isAlly(board[x - 1][i], 0))
                if (x - 1 >= 0 && i >= 0 && i <= 7)
                    moves.push_back({ x - 1, i });
            if (board[x + 1][i] == ChessPiece::Count || !isAlly(board[x + 1][i], 0))
                if (x + 1 <= 7 && i >= 0 && i <= 7)
                    moves.push_back({ x + 1, i });
        }
        if (board[x][y - 1] == ChessPiece::Count || !isAlly(board[x][y - 1], 0))
            if (y - 1 >= 0)
                moves.push_back({ x, y - 1 });
        if (board[x][y + 1] == ChessPiece::Count || !isAlly(board[x][y + 1], 0))
            if (y + 1 <= 7)
                moves.push_back({ x, y + 1 });

        if (!movedKingB && board[x][y + 1] == ChessPiece::Count
            && board[x][y + 2] == ChessPiece::Count && rookbr == 0 && x == 0 && y == 4 && board[0][7] == ChessPiece::RookBlack)
            if (y + 2 <= 7)
                moves.push_back({ x, y + 2 });

        if (!movedKingB && board[x][y - 1] == ChessPiece::Count
            && board[x][y - 2] == ChessPiece::Count
            && board[x][y - 3] == ChessPiece::Count && rookbl == 0 && x == 0 && y == 4 && board[0][0] == ChessPiece::RookBlack)
            if (y - 2 >= 0)
                moves.push_back({ x, y - 2 });
        break;

    case ChessPiece::QueenWhite:
        i = x - 1;
        j = y;
        while (i >= 0) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
        }
        i = x + 1;
        j = y;
        while (i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
        }
        i = x;
        j = y - 1;
        while (j >= 0) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            j--;
        }
        i = x;
        j = y + 1;
        while (j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            j++;
        }
        i = x - 1;
        j = y + 1;
        while (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
            j++;
        }
        i = x - 1;
        j = y - 1;
        while (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
            j--;
        }
        i = x + 1;
        j = y + 1;
        while (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
            j++;
        }
        i = x + 1;
        j = y - 1;
        while (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 1)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
            j--;
        }
        break;

    case ChessPiece::QueenBlack:
        i = x - 1;
        j = y;
        while (i >= 0) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
        }
        i = x + 1;
        j = y;
        while (i <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
        }
        i = x;
        j = y - 1;
        while (j >= 0) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            j--;
        }
        i = x;
        j = y + 1;
        while (j <= 8) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            j++;
        }
        i = x - 1;
        j = y + 1;
        while (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
            j++;
        }
        i = x - 1;
        j = y - 1;
        while (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i--;
            j--;
        }

        i = x + 1;
        j = y + 1;
        while (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
            j++;
        }
        i = x + 1;
        j = y - 1;
        while (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
            if (board[i][j] == ChessPiece::Count)
                moves.push_back({ i, j });
            else if (board[i][j] != ChessPiece::Count && !isAlly(board[i][j], 0)) {
                moves.push_back({ i, j });
                break;
            } else
                break;
            i++;
            j--;
        }
        break;
    default:
        break;
    }

    return moves;
}

bool moves_contains(std::vector<Move> moves, int x, int y) {
    for (const auto move : moves) {
        if (move.x == x && move.y == y) {
            return true;
        }
    }
    return false;
}

void showValidMoves(const std::vector<Move> &selected_piece_moves, sf::RenderWindow &window, int cellSize) {
    for (const auto &move : selected_piece_moves) {
        sf::CircleShape circle(cellSize / 6);
        circle.setFillColor(sf::Color(0, 0, 0, 64));
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition((move.x + 0.5f) * cellSize, (move.y - 0.5f) * cellSize);
        window.draw(circle);
    }
}

bool do_Castle(Move move, ChessPiece piece, int oldX, int oldY, sf::Sound &sound_castle, std::array<std::array<ChessPiece, 8>, 8> &board) {

    if (piece == ChessPiece::KingWhite) {
        if (oldX == 7 && oldY == 4) {
            // King never moved si tura lfl
            if (move.y == 2) {
                board[move.x][move.y + 1] = ChessPiece::RookWhite;
                board[7][0] = ChessPiece::Count;
                sound_castle.play();
                return true;
            } else if (move.y == 6) {
                board[move.x][move.y - 1] = ChessPiece::RookWhite;
                board[7][7] = ChessPiece::Count;
                sound_castle.play();
                return true;
            }
        }
    } else if (piece == ChessPiece::KingBlack) {
        if (oldX == 0 && oldY == 4) {
            if (move.y == 2) {
                board[move.x][move.y + 1] = ChessPiece::RookBlack;
                board[0][0] = ChessPiece::Count;
                sound_castle.play();
                return true;
            } else if (move.y == 6) {
                board[move.x][move.y - 1] = ChessPiece::RookBlack;
                board[0][7] = ChessPiece::Count;
                sound_castle.play();
                return true;
            }
        }
    }
    return false;
}

void remove_move(std::vector<Move> &moves, Move move) {
    auto it = std::find(moves.begin(), moves.end(), move);

    if (it != moves.end()) {
        moves.erase(it);
    }
}

void filter_moves_castle(ChessPiece piece, std::vector<Move> &moves, int kingBmoved, int kingWmoved, int rookbl, int rookbr, int rookwl, int rookwr,
    int x, int y) {

    if (piece == ChessPiece::KingBlack) {
        if (!kingBmoved) {
            if (x == 0 && y == 4) {
                if (rookbl)
                    remove_move(moves, { 0, 2 });
                if (rookbr)
                    remove_move(moves, { 0, 6 });
            }
        } else {
            if (x == 0 && y == 4) {
                remove_move(moves, { 0, 2 });
                remove_move(moves, { 0, 6 });
            }
        }
    }
    if (piece == ChessPiece::KingWhite) {
        if (!kingWmoved) {
            if (x == 7 && y == 4) {
                if (rookwr)
                    remove_move(moves, { 7, 6 });
                if (rookwl)
                    remove_move(moves, { 7, 2 });
            }
        } else {
            if (x == 7 && y == 4) {
                remove_move(moves, { 7, 2 });
                remove_move(moves, { 7, 6 });
            }
        }
    }
}

bool need_transformation(ChessPiece piece, int x, int y) {
    if (piece == ChessPiece::PawnWhite && x == 0) {
        return true;
    } else if (piece == ChessPiece::PawnBlack && x == 7) {
        return true;
    }
    return false;
}

ChessPiece showTransformationOptions(int turn, int windowPosX, int windowPosY) {
    sf::RenderWindow window(sf::VideoMode(450, 80), "Choose Transformation");
    window.setPosition(sf::Vector2i(windowPosX, windowPosY));


    sf::Texture WqueenTexture, WrookTexture, WbishopTexture, WknightTexture;
    sf::Texture BqueenTexture, BrookTexture, BbishopTexture, BknightTexture;
    if (!WqueenTexture.loadFromFile("pieces/wq.png") ||
        !WrookTexture.loadFromFile("pieces/wr.png") ||
        !WbishopTexture.loadFromFile("pieces/wb.png") ||
        !WknightTexture.loadFromFile("pieces/wn.png")) {
        std::cerr << "Error loading images" << std::endl;
        exit(1);
    }
    if (!BqueenTexture.loadFromFile("pieces/bq.png") ||
        !BrookTexture.loadFromFile("pieces/br.png") ||
        !BbishopTexture.loadFromFile("pieces/bb.png") ||
        !BknightTexture.loadFromFile("pieces/bn.png")) {
        std::cerr << "Error loading images" << std::endl;
        exit(1);
    }

    sf::Sprite WqueenSprite(WqueenTexture);
    sf::Sprite WrookSprite(WrookTexture);
    sf::Sprite WbishopSprite(WbishopTexture);
    sf::Sprite WknightSprite(WknightTexture);

    WqueenSprite.setPosition(0, 0);
    WqueenSprite.setScale(0.5f, 0.5f);
    WrookSprite.setPosition(120, 0);
    WrookSprite.setScale(0.5f, 0.5f);
    WbishopSprite.setPosition(240, 0);
    WbishopSprite.setScale(0.5f, 0.5f);
    WknightSprite.setPosition(360, 0);
    WknightSprite.setScale(0.5f, 0.5f);

    sf::Sprite BqueenSprite(BqueenTexture);
    sf::Sprite BrookSprite(BrookTexture);
    sf::Sprite BbishopSprite(BbishopTexture);
    sf::Sprite BknightSprite(BknightTexture);

    BqueenSprite.setPosition(0, 0);
    BqueenSprite.setScale(0.5f, 0.5f);
    BrookSprite.setPosition(120, 0);
    BrookSprite.setScale(0.5f, 0.5f);
    BbishopSprite.setPosition(240, 0);
    BbishopSprite.setScale(0.5f, 0.5f);
    BknightSprite.setPosition(360, 0);
    BknightSprite.setScale(0.5f, 0.5f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (turn) {
                        if (WqueenSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            window.close();
                            return ChessPiece::QueenWhite;
                        } else if (WrookSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            window.close();
                            return ChessPiece::RookWhite;
                        } else if (WbishopSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            window.close();
                            return ChessPiece::BishopWhite;
                        } else if (WknightSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            window.close();
                            return ChessPiece::KnightWhite;
                        }
                    } else {
                        if (BqueenSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            window.close();
                            return ChessPiece::QueenBlack;
                        } else if (BrookSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            window.close();
                            return ChessPiece::RookBlack;
                        } else if (BbishopSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            window.close();
                            return ChessPiece::BishopBlack;
                        } else if (BknightSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            window.close();
                            return ChessPiece::KnightBlack;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        if (turn) {
            window.draw(WqueenSprite);
            window.draw(WrookSprite);
            window.draw(WbishopSprite);
            window.draw(WknightSprite);
        } else {
            window.draw(BqueenSprite);
            window.draw(BrookSprite);
            window.draw(BbishopSprite);
            window.draw(BknightSprite);
        }
        window.display();
    }

    return ChessPiece::Count;
}

void reverseBoard() {
    std::reverse(board.begin(), board.end());
    for (auto &row : board) {
        std::reverse(row.begin(), row.end());
    }
}

struct PieceMoves {
    ChessPiece piece;
    std::vector<Move> moves;
    Move start;
};

std::vector<PieceMoves> get_all_legal_moves(int kingBmoved, int kingWmoved, int rookbl, int rookbr, int rookwl, int rookwr, LastMove last_move,
    std::array<std::array<ChessPiece, 8>, 8>curr_board) {
    std::vector<PieceMoves> all_moves;
    for (int x = 0; x < (int) curr_board.size(); x++) {
        for (int y = 0; y < (int) curr_board[x].size(); y++) {
            ChessPiece piece = curr_board[x][y];
            if (piece != ChessPiece::Count) {
                std::vector<Move> moves = get_moves(piece, x, y, kingWmoved, kingBmoved, rookbl, rookbr, rookwl, rookwr, last_move, curr_board);
                if (!moves.empty()) {
                    all_moves.push_back({ piece, moves, { x, y } });
                }
            }
        }
    }

    //! get only the turn moves
    // for (auto it = all_moves.begin(); it != all_moves.end(); ) {
    //     if (isAlly(it->piece, turn)) {
    //         it++;
    //     } else {
    //         it = all_moves.erase(it);
    //     }
    // }

    return all_moves;
}

int isKingChecked(std::vector<PieceMoves> all_moves, std::array<std::array<ChessPiece, 8>, 8>curr_board) {
    for (auto &piece_move : all_moves) {
        if (piece_move.piece != ChessPiece::KingBlack) {
            for (auto &moves : piece_move.moves) {
                if (curr_board[moves.x][moves.y] == ChessPiece::KingBlack && !isAlly(piece_move.piece, 0)) {
                    return 2;
                }
            }
        }
        if (piece_move.piece != ChessPiece::KingWhite) {
            for (auto &moves : piece_move.moves) {
                if (curr_board[moves.x][moves.y] == ChessPiece::KingWhite && !isAlly(piece_move.piece, 1)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Funcție pentru a afișa tabla de șah
void printBoard(const std::array<std::array<ChessPiece, 8>, 8> &board) {
    for (const auto &row : board) {
        for (const auto &piece : row) {
            switch (piece) {
            case ChessPiece::Count: std::cout << "."; break;
            case ChessPiece::PawnWhite: std::cout << "P"; break;
            case ChessPiece::PawnBlack: std::cout << "p"; break;
            case ChessPiece::RookWhite: std::cout << "R"; break;
            case ChessPiece::RookBlack: std::cout << "r"; break;
            case ChessPiece::KnightWhite: std::cout << "N"; break;
            case ChessPiece::KnightBlack: std::cout << "n"; break;
            case ChessPiece::BishopWhite: std::cout << "B"; break;
            case ChessPiece::BishopBlack: std::cout << "b"; break;
            case ChessPiece::QueenWhite: std::cout << "Q"; break;
            case ChessPiece::QueenBlack: std::cout << "q"; break;
            case ChessPiece::KingWhite: std::cout << "K"; break;
            case ChessPiece::KingBlack: std::cout << "k"; break;
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void print_piece_moves(ChessPiece piece, std::vector<Move> moves) {
    std::cout << "Piece: " << piece << std::endl;
    for (auto &move : moves) {
        std::cout << "(" << move.x << ", " << move.y << ") ";
    }
    std::cout << std::endl;
}

void filter_king_moves(std::vector<Move> &moves, int white, int kingBmoved, int kingWmoved, int rookbl, int rookbr, int rookwl, int rookwr, LastMove last_move, int startX, int startY, std::array<std::array<ChessPiece, 8>, 8> &board) {
    std::array<std::array<ChessPiece, 8>, 8> aux_board = board;
    std::vector<PieceMoves> new_all_moves;
    PieceMoves piece_move;
    std::vector<Move> invalid_moves;
    for (auto &move : moves) {
        aux_board = board; // Copiem tabla curentă în tabla auxiliară
        if (white) {
            piece_move.piece = ChessPiece::KingWhite;
            aux_board[startX][startY] = ChessPiece::Count;
            aux_board[move.x][move.y] = ChessPiece::KingWhite;
        } else {
            piece_move.piece = ChessPiece::KingBlack;
            aux_board[startX][startY] = ChessPiece::Count;
            aux_board[move.x][move.y] = ChessPiece::KingBlack;
        }

        // std::cout << piece_move.piece << " " << "move.x = " << move.x << " move.y = " << move.y << std::endl;

        new_all_moves = get_all_legal_moves(kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, aux_board);
        for (auto it = new_all_moves.begin(); it != new_all_moves.end(); ) {
            if (it->moves.empty()) {
                it = new_all_moves.erase(it); // Șterge piesa și actualizează iteratorul
            } else {
                ++it; // Treci la următorul element
            }
        }

        // for (auto move : new_all_moves) {
            // print_piece_moves(move.piece, move.moves);
        // }

        if (isKingChecked(new_all_moves, aux_board)) {

            // std::cout << piece_move.piece << " " << "move.x = " << move.x << " move.y = " << move.y << std::endl;
            invalid_moves.push_back(move);
            // remove_move(moves, move);
        }
    }
    // std::cout << std::endl;
    for (auto &move : invalid_moves) {
        remove_move(moves, move);
    }
}

bool isCheckMate(std::array<std::array<ChessPiece, 8>, 8> &board, std::vector<PieceMoves> all_moves, int white, int kingBmoved, int kingWmoved, int rookbl, int rookbr, int rookwl, int rookwr, LastMove last_move) {
    std::array<std::array<ChessPiece, 8>, 8> aux_board = board;
    std::vector<PieceMoves> new_all_moves;

    // trecem prin tabla cu 2 for uri
    // pentru fiecare piesa facem mutarea
    int kingChecked = isKingChecked(all_moves, board);

    if (kingChecked == 0) {
        return false;
    }

    for (auto &piece_move : all_moves) {
        // std::cout << "Piesa: " << piece_move.piece << std::endl;
        // std::cout << "Mișcările: ";
        if ((white && piece_move.piece >= ChessPiece::KingWhite && piece_move.piece <= ChessPiece::PawnWhite) ||
            (!white && piece_move.piece >= ChessPiece::KingBlack && piece_move.piece <= ChessPiece::PawnBlack)) {
            for (auto &move : piece_move.moves) {
                // std::cout << "(" << move.x << ", " << move.y << ") ";
                aux_board = board;
                aux_board[move.x][move.y] = piece_move.piece;
                //! patratu de pe care a fost mutat trebuie sa fie gol
                //! De verificat daca x si y sunt chiar x si y (sunt corecte)
                aux_board[piece_move.start.x][piece_move.start.y] = ChessPiece::Count;
                // std::cout << piece_move.piece << " " << "Start.x = " << piece_move.start.x << " " << "Start.y = " << piece_move.start.y << std::endl;


                new_all_moves = get_all_legal_moves(kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, aux_board);
                for (auto &new_move : new_all_moves) {
                    if (new_move.piece == ChessPiece::KingBlack || new_move.piece == ChessPiece::KingWhite) {
                        filter_king_moves(new_move.moves, white, kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, move.y, move.x, aux_board);
                    }
                }

                for (auto move : new_all_moves)
                    print_piece_moves(move.piece, move.moves);


                if (isKingChecked(new_all_moves, aux_board) == 0) {
                    // std::cout << "Piece: " << piece_move.piece << " " << "Move: " << move.x << " " << move.y << std::endl;
                    // printBoard(aux_board);
                    return 0;
                }
            }
            // std::cout << std::endl;
        }
    }
    return 1;
}

bool show_checkmate_dialog(int windowPosX, int windowPosY, int stalemate) {
    sf::RenderWindow window(sf::VideoMode(400, 200), "Checkmate");
    window.setPosition(sf::Vector2i(windowPosX * 1.5, windowPosY * 1.5));

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font" << std::endl;
        return false;
    }

    sf::Text text;
    if (stalemate == 1)
        text.setString("Stalemate! Start a new game? (Y/N)");
    else if (stalemate == 2)
        text.setString("Draw! Start a new game? (Y/N)");
    else
        text.setString("Checkmate! Start a new game? (Y/N)");

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(50, 80);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                exit(0);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Y) {
                    std::cout << "Starting a new game..." << std::endl;
                    window.close();
                    return true; // Începe un nou joc
                } else if (event.key.code == sf::Keyboard::N) {
                    std::cout << "Exiting the game..." << std::endl;
                    window.close();
                    return false; // Închide programul
                }
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return false;
}

int main() {

restart:
    // Create a window with a size of 800x800 pixels
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Calculăm poziția ferestrei pentru a fi centrată
    int windowPosX = (desktop.width - 800) / 2;
    int windowPosY = (desktop.height - 800) / 2;
    window.setPosition(sf::Vector2i(windowPosX, windowPosY));

    int size = 800;
    int cellSize = size / 8;

    board = clean_board;
    int turn = 1;

    // SoundBuffer
    sf::SoundBuffer buffer, buffer_illegal, buffer_move, buffer_capture, buffer_castle;
    sf::Sound sound, sound_illegal, sound_move, sound_capture, sound_castle;

    // Load audio
    if (!buffer.loadFromFile("game-start.wav")) {
        return -1;
    }
    sound.setBuffer(buffer);
    sound.play();

    if (!buffer_illegal.loadFromFile("illegal.wav")) {
        return -1;
    }
    sound_illegal.setBuffer(buffer_illegal);

    if (!buffer_move.loadFromFile("move-self.wav")) {
        return -1;
    }
    sound_move.setBuffer(buffer_move);

    if (!buffer_capture.loadFromFile("capture.wav")) {
        return -1;
    }
    sound_capture.setBuffer(buffer_capture);

    if (!buffer_castle.loadFromFile("castle.wav")) {
        return -1;
    }
    sound_castle.setBuffer(buffer_castle);

    // Start positions
    int startY, startX;
    int selected = -1;
    std::vector<std::pair<int, int>> selectedCells;

    bool isDragging = false;
    sf::Sprite draggedPiece;

    // Create chess board and pieces
    ChessBoard chessBoard;

    int newY = -1;
    int newX = -1;
    int aux_startY = -1, aux_startX = -1;
    int aux_newY = -1, aux_newX = -1;

    int rookwl = 0, rookwr = 0;
    int rookbl = 0, rookbr = 0;
    int kingWmoved = 0, kingBmoved = 0;

    int kingChecked = 0;
    int check_move = 0;
    std::array<std::array<ChessPiece, 8>, 8> aux_board;

    LastMove last_move;
    last_move.oldX = -1;
    last_move.oldY = -1;

    ChessPiece selected_piece = ChessPiece::Count;
    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int x = pos.x / cellSize;
        int y = pos.y / cellSize;
        int made_move = 0;
        std::vector<Move> selected_piece_moves;
        std::vector<PieceMoves> all_moves;
        all_moves.clear();

        // std::cout << kingChecked << std::endl;
        // turn = 1;

        selected_piece_moves = get_moves(selected_piece, startX, startY, kingWmoved, kingBmoved, rookbl, rookbr, rookwl, rookwr, last_move, board);
        if (selected_piece == ChessPiece::KingBlack || selected_piece == ChessPiece::KingWhite) {
            filter_king_moves(selected_piece_moves, turn, kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, startX, startY, board);
            // print_piece_moves(selected_piece, selected_piece_moves);
        }

        all_moves = get_all_legal_moves(kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, board);
        // std::cout << "INAITNE FILTRARE" << std::endl;
        // for (auto &piece : all_moves) {
        //     std::cout << piece.piece << " ";
        //     for (auto &move : piece.moves) {
        //         std::cout << "(" << move.x << ", " << move.y << ") ";
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl;

        for (auto &piece : all_moves) {
            if (piece.piece == ChessPiece::KingBlack || piece.piece == ChessPiece::KingWhite)
                filter_king_moves(piece.moves, turn, kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, startX, startY, board);
        }

        bool check_mate = isCheckMate(board, all_moves, turn, kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move);
        // get turn moves
        for (auto it = all_moves.begin(); it != all_moves.end(); ) {
            if (isAlly(it->piece, turn)) {
                it++;
            } else {
                it = all_moves.erase(it);
            }
        }
        for (auto it = all_moves.begin(); it != all_moves.end(); ) {
            if (it->moves.empty()) {
                it = all_moves.erase(it); // Șterge piesa și actualizează iteratorul
            } else {
                ++it; // Treci la următorul element
            }
        }
        // // print all_moves
        // std::cout << "DUPA FILTRARE" << std::endl;
        // for (auto &piece : all_moves) {
        //     std::cout << piece.piece << " ";
        //     for (auto &move : piece.moves) {
        //         std::cout << "(" << move.x << ", " << move.y << ") ";
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl;
        // break;

        //! Temp fix for stalemate, ma asigur ca exista un rege
        bool King_exists = false;
        bool only_kings = true;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                // if ((board[i][j] == ChessPiece::KingBlack && turn == 0) || (board[i][j] == ChessPiece::KingWhite && turn == 1)) {
                //     King_exists = true;
                //     break;
                // }
                if (board[i][j] != ChessPiece::KingBlack && board[i][j] != ChessPiece::KingWhite && board[i][j] != ChessPiece::Count) {
                    only_kings = false;
                }
            }
        }

        if (check_mate) {
            if (show_checkmate_dialog(windowPosX, windowPosY, 0))
                goto restart;
            break;
            // std::cout << "CHECKMATE" << '\n';
        }
        // Daca culoarea "turn" nu mai are miscari
        else if (all_moves.empty()) {
            std::cout << "Stalemate" << '\n';
            // if (show_checkmate_dialog(windowPosX, windowPosY, 1))
                // goto restart;
            // break;
        } else if (only_kings) {
            if (show_checkmate_dialog(windowPosX, windowPosY, 2))
                goto restart;
            break;
        }

        // print all_moves
        // std::cout << "DUPA FILTRARE" << std::endl;
        // if (all_moves.empty())
        //     std::cout << "All moves is empty" << std::endl;
        // for (auto &piece : all_moves) {
        //     std::cout << piece.piece << " ";
        //     for (auto &move : piece.moves) {
        //         std::cout << "(" << move.x << ", " << move.y << ") ";
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl;
        // break;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                ChessPiece piece = board[y][x];
                if (event.mouseButton.button == sf::Mouse::Left) {
                    selectedCells.clear();
                    if (piece != ChessPiece::Count && isAlly(piece, turn)) {
                        isDragging = true;

                        draggedPiece = chessBoard.getPieceSprite(piece);
                        draggedPiece.setOrigin(draggedPiece.getLocalBounds().width / 2, draggedPiece.getLocalBounds().height / 2);
                        draggedPiece.setPosition(pos.x, pos.y);

                        selected_piece = piece;

                        // board[y][x] = ChessPiece::Count;
                        selected = 1;

                        startY = x;
                        startX = y;

                    }
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    int x = event.mouseButton.x / cellSize;
                    int y = event.mouseButton.y / cellSize;
                    if (!isCellSelected(selectedCells, x, y)) {
                        selectedCells.push_back(std::make_pair(x, y));
                    } else {
                        auto it = std::find_if(selectedCells.begin(), selectedCells.end(), [x, y](const std::pair<int, int> &cell) {
                            return cell.first == x && cell.second == y;
                            });
                        if (it != selectedCells.end()) {
                            selectedCells.erase(it);
                        }
                    }
                    selected = -1;
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if (isDragging) {
                        isDragging = false;
                        newY = pos.x / cellSize;
                        newX = pos.y / cellSize;

                        if (moves_contains(selected_piece_moves, newX, newY)) {
                            // kingChecked = isKingChecked(all_moves, board);
                            bool check_tranformation = need_transformation(selected_piece, newX, newY);
                            aux_board = board;

                            if (check_tranformation) {
                                int transformWindowPosX = windowPosX + newY * cellSize;
                                int transformWindowPosY = windowPosY + newX * cellSize;
                                ChessPiece newPiece = showTransformationOptions(turn, transformWindowPosX, transformWindowPosY);
                                if (newPiece == ChessPiece::Count) {
                                    board[startX][startY] = selected_piece;
                                    continue;
                                }
                                board[startX][startY] = ChessPiece::Count;
                                board[newX][newY] = newPiece;
                            }

                            if (board[newX][newY] != ChessPiece::Count) {
                                sound_capture.play();
                            }
                            if (!check_tranformation) {
                                board[startX][startY] = ChessPiece::Count;
                                board[newX][newY] = selected_piece;
                            }

                            // printBoard(board);
                            // std::cout << std::endl;

                            selected = -1;
                            selected_piece_moves.clear();
                            made_move = 1;
                            bool docastle = false;
                            Move move;
                            move.y = newY;
                            move.x = newX;


                            if (selected_piece == ChessPiece::KingWhite) {
                                if (!kingWmoved) {
                                    if (newY == 2 && !rookwl && board[7][0] == ChessPiece::RookWhite)
                                        docastle = do_Castle(move, selected_piece, startX, startY, sound_castle, board);
                                    else if (newY == 6 && !rookwr && board[7][7] == ChessPiece::RookWhite)
                                        docastle = do_Castle(move, selected_piece, startX, startY, sound_castle, board);
                                }
                            } else if (selected_piece == ChessPiece::KingBlack) {
                                if (!kingBmoved) {
                                    if (newY == 2 && !rookbl && board[0][0] == ChessPiece::RookBlack)
                                        docastle = do_Castle(move, selected_piece, startX, startY, sound_castle, board);
                                    else if (newY == 6 && !rookbr && board[0][7] == ChessPiece::RookBlack)
                                        docastle = do_Castle(move, selected_piece, startX, startY, sound_castle, board);
                                }
                            }

                            printBoard(board);


                            switch (selected_piece) {
                            case ChessPiece::RookWhite:
                                if (startY == 0) {
                                    rookwl = 1;
                                } else if (startY == 7) {
                                    rookwr = 1;
                                }
                                break;
                            case ChessPiece::RookBlack:
                                if (startY == 0) {
                                    rookbl = 1;
                                } else if (startY == 7) {
                                    rookbr = 1;
                                }
                                break;
                            case ChessPiece::KingBlack:
                                kingBmoved = 1;
                                break;
                            case ChessPiece::KingWhite:
                                kingWmoved = 1;
                                break;
                            default:
                                break;
                            }
                            if (isEnPassant(move, selected_piece, last_move)) {
                                sound_capture.play();
                                board[last_move.newX][last_move.newY] = ChessPiece::Count;
                            } else if (!docastle && kingChecked == 0)
                                sound_move.play();

                            all_moves = get_all_legal_moves(kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, board);
                            if (selected_piece == ChessPiece::KingBlack || selected_piece == ChessPiece::KingWhite) {
                                for (auto &piece : all_moves) {
                                    if (piece.piece == selected_piece)
                                        filter_king_moves(piece.moves, turn, kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, startX, startY, board);
                                }
                            }
                            kingChecked = isKingChecked(all_moves, board);

                            if (kingChecked == 2 && turn == 0) {
                                // printBoard(board);

                                int kingChecked2 = 0;
                                check_move = 1;
                                std::vector<PieceMoves> all_moves2 = get_all_legal_moves(kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, board);
                                if (selected_piece == ChessPiece::KingBlack || selected_piece == ChessPiece::KingWhite) {
                                    for (auto &piece : all_moves2) {
                                        if (piece.piece == selected_piece)
                                            filter_king_moves(piece.moves, turn, kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, startX, startY, board);
                                    }
                                }
                                kingChecked2 = isKingChecked(all_moves2, board);

                                if (kingChecked2) {
                                    board[newX][newY] = aux_board[newX][newY];
                                    board[startX][startY] = selected_piece;
                                    sound_illegal.play();
                                    selected = -1;
                                    continue;
                                }
                            } else if (kingChecked == 1 && turn == 1) {
                                // printBoard(board);

                                int kingChecked2 = 0;
                                check_move = 1;
                                std::vector<PieceMoves> all_moves2 = get_all_legal_moves(kingBmoved, kingWmoved, rookbl, rookbr, rookwl, rookwr, last_move, board);
                                kingChecked2 = isKingChecked(all_moves2, board);

                                if (kingChecked2) {
                                    board[newX][newY] = aux_board[newX][newY];
                                    board[startX][startY] = selected_piece;
                                    sound_illegal.play();
                                    selected = -1;
                                    continue;
                                }
                            } else {
                                check_move = 0;
                                sound_move.play();
                                // turn = abs(turn - 1);
                            }
                            turn = abs(turn - 1);

                        } else {
                            if ((newY != startY || newX != startX) && !moves_contains(selected_piece_moves, newX, newY))
                                sound_illegal.play();
                            board[startX][startY] = selected_piece;
                        }

                        if (newY != startY && newX != startX)
                            selected = -1;
                    }
                }
            } else if (event.type == sf::Event::MouseMoved) {
                if (isDragging) {
                    draggedPiece.setPosition(pos.x, pos.y);
                }
            }
        }


        // Clear the window
        window.clear();

        // Draw the background sprite
        window.draw(chessBoard.getBackgroundSprite());
        window.draw(chessBoard.getNotationSprite());

        // Desenează celula selectată în roșu
        for (const auto &cell : selectedCells) {
            sf::RectangleShape cellHighlightred(sf::Vector2f(cellSize, cellSize));
            cellHighlightred.setFillColor(sf::Color(255, 0, 0, 128)); // Roșu semi-transparent
            cellHighlightred.setPosition(cell.first * cellSize, cell.second * cellSize);
            window.draw(cellHighlightred);
        }

        // Highlight last move
        if (newY != -1 && newX != -1) {
            if (made_move && check_move == 0) {
                last_move.piece = selected_piece;
                last_move.oldX = startY;
                last_move.oldY = startX;
                last_move.newY = newY;
                last_move.newX = newX;
                aux_startY = startY;
                aux_startX = startX;
                aux_newY = newY;
                aux_newX = newX;
            }

            sf::RectangleShape cellhighlight(sf::Vector2f(cellSize, cellSize));
            cellhighlight.setFillColor(sf::Color(173, 126, 51, 200));
            cellhighlight.setPosition(aux_startY * cellSize, aux_startX * cellSize);
            window.draw(cellhighlight);

            cellhighlight.setPosition(aux_newY * cellSize, aux_newX * cellSize);
            window.draw(cellhighlight);

        }

        if (selected != -1) {

            sf::RectangleShape columnHighlight(sf::Vector2f(cellSize, cellSize));
            columnHighlight.setFillColor(sf::Color(173, 126, 51, 200));
            columnHighlight.setPosition(startY * cellSize, startX * cellSize);
            window.draw(columnHighlight);

            for (const auto &move : selected_piece_moves) {
                if (board[move.x][move.y] == ChessPiece::Count) {
                    sf::CircleShape circle(cellSize / 6);
                    circle.setFillColor(sf::Color(0, 0, 0, 64));
                    circle.setOrigin(circle.getRadius(), circle.getRadius());
                    circle.setPosition((move.y + 0.5f) * cellSize, (move.x + 0.5f) * cellSize);
                    window.draw(circle);
                } else {
                    sf::CircleShape circle(cellSize / 2.5);
                    circle.setFillColor(sf::Color::Transparent);
                    circle.setOutlineColor(sf::Color(0, 0, 0, 64));
                    circle.setOutlineThickness(9);
                    circle.setOrigin(circle.getRadius(), circle.getRadius());
                    circle.setPosition((move.y + 0.5f) * cellSize, (move.x + 0.5f) * cellSize);
                    window.draw(circle);
                }
            }
        }

        // Draw the pieces
        draw_pieces(window, chessBoard, startX, startY, isDragging);

        if (isDragging) {
            window.draw(draggedPiece);
        }

        // window.clear();

        // Display the contents of the window
        window.display();
    }

    return 0;
}
