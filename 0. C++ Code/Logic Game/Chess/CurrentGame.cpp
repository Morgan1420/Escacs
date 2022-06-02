//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "CurrentGame.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"


CurrentGame::CurrentGame()
{

}


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    chessBoard.LoadBoardFromFile(intitialBoardFile);
}


void CurrentGame::end()
{

}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
    //TODO 1: Interactuar amb la crida per dibuixar gràfics (sprites).
    // 	      Dibuixar a pantalla el gràfic amb el tauler buit.
    //--------------------------------------------------------------
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    if(mouseStatus)
        GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, CELL_INIT_X, CELL_INIT_Y);
    //TODO 1.1 Afegir l'include de GraphicManager --> #include "../GraphicManager.h"
    //TODO 1.2 Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY);
    //	    Per començar podem cridar el drawSprite amb els params --> (IMAGE_BOARD,0,0)


    



    //TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i un peó blanc a la posició (0,0) de la pantalla
 


    //TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i un peó blanc a la casella (0,0) del tauler
 



    //TODO 1.4: Dibuixar a pantalla el gràfic amb el tauler i un peó blanc a la casella (posX, posY) del tauler
 
 




    //TODO 2: Interacció amb el mouse
    //------------------------------------------
    // TODO 2.1: Dibuixar el peó a sobre del tauler només si estem pressionant el botó esquerre del mouse
    //          Si no l'estem pressionant només s'ha de dibuixar el tauler sense el peó

 




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

