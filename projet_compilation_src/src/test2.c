#include <stdio.h>

void main()
{
	int taille = 10;
	int i = 0;
	for (i = 0; i < taille; i++)
	{
		if(i < 5)
		{
			printf("Inférieur à 5\n");
		}
		else
		{
			printf("Oups\n");
			i = taille +1 ;
		}

	}
	if(i > taille)
	{
		printf("Yes\n");
	}
}
