
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define MAX_RAW 10 //max number of raws//
#define MAX_COL 10 //max nubmer of colums //
#define MAX_NUM 9 // max numer for random pick//
#define MIN_NUM 0 // min number for random pick//
#define SUB_NUM 5 //number of submarines//

typedef enum { FALSE = 0, TRUE = 1 } bool; 

// Statement of functions //

void Pre_Game();
void Sub_Scan(char mat[][MAX_COL], int raw);
void Board_Scan(char mat[][MAX_COL], int raw);

void Board_Print(char mat[][MAX_COL], int raw);
bool Horizon_Check(char mat[][MAX_COL], int raw, int sub_raw, int sub_col, int sub_size);
void Horizon_Scan(char mat[][MAX_COL], int raw, int sub_raw, int sub_col, int sub_size);
bool Vertical_Check(char mat[][MAX_COL], int raw, int sub_raw, int sub_col, int sub_size);
void Vertical_Scan(char mat[][MAX_COL], int raw, int sub_raw, int sub_col, int sub_size);



void Game_Exp(char mat[][MAX_RAW]);
void Insert_Attack(char mat[][MAX_COL]);
bool Check_Index(int raw, int colum);
void Same_Spot(int raw, int colum, char mat[][MAX_COL], char Board_mat[][MAX_COL]);
void Diffrent_Spot(int raw, int colum, char Board_mat[][MAX_COL]);





int main()
{//main function//
	Pre_Game();

	return 0;
}
void Pre_Game()
{

	char mat[MAX_RAW ][MAX_COL]; //A declaration of a pre-built matrix on which the game board will be built//

	
	Sub_Scan(mat, MAX_RAW);//send the matrix to function//
	Game_Exp(mat, MAX_RAW);//send matrix to function//

}

void Sub_Scan(char mat[][MAX_COL], int raw)
{
	/* A function that takes in line numbers and a random column and by internal condition,
	it checks for additional functions. Can the submarines be placed in a random manner */

	srand(time(NULL));// function for random numbers//
	int i, sub_size = 5, sub_raw, sub_col, sub_direction, check_H, check_V;


	for (i = 0; i < SUB_NUM; ++i) //for each submarine, the function checks the next conditions: //

	{
		sub_raw = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;//picking random raw number//
		sub_col = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;//picking random colum number//
		sub_direction = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;//picking random number//


		//HORIZONTALL//
		if (sub_direction > MAX_NUM / 2)// putting condition for horizontall//
		{
			check_H = Horizon_Check(mat, MAX_RAW, sub_raw, sub_col, sub_size);//Receives a response from the function whether it can be placed in the table or not//
			if (check_H == TRUE)//if the answer is true//
			{
				Horizon_Scan(mat, MAX_RAW, sub_raw, sub_col, sub_size);// sending to function that build the sub pn the board//
				--sub_size;// Reduce the number of submarines//
			}

			else //Grilling new numbers and trying to reposition//
				--i;
		}

		else
		{// putting condition for vertical//
			//VERTICALL//
			check_V = Vertical_Check(mat, MAX_RAW, sub_raw, sub_col, sub_size);//Receives a response from the function whether it can be placed in the table or not//
			if (check_V == TRUE)//if the answer is true//
			{
				Vertical_Scan(mat, MAX_RAW, sub_raw, sub_col, sub_size);// sending to function that build the sub pn the board//
				--sub_size; // Reduce the number of submarines//

			}
			else //Grilling new numbers and trying to reposition//
				--i;
		}
	}
}

bool Horizon_Check(char mat[][MAX_COL], int raw, int sub_raw, int sub_col, int sub_size)
{//A function that checks whether the submarine can be positioned at the selected position//
	int i, check = FALSE; //declaration of integers//
	if (sub_size == 1)//Check if the size of the submarine is 1, size it to 3//
		sub_size += 2;
	for (i = 0; i < sub_size; ++i) //Checks for each submarine in its appropriate size//
	{ //Checks the conditions if there is no submarine on or near the designated location in any direction//
		if (MAX_COL - sub_col > sub_size && mat[sub_raw][sub_col + i] != '$' && mat[sub_raw][sub_col + sub_size] != '$' &&  mat[sub_raw][sub_col - 1] != '$' &&  mat[sub_raw + 1][sub_col + i] != '$' &&  mat[sub_raw - 1][sub_col + i] != '$')
			check = TRUE;//fit to put on the board//

		else
		{//dont fit :one of the conditions was not realized//
			check = FALSE;//dont fit to put on board//
			break;
		}
	}
	return check;//return the answer if it fits or not to put on the board//
}
void Horizon_Scan(char mat[][MAX_COL], int raw, int sub_raw, int sub_col, int sub_size)
{//Function that absorbs submarines horizontal//
	int i;
	if (sub_size == 1)//Check if the size of the submarine is 1, size it to 3//
		sub_size += 2;

	for (i = 0; i < sub_size; ++i)//Checks for each submarine in its appropriate size//
	{
		mat[sub_raw][sub_col] = '$'; 
			
		++sub_col;// Fill in the matrix with the values '$' and run the whole row//
	}
}
bool Vertical_Check(char mat[][MAX_COL], int raw, int sub_raw, int sub_col, int sub_size)
{//A function that checks whether the submarine can be positioned at the selected position//
	
	int i, check = FALSE;//declaration of integers//
	if (sub_size == 1)//Check if the size of the submarine is 1, size it to 3//
		sub_size += 2;
	for (i = 0; i < sub_size; ++i)//Checks for each submarine in its appropriate size//
	{//Checks the conditions if there is no submarine on or near the designated location in any direction//
		if (MAX_RAW - sub_raw > sub_size  && mat[sub_raw + sub_size][sub_col] != '$' && mat[sub_raw + i][sub_col] != '$' && mat[sub_raw + i][sub_col + 1] != '$'&& mat[sub_raw + i][sub_col - 1] != '$'&& mat[sub_raw - 1][sub_col] != '$')
			check = TRUE;//fit to put on the board//

		else
		{//dont fit :one of the conditions was not realized//
			check = FALSE;//dont fit to put on board//
			break;
		}
	}
	return check;//return the answer if it fits or not to put on the board//
}
void Vertical_Scan(char mat[][MAX_COL], int raw, int sub_raw, int sub_col, int sub_size)
{//Function that absorbs submarines vertically//

	int i;
	if (sub_size == 1)//Check if the size of the submarine is 1, size it to 3//
		sub_size += 2;

	for (i = 0; i < sub_size; ++i)//Checks for each submarine in its appropriate size//
	{

		mat[sub_raw][sub_col] = '$';
		++sub_raw;// Fill in the matrix with the values '$' and run the colum row//
	}
}






