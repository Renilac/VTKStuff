//
//  TesterFile.cpp
//  ResEye
//
//  Created by Renil Lacmane on 1/5/13.
//
//

#include "TesterFile.h"
#include "ProjectionManager.h"
#include <tcl.h>
#include <iostream>
#include <cmath> // for sqrt() and pow()

#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkLookupTable.h"
#include "vtkStructuredGridReader.h"
#include "vtkDataSetMapper.h"
#include "vtkPDBReader.h"
#include "vtkSphereSource.h"
#include "vtkLODActor.h"
#include "vtkGlyph3D.h"
#include "vtkTubeFilter.h"

#include "vtkPDBReaderExample.h"
// atoms
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkLineSource.h"
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
#include "vtkAppendPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkStructuredPointsGeometryFilter.h"
#include "vtkActor.h"
#include "vtkTubeFilter.h"
// fly
#include "vtkRenderWindow.h"
#include "vtkPolyData.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPoints.h"
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"

//#include "SaveImage.h"

// first include the required header files for the vtk classes we are using
#include "vtkActor.h"
#include "vtkCellArray.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkIntArray.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

#include "vtkPolyDataNormals.h"

#include "TypesManager.h"
#include "FileReader.h"

//#include <boost/algorithm/string.hpp>

using namespace std;
//using namespace boost::algorithm;

// ----------------------------- Global variables to allow access by UserMethod ----------------------------
vtkRenderWindow *renWin;
vtkPolyData *inputDataSet;

