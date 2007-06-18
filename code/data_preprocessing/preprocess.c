
/* 
* This file is part of Equaked.
*
* Equaked is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* any later version.
*
* Equaked is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdio.h>
#include <string.h>

#include "preprocess.h"

#define LINE_MAX 256

FILE * orgfile = NULL;
FILE * prewfile = NULL;
FILE * postwfile = NULL;
FILE * cfgfile = NULL;

char * prew_pattern = "[PREW %d count_idx:%u, count_value:%u]";	
int prew_check = 3;

char * data_pattern = "%d";
int data_check = 1;

char * postw_pattern = "[POSTW]";

char buffer[LINE_MAX];
char fileid[8];

int main(int argc, char ** argv){

	int i = 0, data = 0;

	if (argc!=2){
		printf("[ERROR] Try with './preprocess [ROBOTID]'\n");
		return 1;
	}
	strcpy(fileid, argv[1]);

	sprintf(buffer, "d%s.dat", fileid);
	printf("[INFO] PreProcessing file '%s'\n", buffer);

	//open orig file
	orgfile = fopen(buffer, "r");
	if (orgfile == NULL){
		printf("[ERROR] Failed to open '%s'\n", buffer);
		return 1;
	}

	//create d[FILEID]prew.dat 
	sprintf(buffer, "d%sprew.dat", fileid);
	prewfile = fopen(buffer, "w");
	if (prewfile == NULL){
		printf("[ERROR] Failed to create '%s'\n", buffer);
		return 1;
	}

	//create d[FILEID]postw.dat 
	sprintf(buffer, "d%spostw.dat", fileid);
	postwfile = fopen(buffer, "w");
	if (postwfile == NULL){
		printf("[ERROR] Failed to create '%s'\n", buffer);
		return 1;
	}

	//create d[FILEID]postw.dat 
	sprintf(buffer, "d%scfg.dat", fileid);
	cfgfile = fopen(buffer, "w");
	if (cfgfile == NULL){
		printf("[ERROR] Failed to create '%s'\n", buffer);
		return 1;
	}

	unsigned int count_idx = 0;
	unsigned int count_value = 0;
	int widx = 0;

	//read orgfile line by line
	if (fgets(buffer, LINE_MAX, orgfile) == NULL){
		printf("[ERROR] Failed to read line 1\n");
		return 1;

	}
	if (sscanf(buffer, prew_pattern, &widx, &count_idx, &count_value) != prew_check){
		printf("[ERROR] Line 1 not well formated! Should be like %s, or it's %s\n", prew_pattern, buffer);
		return 1;
	}
	printf("[INFO] widx:%d, count_idx:%u, count_value:%u\n", widx, count_idx, count_value);

	//write data to cfg file
	fprintf(cfgfile, "%u\n", widx);
	fprintf(cfgfile, "%u\n", count_idx);
	fprintf(cfgfile, "%u\n", count_value);
	


	//read PREWINDOW_SIZE line
	for (i=0; i < PREWINDOW_SIZE; i++){
		
		if (fgets(buffer, LINE_MAX, orgfile) == NULL){
			printf("[ERROR] Failed to read line %d\n", i + 2);
			return 1;
		}

		//get data
		if (sscanf(buffer, data_pattern, &data) != data_check){
			printf("[ERROR] Line %d not well formated! Should be like %s, or it's %s\n", i+2, data_pattern, buffer);
		}
		//write data to prewfile
		fprintf(prewfile, "%s", buffer);
	}	

	//read 
	if (fgets(buffer, LINE_MAX, orgfile) == NULL){
		printf("[ERROR] Failed to read line %d\n", i + 2);
		return 1;
	}

	//read POSTWINDOW_SIZE line
	for (i=0; i < POSTWINDOW_SIZE; i++){
		
		if (fgets(buffer, LINE_MAX, orgfile) == NULL){
			printf("[ERROR] Failed to read line %d\n", PREWINDOW_SIZE + i + 3);
			return 1;
		}

		//get data
		if (sscanf(buffer, data_pattern, &data) != data_check){
			printf("[ERROR] Line %d not well formated! Should be like %s, or it's %s\n", PREWINDOW_SIZE + i + 3, data_pattern, buffer);
		}
		//write data to prewfile
		fprintf(postwfile, "%s", buffer);
	}	



	fclose(prewfile);
	fclose(cfgfile);
	fclose(postwfile);
	fclose(orgfile);
	return 0;
}
