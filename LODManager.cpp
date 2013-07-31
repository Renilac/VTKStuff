//
//  LODManager.cpp
//  ResEye
//
//  Created by Renil Lacmane on 12/30/12.
//
//

#include "LODManager.h"
#include "TypesManager.h"

#include <vtkActorCollection.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>

vtkstd::list<vtkSmartPointer<vtkActor> > LODManager::calculateLODActors(vtkstd::list<vtkSmartPointer<vtkActor> > actorsList){
	
	return actorsList;
}

vtkSmartPointer<vtkActorCollection> LODManager::calculateLODActors(vtkSmartPointer<vtkActorCollection> actorsList){
	
	// Reset Counter
	actorsList->InitTraversal();
	vtkSmartPointer<vtkActor> first = actorsList->GetNextActor();
	
	// Get inner and outer Actors
	
	// Change innner Actors properties, if inner LOD active
	TypesManager *typesManager = new TypesManager(); // preciso de cria-lo em cada movimento??
	std::list<vtkSmartPointer<vtkActor> > typeStructure = typesManager->convertToBallAndStickType(actorsList); // TODO - implementar ball and stick
	
	//
	
	actorsList->GetLastActor()->Print(std::cout);
	first->VisibilityOff();
	//actorsList->;
	
	
//	vtkCollection *c;
//	vtkObject *o;
//	
//	c->InitTraversal();
//	o=c->GetNextItem();
//	while(o!=0)
//	{
//		// process o
//		// ...
//		
//		// next step
//		o=c->GetNextItem();
//	} 

	
	return actorsList;
}