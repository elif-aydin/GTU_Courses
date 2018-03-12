/* Kutuphanelerin tanitilmasi */
#include <stdio.h>
#include <stdlib.h>

/* Prototiplerin tanitilmasi */
void getPosition(char *col, int *row);
void printBoard(char *board);
void emptyBuffer();

int isPieceMovable(char *board);
int isKnightMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isRookMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isBishopMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isKingMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isQueenMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
void initBoard(char *board);
int isValidCell(char col, int row);
 
int isLower(char * board, int index);
int isUpper(char * board, int index);
int helperRook(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow, char chLower, char chUpper);
int helperBishop(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow, char chLower, char chUpper);

void emptyBuffer()
{
	while ( getchar() != '\n' );
}

int main()
{
	char board [64];
	int initComplete = 0;
	char empty;

	int command;
	scanf("%d", &command);

	while(command!=4)
	{
		switch(command)
		{
			case 1: initBoard(board); 
				initComplete = 1; 
				printf("OK\n");
				break;
			case 2: 
				/*Read space character after command number*/
				scanf("%c", &empty);
				if (initComplete)
				{
					if(isPieceMovable(board))
						printf("YES\n");
					else
						printf("NO\n");
				}
				else
				{  
					printf("Board is not initialized!\n");
					emptyBuffer();
				}
				break;
			case 3: 
				if (initComplete)
					printBoard(board);
				else  
					printf("Board is not initialized!\n");
					emptyBuffer();
				break;

			default: printf("Invalid command!\n"); emptyBuffer(); break;

		}	
		
		scanf("%d", &command);
	
	}
	return (0);
}


void initBoard(char *board)
{
	int i;

    char myboard[64]=
    	{'r','n','b','q','k','b','n','r',

         'p','p','p','p','p','p','p','p',

         ' ',' ',' ',' ',' ',' ',' ',' ',

         ' ',' ',' ',' ',' ',' ',' ',' ',

         ' ',' ',' ',' ',' ',' ',' ',' ',

         ' ',' ',' ',' ',' ',' ',' ',' ',

         'P','P','P','P','P','P','P','P',

         'R','N','B','Q','K','B','N','R'};

    for (i=0;i<64;i++)

        board[i]=myboard[i];
}

int isValidCell(char col, int row)
{ int result=0;
	if ((col=='a'||col=='b'||col=='c'||col=='d'||col=='e'||col=='f'||col=='g'||col=='h') &&
    (row>0 && row < 9))
    	result = 1;
    return result;;
}

void getPosition(char *col, int *row)
{
    scanf("%c%d",&*col,&*row);

}

void printBoard(char *board)
{
    int i;

    printf("\n  a b c d e f g h\n");
    printf("  - - - - - - - -\n");

    for (i=0; i<64; i++)
    {
		if (i % 8 == 0)
			printf("%d|",(8-( i / 8)));
	        printf("%c",board[i]);

        if ((i + 1) % 8 != 0)
        	printf(" ");

        else
        	printf("|\n");
    }

    printf("  - - - - - - - -\n");
}

int isPieceMovable(char *board)
{
char sourceCol, targetCol, empty;
	int sourceColRef, targetColRef;
	int sourceRow, targetRow, indexS, indexT, result;

	getPosition(&sourceCol,&sourceRow);
	scanf("%c",&empty);
	getPosition(&targetCol,&targetRow);

	if(isValidCell(sourceCol, sourceRow) == 0)
		result=0;
	else if(isValidCell(targetCol, targetRow) == 0)
		result=0;
    else {

	/*scanf("%c%d",&sourceCol,&sourceRow);
	scanf("%c", &temp);
	scanf("%c%d",&targetCol,&targetRow);*/

	    sourceColRef = sourceCol - 'a'; /* a */
	    sourceRow = 8 - sourceRow;

	    targetColRef = targetCol - 'a';	/* a */
	    targetRow = 8 - targetRow; /* 8 den azalarak indigi icin */

	    indexS = sourceRow * 8 + sourceColRef;
	    indexT = targetRow * 8 + targetColRef;
	    if  (indexS == indexT)
		    result=0;
        else
            switch (board[indexS])
            {
                case 'r':
                case 'R':
                    result = isRookMovable(board,sourceCol,sourceRow,targetCol,targetRow);
                    break ;
                case 'p':
                case 'P':
                    result = isPawnMovable(board,sourceCol,sourceRow,targetCol,targetRow);
                    break;
                case 'n':
                case 'N':
                    result = isKnightMovable(board,sourceCol,sourceRow,targetCol,targetRow);
                    break;
                case 'b':
                case 'B':
                    result = isBishopMovable(board,sourceCol,sourceRow,targetCol,targetRow);
                    break;
                case 'q':
                case 'Q':
                    result = isQueenMovable(board,sourceCol,sourceRow,targetCol,targetRow);
                    break;
                case 'k':
                case 'K':
                    result = isKingMovable(board,sourceCol,sourceRow,targetCol,targetRow);
                    break;
                default:
                    break;
        }
	}

	return result;
    
}

