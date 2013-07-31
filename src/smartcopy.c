#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "smartcopy.h"

int main(int argc, char **argv)
{
	int c;
	char origFileName[FILENAME_MAX];
	char destFileName[FILENAME_MAX];
	FILE *oFile, *dFile;
	char* buffer;
	long oFSize, dFSize, totalWrited, tmpCount;
	size_t fret;

	int DO_NOT_CONFIRM = 0;
	int isForce = 0;

	if ( argc < 2 )
	{
		printUsage(argv[0]);
		exit(-1);
	}

	while ((c = getopt(argc, argv, "o:d:fy")) != -1) 
	{
		switch (c) 
		{
			case 'o':
				snprintf(origFileName, FILENAME_MAX, "%s", optarg);
				//printf("original file=[%s]\n", origFileName);
				break;
			case 'd':
				snprintf(destFileName, FILENAME_MAX, "%s", optarg);
				//printf("destination file=[%s]\n", destFileName);
				break;
			case 'f':
				isForce = 1;
				break;
			case 'y':
				DO_NOT_CONFIRM = 1;
				break;
			case '?':
				fprintf(stderr, "Unrecognized option  \n");
				break;
		}
	}

	//fprintf(stderr, "optind=%d\n", optind);
	
	if ( optind < 5 )
	{
		printUsage(argv[0]);
		exit(-1);
	}


	oFSize = dFSize = 0;

	if (( oFile = fopen(origFileName, "r")) == NULL )
	{
		fprintf(stderr, "Impossible to open original File [%s]\n", origFileName);
		exit(-2);
	}

	if (( dFile = fopen(destFileName, "a+")) == NULL )
	{
		// close oFile
		fclose(oFile);
		fprintf(stderr, "Impossible to open destination File [%s]\n", destFileName);
		exit(-2);
	}

	oFSize = getFileSize(oFile);
	dFSize = getFileSize(dFile);

	/* 
	 * if destination File size is ZERO
	 * set original file's cursor to beginning of the file
	 * else set both cursors at the same position
	 * that is the destination sile size
	 */
	if ( dFSize == 0L )
	{
		fseek(oFile, 0, SEEK_SET);
	}
	else 
	{
		fseek(oFile, dFSize, SEEK_SET);
		fseek(dFile, dFSize, SEEK_SET);
		totalWrited = dFSize;
	}

	// print sumary
	printf("Original File [%s] Size is [%ld]\n", origFileName, oFSize);
	printf("Destination File [%s] Size is [%ld] - [%3.2f%%] completed\n", destFileName, dFSize, calcPercCompleted(totalWrited, oFSize));
	printf("Force Flush is [%s]\n", (isForce == 1 ? "TRUE" : "FALSE"));
	
	if ( ! DO_NOT_CONFIRM )
	{
		printf("press enter to continue ...\n");
		getchar();
	}
	else
	{
		printf("Do not Confirm is [TRUE]\n");
	}

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	
	fret = 0;
	tmpCount = 0;

	while ( ! feof(oFile) )
	{
		memset(buffer, 0, sizeof(buffer));
		fret = fread(buffer, 1, BUFFER_SIZE, oFile);
		tmpCount = fwrite(buffer, 1, fret, dFile);
		totalWrited += tmpCount;

		printf("\rcopied [%ld] from [%ld] - [%3.2f]%% completed\t\t\t\t", totalWrited, oFSize, calcPercCompleted(totalWrited, oFSize));

		if ( isForce )
		{
			fflush(dFile);
		}
	}
	printf("\n");


	free(buffer);
	fclose(oFile);
	fclose(dFile);

	return ( 0 );
}
