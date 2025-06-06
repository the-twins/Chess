#include <iostream>
#include <string>
#include <cstdlib>
#include <typeinfo>

using namespace std;


const short BLACK = 1;
const short WHITE = 0;
const short BOARD_SIZE = 8;
string COLOR[2] = {"white", "black"};
const short COMMAND_EXIT = 0;
const short COMMAND_MOVE = 1;
const short COMMAND_SHORT_CASTLE = 2;
const short COMMAND_LONG_CASTLE = 3;
const short MOVE_SUCCESS = 0;
const short MOVE_FAIL = 1;
const short MOVE_CANCEL = 2;

class Square
{
    unsigned short row;
    char col;
 
    public:
        Square(char c = 'a', unsigned short r = 1)
        {
            c = tolower(c);
            if(r > 8 || r < 1)
                throw "Invalid row.";           
            if(c < 'a' || c > 'h')
                throw "Invalid column.";
            row = r;
            col = c;
        }
        
        void print()
        {
            cout << col << row;
        }
        
        unsigned short get_x()
        {
            return col - 97;
        }
        
        unsigned short get_y()
        {
            return row - 1;
        }

        char get_col()
        {
            return col;
        }

        unsigned short get_row()
        {
            return row;
        }            
};

class Piece 
{   
    public:
        short color;
        
        Piece(short col)
        {
            color = col;
        }
        
        virtual void get_name() = 0;
        virtual void draw() = 0;
        virtual unsigned short get_trajectory(Square s1, Square s2, Square * trajectory) = 0;
};

class Pawn : public Piece
{
    public:
        Pawn(short col) : Piece(col) {}
            
        void get_name()
        {
            cout << COLOR[color] << " Pawn";
        }
        
        void draw()
        {
            if(color == WHITE)
                cout << "♙";
            else
                cout << "♟";
        }
        
        unsigned short get_trajectory(Square s1, Square s2, Square * trajectory)
        {
            unsigned short row1 = s1.get_row();
            unsigned short row2 = s2.get_row();
            char col1 = s1.get_col();
            char col2 = s2.get_col();
            short traj_row = row1 - row2;
            short traj_col = col1 - col2;
            if(row1 == row2 && col1 == col2)
            {
                trajectory[0] = s1;
                return 1;
            }
            if(color == BLACK && row1 == 7 && abs(traj_row) == 2)
            {
                trajectory[0] = s1;
                trajectory[1] = Square(col1, row2 + 1);
                trajectory[2] = s2;
                return 3;
            }
            if(color == WHITE && row1 == 2 && abs(traj_row) == 2)
            {
                trajectory[0] = s1;
                trajectory[1] = Square(col1, row2 - 1);
                trajectory[2] = s2;
                return 3;
            }
            if(color == WHITE && traj_row == -1 && abs(traj_col) < 2)
            {
                trajectory[0] = s1;
                trajectory[1] = s2;
                return 2;
            }
            if(color == BLACK && traj_row == 1 && abs(traj_col) < 2)
            {
                trajectory[0] = s1;
                trajectory[1] = s2;
                return 2;
            }                
            return 0;                
        }
};

class Rook : public Piece
{
    public:
        Rook(short col) : Piece(col) {}
            
        void get_name()
        {
            cout << COLOR[color] << " Rook";   
        }
        
        void draw()
        {
            if(color == WHITE)
                cout << "♖";
            else
                cout << "♜";
        }
        
        unsigned short get_trajectory(Square s1, Square s2, Square * trajectory)
        {
            unsigned short row1 = s1.get_row();
            unsigned short row2 = s2.get_row();
            char col1 = s1.get_col();
            char col2 = s2.get_col();
            unsigned short traj_row = abs(row1 - row2);
            unsigned short traj_col = abs(col1 - col2);
            if(row1 == row2 && col1 == col2)
            {
                trajectory[0] = s1;
                return 1;
            }
            if(col1 == col2)
            {
                if(row1 < row2)
                {
                    for(unsigned short i = 0; i < traj_row + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        row1++;
                    }
                }
                else
                {
                    for(unsigned short i = 0; i < traj_row + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        row1--;
                    }
                }
                return traj_row + 1;
            }
            if(row1 == row2)
            {
                if(col1 < col2)
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        col1++;
                    }
                }
                else
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        col1--;
                    }
                }
                return traj_col + 1;
            }
            return 0;
        }
};

