//
//  GeneralException.h
//  ResEye
//
//  Created by Renil Lacmane on 7/10/13.
//
//

#ifndef __ResEye__GeneralException__
#define __ResEye__GeneralException__

#include <iostream>
#include <string>

#endif /* defined(__ResEye__GeneralException__) */

class GeneralException {
	std::string message;
	
public:
	GeneralException(std::string message){
		this->message = message;
	}
	
	void getMessage();
};


