//
//  ProjectionManager.cpp
//  ResEye
//
//  Created by Renil Lacmane on 12/30/12.
//
//

#include "ProjectionManager.h"

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCallbackCommand.h>

vtkSmartPointer<vtkRenderer> ProjectionManager::InitializeCanvas(){
    
    // is the class you will use to create the renderer which will draw in the window
    vtkSmartPointer<vtkRenderer> renderer = vtkRenderer::New();
    //renderer->SetBackground(0, 0, 0);
    renderer ->SetBackground(0.8, 0.8, 0.8);
	
	// vtkRenderWindow is the class you will use to create a window
    // The vtkRenderWindow is a container class for vtkRenderer objects
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkRenderWindow::New();
    renderWindow->SetSize(600, 600);
    
    renderWindow->AddRenderer(renderer);
    // renWin->Render(); // não funca
    
    // In order to interact with the scene using the mouse we will use an instance of vtkRenderWindowInteractor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkRenderWindowInteractor::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    
    return renderer;
}

void ProjectionManager::RenderProjection(vtkSmartPointer<vtkRenderer> renderer){
    
	// Assign a smartPoint for a previously defined renderWindowInteractor
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = renderer->GetRenderWindow()->GetInteractor();

    // Starts the event loop and invokes an initiar render
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

}