/****************************************************************************
**	OrangeBot Project
*****************************************************************************
**        /
**       /
**      /
** ______ \
**         \
**          \
*****************************************************************************
**
*****************************************************************************
**	Author: 			Orso Eric
**	Creation Date:
**	Last Edit Date:
**	Revision:			1
**	Version:			0.1 ALFA
****************************************************************************/

/****************************************************************************
**	HYSTORY VERSION
*****************************************************************************
**	V0.1 ALPHA
**		Implemented recursive Tris structure
**		Implemented board generation
**		Tested generation of full move tree
**		Implemented win and finish detection methods
**		Implemented win counters
**		Implemented backpropagation of win counters
****************************************************************************/

/****************************************************************************
**	DESCRIPTION
*****************************************************************************
**
****************************************************************************/

/****************************************************************************
**	KNOWN BUG
*****************************************************************************
**	sizeof(Pieces) is the size of the memory element used for a pieces.
**	not the number of elements inside the neum
****************************************************************************/

/****************************************************************************
**	INCLUDES
****************************************************************************/

//C Libraries
#include <cstdio>
//C++ standard libraries
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <fstream>		//for file save class
#include <algorithm>	//to sort stat vector
//Class Header
#include "tris.h"
//Include user log trace macros (can be disabled with a define for performance)
#include "debug.h"

/****************************************************************************
**	NAMESPACES
****************************************************************************/

//Never use a whole namespace. Use only what you need from it.
using std::cout;
using std::cerr;
using std::endl;
using std::array;
using std::vector;
using std::string;
using std::ofstream;	//output to file
using std::sort;

//Namespace in which class methods are stored
namespace User
{

/****************************************************************************
**	GLOBAL VARIABILE
****************************************************************************/

/****************************************************************************
*****************************************************************************
**	CONSTRUCTORS
*****************************************************************************
****************************************************************************/

/****************************************************************************
**	Default Constructor
**	Tris | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
****************************************************************************/

Tris::Tris( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//Initialize class
	this -> init();

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	RETURN
	///--------------------------------------------------------------------------

	//Trace Return
	DRETURN();

	return;
}	//end constructor: Tris | void

/****************************************************************************
*****************************************************************************
**	DESTRUCTORS
*****************************************************************************
****************************************************************************/

/****************************************************************************
**	Default Destructor
**
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	free all memory
****************************************************************************/

Tris::~Tris( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//counter
	//unsigned int t;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER_ARG("board %p\n", (void *)this);

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	/*
	//if: there is a board position
	if (this -> g_board.empty() == false)
	{
		DPRINT("destroy board\n");
		//Destroy the board vector
		this -> g_board.clear();
	}
	//if: there is a tree of moves
	if (this -> g_moves.empty() == false)
	{
		//for: every move
		for (t = 0;t < this -> g_moves.size();t++)
		{
			DPRINT("destroy move vector\n");
			//destroy the Tris class of this move
			this -> g_moves[t].~Tris();
		}	//end for: every move
		//Destroy move vector
		this -> g_moves.clear();
	}
	*/

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	RETURN
	///--------------------------------------------------------------------------

	//Trace Return
	DRETURN();

	return;
}	//end destructor: ~Tris

/****************************************************************************
*****************************************************************************
**	OPERATORS
*****************************************************************************
****************************************************************************/

/****************************************************************************
**	Operator
**	operator =
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Overload assignment operator = to this class
****************************************************************************/

void Tris::operator = (User::Tris &source )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------


	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//Copy relevant fields from the source class
	this -> copy( &source );

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN();

	return;	//OK
}	//end method: operator = | Tris

/****************************************************************************
**	Operator
**	at | int, int
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Access to a piece of the board
**	return the address to element r, c of the board
**	I just learned references in solving this problem!
****************************************************************************/

Pieces &Tris::at( unsigned int r, unsigned int c )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	/*
	//if: piece is out of bound
	if ((r >= this -> g_board_rows) || (c >= this -> g_board_cols))
	{
		return nullptr;	//FAIL
	}
	*/

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Calculate address of the board position
	return (this -> g_board[ r *this -> g_board_cols +c]);
}	//end method: at | int, int

