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
	//vtkstd::cout << "Position (world coordinates) is: " << focusAreaCenter[0] << " " << focusAreaCenter[1] << " " << focusAreaCenter[2] << vtkstd::endl;
	
	//
	LODManager lodManager;
	lodManager.calculateLODActors(this->innerElementsList, this->outerElementsList, focusAreaCenter);
	
	iren->Modified();
	iren->GetRenderWindow()->Render();
}

// Styles
class MouseInteractorStyle4 : public vtkInteractorStyleTrackballCamera {
public:
    static MouseInteractorStyle4* New();
    vtkTypeMacro(MouseInteractorStyle4, vtkInteractorStyleTrackballCamera);
	
	virtual void OnMouseMove()
	{
		vtkstd::cout << "Position: " << vtkInteractorStyleTrackballCamera::GetInteractor()->GetEventPosition()[0]
		<< " " << vtkInteractorStyleTrackballCamera::GetInteractor()->GetEventPosition()[1] << vtkstd::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnMouseMove();
	}
	
    virtual void OnLeftButtonDown()
    {
		vtkstd::cout << "Pressed left mouse button." << vtkstd::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }
    
    virtual void OnMiddleButtonDown()
    {
		vtkstd::cout << "Pressed middle mouse button." << vtkstd::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
    }
    
    virtual void OnRightButtonDown()
    {
		vtkstd::cout << "Pressed right mouse button." << vtkstd::endl;
		// Forward events
		vtkInteractorStyleTrackballCamera::OnRightButtonDown();
    }
	
};

vtkStandardNewMacro(MouseInteractorStyle4);

