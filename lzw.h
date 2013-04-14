/*
 * lzw.h
 *
 *  Created on: 07-Apr-2013
 *      Author: safiyat
 */

#ifndef LZW_H_
#define LZW_H_

#define MAX 3820

void fill(int *s, char **stra, const char *temp)
/*fill entries in the dictionary*/
{
	*stra=(char *)malloc(sizeof(char)*strlen(temp));
	strcpy(*stra, temp);
	*s=*s+1;
}

void print_table_entry(int i, char *stra)
/*print table entries*/
{
	printf("%d:\t", i);
	printf(" %s\n", stra);
}

void print_trans(int n, char *stra[])
/*print translation of the nth entry from char *stra[]*/
{
	printf("%s", stra[n]);
}

void addchartostr(char cha, char *stra)
/*Add a trailing char to the string*/
{
	stra[strlen(stra)+1]='\0';
	stra[strlen(stra)]=cha;
}

void init(int *sizea, char **stra)
/*Initialize the table upto 256 table entries.*/
{
	char temp[256];
	while(*sizea<256)
	{
		sprintf(temp, "%c", *sizea);
		fill(sizea, &stra[*sizea], temp);
	}
}

#endif /* LZW_H_ */