class Bishop : public Piece
{
    public:
        Bishop(short col) : Piece(col) {}
            
        void get_name()
        {
            cout << COLOR[color] << " Bishop";   
        }
        
        void draw()
        {
            if(color == WHITE)
                cout << "♗";
            else
                cout << "♝";
        }
        
        unsigned short get_trajectory(Square s1, Square s2, Square * trajectory)
        {
            unsigned short row1 = s1.get_row();
            unsigned short row2 = s2.get_row();
            char col1 = s1.get_col();
            char col2 = s2.get_col();
            unsigned short traj_row = abs(row1 - row2);
            unsigned short traj_col = abs(col1 - col2);
            if(row1 == row2 && col1 == col2)
            {
                trajectory[0] = s1;
                return 1;
            }
            if(traj_col == traj_row)
            {
                if(col1 < col2 && row1 < row2)
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        row1++;
                        col1++;
                    }
                    return traj_col + 1;
                }
                if(col1 > col2 && row1 > row2)
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        col1--;
                        row1--;
                    }
                    return traj_col + 1;
                }
                if(col1 < col2 && row1 > row2)
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        col1++;
                        row1--;
                    }
                    return traj_col + 1;
                }
                if(col1 > col2 && row1 < row2)
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        col1--;
                        row1++;
                    }
                    return traj_col + 1;
                }
            }
            return 0;
        }
};

class Knight : public Piece
{
    public:
        Knight(short col) : Piece(col) {}
            
        void get_name()
        {
            cout << COLOR[color] << " Knight";   
        }
        
        void draw()
        {
            if(color == WHITE)
                cout << "♘";
            else
                cout << "♞";
        }
        
        unsigned short get_trajectory(Square s1, Square s2, Square * trajectory)
        {
            unsigned short row1 = s1.get_row();
            unsigned short row2 = s2.get_row();
            char col1 = s1.get_col();
            char col2 = s2.get_col();
            unsigned short traj_row = abs(row1 - row2);
            unsigned short traj_col = abs(col1 - col2);
            
            if(row1 == row2 && col1 == col2)
            {
                trajectory[0] = s1;
                return 1;
            }
            if(traj_row == 1 && traj_col == 2 || traj_row == 2 && traj_col == 1)
            {
                trajectory[0] = s1;
                trajectory[1] = s2;
                return 2;
            }
            return 0;
        }
};

class Queen : public Piece
{
    public:
        Queen(short col) : Piece(col) {}
            
        void get_name()
        {
            cout << COLOR[color] << " Queen";   
        }
        
        void draw()
        {
            if(color == WHITE)
                cout << "♕";
            else
                cout << "♛";
        }
        
