#include<iostream>
#include<Windows.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<dwmapi.h>
#include<vector>
#include<algorithm>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"




// CHESS PIECE CLASS
class chessPiece {
private:

	char pieceType;
	char pieceColour;
	int ind;
	int up;
	int right;
	int totalSquareNum;
	
	//Movement Types
	int mp1;
	int mp2;
	int mp3;
	int mp4;
	int mp5;
	int mp6;
	int mp7;
	int mp8;
	int mp9;
	int mp10;
	int mp11;
	int mp12;
	int mp13;
	int mp14;
	int mp15;
	int mp16;

	// Vector of all squares within the piece's range
	std::vector<int> scope;
	// Vector containing all of the piece's available moves
	std::vector<int> moveSet;

public:
	// Constructor
	chessPiece(int squareIndex, int boardWidth, int boardHeight, char type, char colour, std::vector<chessPiece> pieceList, char postionArray[][2])
	{
		pieceType = type;
		pieceColour = colour;
		ind = squareIndex;
		postionArray[ind][0] = pieceColour;
		postionArray[ind][1] = pieceType;
		up = boardWidth;
		right = 1;
		totalSquareNum = boardWidth * boardHeight;

		mp1 = up;
		mp2 = -up;
		mp3 = right;
		mp4 = -right;
		mp5 = up + right;
		mp6 = up - right;
		mp7 = -up + right;
		mp8 = -up - right;
		mp9 = 2*up + right;
		mp10 = 2*up - right;
		mp11 = -2*up + right;
		mp12 = -2*up - right;
		mp13 = up + 2*right;
		mp14 = up - 2*right;
		mp15 = -up + 2*right;
		mp16 = -up - 2*right;

		// initialise scope
		switch (pieceType) {
		case 'P': // PAWN
			switch (pieceColour) {
				case 'w': // white
					// Up
					if (ind + mp1 < totalSquareNum) {
						scope.push_back(ind + mp1);
						scope.push_back(ind + 2*mp1);
					}
					// North-East Diagonal
					if ((ind + mp5 < totalSquareNum) && ((ind + 1) % up != 0)) {
						scope.push_back(ind + mp5);
					}
					// North-West Diagonal
					if ((ind + mp6 < totalSquareNum) && ((ind + 1) % up != 1)) {
						scope.push_back(ind + mp6);
					}
					break;
				case 'b': // black
					// Down
					if (ind + mp2 >= 0) {
						scope.push_back(ind + mp2);
						scope.push_back(ind + 2*mp2);
					}
					// South-East Diagonal
					if ((ind + mp7 >= 0) && ((ind + 1) % up != 0)) {
						scope.push_back(ind + mp7);
					}
					// South-West Diagonal
					if ((ind + mp8 >= 0) && ((ind + 1) % up != 1)) {
						scope.push_back(ind + mp8);
					}
					break;
			}			
			break;
		case 'N': //KNIGHT
			// 2 Up 1 Right
			if ((ind + mp9 < totalSquareNum) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				scope.push_back(ind + mp9);
			}
			// 2 Up 1 Left
			if ((ind + mp10 < totalSquareNum) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				scope.push_back(ind + mp10);
			}
			// 2 Down 1 Right
			if ((ind + mp11 >= 0) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				scope.push_back(ind + mp11);
			}
			// 2 Down 1 Left
			if ((ind + mp12 >= 0) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				scope.push_back(ind + mp12);
			}
			// 1 Up 2 Right
			if ((ind + mp13 < totalSquareNum) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				scope.push_back(ind + mp13);
			}
			// 1 Up 2 Left
			if ((ind + mp14 < totalSquareNum) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				scope.push_back(ind + mp14);
			}
			// 1 Down 2 Right
			if ((ind + mp15 >= 0) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				scope.push_back(ind + mp15);
			}
			// 1 Down 2 Left
			if ((ind + mp16 >= 0) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				scope.push_back(ind + mp16);
			}
			break;
		case 'B': // BISHOP
			// North-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp5 < totalSquareNum) && ((ind + n * mp5) % up != 0)) {
					scope.push_back(ind + n * mp5);
				}
				else { break; }
			}
			// North-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp6 < totalSquareNum) && ((ind + 1 + n * mp6) % up != 0)) {
					scope.push_back(ind + n * mp6);
				}
				else { break; }
			}
			// South-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp7 >= 0) && ((ind + n * mp7) % up != 0)) {
					scope.push_back(ind + n * mp7);
				}
				else { break; }
			}
			// South-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp8 >= 0) && ((ind + 1 + n * mp8) % up != 0)) {
					scope.push_back(ind + n * mp8);
				}
				else { break; }
			}
			break;
		case 'R': // ROOK
			// Up
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp1 < totalSquareNum) {
					scope.push_back(ind + n * mp1);
				}
				else { break; }
			}
			// Down
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp2 >= 0) {
					scope.push_back(ind + n * mp2);
				}
				else { break; }
			}
			// Right
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 0) && ((ind + n * mp3) % up != 0)) {
					scope.push_back(ind + n * mp3);
				}
				else { break; }
			}
			// Left
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 1) && ((ind + 1 + n * mp4) % up != 0)) {
					scope.push_back(ind + n * mp4);
				}
				else { break; }
			}
			break;
		case 'Q': // QUEEN
			// Up
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp1 < totalSquareNum) {
					scope.push_back(ind + n * mp1);
				}
				else { break; }
			}
			// Down
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp2 >= 0) {
					scope.push_back(ind + n * mp2);
				}
				else { break; }
			}
			// Right
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 0) && ((ind + n * mp3) % up != 0)) {
					scope.push_back(ind + n * mp3);
				}
				else { break; }
			}
			// Left
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 1) && ((ind + 1 + n * mp4) % up != 0)) {
					scope.push_back(ind + n * mp4);
				}
				else { break; }
			}
			// North-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp5 < totalSquareNum) && ((ind + n * mp5) % up != 0)) {
					scope.push_back(ind + n * mp5);
				}
				else { break; }
			}
			// North-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp6 < totalSquareNum) && ((ind + 1 + n * mp6) % up != 0)) {
					scope.push_back(ind + n * mp6);
				}
				else { break; }
			}
			// South-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp7 >= 0) && ((ind + n * mp7) % up != 0)) {
					scope.push_back(ind + n * mp7);
				}
				else { break; }
			}
			// South-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp8 >= 0) && ((ind + 1 + n * mp8) % up != 0)) {
					scope.push_back(ind + n * mp8);
				}
				else { break; }
			}
			break;
		case 'K': // KING
			// The king has similar movement to the queen except it only moves one square in any direction, so no loops :)
			// Up
			if (ind + mp1 < totalSquareNum) {
				scope.push_back(ind + mp1);
			}
			// Down
			if (ind + mp2 >= 0) {
				scope.push_back(ind + mp2);
			}
			// Right
			if ((ind + 1) % up != 0) {
				scope.push_back(ind + mp3);
			}
			// Left
			if ((ind + 1) % up != 1) {
				scope.push_back(ind + mp4);
			}
			// North-East Diagonal
			if ((ind + mp5 < totalSquareNum) && ((ind + 1) % up != 0)) {
				scope.push_back(ind + mp5);
			}
			// North-West Diagonal
			if ((ind + mp6 < totalSquareNum) && ((ind + 1) % up != 1)) {
				scope.push_back(ind + mp6);
			}
			// South-East Diagonal
			if ((ind + mp7 >= 0) && ((ind + 1) % up != 0)) {
				scope.push_back(ind + mp7);
			}
			// South-West Diagonal
			if ((ind + mp8 >= 0) && ((ind + 1) % up != 1)) {
				scope.push_back(ind + mp8);
			}
			break;
		default:
			scope.clear();
		}
	}

	char getColour()
	{
		return pieceColour;
	}

	// Set new piece position and update scope 
	void setPos(GLuint verticleDirection, GLuint horizontalDirection, char postionArray[][2])
	{
		postionArray[ind][0] = NULL;
		postionArray[ind][1] = NULL;
		
		ind = ind + verticleDirection * up + horizontalDirection * right;

		postionArray[ind][0] = pieceColour;
		postionArray[ind][1] = pieceType;

		scope.clear(); // Clear scope before adding new indices
		// Update scope
		switch (pieceType) {
		case 'P': // PAWN
			switch (pieceColour) {
			case 'w': // white
				// Up
				if (ind + mp1 < totalSquareNum) {
					scope.push_back(ind + mp1);
				}
				// North-East Diagonal
				if ((ind + mp5 < totalSquareNum) && ((ind + 1) % up != 0)) {
					scope.push_back(ind + mp5);
				}
				// North-West Diagonal
				if ((ind + mp6 < totalSquareNum) && ((ind + 1) % up != 1)) {
					scope.push_back(ind + mp6);
				}
				break;
			case 'b': // black
				// Down
				if (ind + mp2 >= 0) {
					scope.push_back(ind + mp2);
				}
				// South-East Diagonal
				if ((ind + mp7 >= 0) && ((ind + 1) % up != 0)) {
					scope.push_back(ind + mp7);
				}
				// South-West Diagonal
				if ((ind + mp8 >= 0) && ((ind + 1) % up != 1)) {
					scope.push_back(ind + mp8);
				}
				break;
			}
			break;
		case 'N': //KNIGHT
			// 2 Up 1 Right
			if ((ind + mp9 < totalSquareNum) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				scope.push_back(ind + mp9);
			}
			// 2 Up 1 Left
			if ((ind + mp10 < totalSquareNum) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				scope.push_back(ind + mp10);
			}
			// 2 Down 1 Right
			if ((ind + mp11 >= 0) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				scope.push_back(ind + mp11);
			}
			// 2 Down 1 Left
			if ((ind + mp12 >= 0) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				scope.push_back(ind + mp12);
			}
			// 1 Up 2 Right
			if ((ind + mp13 < totalSquareNum) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				scope.push_back(ind + mp13);
			}
			// 1 Up 2 Left
			if ((ind + mp14 < totalSquareNum) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				scope.push_back(ind + mp14);
			}
			// 1 Down 2 Right
			if ((ind + mp15 >= 0) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				scope.push_back(ind + mp15);
			}
			// 1 Down 2 Left
			if ((ind + mp16 >= 0) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				scope.push_back(ind + mp16);
			}
			break;
		case 'B': // BISHOP
			// North-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp5 < totalSquareNum) && ((ind + n * mp5) % up != 0)) {
					scope.push_back(ind + n * mp5);
				}
				else { break; }
			}
			// North-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp6 < totalSquareNum) && ((ind + 1 + n * mp6) % up != 0)) {
					scope.push_back(ind + n * mp6);
				}
				else { break; }
			}
			// South-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp7 >= 0) && ((ind + n * mp7) % up != 0)) {
					scope.push_back(ind + n * mp7);
				}
				else { break; }
			}
			// South-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp8 >= 0) && ((ind + 1 + n * mp8) % up != 0)) {
					scope.push_back(ind + n * mp8);
				}
				else { break; }
			}
			break;
		case 'R': // ROOK
			// Up
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp1 < totalSquareNum) {
					scope.push_back(ind + n * mp1);
				}
				else { break; }
			}
			// Down
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp2 >= 0) {
					scope.push_back(ind + n * mp2);
				}
				else { break; }
			}
			// Right
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 0) && ((ind + n * mp3) % up != 0)) {
					scope.push_back(ind + n * mp3);
				}
				else { break; }
			}
			// Left
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 1) && ((ind + 1 + n * mp4) % up != 0)) {
					scope.push_back(ind + n * mp4);
				}
				else { break; }
			}
			break;
		case 'Q': // QUEEN
			// Up
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp1 < totalSquareNum) {
					scope.push_back(ind + n * mp1);
				}
				else { break; }
			}
			// Down
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp2 >= 0) {
					scope.push_back(ind + n * mp2);
				}
				else { break; }
			}
			// Right
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 0) && ((ind + n * mp3) % up != 0)) {
					scope.push_back(ind + n * mp3);
				}
				else { break; }
			}
			// Left
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 1) && ((ind + 1 + n * mp4) % up != 0)) {
					scope.push_back(ind + n * mp4);
				}
				else { break; }
			}
			// North-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp5 < totalSquareNum) && ((ind + n * mp5) % up != 0)) {
					scope.push_back(ind + n * mp5);
				}
				else { break; }
			}
			// North-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp6 < totalSquareNum) && ((ind + 1 + n * mp6) % up != 0)) {
					scope.push_back(ind + n * mp6);
				}
				else { break; }
			}
			// South-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp7 >= 0) && ((ind + n * mp7) % up != 0)) {
					scope.push_back(ind + n * mp7);
				}
				else { break; }
			}
			// South-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp8 >= 0) && ((ind + 1 + n * mp8) % up != 0)) {
					scope.push_back(ind + n * mp8);
				}
				else { break; }
			}
			break;
		case 'K': // KING
			// The king has similar movement to the queen except it only moves one square in any direction, so no loops :)
			// Up
			if (ind + mp1 < totalSquareNum) {
				scope.push_back(ind + mp1);
			}
			// Down
			if (ind + mp2 >= 0) {
				scope.push_back(ind + mp2);
			}
			// Right
			if ((ind + 1) % up != 0) {
				scope.push_back(ind + mp3);
			}
			// Left
			if ((ind + 1) % up != 1) {
				scope.push_back(ind + mp4);
			}
			// North-East Diagonal
			if ((ind + mp5 < totalSquareNum) && ((ind + 1) % up != 0)) {
				scope.push_back(ind + mp5);
			}
			// North-West Diagonal
			if ((ind + mp6 < totalSquareNum) && ((ind + 1) % up != 1)) {
				scope.push_back(ind + mp6);
			}
			// South-East Diagonal
			if ((ind + mp7 >= 0) && ((ind + 1) % up != 0)) {
				scope.push_back(ind + mp7);
			}
			// South-West Diagonal
			if ((ind + mp8 >= 0) && ((ind + 1) % up != 1)) {
				scope.push_back(ind + mp8);
			}
			break;
		default:
			scope.clear();
		}
	}

	int getPos()
	{
		return ind;
	}

	std::vector<int> getScope()
	{
		return scope;
	}

	// Generate and return piece moveSet for given board state
	void setMoveSet(char postionArray[][2])
	{
		moveSet.clear(); // clear moveSet before adding new indices
		
		switch (pieceType) {
		case 'P': // PAWN
			switch (pieceColour) {
			case 'w': // white
				// Up
				if (ind + mp1 < totalSquareNum) {
					// if nothing in front of the pawn then it can move up
					if (postionArray[ind + mp1][1] == NULL) {
						moveSet.push_back(ind + mp1);
						
						// add another if here that deals with a pawn that has already moved
						if (postionArray[ind + 2*mp1][1] == NULL) {
							moveSet.push_back(ind + 2 * mp1);
						}
					}
				}
				// North-East Diagonal
				if ((ind + mp5 < totalSquareNum) && ((ind + 1) % up != 0)) {
					// if the right diagonal in front of the pawn is a piece of the opposite colour 
					// (or simply a different coloured piece if I add more colours to the game)
					// then the pawn can capture so it goes in moveSet
					if ((postionArray[ind + mp5][0] != pieceColour) && (postionArray[ind + mp5][0] != NULL)) {
						moveSet.push_back(ind + mp5);
					}
				}
				// North-West Diagonal
				if ((ind + mp6 < totalSquareNum) && ((ind + 1) % up != 1)) {
					// if the left diagonal in front of the pawn is a piece of the opposite colour 
					// (or simply a different coloured piece if I add more colours to the game)
					// then the pawn can capture so it goes in moveSet
					if ((postionArray[ind + mp6][0] != pieceColour) && (postionArray[ind + mp5][0] != NULL)) {
						moveSet.push_back(ind + mp6);
					}
				}
				break;
			case 'b': // black
				// Down
				if (ind + mp2 >= 0) {
					if (postionArray[ind + mp2][1] == NULL) {
						moveSet.push_back(ind + mp2);
						if (postionArray[ind + 2 * mp2][1] == NULL) {
							moveSet.push_back(ind + 2 * mp2);
						}
					}
				}
				// South-East Diagonal
				if ((ind + mp7 >= 0) && ((ind + 1) % up != 0)) {
					if ((postionArray[ind + mp7][0] != pieceColour) && (postionArray[ind + mp7][0] != NULL)) {
						moveSet.push_back(ind + mp7);
					}
				}
				// South-West Diagonal
				if ((ind + mp8 >= 0) && ((ind + 1) % up != 1)) {
					if ((postionArray[ind + mp8][0] != pieceColour) && (postionArray[ind + mp8][0] != NULL)) {
						moveSet.push_back(ind + mp8);
					}
				}
				break;
			}
			break;
		case 'N': //KNIGHT
			// 2 Up 1 Right
			if ((ind + mp9 < totalSquareNum) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				//  if there's no piece of the same colour on ind + mp9, then add ind + mp9 to moveSet
				if (postionArray[ind + mp9][0] != pieceColour) {
					moveSet.push_back(ind + mp9);
				}
			}
			// 2 Up 1 Left
			if ((ind + mp10 < totalSquareNum) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				if (postionArray[ind + mp10][0] != pieceColour) {
					moveSet.push_back(ind + mp10);
				}
			}
			// 2 Down 1 Right
			if ((ind + mp11 >= 0) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				if (postionArray[ind + mp11][0] != pieceColour) {
					moveSet.push_back(ind + mp11);
				}
			}
			// 2 Down 1 Left
			if ((ind + mp12 >= 0) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				if (postionArray[ind + mp12][0] != pieceColour) {
					moveSet.push_back(ind + mp12);
				}
			}
			// 1 Up 2 Right
			if ((ind + mp13 < totalSquareNum) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				if (postionArray[ind + mp13][0] != pieceColour) {
					moveSet.push_back(ind + mp13);
				}
			}
			// 1 Up 2 Left
			if ((ind + mp14 < totalSquareNum) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				if (postionArray[ind + mp14][0] != pieceColour) {
					moveSet.push_back(ind + mp14);
				}
			}
			// 1 Down 2 Right
			if ((ind + mp15 >= 0) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				if (postionArray[ind + mp15][0] != pieceColour) {
					moveSet.push_back(ind + mp15);
				}
			}
			// 1 Down 2 Left
			if ((ind + mp16 >= 0) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				if (postionArray[ind + mp16][0] != pieceColour) {
					moveSet.push_back(ind + mp16);
				}
			}
			break;
		case 'B': // BISHOP
			// North-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp5 < totalSquareNum) && ((ind + n * mp5) % up != 0)) {
					// if there's no piece of the same colour on ind + n*mp5, then add ind + n*mp5 to moveSet
					// if there is a piece blocking that square, then don't add any more squares (along this diagonal) to moveSet
					if (postionArray[ind + n * mp5][0] != pieceColour) {
						moveSet.push_back(ind + n * mp5);
						// if there was a piece of a different colour then after you've added that square to the moveSet 
						// stop adding squares along this diagonal
						if (postionArray[ind + n * mp5][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// North-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp6 < totalSquareNum) && ((ind + 1 + n * mp6) % up != 0)) {
					if (postionArray[ind + n * mp6][0] != pieceColour) {
						moveSet.push_back(ind + n * mp6);

						if (postionArray[ind + n * mp6][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// South-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp7 >= 0) && ((ind + n * mp7) % up != 0)) {
					if (postionArray[ind + n * mp7][0] != pieceColour) {
						moveSet.push_back(ind + n * mp7);

						if (postionArray[ind + n * mp7][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// South-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp8 >= 0) && ((ind + 1 + n * mp8) % up != 0)) {
					if (postionArray[ind + n * mp8][0] != pieceColour) {
						moveSet.push_back(ind + n * mp8);

						if (postionArray[ind + n * mp8][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			break;
		case 'R': // ROOK
			// Up
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp1 < totalSquareNum) {
					// if there's no piece of the same colour on ind + n*mp1, then add ind + n*mp1 to moveSet
					// if there is a piece blocking that square, then don't add any more squares (line) to moveSet
					if (postionArray[ind + n * mp1][0] != pieceColour) {
						moveSet.push_back(ind + n * mp1);

						if (postionArray[ind + n * mp1][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// Down
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp2 >= 0) {
					if (postionArray[ind + n * mp2][0] != pieceColour) {
						moveSet.push_back(ind + n * mp2);

						if (postionArray[ind + n * mp2][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// Right
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 0) && ((ind + n * mp3) % up != 0)) {
					if (postionArray[ind + n * mp3][0] != pieceColour) {
						moveSet.push_back(ind + n * mp3);

						if (postionArray[ind + n * mp3][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// Left
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 1) && ((ind + 1 + n * mp4) % up != 0)) {
					if (postionArray[ind + n * mp4][0] != pieceColour) {
						moveSet.push_back(ind + n * mp4);

						if (postionArray[ind + n * mp4][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			break;
		case 'Q': // QUEEN
			// Up
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp1 < totalSquareNum) {
					// if there's no piece of the same colour on ind + n*mp1, then add ind + n*mp1 to moveSet
					// if there is a piece blocking that square, then don't add any more squares (line) to moveSet
					if (postionArray[ind + n * mp1][0] != pieceColour) {
						moveSet.push_back(ind + n * mp1);

						if (postionArray[ind + n * mp1][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// Down
			for (int n = 1; n < 8; n++) {
				if (ind + n * mp2 >= 0) {
					if (postionArray[ind + n * mp2][0] != pieceColour) {
						moveSet.push_back(ind + n * mp2);

						if (postionArray[ind + n * mp2][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// Right
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 0) && ((ind + n * mp3) % up != 0)) {
					if (postionArray[ind + n * mp3][0] != pieceColour) {
						moveSet.push_back(ind + n * mp3);

						if (postionArray[ind + n * mp3][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// Left
			for (int n = 1; n < 8; n++) {
				if (((ind + 1) % up != 1) && ((ind + 1 + n * mp4) % up != 0)) {
					if (postionArray[ind + n * mp4][0] != pieceColour) {
						moveSet.push_back(ind + n * mp4);

						if (postionArray[ind + n * mp4][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// North-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp5 < totalSquareNum) && ((ind + n * mp5) % up != 0)) {
					// if there's no piece of the same colour on ind + n*mp5, then add ind + n*mp5 to moveSet
					// if there is a piece blocking that square, then don't add any more squares (along this diagonal) to moveSet
					if (postionArray[ind + n * mp5][0] != pieceColour) {
						moveSet.push_back(ind + n * mp5);

						if (postionArray[ind + n * mp5][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// North-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp6 < totalSquareNum) && ((ind + 1 + n * mp6) % up != 0)) {
					if (postionArray[ind + n * mp6][0] != pieceColour) {
						moveSet.push_back(ind + n * mp6);

						if (postionArray[ind + n * mp6][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// South-East Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp7 >= 0) && ((ind + n * mp7) % up != 0)) {
					if (postionArray[ind + n * mp7][0] != pieceColour) {
						moveSet.push_back(ind + n * mp7);

						if (postionArray[ind + n * mp7][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			// South-West Diagonal
			for (int n = 1; n < 8; n++) {
				if ((ind + n * mp8 >= 0) && ((ind + 1 + n * mp8) % up != 0)) {
					if (postionArray[ind + n * mp8][0] != pieceColour) {
						moveSet.push_back(ind + n * mp8);

						if (postionArray[ind + n * mp8][1] != NULL) {
							break;
						}
					}
					else { break; }
				}
				else { break; }
			}
			break;
		case 'K': // KING
			// The king has similar movement to the queen except it only moves one square in any direction, so no loops :)
			// Up
			if (ind + mp1 < totalSquareNum) {
				if (postionArray[ind + mp1][0] != pieceColour) {
					moveSet.push_back(ind + mp1);
				}
			}
			// Down
			if (ind + mp2 >= 0) {
				if (postionArray[ind + mp2][0] != pieceColour) {
					moveSet.push_back(ind + mp2);
				}
			}
			// Right
			if ((ind + 1) % up != 0) {
				if (postionArray[ind + mp3][0] != pieceColour) {
					moveSet.push_back(ind + mp3);
				}
			}
			// Left
			if ((ind + 1) % up != 1) {
				if (postionArray[ind + mp4][0] != pieceColour) {
					moveSet.push_back(ind + mp4);
				}
			}
			// North-East Diagonal
			if ((ind + mp5 < totalSquareNum) && ((ind + 1) % up != 0)) {
				if (postionArray[ind + mp5][0] != pieceColour) {
					moveSet.push_back(ind + mp5);
				}
			}
			// North-West Diagonal
			if ((ind + mp6 < totalSquareNum) && ((ind + 1) % up != 1)) {
				if (postionArray[ind + mp6][0] != pieceColour) {
					moveSet.push_back(ind + mp6);
				}
			}
			// South-East Diagonal
			if ((ind + mp7 >= 0) && ((ind + 1) % up != 0)) {
				if (postionArray[ind + mp7][0] != pieceColour) {
					moveSet.push_back(ind + mp7);
				}
			}
			// South-West Diagonal
			if ((ind + mp8 >= 0) && ((ind + 1) % up != 1)) {
				if (postionArray[ind + mp8][0] != pieceColour) {
					moveSet.push_back(ind + mp8);
				}
			}
			break;
		default:
			moveSet.clear();
		}
	}

	std::vector<int> getMoveSet()
	{
		return moveSet;
	}

};

// LINKING FUNCTION (to help with VAO bindings)
void linkingFunction(VAO VAO, VBO VBO, EBO EBO, GLuint vertStride, GLuint numCoords, GLuint numColors, GLuint numTex)
{
	// Links VBO attributes such as coordinates and colours and textures to VAO
	VAO.LinkAttrib(VBO, 0, numCoords, GL_FLOAT, vertStride * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, numColors, GL_FLOAT, vertStride * sizeof(float), (void*)(numCoords * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, numTex, GL_FLOAT, vertStride * sizeof(float), (void*)((numCoords + numColors) * sizeof(float)));

	// Unbind all to prevent accidentally modyfying them 
	VAO.Unbind();
	VBO.Unbind();
	EBO.Delete();
}


int main()
{
	// SOME CONSTANT VARIABLES
	#pragma region
	int const windowWidth = 800;
	int const windowHeight = 800;
	int const boardHeight = 8;
	int const boardWidth = 8;
	int const bufferAttribNum = 8;
	#pragma endregion
	
	
	// GLFW SETUP
	#pragma region
	// Initialise GLFW
	glfwInit();
	// Tell GLFW what version of OpenGL we are using (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// which means we're only using modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#pragma endregion


	// CHESS BOARD VERTICES AND INDICES
	#pragma region
	// Sets the board vertices
	GLfloat vertices[bufferAttribNum * (boardHeight + 1) * (boardWidth + 1)]{};
	for (int i = 0; i < (boardHeight + 1); ++i) { // columns
		for (int j = 0; j < (boardWidth + 1); ++j) { // rows
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j))] = 0.1f * float(j - boardWidth / 2); // xPos
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 1] = 0.1f * float(i - boardHeight / 2); // yPos
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 2] = 0.0f;  // zPos
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 3] = 1.0f * float((i + j + 1) % 2);  // R
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 4] = 1.0f * float((i + j + 1) % 2) + 0.894f * (1 - float((i + j + 1) % 2));  // G
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 5] = 1.0f * float((i + j + 1) % 2) + 0.709f * (1 - float((i + j + 1) % 2));  // B
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 6] = float(j);  // Texture xCoord
			vertices[(bufferAttribNum * ((boardWidth + 1) * i + j)) + 7] = float(i);  // Texture yCoord
		}
	}


	// Sets the triangle indices. 2 triangles per square. Goes left to right, bottom to top.
	GLuint boardIndices[6 * boardHeight * boardWidth]{};
	GLuint squareIndices[boardHeight * boardWidth][6]{};
	int n = 0;
	for (int m = 0; m < (boardHeight * boardWidth); ++m)
	{
		if (((m + n + 1) % (boardWidth + 1)) == 0) // if m represents an "edge" vertex
		{
			n++;
		}

		// boardIndices are used to display the board
		boardIndices[6 * m] = m + n + boardWidth + 2;
		boardIndices[6 * m + 1] = m + n + boardWidth + 1;
		boardIndices[6 * m + 2] = m + n;
		boardIndices[6 * m + 3] = m + n + boardWidth + 2;
		boardIndices[6 * m + 4] = m + n + 1;
		boardIndices[6 * m + 5] = m + n;

		// squareIndices are used to determine the placement of pieces
		squareIndices[m][0] = m + n;
		squareIndices[m][1] = m + n + boardWidth + 2;
		squareIndices[m][2] = m + n + boardWidth + 1;
		squareIndices[m][3] = m + n;
		squareIndices[m][4] = m + n + boardWidth + 2;
		squareIndices[m][5] = m + n + 1;
	};

	// TEST array of chars indicating what piece type/colour is on each square
	// the purpose of this is so we don't have to loop through pieceList to 
	// check what piece (if any) is on a particular square
	char piecePositions[boardHeight * boardWidth][2];
	for (int z = 1; z < (boardHeight * boardWidth); z++) {
		piecePositions[z][0] = NULL;
		piecePositions[z][1] = NULL;
	}
	#pragma endregion


	// INITIALISE PIECE OBJECTS
	#pragma region

	// Vector of chesspieces, makes accessing the pieces much easier
	std::vector<chessPiece> pieceList{};

	// White Rook1
	chessPiece whiteRook1(0, boardWidth, boardHeight, 'R', 'w', pieceList, piecePositions);
	// White Knight1
	chessPiece whiteKnight1(1, boardWidth, boardHeight, 'N', 'w', pieceList, piecePositions);
	// White Bishop1
	chessPiece whiteBishop1(2, boardWidth, boardHeight, 'B', 'w', pieceList, piecePositions);
	// White Queen
	chessPiece whiteQueen(3, boardWidth, boardHeight, 'Q', 'w', pieceList, piecePositions);
	// White King
	chessPiece whiteKing(4, boardWidth, boardHeight, 'K', 'w', pieceList, piecePositions);
	// White Bishop2
	chessPiece whiteBishop2(5, boardWidth, boardHeight, 'B', 'w', pieceList, piecePositions);
	// White Knight2
	chessPiece whiteKnight2(6, boardWidth, boardHeight, 'N', 'w', pieceList, piecePositions);
	// White Rook2
	chessPiece whiteRook2(7, boardWidth, boardHeight, 'R', 'w', pieceList, piecePositions);
	// White Pawn1
	chessPiece whitePawn1(8, boardWidth, boardHeight, 'P', 'w', pieceList, piecePositions);
	// White Pawn2
	chessPiece whitePawn2(9, boardWidth, boardHeight, 'P', 'w', pieceList, piecePositions);
	// White Pawn3
	chessPiece whitePawn3(10, boardWidth, boardHeight, 'P', 'w', pieceList, piecePositions);
	// White Pawn4
	chessPiece whitePawn4(11, boardWidth, boardHeight, 'P', 'w', pieceList, piecePositions);
	// White Pawn5
	chessPiece whitePawn5(12, boardWidth, boardHeight, 'P', 'w', pieceList, piecePositions);
	// White Pawn6
	chessPiece whitePawn6(13, boardWidth, boardHeight, 'P', 'w', pieceList, piecePositions);
	// White Pawn7
	chessPiece whitePawn7(14, boardWidth, boardHeight, 'P', 'w', pieceList, piecePositions);
	// White Pawn8
	chessPiece whitePawn8(15, boardWidth, boardHeight, 'P', 'w', pieceList, piecePositions);
	// Black Pawn1
	chessPiece blackPawn1(48, boardWidth, boardHeight, 'P', 'b', pieceList, piecePositions);
	// Black Pawn2
	chessPiece blackPawn2(49, boardWidth, boardHeight, 'P', 'b', pieceList, piecePositions);
	// Black Pawn3
	chessPiece blackPawn3(50, boardWidth, boardHeight, 'P', 'b', pieceList, piecePositions);
	// Black Pawn4
	chessPiece blackPawn4(51, boardWidth, boardHeight, 'P', 'b', pieceList, piecePositions);
	// Black Pawn5
	chessPiece blackPawn5(52, boardWidth, boardHeight, 'P', 'b', pieceList, piecePositions);
	// Black Pawn6
	chessPiece blackPawn6(53, boardWidth, boardHeight, 'P', 'b', pieceList, piecePositions);
	// Black Pawn7
	chessPiece blackPawn7(54, boardWidth, boardHeight, 'P', 'b', pieceList, piecePositions);
	// Black Pawn8
	chessPiece blackPawn8(55, boardWidth, boardHeight, 'P', 'b', pieceList, piecePositions);
	// Black Rook1
	chessPiece blackRook1(56, boardWidth, boardHeight, 'R', 'b', pieceList, piecePositions);
	// Black Knight1
	chessPiece blackKnight1(57, boardWidth, boardHeight, 'N', 'b', pieceList, piecePositions);
	// Black Bishop1
	chessPiece blackBishop1(58, boardWidth, boardHeight, 'B', 'b', pieceList, piecePositions);
	// Black Queen
	chessPiece blackQueen(59, boardWidth, boardHeight, 'Q', 'b', pieceList, piecePositions);
	// Black King
	chessPiece blackKing(60, boardWidth, boardHeight, 'K', 'b', pieceList, piecePositions);
	// Black Bishop2
	chessPiece blackBishop2(61, boardWidth, boardHeight, 'B', 'b', pieceList, piecePositions);
	// Black Knight2
	chessPiece blackKnight2(62, boardWidth, boardHeight, 'N', 'b', pieceList, piecePositions);
	// Black Rook2
	chessPiece blackRook2(63, boardWidth, boardHeight, 'R', 'b', pieceList, piecePositions);

	// Fill vector with the pieces we've initialised
	pieceList = { whiteRook1, whiteKnight1, whiteBishop1, whiteQueen, whiteKing, whiteBishop2, whiteKnight2, whiteRook2, whitePawn1, whitePawn2, whitePawn3, whitePawn4, whitePawn5, whitePawn6, whitePawn7, whitePawn8, blackPawn1,blackPawn2, blackPawn3, blackPawn4, blackPawn5, blackPawn6, blackPawn7, blackPawn8, blackRook1, blackKnight1, blackBishop1, blackQueen, blackKing, blackBishop2, blackKnight2, blackRook2 };
	#pragma endregion


	// CREATE WINDOW
	#pragma region
	// creates the window object
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Chess", NULL, NULL);
	// Error checks if something went wrong opening the window
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	};
	// brings the window object into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the window
	glViewport(0, 0, windowWidth, windowHeight);
	#pragma endregion


	// GENERATE SHADERS
	#pragma region
	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
	// Generates Shader object using shaders basic.vert and basic.frag (this one has no textures)
	Shader shaderProgram2("Resource Files/Shaders/basic.vert", "Resource Files/Shaders/basic.frag");
	#pragma endregion

	// CHESS BOARD AND PIECES VAO, VBO, EBO BINDING
	#pragma region
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generate Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(boardIndices, sizeof(boardIndices));
	// Links VBO attributes such as coordinates and colours and textures to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, bufferAttribNum * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, bufferAttribNum * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, bufferAttribNum * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modyfying them 
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Delete();

	// NOTE: The board and the pieces can use the same VBO because they all use the same vertices


	// WHITE ROOK1 BINDING
	VAO VAO2;
	VAO2.Bind();
	//EBO EBO2(squareIndices[whiteRook1.getPos()], sizeof(squareIndices[whiteRook1.getPos()]));
	GLuint* ptr = &boardIndices[6*whiteRook1.getPos()]; // these line are to demonstrate that I don't need squareIndices, I can always use boardIndices instead
	GLuint arr[6] = {*ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5)}; // I'm not sure if I should get rid of squareIndices as it more convenient
	EBO EBO2(arr, sizeof(arr)); // I'll have to decide later
	linkingFunction(VAO2, VBO1, EBO2, bufferAttribNum, 3, 3, 2);

	// WHITE KNIGHT1 BINDING
	VAO VAO3;
	VAO3.Bind();
	EBO EBO3(squareIndices[whiteKnight1.getPos()], sizeof(squareIndices[whiteKnight1.getPos()]));
	linkingFunction(VAO3, VBO1, EBO3, bufferAttribNum, 3, 3, 2);

	// WHITE BISHOP1 BINDING
	VAO VAO4;
	VAO4.Bind();
	EBO EBO4(squareIndices[whiteBishop1.getPos()], sizeof(squareIndices[whiteBishop1.getPos()]));
	linkingFunction(VAO4, VBO1, EBO4, bufferAttribNum, 3, 3, 2);

	// WHITE QUEEN BINDING
	VAO VAO5;
	VAO5.Bind();
	EBO EBO5(squareIndices[whiteQueen.getPos()], sizeof(squareIndices[whiteQueen.getPos()]));
	linkingFunction(VAO5, VBO1, EBO5, bufferAttribNum, 3, 3, 2);

	// WHITE KING BINDING
	VAO VAO6;
	VAO6.Bind();
	EBO EBO6(squareIndices[whiteKing.getPos()], sizeof(squareIndices[whiteKing.getPos()]));
	linkingFunction(VAO6, VBO1, EBO6, bufferAttribNum, 3, 3, 2);

	// WHITE BISHOP2 BINDING
	VAO VAO7;
	VAO7.Bind();
	EBO EBO7(squareIndices[whiteBishop2.getPos()], sizeof(squareIndices[whiteBishop2.getPos()]));
	linkingFunction(VAO7, VBO1, EBO7, bufferAttribNum, 3, 3, 2);

	// WHITE KNIGHT2 BINDING
	VAO VAO8;
	VAO8.Bind();
	EBO EBO8(squareIndices[whiteKnight2.getPos()], sizeof(squareIndices[whiteKnight2.getPos()]));
	linkingFunction(VAO8, VBO1, EBO8, bufferAttribNum, 3, 3, 2);

	// WHITE ROOK2 BINDING
	VAO VAO9;
	VAO9.Bind();
	EBO EBO9(squareIndices[whiteRook2.getPos()], sizeof(squareIndices[whiteRook2.getPos()]));
	linkingFunction(VAO9, VBO1, EBO9, bufferAttribNum, 3, 3, 2);

	// WHITE PAWN1 BINDING
	VAO VAO10;
	VAO10.Bind();
	EBO EBO10(squareIndices[whitePawn1.getPos()], sizeof(squareIndices[whitePawn1.getPos()]));
	linkingFunction(VAO10, VBO1, EBO10, bufferAttribNum, 3, 3, 2);

	// WHITE PAWN2 BINDING
	VAO VAO11;
	VAO11.Bind();
	EBO EBO11(squareIndices[whitePawn2.getPos()], sizeof(squareIndices[whitePawn2.getPos()]));
	linkingFunction(VAO11, VBO1, EBO11, bufferAttribNum, 3, 3, 2);

	// WHITE PAWN3 BINDING
	VAO VAO12;
	VAO12.Bind();
	EBO EBO12(squareIndices[whitePawn3.getPos()], sizeof(squareIndices[whitePawn3.getPos()]));
	linkingFunction(VAO12, VBO1, EBO12, bufferAttribNum, 3, 3, 2);

	// WHITE PAWN4 BINDING
	VAO VAO13;
	VAO13.Bind();
	EBO EBO13(squareIndices[whitePawn4.getPos()], sizeof(squareIndices[whitePawn4.getPos()]));
	linkingFunction(VAO13, VBO1, EBO13, bufferAttribNum, 3, 3, 2);

	// WHITE PAWN5 BINDING
	VAO VAO14;
	VAO14.Bind();
	EBO EBO14(squareIndices[whitePawn5.getPos()], sizeof(squareIndices[whitePawn5.getPos()]));
	linkingFunction(VAO14, VBO1, EBO14, bufferAttribNum, 3, 3, 2);

	// WHITE PAWN6 BINDING
	VAO VAO15;
	VAO15.Bind();
	EBO EBO15(squareIndices[whitePawn6.getPos()], sizeof(squareIndices[whitePawn6.getPos()]));
	linkingFunction(VAO15, VBO1, EBO15, bufferAttribNum, 3, 3, 2);

	// WHITE PAWN7 BINDING
	VAO VAO16;
	VAO16.Bind();
	EBO EBO16(squareIndices[whitePawn7.getPos()], sizeof(squareIndices[whitePawn7.getPos()]));
	linkingFunction(VAO16, VBO1, EBO16, bufferAttribNum, 3, 3, 2);
	// WHITE PAWN8 BINDING
	VAO VAO17;
	VAO17.Bind();
	EBO EBO17(squareIndices[whitePawn8.getPos()], sizeof(squareIndices[whitePawn8.getPos()]));
	linkingFunction(VAO17, VBO1, EBO17, bufferAttribNum, 3, 3, 2);

	// BLACK PAWN1 BINDING
	VAO VAO18;
	VAO18.Bind();
	EBO EBO18(squareIndices[blackPawn1.getPos()], sizeof(squareIndices[blackPawn1.getPos()]));
	linkingFunction(VAO18, VBO1, EBO18, bufferAttribNum, 3, 3, 2);

	// BLACK PAWN2 BINDING
	VAO VAO19;
	VAO19.Bind();
	EBO EBO19(squareIndices[blackPawn2.getPos()], sizeof(squareIndices[blackPawn2.getPos()]));
	linkingFunction(VAO19, VBO1, EBO19, bufferAttribNum, 3, 3, 2);

	// BLACK PAWN3 BINDING
	VAO VAO20;
	VAO20.Bind();
	EBO EBO20(squareIndices[blackPawn3.getPos()], sizeof(squareIndices[blackPawn3.getPos()]));
	linkingFunction(VAO20, VBO1, EBO20, bufferAttribNum, 3, 3, 2);

	// BLACK PAWN4 BINDING
	VAO VAO21;
	VAO21.Bind();
	EBO EBO21(squareIndices[blackPawn4.getPos()], sizeof(squareIndices[blackPawn4.getPos()]));
	linkingFunction(VAO21, VBO1, EBO21, bufferAttribNum, 3, 3, 2);

	// BLACK PAWN5 BINDING
	VAO VAO22;
	VAO22.Bind();
	EBO EBO22(squareIndices[blackPawn5.getPos()], sizeof(squareIndices[blackPawn5.getPos()]));
	linkingFunction(VAO22, VBO1, EBO22, bufferAttribNum, 3, 3, 2);

	// BLACK PAWN6 BINDING
	VAO VAO23;
	VAO23.Bind();
	EBO EBO23(squareIndices[blackPawn6.getPos()], sizeof(squareIndices[blackPawn6.getPos()]));
	linkingFunction(VAO23, VBO1, EBO23, bufferAttribNum, 3, 3, 2);

	// BLACK PAWN7 BINDING
	VAO VAO24;
	VAO24.Bind();
	EBO EBO24(squareIndices[blackPawn7.getPos()], sizeof(squareIndices[blackPawn7.getPos()]));
	linkingFunction(VAO24, VBO1, EBO24, bufferAttribNum, 3, 3, 2);

	// BLACK PAWN8 BINDING
	VAO VAO25;
	VAO25.Bind();
	EBO EBO25(squareIndices[blackPawn8.getPos()], sizeof(squareIndices[blackPawn8.getPos()]));
	linkingFunction(VAO25, VBO1, EBO25, bufferAttribNum, 3, 3, 2);

	// BLACK ROOK1 BINDING
	VAO VAO26;
	VAO26.Bind();
	EBO EBO26(squareIndices[blackRook1.getPos()], sizeof(squareIndices[blackRook1.getPos()]));
	linkingFunction(VAO26, VBO1, EBO26, bufferAttribNum, 3, 3, 2);

	// BLACK KNIGHT1 BINDING
	VAO VAO27;
	VAO27.Bind();
	EBO EBO27(squareIndices[blackKnight1.getPos()], sizeof(squareIndices[blackKnight1.getPos()]));
	linkingFunction(VAO27, VBO1, EBO27, bufferAttribNum, 3, 3, 2);

	// BLACK BISHOP1 BINDING
	VAO VAO28;
	VAO28.Bind();
	EBO EBO28(squareIndices[blackBishop1.getPos()], sizeof(squareIndices[blackBishop1.getPos()]));
	linkingFunction(VAO28, VBO1, EBO28, bufferAttribNum, 3, 3, 2);

	// BLACK QUEEN BINDING
	VAO VAO29;
	VAO29.Bind();
	EBO EBO29(squareIndices[blackQueen.getPos()], sizeof(squareIndices[blackQueen.getPos()]));
	linkingFunction(VAO29, VBO1, EBO29, bufferAttribNum, 3, 3, 2);

	// BLACK KING BINDING
	VAO VAO30;
	VAO30.Bind();
	EBO EBO30(squareIndices[blackKing.getPos()], sizeof(squareIndices[blackKing.getPos()]));
	linkingFunction(VAO30, VBO1, EBO30, bufferAttribNum, 3, 3, 2);

	// BLACK BISHOP2 BINDING
	VAO VAO31;
	VAO31.Bind();
	EBO EBO31(squareIndices[blackBishop2.getPos()], sizeof(squareIndices[blackBishop2.getPos()]));
	linkingFunction(VAO31, VBO1, EBO31, bufferAttribNum, 3, 3, 2);

	// BLACK KNIGHT2 BINDING
	VAO VAO32;
	VAO32.Bind();
	EBO EBO32(squareIndices[blackKnight2.getPos()], sizeof(squareIndices[blackKnight2.getPos()]));
	linkingFunction(VAO32, VBO1, EBO32, bufferAttribNum, 3, 3, 2);

	// BLACK ROOK2 BINDING
	VAO VAO33;
	VAO33.Bind();
	EBO EBO33(squareIndices[blackRook2.getPos()], sizeof(squareIndices[blackRook2.getPos()]));
	linkingFunction(VAO33, VBO1, EBO33, bufferAttribNum, 3, 3, 2);

	VBO1.Unbind();
	VAO vaoArray[33]{ VAO1, VAO2, VAO3, VAO4, VAO5, VAO6, VAO7, VAO8, VAO9, VAO10, VAO11, VAO12, VAO13, VAO14, VAO15, VAO16, VAO17, VAO18, VAO19, VAO20, VAO21, VAO22, VAO23, VAO24, VAO25, VAO26, VAO27, VAO28, VAO29, VAO30, VAO31, VAO32, VAO33 };
	#pragma endregion
	

	// TEXTURES
	#pragma region
	Texture whiteKingTex("Resource Files/Textures/whiteKing.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	whiteKingTex.TexUnit(shaderProgram, "tex0", 1);

	Texture blackKingTex("Resource Files/Textures/blackKing.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	blackKingTex.TexUnit(shaderProgram, "tex0", 1);

	Texture whiteQueenTex("Resource Files/Textures/whiteQueen.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	whiteQueenTex.TexUnit(shaderProgram, "tex0", 1);

	Texture blackQueenTex("Resource Files/Textures/blackQueen.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	blackQueenTex.TexUnit(shaderProgram, "tex0", 1);

	Texture whiteRookTex("Resource Files/Textures/whiteRook.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	whiteRookTex.TexUnit(shaderProgram, "tex0", 1);
	
	Texture blackRookTex("Resource Files/Textures/blackRook.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	blackRookTex.TexUnit(shaderProgram, "tex0", 1);

	Texture whiteBishopTex("Resource Files/Textures/whiteBishop.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	whiteBishopTex.TexUnit(shaderProgram, "tex0", 1);

	Texture blackBishopTex("Resource Files/Textures/blackBishop.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	blackBishopTex.TexUnit(shaderProgram, "tex0", 1);

	Texture whiteKnightTex("Resource Files/Textures/whiteKnight.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	whiteKnightTex.TexUnit(shaderProgram, "tex0", 1);

	Texture blackKnightTex("Resource Files/Textures/blackKnight.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	blackKnightTex.TexUnit(shaderProgram, "tex0", 1);

	Texture whitePawnTex("Resource Files/Textures/whitePawn.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	whitePawnTex.TexUnit(shaderProgram, "tex0", 1);

	Texture blackPawnTex("Resource Files/Textures/blackPawn.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	blackPawnTex.TexUnit(shaderProgram, "tex0", 1);


	Texture startGameTex("Resource Files/Textures/StartGame.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	startGameTex.TexUnit(shaderProgram, "tex0", 1);
	#pragma endregion

	

	// START MENU VERTICES AND INDICES
	#pragma region
	
	// START GAME BUTTON VERTICES
	float startButtonVertices[32]{};

	// BOTTOM LEFT CORNER
	startButtonVertices[0] = -0.2f; // xPos
	startButtonVertices[1] =  0.0f; // yPos
	startButtonVertices[2] =  0.0f; // zPos
	startButtonVertices[3] =  0.3f; // R
	startButtonVertices[4] =  0.2f; // G
	startButtonVertices[5] =  0.8f; // B
	startButtonVertices[6] = 0.0f; // Texture xCoord
	startButtonVertices[7] = 0.0f; // Texture yCoord

	// TOP LEFT CORNER
	startButtonVertices[8] = -0.2f; // xPos
	startButtonVertices[9] =  0.2f; // yPos
	startButtonVertices[10] = 0.0f; // zPos
	startButtonVertices[11] = 0.3f; // R
	startButtonVertices[12] = 0.2f; // G
	startButtonVertices[13] = 0.8f; // B
	startButtonVertices[14] = 0.0f; // Texture xCoord
	startButtonVertices[15] = 1.0f; // Texture yCoord

	// TOP RIGHT CORNER
	startButtonVertices[16] =  0.2f; // xPos
	startButtonVertices[17] =  0.2f; // yPos
	startButtonVertices[18] = 0.0f; // zPos
	startButtonVertices[19] = 0.3f; // R
	startButtonVertices[20] = 0.2f; // G
	startButtonVertices[21] = 0.8f; // B
	startButtonVertices[22] = 1.0f; // Texture xCoord
	startButtonVertices[23] = 1.0f; // Texture yCoord

	// BOTTOM RIGHT CORNER
	startButtonVertices[24] =  0.2f; // xPos
	startButtonVertices[25] =  0.0f; // yPos
	startButtonVertices[26] = 0.0f; // zPos
	startButtonVertices[27] = 0.3f; // R
	startButtonVertices[28] = 0.2f; // G
	startButtonVertices[29] = 0.8f; // B
	startButtonVertices[30] = 1.0f; // Texture xCoord
	startButtonVertices[31] = 0.0f; // Texture yCoord

	// START GAME BUTTON INDICES (2 triangles, 3 vertices each)
	GLuint startButtonIndices[2 * 3] = {0,2,1,0,2,3};


	// Linking
	VAO VAOStartButton;
	VAOStartButton.Bind();
	VBO VBOStartButton(startButtonVertices, sizeof(startButtonVertices));
	EBO EBOStartButton(startButtonIndices, sizeof(startButtonIndices));
	linkingFunction(VAOStartButton, VBOStartButton, EBOStartButton, bufferAttribNum, 3, 3, 2);
	#pragma endregion
	
	bool gameStart = FALSE;
	
	// START MENU
	while (gameStart == FALSE) {
		
		// HANDLE MOUSE CLICKS
		#pragma region
		if (GetAsyncKeyState(VK_LBUTTON) & 1) {
				//Gets cursor position (converts from 800x800 scale to inverted -1x1 scale)
				double xcursorpos;
				double ycursorpos;
				glfwGetCursorPos(window, &xcursorpos, &ycursorpos);
				float x = (2 * float(xcursorpos) - windowWidth) / windowWidth;
				float y = (windowHeight - 2 * float(ycursorpos)) / windowHeight;

				if ((x > startButtonVertices[0]) && (x < startButtonVertices[16])) { // if the mouse xPos is within the x value of the bottom left corner and the top right corner
					if ((y > startButtonVertices[1]) && (y < startButtonVertices[17])) { // if the mouse yPos is within the y value of the bottom left corner and the top right corner
						gameStart = TRUE;
					}
				}
		}
		#pragma endregion
		
		
		// DRAW THE HOME PAGE
		#pragma region
		// Specify the colour of the background
		glClearColor(0.0f, 0.6f, 0.5f, 1.0f);
		// clean the back buffer and assign the new colour to it
		glClear(GL_COLOR_BUFFER_BIT);

		// DRAW START BUTTON
		// Tell OpenGL which shader program we want to use
		shaderProgram.Activate();
		// Binds texture so that it appears in rendering
		//blackKingTex.Bind();
		startGameTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAOStartButton.Bind();
		//Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		#pragma endregion

		// Take care of all GLFW events		
		glfwPollEvents();
	}



	bool pieceClicked = FALSE;
	int clickedPiece;
	char players[] = { 'w', 'b' };
	int playerTurn = 0;

	// MAIN WHILE LOOP (glfwPollEvents() monitors the window for any events. If the window is closed, the code moves on)
	while (!glfwWindowShouldClose(window))
	{
		
		// HANDLE MOUSE CLICKS
		#pragma region
		if (GetAsyncKeyState(VK_LBUTTON) & 1) {
			// If a piece has already been clicked, pick a square for it to go to
			if (pieceClicked == TRUE) {
					
					pieceClicked = FALSE;
					

					// Remove moveSet highlights
					#pragma region
					std::vector<int> pieceMoveSet = pieceList[clickedPiece].getMoveSet();
					for (int e = 0; e < pieceMoveSet.size(); e++) {
						vertices[bufferAttribNum * boardIndices[6 * pieceMoveSet[e] + 2] + 3] = 1.0f * float((boardIndices[6 * pieceMoveSet[e] + 2] + 1) % 2);  // R
						vertices[bufferAttribNum * boardIndices[6 * pieceMoveSet[e] + 2] + 4] = 1.0f * float((boardIndices[6 * pieceMoveSet[e] + 2] + 1) % 2) + 0.894f * (1 - float((boardIndices[6 * pieceMoveSet[e] + 2] + 1) % 2));  // G
						vertices[bufferAttribNum * boardIndices[6 * pieceMoveSet[e] + 2] + 5] = 1.0f * float((boardIndices[6 * pieceMoveSet[e] + 2] + 1) % 2) + 0.709f * (1 - float((boardIndices[6 * pieceMoveSet[e] + 2] + 1) % 2));  // B
					}

					VAO1.Bind();
					VBO1.Bind();
					EBO EBO1(boardIndices, sizeof(boardIndices));
					linkingFunction(VAO1, VBO1, EBO1, bufferAttribNum, 3, 3, 2);
					#pragma endregion


					// Search squares indices or board indices for the square you clicked on and move the piece there
					// Gets cursor position (converts from 800x800 scale to inverted -1x1 scale)
					double xcursorpos;
					double ycursorpos;
					glfwGetCursorPos(window, &xcursorpos, &ycursorpos);
					float x = (2 * float(xcursorpos) - windowWidth) / windowWidth;
					float y = (windowHeight - 2 * float(ycursorpos)) / windowHeight;

					for (int j = 0; j < (boardHeight * boardWidth); j++)
					{
						int ind3 = squareIndices[j][0]; // each square has 6 indices, the first one corresponds to the bottom left corner of the square
						int ind4 = squareIndices[j][1]; // top right corner

						if ((x > vertices[bufferAttribNum * ind3]) && ((x < vertices[bufferAttribNum * ind4])))				// if we've 
						{																									// click on 
							if ((y > vertices[bufferAttribNum * ind3 + 1]) && ((y < vertices[bufferAttribNum * ind4 + 1])))	// a square
							{					
								for (int q = 0; q < pieceMoveSet.size(); q++) {
									if (j == pieceMoveSet[q]) { // if j is a square withing the piece's allowed moves

										// how many indices to move the piece up
										int up = (j - pieceList[clickedPiece].getPos() + pieceList[clickedPiece].getPos() % (boardWidth)-j % (boardWidth)) / boardWidth;
										// how many indices to move the piece to the right
										int right = (j - up * boardWidth) - pieceList[clickedPiece].getPos();

										pieceList[clickedPiece].setPos(up, right, piecePositions);
										vaoArray[clickedPiece + 1].Bind();  // this may cause me problems later: using 'clickedPiece' only works if the objects in pieceList are in the same order as their corresponding VAOs in vaoArray
										EBO EBOtemp(squareIndices[pieceList[clickedPiece].getPos()], sizeof(squareIndices[pieceList[clickedPiece].getPos()]));
										linkingFunction(vaoArray[clickedPiece + 1], VBO1, EBOtemp, bufferAttribNum, 3, 3, 2); // same problem as above, find a method that doesn't require the arrays to be in the same order
										

										// Update who's turn it is. This code is generalised in case I want to play with more than two players
										playerTurn++;
										if (playerTurn == sizeof(players) / sizeof(char)) {
											playerTurn = 0;
										}

										break;
									}
								}
								break;
							}
						}
					}
			}  
			// If no piece was already clicked, check if the last click was on a piece
			else 
			{
				//Gets cursor position (converts from 800x800 scale to inverted -1x1 scale)
				double xcursorpos;
				double ycursorpos;
				glfwGetCursorPos(window, &xcursorpos, &ycursorpos);
				float x = (2 * float(xcursorpos) - windowWidth) / windowWidth;
				float y = (windowHeight - 2 * float(ycursorpos)) / windowHeight;


				for (int i = 0; i < 32; i++) { // go through all the pieces and check if the mouse pos match the piece pos
					int ind1 = squareIndices[pieceList[i].getPos()][0]; // each square has 6 indices, the first one corresponds to the bottom left corner of the square
					int ind2 = squareIndices[pieceList[i].getPos()][1]; // top right corner
					if ((x > vertices[bufferAttribNum * ind1]) && ((x < vertices[bufferAttribNum * ind2]))) // if the mouse xPos is within the x value of the bottom left corner and the top right corner
					{
						if ((y > vertices[bufferAttribNum * ind1 + 1]) && ((y < vertices[bufferAttribNum * ind2 + 1]))) // if the mouse yPos is within the y value of the bottom left corner and the top right corner
						{
							//then pieceList[i] is the piece being clicked on
							

							// if we clicked on the wrong colour then break from the loop and try again
							if (pieceList[i].getColour() != players[playerTurn]) {
								break;
							}
							

							pieceClicked = TRUE;
							
							// update and get moveset
							pieceList[i].setMoveSet(piecePositions);
							std::vector<int> pieceMoveSet = pieceList[i].getMoveSet();

							// Highlight the squares that are in the moveSet of the clicked piece
							#pragma region
							for (int e = 0; e < pieceMoveSet.size(); e++) {

								// Bottom left corner of square
								//vertices[bufferAttribNum * squareIndices[pieceMoveSet[e]][0] + 3] = 0.5; //R
								vertices[bufferAttribNum * boardIndices[6*pieceMoveSet[e] + 2] + 3] = 0.5; //R
								vertices[bufferAttribNum * boardIndices[6 * pieceMoveSet[e] + 2] + 4] = 0.5; //G
								vertices[bufferAttribNum * boardIndices[6 * pieceMoveSet[e] + 2] + 5] = 0.5; //B
							}

							VAO1.Bind();
							VBO VBOtemp(vertices, sizeof(vertices));
							EBO EBO1(boardIndices, sizeof(boardIndices));
							linkingFunction(VAO1, VBOtemp, EBO1, bufferAttribNum, 3, 3, 2);
							VBOtemp.Delete();
							#pragma endregion

							clickedPiece = i;
							break;
						}
					}

				}
			}

		}
		#pragma endregion


		// DRAW BACKGROUND, BOARD, AND PIECES
		#pragma region

		// Specify the colour of the background
		glClearColor(0.7f, 0.13f, 0.17f, 1.0f);
		// clean the back buffer and assign the new colour to it
		glClear(GL_COLOR_BUFFER_BIT);


		// DRAW CHESS BOARD
		// Tell OpenGL which shader program we want to use
		shaderProgram2.Activate();
		// No texture with shaderProgram2
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		//Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6 * (boardHeight * boardWidth), GL_UNSIGNED_INT, (void*)0);
		
		
		// Using different shader program now (this one does textures)
		shaderProgram.Activate();

		
		// DRAW WHITE ROOK1
		// Binds texture so that it appears in rendering
		whiteRookTex.Bind();
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE KNIGHT1
		whiteKnightTex.Bind();
		VAO3.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE BISHOP1
		whiteBishopTex.Bind();
		VAO4.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE QUEEN
		whiteQueenTex.Bind();
		VAO5.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE KING
		whiteKingTex.Bind();
		VAO6.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE BISHOP2
		whiteBishopTex.Bind();
		VAO7.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE KNIGHT2
		whiteKnightTex.Bind();
		VAO8.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE ROOK2
		whiteRookTex.Bind();
		VAO9.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE PAWN1
		whitePawnTex.Bind();
		VAO10.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE PAWN2
		whitePawnTex.Bind();
		VAO11.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE PAWN3
		whitePawnTex.Bind();
		VAO12.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE PAWN4
		whitePawnTex.Bind();
		VAO13.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE PAWN5
		whitePawnTex.Bind();
		VAO14.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE PAWN6
		whitePawnTex.Bind();
		VAO15.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE PAWN7
		whitePawnTex.Bind();
		VAO16.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW WHITE PAWN8
		whitePawnTex.Bind();
		VAO17.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK PAWN1
		blackPawnTex.Bind();
		VAO18.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK PAWN2
		blackPawnTex.Bind();
		VAO19.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK PAWN3
		blackPawnTex.Bind();
		VAO20.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK PAWN4
		blackPawnTex.Bind();
		VAO21.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK PAWN5
		blackPawnTex.Bind();
		VAO22.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK PAWN6
		blackPawnTex.Bind();
		VAO23.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK PAWN7
		blackPawnTex.Bind();
		VAO24.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK PAWN8
		blackPawnTex.Bind();
		VAO25.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK ROOK1
		blackRookTex.Bind();
		VAO26.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK KNIGHT1
		blackKnightTex.Bind();
		VAO27.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK BISHOP1
		blackBishopTex.Bind();
		VAO28.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK QUEEN
		blackQueenTex.Bind();
		VAO29.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK KING
		blackKingTex.Bind();
		VAO30.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK BISHOP2
		blackBishopTex.Bind();
		VAO31.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK KNIGHT2
		blackKnightTex.Bind();
		VAO32.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// DRAW BLACK ROOK2
		blackRookTex.Bind();
		VAO33.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		#pragma endregion


		// Take care of all GLFW events		
		glfwPollEvents();
	}

	// DELETE ALL OBJECTS CREATED
	#pragma region
	VAO1.Delete(); // should probably delete all the VAOs
	VBO1.Delete();
	whiteKingTex.Delete();
	blackKingTex.Delete();
	whiteQueenTex.Delete();
	blackQueenTex.Delete();
	whiteRookTex.Delete();
	blackRookTex.Delete();
	whiteBishopTex.Delete();
	blackBishopTex.Delete();
	whiteKnightTex.Delete();
	blackKnightTex.Delete();
	whitePawnTex.Delete();
	blackPawnTex.Delete();
	shaderProgram.Delete();
	shaderProgram2.Delete();
	
	// deletes the window object from memory
	glfwDestroyWindow(window);
	glfwTerminate();
	#pragma endregion

	return 0;
};