// minha tentativa de ter vários átomos
void meuMapper(vtkRenderer *aren){
//void meuMapper(vtkRenderWindow *renWin, vtkPolyData *inputDataSet){
    
	// vtkPoints[] x;
	// x[0] =
	
	/*
	FileReader *fileReader = new FileReader();
	TypesManager *typesManager = new TypesManager();
	
	vtkstd::list<vtkPoints> atomsLists = fileReader->getAtomsListsFromFile("../../PDB Files/4hhb.pdb");
	vtkstd::list<vtkActor> typeStructure = typesManager->getTypeVanDerWalls(atomsLists);
	
	for (vtkstd::list<vtkActor>::iterator it =  typeStructure.begin(); it != typeStructure.end(); ++it){
		aren->AddActor(&*it);
	}*/
	
	// ..
/*
	// Set Atoms Positions
	//    ifstream input("../../PDB Files/ethanol.pdb");
    ifstream input("../../PDB Files/4hhb.pdb");
	//    ifstream input("../../PDB Files/adrenaline.pdb");
	std::string line, element;
    float radius=0;
    double x, y, z, atom_nr;
    int resT = 7, resP = 7;
    
    if (input.fail()){
        cout << "No valid file uploaded!" << endl;
        exit(0);
    }
    else{
		//vtkPoints *elementsPointsArray;
        // Array of points
        vtkPoints *H_AtomPoints = vtkPoints::New();
        vtkPoints *C_AtomPoints = vtkPoints::New();
        vtkPoints *N_AtomPoints = vtkPoints::New();
        vtkPoints *O_AtomPoints = vtkPoints::New();
        vtkPoints *S_AtomPoints = vtkPoints::New();
        
        float atompos[3];
        
        while(getline(input, line)) {
            // Line containing ATOM filed
            if(line.compare(0, 4, "ATOM" )==0){
                atom_nr = atof(line.substr(30, 8).c_str());
                
                // atribuir valores
                x = atof(line.substr(30, 8).c_str());
                y = atof(line.substr(38, 8).c_str());
                z = atof(line.substr(46, 8).c_str());
                //radius = atof(line.substr(54, 5).c_str());
                element = line.substr(12, 3);
                
                // trim right
                element.erase(element.find_last_not_of(" \n\r\t")+1);
                // trim left
                size_t startpos = element.find_first_not_of(" \n\r\t");
                if( std::string::npos != startpos ){
                    element = element.substr( startpos );
                }
                
                //cout << "Element: " << element << endl;
                
                atompos[0] = x;
                atompos[1] = y;
                atompos[2] = z;
                
                if (element.compare("H") == 0
                    || element.compare("1H1") == 0
                    || element.compare("2H1") == 0
                    || element.compare("3H1") == 0
                    || element.compare("1H2") == 0
                    || element.compare("2H2") == 0
                    || element.compare("HH") == 0){
                    
                    // Hydrogen
                    H_AtomPoints->InsertNextPoint(atompos);
                    
                }else if(element.compare("C") == 0 || element.compare("C1") == 0 || element.compare("C2") == 0
                         || element.compare("CA") == 0
                         || element.compare("CB") == 0
                         || element.compare("CG") == 0 || element.compare("CG1") == 0 || element.compare("CG2") == 0
                         || element.compare("CD") == 0 || element.compare("CD1") == 0 || element.compare("CD2") == 0
                         || element.compare("CE") == 0 || element.compare("CE1") == 0 || element.compare("CE2") == 0 || element.compare("CE3") == 0
                         || element.compare("CH") == 0 || element.compare("CH1") == 0 || element.compare("CH2") == 0
                         || element.compare("CZ") == 0 || element.compare("CZ1") == 0 || element.compare("CZ2") == 0 || element.compare("CZ3") == 0
                         || element.compare("CE") == 0){
                    // Carbon
                    C_AtomPoints->InsertNextPoint(atompos);
                }else if(element.compare("N") == 0
                         || element.compare("ND") == 0 || element.compare("ND1") == 0 || element.compare("ND2") == 0
                         || element.compare("NE") == 0 || element.compare("NE1") == 0 || element.compare("NE2") == 0
                         || element.compare("NH") == 0 || element.compare("NH1") == 0 || element.compare("NH2") == 0
                         || element.compare("NZ") == 0 ){
                    // Nitrogen
                    N_AtomPoints->InsertNextPoint(atompos);
                }
                //else{
                else if(element.compare("O") == 0
                        || element.compare("OD") == 0 || element.compare("OD1") == 0 || element.compare("OD2") == 0
                        || element.compare("OE") == 0 || element.compare("OE1") == 0 || element.compare("OE2") == 0
                        || element.compare("OG") == 0 || element.compare("OG1") == 0
                        || element.compare("OH") == 0
                        || element.compare("OX") == 0)
                {
                    
                    O_AtomPoints->InsertNextPoint(atompos);
                }
                else if(element.compare("S") == 0
                        || element.compare("SD") == 0
                        || element.compare("SG") == 0){
                    // Incluir sulfur
                    
                    S_AtomPoints->InsertNextPoint(atompos);
                }
                else{
                    cout << "There are others: " << element << endl;
                }
                // incluir restantes
                
            }
        }
		
		//vtkActor elementsActors[6];
        
        if(H_AtomPoints->GetNumberOfPoints() != 0){
            // insert array of points
            vtkPolyData *atomPositions1 = vtkPolyData::New();
            radius = 1.09; // falta calcular Van der Waals radius
            vtkSphereSource *sphereSource1 = vtkSphereSource::New();
            vtkGlyph3D *atomGlyphs1 = vtkGlyph3D::New();
            vtkPolyDataMapper *atomMapper1 = vtkPolyDataMapper::New();
            vtkActor *atomActor1 = vtkActor::New();
            double color1[3]= {1, 1, 1}; // 255, 255, 255
            
            configureAtoms(atomPositions1, H_AtomPoints, radius, sphereSource1, resT, resP, atomGlyphs1, atomMapper1, atomActor1, color1);
            
			//elementsActors[0] = &atomActor1;
            aren->AddActor(atomActor1);
            cout << "Hydrogen: " << H_AtomPoints->GetNumberOfPoints() << endl;
        }
        if (C_AtomPoints->GetNumberOfPoints()!=0){
            // insert array of points
            vtkPolyData *atomPositions2 = vtkPolyData::New();
            radius = 1.7; // falta calcular Van der Waals radius
            vtkSphereSource *sphereSource2 = vtkSphereSource::New();
            vtkGlyph3D *atomGlyphs2 = vtkGlyph3D::New();
            vtkPolyDataMapper *atomMapper2 = vtkPolyDataMapper::New();
            vtkActor *atomActor2 = vtkActor::New();
            double color2[3]= {144.0f/255, 144.0f/255, 144.0f/255}; // 144, 144, 144
            
            configureAtoms(atomPositions2, C_AtomPoints, radius, sphereSource2, resT, resP, atomGlyphs2, atomMapper2, atomActor2, color2);
            
            aren->AddActor(atomActor2);
            cout << "Carbon: " << C_AtomPoints->GetNumberOfPoints() << endl;
        }
        if (N_AtomPoints->GetNumberOfPoints()!=0){
            // insert array of points
            vtkPolyData *atomPositions3 = vtkPolyData::New();
            radius = 1.55; // falta calcular Van der Waals radius
            vtkSphereSource *sphereSource3 = vtkSphereSource::New();
            vtkGlyph3D *atomGlyphs3 = vtkGlyph3D::New();
            vtkPolyDataMapper *atomMapper3 = vtkPolyDataMapper::New();
            vtkActor *atomActor3 = vtkActor::New();
            double color3[3]= {48.0f/255, 80.0f/255, 248.0f/255};   // 48, 80, 248
            
            configureAtoms(atomPositions3, N_AtomPoints, radius, sphereSource3, resT, resP, atomGlyphs3, atomMapper3, atomActor3, color3);
            
            aren->AddActor(atomActor3);
            cout << "Nitrogen: " << N_AtomPoints->GetNumberOfPoints() << endl;
        }
        if (O_AtomPoints->GetNumberOfPoints()!=0){
            // insert array of points
            vtkPolyData *atomPositions4 = vtkPolyData::New();
            radius = 1.52; // falta calcular Van der Waals radius
            vtkSphereSource *sphereSource4 = vtkSphereSource::New();
            vtkGlyph3D *atomGlyphs4 = vtkGlyph3D::New();
            vtkPolyDataMapper *atomMapper4 = vtkPolyDataMapper::New();
            vtkActor *atomActor4 = vtkActor::New();
            //double color4[3]= {255.0f/255, 13.0f/255, 13.0f/255};   // 255, 13, 13
            double color4[3]= {1, 0, 0};   // 255, 13, 13
            
            configureAtoms(atomPositions4, O_AtomPoints, radius, sphereSource4, resT, resP, atomGlyphs4, atomMapper4, atomActor4, color4);
            
            aren->AddActor(atomActor4);
            cout << "Oxygen e afins: " << O_AtomPoints->GetNumberOfPoints() << endl;
        }
        if (S_AtomPoints->GetNumberOfPoints() != 0) {
            // insert array of points
            vtkPolyData *atomPositions5 = vtkPolyData::New();
            radius = 1.80;
            vtkSphereSource *sphereSource5 = vtkSphereSource::New();
            vtkGlyph3D *atomGlyphs5 = vtkGlyph3D::New();
            vtkPolyDataMapper *atomMapper5 = vtkPolyDataMapper::New();
            vtkActor *atomActor5 = vtkActor::New();
            double color5[3]= {255.0f/255, 255.0f/255, 48.0f/255};   // 255, 255, 48
            
            configureAtoms(atomPositions5, S_AtomPoints, radius, sphereSource5, resT, resP, atomGlyphs5, atomMapper5, atomActor5, color5);
            
            aren->AddActor(atomActor5);
            cout << "Sulfur e afins: " << S_AtomPoints->GetNumberOfPoints() << endl;
        }
        
		
	
	
        //renWin->Render();
        // interact with data
        //iren->Start();
        
 
        // Clean up - deixar para depois
        //aren->Delete();
        //renWin->Delete();
        //iren->Delete();
//        atomActor->Delete();
//        atomMapper->Delete();
//        atomGlyphs->Delete();
//        sphereSource->Delete();
//        atomPositions->Delete();
 
    }
	*/
}

