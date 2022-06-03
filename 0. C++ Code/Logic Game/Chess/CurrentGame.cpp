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
    GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, 0, 0);
    chessBoard.LoadBoardFromFile(intitialBoardFile);
    casellesResaltar.clear();
}


void CurrentGame::end()
{

}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
    //TODO 1: Interactuar amb la crida per dibuixar gr�fics (sprites).
    // 	      Dibuixar a pantalla el gr�fic amb el tauler buit.
    //--------------------------------------------------------------
    
    
    // Renderitzat de les fitxes
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);   
    chessBoard.render();
    for(int i = 0; i < casellesResaltar.size(); i++)
        GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + CELL_W * casellesResaltar.at(i).getPosicioX(), CELL_INIT_Y + CELL_H * casellesResaltar.at(i).getPosicioY());


    //TODO 2: Interacci� amb el mouse
    //------------------------------------------
    // TODO 2.1: Dibuixar el pe� a sobre del tauler nom�s si estem pressionant el bot� esquerre del mouse
    //          Si no l'estem pressionant nom�s s'ha de dibuixar el tauler sense el pe�

    int posX = 0;
    bool trobat = false;
    while (posX < NUM_COLS && !trobat)
    {
        int  posY = 0;
        while (posY < NUM_ROWS && !trobat)
        {
            if (mouseStatus && (CELL_INIT_X + CELL_W * posX < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * (posX + 1)) && (CELL_INIT_Y + CELL_H * posY < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * (posY + 1)))
            {
                ChessPosition pos(posX, posY);
                casellesResaltar = chessBoard.GetValidMoves(pos);
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



    // TODO 2.2 Dibuixar el pe� a sobre del tauler nom�s si estem pressionant el bot� esquerre del mouse dins dels l�mits del tauler
    //          Si no l'estem pressionant o l'estem pressionant fora dels l�mits del tauler nom�s s'ha de dibuixar el tauler sense el pe�





    // TODO 2.3 Dibuixar el pe� a sobre del tauler nom�s si estem pressionant el bot� esquerre del mouse dins dels l�mits del tauler
    //          S'ha de dibuixar el pe� a la casella sobre la que estem clicant amb el ratol�
    //          Si no l'estem pressionant o l'estem pressionant fora dels l�mits del tauler nom�s s'ha de dibuixar el tauler sense el pe�
 





    //TODO 3: Imprimir text per pantalla
    //------------------------------------------
    // TODO 3.1: Imprimir les coordenades de la posici� actual del ratol� a sota del tauler







    //TODO 4: Mostrar l�estat inicial del joc amb totes les peces col�locades a la seva posici� inicial
    //------------------------------------------
 



    return false;

}

