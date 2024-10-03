#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
//
// Therefore with 64 squares on the board, and with each square being represented
// by 4 bits, we would need half as many bytes.
#define BOARD_SIZE 32

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
	memcpy(board, starting_board, (sizeof(square_e) * BOARD_SIZE));
}

void print_board(square_e *board) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		uint8_t high = HIGH(board[i]);
		uint8_t low = LOW(board[i]);

		printf("%c%c", square_to_char(high),
				square_to_char(low));

		if ((i + 1) % 4 == 0 && i != 0) {
			printf("\n");
		}
	}
}

int main(int argc, char **argv) {
	// Allocate enough memory for the board.
	square_e *board = calloc(BOARD_SIZE, sizeof(square_e));
	
	// Initiaize the game board
	initialize_board(board);

	// Print the board out
	print_board(board);

	// Free the board
	free(board);

	return EXIT_SUCCESS;
}