// Auxuliar method for meuMapper
void configureAtoms(vtkPolyData *atomPositions, vtkPoints *atomPoints, double radius, vtkSphereSource *sphereSource, int resT, int resP, vtkGlyph3D *atomGlyphs, vtkPolyDataMapper *atomMapper, vtkActor *atomActor, double color[]){
	
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
	//atomActor->GetProperty()->SetInterpolationToGouraud(); // Ver o que é necessário para o gouraud
	
	// Bounds
	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
	
	polyData = sphereSource->GetOutput();
	
	double bounds[6];
	//polyData->GetBounds(bounds);
	atomPositions->GetBounds(bounds);
	
	
	//vtkPolyLine *squareSource;
	//= vtkPolyLine::New();
	//squareSource->set
	//
	
	//
	//vtkGlyph3D *square = vtkGlyph3D::New();
	//square->SetInput(atomPositions);
	//square->SetSource(squareSource->GetOutput());
	
	std::cout  << "xmin: " << bounds[0] << " " << "xmax: " << bounds[1] << std::endl
	<< "ymin: " << bounds[2] << " " << "ymax: " << bounds[3] << std::endl
	<< "zmin: " << bounds[4] << " " << "zmax: " << bounds[5] << std::endl;
}

// User Method to do animation for 10 "frames"
void UserMethod(void *vtkNotUsed(arg)){
    float p[3];
    for (int n=0; n<50; n++)
    {
        // get the current particle locations
        vtkPoints *oldPoints = (vtkPoints *) (inputDataSet->GetPoints());
        // Create new points by adding a random component to the old
        vtkPoints *newPoints = vtkPoints::New();
        for (int i=0; i<oldPoints->GetNumberOfPoints(); i++)
        {
            //oldPoints->GetPoint(i, p);
            p[0] += (float) (0.1*(RAND_MAX/2 - rand())/RAND_MAX);
            p[1] += (float) (0.1*(RAND_MAX/2 - rand())/RAND_MAX);
            p[2] += (float) (0.1*(RAND_MAX/2 - rand())/RAND_MAX);
            newPoints->InsertNextPoint(p);
        }
        inputDataSet->SetPoints(newPoints);
        newPoints->Delete();
        renWin->Render();
    }
}

void fly(){
    // Create the vtk renderer stuff
    vtkRenderer *ren = vtkRenderer::New();
    renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren);
    renWin->SetSize (300,300);
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
    //iren->SetUserMethod(UserMethod, 0);
    
    // Create points for the starting positions of the particles
    vtkPoints *startPoints = vtkPoints::New();
    float sp[8][3] = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1},
        {1, 1, 0}, {1, 0, 1}, {0, 1, 1,}, {1, 1, 1}};
    for (int i=0; i<8; i++)
        startPoints->InsertNextPoint(sp[i]);
    
    // Create a data set. Load the starting points
    inputDataSet = vtkPolyData::New();
    inputDataSet->SetPoints(startPoints);
    startPoints->Delete();
    
    // Create a vtkSphereSource object to represent a particle
    vtkSphereSource *sphereSource = vtkSphereSource::New();
    sphereSource->SetThetaResolution(8);
    sphereSource->SetPhiResolution(8);
    sphereSource->SetRadius(.05);
    
    // Create the "cloud" of particles, using a vtkGlyph3D object
    vtkGlyph3D *cloud = vtkGlyph3D::New();
    cloud->SetInput(inputDataSet);
    cloud->SetSource(sphereSource->GetOutput());
    
    // Create the mapper and actor and finish up the visualization pipeline
    vtkPolyDataMapper *cloudMapper = vtkPolyDataMapper::New();
    cloudMapper->SetInput(cloud->GetOutput());
    vtkActor *cloudActor = vtkActor::New();
    cloudActor->SetMapper(cloudMapper);
    cloudActor->GetProperty()->SetColor(0, 1, 1);
    ren->AddActor(cloudActor);
    ren->SetBackground(1,1,1);
    
    // interact with data
    renWin->Render();
    
    //SAVEIMAGE( renWin );
    
    iren->Start();
    
    // Clean up
    ren->Delete();
    renWin->Delete();
    inputDataSet->Delete();
    sphereSource->Delete();
    cloud->Delete();
    cloudMapper->Delete();
    cloudActor->Delete();
}

