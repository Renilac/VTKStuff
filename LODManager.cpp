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

// Method declarations
void calculateAndTransferAtoms(vtkSmartPointer<vtkPoints> innerElementPoints, vtkSmartPointer<vtkPoints> outerElementPoints,
							   int elementCounter,double* focusCenter);

void ReallyDeletePoint(vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkIdTypeArray> id);
void insertPoint(vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkIdTypeArray> id, vtkSmartPointer<vtkPoints> previousPoints);

// Method implementations
vtkSmartPointer<vtkActorCollection> LODManager::calculateLODActors(vtkstd::list<vtkSmartPointer<vtkPoints> > innerElementsList,
																   vtkstd::list<vtkSmartPointer<vtkPoints> > outerElementsList, double* focusAreaCenter){
	// Insert the new point
	// then tell VTK that the data has been modified so the Render() call
	// will update the view with the new data
	// Get inner and outer Actors
	// Change innner Actors properties, if inner LOD active
	// TODO - implementar ball and stick, Faltam me as bounds
	
	int elementCounter = 0;  // TODO - rever
	vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator j = innerElementsList.begin();
	
	for(vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator i = outerElementsList.begin(); i != outerElementsList.end(); i++){
		
		vtkSmartPointer<vtkPoints> outerElementPoints = (*i);
		vtkSmartPointer<vtkPoints> innerElementPoints = (*j);
		
		calculateAndTransferAtoms(innerElementPoints, outerElementPoints, elementCounter, focusAreaCenter); // TODO mudar para receber a pos do picker
		
		vtkstd::cout << "counter: " << elementCounter << endl;
		elementCounter++;
		j++;
		
		// Bounds TODO - Não parece estar a funcar
		//	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
		//
		//	polyData = sphereSource->GetOutput();
		//
		//	double bounds[6];
		//	polyData->GetBounds(bounds);
		//
		//	vtkstd::cout  << "xmin: " << bounds[0] << " " << "xmax: " << bounds[1] << vtkstd::endl
		//			   << "ymin: " << bounds[2] << " " << "ymax: " << bounds[3] << vtkstd::endl
		//			   << "zmin: " << bounds[4] << " " << "zmax: " << bounds[5] << vtkstd::endl;
	}
	
	return NULL;
}

void calculateAndTransferAtoms(vtkSmartPointer<vtkPoints> innerElementPoints, vtkSmartPointer<vtkPoints> outerElementPoints, int elementCounter, double* focusCenter){
	
	// Array of ids of points to be included in focus area
	vtkSmartPointer<vtkIdTypeArray> pointsIdsInsideFocus = vtkSmartPointer<vtkIdTypeArray>::New();
	
	for (vtkIdType i = 0; i < innerElementPoints->GetNumberOfPoints(); i++){
		double *coords;
		
		if((coords = innerElementPoints->GetPoint(i))!=0){
			// (x-x0)^2 + (y-y0)^2 + (z-z0)^2 < r^2
			// if is inside focus area, inside of sphere equation
			if((coords[0] - focusCenter[0])*(coords[0] - focusCenter[0]) +
			   (coords[1] - focusCenter[1])*(coords[1] - focusCenter[1]) +
			   (coords[2] - focusCenter[2])*(coords[2] - focusCenter[2]) < (10*10) ){
				
				pointsIdsInsideFocus->InsertNextValue(i);
			}
			// TODO - confirmar formula
			
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
		vtkstd::cout << "Number of outer points: " << outerElementPoints->GetNumberOfPoints() << vtkstd::endl;
		vtkstd::cout << "Current outer point id: " << i << vtkstd::endl;
		
		double *coords = NULL;
		if((coords = outerElementPoints->GetPoint(i)) != 0){
			// (x-x0)^2 + (y-y0)^2 + (z-z0)^2 < r^2
			// if is inside focus area, inside of sphere equation
			if((coords[0] - focusCenter[0])*(coords[0] - focusCenter[0]) +
			   (coords[1] - focusCenter[1])*(coords[1] - focusCenter[1]) +
			   (coords[2] - focusCenter[2])*(coords[2] - focusCenter[2]) < (10*10) ){
				
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
}

void ReallyDeletePoint(vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkIdTypeArray> ids){
	vtkstd::cout << "Number of points: " << points->GetNumberOfPoints() << vtkstd::endl;
	vtkstd::cout << "Number of points to remove: " << ids->GetNumberOfTuples() << vtkstd::endl;
	
	vtkSmartPointer<vtkPoints> newPoints = vtkSmartPointer<vtkPoints>::New();
	double* coords = NULL;
	
	for(vtkIdType i = 0 ; i < ids->GetNumberOfTuples(); i++){
		if( (coords = points->GetPoint(i))){
			//vtkstd::cout << "Hello " << coords[0] << " " << coords[1] << " " << coords[2] << vtkstd::endl;
			
			newPoints->InsertNextPoint(coords);
		}
	}
	
	points->ShallowCopy(newPoints);
}

void insertPoint(vtkSmartPointer<vtkPoints> newPoints, vtkSmartPointer<vtkIdTypeArray> ids, vtkSmartPointer<vtkPoints> previousPoints){
	vtkstd::cout << "Number of points: " << newPoints->GetNumberOfPoints() << vtkstd::endl;
	vtkstd::cout << "Number of points to insert: " << ids->GetNumberOfTuples() << vtkstd::endl;
	
	double* coords = NULL;
	
	for(vtkIdType i = 0 ; i < ids->GetNumberOfTuples(); i++){
		if( (coords = previousPoints->GetPoint(i))){
			//vtkstd::cout << "Hello " << coords[0] << " " << coords[1] << " " << coords[2] << vtkstd::endl;
			newPoints->InsertNextPoint(coords);
		}
	}
}



