
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
#include "listener.h"

#include <stdio.h>
#include <errno.h>

#include "common.h"
#include "utils.h"
#include "logger.h"
#include "./../data_preprocessing/preprocess.h"

namespace equaked {

Listener::Listener(const String& dir, const String& id = "0"){
	this->_id = id;
	this->_dir = dir; 
}

Listener::~Listener(){
}

void Listener::setConsoleLogger(Logger * l){
	this->_consolelogger = l; 
}

const String& Listener::getId() {
	return this->_id;
}

bool Listener::init(Logger * consolelogger){
	setConsoleLogger(consolelogger); 
	_logger = new Logger(_dir+"d"+_id+".dat");
	String device = "/dev/rfcomm";
	device +=_id;
	
	serials.open(device.c_str());
	if (!serials.is_open()){
		*_consolelogger<<"[ERROR] Failed to open "<<device<<" in {read} mode"<<NEWLINE; 
		return false;
	} else {
		*_consolelogger<<device<<"[INFO] {read} mode ready !"<<NEWLINE;
	}

	oserials.open(device.c_str());
	if (!oserials.is_open()){
		*_consolelogger<<"[ERROR] Failed to open "<<device<<" in {write} mode"<<NEWLINE; 
		return false;
	} else {
		*_consolelogger<<device<<"[INFO] {write} mode ready ! "<<NEWLINE;
	}
	return true;
}


void Listener::close(){
	*_consolelogger<<"[INFO] Close {read, write} communication channels"<<NEWLINE;
	serials.close();
	oserials.flush();
	oserials.close();	
}

bool Listener::listen(){
	String line; 
	char c;
	int count = 0;

	*_consolelogger<<"[INFO] Init transmission"<<NEWLINE;

	//send '1' to start transmission
	oserials<<'1';

	oserials.flush();

	*_consolelogger<<"[INFO] Receiving data ..."<<NEWLINE;

	for(count=0; count < FILE_TOTAL_SIZE; count++){
		//*_consolelogger<<"get("<<count<<")"<<NEWLINE;

		//read data from /dev/epuck[ID]
		std::getline(serials, line); 

		//write line into textfile
		*_logger<<line<<NEWLINE; 
		//*_consolelogger<<line<<NEWLINE;
	
		_logger->flush();	

	}
	return true;
}

}; 
