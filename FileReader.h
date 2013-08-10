//
//  File.h
//  ResEye
//
//  Created by Renil Lacmane on 12/25/12.
//
//

#ifndef __ResEye__FileReader__
#define __ResEye__FileReader__

#include <list>

#include "GeneralException.h"

#include "vtkSmartPointer.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"


class FileReader{
public:
	vtkstd::string filename;
	
	vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > > outerElementsPointsList;
	vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > > innerElementsPointsList;
	
	vtkstd::string getFileName();
	void getAtomsListsFromFile(vtkstd::string filename);
		
};

#endif /* defined(__ResEye__FileReader__) */