        unsigned short get_trajectory(Square s1, Square s2, Square * trajectory)
        {
            unsigned short row1 = s1.get_row();
            unsigned short row2 = s2.get_row();
            char col1 = s1.get_col();
            char col2 = s2.get_col();
            unsigned short traj_row = abs(row1 - row2);
            unsigned short traj_col = abs(col1 - col2);
            if(row1 == row2 && col1 == col2)
            {
                trajectory[0] = s1;
                return 1;
            }
            if(traj_col == traj_row)
            {
                if(col1 < col2 && row1 < row2)
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        row1++;
                        col1++;
                    }
                    return traj_col + 1;
                }
                if(col1 > col2 && row1 > row2)
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        col1--;
                        row1--;
                    }
                    return traj_col + 1;
                }
                if(col1 < col2 && row1 > row2)
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        col1++;
                        row1--;
                    }
                    return traj_col + 1;
                }
                if(col1 > col2 && row1 < row2)
                {
                    for(unsigned short i = 0; i < traj_col + 1; i++)
                    {
                        trajectory[i] = Square(col1, row1);
                        col1--;
                        row1++;
                    }
                    return traj_col + 1;
                }
            }
            else
            {
                if(col1 == col2)
                {
                    if(row1 < row2)
                    {
                        for(unsigned short i = 0; i < traj_row + 1; i++)
                        {
                            trajectory[i] = Square(col1, row1);
                            row1++;
                        }
                    }
                    else
                    {
                        for(unsigned short i = 0; i < traj_row + 1; i++)
                        {
                            trajectory[i] = Square(col1, row1);
                            row1--;
                        }
                    }
                    return traj_row + 1;
                }
                if(row1 == row2)
                {
                    if(col1 < col2)
                    {
                        for(unsigned short i = 0; i < traj_col + 1; i++)
                        {
                            trajectory[i] = Square(col1, row1);
                            col1++;
                        }
                    }
                    else
                    {
                        for(unsigned short i = 0; i < traj_col + 1; i++)
                        {
                            trajectory[i] = Square(col1, row1);
                            col1--;
                        }
                    }
                    return traj_col + 1;
                }
            }
                return 0;
        }
};

class King : public Piece
{
    public:
        King(short col) : Piece(col) {}
            
        void get_name()
        {
            cout << COLOR[color] << " King";   
        }
        
        void draw()
        {
            if(color == WHITE)
                cout << "♔";
            else
                cout << "♚";
        }
        
        unsigned short get_trajectory(Square s1, Square s2, Square * trajectory)
        {
            unsigned short row1 = s1.get_row();
            unsigned short row2 = s2.get_row();
            char col1 = s1.get_col();
            char col2 = s2.get_col();
            if(abs(row1 - row2) > 1 || abs(col1 - col2) > 1)
                return 0;
            if(row1 == row2 && col1 == col2)
            {
                trajectory[0] = s1;
                return 1;
            }
            else
            {
                trajectory[0] = s1;
                trajectory[1] = s2;
                return 2;
            }
        }
};

void print_trajectoty(Square t[], unsigned short n)
{
    for(unsigned short i = 0; i < n; i++)
    {
        t[i].print();
        cout << endl;
    }
}

class Chessboard
{
    Piece * board[BOARD_SIZE][BOARD_SIZE];
    unsigned short turn;
    bool white_short_castle;
    bool black_long_castle;
    bool black_short_castle;
    bool white_long_castle;
    short en_passant;
    
    public:
        Chessboard()
        {
            board[0][0] = new Rook(WHITE);
            board[0][1] = new Knight(WHITE);
            board[0][2] = new Bishop(WHITE);
            board[0][3] = new Queen(WHITE);
            board[0][4] = new King(WHITE);
            board[0][5] = new Bishop(WHITE);
            board[0][6] = new Knight(WHITE);
            board[0][7] = new Rook(WHITE);

            board[7][0] = new Rook(BLACK);
            board[7][1] = new Knight(BLACK);
            board[7][2] = new Bishop(BLACK);
            board[7][3] = new Queen(BLACK);
            board[7][4] = new King(BLACK);
            board[7][5] = new Bishop(BLACK);
            board[7][6] = new Knight(BLACK);
            board[7][7] = new Rook(BLACK);
                        
            for(short i = 0; i < BOARD_SIZE; i++)
            {
                board[1][i] = new Pawn(WHITE);
                board[6][i] = new Pawn(BLACK);
            }

            for(short i = 2; i < 6; i++)
                for(short j = 0; j < BOARD_SIZE; j++)
                    board[i][j] = NULL;
            
            turn = WHITE;
            white_short_castle = true;
            black_long_castle = true;
            black_short_castle = true;
            white_long_castle = true;
            en_passant = -1;
        }
        
