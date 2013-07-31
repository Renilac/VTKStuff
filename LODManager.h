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

class LODManager{
    
public:
	vtkstd::list<vtkSmartPointer<vtkActor> > calculateLODActors(vtkstd::list<vtkSmartPointer<vtkActor> > actorsList);
    vtkSmartPointer<vtkActorCollection> calculateLODActors(vtkSmartPointer<vtkActorCollection> actorsList);
};

#endif /* defined(__ResEye__LODManager__) */
