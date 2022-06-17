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

// ---------------------------------------------------------------------------------------- guardar a Arxiu
void Chessboard::SaveBoardToFile(const string& nomFitxer) //0. Ta1
{
	ofstream fitxer(nomFitxer);

	fitxer.clear();
	for (int fila = 0; fila < NUM_COLS; fila++)
	{
		for (int col = 0; col < NUM_ROWS; col++)
		{
			
			if (m_tauler[col][fila].getTipus() != CPT_EMPTY)
			{
				if (col != 0 || fila != 0)
					fitxer << "\n";

				// color
				if (m_tauler[col][fila].getColor() == CPC_White)
					fitxer << "0. ";
				else
					fitxer << "1. ";

				// tipus
				switch (m_tauler[col][fila].getTipus())
				{
				case CPT_King:
					fitxer << "R";
					break;
				case CPT_Queen:
					fitxer << "D";
					break;
				case CPT_Rook:
					fitxer << "T";
					break;
				case CPT_Bishop:
					fitxer << "A";
					break;
				case CPT_Knight:
					fitxer << "C";
					break;
				case CPT_Pawn:
					fitxer << "P";
					break;
				}

				//Posicio
				char lletra = 97 + col;
				fitxer << lletra << to_string(8 - fila);
			}
		}

	}
	fitxer.close();
}

// ---------------------------------------------------------------------------------------- guardar moviments
void Chessboard::movementsToFile(const string& nomFitxer)
{
	queue<string> moviments;
	
	// guardem els moviments previs en una queue i afegim l'ultim moviment al final
	ifstream fitxer(nomFitxer);
	
	while (!fitxer.eof())
	{
		string moviment;
		getline(fitxer, moviment);
		moviments.push(moviment + "\n");
	}
	moviments.push(m_lastMovement);
	
	fitxer.close();
	
	// fem servir un string per eliminar les imperfeccions del 1r torn i es guarda tot al fitxer
	ofstream file(nomFitxer);
	string stringMoviments;
	while (!moviments.empty())
	{
		stringMoviments.append(moviments.front());
		moviments.pop();		
	}

	
	if (m_primeraTirada)
	{
		stringMoviments.erase(stringMoviments.begin());
		m_primeraTirada = false;
	}

	file << stringMoviments;
	file.close();
}

// ---------------------------------------------------------------------------------------- tauler a zero
void Chessboard::taulerAZero()
{
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			ChessPosition pos(row, col);
			setNovaPiece(pos, CPC_NONE, CPT_EMPTY, 0);
		}
	}
}

// -------------------------------------------------------------------------------------------------------------------- moure fitxa
bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo, bool& gameOver)
{
	// en aquesta funcio no guardem els moviments
	bool esPot = false;

	if (GetPieceColorAtPos(posFrom) != CPC_NONE && posicioDinsVector(posTo, GetValidMoves(posFrom)))
	{
		m_lastMovement = posFrom.toString() + posTo.toString();

		if (GetPieceTypeAtPos(posTo) == CPT_King)
			gameOver = true;
		setNovaPiece(posTo, m_tauler[posFrom.getPosicioX()][posFrom.getPosicioY()].getColor(), m_tauler[posFrom.getPosicioX()][posFrom.getPosicioY()].getTipus(), 1);
		setNovaPiece(posFrom, CPC_NONE, CPT_EMPTY, 1);
		peonsAReines(); 

		esPot = true;
	}

	return esPot;
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



// --------------------------------------------------------------------------------------- getters de les peces 
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

	return moguda;
}

// --------------------------------------------------------------------------------------------- set Nova piece
void Chessboard::setNovaPiece(ChessPosition pos, ChessPieceColor color, ChessPieceType tipus, bool moguda)
{
	m_tauler[pos.getPosicioX()][pos.getPosicioY()].setColor(color);
	m_tauler[pos.getPosicioX()][pos.getPosicioY()].setTipus(tipus);
	m_tauler[pos.getPosicioX()][pos.getPosicioY()].setMoguda(moguda);
}


// ---------------------------------------------------------------------------------------------- altres metodes
void Chessboard::peonsAReines()
{
	for (int row = 0; row < 2; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			if (m_tauler[col][(NUM_ROWS - 1) * row].getTipus() == CPT_Pawn)
				m_tauler[col][(NUM_ROWS - 1) * row].setTipus(CPT_Queen);			
		}
	}
}

bool checkmate() 
{

	return false;
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

// --------------------------------------------------------------------------------- busqueda de reis
int Chessboard::busquedaDeReis()
{
	int contador = 0, guanyador = 0;

	for (int row = 0; row < NUM_ROWS; row++) // aquests loops hourien de ser whiles
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			if (m_tauler[row][col].getTipus() == CPT_King)
			{
				contador++;

				if (m_tauler[row][col].getColor() == CPC_Black)
					guanyador = 2;
				else if (m_tauler[row][col].getColor() == CPC_White)
					guanyador = 1;
			}
		}
	}

	if (contador > 1)
		return 0;
	return guanyador;
}

// --------------------------------------------------------------------------------- render
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