void Game_Exp(char mat[][MAX_RAW])
{//expression for the user, how the progrram works //
	printf("Hello, you are about to play the game in front of the computer the game:'Submarines'.Good luck!\n\n");
	printf("Enter the raw number(0-9) and than the colum number(0-9) to attack.\n");
	printf("When you hit the submarine, you'll see the sign 'X' on the saline, and when you miss it you'll see the '~', a place you did not attack still look like this: '_'\n");
	printf("When you will hit all the Sub's the game will end.\n");
	printf("(for exit, enter '-1' '-1')\n");
	Insert_Attack(mat);//calling to funtion//

}

void Insert_Attack(char mat[][MAX_COL])
{//A function that asks the user to insert row and column values and checks whether there is a submarine in the location//
	char Board_mat[MAX_RAW][MAX_COL];//A statement on the game board as a matrix//
	int R=0, C=0, hits = 0, count = 0; //Declaration and reform of variables//

	Board_Scan(Board_mat, MAX_RAW);//Call to the function you are starting the board//
	
	
	do
	{
		scanf("%d %d", &R, &C);//Receiving line number and column number//

		if (R == -1 && C == -1)//condition to finish //
		{
			printf("See you next time!\n");
			break;
		}

		if (Check_Index(R, C) == TRUE) // A call to a function that checks the values entered by the user follows the instructions//

		{
			if (Board_mat[R][C] == 'X' || Board_mat[R][C] == '~') //Checks whether he has already chosen the same point by comparing the two matrices at that point//
			{
				printf("\nYou've already chosen this place! Choose again.\n");
			}

			if(mat[R][C] == '$' && Board_mat[R][C]!='X') //Checking whether there is a submarine in the matrix and whether we have already chosen this location on our board//
			{
				Same_Spot(R, C, mat, Board_mat);//calling to function that Indicates a successful attack//
				Board_Print(Board_mat, MAX_RAW);//function that prints the board//
				++hits;//number of successful attack's//
				++count;//counting each turn//
			}
			
			if(mat[R][C]!='$' && Board_mat[R][C] != '~') //Checks the condition if there is no submarine on our matrix and whether we did not select that position on the board//
			{
				Diffrent_Spot(R, C, Board_mat);//calling to function that Indicates a unsuccessful attack//
				Board_Print(Board_mat, MAX_RAW);//function that prints the board//
				++count;//counting each turn//
			}

			
			
		}
		else
			printf("Wrong Index,Try Again!\n");//if its not fit the condition of right index//
	} while (hits != 17); //Runs in a loop until it hits the total shading size (5 + 4 + 3 + 3 + 2 = 17)//
	if(hits==17)//Checks the condition that the user has hit all submarines//
		printf(" Congratulation you win! it took you %d turns to finish the game, I'll sure you will get better next time !\n", count);
}
void Board_Print(char mat[][MAX_COL], int raw)
{//function that print the board game//
	printf("\n");
	int i, j;
	for (i = 0; i < raw; ++i)
	{
		printf("\n");
		for (j = 0; j < MAX_COL; ++j)
			printf("%c\t", mat[i][j]);
		printf("\n");
	}
	printf("\n");
}
void Board_Scan(char mat[][MAX_COL], int raw)
{//function that scan the board game at first//
	int i, j;
	for (i = 0; i < raw; ++i)
		for (j = 0; j < MAX_COL; ++j)
			mat[i][j] = '_';
}
bool Check_Index(int raw, int colum)
{//function that check if the user insert numbers as he asked for//
	int check;
	if ((raw > 9 || raw <0) || (colum > 9 || colum < 0))//the numbers only between 0-9)
		check = FALSE;
	else
		check = TRUE;
	return check; //return if the index are correct ot not//
}
void Same_Spot(int raw, int colum, char mat[][MAX_COL], char Board_mat[][MAX_COL])
{//Function that marks the impact on the submarine//
	Board_mat[raw][colum] = 'X';
	printf("\n!! HIT !!\n");
}
void Diffrent_Spot(int raw, int colum, char Board_mat[][MAX_COL])
{//A function that indicates that the submarine is not hit//
	Board_mat[raw][colum] = '~';
	printf("\nMISS!\n");
}


