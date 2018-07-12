/*****************************************************************************/
/*!
* \file   Sudoku.cpp
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: CS280
* \par    Assignment #3
* \date   10/16/14
* 
* \brief
* This file contains the implementation of the following functions for the
* Sudoku C++ assignment.
* 
* Hours spent on this assignment: 10
* 
* Specific portions that gave you the most trouble:
*/
/*****************************************************************************/

#include "Sudoku.h"
#include <iostream>

/*****************************************************************************/
/*!
* Constructor.
*
* \author	Louis.coyleii
* \date 10/16/14
*
*
* \param basesize Size of each square for the board.
* \param stype Type of the symbol for the board (letters or numbers).
* \param SUDOKU_CALLBACK Whether to callback with constructor information.
*
*/
/*****************************************************************************/

Sudoku::Sudoku(int basesize, SymbolType stype, SUDOKU_CALLBACK callback){
  boardlength = basesize * basesize;

  if (stype == SYM_NUMBER){
    firstelement = '1';
    lastelement = '9';
  }
  else{
    firstelement = 'A';
    if (boardlength == 16)
      lastelement = 'P';
    else
      lastelement = 'Y';
  }

  info = callback;

  stats = SudokuStats();
  stats.basesize = basesize;

  for (int i = 0; i < 3; ++i)
    dupes[i] = -1;

}

/*****************************************************************************/
/*!
* Destructor.
*
* \author	Louis.coyleii
* \date 10/16/14
*
*/
/*****************************************************************************/

Sudoku::~Sudoku(){
}

/*****************************************************************************/
/*!
* Sets up the board with the passed in values.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param values Symbols (values) for the board.
* \param size Size of the board to set up.
*                            
*/
/*****************************************************************************/

void Sudoku::SetupBoard(const char *values, int size){
  boardmaxpos = size;

  for(int i = 0; i < size; ++i)
  {
    char value = *values++;
    if (value == '.')
      board.push_back(' ');
    else
      board.push_back(value);
  }
}

/*****************************************************************************/
/*!
* Starts the search for the solution to the board.
*
* \author	Louis.coyleii
* \date 10/16/14
*
*/
/*****************************************************************************/

void Sudoku::Solve(){

  if (callback(MSG_ABORT_CHECK, 0, firstelement))
    return;

  callback(MSG_STARTING, 0, firstelement);

  place_value(0, firstelement);
}

/*****************************************************************************/
/*!
* Inserts the value at the index.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
* \param value Symbol (value) for the cell.
*
*/
/*****************************************************************************/

void Sudoku::insert_into_board(int index, char value){
  board[index] = value;
  stats.moves++;
  stats.placed++;
}

/*****************************************************************************/
/*!
* Recursively attemps to place the value at the index.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
* \param value Symbol (value) for the cell.
*                            
*/
/*****************************************************************************/

void Sudoku::place_value(int index, char value){
  if (callback(MSG_ABORT_CHECK, index, value))
    return;
  
  // BASE CASE //
  if(game_solved())
  {
    callback(MSG_FINISHED_OK, index, value);
    return;
  }
    //Move to a new empty space//
    while (board[index] != ' ')
    {
      ++index;
    }
    
    for(value = firstelement; value <= lastelement; value++)
    {
      if(!is_in_conflict(index, value))
      {
        //place into board//
        insert_into_board(index, value);
        callback(MSG_PLACING, index, value);
        //recursive call//
        place_value(index+1, firstelement);
        //if it returns here that means it was in conflict, or actually that the game was solved//
        //return if the game is solved//
        if(game_solved())
        {
          callback(MSG_FINISHED_OK, index, value);
          return;
        }
        //remove the entry if game was in conflict//
        remove_entry(index, value);
      }
    }
    //if the board is in conflict//
    //backtrack//
    stats.backtracks++;
    return;
    //to the address after the calling code//
     
  callback(MSG_FINISHED_FAIL, index, value);
}

/*****************************************************************************/
/*!
* Returns the row of the index.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
*                 
* \return unsigned The index of the row.                           
*
*/
/*****************************************************************************/

int Sudoku::index_to_row(int index) const{
  return index / (boardlength);
}

/*****************************************************************************/
/*!
* Returns the column of the index.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
*            
* \return unsigned The index of the column.                           
*
*/
/*****************************************************************************/

int Sudoku::index_to_col(int index) const{
  return index % boardlength;
}

/*****************************************************************************/
/*!
* Returns the index of the row or column.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param row The row number to convert.
* \param col The col number to convert.                            
*
* \return unsigned The index of the (row,col).
* 
*/
/*****************************************************************************/

int Sudoku::row_col_to_index(int row, int col) const{
  return (row * boardlength) + col;
}

/*****************************************************************************/
/*!
* Returns whether or not the value at index is allowable.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
*              
* \return bool Whether or not the value at index is allowable.
*                            
*/
/*****************************************************************************/

bool Sudoku::is_in_conflict(int index, char value) const{
  if (dupe_in_col(index, value) != -1)
    return true;
  else if (dupe_in_row(index, value) != -1)
    return true;
  else if (dupe_in_sqr(index, value) != -1)
    return true;
  else
    return false;
}

