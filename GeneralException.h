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

#include <vtkstd/string>

class GeneralException {
	vtkstd::string message;
	
public:
	GeneralException(vtkstd::string message){
		this->message = message;
	}
	
	void getMessage();
};


#endif /* defined(__ResEye__GeneralException__) */