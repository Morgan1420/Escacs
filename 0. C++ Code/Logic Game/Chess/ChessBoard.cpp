#include "ChessBoard.h"


// ---------------------------------------------------------------------------------------- llegir arxiu
void Chessboard::LoadBoardFromFile(const string& nomFitxer)
{

	ifstream fitxer(nomFitxer);
	string linea;

	ChessPosition pos;
	int posVertical, posHoritzontal;

	ChessPieceType tipus;
	ChessPieceColor color;

	do {

		getline(fitxer, linea);



		// Mirem de quin color es
		if (linea.at(0) == '0')
			color = CPC_White;
		else if (linea.at(0) == '1')
			color = CPC_Black;
		else
			color = CPC_NONE;



		// Mirem quin tipus de fitxa es
		switch (linea.at(3))
		{
		case 'R':
			tipus = CPT_King;
			break;

		case 'D':
			tipus = CPT_Queen;
			break;

		case 'T':
			tipus = CPT_Rook;
			break;

		case 'A':
			tipus = CPT_Bishop;
			break;

		case 'C':
			tipus = CPT_Knight;
			break;

		case 'P':
			tipus = CPT_Pawn;
			break;
		}

		// Mirem la seva posició Horitzontal
		switch (linea.at(4))
		{
		case 'a':
			posHoritzontal = 0;
			break;
		case 'b':
			posHoritzontal = 1;
			break;
		case 'c':
			posHoritzontal = 2;
			break;
		case 'd':
			posHoritzontal = 3;
			break;
		case 'e':
			posHoritzontal = 4;
			break;
		case 'f':
			posHoritzontal = 5;
			break;
		case 'g':
			posHoritzontal = 6;
			break;
		case 'h':
			posHoritzontal = 7;
			break;
		}

		// Mirem la seva posició vertical
		switch (linea.at(5))
		{
		case '1':
			posVertical = 7;
			break;
		case '2':
			posVertical = 6;
			break;
		case '3':
			posVertical = 5;
			break;
		case '4':
			posVertical = 4;
			break;
		case '5':
			posVertical = 3;
			break;
		case '6':
			posVertical = 2;
			break;
		case '7':
			posVertical = 1;
			break;
		case '8':
			posVertical = 0;
			break;
		}

		pos.setPosicioX(posHoritzontal);
		pos.setPosicioY(posVertical);

		m_tauler[posHoritzontal][posVertical].setColor(color);
		m_tauler[posHoritzontal][posVertical].setTipus(tipus);

	} while (!fitxer.eof());

	fitxer.close();
}


// ---------------------------------------------------------------------------------------- moure fitxa
bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{
	bool esPot = false;

	if (GetPieceColorAtPos(posFrom) != CPC_NONE && posicioDinsVector(posTo, GetValidMoves(posFrom)))
	{
		setNovaPiece(posTo, m_tauler[posFrom.getPosicioX()][posFrom.getPosicioY()].getColor(), m_tauler[posFrom.getPosicioX()][posFrom.getPosicioY()].getTipus(), m_tauler[posFrom.getPosicioX()][posFrom.getPosicioY()].getMoguda());
		setNovaPiece(posFrom, CPC_NONE, CPT_EMPTY, 0);

		esPot = true;
	}

	return esPot;
}

bool Chessboard::posicioDinsVector(const ChessPosition& pos, VecOfPositions vectorPos)
{
	int i = 0;
	bool trobat = false;

	while (!trobat && i < vectorPos.size())
	{
		if (pos == vectorPos.at(i))
			trobat = true;
		else
			i++;
	}

	return trobat;
}

// ---------------------------------------------------------------------------------------- taula to string
string Chessboard::taulaToString() const
{
	string taulaStr = "";

	for (int fila = 0; fila < NUM_ROWS; fila++)
	{
		// afegim els noms de la fila
		taulaStr.append(to_string(8 - fila));

		// afegim columna a columna les fitxes
		for (int columna = 0; columna < NUM_COLS; columna++)
		{
			taulaStr.append(" ");
			taulaStr.append(m_tauler[fila][columna].pieceToString());
		}

		taulaStr.append("\n");

	}

	// afegim els noms de les files
	taulaStr.append("  a  b  c  d  e  f  g  h");
	return taulaStr;
}



// funcions auxiliars que ens permeten jugar amb les fitxes amb l'objectiu d'acotar codi
ChessPieceColor Chessboard::GetPieceColorAtPos(ChessPosition pos) const
{
	return m_tauler[pos.getPosicioX()][pos.getPosicioY()].getColor();
}

ChessPieceType Chessboard::GetPieceTypeAtPos(ChessPosition pos) const
{
	return m_tauler[pos.getPosicioX()][pos.getPosicioY()].getTipus();
}

bool Chessboard::getMogudaPiece(const ChessPosition pos)
{
	// les uniques peces que depenen de si s'han mogut previament són el rei, les torres i els peons
	bool moguda = m_tauler[pos.getPosicioX()][pos.getPosicioY()].getMoguda();

	if (!moguda)
	{
		// Pawn
		if (GetPieceTypeAtPos(pos) == CPT_Pawn && (pos.getPosicioY() != 1 && pos.getPosicioY() != 6))
			moguda = true;

		// King

		// Rook
	}

	return moguda;
}


void Chessboard::setNovaPiece(ChessPosition pos, ChessPieceColor color, ChessPieceType tipus, bool moguda)
{
	m_tauler[pos.getPosicioX()][pos.getPosicioY()].setColor(color);
	m_tauler[pos.getPosicioX()][pos.getPosicioY()].setTipus(tipus);
	m_tauler[pos.getPosicioX()][pos.getPosicioY()].setMoguda(moguda);
}


void Chessboard::render() 
{
	//GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_WHITE, 0, 0);

	for (int posX = 0; posX < NUM_COLS; posX++)
	{
		for (int posY = 0; posY < NUM_COLS; posY++)
		{
			m_tauler[posX][posY].render(CELL_INIT_X + posX * CELL_W, CELL_INIT_Y + posY * CELL_H);
		}
	}
}