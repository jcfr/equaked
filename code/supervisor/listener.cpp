
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

bool Listener::isActive(){
	return this->_isActive; 
}

bool Listener::isThread(){
	return this->_isThread; 
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
		*_consolelogger<<"Failed to open "<<device<<NEWLINE; 
		setActive(false); 
		return false;
	} else {
		*_consolelogger<<device<<" ready !"<<NEWLINE;
		setActive(true);
	}

	return true;
}

void Listener::setActive(bool active){
	this->_isActive = active; 
}

bool Listener::listen(){
	String line; 
	while(_isActive){
		//read data from /dev/epuck[ID]
		std::getline(serials, line); 

		//write line into textfile
		*_logger<<line<<NEWLINE; 
		//*_consolelogger<<line<<NEWLINE;
	
		_logger->flush();
	
		if (!_isThread) break; 
	}
	return true;
}

}; 
