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
	printf("\nResult of Qn2 j: %d",j);	
}

void Qn3()
{
	int j = -3 , i = 0;
	int end = 0;
	while(end != 1 || i <  3)
	{
		
  		switch ( j + 2 ) 
		{ 
    			case 3: 
    			case 2: j--; end = 1; 
    			case 0: j+=2; end = 1; 
    			default: j= 0; 
  		} 
  		if ( j > 0) end = 1; 
  		j = 3 - i; 
	} 
	printf("\nResult of Qn3 j:%d",j);
}

int main()
{
	Qn1();
	Qn2();
	return 1;
}
