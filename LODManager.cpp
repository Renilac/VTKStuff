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
void focusAreaInnerElementsVisibility(bool hidden, vtkstd::list<vtkSmartPointer<vtkActor> > focusAreaInnerElements){
	
	for (vtkstd::list<vtkSmartPointer<vtkActor> >::iterator focusAreaInnerElement = focusAreaInnerElements.begin();
		 focusAreaInnerElement != focusAreaInnerElements.end(); focusAreaInnerElement++) {
		
		if(hidden){
			(*focusAreaInnerElement)->VisibilityOn();
		}
		else{
			(*focusAreaInnerElement)->VisibilityOff();
		}
		
		(*focusAreaInnerElement)->Modified();
	}
}

void focusAreaOuterElementsVisibility(bool hidden, vtkstd::list<vtkSmartPointer<vtkActor> > focusAreaOuterElements){
	
	for (vtkstd::list<vtkSmartPointer<vtkActor> >::iterator focusAreaOuterElement = focusAreaOuterElements.begin();
		 focusAreaOuterElement != focusAreaOuterElements.end(); focusAreaOuterElement++) {
		
		if(hidden){
			(*focusAreaOuterElement)->VisibilityOn();
		}
		else{
			(*focusAreaOuterElement)->VisibilityOff();
		}
		
		(*focusAreaOuterElement)->Modified();
	}
}

vtkSmartPointer<vtkActorCollection> LODManager::calculateLODActors(vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > > innerElementsList,
																   vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > > outerElementsList,
																   double* focusAreaCenter){
	
	double x = focusAreaCenter[0];
	double y = focusAreaCenter[1];
	//double z = focusAreaCenter[2];
	
	// Pensar se fazer um for e verificar smp se tou no quandrante certo eh o mlhor (por cada move)
	// quadrantes
	vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > >::iterator focusAreaInner = outerElementsList.begin();
	for (vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > >::iterator focusAreaOuter = outerElementsList.begin();
		 focusAreaOuter != outerElementsList.end(); focusAreaOuter++) {
		
		//reset state
		focusAreaInnerElementsVisibility(true, *focusAreaInner);
		focusAreaOuterElementsVisibility(false, *focusAreaInner);
		
		// tenho que activar todos os Actors da area (quadrante) onde estou
		if (x>=0 && y>=0){
			
			vtkstd::cout << "Found quadrant at: " << x << " " << y <<endl;
			
			focusAreaOuterElementsVisibility(false, *focusAreaOuter);
			focusAreaInnerElementsVisibility(true, *focusAreaInner);
		}
		else if(x>=0 && y<0){
			vtkstd::cout << "Found quadrant at: " << x << " " << y <<endl;
			
			focusAreaOuterElementsVisibility(false, *focusAreaOuter);
			focusAreaInnerElementsVisibility(true, *focusAreaInner);
		}
		else if(x<0 && y<0){
			
			vtkstd::cout << "Found quadrant at: " << x << " " << y <<endl;
			
			focusAreaOuterElementsVisibility(false, *focusAreaOuter);
			focusAreaInnerElementsVisibility(true, *focusAreaInner);
		}
		else {
			
			vtkstd::cout << "Found quadrant at: " << x << " " << y <<endl;
			
			focusAreaOuterElementsVisibility(false, *focusAreaOuter);
			focusAreaInnerElementsVisibility(true, *focusAreaInner);
		}
		
		// inner list follows
		focusAreaInner++;
		
	}
	
	//
	
	
	// Insert the new point
	// then tell VTK that the data has been modified so the Render() call
	// will update the view with the new data
	// Get inner and outer Actors
	// Change innner Actors properties, if inner LOD active
	// TODO - implementar ball and stick, Faltam me as bounds
	
//	int elementCounter = 0;  // TODO - rever
//	vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator j = innerElementsList.begin();
//	
//	for(vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator i = outerElementsList.begin(); i != outerElementsList.end(); i++){
//		
//		vtkSmartPointer<vtkPoints> outerElementPoints = (*i);
//		vtkSmartPointer<vtkPoints> innerElementPoints = (*j);
//		
//		vtkstd::cout << "counter: " << elementCounter << endl;
//		
//		calculateAndTransferAtoms(innerElementPoints, outerElementPoints, elementCounter, focusAreaCenter); // TODO mudar para receber a pos do picker
//		
//		
//		elementCounter++;
//		j++;
//		
//		// Bounds TODO - Não parece estar a funcar
//		//	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
//		//
//		//	polyData = sphereSource->GetOutput();
//		//
//		//	double bounds[6];
//		//	polyData->GetBounds(bounds);
//		//
//		//	vtkstd::cout  << "xmin: " << bounds[0] << " " << "xmax: " << bounds[1] << vtkstd::endl
//		//			   << "ymin: " << bounds[2] << " " << "ymax: " << bounds[3] << vtkstd::endl
//		//			   << "zmin: " << bounds[4] << " " << "zmax: " << bounds[5] << vtkstd::endl;
//	}
	
	return NULL;
}

