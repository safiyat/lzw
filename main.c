/*
 * main.c
 *
 *  Created on: 19-Apr-2013
 *      Author: safiyat
 */


#include <stdio.h>
#include "lzwc.h"
#include "lzwd.h"
#include "env_var.h"

int enc=1, verbose=0, cat=0;

int main()
{
	int ch;
	do
	{
		printf("\n\t\t\tLZW Compression\n");
		printf("1. Compression\n");
		printf("2. Decompression\n");
		printf("3. Change Settings\n");
		printf("4. Exit\n");
		printf("\nEnter your choice: ");
		scanf("%d", &ch);
		if(ch==1)
			compression(enc, verbose);
		else if(ch==2)
			decompression(enc, cat);
		else if(ch==3)
			env_var(&enc, &verbose, &cat);
		else if(ch==4)
			break;
		else
			printf("\nInvalid choice!!!\n");
	}while(ch<4||ch>0);
	return 0;
}