vtkLineSource *createLine(float *a1, float r1, float *a2, float r2, float r){
    
    float start[3], end[3];
    
    float dx = a2[0] - a1[0];
    float dy = a2[1] - a1[1];
    float dz = a2[2] - a1[2];
    
    float L = sqrt(dx*dx+dy*dy+dz*dz);
    r1 = (r < r1) ? sqrt(r1*r1 - r*r) : 0.0;
    r2 = (r < r2) ? sqrt(r2*r2 - r*r) : 0.0;
    
    if(L <= (r1+r2)){
        return 0;
    }
    
    start[0] = a1[0] + r1*dx/L;
    start[1] = a1[1] + r1*dy/L;
    start[2] = a1[2] + r1*dz/L;
    end[0] = a2[0] - r2*dx/L;
    end[1] = a2[1] - r2*dy/L;
    end[2] = a2[2] - r2*dz/L;
    
    vtkLineSource *l = vtkLineSource::New();
    l->SetPoint1(start);
    l->SetPoint2(end);
    
    return l;
}

// 2 Atoms connected by a Bond
void atoms(){
    vtkRenderer *aren = vtkRenderer::New();
    
    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(aren);
    renWin->SetSize( 500, 500 );
    
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
    
    // Set the atom positions
    float atompos[2][3] = {{-0.5, 0.0, 0.0} ,{0.5, 0.0, 0.0}};
    vtkPoints *atomPoints = vtkPoints::New();
    for (int i=0; i<2; i++)
        atomPoints->InsertNextPoint(atompos[i]);
    
    vtkPolyData *atomPositions = vtkPolyData::New();
    atomPositions->SetPoints(atomPoints);
    
    atomPoints->Delete();
    
    // Create the atoms
    float radius = 0.1;
    vtkSphereSource *sphereSource = vtkSphereSource::New();
    sphereSource->SetThetaResolution(16);
    sphereSource->SetPhiResolution(16);
    sphereSource->SetRadius(radius);
    
    vtkGlyph3D *atomGlyphs = vtkGlyph3D::New();
    atomGlyphs ->SetInput(atomPositions);
    atomGlyphs ->SetSource(sphereSource->GetOutput());
    
    // Create the mapper & actor for the atoms
    vtkPolyDataMapper *atomMapper = vtkPolyDataMapper::New();
    atomMapper->SetInput(atomGlyphs->GetOutput());
    vtkActor *atomActor = vtkActor::New();
    atomActor->SetMapper(atomMapper);
    atomActor->GetProperty()->SetColor(0.9, 0.7, 0.15);
    
    
    // Create the 'sticks' (i.e. the bonds)
    vtkAppendPolyData *bonds = vtkAppendPolyData::New();
    
    // append each bond (This  would normally be a loop)
    vtkLineSource *bond;
    float stickradius = 0.02;
    bond = createLine(atompos[0], radius, atompos[1], radius, stickradius);
    if(bond != NULL){
        bonds->AddInput(bond->GetOutput());
    }
    
    // Wrap a tube around the bonds
    vtkTubeFilter *sticks =  vtkTubeFilter::New();
    sticks->SetInput(bonds->GetOutput());
    sticks->SetRadius(stickradius);
    sticks->SetNumberOfSides(8);
    
    // Create the mapper & actor for the sticks
    vtkPolyDataMapper *sticksMapper = vtkPolyDataMapper::New();
    sticksMapper->SetInput(sticks->GetOutput());
    vtkActor *sticksActor = vtkActor::New();
    sticksActor->SetMapper(sticksMapper);
    sticksActor->GetProperty()->SetColor(0, 0.8, 0);
    
    // Add to renderer
    aren->AddActor(sticksActor);
    aren->AddActor(atomActor);
    aren->SetBackground(1,1,1);
    
    
    renWin->Render();
    // interact with data
    iren->Start();
    
    // Clean up
    aren->Delete();
    renWin->Delete();
    iren->Delete();
    sticksActor->Delete();
    sticksMapper->Delete();
    sticks->Delete();
    bonds->Delete();
    atomActor->Delete();
    atomMapper->Delete();
    atomGlyphs->Delete();
    sphereSource->Delete();
    atomPositions->Delete();
}