/****************************************************************************
*****************************************************************************
**	SETTERS
*****************************************************************************
****************************************************************************/

/****************************************************************************
**	Public Setter
**	copy | Tris *
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	copy the board configuration and player turn but not the move structure
****************************************************************************/

bool Tris::copy( User::Tris *source )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER_ARG("source: %p | dest: %p\n", (void *)source, (void *)this);
	//if: source is invalid
	if ((source == NULL) || (source -> is_valid() == false))
	{
		DRETURN_ARG("ERR: source invalid\n");
		return true;	//FAIL
	}

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//Copy the board configuration
	this -> g_board = source -> g_board;
	//Copy the next turn ownership
	this -> g_next_player = source -> get_next_player();
	//if: the move vector is not empty (BUG)
	if (this -> g_moves.size())
	{
		DPRINT("ERR: move vector is size: %d\n", this -> g_moves.size());
		DPRINT("Dump bogous move vector\n");
		//temp counter
		unsigned int t;
		//for: every bogous board
		for (t = 0;t < this -> g_moves.size();t++)
		{
			//show board
			this -> g_moves[t].show_board();
		}	//end for: every bogous board
		//Trace Return
		DRETURN();
		return true;	//FAIL
	}

	//BUG
	//Initialize move vector
	//this -> g_moves = vector<User::Tris>();

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	RETURN
	///--------------------------------------------------------------------------

	//Trace Return
	DRETURN();

	return false;	//OK
}	//end method: copy | Tris *

/****************************************************************************
**	Public Method
**	set_board | string
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Set board position to given character configuration
****************************************************************************/

bool Tris::set_board( string str )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//counter
	unsigned int t;
	//temp piece
	Pieces piece;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();

	if (str.size() != 9)
	{
		DRETURN_ARG("ERR: bad string size: %d\n", str.size() );
		return true; //Fail
	}

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	//for every board position
	for (t = 0;t < User::Tris::g_board_size;t++)
	{
		//convert
		piece = User::Tris::char_to_piece( str[t] );
		//check
		if (piece == User::Pieces::NUM_PIECES)
		{
			DRETURN_ARG("ERR: bad string size: %d\n", str.size() );
			return true; //Fail
		}
		//save
		this -> g_board[ t ] = piece;
	}


	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN();

	return false;	//OK
}	//end method:

/****************************************************************************
*****************************************************************************
**	GETTERS
*****************************************************************************
****************************************************************************/

/****************************************************************************
**	Public Getter
**	get_next_player | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Get the next player
****************************************************************************/

Pieces Tris::get_next_player( void )
{
	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	return this -> g_next_player;
}	//end method: get_next_player | void

/****************************************************************************
**	Public Getter
**	get_num_moves | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Get the number of moves possible from this board position
****************************************************************************/

int Tris::get_num_moves( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//counter
	unsigned int t;
	//Number of moves
	int num_moves;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();
	//if: invalid board
	if (this -> g_board.empty() == true)
	{
		DRETURN_ARG("ERR: invalid board\n");
		return -1;
	}

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//Clear accumulator
	num_moves = 0;
	//for: every board position
	for (t = 0;t < this -> g_board.size();t++)
	{
		//if the board position is empty increase the accumulator
		num_moves += (this -> g_board[t] == User::Pieces::EMPTY);
	}	//end for: every board position

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN_ARG("number of valid moves: %d\n", num_moves);

	return num_moves;	//OK
}	//end method: get_num_moves | void

/****************************************************************************
*****************************************************************************
**	TESTERS
*****************************************************************************
****************************************************************************/

/****************************************************************************
**	Public Method
**	is_valid | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
****************************************************************************/

bool Tris::is_valid( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	bool f_ret;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();
	//valid by default
	f_ret = true;

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//if: board vector is destroyed
	if (this -> g_board.empty() == true)
	{
		//Invalid
		f_ret = false;
	}

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN_ARG((f_ret)?("valid\n"):("invalid\n"));

	return f_ret;	//OKOverload assignment operator
}	//end method: is_valid | void

