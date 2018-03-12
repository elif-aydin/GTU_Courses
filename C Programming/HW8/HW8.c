/*************************************************************
 *                                                           *
 * HW08                                                      *
 * Student Name: Elif Seyma ARMAGAN                          *
 * Student ID  : 151044042                                   *
 * Date        : 22.04.2016                                  *
 * Points      : Karsilikli 2 kisinin oynayabilecegi satranc *
 *               programi                                    *
 *                                                           *
 *************************************************************/

/* Kutuphanelerin tanitilmasi */
#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8 /* mainde vardi */


/* Prototiplerin tanitilmasi */
void getPosition(char *col, int *row);
void printBoard(char *board);
int isInCheck(char* board);
void initBoard(char *board);
int isValidCell(char col, int row);
int makeMove(char *board, char sc, int sr, char tc, int tr);
int isPieceMovable(char *board, char sc, int sr, char tc, int tr);
int isKnightMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isRookMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isBishopMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isKingMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isQueenMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow);
int isBlack(char player);
int isWhite(char player);
char getPlayer(char * board, char sc, int sr);

int helperRook(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow, char chLower, char chUpper);
int helperBishop(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow, char chLower, char chUpper);
int isUpper(char * board, int index);
int isLower(char * board, int index);



int main() 
{
    char board [BOARD_SIZE*BOARD_SIZE], empty;
    int player = 1; /* 1 white, 0 black */
    char sc,tc; /* source/target cols */
    int sr,tr; /* source/target rows */
    int moveStatus = 0;
    int checkStatus = 0;
    char currPlayer;

    initBoard(board);

    do {
        printBoard(board);
        printf("%s player move > ", player ? "White" : "Black"); /* true ise ilk kisim false ise 2 */
        getPosition(&sc,&sr);
        scanf("%c", &empty);
        getPosition(&tc,&tr);
        scanf("%c", &empty);
        currPlayer = getPlayer(board, sc,sr);

        if(!isValidCell(sc,sr)) {
            printf("Source position is invalid\n");
            continue;
        }
        if(!isValidCell(tc,tr)) {
            printf("Target position is invalid\n");
            continue;
        }
        if((isBlack(currPlayer) && player) ||
           (isWhite(currPlayer) && !player)) {
            printf("Illegal piece. \n");
            continue;
        }

        moveStatus = makeMove(board,sc,sr,tc,tr);
        switch(moveStatus) {
            case 0:
                printf("Invalid move!\n");
                break;
            case 1:
                printf("Your king is in check!\n");
                ++checkStatus;
                break;
            case 3:
                printf("Check!\n ");
            case 2:
                player = !player;
                checkStatus = 0;
                break;
        }
    } while(checkStatus < 2);
    printf("%s player WINS!\n", player ? "Black" : "White");
    return 0;
}

/* Tahtayi baslangic konumuna initialize eder. */
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

/* Initialize edilen tabloyu ekrana basar. */
void printBoard(char *board)
{
    int i;

  	printf("\n  a b c d e f g h\n");
    printf("  - - - - - - - -\n");

    for (i=0;i<64;i++)
    {
		if (i%8==0) 
			printf("%d|",(8-(i/8)));
	        printf("%c",board[i]);

	    /* Karakterlerin arasina boslugu yalnizca son sutunda birakmaz */
        if ((i+1)%8!=0) 
        	printf(" ");

        else 
        	printf("|\n");
    }
    printf("  - - - - - - - -\n");
}

/* Belirtilen hareketin gecerliligini kontrol eder. */
int isPieceMovable(char *board, char sc, int sr, char tc, int tr)
{
	int index, result;

	if (sc < 97 || sc > 104) /* a-h ascii araligi */
	{
		return (0);	
	}
	sc = sc - 97; /* 97 ascii ye göre a ya esittir */
	
	if (sr < 1 || sr > 8)
	{
		return (0);
	}
	sr = 8 - sr; /* tabloya gore row 8 den azalarak indigi icin */
	
	if(tc < 97 || tc > 104) /* a-h ascii araligi */
	{
		return (0);
	}
	tc = tc - 97;	/* 97 ascii ye göre a ya esittir */

	if (tr < 1 || tr > 8)
	{
		return (0);
	}
	tr = 8 - tr; /* tabloya gore row 8 den azalarak indigi icin */

	/* Source koordinatlarin index ini bulma*/
	index = sr * 8 + sc; 
    result = 0;
      
     /* Source konumunda bulunan tasa gore gecerli fonksiyonu cagirma */   
    switch (board[index])
    {
    	case 'r':
    	case 'R':
    		result = isRookMovable(board,sc,sr,tc,tr);
    		break ;

    	case 'p':
    	case 'P':
    		result = isPawnMovable(board,sc,sr,tc,tr);
    		break;

    	case 'n':
    	case 'N':
    		result = isKnightMovable(board,sc,sr,tc,tr);
    		break;
		
    	case 'b':
    	case 'B':
    		result = isBishopMovable(board,sc,sr,tc,tr);
			break;
		
    	case 'q':
    	case 'Q':
    		result = isQueenMovable(board,sc,sr,tc,tr);
    		break;
    	
    	case 'k':
    	case 'K':
    		result = isKingMovable(board,sc,sr,tc,tr);
    		break;

    	default:
    		break;	
	}	
	return (result);          
}

