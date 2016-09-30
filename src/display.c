#include "defs.h"

void print_move(s_move move)
{  
  int p;
  for(p = 0; p <= 63; ++p)
  {
    if(move.from>>p & 1) {break;}
  }
  printf("%c%c ", POS_TO_COL_CHAR(p), POS_TO_ROW_CHAR(p));
  
  for(p = 0; p <= 63; ++p)
  {
    if(move.to>>p & 1) {break;}
  }
  printf("%c%c ", POS_TO_COL_CHAR(p), POS_TO_ROW_CHAR(p));
  
  switch(move.piece_type)
  {
    case bP:
      printf("(p) ");
      break;
    case wP:
      printf("(P) ");
      break;
    case KNIGHTS:
      printf("(N) ");
      break;
    case BISHOPS:
      printf("(B) ");
      break;
    case ROOKS:
      printf("(R) ");
      break;
    case QUEENS:
      printf("(Q) ");
      break;
    case KINGS:
      printf("(K) ");
      break;
    default:
      break;
  }
  
  // Type
  switch(move.type)
  {
    case QUIET:
      printf("normal");
      break;
    case DOUBLE_PAWN:
      printf("double_move");
      break;
    case CAPTURE:
      printf("capture");
      break;
    case EP:
      printf("ep");
      break;
    case PROMOTE:
      printf("promote");
      break;
    case KSC:
      printf("KSC");
      break;
    case QSC:
      printf("QSC");
      break;
    default:
      printf("??? (%i)", move.type);
      printf("\n");
      
      printf("from:\n");
      print_u64(move.from);
      
      printf("to:\n");
      print_u64(move.to);
      break;
  }
    
  printf("\n");
}

void print_moves(s_move* moves, int num_moves)
{
  assert(moves != NULL);
  
  int i;
  for(i = 0; i < num_moves; ++i)
  {
    if(i+1 < 10) {printf(" ");}
    printf("%i: ", i+1);
    
    print_move(moves[i]);
  }
}

void print_u64(uint64_t board)
{
  int i;
  for(i = 63; i >= 0; --i)
  {
    printf("%i", (int)(1&(board>>i)));
    if(i%8 == 0) {printf("\n");}
  }
  printf("\n");
  return;
}

void display_board(s_board *board)
{
  int i;
  for(i = 63; i >= 0; --i)
  {
    if(GETBIT(board->combined[wP], i))
    {
      printf("P");
    }
    else if(GETBIT(board->combined[bP], i))
    {
      printf("p");
    }
    else if(GETBIT(board->combined[KNIGHTS], i))
    {
      if(GETBIT(board->colour[WHITE], i))
      {
        printf("N");
      }
      else
      {
        printf("n");
      }
    }
    else if(GETBIT(board->combined[BISHOPS], i))
    {
      if(GETBIT(board->colour[WHITE], i))
      {
        printf("B");
      }
      else
      {
        printf("b");
      }
    }
    else if(GETBIT(board->combined[ROOKS], i))
    {
      if(GETBIT(board->colour[WHITE], i))
      {
        printf("R");
      }
      else
      {
        printf("r");
      }
    }
    else if(GETBIT(board->combined[QUEENS], i))
    {
      if(GETBIT(board->colour[WHITE], i))
      {
        printf("Q");
      }
      else
      {
        printf("q");
      }
    }
    else if(GETBIT(board->combined[KINGS], i))
    {
      if(GETBIT(board->colour[WHITE], i))
      {
        printf("K");
      }
      else
      {
        printf("k");
      }
    }
    else
    {
      printf("-");
    }
    
    if(i%8 == 0)
    {
      printf("\n");
    }
  }
  
  if(board->turn == WHITE) {printf("Turn: w\n");}
  else {printf("Turn: b\n");}
  
  printf("Castling: ");
  if(board->castling[wKSC]) {printf("K");}
  if(board->castling[wQSC]) {printf("Q");}
  if(board->castling[bKSC]) {printf("k");}
  if(board->castling[bQSC]) {printf("q");}
  printf("\n");
  
  printf("Ep: %"PRIdPTR"\n", board->ep);
}