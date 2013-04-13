/*
 * main.c
 *
 *  Created on: 07-Apr-2013
 *      Author: safiyat
 */


#include <stdio.h>
#include "lzwc.c"
#include "lzwd.c"
int main()
{
	int ch;
	do
	{
		printf("\n\t\t\tLZW Compression\n");
		printf("1. Compression\n");
		printf("2. Decompression\n");
		printf("3. Exit\n");
		printf("\nEnter your choice: ");
		scanf("%d", &ch);
		if(ch==1)
			compression();
		else if(ch==2)
			decompression();
		else if(ch==3)
			break;
		else
			printf("\nInvalid choice!!!\n");
	}while(ch<3||ch>0);
	return 0;
}
