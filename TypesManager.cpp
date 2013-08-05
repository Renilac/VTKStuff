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

#include "TypesManager.h"
#include "GeneralException.h"

#include <vtkPoints.h>
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSmartPointer.h"
#include "vtkProperty.h"


vtkstd::list<vtkstd::string> TypesManager::getProteinStructureTypes(){
	
	vtkstd::list<vtkstd::string> proteinStructureTypes;
	proteinStructureTypes.push_back("BALL_AND_STICK");
	proteinStructureTypes.push_back("VAN_DER_WALLS");
	
	return proteinStructureTypes;
}

// TODO - Mapear bem os atomos

// Create placeholder for atoms of structure type VanDerWalls
vtkstd::list<vtkSmartPointer<vtkActor> > TypesManager::createVanDerWallsType(vtkstd::list<vtkSmartPointer<vtkPoints> > elementsList) {
	if(elementsList.empty()){
		throw GeneralException("ConvertToVanDerWallsType called with empty parameters!");
	}
	/*
	 elementsPointsArray[0] = H_AtomPoints;
	 elementsPointsArray[1] = C_AtomPoints;
	 elementsPointsArray[2] = N_AtomPoints;
	 elementsPointsArray[3] = O_AtomPoints;
	 elementsPointsArray[4] = S_AtomPoints;
	 */
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
		element++;		// TODO - juntar variaveis (radius, color)
		radius = 1.7;	// TODO - falta calcular Van der Waals radius
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
		radius = 1.55; // TODO calcular Van der Waals radius
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
	/*
	 elementsPointsArray[0] = H_AtomPoints;
	 elementsPointsArray[1] = C_AtomPoints;
	 elementsPointsArray[2] = N_AtomPoints;
	 elementsPointsArray[3] = O_AtomPoints;
	 elementsPointsArray[4] = S_AtomPoints;
	 */
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
		radius = 0.50; // TODO calcular Van der Waals radius
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




