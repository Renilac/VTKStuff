//
//  main.cpp
//  ResEye
//
//  Created by Renil Lacmane on 10/30/12.
//
// -------------------------------------------------------------------

// VTK include files

// Common include Files
#include <list>
#include <string.h>
// Auxiliar include files
#include "TesterFile.h"
#include "FileReader.h"
#include "LODManager.h"
#include "ChunkManager.h"
#include "TypesManager.h"
#include "InfoManager.h"
#include "ProjectionManager.h"
#include "InputDataManager.h"
#include "GeneralException.h"
#include "vtkProperty.h"
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkRenderWindow.h>
#include <vtkCubeAxesActor.h>

int main(){
    
	try {
		vtkstd::cout << "Starting application.." << endl;
		
		// Another input call for file location (Qt) - TODO
		vtkstd::string filepath= "../../PDB Files/4hhb.pdb";
		//vtkstd::string filepath= "../../PDB Files/ethanol.pdb";
		//vtkstd::string filepath= "../../PDB Files/adrenaline.pdb";
		
		// Call Projection Manager
		ProjectionManager projectionManager;
		vtkSmartPointer<vtkRenderer> renderer = projectionManager.InitializeCanvas();
		
		// Actor simulation focus area
		vtkSmartPointer<vtkSphereSource> focusArea = vtkSmartPointer<vtkSphereSource>::New();
		focusArea->SetCenter(0.0, 0.0, 0.0);
		focusArea->SetRadius(10);
		focusArea->SetThetaResolution(9);
		focusArea->SetPhiResolution(9);
		focusArea->Update();
		vtkSmartPointer<vtkPolyDataMapper> focusMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		focusMapper->SetInputConnection(focusArea->GetOutputPort());
		vtkSmartPointer<vtkActor> focusAreaActor = vtkSmartPointer<vtkActor>::New();
		focusAreaActor->SetMapper(focusMapper);
		focusAreaActor->GetProperty()->SetOpacity(0.5);
		focusAreaActor->VisibilityOff();
		// ---
		
		// Axys Widget
		vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
		vtkSmartPointer<vtkOrientationMarkerWidget> widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
		widget->SetOutlineColor( 0.7, 0.7, 0.7 );
		widget->SetOrientationMarker( axes );
		widget->SetInteractor( renderer->GetRenderWindow()->GetInteractor());
		//widget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
		widget->SetEnabled( 1 );
		widget->InteractiveOff();
		// ---
		vtkstd::cout << "Focus Sphere and axys widget created.." << endl;
		
		// Call FileReader -> creates Array
		FileReader *fileReader = new FileReader();
		fileReader->getAtomsListsFromFile(filepath);
		// Criar placeholders
		vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > > innerElementsPointsList = fileReader->innerElementsPointsList;
		vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > > outerElementsPointsList = fileReader->outerElementsPointsList;
		
		// Call TypesManager
		TypesManager *typesManager = new TypesManager();
		vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > > innerActors = typesManager->createBallAndStickType(innerElementsPointsList);
		vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > > outerActors = typesManager->createVanDerWallsType(outerElementsPointsList);
		
		// ------------------------------------------- MeshManager Modules ---------------------------------
		
		// Call InputManager
		InputDataManager inputManager;
		inputManager.setInteractionBehaviourToWindow(renderer, focusAreaActor, innerActors, outerActors); // TODO Remover focusAreaActor
		
		// TODO - LODManager adiciona actors
		// Init structures
		for (vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > >::iterator it =  innerActors.begin(); it != innerActors.end(); ++it){
			for (vtkstd::list<vtkSmartPointer<vtkActor> >::iterator actors =  (*it).begin(); actors != (*it).end(); ++actors){
				renderer->AddActor(*actors);
			}
		}
		for (vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > >::iterator it =  outerActors.begin(); it != outerActors.end(); ++it){
			for (vtkstd::list<vtkSmartPointer<vtkActor> >::iterator actors =  (*it).begin(); actors != (*it).end(); ++actors){
				renderer->AddActor(*actors);
			}
		}
		renderer->AddActor(focusAreaActor);
		
		// Call InfoManager  - TODO if needed
		
		// Call ProjectionManager Render
		projectionManager.RenderProjection(renderer);
		// ...
		
		
		// -------- Tester, for experimental code
		//TesterFile tester;
		//tester.callTester(renderer);
		//cout << "Tester end processing!" << endl;
		// ----------------
		
		// TODO - fazer deletes
		
	} catch (GeneralException  & e) {
		e.getMessage();
	}
	
    return EXIT_SUCCESS;
}