        unsigned short get_turn()
        {
            return turn;
        }
        
        void draw()
        {
            cout << "\033[30m" << "\033[47m";
            cout << " abcdefgh " << endl;
            for(short i = BOARD_SIZE - 1; i >= 0; i--)
            {
                cout << i + 1;
                for(short j = 0; j < BOARD_SIZE; j++)
                    if(board[i][j] != NULL)
                        board[i][j]->draw();
                    else
                        cout << ".";
                cout << ' '<< endl;
            }
            cout << " abcdefgh " << endl;
            cout << "\033[0m" << "\033[0m";
        }
        
        short castle(short side)
        {
            if(turn == WHITE && side == COMMAND_LONG_CASTLE)
            {
                if(!white_long_castle)
                    return MOVE_FAIL;
                for(short i = 1; i < 4; i++)
                {
                    if(board[0][i] != NULL)
                        return MOVE_FAIL;
                }
                for(short i = 2; i < 5; i++)
                {
                    Square s(i + 97, 1);
                    if(is_under_attack(s, BLACK))
                        return MOVE_FAIL;
                }
                board[0][2] = board[0][4];
                board[0][4] = NULL; 
                board[0][3] = board[0][0];
                board[0][0] = NULL;
                white_short_castle = false;
                white_long_castle = false;
            }
            if(turn == WHITE && side == COMMAND_SHORT_CASTLE)
            {
                if(!white_short_castle)
                    return MOVE_FAIL;
                for(short i = 5; i < 7; i++)
                {
                    if(board[0][i] != NULL)
                        return MOVE_FAIL;
                }
                for(short i = 4; i < 7; i++)
                {
                    Square s(i + 97, 1);
                    if(is_under_attack(s, BLACK))
                        return MOVE_FAIL;
                }
                board[0][6] = board[0][4];
                board[0][4] = NULL; 
                board[0][5] = board[0][7];
                board[0][7] = NULL;
                white_short_castle = false;
                white_long_castle = false;
            }
            if(turn == BLACK && side == COMMAND_LONG_CASTLE)
            {
                if(!black_long_castle)
                    return MOVE_FAIL;
                for(short i = 1; i < 4; i++)
                {
                    if(board[7][i] != NULL)
                        return MOVE_FAIL;
                }
                for(short i = 2; i < 5; i++)
                {
                    Square s(i + 97, 8);
                    if(is_under_attack(s, WHITE))
                        return MOVE_FAIL;
                }
                board[7][2] = board[7][4];
                board[7][4] = NULL;
                board[7][3] = board[7][0];
                board[7][0] = NULL;
                black_short_castle = false;
                black_long_castle = false;
            }
            if(turn == BLACK && side == COMMAND_SHORT_CASTLE)
            {
                if(!black_short_castle)
                    return MOVE_FAIL;
                for(short i = 5; i < 7; i++)
                {
                    if(board[7][i] != NULL)
                        return MOVE_FAIL;
                } 
                for(short i = 4; i < 7; i++)
                {
                    Square s(i + 97, 8);
                    if(is_under_attack(s, WHITE))
                        return MOVE_FAIL;
                }
                board[7][6] = board[7][4];
                board[7][4] = NULL;
                board[7][5] = board[7][7];
                board[7][7] = NULL;
                black_short_castle = false;
                black_long_castle = false;
            }
            if(turn == WHITE)
                turn = BLACK;
            else
                turn = WHITE;
                
            return MOVE_SUCCESS;
        }
        
