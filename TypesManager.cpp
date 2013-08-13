//
//  TypesManager.cpp
//  ResEye
//
//  Created by Renil Lacmane on 12/30/12.
//
//  Responsible for managing each type of structural information to use
//  in each LOD, depending on user display selection
//
//  Structure types are identified by consts
//

#include <string>
#include <exception>
#include <math.h>

#include "TypesManager.h"
#include "GeneralException.h"

#include <vtkPoints.h>
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSmartPointer.h"
#include <vtkProperty.h>
#include <vtkLine.h>
#include <vtkCellArray.h>

#include <vtkTubeFilter.h>
#include <vtkLineSource.h>

vtkstd::list<vtkstd::string> TypesManager::getProteinStructureTypes(){
	
	vtkstd::list<vtkstd::string> proteinStructureTypes;
	proteinStructureTypes.push_back("BALL_AND_STICK");
	proteinStructureTypes.push_back("VAN_DER_WALLS");
	
	return proteinStructureTypes;
}

vtkSmartPointer<vtkActor> TypesManager::associateVanDerWallsToActors(
		 vtkSmartPointer<vtkPoints > focusAreaElement, int elementPos){
	
	vtkSmartPointer<vtkPoints > element = focusAreaElement;
	float radius= 0;
	int resT= 12, resP= 12;
	
	if(elementPos == 0){
		// Hydrogen
		// element++;
		radius = 1.09;
		double color1[3]= {1, 1, 1};		// 255, 255, 255
		vtkPolyData *atomPositions1 = vtkPolyData::New();
		vtkSphereSource *sphereSource1 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs1 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper1 = vtkPolyDataMapper::New();
		vtkActor *atomActor1 = vtkActor::New();
		
		configureAtoms(atomPositions1, element, radius, sphereSource1, resT, resP, atomGlyphs1, atomMapper1, atomActor1, color1, false);
		//elementsActors.push_back(atomActor1);
		
		return atomActor1;
	}
	
	if(elementPos == 1){
		// Carbon
		//element++;		
		radius = 1.7;
		vtkPolyData *atomPositions2 = vtkPolyData::New();
		vtkSphereSource *sphereSource2 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs2 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper2 = vtkPolyDataMapper::New();
		vtkActor *atomActor2 = vtkActor::New();
		double color2[3]= {144.0f/255, 144.0f/255, 144.0f/255}; // 144, 144, 144
		
		configureAtoms(atomPositions2, element, radius, sphereSource2, resT, resP, atomGlyphs2, atomMapper2, atomActor2, color2, false);
		//elementsActors.push_back(atomActor2);
		
		return atomActor2;
	}
	
	if(elementPos == 2){
		
		// Nitrogen
		//element++;
		vtkPolyData *atomPositions3 = vtkPolyData::New();
		radius = 1.55;
		vtkSphereSource *sphereSource3 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs3 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper3 = vtkPolyDataMapper::New();
		vtkActor *atomActor3 = vtkActor::New();
		double color3[3]= {48.0f/255, 80.0f/255, 248.0f/255};   // 48, 80, 248
		
		configureAtoms(atomPositions3, element, radius, sphereSource3, resT, resP, atomGlyphs3, atomMapper3, atomActor3, color3, false);
		//elementsActors.push_back(atomActor3);
		
		return atomActor3;
	}
	
	if(elementPos == 3){
		
		// Oxygen
		//element++;
		vtkPolyData *atomPositions4 = vtkPolyData::New();
		radius = 1.52; // falta calcular Van der Waals radius
		vtkSphereSource *sphereSource4 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs4 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper4 = vtkPolyDataMapper::New();
		vtkActor *atomActor4 = vtkActor::New();
		//double color4[3]= {255.0f/255, 13.0f/255, 13.0f/255};   // 255, 13, 13
		double color4[3]= {1, 0, 0};   // 255, 13, 13
		
		configureAtoms(atomPositions4, element, radius, sphereSource4, resT, resP, atomGlyphs4, atomMapper4, atomActor4, color4, false);
		//elementsActors.push_back(atomActor4);
		
		return atomActor4;
	}
	
	if(elementPos == 4){
		
		// Sulfur
		//element++;
		vtkPolyData *atomPositions5 = vtkPolyData::New();
		radius = 1.80;
		vtkSphereSource *sphereSource5 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs5 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper5 = vtkPolyDataMapper::New();
		vtkActor *atomActor5 = vtkActor::New();
		double color5[3]= {255.0f/255, 255.0f/255, 48.0f/255};   // 255, 255, 48
		
		configureAtoms(atomPositions5, element, radius, sphereSource5, resT, resP, atomGlyphs5, atomMapper5, atomActor5, color5, false);
		//elementsActors.push_back(atomActor5);
		
		return atomActor5;
	}
	
	throw new GeneralException("missing element");
}

