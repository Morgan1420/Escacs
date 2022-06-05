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
    void end();  
    
    
    
private:
    Chessboard chessBoard;
    VecOfPositions casellesResaltar;
};

#endif /* CurrentGame_hpp */
