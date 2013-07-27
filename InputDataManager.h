//
//  InputDataManager.h
//  ResEye
//
//  Created by Renil Lacmane on 12/30/12.
//
//

#ifndef __ResEye__InputDataManager__
#define __ResEye__InputDataManager__

#include <iostream>

#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCubeSource.h>

class InputDataManager{
  
public:
	void setInteractionBehaviourToWindow (vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkActor> focusAreaActor);
	
private:
	void assignObserverInteractionMethod(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkActor> focusAreaActor);
	void assignStyleInteractionMethod(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkActor> focusAreaActor);

};

#endif /* defined(__ResEye__InputDataManager__) */