/****************************************************************************
**	Public Tester
**	get_victor | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Get victor of the game. EMPTY means no one won. if EMPTY when valid move are 0 means DRAW.
****************************************************************************/

Pieces Tris::get_victor( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//Counters
	unsigned int t;
	unsigned int tr, tc;
	unsigned int tri, tci;
	unsigned int cnt_win;
	//memory of previously scanned piece
	Pieces mem;
	//Number of search pattern
	const int num_patterns = 6;
	//Number of dimensions
	const int num_dimensions = 4;
	//Scan pattern. Identify how to scan
	const array<const array<int, num_dimensions>, num_patterns> scan_pattern =
	{ {
		{ +1, +0, +0, +1 },					//Horizontal scan.
		{ +0, +1, +1, +0 },					//Vertical scan.
		{ +1, +0, +1, +1 },					//Half of Descending Diagonal scan.
		{ +0, +1, +1, +1 },					//Other Half of Descending Diagonal scan.
		{ +1, +0, -1, +1 },					//Half of Ascending Diagonal scan.
		{ +0, +1, -1, +1 },					//Other half Ascending Diagonal scan.
	} };

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

		///--------------------------------------------------------------------------
		///	WIN SCANNER
		///--------------------------------------------------------------------------
		//	General algorithm that finds a line of a given length of same symbols
		//	inside a matrix in 8-Connect

	//for: every scan pattern
	for (t = 0;t < num_patterns;t++)
	{
		//Initialize first scan dimension
		tr = 0;
		tc = 0;
		//while: I'm not done scanning the outer dimension and I have yet to find a winner
		while ( ((tr < this -> g_board_rows) && (tc < this -> g_board_cols)) )
		{
			//Initialize inner dimension scan
			tri = tr;
			tci = tc;
			//Initialize victor scan
			cnt_win = 0;
			mem = this -> at(tri, tci);
			//while: I'm not done scanning the inner dimension  and I have yet to find a winner
			while ( ((tri < this -> g_board_rows) && (tci < this -> g_board_cols)) )
			{
				//cout << tr << tc << tri << tci << "\n";
				///Count the line length of equal symbols in this dimension
				//if: piece match with previously scanned piece
				if (mem == this -> at(tri, tci))
				{
					//increase line length
					cnt_win++;
				}
				//reset line length to 1. match is with current piece only
				else
				{
					cnt_win = 1;
				}
				//update memory
				mem = this -> at(tri, tci);
				///Detect victory line
				//if: a long enough line of valid symbols is found
				if ((mem != User::Pieces::EMPTY) && (cnt_win >= g_win_line_length))
				{
					//cout << "winner: " << piece_to_char(mem) << "\n";
					DRETURN_ARG("winner detected: %c\n", piece_to_char(mem));
					//return the winning piece
					return mem;
				}

				//advance scan of the inner dimension according to the scan pattern
				tri += scan_pattern[ t ][ 2 ];
				tci += scan_pattern[ t ][ 3 ];
			}	//while: I'm not done scanning the inner dimension

			//advance scan of the outer dimension according to the scan pattern
			tr += scan_pattern[ t ][ 0 ];
			tc += scan_pattern[ t ][ 1 ];
		}	//end while: I'm not done scanning the dimension
	} //end for: every scan pattern

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN_ARG("Result is a draw\n");

	return User::Pieces::EMPTY;	//Draw
}	//end method: get_victor | void

/****************************************************************************
**	Public Getter
**	get_victory_value | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Calculate the value a victory would have in this position.
**	early victories are worth more because they have more end-leaves.
**	The value of a victory is the number of leves at the bottom of the tree it would generate
**	moves left		|	0	1	2	3	4	5	6	7		8		9
*	victory value	|	1	1	2	6	24	120	720	5040	40320	362880
****************************************************************************/