// This example demonstrate the use of VTK data arrays as attribute
// data as well as field data. It creates geometry (vtkPolyData) as
// well as attribute data explicitly.
int arrays(){
    int i;
    
       // Create a float array which represents the points.
       vtkFloatArray* pcoords = vtkFloatArray::New();
    
       // Note that by default, an array has 1 component.
       // We have to change it to 3 for points
       pcoords->SetNumberOfComponents(3);
       // We ask pcoords to allocate room for at least 4 tuples
       // and set the number of tuples to 4.
       pcoords->SetNumberOfTuples(4);
       // Assign each tuple. There are 5 specialized versions of SetTuple:
       // SetTuple1 SetTuple2 SetTuple3 SetTuple4 SetTuple9
       // These take 1, 2, 3, 4 and 9 components respectively.
       float pts[4][3] = { {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
                               {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0} };
       for (i=0; i<4; i++)
             {
                 pcoords->SetTuple(i, pts[i]);
                 }
    
       // Create vtkPoints and assign pcoords as the internal data array.
       vtkPoints* points = vtkPoints::New();
       points->SetData(pcoords);
    
       // Create the cells. In this case, a triangle strip with 2 triangles
       // (which can be represented by 4 points)
       vtkCellArray* strips = vtkCellArray::New();
       strips->InsertNextCell(4);
       strips->InsertCellPoint(0);
       strips->InsertCellPoint(1);
       strips->InsertCellPoint(2);
       strips->InsertCellPoint(3);
    
       // Create an integer array with 4 tuples. Note that when using
       // InsertNextValue (or InsertNextTuple1 which is equivalent in
       // this situation), the array will expand automatically
       vtkIntArray* temperature = vtkIntArray::New();
       temperature->SetName("Temperature");
       temperature->InsertNextValue(10);
       temperature->InsertNextValue(20);
       temperature->InsertNextValue(30);
       temperature->InsertNextValue(40);
    
       // Create a double array.
       vtkDoubleArray* vorticity = vtkDoubleArray::New();
       vorticity->SetName("Vorticity");
       vorticity->InsertNextValue(2.7);
       vorticity->InsertNextValue(4.1);
       vorticity->InsertNextValue(5.3);
       vorticity->InsertNextValue(3.4);
    
       // Create the dataset. In this case, we create a vtkPolyData
       vtkPolyData* polydata = vtkPolyData::New();
       // Assign points and cells
       polydata->SetPoints(points);
       polydata->SetStrips(strips);
       // Assign scalars
       polydata->GetPointData()->SetScalars(temperature);
       // Add the vorticity array. In this example, this field
       // is not used.
       polydata->GetPointData()->AddArray(vorticity);
    
       // Create the mapper and set the appropriate scalar range
       // (default is (0,1)
       vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
       mapper->SetInput(polydata);
       mapper->SetScalarRange(0, 40);
    
       // Create an actor.
       vtkActor* actor = vtkActor::New();
       actor->SetMapper(mapper);
    
// Create the rendering objects.
       vtkRenderer* ren = vtkRenderer::New();
       ren->AddActor(actor);
    
       vtkRenderWindow* renWin = vtkRenderWindow::New();
       renWin->AddRenderer(ren);
    
       vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
       iren->SetRenderWindow(renWin);
       iren->Initialize();
       iren->Start();
    
       pcoords->Delete();
       points->Delete();
       strips->Delete();
       temperature->Delete();
       vorticity->Delete();
       polydata->Delete();
       mapper->Delete();
       actor->Delete();
       ren->Delete();
       renWin->Delete();
       iren->Delete();
    
       return 0;
}

// Mols 1 - Source do PDBReader
void mols1(){
    
    cout << "Molecular Struture 1!"<< endl;
    
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(.1, .2, .3);
    
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(900, 600);
    
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);
    
    vtkSmartPointer<vtkPDBReader> pdb = vtkSmartPointer<vtkPDBReader>::New();
//    pdb->SetFileName("../../PDB Files/4hhb.pdb");
//    pdb->SetFileName("../../PDB Files/ethanol.pdb");
    ifstream input("../../PdbFiles/adrenaline.pdb");
    pdb->SetHBScale(1.0);
    pdb->SetBScale(1.0);
    pdb->Update();
    std::cout <<"# of atoms is: " << pdb->GetNumberOfAtoms() << std::endl;
    
    //pdb->Radii;
    
    double resolution = std::sqrt(300000.0 / pdb->GetNumberOfAtoms());
    if (resolution > 20){
        resolution = 20;
    }
    if (resolution < 4){
        resolution = 4;
    }
    std::cout <<"Resolution is: " << resolution << std::endl;
    
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetCenter(0, 0, 0);
    sphere->SetRadius(1);
    sphere->SetThetaResolution(static_cast<int>(resolution));
    sphere->SetPhiResolution(static_cast<int>(resolution));
    
    
    vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
    glyph->SetInputConnection(pdb->GetOutputPort());
    glyph->SetOrient(1);
    glyph->SetColorMode(1);
    // glyph->ScalingOn();
    glyph->SetScaleMode(2);
    glyph->SetScaleFactor(.25);
    glyph->SetSourceConnection(sphere->GetOutputPort());
    
    vtkSmartPointer<vtkPolyDataMapper> atomMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    atomMapper->SetInputConnection(glyph->GetOutputPort());
    atomMapper->ImmediateModeRenderingOn();
    atomMapper->UseLookupTableScalarRangeOff();
    atomMapper->ScalarVisibilityOn();
    atomMapper->SetScalarModeToDefault();
    
    vtkSmartPointer<vtkLODActor> atom = vtkSmartPointer<vtkLODActor>::New();
    atom->SetMapper(atomMapper);
    atom->GetProperty()->SetRepresentationToSurface();
    atom->GetProperty()->SetInterpolationToGouraud();
    atom->GetProperty()->SetAmbient(0.15);
    atom->GetProperty()->SetDiffuse(0.85);
    atom->GetProperty()->SetSpecular(0.1);
    atom->GetProperty()->SetSpecularPower(30);
    atom->GetProperty()->SetSpecularColor(1, 1, 1);
    atom->SetNumberOfCloudPoints(30000);
    
    renderer->AddActor(atom);
    
    vtkSmartPointer<vtkTubeFilter> tube = vtkSmartPointer<vtkTubeFilter>::New();
    tube->SetInputConnection(pdb->GetOutputPort());
    tube->SetNumberOfSides(static_cast<int>(resolution));
    tube->CappingOff();
    tube->SetRadius(0.2);
    tube->SetVaryRadius(0);
    tube->SetRadiusFactor(10);
    
    vtkSmartPointer<vtkPolyDataMapper> bondMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    bondMapper->SetInputConnection(tube->GetOutputPort());
    bondMapper->ImmediateModeRenderingOn();
    bondMapper->UseLookupTableScalarRangeOff();
    bondMapper->ScalarVisibilityOff();
    bondMapper->SetScalarModeToDefault();
    
    vtkSmartPointer<vtkLODActor> bond = vtkSmartPointer<vtkLODActor>::New();
    bond->SetMapper(bondMapper);
    bond->GetProperty()->SetRepresentationToSurface();
    bond->GetProperty()->SetInterpolationToGouraud();
    bond->GetProperty()->SetAmbient(0.15);
    bond->GetProperty()->SetDiffuse(0.85);
    bond->GetProperty()->SetSpecular(0.1);
    bond->GetProperty()->SetSpecularPower(30);
    bond->GetProperty()->SetSpecularColor(1, 1, 1);
    bond->GetProperty()->SetDiffuseColor(1.0000, 0.8941, 0.70981);
    
    renderer->AddActor(bond);
    
    interactor->Initialize();
    interactor->Start();

}

