//
//  InteractionStyles.cpp
//  ResEye
//
//  Created by Renil Lacmane on 7/23/13.
//
//
// Definition of interaction styles


#include "InteractionStyles.h"

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

#include <vtkPropPicker.h>
#include <vtkRenderWindow.h>
#include <vtkCommand.h>

#include <vtkRendererCollection.h>
#include <vtkRenderer.h>
#include <vtkActorCollection.h>

#include "LODManager.h"

// Styles
class MouseInteractorStyle4 : public vtkInteractorStyleTrackballCamera {
public:
    static MouseInteractorStyle4* New();
    vtkTypeMacro(MouseInteractorStyle4, vtkInteractorStyleTrackballCamera);
	
	virtual void OnMouseMove()
	{
		std::cout << "Position: " << vtkInteractorStyleTrackballCamera::GetInteractor()->GetEventPosition()[0]
		<< " " << vtkInteractorStyleTrackballCamera::GetInteractor()->GetEventPosition()[1] << std::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnMouseMove();
	}
	
    virtual void OnLeftButtonDown()
    {
		std::cout << "Pressed left mouse button." << std::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }
    
    virtual void OnMiddleButtonDown()
    {
		std::cout << "Pressed middle mouse button." << std::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
    }
    
    virtual void OnRightButtonDown()
    {
		std::cout << "Pressed right mouse button." << std::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnRightButtonDown();
    }
	
};

vtkStandardNewMacro(MouseInteractorStyle4);

// Class vtkMouseMoveCallback
void vtkMouseMoveCallback::Execute(vtkObject *caller, unsigned long eventId, void * vtkNotUsed(callData)) {
	
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::SafeDownCast(caller);
	actor->VisibilityOn();
	
	// Pick from this location.
	int* clickPos = iren->GetEventPosition();
	vtkSmartPointer<vtkPropPicker>  picker = vtkSmartPointer<vtkPropPicker>::New();
	picker->Pick(clickPos[0], clickPos[1], 0, iren->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
	
	double* focusAreaCenter = picker->GetPickPosition();
	actor->SetPosition(focusAreaCenter[0], focusAreaCenter[1], focusAreaCenter[2]);
	//std::cout << "Position (world coordinates) is: " << focusAreaCenter[0] << " " << focusAreaCenter[1] << " " << focusAreaCenter[2] << std::endl;
	
	//
	LODManager lodManager;
	lodManager.calculateLODActors(this->innerElementsList, this->outerElementsList, focusAreaCenter);
	
	iren->Modified();
	iren->GetRenderWindow()->Render();
}


/*etet
 class vtkMouseMoveCallback : public vtkCommand {
 
 private:
 //int TimerCount;
 int x, y, z;
 public:
 vtkActor* actor;
 
 public:
 static vtkMouseMoveCallback *New()
 {
 vtkMouseMoveCallback *cb = new vtkMouseMoveCallback;
 //cb->TimerCount = 0;
 return cb;
 }
 
 virtual void Execute(vtkObject *caller, unsigned long eventId, void * vtkNotUsed(callData)) {
 //if (vtkCommand::TimerEvent == eventId){
 //	++this->TimerCount;
 //}
 //std::cout << this->TimerCount << std::endl;
 
 vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::SafeDownCast(caller);
 
 this->x = iren->GetEventPosition()[0];
 this->y = iren->GetEventPosition()[1];
 this->z = iren->GetEventPosition()[2];
 
 actor->SetPosition(this->x, this->y, this->z);
 std::cout << "position: "<< this->x << " " << this->x << " " << this->z << " " << std::endl;
 
 iren->GetRenderWindow()->Render();
 }
 };
 */


// ------------------- Callback functions ------------------
/*
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
 */