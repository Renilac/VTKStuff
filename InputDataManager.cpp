//
//  InputDataManager.cpp
//  ResEye
//
//  Created by Renil Lacmane on 12/30/12.
//
//

#include "InputDataManager.h"
#include "InteractionStyles.h"

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCallbackCommand.h>


// Reconsiderar
#include <vtkSmartPointer.h>
#include <vtkPointPicker.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkProperty.h>

#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkCubeSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkPoints.h>
// REconsiderar
#include <vtkPolyDataMapper.h>
#include <vtkCubeSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

void InputDataManager::setInteractionBehaviourToWindow(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkActor> focusAreaActor, vtkstd::list<vtkSmartPointer<vtkPoints> > innerElementsList, vtkstd::list<vtkSmartPointer<vtkPoints> > outerElementsList){
	assignObserverInteractionMethod(renderer, focusAreaActor, innerElementsList, outerElementsList);
	//assignStyleInteractionMethod(renderer);
}

void InputDataManager::assignObserverInteractionMethod(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkActor> focusAreaActor, vtkstd::list<vtkSmartPointer<vtkPoints> > innerElementsList, vtkstd::list<vtkSmartPointer<vtkPoints> > outerElementsList){
	//InteractionStyles inter;
	
	// Sign up to receive Event
	vtkSmartPointer<vtkMouseMoveCallback> callback = vtkSmartPointer<vtkMouseMoveCallback>::New();
	callback->actor = focusAreaActor;
	//callback->pointsList = points;
	callback->innerElementsList = innerElementsList;
	callback->outerElementsList = outerElementsList;
	renderer->GetRenderWindow()->GetInteractor()->AddObserver(vtkCommand::MouseMoveEvent, callback);
	
	
}

void InputDataManager::assignStyleInteractionMethod(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkActor> focusAreaActor, vtkstd::list<vtkSmartPointer<vtkPoints> > points){
	
	//vtkSmartPointer<MouseInteractorStyle4> style = vtkSmartPointer<MouseInteractorStyle4>::New();
	//renderer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(style);
}