vtkSmartPointer<vtkActor> TypesManager::associateBallAndStickToActors(vtkSmartPointer<vtkPoints > focusAreaElement, int elementPos){
	//	elementsPointsArray[0] = H_AtomPoints;
	//	elementsPointsArray[1] = C_AtomPoints;
	//	elementsPointsArray[2] = N_AtomPoints;
	//	elementsPointsArray[3] = O_AtomPoints;
	//	elementsPointsArray[4] = S_AtomPoints;
	
	/// ------
	float radius= 0;
	int resT= 14, resP= 14;
	vtkSmartPointer<vtkPoints > element = focusAreaElement;
	
	if(elementPos == 0){
		
		// Hydrogen
		// element;
		vtkPolyData *atomPositions1 = vtkPolyData::New();
		radius = 0.50; // falta calcular Van der Waals radius
		vtkSphereSource *sphereSource1 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs1 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper1 = vtkPolyDataMapper::New();
		vtkActor *atomActor1 = vtkActor::New();
		double color1[3]= {1, 1, 1};		// 255, 255, 255
		
		configureAtoms(atomPositions1, element, radius, sphereSource1, resT, resP, atomGlyphs1, atomMapper1, atomActor1, color1, true);
		//elementsActors.push_back(atomActor1);
		return atomActor1;
	}
	else if(elementPos == 1){
		// Carbon
		//	element++;
		vtkPolyData *atomPositions2 = vtkPolyData::New();
		radius = 0.50; // falta calcular Van der Waals radius
		vtkSphereSource *sphereSource2 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs2 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper2 = vtkPolyDataMapper::New();
		vtkActor *atomActor2 = vtkActor::New();
		double color2[3]= {144.0f/255, 144.0f/255, 144.0f/255}; // 144, 144, 144
		
		configureAtoms(atomPositions2, element, radius, sphereSource2, resT, resP, atomGlyphs2, atomMapper2, atomActor2, color2, true);
		//elementsActors.push_back(atomActor2);
		return atomActor2;
	}
	else if(elementPos == 2){
		// Nitrogen
		//	element++;
		vtkPolyData *atomPositions3 = vtkPolyData::New();
		radius = 0.50;
		vtkSphereSource *sphereSource3 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs3 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper3 = vtkPolyDataMapper::New();
		vtkActor *atomActor3 = vtkActor::New();
		double color3[3]= {48.0f/255, 80.0f/255, 248.0f/255};   // 48, 80, 248
		
		configureAtoms(atomPositions3, element, radius, sphereSource3, resT, resP, atomGlyphs3, atomMapper3, atomActor3, color3, true);
		//	elementsActors.push_back(atomActor3);
		
		return atomActor3;
	}
	else if(elementPos == 3){
		// Oxygen
		//	element++;
		vtkPolyData *atomPositions4 = vtkPolyData::New();
		radius = 0.50; // falta calcular Van der Waals radius
		vtkSphereSource *sphereSource4 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs4 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper4 = vtkPolyDataMapper::New();
		vtkActor *atomActor4 = vtkActor::New();
		//double color4[3]= {255.0f/255, 13.0f/255, 13.0f/255};   // 255, 13, 13
		double color4[3]= {1, 0, 0};   // 255, 13, 13
		
		configureAtoms(atomPositions4, element, radius, sphereSource4, resT, resP, atomGlyphs4, atomMapper4, atomActor4, color4, true);
		//	elementsActors.push_back(atomActor4);
		
		return atomActor4;
	}
	else
		//if(elementPos == 4)
	{
		// Sulfur
		//element++;
		vtkPolyData *atomPositions5 = vtkPolyData::New();
		radius = 0.50;
		vtkSphereSource *sphereSource5 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs5 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper5 = vtkPolyDataMapper::New();
		vtkActor *atomActor5 = vtkActor::New();
		double color5[3]= {255.0f/255, 255.0f/255, 48.0f/255};   // 255, 255, 48
		
		configureAtoms(atomPositions5, element, radius, sphereSource5, resT, resP, atomGlyphs5, atomMapper5, atomActor5, color5, true);
		//	elementsActors.push_back(atomActor5);
		
		return atomActor5;
	}
	
	throw new GeneralException("missing element");
	
}

