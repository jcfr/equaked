
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
#ifndef _LISTENER_H_
#define _LISTENER_H_

#include <string>
#include <iostream>
#include <fstream>

namespace equaked {

typedef std::string String;


class Logger;  


class Listener {
	public:
		Listener(const String& dir, const String& id); 
		~Listener();
		void setConsoleLogger(Logger*); 
		const String& getId();
		bool isActive();
		bool isThread();
		bool init(Logger*); 
		bool listen(); 

	protected:
		void setActive(bool active);
 
	private:
		bool _isThread; 
		bool _isActive;
		String _id;
		String _dir; 
		Logger * _logger;
		Logger * _consolelogger; 
		std::ifstream serials;  
		
};

};

#endif //_LISTENER_H_