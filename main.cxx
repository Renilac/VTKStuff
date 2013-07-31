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

// -------------------------------------------------------------------

//using namespace std;

int main(){
    
	try {
		// Another input call for file location (Qt) - TODO
		std::string filepath= "../../PDB Files/4hhb.pdb";
		// Call FileReader -> creates Array
		FileReader *fileReader = new FileReader();
		std::list<vtkSmartPointer<vtkPoints> > atomsLists = fileReader->getAtomsListsFromFile(filepath);
		// Call Projection Manager
		ProjectionManager projectionManager;
		vtkSmartPointer<vtkRenderer> renderer = projectionManager.InitializeCanvas();
		
		// Actor simulation focus area
		//vtkSmartPointer<vtkCubeSource> focusArea = vtkSmartPointer<vtkCubeSource>::New();
		//focusArea->SetBounds(-10, 10, -10, 10, -10, 10);
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
		
		
		
//		vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();
//		cubeAxesActor->SetBounds(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
//		cubeAxesActor->SetCamera(renderer->GetActiveCamera());
//		
//		renderer->AddActor(cubeAxesActor);
		// ----
		
		// Call InputManager
		InputDataManager inputManager;
		inputManager.setInteractionBehaviourToWindow(renderer, focusAreaActor);
		// TODO - decidir types a inicializar
		// converter depois
		// Call TypesManager
		// Init structure type
		TypesManager *typesManager = new TypesManager();
		std::list<vtkSmartPointer<vtkActor> > typeStructure = typesManager->convertToVanDerWallsType(atomsLists); // TODO - implementar ball and stick
	   
		// ---------------------------------------------------------------- MeshManager Modules ---------------------------------
		// Call LODManager -> returns 3 Arrays
//		LODManager lodManager;
//		vtkstd::list<vtkSmartPointer<vtkActor> > lodGroupedActors = lodManager.calculateLODActors(typeStructure); // TODO - implementar
		
		// Add Actors to renderer
		for (std::list<vtkSmartPointer<vtkActor> >::iterator it =  typeStructure.begin(); it != typeStructure.end(); ++it){
			renderer->AddActor(*it);
		}
		renderer->AddActor(focusAreaActor);
		
		// Call InfoManager  - TODO if needed
		
		
		// -------- Tester, for experimental code
	   // TesterFile tester;
		//tester.callTester(renderer);
		//cout << "Tester end processing!" << endl;
		// ----------------

		
		// Axys Widget (falta instalar widgets)
		vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
		
		vtkSmartPointer<vtkOrientationMarkerWidget> widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
		widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
		widget->SetOrientationMarker( axes );
		widget->SetInteractor( renderer->GetRenderWindow()->GetInteractor());
		widget->SetViewport( 0.0, 0.0, 0.4, 0.4 );
		widget->SetEnabled( 1 );
		widget->InteractiveOn();
		
		// Call ProjectionManager Render
		projectionManager.RenderProjection(renderer);
		// ...

		// -------- Exemplos - TODO remover
		// exemplo de testes com esferas
		//SpecularSpheresExample spheres;
		//spheres.handleSpheresExample();
		
		// FileReader * Mothra= new FileReader(); ->
		//FileReader fr;
		//fr.handleAtoms();
		
		// -----------------

	} catch (GeneralException  & e) {
		e.getMessage();
	}

    return EXIT_SUCCESS;
}