/* Kullanicidan yapmak istedigi hamleyi alma */
void getPosition(char *col, int *row)
{
   scanf("%c%d",col,row);
}

/* Bu fonksiyon kullanicinin girdigi koordinatlarin tahta uzerinde bulunma durumunu
   kontrol eder. */
int isValidCell(char col, int row)
{
	int result;
	
	/* girilen hamledeki col a-h araliginda ve row 0-8 araliginda  olmalidir. */
	if ((col=='a'||col=='b'||col=='c'||col=='d'||col=='e'||col=='f'||col=='g'||col=='h') &&
        (row>0 && row < 9))
        result = 1;

   	else    
    	result = 0;

    return (result);
}

/* Bu fonksiyon check durumunu kontrol eder. */
int isInCheck(char* board)
{
	/*  Return degerleri :
		0=> No check
	    1=> white check 
	    2=> black check */

	int i, j, sourceRow, targetRow, tempBlack, tempWhite;
	char sourceCol, targetCol;
	
	/* Bu kismin algoritmasi su sekildedir. Once parametre olarak gelen board un herhangi
	bir indexinde K veya k olup olmadigini kontrol eder. Eger bu durum saglandiysa o board
	icin butun olasi source ve target koordinatlari bir dongu icerisinde kontrol eder.
	Bu koordinatlarin her bir tas hareketi icin movable olup olmadigina bakar. Eger
	herhangi bir tas icin k veya K movable durumdaysa check durumu olusmus olur. Bu
	kontrol  K icin ayri k icin ayridir. */
    for (i = 0; i < 64; i++)
	{
	/* queen in pozisyonunu bulur ve queen i tehdit eden tas var mi ona bakar*/
        if (board[i] == 'K' || board[i] == 'k')
        {
       		for (j = 0; j < 64; j++) 
        	{
        		/* i ve j kullanilarak koordinatlarin bulunmasi */
            	sourceRow = j / 8;
            	sourceCol = j % 8;
            	targetRow = i / 8;
            	targetCol = i % 8;
            	
            	/* Initialize */
            	tempBlack = 0;
            	tempWhite = 0;

            	/************************************************
            	 * K icin check durumu kontrolu (White = Buyuk) *
            	 ************************************************/
            	
            	if (board[i] =='K' && board[j]=='r') 
            	    tempWhite = isRookMovable(board,sourceCol,sourceRow,targetCol,targetRow);
            	
            	/* piyon normalde one dogru gider. Sadece caprazinda rakip tas varsa onun yerine gecer */
            	else if (board[i] == 'K' && board[j]== 'p' && (j + 8) != i) 
             		tempWhite = isPawnMovable(board,sourceCol,sourceRow,targetCol,targetRow);
            	
            	else if (board[i] =='K' && board[j]=='n')              
              		tempWhite= isKnightMovable(board,sourceCol,sourceRow,targetCol,targetRow);
            	
            	else if (board[i] =='K' && board[j]=='b')             
               		tempWhite= isBishopMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	            
	            else if (board[i] =='K' && board[j]=='q')             
	                tempWhite= isQueenMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	            
	            else if (board[i] =='K' && board[j]=='k')             
	                tempWhite= isKingMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	            

	            /************************************************
            	 * k icin check durumu kontrolu (Black = Kucuk) *
            	 ************************************************/

	            else if (board[i] =='k' && board[j]=='R')              
	               	tempBlack = isRookMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	            
	            /* piyon normalde one dogru gider. Sadece caprazinda rakip tas varsa onun yerine gecer */
	            else if (board[i] =='k' && board[j]=='P' && (j-8) != i) 
	             	tempBlack= isPawnMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	            
	            else if (board[i] =='k' && board[j]=='N')               
	             	tempBlack=isKnightMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	            
	            else if (board[i] =='k' && board[j]=='B')               
	             	tempBlack= isBishopMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	            
	            else if (board[i] =='k' && board[j]=='Q')               
	                tempBlack= isQueenMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	            
	            else if (board[i] =='k' && board[j]=='K')               
	             	tempBlack= isKingMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	            

	            if (tempBlack==1) 
	            	return (2);
	            
	            if (tempWhite==1) 
	            	return (1);
	        }
	    }    
	}
	return (0);
}

