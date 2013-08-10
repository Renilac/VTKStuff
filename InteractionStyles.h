//
//  InteractionStyles.h
//  ResEye
//
//  Created by Renil Lacmane on 7/23/13.
//
//

#ifndef __ResEye__InteractionStyles__
#define __ResEye__InteractionStyles__

#include <iostream>

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCommand.h>
#include <vtkstd/list>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>

class vtkMouseMoveCallback : public vtkCommand{

private:
    int x, y, z;
public:
    vtkActor* actor;
	vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > > innerElementsList;
	vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > > outerElementsList;
	
    static vtkMouseMoveCallback *New() {
		vtkMouseMoveCallback *callback = new vtkMouseMoveCallback;
		return callback;
	}
	
    virtual void Execute(vtkObject *caller, unsigned long eventId, void * vtkNotUsed(callData));

};



#endif /* defined(__ResEye__InteractionStyles__) */