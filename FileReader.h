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

#include "vtkSmartPointer.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"


class FileReader{
public:
	vtkstd::string filename;
	vtkstd::list<vtkSmartPointer<vtkPoints> > innerElementsList;
	vtkstd::list<vtkSmartPointer<vtkPoints> >  atomGroupedCoordsList;
	
public:
	vtkstd::string getFileName();
	vtkstd::list<vtkSmartPointer<vtkPoints> > getAtomsListsFromFile(vtkstd::string filename);
		
};

#endif /* defined(__ResEye__FileReader__) */
