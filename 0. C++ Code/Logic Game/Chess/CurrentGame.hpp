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
    CurrentGame();
    
    void init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
	bool updateAndRender(int mousePosX, int mousePosY, bool mouseStatus);
    void printWinner ();
    void end();  
    void printTorn();
    
private:
    Chessboard chessBoard;
    VecOfPositions casellesResaltar;
    ChessPieceColor m_torn;
    bool m_gameOver;
};

#endif /* CurrentGame_hpp */