int Tris::get_victory_value( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//Number of moves left to fill the board
	int moves_left;
	//value of the victory from this position
	int value;
	//Precalculate the factorial for all possible move left
	const static array<int, 10> factorial = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//calculate number of moves left from this board position
	moves_left = this -> get_num_moves();
	//if: invalid number of moves
	if (moves_left > 9)
	{
		DRETURN_ARG("ERR: bad number of moves left\n");
		return -1;	//FAIL
	}
	//The value of a victory is the number of leves at the bottom of the tree it would generate
	value = factorial[ moves_left ];

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN_ARG("Victory value: %d\n", value);

	return value;	//OK
}	//end method: get_victory_value | void

/****************************************************************************
**	Public Tester
**	is_finished | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**		TRUE: finished
**		FALSE: ongoing
**	DESCRIPTION:
**	is the game finished?
**	the game is finished if a player has won or if there are no moves left
****************************************************************************/

bool Tris::is_finished( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//if: there are moves left and a player didn't win
	if ((this -> get_victor() == User::Pieces::EMPTY) && (this -> get_num_moves() > 0))
	{
		DRETURN_ARG("Game ongoing\n");
		return false;
	}

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN_ARG("Game finished\n");
	return true;
}	//end method: is_finished | void

/****************************************************************************
*****************************************************************************
**	PUBLIC METHODS
*****************************************************************************
****************************************************************************/

/****************************************************************************
**	Public Method
**	generate_moves | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	generate a board for every valid board position
**	I show the board in two cases.
**		when it's the last leaf (a victor has been decided)
**		when all moves from this position have been accounted for
****************************************************************************/

bool Tris::generate_moves( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//counter
	unsigned int t, ti, index;
	//number of valid moves from this board position
	int num_valid_moves;
	//return
	bool f_ret;
	//Pointer to tris board
	User::Tris *leaf;
	//temp piece
	User::Pieces piece;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER_ARG("%p\n", (void *)this);
	//if move vector already exist
	if (this -> g_moves.empty() == false)
	{
		DRETURN_ARG("ERR: move vector already exist\n");
		return true;	//FAIL
	}

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	//Compute number of valid moves from this board position
	num_valid_moves = this -> get_num_moves();

		///--------------------------------------------------------------------------
		///	CHECK VICTORY
		///--------------------------------------------------------------------------

	//Return true if game is finished
	if (this -> is_finished() == true)
	{
		//detect who the winner was. EMPTY means the game was a draw
		piece = this -> get_victor();
		//A win in move 5 is worth more than a win in move 9. All free positions after the move would lead to victory as well.
		index = this -> get_victory_value();
		//if: failed to get a valid victory value
		if (index < 0)
		{
			DRETURN_ARG("ERR: failed to get a valid victory value: %d\n", index );
			return true; //fail
		}
		//increment the winner counter by all full boards from this position
		this -> g_cnt_win[ piece ] += index;
		//the number of boards is the sum of all wins
		this -> g_num_boards += index;
		//counts the actual number of board configurations in the tree structure
		this -> g_num_leaves += 1;
		//This is the last leaf in the branch
		this -> show_board();
		//This leaf is finished and won't spawn any more moves
		DRETURN_ARG("Game finished with winner: %c\n", piece_to_char(piece));
		return false; //OK
	}

		///--------------------------------------------------------------------------
		///	GENERATE NEXT MOVES
		///--------------------------------------------------------------------------

	//if: there is at least one valid move from this board position
	if (num_valid_moves > 0 )
	{
		//Create moves vector. This constructs all boards
		this -> g_moves = vector<Tris>(num_valid_moves, User::Tris() );

		//Clear index ->
		index = 0;
		//for: every possible board position
		for (t = 0;t < User::Tris::g_board_size;t++)
		{
			//If: I can make a move here
			if (this -> g_board[t] == User::Pieces::EMPTY)
			{
				//link the board
				leaf = &(this -> g_moves[ index ]);
				//link the father of the leaf
				leaf -> father = this;
				//DEBUG
				DPRINT("generating move: %d of board: %p as board: %p\n", index, (void *)this, (void *)leaf );
				//copy current board position inside the leaf
				leaf -> copy( this );
				//if: somehow the leaf already has a move tree (BUG)
				if (leaf -> g_moves.empty() ==false)
				{
					DRETURN_ARG("ERR: move vector is not empty after copy\n");
					return true;
				}
				//Play move. The active player move in the generated position
				leaf -> g_board[ t ] = this -> g_next_player;
				//The move pass to the opponent
				leaf -> g_next_player = User::Tris::get_opponent( this -> g_next_player );
				//Recursively ask the leaf to play all moves from that position
				f_ret = leaf -> generate_moves();
				//HERE: when generate moves return, all the counters of the leaves are filled.
				//Accumulate the leaf counters in the father leaf (this board)
				//for: every victory counter. one for every piece
				for (ti = 0;ti < User::Pieces::NUM_PIECES;ti++)
				{
					//Accumulate the victories scored by the piece in the father leaf
					this -> g_cnt_win[ti] += leaf -> g_cnt_win[ti];
				}
				//if: failed to generate moves
				if (f_ret == true)
				{
					DRETURN_ARG("ERR: failed to generate moves\n");
					return true;
				}
				//Advance to next move
				index++;
			}	//end if: I can make a move here
		}	//end for: every possible board position

		///Compute number of boards (final configurations)
		//clear accumulator
		ti = 0;
		//for: each win
		for (t = 0;t < User::Pieces::NUM_PIECES;t++)
		{
			ti += this -> g_cnt_win[t];
		}
		//Save total number of boards
		this -> g_num_boards = ti;

		///Compute number of leaves
		//clear accumulator (i must count the father itself when counting the number of leaves)
		ti = 1;
		//for each leaf
        for (t = 0;t < this -> g_moves.size();t++)
        {
			//accumulate the total number of leaves spawning from the leaf
			ti += this -> g_moves[t].g_num_leaves;
        }
        //Save number of leaves
        this -> g_num_leaves = ti;

        ///Debug
		//All moves from this position have been accounted for
		this -> show_board();
	} //end if: there is at least one valid move from this board position
	//this board position is the end
	else
	{
		DPRINT("End of the line\n");
	}


	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN();

	return false;	//OK
}	//end method: generate_moves | void

