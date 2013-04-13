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
	int size=0, match, term, ocode, ncode;
	char *p, path[128], *str[MAX], CHAR, STR[32];
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
	init(&size, str);
	/**********************************************************
	Input the key from the user, upto 32 characters.
	**********************************************************/
	match=read(ifile); //Don't read() directly. Subtract key[k++] first. k is int, initialized as 0.
	ocode=match;
	fprintf(ofile, "%c", ocode);
	odsize++;
	while(1)
	{
		term=read(ifile);
		if(term==EOF)
			break;
		//Process term here. Subtract key[k++]. Then do k=k%strlen(key).
		match=term;
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
		if(size<4096)
			fill(&size, &str[size], STR);
		ocode=ncode;
	};
	printf("\nOutput file: %s", path);
	printf("\nCompressed size: %d Bytes. Decompressed size: %d Bytes.", idsize-1, odsize);
	fclose(ifile);
	fclose(ofile);
	return 0;
}
