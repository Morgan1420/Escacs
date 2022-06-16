#include "ChessBoard.h"
#


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

void Chessboard::reproduccioPosicions()
{
	ifstream fitxer("moviments:guardats.txt");
	bool a = 0;

	if (fitxer.is_open() && !fitxer.eof())
	{
		m_reproduint = 1;
		ChessPosition posFrom;
		ChessPosition posTo;
		fitxer >> posFrom >> posTo;
		 
		MovePiece(posFrom, posTo, a);

		while (!fitxer.eof())
		{
			fitxer >> posFrom >> posTo;
			MovePiece(posFrom, posTo, a);
		}
		
	}

	fitxer.close();

}

void Chessboard::guardaPosicioAFitxer(const ChessPosition& posFrom, const ChessPosition& posTo)
{
	ofstream fitxer("moviments_guardats.txt");

	if (fitxer.is_open())
	{
		fitxer << posFrom << " " << posTo;
	}

	fitxer.close();
}

// ---------------------------------------------------------------------------------------- moure fitxa
bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo, bool& gameOver)
{
	bool esPot = false;

	if (GetPieceColorAtPos(posFrom) != CPC_NONE && posicioDinsVector(posTo, GetValidMoves(posFrom)))
	{
		if (GetPieceTypeAtPos(posTo) == CPT_King)
			gameOver = true;
		setNovaPiece(posTo, m_tauler[posFrom.getPosicioX()][posFrom.getPosicioY()].getColor(), m_tauler[posFrom.getPosicioX()][posFrom.getPosicioY()].getTipus(), 1);
		setNovaPiece(posFrom, CPC_NONE, CPT_EMPTY, 1);
		peonsAReines();

		if(m_reproduint == 0)
			guardaPosicioAFitxer(posFrom, posTo);

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

/*
Jaque seria, si una pieza del color contrario a un rey puede llegar a este, entonces el rey se podria mover para evitar esto || otra pieza podria matar
a la pieza atacante (incluido el rey) || una pieza se puede interponer entre la trayectoria del rey y la pieza atacante. El rey
no puede ir a una posicion donde puedan matarlo, quitar del vector de posiciones donde puede ir el rey aquellas posiciones donde pueda ser matado
o quitar del vector de posiciones donde puede ir una pieza que moviendose, puedan matar al rey

Jaque mate seria Jaque && el rey no se puede mover && le estan atacando


Tambien hay que tener en cuenta que, si el rey no esta atacado, al mover cualquier ficha, podria estar atacado, entonces no se puede mover 

*/


//la idea es que check sea una subfuncion de checkmate

bool Chessboard::checkAux(ChessPosition posicion, ChessPosition posicionRei) //crec q fa algo semblant a posicioDinsVector() pero yolo
{
	bool check = false;
	
	VecOfPositions aux;

	aux = GetValidMoves(posicion);

	for (int i = 0; i < aux.size(); i++)
	{
		if (aux[i] == posicionRei)
			check = true;
	}

	if (check)
		m_reiAtacat = true;
	else
		m_reiAtacat = false;

	return check;
}

//si el rei esta atacado

bool Chessboard::check(VecOfPositions &vec, ChessPosition posicionRei) //rep un vector de posicions valides per al rei
{
	bool checkMate = false;

	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS ; j++)
		{
			if (m_tauler[i][j].getTipus() != CPC_NONE) //no faria falta aquest if per que a getValidMoves no contempla les posicions posibles de una casella vuida pero yolo
			{
				if (checkAux(m_tauler[i][j].getPosicion(), posicionRei))
				{
					checkMate = true;
				}
			}
		}
	}

	return false;
}

ChessPosition Chessboard::buscarRei(ChessPieceColor color)
{


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
