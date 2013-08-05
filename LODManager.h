//
//  LODManager.h
//  ResEye
//
//  Created by Renil Lacmane on 12/30/12.
//
//

#ifndef __ResEye__LODManager__
#define __ResEye__LODManager__

#include <iostream>

#include <vtkSmartPointer.h>
#include <vtkstd/list>
#include <vtkActor.h>
#include <vtkPoints.h>

#include <vtkDataSet.h>

class LODManager{
    
public:
    vtkSmartPointer<vtkActorCollection> calculateLODActors(vtkstd::list<vtkSmartPointer<vtkPoints> > innerElementsList, vtkstd::list<vtkSmartPointer<vtkPoints> > outerElementsList, double* focusAreaCenter);
};

#endif /* defined(__ResEye__LODManager__) */
