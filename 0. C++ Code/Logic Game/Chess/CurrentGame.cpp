//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "CurrentGame.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"

#include "ChessBoard.h"

CurrentGame::CurrentGame()
{

}


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    // Dibuixem el tauler, eliminem les fitxes a resaltar i asignem el 1r torn a les blanques;
    if (mode == GM_NORMAL)
    {
        GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, 0, 0);
        chessBoard.LoadBoardFromFile(intitialBoardFile);
        casellesResaltar.clear();
        m_torn = CPC_White;
        m_gameOver = false;
    }

}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
      
    // Renderitzat de les fitxes
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);   
    chessBoard.render();
    for(int i = 0; i < casellesResaltar.size(); i++)
        GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + CELL_W * casellesResaltar.at(i).getPosicioX(), CELL_INIT_Y + CELL_H * casellesResaltar.at(i).getPosicioY());


    // Analitzem si el jugador pitja una casella
    int posX = 0;
    bool trobat = false;
    while (posX < NUM_COLS && !trobat)
    {
        int  posY = 0;
        while (posY < NUM_ROWS && !trobat)
        {
            if (mouseStatus && (CELL_INIT_X + CELL_W * posX < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * (posX + 1)) && (CELL_INIT_Y + CELL_H * posY < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * (posY + 1)))
            {
                // mirem si la casella que pitjem està resaltada
                int k = 0;
                bool moure = false;
                while (k < casellesResaltar.size() && !moure)
                {
                    if (casellesResaltar.at(k).getPosicioX() == posX && casellesResaltar.at(k).getPosicioY() == posY)
                        moure = true;

                    k++;
                }

                // procedim a fer diferents coses depenent si la casella estava resaltada o no
                if (!moure)
                {
                    ChessPosition pos(posX, posY);
                    if (chessBoard.GetPieceColorAtPos(pos) == m_torn)
                    {
                        chessBoard.setCasellaSeleccionada(pos);
                        casellesResaltar = chessBoard.GetValidMoves(chessBoard.getCasellaSeleccionada());
                    }                    
                }
                else
                {
                    ChessPosition desti(posX, posY);
                    chessBoard.MovePiece(chessBoard.getCasellaSeleccionada(), desti, m_gameOver);
                    casellesResaltar.clear();

                    
                    
                    if (m_torn == CPC_Black)
                        m_torn = CPC_White;
                    else
                        m_torn = CPC_Black;
                    
                }

                trobat = true;

                
            }
            posY++;
        }
        posX++;
    }
    
    this->printTorn();
    

    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS)  + 60  ;
    std::string msg = "PosX: "  /* + to_string(mousePosX) + ", PosY: " + to_string(mousePosY)*/;
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);



    return m_gameOver;

}

void CurrentGame::printWinner()
{
    std::string guanyador (m_torn == CPC_White ? "Negres" : "Blanques");
    std::string msg = "Guanyen les " + guanyador + "!!";
    
    GraphicManager::getInstance()->drawFont(FONT_RED_30, 50, 260, 2, msg);
}

void CurrentGame::printTorn()
{
    std::string torn(m_torn == CPC_White ? "Negres" : "Blanques");
   
    std::string msg = "Torn de les: " + torn;
    GraphicManager::getInstance()->drawFont(FONT_RED_30, 330, 640, 0.8, msg);
}


void CurrentGame::end()
{

}