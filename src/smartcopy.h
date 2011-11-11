
#ifndef __smartcopy_h
#define __smartcopy_h

#include <stdio.h>
#include "project_defines.h"

void printUsage(char* execName)
{
	printf("%s - version %d.%d\n", EXEC_NAME, MAJOR_VERSION, MINOR_VERSION);
	printf("\tUsage: %s -o <original_file> -d <destination_file>\n", execName);
}



#endif