/****************************************************************************
**	Public Method
**	save | string
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Save on file the tree structure of the game with all related stats.
**	Sorted first by number of draws, than by number of moves.
**	This output is meant to be used to train a neural network
****************************************************************************/

bool Tris::save( string filename )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//counter
	unsigned int t, ti;
	//total number of board configurations
	int num_boards;
	//Temp tris statistic
	User::Tris_stats tmp;
	//Vector filled with the statistics of the game
	vector<User::Tris_stats> stats;
	//Output file
	ofstream out;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	//Fetch total number of board configurations in the tree structure
	num_boards = this -> g_num_leaves;

	cout << "Total number of boards: " << num_boards << "\n";

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

		///--------------------------------------------------------------------------
		///	TRIS STATS
		///--------------------------------------------------------------------------

	///Initialize stat vector
	//Initialize vector on total number of games of the parent class
	stats = vector<User::Tris_stats>( num_boards );
	//if: vector creation failed
	if (stats.empty() == true)
	{
		cerr << "Unable to create stat vector\n";
		return true;	//fail
	}
	//fill the stat vector. recursively calls itself to explore the whole tree (simple but stack heavy implementation)
	this -> fill_stat_vector( stats, 0 );

		///--------------------------------------------------------------------------
		///	SORT
		///--------------------------------------------------------------------------

	//sort by win rate O decreasing
	//	highest priority is number ofmoves
	//	second priority is winrate of O
	//	third priority is winrate of X
	sort
	(
		stats.begin(),
		stats.end(),
		//Use a lambda to make my custom compare function
		[](User::Tris_stats a, User::Tris_stats b)
		{
			//if same number of moves
			if (a.num_moves == b.num_moves)
			{
				//if same winrate O
				if (a.rate[0] == b.rate[0])
				{
					//sort by decreasing winrate X
					return (a.rate[1] > b.rate[1]);
				}
				//sort by decreasing winrate O
				return (a.rate[0] > b.rate[0]);
			}
			//sort by increasing number of moves
			return (a.num_moves < b.num_moves);
		}
	);

		///--------------------------------------------------------------------------
		///	SAVE
		///--------------------------------------------------------------------------

	//open file
	out.open( filename );
	//check
	if (out.is_open() == false)
	{
		cerr << "Unable to open save file: " << filename << "\n";
		return true;	//fail
	}
	//Legend
	out << "//Tris game statistic\n";
	out << "//number of boards\n";
	out << stats.size() << "\n";
	out << "//Structure\n";
	out << "//&int[1] &<&char[9]&> &int[4]\n";
	//for every entry
	for (t = 0;t < stats.size();t++)
	{
		//fetch entry
		tmp = stats[t];
		//Number of moves done in this board configuration
		out << tmp.num_moves << ",";
		//board configuration
		out << tmp.board << ",";
		out.precision(1);
		out.setf( out.fixed );
		//for every win rate
		for (ti = 0;ti < 2; ti++)
		{
			//print the value of the counter
			out << tmp.rate[ ti ] << ",";
		}
		//for every counter
		for (ti = 0;ti < 4; ti++)
		{
			//print the value of the counter
			out << tmp.cnt_win[ ti ] << ",";
		}

		//next entry
		out << "\n";
	}
	//Close file
	out.close();

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------



	return false;	//OK
}	//end method: save | string

