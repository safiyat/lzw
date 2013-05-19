/*
 * env_var.h
 *
 *  Created on: 19-Apr-2013
 *      Author: safiyat
 */

#ifndef ENV_VAR_H_
#define ENV_VAR_H_

int env_var(int *enc, int *verbose, int *cat)
{
	char *onoff[2]={"OFF", "ON"};
	int set;
	while(1)
	{
		printf("\n\n\n\t\t\tSETTINGS\n\n");
		printf("1. Encryption: %s\n", onoff[*enc]);
		printf("2. Verbose Compression: %s\n", onoff[*verbose]);
		// comment
		printf("3. Display the decompressed output: %s\n", onoff[*cat]);
		printf("4. Return to Main Menu\n");
		printf("\nEnter the setting to change, or return (1-4): ");
		scanf("%d", &set);
		if(set==4)
			return 0;
		else if(set==1)
			*enc=(*enc+1)%2;
		else if(set==2)
			*verbose=(*verbose+1)%2;
		else if(set==3)
			*cat=(*cat+1)%2;
	}
	return 0;
}

#endif /* ENV_VAR_H_ */
