#include "defs.h"
#include <string.h>

const char temp[256] = START_FEN;

int set_fen(s_board *board, const char *fen)
{
  assert(board != NULL);
  assert(fen != NULL);
  
  if(strncmp(fen, "startpos", 8) == 0)
  {
    fen = temp;
  }
  
  int i;
  for(i = 0; i < 7; ++i)
  {
    board->combined[i] = 0;
  }
  board->colour[WHITE] = 0;
  board->colour[BLACK] = 0;
  
  board->ep = 0;
  
  board->castling[wKSC] = 0;
  board->castling[wQSC] = 0;
  board->castling[bKSC] = 0;
  board->castling[bQSC] = 0;
  
  /*
  int i, j;
  for(i = 0; i < 12; ++i)
  {
    board->num_pieces[i] = 0;
    for(j = 0; j < 10; ++j)
    {
      board->locations[i][j] = 0;
    }
  }
  */
  
  int n = 0, x = 63;
  while(fen[n] != ' ')
  {
    switch(fen[n])
    {
      case '/':
      {
        x++;
        break;
      }
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      {
        x -= fen[n] - '1'; // FIXME: fen[n] = '0';
        break;
      }
      case 'p':
      {
        board->combined[bP] ^= (uint64_t)1<<x;
        board->colour[BLACK] ^= (uint64_t)1<<x;
        break;
      }
      case 'n':
      {
        board->combined[KNIGHTS] ^= (uint64_t)1<<x;
        board->colour[BLACK] ^= (uint64_t)1<<x;
        break;
      }
      case 'b':
      {
        board->combined[BISHOPS] ^= (uint64_t)1<<x;
        board->colour[BLACK] ^= (uint64_t)1<<x;
        break;
      }
      case 'r':
      {
        board->combined[ROOKS] ^= (uint64_t)1<<x;
        board->colour[BLACK] ^= (uint64_t)1<<x;
        break;
      }
      case 'q':
      {
        board->combined[QUEENS] ^= (uint64_t)1<<x;
        board->colour[BLACK] ^= (uint64_t)1<<x;
        break;
      }
      case 'k':
      {
        board->combined[KINGS] ^= (uint64_t)1<<x;
        board->colour[BLACK] ^= (uint64_t)1<<x;
        break;
      }
      case 'P':
      {
        board->combined[wP] ^= (uint64_t)1<<x;
        board->colour[WHITE] ^= (uint64_t)1<<x;
        break;
      }
      case 'N':
      {
        board->combined[KNIGHTS] ^= (uint64_t)1<<x;
        board->colour[WHITE] ^= (uint64_t)1<<x;
        break;
      }
      case 'B':
      {
        board->combined[BISHOPS] ^= (uint64_t)1<<x;
        board->colour[WHITE] ^= (uint64_t)1<<x;
        break;
      }
      case 'R':
      {
        board->combined[ROOKS] ^= (uint64_t)1<<x;
        board->colour[WHITE] ^= (uint64_t)1<<x;
        break;
      }
      case 'Q':
      {
        board->combined[QUEENS] ^= (uint64_t)1<<x;
        board->colour[WHITE] ^= (uint64_t)1<<x;
        break;
      }
      case 'K':
      {
        board->combined[KINGS] ^= (uint64_t)1<<x;
        board->colour[WHITE] ^= (uint64_t)1<<x;
        break;
      }
      default:
      {
        break;
      }
    }
    n++;
    x--;
  }
  n += 1;
  
  if(fen[n] == 'w')
  {
    board->turn = WHITE;
  }
  else if(fen[n] == 'b')
  {
    board->turn = BLACK;
  }
  else
  {
    return -1;
  }
  n += 2;
  
  while(fen[n] != ' ' && fen[n] != '\0' && fen[n] != '\n')
  {
    switch(fen[n])
    {
      case 'K':
      {
        board->castling[wKSC] = 1;
        break;
      }
      case 'Q':
      {
        board->castling[wQSC] = 1;
        break;
      }
      case 'k':
      {
        board->castling[bKSC] = 1;
        break;
      }
      case 'q':
      {
        board->castling[bQSC] = 1;
        break;
      }
      case '-':
      {
        break;
      }
      default:
      {
        return -2;
      }
    }
    n++;
  }
  n++;
  
  if(fen[n] != '-')
  {
    int col = fen[n] - 'a';
    int row = fen[n+1] - '1';
    board->ep = (uint64_t)1<<(row*8 + 7 - col);
    n++;
  }
  n += 2;
  
  /*
  board->colour[WHITE] = board->combined[wP] | board->pieces[wN] | board->pieces[wB] |
                                board->pieces[wR] | board->pieces[wQ] | (board->colour[WHITE] & board->combined[KINGS]);
  
  board->colour[BLACK] = board->combined[bP] | board->pieces[bN] | board->pieces[bB] |
                                board->pieces[bR] | board->pieces[bQ] | (board->colour[BLACK] & board->combined[KINGS]);
  
  board->combined[KNIGHTS] = board->pieces[wN] | board->pieces[bN];
  board->combined[BISHOPS] = board->pieces[wB] | board->pieces[bB];
  board->combined[ROOKS]   = board->pieces[wR] | board->pieces[bR];
  board->combined[QUEENS]  = board->pieces[wQ] | board->pieces[bQ];
  board->combined[KINGS]   = (board->colour[WHITE] & board->combined[KINGS]) | (board->colour[BLACK] & board->combined[KINGS]);
  */
  
  #ifdef HASHTABLE
    board->key = create_key_board(board);
  #endif
  
  //update_attacking(board);
  
  return 0;
}