// Mols 2 - O que fiz com o OpenGL
void mols2(){
    
    cout << "Molecular Struture 2!"<< endl;
    
    ProjectionManager proMan;
    // is the class you will use to create the renderer which will draw in the window
    vtkSmartPointer<vtkRenderer> renderer = proMan.InitializeCanvas();
    
    vtkSmartPointer<vtkPDBReader> pdb = vtkSmartPointer<vtkPDBReader>::New();
    pdb->SetFileName("../../PDB Files/4hhb.pdb");
    pdb->SetHBScale(1.0);
    pdb->SetBScale(1.0);
    pdb->Update();
    std::cout <<"# of atoms is: " << pdb->GetNumberOfAtoms() << std::endl;
    
    double resolution = std::sqrt(300000.0 / pdb->GetNumberOfAtoms());
    if (resolution > 20){
        resolution = 20;
    }
    if (resolution < 4){
        resolution = 4;
    }
    std::cout <<"Resolution is: " << resolution << std::endl;
    
    ifstream input("../../PDB Files/4hhb.pdb");
    string line, element;
    //double radius=0;
    double x, y, z, atom_nr;
    
    if (input.fail()){
        cout << "No valid file was read!" << endl;
        exit(0);
    }
    else
        while( getline( input, line ) ) {
            
            vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
            
            
            if(line.compare(0, 4, "ATOM" )==0){
                atom_nr = atof(line.substr(30, 8).c_str());
                x = atof(line.substr(30, 8).c_str());
                y = atof(line.substr(38, 8).c_str());
                z = atof(line.substr(46, 8).c_str());
                element = line.substr(76, 2);
                
                sphere->SetCenter(x, y, z);
                sphere->SetRadius(atof(line.substr(54, 5).c_str()));
                
                sphere->SetThetaResolution(static_cast<int>(resolution));
                sphere->SetPhiResolution(static_cast<int>(resolution));
                
                vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
                glyph->SetInputConnection(pdb->GetOutputPort());
                glyph->SetOrient(1);
                glyph->SetColorMode(1);
                // glyph->ScalingOn();
                glyph->SetScaleMode(2);
                glyph->SetScaleFactor(.25);
                glyph->SetSourceConnection(sphere->GetOutputPort());
                
                vtkSmartPointer<vtkPolyDataMapper> atomMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
                atomMapper->SetInputConnection(glyph->GetOutputPort());
                atomMapper->ImmediateModeRenderingOn();
                atomMapper->UseLookupTableScalarRangeOff();
                atomMapper->ScalarVisibilityOn();
                atomMapper->SetScalarModeToDefault();
                
                vtkSmartPointer<vtkLODActor> atom = vtkSmartPointer<vtkLODActor>::New();
                atom->SetMapper(atomMapper);
                atom->GetProperty()->SetRepresentationToSurface();
                atom->GetProperty()->SetInterpolationToGouraud();
                atom->GetProperty()->SetAmbient(0.15);
                atom->GetProperty()->SetDiffuse(0.85);
                atom->GetProperty()->SetSpecular(0.1);
                atom->GetProperty()->SetSpecularPower(30);
                atom->GetProperty()->SetSpecularColor(1, 1, 1);
                atom->SetNumberOfCloudPoints(30000);
                
                renderer->AddActor(atom);
                
//                vtkSmartPointer<vtkTubeFilter> tube = vtkSmartPointer<vtkTubeFilter>::New();
//                tube->SetInputConnection(pdb->GetOutputPort());
//                tube->SetNumberOfSides(static_cast<int>(resolution));
//                tube->CappingOff();
//                tube->SetRadius(0.2);
//                tube->SetVaryRadius(0);
//                tube->SetRadiusFactor(10);
//                
//                vtkSmartPointer<vtkPolyDataMapper> bondMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//                bondMapper->SetInputConnection(tube->GetOutputPort());
//                bondMapper->ImmediateModeRenderingOn();
//                bondMapper->UseLookupTableScalarRangeOff();
//                bondMapper->ScalarVisibilityOff();
//                bondMapper->SetScalarModeToDefault();
//                
//                vtkSmartPointer<vtkLODActor> bond = vtkSmartPointer<vtkLODActor>::New();
//                bond->SetMapper(bondMapper);
//                bond->GetProperty()->SetRepresentationToSurface();
//                bond->GetProperty()->SetInterpolationToGouraud();
//                bond->GetProperty()->SetAmbient(0.15);
//                bond->GetProperty()->SetDiffuse(0.85);
//                bond->GetProperty()->SetSpecular(0.1);
//                bond->GetProperty()->SetSpecularPower(30);
//                bond->GetProperty()->SetSpecularColor(1, 1, 1);
//                bond->GetProperty()->SetDiffuseColor(1.0000, 0.8941, 0.70981);
//                
//                renderer->AddActor(bond);
//                
//                interactor->Initialize();
//                interactor->Start();

                
                //cout << element << endl;
                
                // create atoms, if the coordinates are valid
                //                    if (x!=0){
                //                        //                cout << "Atom nr: " << atom_nr << " x: " << x << " y: " << y << " z: " << z << '\n';
                //
                //                        // color defined by element
                //                        glColor3d( 0.9, 0.9, 0.9);
                //                        if( element.compare(1,1, "C") == 0){
                //                            glColor3d( 144/(double)255, 144/(double)255, 144/(double)255);
                //                            radius=0.68;
                //                        }else if( element.compare(1,1, "N") == 0){
                //                            glColor3d( 48/(double)255, 80/(double)255, 248/(double)255);
                //                            radius=0.68;
                //                        }else if( element.compare(1,1, "O") == 0){
                //                            glColor3d( 255/(double)255, 13/(double)255, 13/(double)255);
                //                            radius=0.68;
                //                        }
                //
                //                        glPushMatrix();						//Save the current state of transformations
                //
                //                        glTranslated(x, y, z);              //Move to the center of the sphere
                //                        glRotatef(20, 1.0f, 2.0f, 3.0f);	//Rotate about the the vector (1, 2, 3)
                //
                //                        glutSolidSphere(radius, slices, 16);	// create sphere
                //                        
                //                        glPopMatrix();
                //                    }
  
                
    
    // vtkRenderWindow is the class you will use to create a window
    // The vtkRenderWindow is a container class for vtkRenderer objects
    proMan.RenderProjection(renderer);
                
    }
    else {
                //            cout << "There are no atom field!" << endl;
      }
    }

}