        short move(Square s1, Square s2)
        {
            unsigned short x1 = s1.get_x();
            unsigned short y1 = s1.get_y();
            unsigned short x2 = s2.get_x();
            unsigned short y2 = s2.get_y();
            Square trajectory[8];
            unsigned short trajectory_len = 0;
            
            if(!board[y1][x1] || board[y1][x1]->color != turn)
                return MOVE_FAIL;
            
            if(trajectory_len = board[y1][x1]->get_trajectory(s1, s2, trajectory))
            {
                if(dynamic_cast<Pawn*>(board[y1][x1]))
                {
                    if(x2 != x1 && board[y2][x2] == NULL && !is_en_passant(s1, s2))
                        return MOVE_FAIL;
                    if(x1 == x2 && board[y2][x2])
                        return MOVE_FAIL;
                }
                
                if(trajectory_len == 1)
                    return MOVE_CANCEL;
                if(board[y2][x2] && board[y1][x1]->color == board[y2][x2]->color)
                    return MOVE_FAIL;
                
                for(short i = 1; i < trajectory_len - 1; i++)
                {
                    if(board[trajectory[i].get_y()][trajectory[i].get_x()] != NULL)
                    {
                        return MOVE_FAIL;
                    }
                }
                
                board[y1][x1]->get_name();
                cout << " ";
                s1.print();
                cout << " -> ";
                s2.print();
                if(board[y2][x2] != NULL)
                {                    
                    cout << " capture ";
                    board[y2][x2]->get_name();
                }
                else if(is_en_passant(s1, s2))
                {
                    cout << " capture "; 
                    board[y1][x2]->get_name();
                    cout << " en passant";
                }
                cout << endl; 
                
                if(board[y1][x1] == board[0][4] || board[y2][x2] == board[0][4])
                {
                    white_short_castle = false;
                    white_long_castle = false;
                }
                if(board[y1][x1] == board[7][4] || board[y2][x2] == board[7][4])
                {
                    black_long_castle = false;
                    black_short_castle = false;
                }
                if(board[y1][x1] == board[0][0] || board[y2][x2] == board[0][0])
                    white_long_castle = false;
                if(board[y1][x1] == board[0][7] || board[y2][x2] == board[0][7])
                    white_short_castle = false;
                if(board[y1][x1] == board[7][0] || board[y2][x2] == board[7][0])
                    black_long_castle = false;
                if(board[y1][x1] == board[7][7] || board[y2][x2] == board[7][7])
                    black_short_castle = false; 
                
                if(is_en_passant(s1,s2))
                    board[y1][x2] = NULL;
                board[y2][x2] = board[y1][x1];
                board[y1][x1] = NULL;
                
                if(dynamic_cast<Pawn*>(board[y2][x2]) && abs(y2 - y1) == 2)
                    en_passant = x1;
                else
                    en_passant = -1;                    
                
                if(dynamic_cast<Pawn*>(board[y2][x2]) && y2 == 7 && board[y2][x2]->color == WHITE)
                {
                   board[y2][x2] = promote(WHITE);
                   cout << "White Pawn promoted to ";
                   board[y2][x2]->get_name();
                }
                if(dynamic_cast<Pawn*>(board[y2][x2]) && y2 == 0 && board[y2][x2]->color == BLACK)
                {
                   board[y2][x2] = promote(BLACK);
                   cout << "Black Pawn promoted to ";
                   board[y2][x2]->get_name();
                }
                
                if(turn == WHITE)
                    turn = BLACK;
                else
                    turn = WHITE;
                
                return MOVE_SUCCESS;
            }
            return MOVE_FAIL;
        }

        bool is_under_attack(Square s1, short c)
        {
            unsigned short len;
            bool piece;
            Square trajectory[8];
            for(short y = 0; y < 8; y++)
                for(short x = 0; x < 8; x++)
                    if(board[y][x] && board[y][x]->color == c)
                    {
                        piece = false;
                        Square s2(x + 97, y + 1);
                        len = board[y][x]->get_trajectory(s2, s1, trajectory);
                        if(len == 0 || len == 1)
                            continue;
                        for(short i = 1; i < len - 1; i++)
                        {
                            if(board[trajectory[i].get_y()][trajectory[i].get_x()])
                                piece = true;
                        }
                        if(piece == false)
                        {
                            if(dynamic_cast<Pawn*>(board[y][x]) && x == s1.get_x())
                                continue;
                            return true;
                        }
                    }
            return false;
        }

