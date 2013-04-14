/*
 * lzwd.c
 *
 *  Created on: 08-Apr-2013
 *      Author: safiyat
 */


#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>
#include "lzw.h"

int idsize=0, odsize=0;

int read(FILE *file)
{
	static unsigned char a, b;
	static int j=-1;
	fread(&a, sizeof(unsigned char), 1, file);
	idsize++;
	if(feof(file))
		return -1;
	if(feof(file)==0)
	{
		j++;
		if((j%2)==0)
		{
			fread(&b, sizeof(unsigned char), 1, file);
			idsize++;
			return (a*16+b/16);
		}
		else
		{
			return (a+(b%16)*256);
		}
	}
	return a;
}

int decompression()
{
	int size=0, match, term, ocode, ncode, k;
	char *p, path[128], *str[MAX], CHAR, STR[32], key[33];
	FILE *ifile, *ofile;
	printf("\n\nEnter the compressed file's name: ");
	scanf("%s", path);
	ifile=fopen(path, "rb");
	p=rindex(path, '.');
	if(strncmp(p, ".lzw", strlen(p)))
	{
		printf("\nNot a compressed file!!!\n");
		fclose(ifile);
		return -1;
	}
	if(p!=NULL)
		*p='\0';
	strcat(path, ".txt");
	ofile=fopen(path, "w");
	if((ifile==NULL||ofile==NULL))
	{
		printf("\nI/O Error!!!");
		return -1;
	}
	__fpurge(stdin);
	printf("\nEnter key to decrypt the compressed file: ");
	gets(key);
	k=0;
	init(&size, str);
	match=read(ifile);
	match-=key[k];
	k++;
	if(k==strlen(key))
		k=0;
	ocode=match;
	fprintf(ofile, "%c", ocode);
	odsize++;
	while(1)
	{
		term=read(ifile);
		if(term==EOF)
			break;
		match=term;
		match-=key[k];
		k++;
		if(k==strlen(key))
			k=0;
		ncode=match;
		if(ncode<size)
			strcpy(STR, str[ncode]);
		else
		{
			strcpy(STR, str[ocode]);
			addchartostr(CHAR, STR);
		}
		fprintf(ofile, "%s", STR);
		odsize+=strlen(STR);
		CHAR=STR[0];
		strcpy(STR, str[ocode]);
		addchartostr(CHAR, STR);
		if(size<MAX)
			fill(&size, &str[size], STR);
		ocode=ncode;
	};
	printf("\nOutput file: %s", path);
	printf("\nCompressed size: %d Bytes. Decompressed size: %d Bytes.", idsize-1, odsize);
	fclose(ifile);
	fclose(ofile);
	return 0;
}
