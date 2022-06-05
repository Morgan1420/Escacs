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
    GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, 0, 0);
    chessBoard.LoadBoardFromFile(intitialBoardFile);
    casellesResaltar.clear();
    m_torn = CPC_White;
}


void CurrentGame::end()
{

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
                    chessBoard.MovePiece(chessBoard.getCasellaSeleccionada(), desti);
                    casellesResaltar.clear();
                    
                    if (m_torn == CPC_Black)
                        m_torn = CPC_White;
                    else
                        m_torn = CPC_Black;

                    Sleep(100);
                    
                }

                trobat = true;
                
            }
            posY++;
        }
        posX++;
    }
    



    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;
    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);


    
    // TODO 2.2 Dibuixar el peó a sobre del tauler només si estem pressionant el botó esquerre del mouse dins dels límits del tauler
    //          Si no l'estem pressionant o l'estem pressionant fora dels límits del tauler només s'ha de dibuixar el tauler sense el peó





    // TODO 2.3 Dibuixar el peó a sobre del tauler només si estem pressionant el botó esquerre del mouse dins dels límits del tauler
    //          S'ha de dibuixar el peó a la casella sobre la que estem clicant amb el ratolí
    //          Si no l'estem pressionant o l'estem pressionant fora dels límits del tauler només s'ha de dibuixar el tauler sense el peó
 





    //TODO 3: Imprimir text per pantalla
    //------------------------------------------
    // TODO 3.1: Imprimir les coordenades de la posició actual del ratolí a sota del tauler







    //TODO 4: Mostrar l’estat inicial del joc amb totes les peces col·locades a la seva posició inicial
    //------------------------------------------
 



    return false;

}

