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
	
public:
    // constructor e tal
	TypesManager() {};

	enum structureTypes{ VAN_DER_WALLS, BALL_AND_STICK};
	vtkstd::list<vtkstd::string> getProteinStructureTypes();
	vtkstd::list<vtkSmartPointer<vtkActor> > createVanDerWallsType(vtkstd::list<vtkSmartPointer<vtkPoints> > elementsList);
	vtkstd::list<vtkSmartPointer<vtkActor> > createBallAndStickType(vtkstd::list<vtkSmartPointer<vtkPoints> > elementsList);
	
	void configureAtoms(vtkPolyData *atomPositions, vtkSmartPointer<vtkPoints> atomPoints, double radius, vtkSphereSource *sphereSource, int resT, int resP, vtkGlyph3D *atomGlyphs, vtkPolyDataMapper *atomMapper, vtkActor *atomActor, double color[]);
};

#endif /* defined(__ResEye__TypesManager__) */