/****************************************************************************
**	Public Method
**	show_board | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Show the content of the board
****************************************************************************/

bool Tris::show_board( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//counters
	unsigned int t, ti;
	//temp piece
	Pieces p;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER_ARG("%p\n", (void *)this);
	//if: invalid class
	if (this -> is_valid() == false)
	{
		DRETURN_ARG("ERR: invalid\n");
		return true;	//FAIL
	}

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------


	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------


	p =  this -> g_next_player;
	DPRINT("next turn: %c\n", piece_to_char(p));
	#ifdef _ENABLE_COUT_BOARD
	cout << "next turn: " << piece_to_char(p) << "\n";
	#endif
	//for every row
	for (t = 0;t < User::Tris::g_board_rows;t++)
	{
		if (t != 0)
		{
			DPRINT("-----------\n");
			#ifdef _ENABLE_COUT_BOARD
			cout << "\n" << "-----------\n";
			#endif
		}
		//for every col
		for (ti = 0;ti < User::Tris::g_board_cols;ti++)
		{
			//fetch piece
			p = this -> g_board[ t *User::Tris::g_board_cols +ti ];

			if (ti != 0)
			{
				DPRINT_NOTAB(" | ");
				#ifdef _ENABLE_COUT_BOARD
				cout << " | ";
				#endif
			}
			else
			{
				DPRINT(" ");
				#ifdef _ENABLE_COUT_BOARD
				cout << " ";
				#endif
			}
			DPRINT_NOTAB("%c", piece_to_char( p ));
			#ifdef _ENABLE_COUT_BOARD
			cout << piece_to_char( p );
			#endif
		}	//end for every cols
		DPRINT_NOTAB("\n");
	}	//end for every row
	#ifdef _ENABLE_COUT_BOARD
	cout << "\n\n";
	#endif

	//initialize accumulator
	ti = 0;
	DPRINT("Winners | ");
	//for: every victory counter
	for (t = 0;t < (unsigned int)User::Pieces::NUM_PIECES;t++)
	{
		if (t == (unsigned int)User::Pieces::EMPTY)
		{
			DPRINT_NOTAB("draws: %d | ", this -> g_cnt_win[ t ] );
		}
		else
		{
			DPRINT_NOTAB("wins <%c>: %d | ", User::Tris::piece_to_char((Pieces)t), this -> g_cnt_win[ t ] );
		}
		//Accumulate total number of victories
		ti += this -> g_cnt_win[ t ];
	}
	DPRINT_NOTAB("\n");
	DPRINT("total: %d | total possibilities: %d | total leaves: %d\n", ti, this -> g_num_boards, this -> g_num_leaves);

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN();

	return false;	//OK
}	//end method: show_board | void

