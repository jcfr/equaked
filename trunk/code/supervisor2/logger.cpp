
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
#include "logger.h"

#include <iostream>

namespace equaked {

Logger::Logger(const String& file, bool enable){
	if (file.length()==0){
		_os = &std::cout; 
	} else {
		_os = new std::ofstream(file.c_str());
	}
	this->_enable = enable; 
}

Logger::~Logger(){
	std::ofstream * fos = dynamic_cast<std::ofstream*>(_os); 
	if (fos!=NULL) fos->close(); 
}

void Logger::flush(){
	_os->flush();
}

void Logger::setEnable(bool enable){
	this->_enable = enable; 
}

bool Logger::isEnable(){
	return this->_enable; 
}

void Logger::info(const char *  message){
	if (_enable){
		*this->getOs()<<message; 
	}
}

std::ostream* Logger::getOs(){
	return this->_os; 
}

Logger& operator<<(Logger& l, const String& str){
	if (l.isEnable()){ *l.getOs()<<str; }
	return l;
}


Logger& operator<<(Logger& l, const char* str){
	if (l.isEnable()){ *l.getOs()<<str; }
	return l; 
}

Logger& operator<<(Logger& l, int i){
	if (l.isEnable()){ *l.getOs()<<i; }
	return l;
}
 
};

