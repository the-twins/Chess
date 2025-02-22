#include <iostream>
#include <string>

using namespace std;

const short BLACK = 1;
const short WHITE = 0;
const short BOARD_SIZE = 8;
string COLOR[2] = {"white", "black"};

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
            cout << "P";
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
            cout << "R";
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
            cout << "B";
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
            cout << "k";
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
            cout << "Q";
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
            cout << "K";
        }
};

class Square
{
    unsigned short row;
    char col;
 
    public:
        Square(char c, unsigned short r)
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
};

class Chessboard
{
    Piece * board[BOARD_SIZE][BOARD_SIZE];
    
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
        }
        
        void draw()
        {
            for(short i = BOARD_SIZE - 1; i >= 0; i--)
            {
                cout << i + 1;
                for(short j = 0; j < BOARD_SIZE; j++)
                    if(board[i][j] != NULL)
                        board[i][j]->draw();
                    else
                        cout << ".";
                cout << endl;
            }
            cout << " abcdefgh" << endl;
        }
        
        int move(Square s1, Square s2)
        {
            unsigned short x1 = s1.get_x();
            unsigned short y1 = s1.get_y();
            unsigned short x2 = s2.get_x();
            unsigned short y2 = s2.get_y();
            
            if(!board[y1][x1])
                return 1;
            if(board[y2][x2] && board[y1][x1]->color == board[y2][x2]->color)
                return 2;
            cout << "Hello"<< endl;
            board[y2][x2] = board[y1][x1];
            board[y1][x1] = NULL;
            return 0;
        }            
};


    
int main()
{
    Chessboard board;
    
    /*board.draw();
    try
    {
        Square square('e', 2);
        square.print();
        cout << square.get_x() << square.get_y();
    }
    catch (const char* exp)
    {
        cout << exp << endl;
        return 1;
    }
    cout << endl;*/
    Square s('e', 2);
    Square s1('e', 4);
    cout << board.move(s, s1) << endl;
    board.draw();
    
    
    
    
    
    return 0;
}
