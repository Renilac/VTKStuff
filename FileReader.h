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
		std::list<vtkSmartPointer<vtkPoints> > getAtomsListsFromFile(std::string filename);
		std::string filename;
		std::string getFileName();
		void handleAtoms();
};

#endif /* defined(__ResEye__FileReader__) */
