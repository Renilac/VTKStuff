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
#include "vtkCommand.h"

#endif /* defined(__ResEye__InteractionStyles__) */

class InteractionStyles{
	
	class MouseInteractorStyle4 : public vtkInteractorStyleTrackballCamera {};
	
public:
	
	void KeypressCallbackFunction(vtkObject* caller, long unsigned int vtkNotUsed(eventId), void* clientData, void* vtkNotUsed(callData) ){};
};

class vtkMouseMoveCallback : public vtkCommand{

private:
    int x, y, z;
public:
    vtkActor* actor;
	
public:
    static vtkMouseMoveCallback *New() {
		vtkMouseMoveCallback *callback = new vtkMouseMoveCallback;
		//cb->TimerCount = 0;
		return callback;
	}
	
    virtual void Execute(vtkObject *caller, unsigned long eventId, void * vtkNotUsed(callData));

};