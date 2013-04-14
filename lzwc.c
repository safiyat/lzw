/*
 * lzwc.c
 *
 *  Created on: 08-Apr-2013
 *      Author: safiyat
 */


#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>
#include "lzw.h"

int icsize=0, ocsize=0;

int write(FILE *file, int n)
{
	static int i, temp;
	unsigned char ch;
	if((i%2)==0)
	{
		ch=n/16;
		temp=n%16;
		fwrite(&ch, sizeof(unsigned char), 1, file);
		ocsize++;
	}
	else
	{
		ch=n/256+(temp*16);
		fwrite(&ch, sizeof(unsigned char), 1, file);
		ocsize++;
		if(n==0)
			return 0;
		ch=n%256;
		fwrite(&ch, sizeof(unsigned char), 1, file);
		ocsize++;
		temp=0;
	}
	i++;
	if(temp!=0)
		return 1;
	return 0;
};

int compression()
{
	int ch, size=0, i, match, flag, j, check, exit, k;
	char txt[256], *p, *path, *str[MAX], STR[32], CHAR, key[33];
	FILE *ifile, *ofile;
	printf("\n1. Compress text");
	printf("\n2. Compress a text file");
	printf("\n3. See a sample run");
	printf("\n4. Exit");
	printf("\n\nEnter your choice: ");
	scanf("%d", &ch);
	switch(ch)
	{
		case 1:
				__fpurge(stdin);
				printf("\nEnter text: ");
				gets(txt);
				p=txt;
				ofile=fopen("file.lzw", "wb");
				break;

		case 2:
				printf("Enter the relative path of the text file: ");
				path=(char *)malloc(sizeof(char)*128);
				scanf("%s", path);
				ifile=fopen(path, "r");
				p=rindex(path, '.');
				if(strncmp(p, ".lzw", strlen(p))==0)
				{
					printf("\nAlready a compressed file!!!\n");
					fclose(ifile);
					return -1;
				}
				if(p!=NULL)
					*p='\0';
				strcat(path, ".lzw");
				ofile=fopen(path, "wb");
				if((ifile==NULL||ofile==NULL))
				{
					printf("\nI/O Error!!!");
					fclose(ifile);
					fclose(ofile);
					return -1;
				}
				p=(char *)malloc(sizeof(char));
				break;

		case 3:
				printf("\n\nSample text:\n She sells seashells by the seashore. The shells she sells are surely seashells. So if she sells shells, on the seashore, I am sure she sells seashore shells.\n\n");
				strcpy(txt, "She sells seashells by the seashore. The shells she sells are surely seashells. So if she sells shells, on the seashore, I am sure she sells seashore shells.");
				ofile=fopen("file.lzw", "wb");
				p=txt;
				break;

		case 4:
				return 0;
	}
	__fpurge(stdin);
	printf("\nEnter a passphrase to encrypt the compressed file (upto 32 characters): ");
	gets(key);
	k=0;
	init(&size, str);
	i=0;
	if(ch==2)
		*p=getc(ifile);
	else
		p=txt;

	STR[i++]=*p;
	icsize++;
	match=STR[0];
	exit=1;
	while(exit)
	{
		if(ch==2)
			*p=getc(ifile);
		else
		{
			p++;
		}
		CHAR=*p;
		icsize++;
		if(ch!=2&&CHAR==NULL)
			exit=0;
		STR[i++]=CHAR;
		STR[i]='\0';
		flag=0;
		for(j=0; j<size; j++)
		{
			if(strncmp(str[j], STR, strlen(STR))==0)
			{
				match=j;
				flag=1;
				break;
			}
		}
		if(flag)
			continue;
		match+=key[k];
		k++;
		if(k==strlen(key))
			k=0;
		check=write(ofile, match);
		if(size<MAX)
			fill(&size, &str[size], STR);
		i=1;
		STR[0]=CHAR;
		match=STR[0];
		if(ch==2)
			if(feof(ifile))
				break;

	};
	if(exit==0)
	{
		match+=key[k];
		k++;
		if(k==strlen(key))
			k=0;
		check=write(ofile, match);
	}
	if(check)
		write(ofile, 0);
	if(ch==2)
		fclose(ifile);
	fclose(ofile);
	printf("\nOutput file: ");
	if(ch==2)
		printf("%s", path);
	else
		printf("file.lzw");
	printf("\nUncompressed size: %d Bytes. Compressed size: %d Bytes.\n", icsize-1, ocsize);
	return 0;
}

