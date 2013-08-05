//
//  GeneralException.cpp
//  ResEye
//
//  Created by Renil Lacmane on 7/10/13.
//
//

#include "GeneralException.h"
#include "Utils.h"

#include <vtkstd/string>

void GeneralException::getMessage(){
	Utils utils;
	
	vtkstd::cout << "Exception " << utils.currentDateTime() << ": "  << this->message << vtkstd::endl;
}