// Create placeholder for atoms of structure type VanDerWalls
vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > >
TypesManager::createVanDerWallsType(vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > > elementsList){
	
	if(elementsList.empty()){
		throw GeneralException("ConvertToVanDerWallsType called with empty parameters!");
	}
	
	//	elementsPointsArray[0] = H_AtomPoints;
	//	elementsPointsArray[1] = C_AtomPoints;
	//	elementsPointsArray[2] = N_AtomPoints;
	//	elementsPointsArray[3] = O_AtomPoints;
	//	elementsPointsArray[4] = S_AtomPoints;
	
	try{
		// mapping
		vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > > outerActors;
		//		// 4 areas
		//		vtkstd::list<vtkSmartPointer<vtkActor> > focusAreaXYActors;
		//		vtkstd::list<vtkSmartPointer<vtkActor> > focusAreaXYminusActors;
		//		vtkstd::list<vtkSmartPointer<vtkActor> > focusAreaXminusYminusActors;
		//		vtkstd::list<vtkSmartPointer<vtkActor> > focusAreaXminusYActors;
		//		// Array of Points
		//		// focusAreaXY
		//		vtkSmartPointer<vtkPoints> H1_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> C1_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> N1_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> O1_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> S1_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		// focusAreaXYminus
		//		vtkSmartPointer<vtkPoints> H2_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> C2_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> N2_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> O2_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> S2_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		// focusAreaXminusYminus
		//		vtkSmartPointer<vtkPoints> H3_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> C3_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> N3_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> O3_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> S3_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		// focusAreaXminusY
		//		vtkSmartPointer<vtkPoints> H4_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> C4_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> N4_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> O4_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//		vtkSmartPointer<vtkPoints> S4_AtomActors = vtkSmartPointer<vtkPoints>::New();
		//
		//		focusAreaXYActors.push_back(H1_AtomActors);
		//		focusAreaXYActors.push_back(C1_AtomActors);
		//		focusAreaXYActors.push_back(N1_AtomActors);
		//		focusAreaXYActors.push_back(O1_AtomActors);
		//		focusAreaXYActors.push_back(S1_AtomActors);
		//
		//		focusAreaXYminusActors.push_back(H2_AtomActors);
		//		focusAreaXYminusActors.push_back(C2_AtomActors);
		//		focusAreaXYminusActors.push_back(N2_AtomActors);
		//		focusAreaXYminusActors.push_back(O2_AtomActors);
		//		focusAreaXYminusActors.push_back(S2_AtomActors);
		//
		//		focusAreaXminusYminusActors.push_back(H3_AtomActors);
		//		focusAreaXminusYminusActors.push_back(C3_AtomActors);
		//		focusAreaXminusYminusActors.push_back(N3_AtomActors);
		//		focusAreaXminusYminusActors.push_back(O3_AtomActors);
		//		focusAreaXminusYminusActors.push_back(S3_AtomActors);
		//
		//		focusAreaXminusYActors.push_back(H4_AtomActors);
		//		focusAreaXminusYActors.push_back(C4_AtomActors);
		//		focusAreaXminusYActors.push_back(N4_AtomActors);
		//		focusAreaXminusYActors.push_back(O3_AtomActors);
		//		focusAreaXminusYActors.push_back(S4_AtomActors);
		//
		//
		//		outerActors.push_back(focusAreaXYActors);
		//		outerActors.push_back(focusAreaXYminusActors);
		//		outerActors.push_back(focusAreaXminusYminusActors);
		//		outerActors.push_back(focusAreaXminusYActors);
		
		
		for (vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > >::iterator focusAreaPoints = elementsList.begin();
			 focusAreaPoints!= elementsList.end(); focusAreaPoints++){
			
			int elementPos = 0;
			vtkstd::list<vtkSmartPointer<vtkActor> > actorsFocusAreas;
			for (vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator element = (*focusAreaPoints).begin();
				 element != (*focusAreaPoints).end(); element++) {
				
				vtkSmartPointer<vtkActor> elementActor = associateVanDerWallsToActors(*element, elementPos);
				actorsFocusAreas.push_back(elementActor);
				elementPos++;
				
			}
			outerActors.push_back(actorsFocusAreas);
		}
		
		return outerActors;
		
	}
	catch(vtkstd::exception e){
		throw GeneralException("Could not create elementsActors properly for Van Der Walls type");
	}
}

