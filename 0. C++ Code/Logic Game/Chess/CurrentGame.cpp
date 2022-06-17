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



void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    // Dibuixem el tauler, eliminem les fitxes a resaltar i asignem el 1r torn a les blanques;
    GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, 0, 0);
    m_initialBoardFile = intitialBoardFile;
    m_movementsFile = movementsFile;
    m_partidaGuardada = "data/Games/partida_guardada.txt";
    casellesResaltar.clear();
    m_torn = CPC_White;
    
    m_decisioMenu = 0;
}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus)
{

    switch (m_decisioMenu)
    {
    case 1:
        jugarPartida(mousePosX, mousePosY, mouseStatus);
        break;
    case 2:
        jugarPartida(mousePosX, mousePosY, mouseStatus);
        break;
    case 3:
        reproduirPartida();
        break;
    default:
        menu(mousePosX, mousePosY, mouseStatus);
        
    }

    return m_gameOver;

}

// --------------------------------------------------------------------------------------------------------------------------- metodes de joc
// ----------------------------------------------------------------------------------------------------------- menu principal
void CurrentGame::menu(int mousePosX, int mousePosY, bool mouseStatus) {

    // imprimir missatges 
    int posTextX = CELL_INIT_X;

    std::string msg = "Nova Partida";
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, CELL_INIT_Y + (CELL_H * 1), 0.8, msg);

    msg = "Carregea partida";
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, CELL_INIT_Y + (CELL_H * 3), 0.8, msg);

    msg = "Reproduir partida";
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, CELL_INIT_Y + (CELL_H * 5), 0.8, msg);

    // calcular si es pitja un missatge
    if (mouseStatus && (CELL_INIT_X < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * 2) && (CELL_INIT_Y + (CELL_H * 1) < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * 2))
    {
        // botó new game
        m_decisioMenu = 1;
        m_gameOver = false;
        chessBoard.taulerAZero();
        chessBoard.LoadBoardFromFile(m_initialBoardFile);
        chessBoard.setPrimerTorn(true);

        ofstream file(m_movementsFile);
        file.clear();
        file.close();
    }
    else if (mouseStatus && (CELL_INIT_X < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * 3) && (CELL_INIT_Y + (CELL_H * 3) < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * 4))
    {
        // botó carregar joc
        m_decisioMenu = 2;
        ifstream file(m_partidaGuardada);
        ifstream fileM(m_movementsFile);
        if (file.peek() == '0' || file.peek() == '1')
        {
            chessBoard.taulerAZero();
            chessBoard.LoadBoardFromFile(m_partidaGuardada);
            chessBoard.setPrimerTorn(false);

            // busquem si segueixen vius els reis i quin no ho està
            switch(chessBoard.busquedaDeReis())
            { 
            case 1:
                m_torn = CPC_Black;
                m_gameOver = true;
                break;
            case 2:
                m_torn = CPC_White;
                m_gameOver = true;
                break;
            default:
                string nextMovement, x, y, pos;
                
                getline(fileM, nextMovement);
                
                x = nextMovement.at(2);
                y = nextMovement.at(3);
                pos = x + y;
                
                ChessPosition posTo(pos);
                
                if (chessBoard.GetPieceColorAtPos(posTo) == CPC_Black)
                    m_torn = CPC_White;
                else
                    m_torn = CPC_Black;


                m_gameOver = false;
            }
        }
        else
        {
            chessBoard.setPrimerTorn(true);
            chessBoard.taulerAZero();
            chessBoard.LoadBoardFromFile(m_initialBoardFile);
            m_gameOver = false;
        }
        file.close();
    }
    else if (mouseStatus && (CELL_INIT_X < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * 3) && (CELL_INIT_Y + (CELL_H * 5) < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * 6))
    {
        // reproduir partida
        m_decisioMenu = 3;
        chessBoard.taulerAZero();
        chessBoard.LoadBoardFromFile(m_initialBoardFile);
        m_torn = CPC_White;

        ifstream file(m_movementsFile);
        while (!file.eof())
        {
            string str;
            getline(file, str);
            m_moviments.push(str);
        }
        file.close();
    }
}

// _---------------------------------------------------------------------------------------------------------- jugar partida
void CurrentGame::jugarPartida(int mousePosX, int mousePosY, bool mouseStatus)
{
    // Renderitzat de les fitxes
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    printGameMode();
    chessBoard.render();
    for (int i = 0; i < casellesResaltar.size(); i++)
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

                    chessBoard.SaveBoardToFile(m_partidaGuardada);
                    chessBoard.movementsToFile(m_movementsFile);
                    

                }

                trobat = true;

            }
            posY++;
        }
        posX++;
    }

    printTorn();
}

// ----------------------------------------------------------------------------------------------------------- reproduir partida
void CurrentGame::reproduirPartida()
{
    // Renderitzat de les fitxes
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    printTorn();
    printGameMode();
    chessBoard.render();

    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE) && !m_moviments.empty())
    {
        string nextMovement = m_moviments.front();

        // asignem les posicions de partida i arribada
        string x, y, pos;
        
        // posfrom
        x = nextMovement.at(0);
        y = nextMovement.at(1);
        pos = x + y;
        ChessPosition posFrom(pos);
        
        // posTo
        x = nextMovement.at(2);
        y = nextMovement.at(3);
        pos = x + y;
        ChessPosition posTo(pos);

        // movem la peça que toca
        chessBoard.MovePiece(posFrom, posTo, m_gameOver);

        // eliminem el moviment de la queue
        m_moviments.pop();
        

        if (m_torn == CPC_Black)
            m_torn = CPC_White;
        else
            m_torn = CPC_Black;
    }

    if (m_moviments.empty())
        printReproducioAcabada();


    
}


// -------------------------------------------------------------------------------------- prints 
void CurrentGame::printWinner(int mousePosX, int mousePosY, bool mouseStatus, bool& final)
{
    std::string guanyador (m_torn == CPC_White ? "Negres" : "Blanques");
    std::string msg = "Guanyen les " + guanyador + "!!";
    
    GraphicManager::getInstance()->drawFont(FONT_RED_30, 50, 260, 2, msg);

    msg = "Tornar al menu!!";
    GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X + (CELL_W * 3), CELL_INIT_Y + (CELL_H * 7), 0.8, msg);

    // calcular si es pitja un missatge
    if (mouseStatus && (CELL_INIT_X + CELL_W * 3 < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * 5) && (CELL_INIT_Y + (CELL_H * 7) < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * 8))
    {
        m_decisioMenu = 0;
        m_gameOver = false;
        final = m_gameOver;
    }
}

void CurrentGame::printTorn()
{
    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;

    std::string torn(m_torn == CPC_Black ? "Negres" : "Blanques");
    std::string msg = "Torn de les " + torn;
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);
}

void CurrentGame::printGameMode()
{
    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * (NUM_ROWS)) + 100;

    std::string gameMode(m_decisioMenu == 3 ? "RePlay" : "Normal");
    std::string msg = "Game Mode: " + gameMode;
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);
}

void CurrentGame::printReproducioAcabada()
{
    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * (NUM_ROWS)) + 140;

    std::string msg = "No more moves to replay";
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);
}
// -------------------------------------------------------------------------------------- end
void CurrentGame::end()
{

}