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

#include <vtkPoints.h>
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
#include "vtkPolyDataMapper.h"

#include <vtkDataSet.h>
#include <vtkIdTypeArray.h>

// method declarations
void calculateAndTransferAtoms(vtkSmartPointer<vtkPoints> innerElementPoints, vtkSmartPointer<vtkPoints> outerElementPoints,
							   int elementCounter,double* focusCenter);
void ReallyDeletePoint(vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkIdTypeArray> id);
void insertPoint(vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkIdTypeArray> id, vtkSmartPointer<vtkPoints> previousPoints);

vtkstd::list<vtkSmartPointer<vtkActor> > LODManager::calculateLODActors(vtkstd::list<vtkSmartPointer<vtkActor> > actorsList){
	
	return actorsList;
}

vtkSmartPointer<vtkActorCollection> LODManager::calculateLODActors(vtkstd::list<vtkSmartPointer<vtkPoints> > innerElementsList,
																   vtkstd::list<vtkSmartPointer<vtkPoints> > outerElementsList, double* focusAreaCenter){
	//vtkSmartPointer<vtkActorCollection> LODManager::calculateLODActors(vtkstd::list<vtkSmartPointer<vtkPolyData> > elementsAtomPoints){
	
	int elementCounter = 0;  // TODO - rever
	
	// Insert the new point
	// then tell VTK that the data has been modified so the Render() call
	// will update the view with the new data
	vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator j = innerElementsList.begin();
	
	for(vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator i = outerElementsList.begin(); i != outerElementsList.end(); i++){
		
		vtkSmartPointer<vtkPoints> outerElementPoints = (*i);
		vtkSmartPointer<vtkPoints> innerElementPoints = (*j);
		
		calculateAndTransferAtoms(innerElementPoints, outerElementPoints, elementCounter, focusAreaCenter); // TODO mudar para receber a pos do picker
		
		vtkstd::cout << "counter: " << elementCounter << endl;
		elementCounter++;
		j++;
	}
	
	// Get inner and outer Actors
	// Change innner Actors properties, if inner LOD active
	// TODO - implementar ball and stick
	
	return NULL;
}

void calculateAndTransferAtoms(vtkSmartPointer<vtkPoints> innerElementPoints, vtkSmartPointer<vtkPoints> outerElementPoints, int elementCounter, double* focusCenter){
	/*
	 elementsPointsArray[0] = H_AtomPoints;
	 elementsPointsArray[1] = C_AtomPoints;
	 elementsPointsArray[2] = N_AtomPoints;
	 elementsPointsArray[3] = O_AtomPoints;
	 elementsPointsArray[4] = S_AtomPoints;
	 */
	
	//	if(elementCounter == 0){ // H_AtomPoints
	// Faltam me as bounds
	
	// Array of ids of points to be included in focus area
	vtkSmartPointer<vtkIdTypeArray> pointsIdsInsideFocus = vtkSmartPointer<vtkIdTypeArray>::New();
	
	for (int i = 0; i < innerElementPoints->GetNumberOfPoints(); i++){
		double *coords;
		
		if((coords = innerElementPoints->GetPoint(i))!=0){
			// (x-x0)^2 + (y-y0)^2 + (z-z0)^2 < r^2, inside of sphere equation
			if((coords[0] - focusCenter[0])*(coords[0] - focusCenter[0]) +
			   (coords[1] - focusCenter[1])*(coords[1] - focusCenter[1]) +
			   (coords[2] - focusCenter[2])*(coords[2] - focusCenter[2]) < (10*10) ){ // is inside focus sphere
				
				pointsIdsInsideFocus->InsertNextValue(i);
			} // TODO - confirmar formula
			
		}
	}	
	
	if(pointsIdsInsideFocus->GetNumberOfTuples()> 0){
		// Call insert of same points to outer element, repectively
		insertPoint(outerElementPoints, pointsIdsInsideFocus, innerElementPoints);
		innerElementPoints->Modified();
		outerElementPoints->Modified();
		// Call delete of points from inner element
		ReallyDeletePoint(innerElementPoints, pointsIdsInsideFocus);
		innerElementPoints->Modified();
		outerElementPoints->Modified();
	}
	
	// Array of ids of points to be included in outer area
	vtkSmartPointer<vtkIdTypeArray> pointsIdsOutsideFocus = vtkSmartPointer<vtkIdTypeArray>::New();
	
	for (vtkIdType i = 0; i < outerElementPoints->GetNumberOfPoints(); ++i){
		std::cout << "Number of outer points: " << outerElementPoints->GetNumberOfPoints() << std::endl;
		std::cout << "Current outer point id: " << i << std::endl;
		
		double *coords = NULL;
		if((coords = outerElementPoints->GetPoint(i)) != 0){
			
			// (x-x0)^2 + (y-y0)^2 + (z-z0)^2 < r^2, inside of sphere equation
			if((coords[0] - focusCenter[0])*(coords[0] - focusCenter[0]) +
			   (coords[1] - focusCenter[1])*(coords[1] - focusCenter[1]) +
			   (coords[2] - focusCenter[2])*(coords[2] - focusCenter[2]) < (10*10) ){  // is inside focus sphere
				
				pointsIdsOutsideFocus->InsertNextValue(i);
			}
		}
	}
	if(pointsIdsOutsideFocus->GetNumberOfTuples() > 0){
		// Call insert of same points to outer element, repectively
		insertPoint(innerElementPoints, pointsIdsOutsideFocus, outerElementPoints);
		innerElementPoints->Modified();
		outerElementPoints->Modified();
		// Call delete of points from inner element
		ReallyDeletePoint(outerElementPoints, pointsIdsOutsideFocus);
		innerElementPoints->Modified();
		outerElementPoints->Modified();
	}
	
	//	}
	//	else if(elementCounter == 1){
	//
	//	}
	//	else{
	//
	//	}
	
	//		polyData = sphereSource->GetOutput()->GetPoints()->InsertNextPoint(const float *x)
	
}

void ReallyDeletePoint(vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkIdTypeArray> ids){
	std::cout << "Number of points: " << points->GetNumberOfPoints() << std::endl;
	std::cout << "Number of points to remove: " << ids->GetNumberOfTuples() << std::endl;
	
	vtkSmartPointer<vtkPoints> newPoints = vtkSmartPointer<vtkPoints>::New();
	double* coords = NULL;
	
	for(vtkIdType i = 0 ; i < ids->GetNumberOfTuples(); i++){
		if( (coords = points->GetPoint(i))){
			std::cout << "Hello " << coords[0] << " " << coords[1] << " " << coords[2] << std::endl;
			
			newPoints->InsertNextPoint(coords);
		}
	}
	
	points->ShallowCopy(newPoints);
}

void insertPoint(vtkSmartPointer<vtkPoints> newPoints, vtkSmartPointer<vtkIdTypeArray> ids, vtkSmartPointer<vtkPoints> previousPoints){
	std::cout << "Number of points: " << newPoints->GetNumberOfPoints() << std::endl;
	std::cout << "Number of points to insert: " << ids->GetNumberOfTuples() << std::endl;
	
	double* coords = NULL;
	
	for(vtkIdType i = 0 ; i < ids->GetNumberOfTuples(); i++){
		if( (coords = previousPoints->GetPoint(i))){
			//std::cout << "Hello " << coords[0] << " " << coords[1] << " " << coords[2] << std::endl;
			newPoints->InsertNextPoint(coords);
		}
	}
}