// Mols 3 - Exemplo retirado do PDBReader, ToDo - modificar
void mols3(vtkSmartPointer<vtkRenderer> renderer){
    cout << "Molecular Struture 3!"<< endl;
    
    //vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(.1, .2, .3);
    
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(300, 300);
    
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);
    
    vtkSmartPointer<vtkPDBReaderExample> pdb = vtkSmartPointer<vtkPDBReaderExample>::New();
    pdb->SetFileName("../../PDB Files/4hhb.pdb");
    pdb->SetHBScale(1.0);
    pdb->SetBScale(1.0);
    pdb->Update();
    std::cout <<"# of atoms is: " << pdb->GetNumberOfAtoms() << std::endl;
    
    double resolution = std::sqrt(300000.0 / pdb->GetNumberOfAtoms());
    if (resolution > 20){
        resolution = 20;
    }
    if (resolution < 4){
        resolution = 40;
    }
    std::cout <<"Resolution is: " << resolution << std::endl;
    
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetCenter(0, 0, 0);
    sphere->SetRadius(1);
    sphere->SetThetaResolution(static_cast<int>(resolution));
    sphere->SetPhiResolution(static_cast<int>(resolution));
    
    vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
    glyph->SetInputConnection(pdb->GetOutputPort());
    glyph->SetOrient(1);
    glyph->SetColorMode(1);
    // glyph->ScalingOn();
    glyph->SetScaleMode(2);
    glyph->SetScaleFactor(.25);
    glyph->SetSourceConnection(sphere->GetOutputPort());
    
    vtkSmartPointer<vtkPolyDataMapper> atomMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    atomMapper->SetInputConnection(glyph->GetOutputPort());
    atomMapper->ImmediateModeRenderingOn();
    atomMapper->UseLookupTableScalarRangeOff();
    atomMapper->ScalarVisibilityOn();
    atomMapper->SetScalarModeToDefault();
    
    vtkSmartPointer<vtkLODActor> atom = vtkSmartPointer<vtkLODActor>::New();
    atom->SetMapper(atomMapper);
    atom->GetProperty()->SetRepresentationToSurface();
    atom->GetProperty()->SetInterpolationToGouraud();
    atom->GetProperty()->SetAmbient(0.15);
    atom->GetProperty()->SetDiffuse(0.85);
    atom->GetProperty()->SetSpecular(0.1);
    atom->GetProperty()->SetSpecularPower(30);
    atom->GetProperty()->SetSpecularColor(1, 1, 1);
    atom->SetNumberOfCloudPoints(30000);
    
    renderer->AddActor(atom);
    
    vtkSmartPointer<vtkTubeFilter> tube = vtkSmartPointer<vtkTubeFilter>::New();
    tube->SetInputConnection(pdb->GetOutputPort());
    tube->SetNumberOfSides(static_cast<int>(resolution));
    tube->CappingOff();
    tube->SetRadius(0.2);
    tube->SetVaryRadius(0);
    tube->SetRadiusFactor(10);
    
    vtkSmartPointer<vtkPolyDataMapper> bondMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    bondMapper->SetInputConnection(tube->GetOutputPort());
    bondMapper->ImmediateModeRenderingOn();
    bondMapper->UseLookupTableScalarRangeOff();
    bondMapper->ScalarVisibilityOff();
    bondMapper->SetScalarModeToDefault();
    
    vtkSmartPointer<vtkLODActor> bond = vtkSmartPointer<vtkLODActor>::New();
    bond->SetMapper(bondMapper);
    bond->GetProperty()->SetRepresentationToSurface();
    bond->GetProperty()->SetInterpolationToGouraud();
    bond->GetProperty()->SetAmbient(0.15);
    bond->GetProperty()->SetDiffuse(0.85);
    bond->GetProperty()->SetSpecular(0.1);
    bond->GetProperty()->SetSpecularPower(30);
    bond->GetProperty()->SetSpecularColor(1, 1, 1);
    bond->GetProperty()->SetDiffuseColor(1.0000, 0.8941, 0.70981);
    
    renderer->AddActor(bond);
    
    //interactor->Initialize();
    //interactor->Start();
    
    //return renderer;
    
}