/****************************************************************************
*****************************************************************************
**	PUBLIC STATIC METHODS
*****************************************************************************
****************************************************************************/

/****************************************************************************
**	Public Static Method
**	get_opponent | Pieces
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Get opponent of a given player
****************************************************************************/

Pieces Tris::get_opponent( Pieces player )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//return value
	Pieces ret;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//If Circle
	if (player == User::Pieces::CIRCLE)
	{
		//opponent is cross
		ret = User::Pieces::CROSS;
	}
	//If cross
	else if (player == User::Pieces::CROSS)
	{
		//opponent is Circle
		ret = User::Pieces::CIRCLE;
	}
	//default
	else
	{
		//Calculate default player
		ret = User::Pieces::EMPTY;
	}

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN_ARG("Opponent of %c is %c\n", piece_to_char( player ), piece_to_char( ret ));

	return ret;	//OK
}	//end method: get_opponent | Pieces

/****************************************************************************
**	Public Static Method
**	piece_to_char | Pieces
*****************************************************************************
**	PARAMETER:
**	RETURN:
**		NUM_PIECES means could not convert
**	DESCRIPTION:
**	convert from chat to piece
****************************************************************************/

inline Pieces Tris::char_to_piece( char c )
{
	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//convert from piece to its character rapresentation
	return (((c) == ' ')?(User::Pieces::EMPTY):(((c) == 'O')?(User::Pieces::CIRCLE):(((c) == 'X')?(User::Pieces::CROSS):(User::Pieces::NUM_PIECES))));
}	//end method: piece_to_char | Pieces

/****************************************************************************
**	Public Static Method
**	piece_to_char | Pieces
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	convert from piece to its character rapresentation
****************************************************************************/

inline char Tris::piece_to_char( Pieces piece )
{
	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//convert from piece to its character rapresentation
	return (((piece) == User::Pieces::EMPTY)?(' '):(((piece) == User::Pieces::CIRCLE)?('O'):(((piece) == User::Pieces::CROSS)?('X'):('?'))));
}	//end method: piece_to_char | Pieces

/****************************************************************************
*****************************************************************************
**	PRIVATE METHODS
*****************************************************************************
****************************************************************************/

/****************************************************************************
**	Private Method
**	init | void
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Initialize Tris class
**	>empty board position
**	>no moves tree
**	>Circle as starting player
****************************************************************************/

bool Tris::init( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//counter
	unsigned int t;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	//Create board position vector
	this -> g_board = vector<Pieces>(User::Tris::g_board_size, User::Pieces::EMPTY );
	//Virgin board. Next player is CIRCLE. CIRCLE start first
	this -> g_next_player = User::Pieces::CIRCLE;

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//for every piece
	for (t = 0;t < User::Pieces::NUM_PIECES;t++)
	{
		//Initialize the victory counters
		this -> g_cnt_win[ t ] = 0;
	}
	//initialize tree profiling counters
	this -> g_num_leaves = 0;
	this -> g_num_boards = 0;
	//initialize reference to the father of this leaf
	this -> father = nullptr;

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN();

	return false;	//OK
}	//end method: init | void

/****************************************************************************
**	Private Method
**	get_board_index | Tris *
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	get index of the leaf inside the moves vector of the structure. -1 means it's not there or the move vector does not exist
****************************************************************************/

int Tris::get_board_index( Tris *leaf )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//index of the leaf inside the move vector
	unsigned int index;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();
	//if: bad argument
	if (leaf == NULL)
	{
		DRETURN_ARG("ERR: bad input pointer\n");
		return -1; //Fail
	}
	//if: this board does not have a move vector
	if (this -> g_moves.empty())
	{
		DRETURN_ARG("ERR: this board does not have a move vector\n");
		return -1; //Fail
	}

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	//init search
	index = 0;
	//while: I haven't ran out of entries
	while (index < this -> g_moves.size())
	{
		//if: I haven't found the leaf
		if (leaf != &(this -> g_moves[index]))
		{
			DRETURN_ARG("leaf found with index: %d\n", index);
			return index;
		}
		//next entry
		index++;
	}

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN_ARG("ERR: Failed to find leaf in move vector\n");

	return -1;	//Fail
}	//end method: get_board_index | Tris *