int isUpper(char * board, int index)
{
	if (board[index] == 'P' || board[index] == 'R' ||board[index] == 'N' ||board[index] == 'B' ||board[index] == 'Q' || board[index] == 'K')
		return 1;
	else
		return 0;
}

int isLower(char * board, int index)
{
	if (board[index] == 'p' || board[index] == 'r' ||board[index] == 'n' ||board[index] == 'b' ||board[index] == 'q' || board[index] == 'k')
		return 1;
	else
		return 0;
}

/* *******************************
 *            TASLAR             *
 *********************************/

int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	int indexS,indexT, next;
	indexS = sourceRow * 8 + sourceCol-'a';
	indexT = targetRow * 8 + targetCol-'a';


	if (board[indexS] == 'p')
		next = indexS + 8;

	else if(board[indexS] == 'P')
		next = indexS - 8;

	if (board[indexT] == ' ' && next == indexT)
		return (1);

	/* p ise capraz */
	if (board[indexS] == 'p')
	{	/*	sag capraz */
		if (((indexS-1)%8>0) &&  (board[indexS+7] == board[indexT]) &&
            (sourceRow+1 == targetRow) && isUpper(board, indexT))
 			return 1;
		/* sol capraz */
		else if ((indexS%8> 0) && board[indexS+9] == board[indexT] && sourceRow+1 == targetRow && isUpper(board, indexT))
            return 1;
        else return 0;
	}

	/* P ise capraz*/
	else if (board[indexS] == 'P')
	{
		if ((indexS-1)%8>0 && board[indexS-7] == board[indexT] && sourceRow-1 == targetRow && isLower(board, indexT))
				return 1;
		else if (indexS%8> 0 && board[indexS-9] == board[indexT] && sourceRow-1 == targetRow&& isLower(board, indexT))
				return 1;
		else return 0;
		}
	    
	return 1; 
}

int isKingMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	int indexS,indexT;
	indexS = sourceRow * 8 + sourceCol;
	indexT = targetRow * 8 + targetCol;

	if (board[indexS] == 'k')
	{
		if ((((indexS+9 == indexT || indexS+8 == indexT || indexS+7 == indexT) && sourceRow+1 == targetRow)&& board[indexT] == ' ')
			|| isUpper(board,indexT))
			return 0;

		else if ((((indexS-1 == indexT || indexS+1 == indexT) && sourceRow == targetRow) && board[indexT] == ' ')
				|| isUpper(board,indexT))
			return 0;

		else if((((indexS-9 == indexT || indexS-8 == indexT || indexS-7) && sourceRow-1 == targetRow)&& board[indexT] == ' ')
				|| isUpper(board,indexT))
			return 0;

	}

	if (board[indexS] == 'K')
	{
		if ((((indexS+9 == indexT|| indexS+8 == indexT || indexS+7 == indexT) && sourceRow+1 == targetRow)&& board[indexT] == ' ')
		|| isLower(board,indexT))
			return 0;

		else if ((((indexS-1 == indexT || indexS+1 == indexT) && sourceRow == targetRow) && board[indexT] == ' ')
		|| isLower(board,indexT))
			return 0;

		else if((((indexS-9 == indexT || indexS-8 == indexT || indexS-7) && sourceRow-1 == targetRow)&& board[indexT] == ' ')
		|| isLower(board,indexT))
			return 0;
	}
	return 1;
}

int isKnightMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	int rowDistance,colDistance,indexT,indexS;

	indexS = sourceRow * 8 + sourceCol;
	indexT = targetRow * 8 + targetCol;

	rowDistance = abs(targetRow - sourceRow);
	colDistance = abs(targetCol - sourceCol);

	if ((rowDistance == 1 && colDistance == 2) || (rowDistance == 2 && colDistance == 1))
		{
			if (board[indexS] == 'n')
				{
					if(board[indexT] == ' ' || isUpper(board,indexT))
					return 0;
				}

			else if(board[indexS] == 'N')
				{
					if(board[indexT] == ' ' || isLower(board,indexT))
					return 0;
				}
		}
		return 1;
}

int isRookMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	return helperRook(board, sourceCol, sourceRow, targetCol, targetRow, 'r', 'R');
}