// Create placeholder for atoms of structure type VanDerWalls
vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > > TypesManager::createBallAndStickType(vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > > elementsList) {
	if(elementsList.empty()){
		throw GeneralException("ConvertToVanDerWallsType called with empty parameters!");
	}
	
	try{
		// mapping
		vtkstd::list<vtkstd::list<vtkSmartPointer<vtkActor> > > innerActors;
		//		vtkstd::list<vtkSmartPointer<vtkActor> > actorsFocusAreas;
		//		vtkSmartPointer<vtkActor> element;
		
		for (vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > >::iterator focusAreas = elementsList.begin();
			 focusAreas!= elementsList.end(); focusAreas++){
			
			int elementPos = 0;
			vtkstd::list<vtkSmartPointer<vtkActor> > actorsFocusAreas;
			for (vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator element = (*focusAreas).begin();
				 element != (*focusAreas).end(); element++){
				
				vtkSmartPointer<vtkActor> elementActor = associateBallAndStickToActors(*element, elementPos);
				actorsFocusAreas.push_back(elementActor);
				elementPos++;
				
			}
			innerActors.push_back(actorsFocusAreas);
		}
		
		return innerActors;
		
	}
	catch(vtkstd::exception e){
		throw GeneralException("Could not create elementsActors properly for Ball and Stick type");
	}
}

void makeBonds(vtkSmartPointer<vtkPoints> initialAtomPoints, vtkSmartPointer<vtkPoints> endAtomPoints,
			   vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkCellArray> lines){
	
	double limitAngstrom = 2.0*2.0;
	
	for (vtkIdType i = 0; i < initialAtomPoints->GetNumberOfPoints(); i++){
		
		double initialPoint[3];
		initialAtomPoints->GetPoint(i, initialPoint);
		
		for (vtkIdType i = 0; i < endAtomPoints->GetNumberOfPoints(); i++){
			
			double finalPoint[3];
			endAtomPoints->GetPoint(i, finalPoint);
			
			double dx = finalPoint[0] - initialPoint[0]; // -1 - -2 = 1, - 1 - 0 = - 1, 1 - -2 = 3 
			double dy = finalPoint[1] - initialPoint[1];
			double dz = finalPoint[2] - initialPoint[2];
			
			double distSquare = dx*dx + dy*dy + dz*dz;
			
			double dist1 = 0.56 + 0.56 + 0.56;
			double max = dist1*dist1;
			
			//vtkstd::cout << distSquare << " " << limitAngstrom*limitAngstrom << " " << max << endl;
			
			if(dx*dx < limitAngstrom && dy*dy < limitAngstrom && dz*dz < limitAngstrom){
			//if(distSquare <= max){
				points->InsertNextPoint(initialPoint);
				points->InsertNextPoint(finalPoint);
				
				vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
				line->GetPointIds()->SetId(0, points->GetNumberOfPoints()-2);
				line->GetPointIds()->SetId(1, points->GetNumberOfPoints()-1);
				
				lines->InsertNextCell(line);
				
//				vtkSmartPointer<vtkLineSource> line = vtkSmartPointer<vtkLineSource>::New();
//				line->SetPoint1(initialPoint);
//				line->SetPoint2(finalPoint);
			}
		}
	}
	
}

