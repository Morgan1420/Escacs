#ifndef CurrentGame_hpp
#define CurrentGame_hpp

#include <stdio.h>
#include <string>
#include "GameInfo.h"

#include <Windows.h>

#include "ChessBoard.h"

using namespace std;



class CurrentGame {

public:
    CurrentGame() {};
    
    // init, update i end
    void init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
	bool updateAndRender(int mousePosX, int mousePosY, bool mouseStatus);
    void end();  

    // metodes de joc
    void jugarPartida(int mousePosX, int mousePosY, bool mouseStatus);
    void menu(int mousePosX, int mousePosY, bool mouseStatus);
    void reproduirPartida();

    // prints
    void printWinner();
    void printTorn();
private:
    Chessboard chessBoard;
    VecOfPositions casellesResaltar;
    ChessPieceColor m_torn;
    bool m_gameOver;
    int m_decisioMenu;
    string m_initialBoardFile, m_movementsFile, m_partidaGuardada;
    queue<string> m_moviments;
};

#endif /* CurrentGame_hpp */