/*****************************************************************************/
/*!
* Returns whether or not the value at index is dupe in the row.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
*
* \return bool Whether or not the value at index is dupe in the row.
*
*/
/*****************************************************************************/

int Sudoku::dupe_in_row(int index, char value) const{
  int row = index_to_row(index);
  int rowstart = row_col_to_index(row, 0);
  int rowend = rowstart + boardlength;
  for (int i = rowstart; i < rowend; ++i){
    if (i != index && value == board[i])
      return i;
  }

  return -1;
}

/*****************************************************************************/
/*!
* Returns whether or not the value at index is dupe in the column.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
*
* \return bool Whether or not the value at index is dupe in the column.
*
*/
/*****************************************************************************/

int Sudoku::dupe_in_col(int index, char value) const{
  int col = index_to_col(index);
  int colstart = row_col_to_index(0, col);
  int colend = colstart + boardlength * (boardlength - 1);
  for (int i = colstart; i < colend; i += boardlength){
    if (i != index && value == board[i])
      return i;
  }

  return -1;
}

/*****************************************************************************/
/*!
* Returns whether or not the value at index is dupe in the square.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
*
* \return bool Whether or not the value at index is dupe in the square.
*
*/
/*****************************************************************************/

int Sudoku::dupe_in_sqr(int index, char value) const{
  int sqrstart = find_sqr_start(index);
  int i = sqrstart;
  int sqrend = sqrstart + (boardlength*2 + stats.basesize);
  while (i < sqrend){
    if (i != index && value == board[i])
      return i;
    // if at the last element in the square
    if ((i + 1) % stats.basesize == 0)
      // make next comparison to the first element in the next row of sqr
      i += boardlength - (stats.basesize - 1);
    else
      ++i;
  } 

  return -1;
}

/*****************************************************************************/
/*!
* Returns the start of the square that the passed index is in.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
*
* \return int The index of the start of the square that index is in.
*
*/
/*****************************************************************************/

int Sudoku::find_sqr_start(int index) const{
  // determine the first column of the sqr index is in
  int sqrfirstcol = index_to_col(index - (index % stats.basesize));
  int row = index_to_row(index);
  // determine the first row of the sqr the index is in
  int sqrfirstrow = row - (row % stats.basesize);
  // return the index of the first (row,column);
  return row_col_to_index(sqrfirstrow, sqrfirstcol);
}

/*****************************************************************************/
/*!
* Returns whether or not the value at index is the final position.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.
*              
* \return bool Whether or not the index is the last position on the board.
*                            
*/
/*****************************************************************************/

bool Sudoku::is_final_position(int index) const{
  return index == (boardmaxpos - 1);
}

/*****************************************************************************/
/*!
* Adds the index to the list of duplicates.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param index Position of the cell.   
*                                         
*/
/*****************************************************************************/

void Sudoku::update_duplicates(int index){
  dupes[0] = dupe_in_row(index, board[index]);
  dupes[1] = dupe_in_col(index, board[index]);
  dupes[2] = dupe_in_sqr(index, board[index]);
  if (dupes[2] == dupes[0] || dupes[2] == dupes[1])
    dupes[2] = -1;
}

/*****************************************************************************/
/*!
* Calls the callback function for the index and value with the message.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param message The message to send with the callback.
* \param index Position of the cell.
* \param value Symbol (value) for the cell.
*                         
* \return bool                         
*/
/*****************************************************************************/

bool Sudoku::callback(MessageType message, int index, char value){

  // find all the dupes for this index and assign to the array
  update_duplicates(index);


  return info(*this, board.c_str(), message, stats.moves, stats.basesize, index, value, dupes);
}

/*****************************************************************************/
/*!
* Gets the board, for debugging with the driver.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \return	char* The current board.
*/
/*****************************************************************************/
  // For debugging with the driver
const char* Sudoku::GetBoard() const{
  return board.c_str();
}

/*****************************************************************************/
/*!
* Returns the current stats for the board.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \return	SodokuStats The current stats for the board.
*/
/*****************************************************************************/

Sudoku::SudokuStats Sudoku::GetStats() const{
  return stats;
}

/*****************************************************************************/
/*!
* Returns whether or not the game has been solved.
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \return	bool Whether or not the game has been solved.
*/
/*****************************************************************************/
bool Sudoku::game_solved() const
{
  for (int i = 0; i < boardmaxpos; i++)
  {
    if(board[i] == ' ')
      return false;
    if(is_in_conflict(i, board[i]))
      return false;
  }    
  return true;
  /*if(!is_in_conflict(index) && is_final_position(index) && board[index] != ' ')
    return true;
  else
    return false;*/
}

/*****************************************************************************/
/*!
* Removes an entry from the board
*
* \author	Louis.coyleii
* \date 10/16/14
*
* \param	index The index of the entry to remove from the board.
*/
/*****************************************************************************/
void Sudoku::remove_entry(int index, char value) {
  board[index] = ' ';
  stats.placed--;
  callback(MSG_REMOVING, index, value); 
}
    

