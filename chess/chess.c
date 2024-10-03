/**
 * chess.c - a simple implementation of the game of chess in C
 *
 * @author Hypirae <github.com/Hypirae>
 * @copyright 2024
 * @license MIT
 *
 * Nothing inherently makes sense and though I have gone through
 * great trouble to add informative documentation I fear that I have
 * instead gummed it up by combining notes and code into the same file.
 *
 * Cry about it... idk
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Customary rambling:
//
// There are 64 spaces on a chess board.
// There are also 6 different suits...
// Each suit can either of the white rank or the black rank...
// Of course there is the need to represent an empty space...
//
// So in total, if I were to represent the suits using 3 bits
// I would have enough space for all of the suits, plus two spaces
// for colored but empty spaces (currently unused), and a free bit to spare.
//
// This means that I should be able to represent each piece as a 4 bit number
// so that would reduce the amount of memory needed to represent the board in
// half. There is no clear evidence that this is a good thing and current
// endeavors seem to point to that not being the case.
//
// So essentially:
//
// Each square is represented by 4 bytes.
// 0  0  0  0
// ^  ^_____^
// 1     2
//
// 1. Color of the piece on the square
// 2. Suit of the piece on the square
//
// 0000 = BLACK EMPTY
// 0001 = BLACK PAWN
// 0010 = BLACK KNIGHT
// 0011 = BLACK BISHOP
// 0100 = BLACK ROOK
// 0101 = BLACK QUEEN
// 0110 = BLACK KING
// 1000 = WHITE EMPTY
// 1001 = WHITE PAWN
// 1010 = WHITE KNIGHT
// 1011 = WHITE BISHOP
// 1100 = WHITE ROOK
// 1101 = WHITE QUEEN
// 1110 = WHITE KING
// 1111 = UNDEFINED

// The board should be 32 bytes in size
//
// However, realistically, the compiler can pick any
// integer width that it wants in order to represent
// our enum so this moreso defines the number of spaces
// on a board.
//
// This behavior can be changed but to do so is compiler
// dependent.
#define BOARD_SIZE 32

// Some macros to help get the high and low pieces in each byte.
#define HIGH(x) (x >> 4)
#define LOW(x) (x & 0x0F)

// See above for the numbering scheme
typedef enum SQUARE {
	BLACKEMPTY  = 0,
	BLACKPAWN   = 1,
	BLACKKNIGHT = 2,
	BLACKBISHOP = 3,
	BLACKROOK   = 4,
	BLACKQUEEN  = 5,
	BLACKKING   = 6,
	WHITEEMPTY  = 8,
	WHITEPAWN   = 9,
	WHITEKNIGHT = 10,
	WHITEBISHOP = 11,
	WHITEROOK   = 12,
	WHITEQUEEN  = 13,
	WHITEKING   = 14,
} square_e;

const char square_to_char(uint8_t square) {
	switch (square) {
		case BLACKEMPTY:
		case WHITEEMPTY:
			return '.';
			break;
		case BLACKPAWN:
			return 'p';
			break;
		case WHITEPAWN:
			return 'P';
			break;
		case BLACKKNIGHT:
			return 'n';
			break;
		case WHITEKNIGHT:
			return 'N';
			break;
		case BLACKBISHOP:
			return 'b';
			break;
		case WHITEBISHOP:
			return 'B';
			break;
		case BLACKROOK:
			return 'r';
			break;
		case WHITEROOK:
			return 'R';
			break;
		case BLACKQUEEN: 
			return 'q';
			break;
		case WHITEQUEEN:
			return 'Q';
			break;
		case BLACKKING:
			return 'k';
			break;
		case WHITEKING: 
			return 'K';
			break;
		default:
			return 0; // sneaky lil bugger
	}
}

void initialize_board(square_e *board) {
	// Pre-computed starting board
	square_e starting_board[BOARD_SIZE] = {
		66, 53, 99, 36,        // (br bn), (bb bq), (bk bb), (bn br)
		17, 17, 17, 17,        // (bp bp), (bp bp), (bp bp), (bp bp)
		0, 0, 0, 0,            // (), (), (), ()
		0, 0, 0, 0,            // (), (), (), ()
		0, 0, 0, 0,            // (), (), (), ()
		0, 0, 0, 0,            // (), (), (), ()
		153, 153, 153, 153,    // (wp wp), (wp wp), (wp wp), (wp wp)
		202, 189, 235, 172     // (wr wn), (wb wq), (wk wb), (wn wr)
	};
	
	// Copy the starting board over to our game board
	// IMPORTANT: You must copy based on the size of square_e rather
	//            than trying to copy by bytes as the compiler
	//            is not garaunteed to pick a uint8_t
	memcpy(board, starting_board, (sizeof(square_e) * BOARD_SIZE));
}

void print_board(square_e *board) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		uint8_t high = HIGH(board[i]); // Piece on the left
		uint8_t low = LOW(board[i]);   // Piece on the right

		// TODO: Add ANSI escape codes to generate a board
		//       that is alternating black and white
		printf("%c%c", square_to_char(high),
				square_to_char(low));

		// Print the board into a neat 8 x 8 grid
		// Since 0 % 4 == 0 we need to make sure to skip this
		if ((i + 1) % 4 == 0 && i != 0) {
			printf("\n");
		}
	}
}

int main(int argc, char **argv) {
	// Allocate enough memory for the board
	// IMPORTANT: Allocate based on the size of square_e and not
	//            on byte length as it is not garaunteed that it
	//            is represented as a uint8_t
	square_e *board = calloc(BOARD_SIZE, sizeof(square_e));
	
	// Initiaize the game board
	initialize_board(board);

	// Print the board out
	print_board(board);

	// Free the board
	free(board);

	return EXIT_SUCCESS;
}

