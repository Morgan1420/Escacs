#include "Piece.h"


// ----------------------- Constructors 
Piece::Piece()
{
	m_color = CPC_NONE;
	m_tipus = CPT_EMPTY;
	m_moguda = false;
}


// ----------------------- Metodes
string Piece::pieceToString() const
{
	string str = "";

	switch (m_color)
	{
	case CPC_White:
		str.append("w");
		break;

	case CPC_Black:
		str.append("b");
		break;

	default:
		str.append("_");
	}

	switch (m_tipus)
	{
	case CPT_King:
		str.append("K");
		break;

	case CPT_Queen:
		str.append("Q");
		break;

	case CPT_Rook:
		str.append("R");
		break;

	case CPT_Knight:
		str.append("H");
		break;

	case CPT_Bishop:
		str.append("B");
		break;

	case CPT_Pawn:
		str.append("P");
		break;

	default:
		str.append("_");
	}

	return str;
}

void Piece::render(int posX, int posY)
{

	if (m_color == CPC_Black)
	{
		switch(m_tipus)
		{
		case CPT_King:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_BLACK, posX, posY);
			break;													   
		case CPT_Queen:												   
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_BLACK, posX, posY);
			break;													   
		case CPT_Bishop:											   
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_BLACK, posX, posY);
			break;													   
		case CPT_Knight:											   
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_BLACK, posX, posY);
			break;													   
		case CPT_Rook:												   
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_BLACK, posX, posY);
			break;													   
		case CPT_Pawn:												   
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_BLACK, posX, posY);
			break;
		}
	}
	else if (m_color == CPC_White)
	{
		switch (m_tipus)
		{
		case CPT_King:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_WHITE, posX, posY);
			break;
		case CPT_Queen:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_WHITE, posX, posY);
			break;
		case CPT_Bishop:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_WHITE, posX, posY);
			break;
		case CPT_Knight:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_WHITE, posX, posY);
			break;
		case CPT_Rook:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_WHITE, posX, posY);
			break;
		case CPT_Pawn:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, posX, posY);
			break;
		}
	}
}
