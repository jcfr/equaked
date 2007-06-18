
#ifndef _UTILS_H_
#define _UTILS_H_

#include <string.h>

#include "common.h"

class Utils {
	public:
		static void strcpy(char * dest, const char * src){

			int src_strlen = strnlen(src, MAXSTRLEN); 
			dest = new char[src_strlen];
			strncpy(dest, src, src_strlen-1);
			dest[src_strlen-1] = '\0'; 
		}
}; 
 
#endif //_UTILS_H_
