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

// Styles
class MouseInteractorStyle4 : public vtkInteractorStyleTrackballCamera {
public:
    static MouseInteractorStyle4* New();
    vtkTypeMacro(MouseInteractorStyle4, vtkInteractorStyleTrackballCamera);
	
	virtual void OnMouseMove(){
		std::cout << "Position: " << vtkInteractorStyleTrackballCamera::GetInteractor()->GetEventPosition()[0]
		<< " " << vtkInteractorStyleTrackballCamera::GetInteractor()->GetEventPosition()[1] << std::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnMouseMove();
	}
	
    virtual void OnLeftButtonDown(){
		std::cout << "Pressed left mouse button." << std::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }
    
    virtual void OnMiddleButtonDown(){
		std::cout << "Pressed middle mouse button." << std::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
    }
    
    virtual void OnRightButtonDown(){
		std::cout << "Pressed right mouse button." << std::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnRightButtonDown();
    }
	
};

// REconsiderar
#include <vtkPolyDataMapper.h>
#include <vtkCubeSource.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
void KeypressCallbackFunction(vtkObject* caller, long unsigned int vtkNotUsed(eventId), void* clientData, void* vtkNotUsed(callData) ){
	
	// get render window interactor
	vtkRenderWindowInteractor *iren = static_cast<vtkRenderWindowInteractor*>(caller);
	
	int * pos = iren->GetEventPosition();
	cout << "Position: " << pos[0] << " " << pos[1] << endl;
	
	// Prove that we can access the cube source
	vtkCubeSource* source = static_cast<vtkCubeSource*>(clientData);
	//source->SetCenter(pos[0], pos[1], 0.0);
	//source->Update();
	
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	// hmm
	vtkSmartPointer<vtkPolyDataMapper> focusMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	focusMapper->SetInputConnection(source->GetOutputPort());
	vtkSmartPointer<vtkActor> focusAreaActor = vtkSmartPointer<vtkActor>::New();
	focusAreaActor->SetMapper(focusMapper);
	vtkPolyData* polydata = vtkPolyData::SafeDownCast(focusAreaActor->GetMapper()->GetInputAsDataSet());
	//
	
	transform->SetMatrix(focusAreaActor->GetMatrix());
	
	vtkSmartPointer<vtkTransformPolyDataFilter> transformPolyData = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
#if VTK_MAJOR_VERSION <= 5
	transformPolyData->SetInputConnection(polydata->GetProducerPort());
#else
	transformPolyData->SetInputData(source);
#endif
	
	transform->Translate(pos[0], pos[1], 0.0);
	transformPolyData->SetTransform(transform);
	
	polydata->Modified();
	//this->Data->Modified();
	
	transformPolyData->Update();
	
	std::cout << "Center is " << source->GetCenter()[0] << " " << source->GetCenter()[1] << " " << source->GetCenter()[2] <<std::endl;
}

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
	
	/*
	vtkSmartPointer<vtkCallbackCommand> keypressCallback = vtkSmartPointer<vtkCallbackCommand>::New();
	// Allow the observer to access the sphereSource
	keypressCallback->SetClientData(focusArea);		// duvida
	keypressCallback->SetCallback(KeypressCallbackFunction );
	
	//renderWindowInteractor->AddObserver(vtkCommand::MouseMoveEvent, keypressCallback);
	renderer->GetRenderWindow()->GetInteractor()->AddObserver(vtkCommand::MouseMoveEvent, keypressCallback);
	*/
}

void InputDataManager::assignStyleInteractionMethod(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkActor> focusAreaActor, vtkstd::list<vtkSmartPointer<vtkPoints> > points){
	//InteractionStyles inter;
	
	vtkSmartPointer<MouseInteractorStyle4> style = vtkSmartPointer<MouseInteractorStyle4>::New();
	//renderWindowInteractor->SetInteractorStyle(style);
	renderer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(style);
}

