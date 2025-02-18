#include <iostream>
#include <string>

using namespace std;

const short BLACK = 1;
const short WHITE = 0;
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

void show_name(Piece & p)
{
    p.get_name();
}
    
int main()
{
    Pawn pawn(WHITE);
    Rook rook(BLACK);
    Bishop bishop(BLACK);
    Knight knight(BLACK);
    Queen queen(BLACK);
    King king(BLACK);
    show_name(pawn);
    show_name(rook);
    show_name(bishop);
    show_name(knight);
    show_name(queen);
    show_name(king);
    king.draw();
    queen.draw();
    knight.draw();
    bishop.draw();
    pawn.draw();
    rook.draw();
    
    return 0;
}
