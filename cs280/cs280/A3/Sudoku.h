//---------------------------------------------------------------------------
#ifndef SUDOKUH
#define SUDOKUH
//---------------------------------------------------------------------------
#include <stddef.h> // size_t
#include <string>
#include <set>

class Sudoku
{
  public:
      // Used by the callback function 
    enum MessageType
    {
      MSG_STARTING,      // the board is setup, ready to go
      MSG_FINISHED_OK,   // finished and found a solution
      MSG_FINISHED_FAIL, // finished but no solution found
      MSG_ABORT_CHECK,   // checking to see if algorithm should continue
      MSG_PLACING,       // placing a symbol on the board
      MSG_REMOVING       // removing a symbol (back-tracking)
    };

      // 1-9 for 9x9, A-P for 16x16, A-Y for 25x25
    enum SymbolType {SYM_NUMBER, SYM_LETTER};

    const static char EMPTY_CHAR = ' ';

      // Implemented in the client and called during the search for a solution
    typedef bool (*SUDOKU_CALLBACK)
      (const Sudoku& sudoku, // the gameboard object itself
       const char *board,    // one-dimensional array of symbols
       MessageType message,  // type of message
       size_t move,          // the move number
       int basesize,         // 3, 4, 5, etc. (for 9x9, 16x16, 25x25, etc.)
       int index,            // index of current cell
       char value,           // symbol (value) in current cell
       int *dup_indexes      // index of each duplicate sorted from lowest
                             // index to highest. -1 means no conflict.
                             // max of 3 duplicates.
      );

    struct SudokuStats
    {
      int basesize;      // 3, 4, 5, etc.
      int placed;        // the number of values the algorithm has placed 
      size_t moves;      // total number of values that have been tried
      size_t backtracks; // total number of times the algorithm backtracked
      SudokuStats() : basesize(0), placed(0), moves(0), backtracks(0) {}
    };

      // Constructor
    Sudoku(int basesize, SymbolType stype = SYM_NUMBER, SUDOKU_CALLBACK callback = 0);

      // Destructor
    ~Sudoku();

      // The client (driver) passed the board in the values parameter
    void SetupBoard(const char *values, int size);

      // Once the board is setup, this will start the search for the solution
    void Solve();

      // For debugging with the driver
    const char *GetBoard() const;
    SudokuStats GetStats() const;
    

  private:
    SudokuStats stats;
    int boardlength;
    int boardmaxpos;
    std::string board;
    char firstelement;
    char lastelement;
    int dupes[3];
    SUDOKU_CALLBACK info;

    void place_value(int index, char value);
    int index_to_row(int index) const;
    int index_to_col(int index) const;
    int row_col_to_index(int row, int col) const;
    bool is_in_conflict(int index, char value) const;
    int dupe_in_row(int index, char value) const;
    int dupe_in_col(int index, char value) const;
    int dupe_in_sqr(int index, char value) const;
    int find_sqr_start(int index) const;
    bool is_final_position(int index) const;
    void update_duplicates(int index);
    void insert_into_board(int index, char value);
    void remove_entry(int index, char value); 
    bool game_solved() const;
    bool callback(MessageType message, int index, char value);
};

#endif  // SUDOKUH