char getPlayer(char * board, char sc, int sr)
{
	int index ;

	if (sc < 97 || sc > 104) /* a-h ascii araligi */
	{
		return (0);	
	}
	sc = sc - 97; /* a */
	
	if (sr < 1 || sr > 8)
	{
		return (0);
	}

	/* Parametre olarak gelen koordinatlarin tahtaya uygun hale getirilemesi */
	sr = 8 - sr;

	index = sr * 8 + sc; 

	return (board[index]);
}

int makeMove(char *board, char sc, int sr, char tc, int tr)
{
	/* Return Degerleri
	If move is invalid, returns 0
	If move is invalid because same player's king is in check, returns 1
	If move is valid, returns 2
	If move is valid and opponent player's king is in check, returns 3*/
	
	int sonuc, sourceIndex, result, targetIndex, currentPlayer;
	char tempPiece;

	/* tahtadaki index i bulma */
    sourceIndex = (8 - sr) * 8 + (sc - 'a'); 
    targetIndex = (8 - tr) * 8 + (tc - 'a');

    /* Eger isWhite fonksiyonu 1 return ettiyse tas beyazdir diger turlu ise siyahtir. */
    if (isWhite(board[sourceIndex]))
        currentPlayer = 1;
    
    else    
    	currentPlayer = 0;

    /* isPieceMovable fonksiyonu cagrilarak o hamlenin gecerli olup olmadigi kontrol edilir.
       Bu fonksiyon hamle gecerliyse 1 degilse 0 return eder.*/
    sonuc = isPieceMovable(board, sc, sr, tc, tr);
   

    if (sonuc == 1) 
    {
    	/* Eger sonuc 1 ise hareket movable demektir. Gider o tasi yer. */
    	tempPiece = board[targetIndex];
    	board[targetIndex] = board[sourceIndex];
	    board[sourceIndex] = ' ';

	    /* Hareket valid hale gelir. */
	    sonuc = 2;

	    /* Check durumu kontrol edilir. 0=> No check 1=> white check  2=> black check */
    	result = isInCheck(board); 
    	
    	/* Eger hamle sirasi black tastaysa ve hamle sonucu check oluyosa ya da
    	tersiyse o hamleyi yaptirmaz ve your king is in check der. */
    	if ((currentPlayer == 0 && result == 2) || (currentPlayer == 1 && result == 1)) /* curplayer ===  0 black 1 white */
    	{
    		board[sourceIndex] = board[targetIndex];
	        board[targetIndex] = tempPiece;	        

	        sonuc = 1;
    	}

    	/* Eger oynayan oyuncu blackse ve white check durumudaysa ya da tam tersiyse 
    	   return degeri 3 olmalidir. */
    	if ((currentPlayer == 0 && result == 1) || (currentPlayer == 1 && result == 2))
    		sonuc = 3;
    }
	  
	return (sonuc);
}

/* O hucredeki tasin white lik durumunu kontrol eder. */
int isWhite(char player)
{
	if (player == 'P' || player == 'R' || player == 'N' || 
		player == 'B' || player == 'Q' || player == 'K')
		return (1);
	
	else
		return (0);
}

/* O hucredeki tasin black lik durumunu kontrol eder. */
int isBlack(char player)
{
	if (player == 'p' || player == 'r' || player == 'n' ||
		player == 'b' || player == 'q' || player == 'k')
		return (1);
	
	else
		return (0);
}

/* Board icin verilen index de bulunan taslarin kucuk tas olma durumu */
int isLower(char * board, int index)
{
	if (board[index] == 'p' || board[index] == 'r' ||board[index] == 'n' ||
		board[index] == 'b' ||board[index] == 'q' || board[index] == 'k')
		return (1);
	
	else
		return (0);
}

/* Board icin verilen index de bulunan taslarin buyuk tas olma durumu */
int isUpper(char * board, int index)
{
	if (board[index] == 'P' || board[index] == 'R' ||board[index] == 'N' || 
		board[index] == 'B' ||board[index] == 'Q' || board[index] == 'K')
		return (1);
	
	else
		return (0);
}

/*************************
 * TASLARIN HAREKETLERI  *
 *************************/

