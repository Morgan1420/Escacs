#pragma once
#include "Piece.h"
#include "ChessPosition.h"
#include <queue>

#define NUM_ROWS 8
#define NUM_COLS 8

typedef vector<ChessPosition> VecOfPositions;

class Chessboard
{
public:   
    // Constructor
    Chessboard() : m_gameOver(false), m_primeraTirada(true) {}

    // Getters i Setters
    Piece getPiece(int x, int y) { return m_tauler[x][y]; }
    ChessPosition getCasellaSeleccionada() { return m_casellaSeleccionada; }
    void setCasellaSeleccionada(ChessPosition casella) { m_casellaSeleccionada = casella; }
    void setPrimerTorn(bool primerTorn) { m_primeraTirada = primerTorn; }
    void taulerAZero();

    // Metodes amb files
    void LoadBoardFromFile(const string& nomFitxer); // Cal copiar i modificar el metode loadFromFile de Source.cpp
    void SaveBoardToFile(const string& nomFitxer);
    void movementsToFile(const string& nomFitxer);

    // visualitzaciˇ
    void render();
    string taulaToString() const;

    // Metodes auxiliars
    VecOfPositions GetValidMoves(const ChessPosition& pos);
    bool posicioValida(ChessPosition posAuxiliar, ChessPosition pos);
    bool posicioDinsVector(const ChessPosition& pos, VecOfPositions vectorPos);
    int busquedaDeReis();

    // metodes directes de Piece
    ChessPieceColor GetPieceColorAtPos(ChessPosition pos) const;
    ChessPieceType GetPieceTypeAtPos(ChessPosition pos) const;
    bool getMogudaPiece(const ChessPosition pos);
    void setNovaPiece(ChessPosition pos, ChessPieceColor color, ChessPieceType tipus, bool moguda);
    bool MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo, bool& gameOver);
    void peonsAReines();

    // analisis
    void analisiDiagonals(const ChessPosition& pos, VecOfPositions& vectorPos);
    void analisiVerticals(const ChessPosition& pos, VecOfPositions& vectorPos);
    void analisiHoritzontals(const ChessPosition& pos, VecOfPositions& vectorPos);
    void analisiPeo(const ChessPosition& pos, VecOfPositions& vectorPos);
    void analisiCavall(const ChessPosition& pos, VecOfPositions& vectorPos);
private:
    Piece m_tauler[NUM_COLS][NUM_ROWS];
    ChessPosition m_casellaSeleccionada;
    bool m_gameOver;
    string m_lastMovement;
    bool m_primeraTirada;
};


/*
    Aqui representem un tauler d'escacs amb les negres amunt i les blanques avall:

        i/j 0       1       2       3       4       5       6       7
        0   TORRE   CAVALL  ALFIL   DAMA    REI     ALFIL   CAVALL  TORRE
        1   PEO     PEO     PEO     PEO     PEO     PEO     PEO     PEO
        2   BUIT    BUIT    BUIT    BUIT    BUIT    BUIT    BUIT    BUIT
        3   BUIT    BUIT    BUIT    BUIT    BUIT    BUIT    BUIT    BUIT
        4   BUIT    BUIT    BUIT    BUIT    BUIT    BUIT    BUIT    BUIT
        5   BUIT    BUIT    BUIT    BUIT    BUIT    BUIT    BUIT    BUIT
        6   PEO     PEO     PEO     PEO     PEO     PEO     PEO     PEO
        7   TORRE   CAVALL  ALFIL   DAMA    REI     ALFIL   CAVALL  TORRE
*/