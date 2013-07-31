
#ifndef __smartcopy_h
#define __smartcopy_h

#include <stdio.h>
#include "project_defines.h"

void printUsage(char* execName)
{
	printf("%s - version %d.%d\n", EXEC_NAME, MAJOR_VERSION, MINOR_VERSION);
	printf("\tUsage: %s -f -y -o <original_file> -d <destination_file>\n", execName);
}

long getFileSize(FILE *fileDescriptor)
{
	long lastPosition = 0L;
	long fileSize = 0L;

	lastPosition = ftell(fileDescriptor);
	fseek(fileDescriptor, 0, SEEK_END);
	fileSize = ftell(fileDescriptor);
	fseek(fileDescriptor, 0, lastPosition);

	return ( fileSize );
}

double calcPercCompleted(long parcial, long total)
{
	double perc = 0.0f;

	if ( 0L < parcial )
	{
		perc = (double)((100.0f * parcial) / (double)total);
		//printf("\rparcial: [%ld] - total [%ld] - perc: [%3.2f]\t\t\t\t", parcial, total, perc);
	}

	return ( perc );
}

#endif
