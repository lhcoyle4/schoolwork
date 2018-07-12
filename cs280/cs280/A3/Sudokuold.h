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
    typedef bool (*CALLBACK)
      (const Sudoku& sudoku, // the gameboard object itself
       const char *board,    // one-dimensional array of symbols
       MessageType message,   // type of message
       size_t move,           // the move number
       unsigned basesize,    // 3, 4, 5, etc. (for 9x9, 16x16, 25x25, etc.)
       unsigned index,       // index of current cell
       char value,           // symbol (value) in current cell
       int *dup_indexes      // index of each duplicate sorted from lowest
                              // index to highest. -1 means no conflict.
                              // max of 3 duplicates.
      );

    struct SudokuStats
    {
      unsigned basesize; // 3, 4, 5, etc.
      unsigned placed;   // the number of values the algorithm has placed 
      size_t moves;      // total number of values that have been tried
      size_t backtracks; // total number of times the algorithm backtracked
      SudokuStats() : basesize(0), placed(0), moves(0), backtracks(0) {}
    };

      // Constructor
    Sudoku(int basesize, SymbolType stype = SYM_NUMBER, CALLBACK callback = 0);

      // Destructor
    ~Sudoku();

      // The client (driver) passed the board in the values parameter
    void SetupBoard(const char *values, size_t size);

      // Once the board is setup, this will start the search for the solution
    void Solve();

      // For debugging with the driver
    const char *GetBoard() const;
    SudokuStats GetStats() const;

  private:
    SudokuStats stats;
    unsigned boardlength;
    size_t boardmaxpos;
    std::string board;
    char firstelement;
    char lastelement;
    int dupes[3];
    unsigned blanks[625];
    CALLBACK info;

    void place_value(unsigned index, char value);
    unsigned index_to_row(unsigned index) const;
    unsigned index_to_col(unsigned index) const;
    unsigned row_col_to_index(unsigned row, unsigned col) const;
    bool is_in_conflict(unsigned index) const;
    int dupe_in_row(unsigned index) const;
    int dupe_in_col(unsigned index) const;
    int dupe_in_sqr(unsigned index) const;
    unsigned find_sqr_start(unsigned index) const;
    bool is_final_position(unsigned index) const;
    void update_duplicates(unsigned index);
    void insert_into_board(unsigned index, char value);
    bool callback(MessageType message, unsigned index, char value);
};

#endif  // SUDOKUH
