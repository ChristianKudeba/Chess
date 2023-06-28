#include<iostream>
#include<Windows.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<dwmapi.h>
#include<vector>
#include<iterator>
#include<algorithm>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"




// CHESS PIECE CLASS
class chessPiece {
private:

	int pieceOrder;
	int texOrder;
	int vaoOrder;
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
	chessPiece(int vaoVecOrder, int textureVecOrder, int pieceListOrder, int squareIndex, int boardWidth, int boardHeight, char type, char colour, std::vector<chessPiece>& pieceList, std::vector<int>& postionArray)
	{
		pieceOrder = pieceListOrder;
		texOrder = textureVecOrder;
		vaoOrder = vaoVecOrder;
		pieceType = type;
		pieceColour = colour;
		ind = squareIndex;
		postionArray[ind] = pieceOrder;
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
			#pragma region
			switch (pieceColour) {
				case 'w': // white
					#pragma region
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
					#pragma endregion
				case 'b': // black
					#pragma region
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
					#pragma endregion
			}			
			break;
			#pragma endregion
		case 'N': //KNIGHT
			#pragma region
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
			#pragma endregion
		case 'B': // BISHOP
			#pragma region
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
			#pragma endregion
		case 'R': // ROOK
			#pragma region
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
			#pragma endregion
		case 'Q': // QUEEN
			#pragma region
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
			#pragma endregion
		case 'K': // KING
			#pragma region
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
			#pragma endregion
		default:
			scope.clear();
		}
	}

	// Set new piece position and update scope 
	void setPos(GLuint verticleDirection, GLuint horizontalDirection, std::vector<int>& postionArray)
	{
		postionArray[ind] = -1;
		
		ind = ind + verticleDirection * up + horizontalDirection * right;

		postionArray[ind] = pieceOrder;

		scope.clear(); // Clear scope before adding new indices
		// Update scope
		switch (pieceType) {
		case 'P': // PAWN
			#pragma region
			switch (pieceColour) {
			case 'w': // white
				#pragma region
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
				#pragma endregion
			case 'b': // black
				#pragma region
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
				#pragma endregion
			break;
			#pragma endregion
		case 'N': //KNIGHT
			#pragma region
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
			#pragma endregion
		case 'B': // BISHOP
			#pragma region
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
			#pragma endregion
		case 'R': // ROOK
			#pragma region
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
			#pragma endregion
			break;
		case 'Q': // QUEEN
			#pragma region
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
			#pragma endregion
		case 'K': // KING
			#pragma region
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
			#pragma endregion
		default:
			scope.clear();
		}
	}

	// Generate and return piece moveSet for given board state
	void setMoveSet(std::vector<int>& postionArray, std::vector<chessPiece>& listOfLivingPieces)
	{
		moveSet.clear(); // clear moveSet before adding new indices
		
		switch (pieceType) {
		case 'P': // PAWN
			#pragma region
			switch (pieceColour) {
			case 'w': // white
				#pragma region
				// Up
				if (ind + mp1 < totalSquareNum) {
					// if nothing in front of the pawn then it can move up
					if (postionArray[ind + mp1] == -1) {
						moveSet.push_back(ind + mp1);
						
						// if nothing two ahead of the pawn it can move up 2 
						if (postionArray[ind + 2*mp1] == -1) {
							moveSet.push_back(ind + 2 * mp1);
						}
					}
				}
				// North-East Diagonal
				if ((ind + mp5 < totalSquareNum) && ((ind + 1) % up != 0)) {
					// if the right diagonal in front of the pawn is a piece of the opposite colour 
					// (or simply a different coloured piece if I add more colours to the game)
					// then the pawn can capture so it goes in moveSet
					if ((postionArray[ind + mp5] != -1) && (listOfLivingPieces[postionArray[ind + mp5]].getColour() != pieceColour)) {
						moveSet.push_back(ind + mp5);
					}
				}
				// North-West Diagonal
				if ((ind + mp6 < totalSquareNum) && ((ind + 1) % up != 1)) {
					// if the left diagonal in front of the pawn is a piece of the opposite colour 
					// (or simply a different coloured piece if I add more colours to the game)
					// then the pawn can capture so it goes in moveSet
					if ((postionArray[ind + mp6] != -1) && (listOfLivingPieces[postionArray[ind + mp6]].getColour() != pieceColour)){
						moveSet.push_back(ind + mp6);
					}
				}
				break;
				#pragma endregion
			case 'b': // black
				#pragma region
				// Down
				if (ind + mp2 >= 0) {
					if (postionArray[ind + mp2] == -1) {
						moveSet.push_back(ind + mp2);
						if (postionArray[ind + 2 * mp2] == -1) {
							moveSet.push_back(ind + 2 * mp2);
						}
					}
				}
				// South-East Diagonal
				if ((ind + mp7 >= 0) && ((ind + 1) % up != 0)) {
					if ((postionArray[ind + mp7] != -1) && (listOfLivingPieces[postionArray[ind + mp7]].getColour() != pieceColour)){
						moveSet.push_back(ind + mp7);
					}
				}
				// South-West Diagonal
				if ((ind + mp8 >= 0) && ((ind + 1) % up != 1)) {
					if ((postionArray[ind + mp8] != -1) && (listOfLivingPieces[postionArray[ind + mp8]].getColour() != pieceColour)){
						moveSet.push_back(ind + mp8);
					}
				}
				break;
			}
			#pragma endregion
			break;
			#pragma endregion
		case 'N': //KNIGHT
			#pragma region
			// 2 Up 1 Right
			if ((ind + mp9 < totalSquareNum) && ((ind + 1) % up != 0)) {
				//  if there's no piece of the same colour on ind + mp9, then add ind + mp9 to moveSet
				if ((postionArray[ind + mp9] == -1) || (listOfLivingPieces[postionArray[ind + mp9]].getColour() != pieceColour)){
					moveSet.push_back(ind + mp9);
				}
			}
			// 2 Up 1 Left
			if ((ind + mp10 < totalSquareNum) && ((ind + 1) % up != 1)) {
				if ((postionArray[ind + mp10] == -1) || (listOfLivingPieces[postionArray[ind + mp10]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp10);
				}
			}
			// 2 Down 1 Right
			if ((ind + mp11 >= 0) && ((ind + 1) % up != 0)) {
				if ((postionArray[ind + mp11] == -1) || (listOfLivingPieces[postionArray[ind + mp11]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp11);
				}
			}
			// 2 Down 1 Left
			if ((ind + mp12 >= 0) && ((ind + 1) % up != 1)) {
				if ((postionArray[ind + mp12] == -1) || (listOfLivingPieces[postionArray[ind + mp12]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp12);
				}
			}
			// 1 Up 2 Right
			if ((ind + mp13 < totalSquareNum) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				if ((postionArray[ind + mp13] == -1) || (listOfLivingPieces[postionArray[ind + mp13]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp13);
				}
			}
			// 1 Up 2 Left
			if ((ind + mp14 < totalSquareNum) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				if ((postionArray[ind + mp14] == -1) || (listOfLivingPieces[postionArray[ind + mp14]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp14);
				}
			}
			// 1 Down 2 Right
			if ((ind + mp15 >= 0) && ((ind + 1) % up != 0) && ((ind + 1) % up != up - 1)) {
				if ((postionArray[ind + mp15] == -1) || (listOfLivingPieces[postionArray[ind + mp15]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp15);
				}
			}
			// 1 Down 2 Left
			if ((ind + mp16 >= 0) && ((ind + 1) % up != 1) && ((ind + 1) % up != 2)) {
				if ((postionArray[ind + mp16] == -1) || (listOfLivingPieces[postionArray[ind + mp16]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp16);
				}
			}
			break;
			#pragma endregion
		case 'B': // BISHOP
			#pragma region
			// North-East Diagonal
			for (int n = 1; n < totalSquareNum; n++) {
				if ((ind + n * mp5 < totalSquareNum) && ((ind + n * mp5) % up != 0)) {
					// if there's no piece on ind + n*mp5, then add ind + n*mp5 to moveSet
					if (postionArray[ind + n * mp5] == -1) {
						moveSet.push_back(ind + n * mp5);
					}
					// if there is a piece of another colour on that square, then don't add ind + n*mp5 as the last move from this diagonal to moveSet
					else if (listOfLivingPieces[postionArray[ind + n * mp5]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp5);
						break;
					}
					// if there is a piece of the same colour, than don't add any more squares (along this diagonal) to moveSet
					else { break; }
				}
				else { break; }
			}
			// North-West Diagonal
			for (int n = 1; n < totalSquareNum; n++) {
				if ((ind + n * mp6 < totalSquareNum) && ((ind + 1 + n * mp6) % up != 0)) {
					if (postionArray[ind + n * mp6] == -1) {
						moveSet.push_back(ind + n * mp6);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp6]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp6);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// South-East Diagonal
			for (int n = 1; n < totalSquareNum; n++) {
				if ((ind + n * mp7 >= 0) && ((ind + n * mp7) % up != 0)) { // add condition so it can't go below 0
					if (postionArray[ind + n * mp7] == -1) {
						moveSet.push_back(ind + n * mp7);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp7]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp7);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// South-West Diagonal
			for (int n = 1; n < totalSquareNum; n++) {
				if ((ind + n * mp8 >= 0) && ((ind + 1 + n * mp8) % up != 0)) {
					if (postionArray[ind + n * mp8] == -1) {
						moveSet.push_back(ind + n * mp8);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp8]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp8);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			break;
			#pragma endregion
		case 'R': // ROOK
			#pragma region
			// Up
			for (int n = 1; n < totalSquareNum; n++) {
				if (ind + n * mp1 < totalSquareNum) {
					if (postionArray[ind + n * mp1] == -1) {
						moveSet.push_back(ind + n * mp1);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp1]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp1);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// Down
			for (int n = 1; n < totalSquareNum; n++) {
				if (ind + n * mp2 >= 0) {
					if (postionArray[ind + n * mp2] == -1) {
						moveSet.push_back(ind + n * mp2);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp2]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp2);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// Right
			for (int n = 1; n < totalSquareNum; n++) {
				if (((ind + 1) % up != 0) && ((ind + n * mp3) % up != 0)) {
					if (postionArray[ind + n * mp3] == -1) {
						moveSet.push_back(ind + n * mp3);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp3]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp3);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// Left
			for (int n = 1; n < totalSquareNum; n++) {
				if (((ind + 1) % up != 1) && ((ind + 1 + n * mp4) % up != 0)) {
					if (postionArray[ind + n * mp4] == -1) {
						moveSet.push_back(ind + n * mp4);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp4]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp4);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			break;
			#pragma endregion
		case 'Q': // QUEEN
			#pragma region
			// North-East Diagonal
			for (int n = 1; n < totalSquareNum; n++) {
				if ((ind + n * mp5 < totalSquareNum) && ((ind + n * mp5) % up != 0)) {
					if (postionArray[ind + n * mp5] == -1) {
						moveSet.push_back(ind + n * mp5);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp5]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp5);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// North-West Diagonal
			for (int n = 1; n < totalSquareNum; n++) {
				if ((ind + n * mp6 < totalSquareNum) && ((ind + n * mp6) % up != 0)) {
					if (postionArray[ind + n * mp6] == -1) {
						moveSet.push_back(ind + n * mp6);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp6]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp6);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// South-East Diagonal
			for (int n = 1; n < totalSquareNum; n++) {
				if ((ind + n * mp7 >= 0) && ((ind + n * mp7) % up != 0)) {
					if (postionArray[ind + n * mp7] == -1) {
						moveSet.push_back(ind + n * mp7);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp7]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp7);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// South-West Diagonal
			for (int n = 1; n < totalSquareNum; n++) {
				if ((ind + n * mp8 >= 0) && ((ind + 1 + n * mp8) % up != 0)) {
					if (postionArray[ind + n * mp8] == -1) {
						moveSet.push_back(ind + n * mp8);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp8]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp8);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// Up
			for (int n = 1; n < totalSquareNum; n++) {
				if (ind + n * mp1 < totalSquareNum) {
					if (postionArray[ind + n * mp1] == -1) {
						moveSet.push_back(ind + n * mp1);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp1]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp1);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// Down
			for (int n = 1; n < totalSquareNum; n++) {
				if (ind + n * mp2 >= 0) {
					if (postionArray[ind + n * mp2] == -1) {
						moveSet.push_back(ind + n * mp2);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp2]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp2);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// Right
			for (int n = 1; n < totalSquareNum; n++) {
				if (((ind + 1) % up != 0) && ((ind + n * mp3) % up != 0)) {
					if (postionArray[ind + n * mp3] == -1) {
						moveSet.push_back(ind + n * mp3);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp3]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp3);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			// Left
			for (int n = 1; n < totalSquareNum; n++) {
				if (((ind + 1) % up != 1) && ((ind + 1 + n * mp4) % up != 0)) {
					if (postionArray[ind + n * mp4] == -1) {
						moveSet.push_back(ind + n * mp4);
					}
					else if (listOfLivingPieces[postionArray[ind + n * mp4]].getColour() != pieceColour) {
						moveSet.push_back(ind + n * mp4);
						break;
					}
					else { break; }
				}
				else { break; }
			}
			break;
			#pragma endregion
		case 'K': // KING
			#pragma region
			// The king has similar movement to the queen except it only moves one square in any direction, so no loops :)
			// Up
			if (ind + mp1 < totalSquareNum) {
				if ((postionArray[ind + mp1] == -1) || (listOfLivingPieces[postionArray[ind + mp1]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp1);
				}
			}
			// Down
			if (ind + mp2 >= 0) {
				if ((postionArray[ind + mp2] == -1) || (listOfLivingPieces[postionArray[ind + mp2]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp2);
				}
			}
			// Right
			if ((ind + 1) % up != 0) {
				if ((postionArray[ind + mp3] == -1) || (listOfLivingPieces[postionArray[ind + mp3]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp3);
				}
			}
			// Left
			if ((ind + 1) % up != 1) {
				if ((postionArray[ind + mp4] == -1) || (listOfLivingPieces[postionArray[ind + mp4]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp4);
				}
			}
			// North-East Diagonal
			if ((ind + mp5 < totalSquareNum) && ((ind + 1) % up != 0)) {
				if ((postionArray[ind + mp5] == -1) || (listOfLivingPieces[postionArray[ind + mp5]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp5);
				}
			}
			// North-West Diagonal
			if ((ind + mp6 < totalSquareNum) && ((ind + 1) % up != 1)) {
				if ((postionArray[ind + mp6] == -1) || (listOfLivingPieces[postionArray[ind + mp6]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp6);
				}
			}
			// South-East Diagonal
			if ((ind + mp7 >= 0) && ((ind + 1) % up != 0)) {
				if ((postionArray[ind + mp7] == -1) || (listOfLivingPieces[postionArray[ind + mp7]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp7);
				}
			}
			// South-West Diagonal
			if ((ind + mp8 >= 0) && ((ind + 1) % up != 1)) {
				if ((postionArray[ind + mp8] == -1) || (listOfLivingPieces[postionArray[ind + mp8]].getColour() != pieceColour)) {
					moveSet.push_back(ind + mp8);
				}
			}
			break;
			#pragma endregion
		default:
			moveSet.clear();
		}
	}

	void setOrder(int newPieceOrder, int newVaoOrder, std::vector<int>& postionArray) {
		pieceOrder = newPieceOrder;
		postionArray[ind] = pieceOrder;
		vaoOrder = newVaoOrder;
	}

	void setGraveOrder(int newPosition, int newPieceOrder, int newVaoOrder, std::vector<int>& postionArray)
	{
		ind = newPosition;
		pieceOrder = newPieceOrder;
		postionArray.push_back(newPosition);
		//postionArray[ind] = pieceOrder;
		vaoOrder = newVaoOrder;
	}

	std::vector<int> getScope()
	{
		return scope;
	}

	std::vector<int> getMoveSet()
	{
		return moveSet;
	}

	int getPos()
	{
		return ind;
	}

	int getTexOrder() {
		return texOrder;
	}

	int getVaoOrder() {
		return vaoOrder;
	}

	char getColour()
	{
		return pieceColour;
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
	int const piecesPerSide = 16;
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

	// BOARD
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

	#pragma endregion

	// GRAVEYARD
	#pragma region
	
	// BLACK graveyard vertices
	GLfloat blackGraveyardVertices[bufferAttribNum * 2 * (piecesPerSide + 1)]{};
	for (int i = 0; i < 2; ++i) { // columns
		for (int j = 0; j < (piecesPerSide + 1); ++j) { // rows
			blackGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j))] = 0.1f * float(j*0.5 - boardWidth / 2); // xPos
			blackGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 1] = 0.1f * float((i*0.75 + boardHeight) / 2); // yPos
			blackGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 2] = 0.0f;  // zPos
			blackGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 3] = 0.0f;  // R
			blackGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 4] = 0.0f;  // G
			blackGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 5] = 0.0f;  // B
			blackGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 6] = float(j);  // Texture xCoord
			blackGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 7] = float(i);  // Texture yCoord
		}
	}


	// WHITE graveyard vertices
	GLfloat whiteGraveyardVertices[bufferAttribNum * 2 * (piecesPerSide + 1)]{};
	for (int i = 0; i < 2; ++i) { // columns
		for (int j = 0; j < (piecesPerSide + 1); ++j) { // rows
			whiteGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j))] = 0.1f * float(j * 0.5 - boardWidth / 2); // xPos
			whiteGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 1] = -0.1f * float((i * 0.75 + boardHeight) / 2); // yPos
			whiteGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 2] = 0.0f;  // zPos
			whiteGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 3] = 0.0f;  // R
			whiteGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 4] = 0.0f;  // G
			whiteGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 5] = 0.0f;  // B
			whiteGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 6] = float(j);  // Texture xCoord
			whiteGraveyardVertices[(bufferAttribNum * ((piecesPerSide + 1) * i + j)) + 7] = float(i);  // Texture yCoord
		}
	}

	// graveyard indices
	GLuint graveyardIndices[2 * piecesPerSide][6]{};
	n = 0;
	for (int m = 0; m < (2 * piecesPerSide); ++m)
	{
		if (((m + n + 1) % (piecesPerSide + 1)) == 0) // if m represents an "edge" vertex
		{
			n++;
		}

		// graveyardIndices are used to determine the placement of pieces when they die
		graveyardIndices[m][0] = m + n;
		graveyardIndices[m][1] = m + n + piecesPerSide + 2;
		graveyardIndices[m][2] = m + n + piecesPerSide + 1;
		graveyardIndices[m][3] = m + n;
		graveyardIndices[m][4] = m + n + piecesPerSide + 2;
		graveyardIndices[m][5] = m + n + 1;
	};
	#pragma endregion


	// Vector of ints indicating which piece is on each square
	// the purpose of this is so we don't have to loop through pieceList to 
	// check what piece (if any) is on a particular square
	std::vector<int> livePiecePositions(boardHeight * boardWidth, -1);
	
	std::vector<int> whiteGraveyardPositions;

	std::vector<int> blackGraveyardPositions;


	#pragma endregion


	// INITIALISE PIECE OBJECTS
	#pragma region

	// Vector of LIVE chesspieces, makes accessing the pieces much easier
	std::vector<chessPiece> livePieceList{};

	// White Rook1
	chessPiece whiteRook1(0, 4, 0, 0, boardWidth, boardHeight, 'R', 'w', livePieceList, livePiecePositions);
	// White Knight1
	chessPiece whiteKnight1(1, 8, 1, 1, boardWidth, boardHeight, 'N', 'w', livePieceList, livePiecePositions);
	// White Bishop1
	chessPiece whiteBishop1(2, 6, 2, 2, boardWidth, boardHeight, 'B', 'w', livePieceList, livePiecePositions);
	// White Queen
	chessPiece whiteQueen(3, 2, 3, 3, boardWidth, boardHeight, 'Q', 'w', livePieceList, livePiecePositions);
	// White King
	chessPiece whiteKing(4, 0, 4, 4, boardWidth, boardHeight, 'K', 'w', livePieceList, livePiecePositions);
	// White Bishop2
	chessPiece whiteBishop2(5, 6, 5, 5, boardWidth, boardHeight, 'B', 'w', livePieceList, livePiecePositions);
	// White Knight2
	chessPiece whiteKnight2(6, 8, 6, 6, boardWidth, boardHeight, 'N', 'w', livePieceList, livePiecePositions);
	// White Rook2
	chessPiece whiteRook2(7, 4, 7, 7, boardWidth, boardHeight, 'R', 'w', livePieceList, livePiecePositions);
	// White Pawn1
	chessPiece whitePawn1(8, 10, 8, 8, boardWidth, boardHeight, 'P', 'w', livePieceList, livePiecePositions);
	// White Pawn2
	chessPiece whitePawn2(9, 10, 9, 9, boardWidth, boardHeight, 'P', 'w', livePieceList, livePiecePositions);
	// White Pawn3
	chessPiece whitePawn3(10, 10, 10, 10, boardWidth, boardHeight, 'P', 'w', livePieceList, livePiecePositions);
	// White Pawn4
	chessPiece whitePawn4(11, 10, 11, 11, boardWidth, boardHeight, 'P', 'w', livePieceList, livePiecePositions);
	// White Pawn5
	chessPiece whitePawn5(12, 10, 12, 12, boardWidth, boardHeight, 'P', 'w', livePieceList, livePiecePositions);
	// White Pawn6
	chessPiece whitePawn6(13, 10, 13, 13, boardWidth, boardHeight, 'P', 'w', livePieceList, livePiecePositions);
	// White Pawn7
	chessPiece whitePawn7(14, 10, 14, 14, boardWidth, boardHeight, 'P', 'w', livePieceList, livePiecePositions);
	// White Pawn8
	chessPiece whitePawn8(15, 10, 15, 15, boardWidth, boardHeight, 'P', 'w', livePieceList, livePiecePositions);
	// Black Pawn1
	chessPiece blackPawn1(16, 11, 16, 48, boardWidth, boardHeight, 'P', 'b', livePieceList, livePiecePositions);
	// Black Pawn2
	chessPiece blackPawn2(17, 11, 17, 49, boardWidth, boardHeight, 'P', 'b', livePieceList, livePiecePositions);
	// Black Pawn3
	chessPiece blackPawn3(18, 11, 18, 50, boardWidth, boardHeight, 'P', 'b', livePieceList, livePiecePositions);
	// Black Pawn4
	chessPiece blackPawn4(19, 11, 19, 51, boardWidth, boardHeight, 'P', 'b', livePieceList, livePiecePositions);
	// Black Pawn5
	chessPiece blackPawn5(20, 11, 20, 52, boardWidth, boardHeight, 'P', 'b', livePieceList, livePiecePositions);
	// Black Pawn6
	chessPiece blackPawn6(21, 11, 21, 53, boardWidth, boardHeight, 'P', 'b', livePieceList, livePiecePositions);
	// Black Pawn7
	chessPiece blackPawn7(22, 11, 22, 54, boardWidth, boardHeight, 'P', 'b', livePieceList, livePiecePositions);
	// Black Pawn8
	chessPiece blackPawn8(23, 11, 23, 55, boardWidth, boardHeight, 'P', 'b', livePieceList, livePiecePositions);
	// Black Rook1
	chessPiece blackRook1(24, 5, 24, 56, boardWidth, boardHeight, 'R', 'b', livePieceList, livePiecePositions);
	// Black Knight1
	chessPiece blackKnight1(25, 9, 25, 57, boardWidth, boardHeight, 'N', 'b', livePieceList, livePiecePositions);
	// Black Bishop1
	chessPiece blackBishop1(26, 7, 26, 58, boardWidth, boardHeight, 'B', 'b', livePieceList, livePiecePositions);
	// Black Queen
	chessPiece blackQueen(27, 3, 27, 59, boardWidth, boardHeight, 'Q', 'b', livePieceList, livePiecePositions);
	// Black King
	chessPiece blackKing(28, 1, 28, 60, boardWidth, boardHeight, 'K', 'b', livePieceList, livePiecePositions);
	// Black Bishop2
	chessPiece blackBishop2(29, 7, 29, 61, boardWidth, boardHeight, 'B', 'b', livePieceList, livePiecePositions);
	// Black Knight2
	chessPiece blackKnight2(30, 9, 30, 62, boardWidth, boardHeight, 'N', 'b', livePieceList, livePiecePositions);
	// Black Rook2
	chessPiece blackRook2(31, 5, 31, 63, boardWidth, boardHeight, 'R', 'b', livePieceList, livePiecePositions);

	// Fill vector with the pieces we've initialised
	livePieceList = { whiteRook1, whiteKnight1, whiteBishop1, whiteQueen, whiteKing, whiteBishop2, whiteKnight2, whiteRook2, whitePawn1, whitePawn2, whitePawn3, whitePawn4, whitePawn5, whitePawn6, whitePawn7, whitePawn8, blackPawn1,blackPawn2, blackPawn3, blackPawn4, blackPawn5, blackPawn6, blackPawn7, blackPawn8, blackRook1, blackKnight1, blackBishop1, blackQueen, blackKing, blackBishop2, blackKnight2, blackRook2 };
	
	// Vector of CAPTURED chesspieces (starts off empty)
	std::vector<chessPiece> deadPieceList{};

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

	std::vector<VAO> livePieceVaoVec = { VAO2, VAO3, VAO4, VAO5, VAO6, VAO7, VAO8, VAO9, VAO10, VAO11, VAO12, VAO13, VAO14, VAO15, VAO16, VAO17, VAO18, VAO19, VAO20, VAO21, VAO22, VAO23, VAO24, VAO25, VAO26, VAO27, VAO28, VAO29, VAO30, VAO31, VAO32, VAO33 };

	std::vector<VAO> deadPieceVaoVec = { };

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


	std::vector<Texture> pieceTextureVec = { whiteKingTex, blackKingTex, whiteQueenTex, blackQueenTex, whiteRookTex, blackRookTex, whiteBishopTex, blackBishopTex, whiteKnightTex, blackKnightTex, whitePawnTex, blackPawnTex };



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



	bool pieceClicked = FALSE; // Has a piece been clicked?
	int clickedPiece;		   // What is the livePieceList order of the selected piece?
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
					std::vector<int> pieceMoveSet = livePieceList[clickedPiece].getMoveSet();
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

										// CAPTURES
										// check if another piece is already on the square and if so remove it
										if (livePiecePositions[j] != -1) {

											int victimPieceOrder = livePiecePositions[j];
											
											
											// Add piece to dead piece vector
											int newOrder = deadPieceList.size();
											deadPieceList.push_back(livePieceList[livePiecePositions[j]]);
											

											// Remove piece from live piece vector and remove the piece's VAO from livePieceVaoVec
											std::vector<chessPiece>::iterator ptr;
											ptr = livePieceList.begin();
											advance(ptr, livePiecePositions[j]);

											std::vector<VAO>::iterator ptr2;
											ptr2 = livePieceVaoVec.begin();
											advance(ptr2, livePiecePositions[j]);

											livePieceList.erase(ptr);
											livePieceVaoVec.erase(ptr2);


											// Update order for all the pieces in live piece vector that came after the piece we just removed
											for (int livePieceOrder = livePiecePositions[j]; livePieceOrder < livePieceList.size(); livePieceOrder++) {											
												int newVaoOrder = livePieceList[livePieceOrder].getVaoOrder() - 1;
												livePieceList[livePieceOrder].setOrder(livePieceOrder, newVaoOrder, livePiecePositions); // set order also updates livePiecePositions and vaoOrder
											}

											if (clickedPiece > victimPieceOrder) { clickedPiece--; }  // Make sure we select the right piece to move after updating livePieceList


											// Give the piece a new VAO
											if (players[playerTurn] == 'b') {




												int newPos = blackGraveyardPositions.size();

												VAO VAOdead;
												VAOdead.Bind();
												VBO VBOdead(blackGraveyardVertices, sizeof(blackGraveyardVertices));
												EBO EBOdead(graveyardIndices[newPos], sizeof(graveyardIndices[newPos]));
												linkingFunction(VAOdead, VBOdead, EBOdead, bufferAttribNum, 3, 3, 2);
												int newDeadVaoOrder = deadPieceVaoVec.size();
												deadPieceVaoVec.push_back(VAOdead);

												// Update the dead piece's order
												deadPieceList[newOrder].setGraveOrder(newPos, newOrder, newDeadVaoOrder, blackGraveyardPositions);
											}
											else {
												int newPos = whiteGraveyardPositions.size();


												VAO VAOdead;
												VAOdead.Bind();
												VBO VBOdead(whiteGraveyardVertices, sizeof(whiteGraveyardVertices));
												EBO EBOdead(graveyardIndices[newPos], sizeof(graveyardIndices[newPos]));
												linkingFunction(VAOdead, VBOdead, EBOdead, bufferAttribNum, 3, 3, 2);
												int newDeadVaoOrder = deadPieceVaoVec.size();
												deadPieceVaoVec.push_back(VAOdead);

												// Update the dead piece's order
												deadPieceList[newOrder].setGraveOrder(newPos, newOrder, newDeadVaoOrder, whiteGraveyardPositions);
											}
										}
										
										// how many indices to move the piece up
										int up = (j - livePieceList[clickedPiece].getPos() + livePieceList[clickedPiece].getPos() % (boardWidth)-j % (boardWidth)) / boardWidth;
										// how many indices to move the piece to the right
										int right = (j - up * boardWidth) - livePieceList[clickedPiece].getPos();

										livePieceList[clickedPiece].setPos(up, right, livePiecePositions); // set new piece position
										livePieceVaoVec[livePieceList[clickedPiece].getVaoOrder()].Bind();  // bind the correct vao
										EBO EBOtemp(squareIndices[livePieceList[clickedPiece].getPos()], sizeof(squareIndices[livePieceList[clickedPiece].getPos()])); 
										linkingFunction(livePieceVaoVec[livePieceList[clickedPiece].getVaoOrder()], VBO1, EBOtemp, bufferAttribNum, 3, 3, 2); 
										

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


				for (int i = 0; i < livePieceList.size(); i++) { // go through all the pieces and check if the mouse pos match the piece pos
					int ind1 = squareIndices[livePieceList[i].getPos()][0]; // each square has 6 indices, the first one corresponds to the bottom left corner of the square
					int ind2 = squareIndices[livePieceList[i].getPos()][1]; // top right corner
					if ((x > vertices[bufferAttribNum * ind1]) && ((x < vertices[bufferAttribNum * ind2]))) // if the mouse xPos is within the x value of the bottom left corner and the top right corner
					{
						if ((y > vertices[bufferAttribNum * ind1 + 1]) && ((y < vertices[bufferAttribNum * ind2 + 1]))) // if the mouse yPos is within the y value of the bottom left corner and the top right corner
						{
							//then livePieceList[i] is the piece being clicked on
							clickedPiece = i;

							// if we clicked on the wrong colour then break from the loop and try again
							if (livePieceList[i].getColour() != players[playerTurn]) {
								break;
							}
							

							pieceClicked = TRUE;
							
							// update and get moveset
							livePieceList[i].setMoveSet(livePiecePositions, livePieceList);
							std::vector<int> pieceMoveSet = livePieceList[i].getMoveSet();

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


		// DRAW PIECES

		for (int order = 0; order < livePieceList.size(); order++) {
			pieceTextureVec[livePieceList[order].getTexOrder()].Bind(); // Binds texture so that it appears in rendering
			livePieceVaoVec[livePieceList[order].getVaoOrder()].Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		}


		// Draw Graveyard pieces
		for (int order = 0; order < deadPieceList.size(); order++) {
			pieceTextureVec[deadPieceList[order].getTexOrder()].Bind(); // Binds texture so that it appears in rendering
			deadPieceVaoVec[deadPieceList[order].getVaoOrder()].Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		}


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