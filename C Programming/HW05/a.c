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

void printBoard(char *board)
{
    int i;

    printf("  a b c d e f g h\n");
    printf("  - - - - - - - -\n");

    for (i=0;i<64;i++)
    {
		if (i%8==0) printf("%d|",(8-(i/8)));
	        printf("%c",board[i]);

        if ((i+1)%8!=0) 
        	printf(" ");

        else 
        	printf("|\n");
    }

    printf("  - - - - - - - -\n");
}

void emptyBuffer()
{
	while ( getchar() != '\n' );
}

int isPieceMovable(char *board)
{
	char sourceCol, targetCol, temp;
	int sourceRow, targetRow, index, result;

	scanf("%c%d",&sourceCol,&sourceRow);
	scanf("%c", &temp);
	scanf("%c%d",&targetCol,&targetRow);

	if (sourceCol < 97 || sourceCol > 104) /* a-h ascii araligi */
	{
		return (0);	
	}
	sourceCol = sourceCol - 97; /* a */
	
	if (sourceRow < 1 || sourceRow > 8)
	{
		return (0);
	}
	sourceRow = 8 - sourceRow;
	

	if(targetCol < 97 || targetCol > 104) /* a-h ascii araligi */
	{
		return (0);
	}
	targetCol = targetCol - 97;	/* a */

	if (targetRow < 1 || targetRow > 8)
	{
		return (0);
	}
	targetRow = 8 - targetRow; /* 8 den azalarak indigi icin */


	index = sourceRow * 8 + sourceCol;
    result = 0;
        
    switch (board[index])
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
	return (result);          
}

int isValidCell(char col, int row)
{
	int result;

		if ((col=='a'||col=='b'||col=='c'||col=='d'||col=='e'||col=='f'||col=='g'||col=='h') &&
        (row>0 && row < 9))
       
        	result = (1);

   		else    
    		result = (0);

    	return (result);

}

void getPosition(char *col, int *row)
{
    while((*col=getchar())==' ');

    *row=getchar();

    *row=*row -'0';
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

/* TASLAR  */
int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	int indexS,indexT, next;
	indexS = sourceRow * 8 + sourceCol;
	indexT = targetRow * 8 + targetCol;


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

    if (abs(sourceRow-targetRow) > 1 || (sourceCol-targetCol) > 1)
	    return 0;
	else if ((isUpper(board,indexT) &&  isLower(board, indexS))||
            (isUpper(board,indexS) &&  isLower(board, indexT)) ||
            board[indexT]==' ')
        return 1;
    else  return 0;

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
			if ((board[indexS] == 'n') && (board[indexT] != ' ')  &&  (isLower(board,indexT)))
					return 0;
			if ((board[indexS] == 'N') && (board[indexT] != ' ') &&  (isUpper(board,indexT)))
					return 0;
		}
	else return 0;
	
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
			return 0;

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
						return 0;

				if (board[indexT] == ' ' || isUpper(board, indexT))
					return 1;

				return 0;
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
						return 0;
					
						
				if (board[indexT] == ' ' || isUpper(board, indexT))
					return 1;

				return 0;
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
						return 0;

				if (board[indexT] == ' ' || isLower(board, indexT))
					return 1;

				return 0;
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
						return 0;

				if (board[indexT] == ' ' || isLower(board, indexT))
					return 1;

				return 0;
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
	int indexS, indexT, rowDistance, colDistance, i, distance, colSign, rowSign;;

	indexS = sourceRow * 8 + sourceCol; /* Source index */
	indexT = targetRow * 8 + targetCol; /* Target index */

	rowDistance=targetRow-sourceRow;
    colDistance=targetCol-sourceCol;

    if (abs(rowDistance) == abs(colDistance))
    {
        distance=abs(rowDistance);
        rowSign=rowDistance/abs(rowDistance);
        colSign=colDistance/abs(colDistance);
        if ((isLower(board, indexT)==1 && (isLower(board, indexS)==1)) ||
           (isUpper(board, indexS)==1 && isUpper(board, indexT)==1))
           return 0;;
        for (i=1; i<distance; i++)
        {
            if (board[(sourceRow+(rowSign*i))*8+sourceCol+colSign*i]!=' ') return 0;
        }
    }
    else return 0;

	return 1;
}

int isQueenMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{ int result=0; 
	if (helperBishop(board, sourceCol,sourceRow,targetCol,targetRow, 'q', 'Q'))
		result=1;
	else if (helperRook(board,sourceCol,sourceRow,targetCol,targetRow, 'q', 'Q'))
		result=1;

	return result;	
}


