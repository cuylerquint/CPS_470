/**
Cuyler Quint
CPS 450
Activiy 3

	Recreate Given functions and modfity them to not use goto's or break
	statements.

	Qn4 Follow-up:
		In this example i will say the code readbiltiy is more straight 	forward to understand instead of having extra checks which required more 	logical thinking and tinker	
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int Qn1()
{
	int i = 0, j = 0, k = 0;
	k = ( j + 13 ) / 27; 
  	loop: 
		if( k > 10){goto Out;}
		else
		{
    			k = k + 1; 
    			i = 3 * k - 1; 
    			goto loop; 
		}	
	Out:
		printf("\nFinished Qn1");
		return 1;
}

void Qn2()
{
	int k = 1, j = 0;
	switch(k)
	{
		case 1:
			j = 2 * k -1;
		case 2:
			j = 2 * k -1;
		case 3:
			j = 3 * k + 1;
		case 5:	
			j = 3 * k + 1;
		case 4:
			j = 4 * k - 1;
		case 6:
			j = k - 2;
		case 7:
			j = k - 2;
		case 8:
			j = k - 2;
		}
	printf("\nResult of Qn2 j:%d",j);	
}

void Qn3()
{
	int j = -3 , i = 0, exit = 0;
	for(i = 0; i < 3 && !exit; i++)
	{	
  		switch ( j + 2 ) 
		{ 
			case 3:
    			case 2: j--; exit = 1; 
    			case 0: j+=2; exit = 1; 
    			default: j= 0; 
  		} 
  		if ( j > 0) exit = 1; 
  		j = 3 - i; 
	} 
	printf("\nResult of Qn3 j:%d",j);
}

void Qn4()
{
	int n = 3, exit1 = 0, exit2 = 0;
	int x[3][3] = {
		{0,1,2},
		{4,5,6},
		{0,0,0}
		};

	for (int i = 1; i <= n && !exit1; i++) 
	{ 
		for (int j = 1; j <= n && !exit2; j++)
 		{
			if (x[i][j] != 0) 
      				exit2 = 1; 
  			if(exit2 == 0)
				printf("First all-zero row is:%d", i); 
				exit1 = 1;
		} 
	}	 
	printf("\nFinished Qn4");

}

int main()
{
	Qn1();
	Qn2();
	Qn3();
	Qn4();
	return 1;
}
