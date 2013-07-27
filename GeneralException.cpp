//
//  GeneralException.cpp
//  ResEye
//
//  Created by Renil Lacmane on 7/10/13.
//
//

#include "GeneralException.h"
#include "Utils.h"

void GeneralException::getMessage(){
	Utils utils;
	
	std::cout << "Exception " << utils.currentDateTime() << ": "  << this->message << std::endl;
}