int helperRook(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow, char chLower, char chUpper)
{
	int indexS, indexT, i, rowDistance, colDistance,sign;

	indexS = sourceRow * 8 + sourceCol; /* Source index */
	indexT = targetRow * 8 + targetCol; /* Target index */

	rowDistance = abs(targetRow - sourceRow);
	colDistance = abs(targetCol - sourceCol);

		if((sourceRow != targetRow) && (sourceCol != targetCol))
			return 1;

		/* r icin */
		if (board[indexS] == chLower)
		{
			/* ayni satir icin */
			if(targetRow - sourceRow == 0)
			{
				if (targetCol - sourceCol < 0)
					sign = -1;

				else
					sign = 1;

				for (i=1; i < colDistance; i++)
					if(board[indexS+(i*sign)] != ' ' )
						return 1;

				if (board[indexT] == ' ' || isUpper(board, indexT))
					return 0;

				return 1;
			}

			/* ayni sutun icin */
			else if(targetCol - sourceCol == 0)
			{
				if(targetRow-sourceRow < 0)
					sign = 1;
				else
					sign = -1;

				for(i=1; i < rowDistance; i++)
					if (board[indexS - (i*8*sign)] != ' ')
						return 1;


				if (board[indexT] == ' ' || isUpper(board, indexT))
					return 0;

				return 1;
			}
		}

		/* R icin */
		if (board[indexS] == chUpper)
		{
			/* ayni satir icin */
			if(targetRow - sourceRow == 0)
			{
				if (targetCol - sourceCol < 0)
					sign = -1;

				else
					sign = 1;

				for (i=1; i < colDistance; i++)
					if(board[indexS+(i*sign)] != ' ')
						return 1;

				if (board[indexT] == ' ' || isLower(board, indexT))
					return 0;

				return 1;
			}

			/* ayni sutun icin */
			else if(targetCol - sourceCol == 0)
			{
				if(targetRow-sourceRow < 0)
					sign = 1;
				else
					sign = -1;

				for(i=1; i < rowDistance; i++)
					if (board[indexS-((i*8)*sign)] != ' ' )
						return 1;

				if (board[indexT] == ' ' || isLower(board, indexT))
					return 0;

				return 1;
			}
		}
	return 1;
}

int isBishopMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	return helperBishop(board, sourceCol, sourceRow, targetCol, targetRow, 'b', 'B');
}

int helperBishop(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow, char chLower, char chUpper)
{
	int indexS, indexT, rowDistance, colDistance, i;

	indexS = sourceRow * 8 + sourceCol; /* Source index */
	indexT = targetRow * 8 + targetCol; /* Target index */

	rowDistance = abs(targetRow - sourceRow);
	colDistance = abs(targetCol - sourceCol);

		if (rowDistance == colDistance)
			{
				if (board[indexS] == chLower)
				{
					if ((targetRow - sourceRow < 0) && (targetCol - sourceCol > 0))  /* sag ust capraza gitme durumu */
					{
						for(i=1; i < rowDistance; i++)
							if (board[indexS-(i*8)+i] != ' ')
								return 1;
						if (board[indexT] == ' ' || isUpper(board, indexT))
							return 0;

					}

					if ((targetRow - sourceRow < 0) && (targetCol - sourceCol < 0)) /* sol ust capraz gitme durumu */
					{
						for	(i=1; i< rowDistance; i++)
							if(board[indexS-(i*8)-i] != ' ')
								return 1;
						if (board[indexT] == ' ' || isUpper(board, indexT))
							return 0;
					}

					if ((targetRow - sourceRow > 0) && (targetCol - sourceCol > 0)) /* sag alt capraz gitme durumu */
					{
 						for (i=1; i<rowDistance; i++)
 							if(board[indexS+(i*8)+i] != ' ')
 								return 1;
 						if (board[indexT] == ' ' || isUpper(board, indexT))
 							return 0;
 					}

 					if ((targetRow - sourceRow > 0) && (targetCol - sourceCol < 0)) /* sol alt capraza gitme durumu */
 					{
 						for(i=1; i<rowDistance; i++)
 							if(board[indexS+(i*8)-i] != ' ')
 								return 1;
 						if(board[indexT] == ' ' || isUpper(board, indexT))
 							return 0;
 					}
 				}

 				if (board[indexS] == chUpper)
				{
					if ((targetRow - sourceRow < 0) && (targetCol - sourceCol > 0))  /* sag ust capraza gitme durumu */
					{
						for(i=1; i < rowDistance; i++)
							if (board[indexS-(i*8)+i] != ' ')
								return 1;
						if (board[indexT] == ' ' || isLower(board, indexT))
							return 0;

					}

					if ((targetRow - sourceRow < 0) && (targetCol - sourceCol < 0)) /* sol ust capraz gitme durumu */
					{
						for	(i=1 ; i< rowDistance; i++)
							if(board[indexS-(i*8)-i] != ' ')
								return 1;
						if (board[indexT] == ' ' || isLower(board, indexT))
							return 0;
					}

					if ((targetRow - sourceRow > 0) && (targetCol - sourceCol > 0)) /* sag alt capraz gitme durumu */
					{
 						for (i=1; i<rowDistance; i++)
 							if(board[indexS+(i*8)+i] != ' ')
 								return 1;
 						if (board[indexT] == ' ' || isLower(board, indexT))
 							return 0;
 					}

 					if ((targetRow - sourceRow > 0) && (targetCol - sourceCol < 0)) /* sol alt capraza gitme durumu */
 					{
 						for(i=1; i<rowDistance; i++)
 							if(board[indexS+(i*8)-i] != ' ')
 								return 1;
 						if(board[indexT] == ' ' || isLower(board, indexT))
 							return 0;
 					}
				}
			}
	return 1;
}

int isQueenMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	if (helperBishop(board, sourceCol,sourceRow,targetCol,targetRow, 'q', 'Q'))
		return 1;
	else if (helperRook(board,sourceCol,sourceRow,targetCol,targetRow, 'q', 'Q'))
		return 1;

	return 1;
}