vtkSmartPointer<vtkActor> calculateBondsActorsByPoints(vtkstd::list<vtkSmartPointer<vtkPoints> > focusAreaElements){
	
	vtkSmartPointer<vtkActor> focusAreaBonds = vtkSmartPointer<vtkActor>::New();
	vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator focusAreaElement = focusAreaElements.begin();
	
	// Calcular lines entre qual atomos
	// Comparar cada elemento com a sua lista de pontos, e a lista dos outros elements
	// Hidrogen nao se ligam entre eles

	vtkstd::cout << "Estou aqui para calcular os bonds" << endl;
	// --
	vtkSmartPointer<vtkPoints> H_AtomPoints = vtkSmartPointer<vtkPoints>::New();
	H_AtomPoints = (*focusAreaElement);
	vtkSmartPointer<vtkPoints> C_AtomPoints = vtkSmartPointer<vtkPoints>::New();
	C_AtomPoints = (*(++focusAreaElement));
	vtkSmartPointer<vtkPoints> N_AtomPoints = vtkSmartPointer<vtkPoints>::New();
	N_AtomPoints = (*(++focusAreaElement));
	vtkSmartPointer<vtkPoints> O_AtomPoints = vtkSmartPointer<vtkPoints>::New();
	O_AtomPoints = (*(++focusAreaElement));
	vtkSmartPointer<vtkPoints> S_AtomPoints = vtkSmartPointer<vtkPoints>::New();
	S_AtomPoints = (*(++focusAreaElement));
	
	vtkstd::cout << "O pontos " << O_AtomPoints->GetNumberOfPoints() << endl;
	
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	
	makeBonds(H_AtomPoints, C_AtomPoints, points, lines);
	makeBonds(H_AtomPoints, N_AtomPoints, points, lines);
	makeBonds(H_AtomPoints, O_AtomPoints, points, lines);
	makeBonds(H_AtomPoints, S_AtomPoints, points, lines);
	
	makeBonds(C_AtomPoints, C_AtomPoints, points, lines);
	makeBonds(C_AtomPoints, N_AtomPoints, points, lines);
	makeBonds(C_AtomPoints, O_AtomPoints, points, lines);
	makeBonds(C_AtomPoints, S_AtomPoints, points, lines);
	
	makeBonds(N_AtomPoints, N_AtomPoints, points, lines);
	makeBonds(N_AtomPoints, O_AtomPoints, points, lines);
	makeBonds(N_AtomPoints, S_AtomPoints, points, lines);
	
	makeBonds(O_AtomPoints, O_AtomPoints, points, lines);
	makeBonds(O_AtomPoints, S_AtomPoints, points, lines);
	
	
	vtkstd::cout << "Actor pontos " << points->GetNumberOfPoints() << endl;
	
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	polydata->SetLines(lines);
	
	vtkSmartPointer<vtkTubeFilter> tube = vtkSmartPointer<vtkTubeFilter>::New();
    tube->SetInput(polydata);
    tube->SetNumberOfSides(7);
    tube->SetRadius(0.17);
	tube->CappingOn();
	
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInput(tube->GetOutput());
	
	focusAreaBonds->SetMapper(mapper);
	focusAreaBonds->GetProperty()->SetColor(0.9, 0.7, 0.4);
	focusAreaBonds->VisibilityOff();
	
	return focusAreaBonds;
}

