
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
#include <iostream>
#include <ctime>
#include <sstream>

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


#include "logger.h"
#include "listener.h"

#define PROJECT_NAME "Equaked"
#define PROJECT_VER "0.0.1"
#define MAX_HORDSIZE 16
#define DATADIRECTORY "/home/fillion/si_project/data/"

using namespace equaked;

Logger logger; 

void run(char * rid){
	bool running = true;
	
	Listener * hord[MAX_HORDSIZE];
	for (int i=0; i < MAX_HORDSIZE; i++){hord[i]=NULL; }

	//create a new data sub-directory
	std::ostringstream dir_os; 
	dir_os<<DATADIRECTORY<<time(0)<<"/";

	//create directory
	if (mkdir(dir_os.str().c_str(), 0700)!=0){
		logger<<"Failed to create directory "<<dir_os.str()<<NEWLINE;
		logger<<"=>"<<strerror(errno)<<NEWLINE;
		return; 
	} else {
		logger<<dir_os.str()<<" created"<<NEWLINE;
	}
	
 
	hord[0] = new Listener(dir_os.str().c_str(), rid);
	//hord[1] = new Listener(dir_os.str().c_str(), "58");
	//hord[2] = new Listener(dir_os.str().c_str(), "57"); 
	
	//init units
	logger<<"Initializing robots ..."<<NEWLINE;
	for(int i=0; hord[i]!=NULL && running; i++){ running = hord[i]->init(&logger); }

	logger<<"Listening robots ..."<<NEWLINE;
	//listen units
	while(running){
		for(int i=0; hord[i]!=NULL && running; i++){
			running = hord[i]->listen(); 
		}
	}
}

int main(int argc, char* argv[]){
	logger<<PROJECT_NAME<<" supervisor module - "<<PROJECT_VER<<NEWLINE; 

	if (argc!=2){
		logger<<"missing argument, try ./supervisor [#ID]"<<NEWLINE;
		return 1;
	}	
	//TODO: check argument value, should be an integer
	run(argv[1]); 

	return 0;
}