/*
int main(){
    
	try {
		
		// Call Projection Manager
		ProjectionManager projectionManager;
		vtkSmartPointer<vtkRenderer> renderer = projectionManager.InitializeCanvas();
		// Actor simulation focus area
		vtkSmartPointer<vtkSphereSource> focusArea = vtkSmartPointer<vtkSphereSource>::New();
		focusArea->SetCenter(0.0, 0.0, 0.0);
		focusArea->SetRadius(10);
		focusArea->SetThetaResolution(9);
		focusArea->SetPhiResolution(9);
		focusArea->Update();
		vtkSmartPointer<vtkPolyDataMapper> focusMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		focusMapper->SetInputConnection(focusArea->GetOutputPort());
		vtkSmartPointer<vtkActor> focusAreaActor = vtkSmartPointer<vtkActor>::New();
		focusAreaActor->SetMapper(focusMapper);
		focusAreaActor->GetProperty()->SetOpacity(0.5);
		focusAreaActor->VisibilityOff();
		
		// Another input call for file location (Qt) - TODO
		//vtkstd::string filepath= "../../PDB Files/4hhb.pdb";
		vtkstd::string filepath= "../../PDB Files/ethanol.pdb";
		
		// Call FileReader -> creates Array
		FileReader *fileReader = new FileReader();
		vtkstd::list<vtkSmartPointer<vtkPoints> > elementsListWithCoords = fileReader->getAtomsListsFromFile(filepath);
		// Criar placeholders
		vtkstd::list<vtkSmartPointer<vtkPoints> > innerElementsList = fileReader->innerElementsList;
		vtkstd::list<vtkSmartPointer<vtkPoints> > outerElementsList = elementsListWithCoords;
		// Call TypesManager
		TypesManager *typesManager = new TypesManager();
		vtkstd::list<vtkSmartPointer<vtkActor> > innerActors = typesManager->createBallAndStickType(innerElementsList);
		vtkstd::list<vtkSmartPointer<vtkActor> > outerActors = typesManager->createVanDerWallsType(outerElementsList);
		
		// ------------------------------------------- MeshManager Modules ---------------------------------
		
		// Call InputManager
		InputDataManager inputManager;
		inputManager.setInteractionBehaviourToWindow(renderer, focusAreaActor, innerElementsList, outerElementsList);
		
		// Init structures
		for (vtkstd::list<vtkSmartPointer<vtkActor> >::iterator it =  innerActors.begin(); it != innerActors.end(); ++it){
			renderer->AddActor(*it);
		}
		for (vtkstd::list<vtkSmartPointer<vtkActor> >::iterator it =  outerActors.begin(); it != outerActors.end(); ++it){
			renderer->AddActor(*it);
		}
		renderer->AddActor(focusAreaActor);
		
		// Call InfoManager  - TODO if needed
		
		// -------- Tester, for experimental code
		//TesterFile tester;
		//tester.callTester(renderer);
		//cout << "Tester end processing!" << endl;
		// ----------------

		// TODO - fazer deletes
		
		// Axys Widget
		vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
		
		vtkSmartPointer<vtkOrientationMarkerWidget> widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
		widget->SetOutlineColor( 0.7, 0.7, 0.7 );
		widget->SetOrientationMarker( axes );
		widget->SetInteractor( renderer->GetRenderWindow()->GetInteractor());
		//widget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
		widget->SetEnabled( 1 );
		widget->InteractiveOff();

		// Call ProjectionManager Render
		projectionManager.RenderProjection(renderer);
		// ...
		
	} catch (GeneralException  & e) {
		e.getMessage();
	}

    return EXIT_SUCCESS;
}
*/