vtkstd::list<vtkSmartPointer<vtkActor> > TypesManager::createBallAndStickTypeBonds(vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > > elementsList){
	if(elementsList.empty()){
		throw GeneralException("ConvertToVanDerWallsType called with empty parameters!");
	}
	
	//	elementsPointsArray[0] = H_AtomPoints;
	//	elementsPointsArray[1] = C_AtomPoints;
	//	elementsPointsArray[2] = N_AtomPoints;
	//	elementsPointsArray[3] = O_AtomPoints;
	//	elementsPointsArray[4] = S_AtomPoints;
	
	try{
		
		vtkstd::list<vtkSmartPointer<vtkActor> > outerBondsActors;
		
		for (vtkstd::list<vtkstd::list<vtkSmartPointer<vtkPoints> > >::iterator focusAreaPoints = elementsList.begin();
			 focusAreaPoints!= elementsList.end(); focusAreaPoints++){
			
			vtkSmartPointer<vtkActor> bondsActorFocusArea = vtkSmartPointer<vtkActor>::New();
			
			bondsActorFocusArea = calculateBondsActorsByPoints(*focusAreaPoints);
			
			outerBondsActors.push_back(bondsActorFocusArea);
		}
		
		return outerBondsActors;
		
	}
	catch(vtkstd::exception e){
		throw GeneralException("Could not create elementsActors properly for Van Der Walls type");
	}
	
}

// Auxuliar method for meuMapper
void TypesManager::configureAtoms(vtkPolyData *atomPositions, vtkSmartPointer<vtkPoints> atomPoints,
								  double radius, vtkSphereSource *sphereSource, int resT, int resP, vtkGlyph3D *atomGlyphs,
								  vtkPolyDataMapper *atomMapper, vtkActor *atomActor, double color[], bool hidden){
	
	// insert array of points
	atomPositions->SetPoints(atomPoints);
	// Atoms format (spheres)
	// Create the atoms
	sphereSource->SetThetaResolution(resT);
	sphereSource->SetPhiResolution(resP);
	sphereSource->SetRadius(radius); // alterar para radius
	
	atomGlyphs ->SetInput(atomPositions);
	atomGlyphs ->SetSource(sphereSource->GetOutput());
	// Create the mapper & actor for the atoms
	atomMapper->SetInput(atomGlyphs->GetOutput());
	
	atomActor->SetMapper(atomMapper);
	atomActor->GetProperty()->SetColor(color[0], color[1], color[2]);
	//atomActor->GetProperty()->SetInterpolationToGouraud(); // Ver o que é necessário para o gouraud (default ?)
	
	if(hidden){
		atomActor->VisibilityOff();
	}
}