void calculateAndTransferAtoms(vtkSmartPointer<vtkPoints> innerElementPoints, vtkSmartPointer<vtkPoints> outerElementPoints, int elementCounter, double* focusCenter){
	
	// Array of ids of points to be included in focus area
	vtkSmartPointer<vtkIdTypeArray> pointsIdsInsideFocus = vtkSmartPointer<vtkIdTypeArray>::New();
	
	for (vtkIdType i = 0; i < innerElementPoints->GetNumberOfPoints(); i++){
		
		vtkstd::cout << "Existing inner points: " << innerElementPoints->GetNumberOfPoints() << vtkstd::endl;
		
		double coords[3];
		innerElementPoints->GetPoint(i, coords);
		// (x-x0)^2 + (y-y0)^2 + (z-z0)^2 < r^2
		// if is inside focus area, inside of sphere equation
		if((coords[0] - focusCenter[0])*(coords[0] - focusCenter[0]) +
		   (coords[1] - focusCenter[1])*(coords[1] - focusCenter[1]) +
		   (coords[2] - focusCenter[2])*(coords[2] - focusCenter[2]) < (10*10) ){
			
			pointsIdsInsideFocus->InsertNextValue(i);
		}
		// TODO - confirmar formula
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
		
		vtkstd::cout << "Existing outer points: " << outerElementPoints->GetNumberOfPoints() << vtkstd::endl;
		
		double coords[3];
		outerElementPoints->GetPoint(i, coords);
		//vtkstd::cout << "Outer point coords " << coords[0] << " " << coords[1] << " " << coords[2] << vtkstd::endl;
		
		// (x-x0)^2 + (y-y0)^2 + (z-z0)^2 < r^2
		// if is inside focus area, inside of sphere equation
		if((coords[0] - focusCenter[0])*(coords[0] - focusCenter[0]) +
		   (coords[1] - focusCenter[1])*(coords[1] - focusCenter[1]) +
		   (coords[2] - focusCenter[2])*(coords[2] - focusCenter[2]) < (10*10) ){
			
			pointsIdsOutsideFocus->InsertNextValue(i);
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
	vtkstd::cout << "Removal Method" << vtkstd::endl;
	vtkstd::cout << "Number of points: " << points->GetNumberOfPoints() << vtkstd::endl;
	vtkstd::cout << "Number of points to remove: " << ids->GetNumberOfTuples() << vtkstd::endl;
	
	vtkSmartPointer<vtkPoints> newPoints = vtkSmartPointer<vtkPoints>::New();
	double coords[3];
	
	for(vtkIdType i = 0 ; i < ids->GetNumberOfTuples(); i++){
		
		points->GetPoint(i, coords);
		vtkstd::cout << "Current point id to remove: " << i << vtkstd::endl;
		vtkstd::cout << "coords: " << coords[0] << " " << coords[1] << " " << coords[2] << vtkstd::endl;
		
		newPoints->InsertNextPoint(coords);
	}
	
	points->ShallowCopy(newPoints);
	points->Modified();
}

void insertPoint(vtkSmartPointer<vtkPoints> newPoints, vtkSmartPointer<vtkIdTypeArray> ids, vtkSmartPointer<vtkPoints> previousPoints){
	vtkstd::cout << "Insertion Method" << vtkstd::endl;
	vtkstd::cout << "Number of points: " << newPoints->GetNumberOfPoints() << vtkstd::endl;
	vtkstd::cout << "Number of points to insert: " << ids->GetNumberOfTuples() << vtkstd::endl;
	
	double coords[3];
	
	for(vtkIdType i = 0 ; i < ids->GetNumberOfTuples(); i++){
		previousPoints->GetPoint(i, coords);
		vtkstd::cout << "Current point id to insert: " << i << vtkstd::endl;
		vtkstd::cout << "coords: " << coords[0] << " " << coords[1] << " " << coords[2] << vtkstd::endl;
		
		newPoints->InsertNextPoint(coords);
	}
	
	newPoints->Modified();
}



