/**********************************************************************************
**	ENVIROMENT VARIABILE
**********************************************************************************/

#ifndef TRIS_H_
	#define TRIS_H_

/**********************************************************************************
**	GLOBAL INCLUDES
**********************************************************************************/

/**********************************************************************************
**	NAMESPACE
**********************************************************************************/

//Assign class to a namespace
namespace User
{

/**********************************************************************************
**	DEFINES
**********************************************************************************/

//#define _ENABLE_COUT_BOARD

/**********************************************************************************
**	MACROS
**********************************************************************************/

/**********************************************************************************
**	ENUMS
**********************************************************************************/

//Enumerate possible pieces in Tris.
enum _Pieces
{
	EMPTY,		//Empty board position
	CIRCLE,		//Circle is used by player circle. Circle always starts
	CROSS,		//Cross is the piece used by player cross. Cross is second
	NUM_PIECES	//with magic, this is the number of pieces in the structure
};

/**********************************************************************************
**	PROTOTYPE: CLASSES
**********************************************************************************/

/**********************************************************************************
**	PROTOTYPE: STRUCTURES
**********************************************************************************/

//board configuration and related statistics
struct _Tris_stats
{
	//Number of moves in this board configuration
	int num_moves;
	//Content of the board (character form)
	char board[10];
	//Counters for total branches from this board positions, and draws and wins for either sides
	int cnt_win[4];
	//winrate of two players
	double rate[2];
};

/**********************************************************************************
**	TYPEDEF
**********************************************************************************/

//Create a type based on possible Pieces
typedef enum _Pieces Pieces;
//create a type based on stats of a board configuration
typedef struct _Tris_stats Tris_stats;

/**********************************************************************************
**	PROTOTYPE: GLOBAL VARIABILES
**********************************************************************************/

/**********************************************************************************
**	PROTOTYPE: CLASS
**********************************************************************************/

/****************************************************************************
**	Class
**	Tris
*****************************************************************************
**	PARAMETER:
**	RETURN:
**	DESCRIPTION:
**	Describe a game of tris.
****************************************************************************/

class Tris
{
	//Visible to all
	public:
		///--------------------------------------------------------------------------
		///	CONSTRUCTORS
		///--------------------------------------------------------------------------

		//Empty constructor
		Tris( void );
		//Construct a new board copying a source board
		//Tris( User::Tris *source );

		///--------------------------------------------------------------------------
		///	DESTRUCTORS
		///--------------------------------------------------------------------------

		//Default destructor
		~Tris( void );

		///--------------------------------------------------------------------------
		///	SETTERS
		///--------------------------------------------------------------------------

		//copy the board configuration and player turn but not the move structure
		bool copy( User::Tris *source );
		//Set board position to given character configuration
		bool set_board( std::string str );

		///--------------------------------------------------------------------------
		///	GETTERS
		///--------------------------------------------------------------------------

		//Get the next player
		Pieces get_next_player( void );
		//Get the number of moves possible from this board position
		int get_num_moves( void );
		//Calculate the value a victory would have in this position. early victories are worth more because they have more end-leaves.
		int get_victory_value( void );

		///--------------------------------------------------------------------------
		///	TESTERS
		///--------------------------------------------------------------------------

		//Is the game valid
		bool is_valid( void );
		//Get victor of the game. EMPTY means no one won. if EMPTY when valid move are 0 means DRAW.
		Pieces get_victor( void );
		//is the game finished? TRUE: finished
		bool is_finished( void );

		///--------------------------------------------------------------------------
		///	OPERATORS
		///--------------------------------------------------------------------------

		//Overload assignment operator
		void operator = (User::Tris &source );
		//Access to a piece of the board
		Pieces &at( unsigned int r, unsigned int c );

		///--------------------------------------------------------------------------
		///	PUBLIC METHODS
		///--------------------------------------------------------------------------

		//Generate all possible moves from this board position and attach them to g_moves
		bool generate_moves( void );
		//Save on file the tree structure of the game with all related stats. Sorted first by number of draws, than by number of moves.
		bool save( std::string filename );
		//Show the board position
		bool show_board( void );

		///--------------------------------------------------------------------------
		///	PUBLIC STATIC METHODS
		///--------------------------------------------------------------------------

		//Get opponent of a given player
		static Pieces get_opponent( Pieces player );
		//convert from piece to its character
		static char piece_to_char( Pieces piece );
		//convert from chat to piece
		static Pieces char_to_piece( char c );

		///--------------------------------------------------------------------------
		///	PUBLIC VARS
		///--------------------------------------------------------------------------

		//Size of a tris board

		const unsigned int g_board_rows = 3;
		const unsigned int g_board_cols = 3;
		const unsigned int g_board_size = g_board_cols *g_board_rows;
		//How long a line must be to score a win. Line is in 8-Connect
		const unsigned int g_win_line_length = 3;

	//Visible to derived classes
	protected:
		///--------------------------------------------------------------------------
		///	PROTECTED METHODS
		///--------------------------------------------------------------------------

		///--------------------------------------------------------------------------
		///	PROTECTED VARS
		///--------------------------------------------------------------------------

	//Visible only inside the class
	private:
		///--------------------------------------------------------------------------
		///	PRIVATE METHODS
		///--------------------------------------------------------------------------

		//Initialize class
		bool init( void );
		//get index of the leaf inside the moves vector of the structure. -1 means it's not there or the move vector does not exist
		int get_board_index( Tris *leaf );
		//get the leaf immediately after the current leaf in the move vector fo the structure. NULL means there is not one or the leaf it's not there
		//Tris *get_next_leaf( Tris *leaf );

		//Recursively explore the tree and fill the stat vector
		int fill_stat_vector( std::vector<User::Tris_stats> &stat, int index );
		//Here so that i can easly copy the code.
		bool dummy( void );



		///--------------------------------------------------------------------------
		///	PRIVATE VARS
		///--------------------------------------------------------------------------

			///--------------------------------------------------------------------------
			///
			///--------------------------------------------------------------------------

		//Next player turn
		Pieces g_next_player;
		//Board position. A board position is a sequence of Pieces
		std::vector<Pieces> g_board;
		//vector of moves from this board position
		std::vector<Tris> g_moves;

			///--------------------------------------------------------------------------
			///
			///--------------------------------------------------------------------------

		//Reference to the parent structure
		Tris *father;
		//number of leaves this structure has
		int g_num_leaves;
		//Total number of complete boards from this board configuration
		int g_num_boards;
		//number of games won by each player. win by empty means draw. vector is size of the number of pieces
		int g_cnt_win[ User::Pieces::NUM_PIECES ];

};	//End Class:

/**********************************************************************************
**	NAMESPACE
**********************************************************************************/

} //End Namespace

#else
    #warning "Multiple inclusion of hader file"
#endif