/*
 
 vtkstd::list<vtkstd::string> TypesManager::getProteinStructureTypes(){
 
 vtkstd::list<vtkstd::string> proteinStructureTypes;
 proteinStructureTypes.push_back("BALL_AND_STICK");
 proteinStructureTypes.push_back("VAN_DER_WALLS");
 
 return proteinStructureTypes;
 }

 
 // Create placeholder for atoms of structure type VanDerWalls
 vtkstd::list<vtkSmartPointer<vtkActor> > TypesManager::createVanDerWallsType(vtkstd::list<vtkSmartPointer<vtkPoints> > elementsList) {
 if(elementsList.empty()){
 throw GeneralException("ConvertToVanDerWallsType called with empty parameters!");
 }
 
 //	elementsPointsArray[0] = H_AtomPoints;
 //	elementsPointsArray[1] = C_AtomPoints;
 //	elementsPointsArray[2] = N_AtomPoints;
 //	elementsPointsArray[3] = O_AtomPoints;
 //	elementsPointsArray[4] = S_AtomPoints;
 
 try{
 
 float radius= 0;
 int resT= 10, resP= 10;
 
 vtkstd::list<vtkSmartPointer<vtkActor> > elementsActors;
 vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator element = elementsList.begin();
 
 // Hydrogen
 // element++;
 radius = 1.09;
 double color1[3]= {1, 1, 1};		// 255, 255, 255
 vtkPolyData *atomPositions1 = vtkPolyData::New();
 vtkSphereSource *sphereSource1 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs1 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper1 = vtkPolyDataMapper::New();
 vtkActor *atomActor1 = vtkActor::New();
 
 configureAtoms(atomPositions1, *element, radius, sphereSource1, resT, resP, atomGlyphs1, atomMapper1, atomActor1, color1);
 elementsActors.push_back(atomActor1);
 
 // Carbon
 element++;
 radius = 1.7;
 vtkPolyData *atomPositions2 = vtkPolyData::New();
 vtkSphereSource *sphereSource2 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs2 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper2 = vtkPolyDataMapper::New();
 vtkActor *atomActor2 = vtkActor::New();
 double color2[3]= {144.0f/255, 144.0f/255, 144.0f/255}; // 144, 144, 144
 
 configureAtoms(atomPositions2, *element, radius, sphereSource2, resT, resP, atomGlyphs2, atomMapper2, atomActor2, color2);
 elementsActors.push_back(atomActor2);
 
 // Nitrogen
 element++;
 vtkPolyData *atomPositions3 = vtkPolyData::New();
 radius = 1.55;
 vtkSphereSource *sphereSource3 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs3 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper3 = vtkPolyDataMapper::New();
 vtkActor *atomActor3 = vtkActor::New();
 double color3[3]= {48.0f/255, 80.0f/255, 248.0f/255};   // 48, 80, 248
 
 configureAtoms(atomPositions3, *element, radius, sphereSource3, resT, resP, atomGlyphs3, atomMapper3, atomActor3, color3);
 elementsActors.push_back(atomActor3);
 
 // Oxygen
 element++;
 vtkPolyData *atomPositions4 = vtkPolyData::New();
 radius = 1.52; // falta calcular Van der Waals radius
 vtkSphereSource *sphereSource4 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs4 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper4 = vtkPolyDataMapper::New();
 vtkActor *atomActor4 = vtkActor::New();
 //double color4[3]= {255.0f/255, 13.0f/255, 13.0f/255};   // 255, 13, 13
 double color4[3]= {1, 0, 0};   // 255, 13, 13
 
 configureAtoms(atomPositions4, *element, radius, sphereSource4, resT, resP, atomGlyphs4, atomMapper4, atomActor4, color4);
 elementsActors.push_back(atomActor4);
 
 // Sulfur
 element++;
 vtkPolyData *atomPositions5 = vtkPolyData::New();
 radius = 1.80;
 vtkSphereSource *sphereSource5 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs5 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper5 = vtkPolyDataMapper::New();
 vtkActor *atomActor5 = vtkActor::New();
 double color5[3]= {255.0f/255, 255.0f/255, 48.0f/255};   // 255, 255, 48
 
 configureAtoms(atomPositions5, *element, radius, sphereSource5, resT, resP, atomGlyphs5, atomMapper5, atomActor5, color5);
 elementsActors.push_back(atomActor5);
 
 //
 return elementsActors;
 
 }
 catch(vtkstd::exception e){
 throw GeneralException("Could not create elementsActors properly for Van Der Walls type");
 }
 }
 
 // Create placeholder for atoms of structure type VanDerWalls
 vtkstd::list<vtkSmartPointer<vtkActor> > TypesManager::createBallAndStickType(vtkstd::list<vtkSmartPointer<vtkPoints> > elementsList) {
 if(elementsList.empty()){
 throw GeneralException("ConvertToVanDerWallsType called with empty parameters!");
 }
 
 //	elementsPointsArray[0] = H_AtomPoints;
 //	elementsPointsArray[1] = C_AtomPoints;
 //	elementsPointsArray[2] = N_AtomPoints;
 //	elementsPointsArray[3] = O_AtomPoints;
 //	elementsPointsArray[4] = S_AtomPoints;
 
 try{
 
 float radius= 0;
 int resT= 10, resP= 10;
 
 vtkstd::list<vtkSmartPointer<vtkActor> > elementsActors;
 vtkstd::list<vtkSmartPointer<vtkPoints> >::iterator element = elementsList.begin();
 
 // Hydrogen
 // element;
 vtkPolyData *atomPositions1 = vtkPolyData::New();
 radius = 0.50; // falta calcular Van der Waals radius
 vtkSphereSource *sphereSource1 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs1 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper1 = vtkPolyDataMapper::New();
 vtkActor *atomActor1 = vtkActor::New();
 double color1[3]= {1, 1, 1};		// 255, 255, 255
 
 configureAtoms(atomPositions1, *element, radius, sphereSource1, resT, resP, atomGlyphs1, atomMapper1, atomActor1, color1);
 elementsActors.push_back(atomActor1);
 
 // Carbon
 element++;
 vtkPolyData *atomPositions2 = vtkPolyData::New();
 radius = 0.50; // falta calcular Van der Waals radius
 vtkSphereSource *sphereSource2 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs2 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper2 = vtkPolyDataMapper::New();
 vtkActor *atomActor2 = vtkActor::New();
 double color2[3]= {144.0f/255, 144.0f/255, 144.0f/255}; // 144, 144, 144
 
 configureAtoms(atomPositions2, *element, radius, sphereSource2, resT, resP, atomGlyphs2, atomMapper2, atomActor2, color2);
 elementsActors.push_back(atomActor2);
 
 // Nitrogen
 element++;
 vtkPolyData *atomPositions3 = vtkPolyData::New();
 radius = 0.50;
 vtkSphereSource *sphereSource3 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs3 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper3 = vtkPolyDataMapper::New();
 vtkActor *atomActor3 = vtkActor::New();
 double color3[3]= {48.0f/255, 80.0f/255, 248.0f/255};   // 48, 80, 248
 
 configureAtoms(atomPositions3, *element, radius, sphereSource3, resT, resP, atomGlyphs3, atomMapper3, atomActor3, color3);
 elementsActors.push_back(atomActor3);
 
 // Oxygen
 element++;
 vtkPolyData *atomPositions4 = vtkPolyData::New();
 radius = 0.50; // falta calcular Van der Waals radius
 vtkSphereSource *sphereSource4 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs4 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper4 = vtkPolyDataMapper::New();
 vtkActor *atomActor4 = vtkActor::New();
 //double color4[3]= {255.0f/255, 13.0f/255, 13.0f/255};   // 255, 13, 13
 double color4[3]= {1, 0, 0};   // 255, 13, 13
 
 configureAtoms(atomPositions4, *element, radius, sphereSource4, resT, resP, atomGlyphs4, atomMapper4, atomActor4, color4);
 elementsActors.push_back(atomActor4);
 
 // Sulfur
 element++;
 vtkPolyData *atomPositions5 = vtkPolyData::New();
 radius = 0.50;
 vtkSphereSource *sphereSource5 = vtkSphereSource::New();
 vtkGlyph3D *atomGlyphs5 = vtkGlyph3D::New();
 vtkPolyDataMapper *atomMapper5 = vtkPolyDataMapper::New();
 vtkActor *atomActor5 = vtkActor::New();
 double color5[3]= {255.0f/255, 255.0f/255, 48.0f/255};   // 255, 255, 48
 
 configureAtoms(atomPositions5, *element, radius, sphereSource5, resT, resP, atomGlyphs5, atomMapper5, atomActor5, color5);
 elementsActors.push_back(atomActor5);
 
 //
 return elementsActors;
 }
 catch(vtkstd::exception e){
 throw GeneralException("Could not create elementsActors properly for Ball and Stick type");
 }
 }
 
 // Auxuliar method for meuMapper
 void TypesManager::configureAtoms(vtkPolyData *atomPositions, vtkSmartPointer<vtkPoints> atomPoints, double radius, vtkSphereSource *sphereSource, int resT, int resP, vtkGlyph3D *atomGlyphs, vtkPolyDataMapper *atomMapper, vtkActor *atomActor, double color[]){
 
 // insert array of points
 atomPositions->SetPoints(atomPoints);
 // Atoms format (spheres)
 // Create the atoms
 sphereSource->SetThetaResolution(resT);
 sphereSource->SetPhiResolution(resP);
 sphereSource->SetRadius(radius); // alterar para radius
 
 atomGlyphs ->SetInput(atomPositions);
 atomGlyphs ->SetSource(sphereSource->GetOutput());
 // Create the mapper & actor for the atoms
 atomMapper->SetInput(atomGlyphs->GetOutput());
 
 atomActor->SetMapper(atomMapper);
 atomActor->GetProperty()->SetColor(color[0], color[1], color[2]);
 //atomActor->GetProperty()->SetInterpolationToGouraud(); // Ver o que é necessário para o gouraud (default ?)
 
 
 }
 
 */


