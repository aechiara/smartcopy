#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "smartcopy.h"

int main(int argc, char **argv)
{
	int c;
	char origFileName[FILENAME_MAX];
	char destFileName[FILENAME_MAX];

	if ( argc < 2 )
	{
		printUsage(argv[0]);
	}

	while ((c = getopt(argc, argv, "od:")) != -1) 
	{
		switch (c) 
		{
			case 'o':
				snprintf(origFileName, FILENAME_MAX, "%s", optarg);
				printf("original file=[%s]\n", origFileName);
				break;
			case 'd':
				snprintf(destFileName, FILENAME_MAX, "%s",optarg);
				printf("destination file=[%s]\n", destFileName);
				break;
			case '?':
				fprintf(stderr, "Unrecognized option  \n");
				break;
		}
	}

	fprintf(stderr, "optind=%d\n", optind);

	return ( 0 );
}