int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	/* Degiskenlerin tanitilmasi */
	int indexS,indexT, next;
	
	/* Source ve Target koordinatinin board icin index degerinin hesaplanmasi*/
	indexS = sourceRow * 8 + sourceCol;
	indexT = targetRow * 8 + targetCol;

	/* Kucuk p one gitmek isterse next source index'in 8 fazlasi olmalidir */
	if (board[indexS] == 'p')
		next = indexS + 8;

	/* Buyuk P one gitmek isterse next source index'in 8 eksigi olmalidir  */
	else
		next = indexS - 8;

	/* Piyon eger onu bossa ve gitmek istedigi yer onune esitse hareket eder */
	if (board[indexT] == ' ' && next == indexT)
		return (1);

	 else if (next == indexT)
	 	return (0);

	/* p ise capraz gitme durumu */
	if (board[indexS] == 'p')
	{	/*	sag capraza gitme durumu */
		if (board[indexS+7] == board[indexT] && sourceRow+1 == targetRow )
		{
			if(board[indexT] == ' ')
				return (0);
			
			else if (isLower(board, indexT))
				return(0);
			
			else
				return (1=;
		}
		/* sol capraza gitme durumu */
		else if (board[indexS+9] == board[indexT] && sourceRow+1 == targetRow )
		{
			if(board[indexT] == ' ')
				return (0);
			
			else if (isLower(board, indexT))
				return (0);

			else
				return (1);
		}
		else
			return (0);
	}

	/* P ise capraz*/
	else if (board[indexS] == 'P')
	{	
		/* sag capraza gitme durumu */
		if (board[indexS-7] == board[indexT] && sourceRow-1 == targetRow)
		{
			if(board[indexT] == ' ')
				return (0);
			
			else if (isUpper(board, indexT))
				return (0);

			else
				return (1);
		}
		
		/* sol capraza gitme durumu */
		if (board[indexS-9] == board[indexT] && sourceRow-1 == targetRow)
		{
			if(board[indexT] == ' ')
				return (0);
			
			else if (isUpper(board, indexT))
				return (0);

			else
				return (1);
		}
		else
			return (0);
	}

	return (0);
}

int isKingMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	/* Degiskenlerin tanitilmasi */
	int indexS,indexT;
	
	/* Source ve Target koordinatinin board icin index degerinin hesaplanmasi */
	indexS = sourceRow * 8 + sourceCol;
	indexT = targetRow * 8 + targetCol;

	/* King yalnizca ayni satir ya da ayni sutunda ve 1 birim hareket edebilir */
  		if ((abs(sourceRow-targetRow)<=1) && (abs(sourceCol-targetCol)<=1) &&
        ((isUpper(board,indexS) &&  isLower(board,indexT)) ||
         (isUpper(board,indexT) &&  isLower(board,indexS)) ||
         (board[indexT]==' ')))
        
        return (1);
    
    return (0);
}
} 

int isKnightMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	/* Degiskenlerin tanitilmasi */
	int rowDistance,colDistance,indexT,indexS;
	
	/* Source ve Target koordinatinin board icin index degerinin hesaplanmasi */
	indexS = sourceRow * 8 + sourceCol;
	indexT = targetRow * 8 + targetCol;

	rowDistance = abs(targetRow - sourceRow);
	colDistance = abs(targetCol - sourceCol);
		
	/* Knight yalnizca satir farki 1 sutun farki 2 veya * 
	 *satir farki 2 sutun farki 1 oldugunda hareket eder  */	
	if ((rowDistance == 1 && colDistance == 2) || (rowDistance == 2 && colDistance == 1))
		{
			if ((board[indexS] == 'n') && (board[indexT] != ' ')  &&  (isLower(board,indexT)))
					return 0;
			if ((board[indexS] == 'N') && (board[indexT] != ' ') &&  (isUpper(board,indexT)))
					return 0;
		}
	else 
		return (0);
	
	return (1);
}

int isRookMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow)
{
	return helperRook(board, sourceCol, sourceRow, targetCol, targetRow, 'r', 'R');
}

int helperRook(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow, char chLower, char chUpper)
{
	/* Degiskenlerin tanitilmasi */
	int indexS, indexT, i, rowDistance, colDistance,sign;
	
	/* Source ve Target koordinatinin board icin index degerinin hesaplanmasi */
	indexS = sourceRow * 8 + sourceCol; /* Source index */ 
	indexT = targetRow * 8 + targetCol; /* Target index */ 
	
	/* Satir ve sutun farkinin hesaplanmasi */	
	rowDistance = abs(targetRow - sourceRow);	
	colDistance = abs(targetCol - sourceCol);

		if((sourceRow != targetRow) && (sourceCol != targetCol)) 
			return (0);

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
	int indexS, indexT, rowDistance, colDistance, i, distance, colSign, rowSign;

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
{ 
	/* Degiskenlerin tanitilmasi */
	int result;
	
	result=0; 

	/* Queen icin bishop ve rook taslarinin hareketi gecerlidir*/
	if (helperBishop(board, sourceCol,sourceRow,targetCol,targetRow, 'q', 'Q'))
		result=1;
	else if (helperRook(board,sourceCol,sourceRow,targetCol,targetRow, 'q', 'Q'))
		result=1;

	return (result);	
}