        Piece * promote(short col)
        {
            char ch;
            Piece *piece = NULL;
            
            cout << "Choose a piece for promotion." << endl;
            cout << "b) Bishop   k) Knight" << endl;
            cout << "q) Queen    r) Rook" << endl;
            cout << "Enter b, k, q or r: ";
            while(!piece)
            {
                cin >> ch;
                ch = toupper(ch);
                if(ch == 'B')
                    piece = new Bishop(col);
                else if(ch == 'K')
                    piece = new Knight(col);
                else if(ch == 'Q')
                    piece = new Queen(col);
                else if(ch == 'R')
                    piece = new Rook(col);
                else
                    cout << "Try again. You must choose b, k, q or r : ";
                while (getchar() != '\n');
            }
            return piece;
        }

        bool is_en_passant(Square s1, Square s2)
        {
            unsigned short x1 = s1.get_x();
            unsigned short y1 = s1.get_y();
            unsigned short x2 = s2.get_x();
            unsigned short y2 = s2.get_y();
            if(!dynamic_cast<Pawn*>(board[y1][x1]))
                return false;
            if(abs(x2 - x1) != 1 || en_passant != x2)
                return false;
            if(board[y1][x1]->color == WHITE && (y2 != 5 || y1 != 4))
                return false;
            if(board[y1][x1]->color == BLACK && (y2 != 2 || y1 != 3))
                return false;
            return true;
        }            
};

short get_command(Square &s)
{
    string command;
    char row, col;
    while(1)
    {
        cin >> command;
        while (getchar() != '\n')
        for(short i = 0; i < command.length(); i++)
            command[i] = tolower(command[i]);
        if(command == "exit")
            return COMMAND_EXIT;
        if(command == "short-castle")
            return COMMAND_SHORT_CASTLE;
        if(command == "long-castle")
            return COMMAND_LONG_CASTLE;
        if(command.length() != 2)
            cout << "Invalid command. Try again." << endl;
        else
        {
            col = command[0];
            row = command[1];
            if(row > '9' || row < '0')
            {
                cout << "Invalid command. Try again." << endl; 
                continue;
            }
            try
            {
                s = Square(col, row - 48);
                return COMMAND_MOVE;
            }
            catch (const char* exp)
            {
               cout << exp << " Try again." << endl;
            }                      
        }
    }
}

int main()
{
    Chessboard board;
    
    Square s1('e', 2);
    Square s2('e', 4);

    while(1)
    {
        system("clear");  
        board.draw();
        short command;
        if(board.get_turn() == WHITE)
            cout << "White's move" << endl;
        else
            cout << "Black's move" << endl;
        cout << "Enter square(or exit):";
        command = get_command(s1);
        if(command == COMMAND_EXIT)
            break;
        if(command == COMMAND_LONG_CASTLE || command == COMMAND_SHORT_CASTLE)
        {
            if(board.castle(command) == MOVE_SUCCESS)
            {
                cout << "Success castle" << endl;
                getchar();
            }
            else
            {
                cout << "Can not castle" << endl;
                getchar();
            }
            getchar();
            continue;
        }
        cout << "Enter square(or exit):";
        command = get_command(s2);
        if(command == COMMAND_EXIT)
            break;
        if(command == COMMAND_LONG_CASTLE || command == COMMAND_SHORT_CASTLE)
        {
            cout << "Invalid move" << endl;
            getchar();
            getchar();
            continue;
        }      
        short ans = board.move(s1, s2);      
        if(ans == MOVE_CANCEL)
            cout << "Move canceled" << endl;
        if(ans == MOVE_FAIL)
            cout << "Invalid move" << endl;
        getchar();        
    }

    return 0;
}