/****************************************************************************
**	Public Method
**	fill_stat_vector | vector, int
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Recursively explore the tree and fill the stat vector
****************************************************************************/

int Tris::fill_stat_vector( vector<User::Tris_stats> &stat, int index )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	//counter
	unsigned int t;
	//number of moves of this board
	int num_moves;
	//Temp tris statistic
	User::Tris_stats tmp;

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER_ARG("board: %p, entry: %d\n", (void *)this, index);

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

		///--------------------------------------------------------------------------
		///	COMPUTE ENTRY
		///--------------------------------------------------------------------------

	///Fill moves
	//Get moves left
	num_moves = this -> get_num_moves();
	//Calculate moves done
	num_moves = User::Tris::g_board_size -num_moves;
	//save number of moves
	tmp.num_moves = num_moves;
	///Fill board position
	//for every board position
	for (t = 0; t < User::Tris::g_board_size;t++)
	{
		//fill the board position with characters
		tmp.board[t] = User::Tris::piece_to_char( this -> g_board[ t ] );
	}
	//add terminator
	tmp.board[t] = '\0';
	///Fill counters
	//total final board configurations from this board position
	tmp.cnt_win[ 0 ] = this -> g_num_boards;
	//for every player
	for (t = 0;t < User::Pieces::NUM_PIECES;t++)
	{
		//save win for that player
		tmp.cnt_win[ t +1 ] = this -> g_cnt_win[ t ];
	}
	///Compute win rate
	tmp.rate[0] = 100.0 * tmp.cnt_win[2] /tmp.cnt_win[0];
	tmp.rate[1] = 100.0 * tmp.cnt_win[3] /tmp.cnt_win[0];

		///--------------------------------------------------------------------------
		///	ADD ENTRY
		///--------------------------------------------------------------------------

	//Add entry to the stat vector and advance to next entry
	stat[ index ] = tmp;

		///--------------------------------------------------------------------------
		///	EXPLORE ALL MOVES
		///--------------------------------------------------------------------------

	//for every move inside the move vector
	for (t = 0; t < this -> g_moves.size();t++)
	{
		//advance to the next entry
		index++;
		//recursively call the fill function on the next leaf
		index = this -> g_moves[t].fill_stat_vector( stat, index );
	}


	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN_ARG( "num_moves: %d, board <%s>, tot: %d, draw: %d, win <O>: %d, win <X>: %d, rate <O>%2.1f, rate <X>%2.1f,\n", tmp.num_moves, tmp.board, tmp.cnt_win[0], tmp.cnt_win[1], tmp.cnt_win[2], tmp.cnt_win[3], tmp.rate[0], tmp.rate[1] );

	return index;	//OK
}	//end method: fill_stat_vector | vector, int

/****************************************************************************
**	Public Method
**
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
****************************************************************************/

bool Tris::dummy( void )
{
	///--------------------------------------------------------------------------
	///	STATIC VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	LOCAL VARIABILE
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	CHECK
	///--------------------------------------------------------------------------

	//Trace Enter main
	DENTER();

	if (false)
	{
		std::cerr << __FUNCTION__ << ":\n";
		return true; //Fail
	}

	///--------------------------------------------------------------------------
	///	INITIALIZATIONS
	///--------------------------------------------------------------------------


	///--------------------------------------------------------------------------
	///	BODY
	///--------------------------------------------------------------------------

	///--------------------------------------------------------------------------
	///	FINALIZATIONS
	///--------------------------------------------------------------------------

	//Trace Return from main
	DRETURN();

	return false;	//OK
}	//end method:

/****************************************************************************
**	NAMESPACES
****************************************************************************/

} //End Namespace