// não deu
void vtkColorMapping(){
   
    ProjectionManager proMan;
    
    // is the class you will use to create the renderer which will draw in the window
    vtkSmartPointer<vtkRenderer> ren1 = proMan.InitializeCanvas();
    
    // There are two basic types of objects involved:
    // vtkDataObject(coordinates, etc), vtkProcessObject(algorithms, etc)
    // Data Objects and Process Objects are connected together to form a visualization pipeline.
    // Source -> Reader -> Filter -> Mapper ->Actor
    
    // The primary VTK classes used for color mapping are vtkLookupTable and vtkDataSetMapper.
    vtkSmartPointer<vtkLookupTable> lut = vtkLookupTable::New();
    lut->SetNumberOfColors(16);
    lut->SetHueRange(0.0, 0.667);
    lut->Build();
    
    vtkSmartPointer<vtkStructuredGridReader> reader = vtkStructuredGridReader::New();
    reader->SetFieldDataName("./Data/subset.vtk");
    reader->Update();
    
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkDataSetMapper::New();
    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->SetLookupTable(lut);
    //Tcl_Eval(mapper->SetScalarRange((reader->GetOutput()->GetScalarRange()));
    mapper->SetScalarRange(0.0, 0.7);
    
    vtkSmartPointer<vtkActor> actors = vtkActor::New();
    actors->SetMapper(mapper);
    
    ren1->AddActor(actors);
    
    // vtkRenderWindow is the class you will use to create a window
    // The vtkRenderWindow is a container class for vtkRenderer objects
    proMan.RenderProjection(ren1);
}

void vtkConeCreation(){
    
    ProjectionManager proMan;
    
    // is the class you will use to create the renderer which will draw in the window
    vtkSmartPointer<vtkRenderer> ren1 = proMan.InitializeCanvas();
    
    // Instance of vtkConeSource to generate polygonal data for a cone
    vtkSmartPointer<vtkConeSource> cone = vtkConeSource::New();
    cone->SetResolution(100);
    
    // Instance of vtkPolyDataMapper to take the polygonal data from the vtkConeSource and create a rendering for the renderer
    vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkPolyDataMapper::New();
    coneMapper->SetInput(cone->GetOutput());
    
    // Is the class you will use to represent 3D geometric data in the scene
    vtkSmartPointer<vtkActor> coneActor = vtkActor::New();
    coneActor->SetMapper(coneMapper);
    coneActor->GetProperty()->SetColor(1, 0, 0);
    
    ren1->AddActor(coneActor);
    
    // vtkRenderWindow is the class you will use to create a window
    // The vtkRenderWindow is a container class for vtkRenderer objectsrrrrrrqqqqqrqqrrr
    proMan.RenderProjection(ren1);
    
}

// ------------------------ Mouse interactions ------------------------
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>

#include "InputDataManager.h"

void mouseEventsStuff(vtkSmartPointer<vtkRenderer> renderer){
	// focus Area
	vtkSmartPointer<vtkCubeSource> focusArea = vtkSmartPointer<vtkCubeSource>::New();
	focusArea->SetBounds(-2, 2, -2, 2, -2, 2);
	focusArea->SetCenter(8.0, 0.0, 0.0);
	focusArea->Update();
	vtkSmartPointer<vtkPolyDataMapper> focusMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	focusMapper->SetInputConnection(focusArea->GetOutputPort());
	vtkSmartPointer<vtkActor> focusAreaActor = vtkSmartPointer<vtkActor>::New();
	focusAreaActor->SetMapper(focusMapper);
	// ----
	
	// Sphere
	vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetCenter(0.0, 0.0, 0.0);
	sphereSource->SetRadius(5.0);
	// added by me
	sphereSource->SetPhiResolution(16);
	sphereSource->SetThetaResolution(16);
	sphereSource->Update();
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	// added by me
	actor->GetProperty()->SetInterpolationToGouraud();
	
	renderer->AddActor(actor);
	renderer->AddActor(focusAreaActor);
	
	//InputDataManager idm;
	//idm.setInteractionBehaviourToWindow(renderer, focusAreaActor, );

}

// At the end because of method  referencing
void TesterFile::callTester(vtkSmartPointer<vtkRenderer> renderer){
    
    cout << "Tester processing..." << endl;
    
    // --------------------------------------------------------------
    int choice = 3;
    
    if (choice==1){
        mols1();
    }
    else if(choice==2){
        mols2();
    }
    else{
        //mols3(renderer);
        //atoms();
        //fly();
        //arrays();
        
        // - - -
		//vtkRenderWindow *renWin;
		//vtkPolyData *inputDataSet;
		//meuMapper(renWin, inputDataSet); ideal
		//meuMapper(renderer);
		mouseEventsStuff(renderer); // Comparar se padrao observer/event é melhor
		// - - -
    }
	
    // --------------------------------------------------------------
    //firstProjection();
    
    
	//    std::list<std::string> list;
	//	list.assign(1, "bro");
	//	cout << list.front() << endl;
    
	cout << "Tester end processing!" << endl;
}