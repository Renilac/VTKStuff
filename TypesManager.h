//
//  TypesManager.h
//  ResEye
//
//  Created by Renil Lacmane on 12/30/12.
//
//

#ifndef __ResEye__TypesManager__
#define __ResEye__TypesManager__

#include <iostream>
#include <list>

#include "vtkDataArray.h"
#include "vtkPolyData.h"
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSmartPointer.h"
#include "vtkPoints.h"


class TypesManager{
	
private:
	std::string filename;
	
public:
    // constructor e tal
	TypesManager() {};
	
	std::string getFileName(); // TODO - ver se ainda se usa
	std::list<vtkPoints> createAtomsFromFile(std::string filename);
	
	enum structureTypes{ VAN_DER_WALLS, BALL_AND_STICK};
	std::list<std::string> getProteinStructureTypes();

	std::list<vtkSmartPointer<vtkActor> > convertToVanDerWallsType(std::list<vtkSmartPointer<vtkPoints> > elementsAtomPoints);
	vtkPolyData *convertToBallAndStickType(vtkSmartPointer<vtkPoints> elementsAtomPoints);
	
	void configureAtoms(vtkPolyData *atomPositions, vtkSmartPointer<vtkPoints> atomPoints, double radius, vtkSphereSource *sphereSource, int resT, int resP, vtkGlyph3D *atomGlyphs, vtkPolyDataMapper *atomMapper, vtkActor *atomActor, double color[]);
    
};

#endif /* defined(__ResEye__TypesManager__) */
