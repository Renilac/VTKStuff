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

#include "TypesManager.h"
#include "GeneralException.h"

#include <vtkPoints.h>
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSmartPointer.h"
#include "vtkProperty.h"


std::list<std::string> TypesManager::getProteinStructureTypes(){

	std::list<std::string> proteinStructureTypes;
	proteinStructureTypes.push_back("BALL_AND_STICK");
	proteinStructureTypes.push_back("VAN_DER_WALLS");
	
	return proteinStructureTypes;
}

std::list<vtkSmartPointer<vtkActor> > TypesManager::convertToVanDerWallsType(std::list<vtkSmartPointer<vtkPoints> > elementsAtomPoints) {
	
	if(elementsAtomPoints.empty()){
		throw GeneralException("ConvertToVanDerWallsType called with empty parameters!");
	}
	
	float radius= 0;
    int resT= 7, resP= 7;
	
	std::list<vtkSmartPointer<vtkActor> > elementsActors;
	
	/*
	 elementsPointsArray[0] = H_AtomPoints;
	 elementsPointsArray[1] = C_AtomPoints;
	 elementsPointsArray[2] = N_AtomPoints;
	 elementsPointsArray[3] = O_AtomPoints;
	 elementsPointsArray[4] = S_AtomPoints;
	 */
	
	//float atompos[3];
	//std::list<vtkSmartPointer<vtkPoints> > points;
	//std::list<vtkSmartPointer<vtkPoints> >::iterator it = points.begin();
	//(*it)->InsertNextPoint(atompos);
	
	std::list<vtkSmartPointer<vtkPoints> >::iterator elementGroup = elementsAtomPoints.begin();

	//elementGroup;
	//if(H_AtomPoints->GetNumberOfPoints() != 0){
	if((*elementGroup)->GetNumberOfPoints() != 0){			// Hydrogen
		// insert array of points
		vtkPolyData *atomPositions1 = vtkPolyData::New();
		radius = 1.09; // falta calcular Van der Waals radius
		vtkSphereSource *sphereSource1 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs1 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper1 = vtkPolyDataMapper::New();
		vtkActor *atomActor1 = vtkActor::New();
		double color1[3]= {1, 1, 1};		// 255, 255, 255
		
		configureAtoms(atomPositions1, *elementGroup, radius, sphereSource1, resT, resP, atomGlyphs1, atomMapper1, atomActor1, color1);
		
		elementsActors.push_back(atomActor1);
		//aren->AddActor(atomActor1);
		
		cout << "Hydrogen: " << (*elementGroup)->GetNumberOfPoints() << endl;
	}
	
	++elementGroup;
	//if (C_AtomPoints->GetNumberOfPoints()!=0){
	if ((*elementGroup)->GetNumberOfPoints()!=0){				// Carbon
		// insert array of points
		vtkPolyData *atomPositions2 = vtkPolyData::New();
		radius = 1.7; // falta calcular Van der Waals radius
		vtkSphereSource *sphereSource2 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs2 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper2 = vtkPolyDataMapper::New();
		vtkActor *atomActor2 = vtkActor::New();
		double color2[3]= {144.0f/255, 144.0f/255, 144.0f/255}; // 144, 144, 144
		
		configureAtoms(atomPositions2, *elementGroup, radius, sphereSource2, resT, resP, atomGlyphs2, atomMapper2, atomActor2, color2);
		
		elementsActors.push_back(atomActor2);
		//aren->AddActor(atomActor2);

		cout << "Carbon: " << (*elementGroup)->GetNumberOfPoints() << endl;
	}
	
	++elementGroup;
	//if (N_AtomPoints->GetNumberOfPoints()!=0){
	if ((*elementGroup)->GetNumberOfPoints()!=0){					// Nitrogen
		// insert array of points
		vtkPolyData *atomPositions3 = vtkPolyData::New();
		radius = 1.55; // TODO calcular Van der Waals radius
		vtkSphereSource *sphereSource3 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs3 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper3 = vtkPolyDataMapper::New();
		vtkActor *atomActor3 = vtkActor::New();
		double color3[3]= {48.0f/255, 80.0f/255, 248.0f/255};   // 48, 80, 248
		
		configureAtoms(atomPositions3, *elementGroup, radius, sphereSource3, resT, resP, atomGlyphs3, atomMapper3, atomActor3, color3);
		
		elementsActors.push_back(atomActor3);
		//aren->AddActor(atomActor3);

		cout << "Nitrogen: " << (*elementGroup)->GetNumberOfPoints() << endl;
	}
	
	++elementGroup;
	//if (O_AtomPoints->GetNumberOfPoints()!=0){
	if ((*elementGroup)->GetNumberOfPoints()!=0){					// Oxygen
		// insert array of points
		vtkPolyData *atomPositions4 = vtkPolyData::New();
		radius = 1.52; // falta calcular Van der Waals radius
		vtkSphereSource *sphereSource4 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs4 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper4 = vtkPolyDataMapper::New();
		vtkActor *atomActor4 = vtkActor::New();
		//double color4[3]= {255.0f/255, 13.0f/255, 13.0f/255};   // 255, 13, 13
		double color4[3]= {1, 0, 0};   // 255, 13, 13
		
		configureAtoms(atomPositions4, *elementGroup, radius, sphereSource4, resT, resP, atomGlyphs4, atomMapper4, atomActor4, color4);
		
		elementsActors.push_back(atomActor4);
		//aren->AddActor(atomActor4);
		
		cout << "Oxygen e afins: " << (*elementGroup)->GetNumberOfPoints() << endl;
	}
	
	++elementGroup;
	//if (S_AtomPoints->GetNumberOfPoints() != 0) {
	if ((*elementGroup)->GetNumberOfPoints() != 0) {				// Sulfur
		// insert array of points
		vtkPolyData *atomPositions5 = vtkPolyData::New();
		radius = 1.80;
		vtkSphereSource *sphereSource5 = vtkSphereSource::New();
		vtkGlyph3D *atomGlyphs5 = vtkGlyph3D::New();
		vtkPolyDataMapper *atomMapper5 = vtkPolyDataMapper::New();
		vtkActor *atomActor5 = vtkActor::New();
		double color5[3]= {255.0f/255, 255.0f/255, 48.0f/255};   // 255, 255, 48
		
		configureAtoms(atomPositions5, *elementGroup, radius, sphereSource5, resT, resP, atomGlyphs5, atomMapper5, atomActor5, color5);
		
		elementsActors.push_back(atomActor5);
		//aren->AddActor(atomActor5);
		
		cout << "Sulfur e afins: " << (*elementGroup)->GetNumberOfPoints() << endl;
	}
	
	return elementsActors;
}
	
// Auxuliar method for meuMapper
void TypesManager::configureAtoms(vtkPolyData *atomPositions, vtkSmartPointer<vtkPoints> atomPoints, double radius, vtkSphereSource *sphereSource, int resT, int resP, vtkGlyph3D *atomGlyphs, vtkPolyDataMapper *atomMapper, vtkActor *atomActor, double color[]){

	// insert array of points
	atomPositions->SetPoints(atomPoints);
	
	//atomPoints->Delete(); // ver porque o pus ?aqui?
	
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
	
	// Bounds TODO - Não parece estar a funcar
	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
	
	polyData = sphereSource->GetOutput();
	
	double bounds[6];
	polyData->GetBounds(bounds);
	
	std::cout  << "xmin: " << bounds[0] << " " << "xmax: " << bounds[1] << std::endl
			   << "ymin: " << bounds[2] << " " << "ymax: " << bounds[3] << std::endl
			   << "zmin: " << bounds[4] << " " << "zmax: " << bounds[5] << std::endl;
}

// Convencionar a ordem dos elementos
// devia ser assignball and stick properties
vtkPolyData *TypesManager::convertToBallAndStickType(vtkSmartPointer<vtkPoints> elementsAtomPoints){
	return NULL;
}
	
	
	
	

