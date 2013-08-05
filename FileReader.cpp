//
//  File.cpp
//  ResEye
//
//  Created by Renil Lacmane on 12/25/12.
//
//

#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <list>
#include <exception>

#include "vtkPoints.h"
#include "vtkSmartPointer.h"



using namespace std;

vtkstd::string FileReader::getFileName(){
	return filename;
}

vtkstd::list<vtkSmartPointer<vtkPoints> > FileReader::getAtomsListsFromFile(vtkstd::string filename){
	
	this->filename = filename;
	
	// Set Atoms Positions
	try {
		//	file.read();
	
		ifstream input(filename.c_str());
		//ifstream input("../../PDB Files/ethanol.pdb");
		//ifstream input("../../PDB Files/4hhb.pdb");
		//fstream input("../../PDB Files/adrenaline.pdb");
	
		if (input.fail()){
			cout << "No valid file uploaded!" << endl;
		}
		else{
			vtkstd::string line, element;
			double x, y, z, atom_nr;
			float atompos[3];
			
			//float radius=0;
			//int resT = 7, resP = 7;
			
			vtkstd::list<vtkSmartPointer<vtkPoints> > atomGroupedCoordsList;
			// Array of points
			vtkSmartPointer<vtkPoints> H_AtomPoints = vtkSmartPointer<vtkPoints>::New();
			vtkSmartPointer<vtkPoints> C_AtomPoints = vtkSmartPointer<vtkPoints>::New();
			vtkSmartPointer<vtkPoints> N_AtomPoints = vtkSmartPointer<vtkPoints>::New();
			vtkSmartPointer<vtkPoints> O_AtomPoints = vtkSmartPointer<vtkPoints>::New();
			vtkSmartPointer<vtkPoints> S_AtomPoints = vtkSmartPointer<vtkPoints>::New();
			
			// inner array of elements
			vtkstd::list<vtkSmartPointer<vtkPoints> > innerElementsList;
			// Array of points
			vtkSmartPointer<vtkPoints> H2_AtomPoints = vtkSmartPointer<vtkPoints>::New();
			vtkSmartPointer<vtkPoints> C2_AtomPoints = vtkSmartPointer<vtkPoints>::New();
			vtkSmartPointer<vtkPoints> N2_AtomPoints = vtkSmartPointer<vtkPoints>::New();
			vtkSmartPointer<vtkPoints> O2_AtomPoints = vtkSmartPointer<vtkPoints>::New();
			vtkSmartPointer<vtkPoints> S2_AtomPoints = vtkSmartPointer<vtkPoints>::New();
        
			innerElementsList.push_back(H2_AtomPoints);
			innerElementsList.push_back(C2_AtomPoints);
			innerElementsList.push_back(N2_AtomPoints);
			innerElementsList.push_back(O2_AtomPoints);
			innerElementsList.push_back(S2_AtomPoints);
			
			this->innerElementsList = innerElementsList;
			
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
					if( vtkstd::string::npos != startpos ){
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
					}
					else if(element.compare("C") == 0 || element.compare("C1") == 0 || element.compare("C2") == 0
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
					}
					else if(element.compare("N") == 0
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
							|| element.compare("OX") == 0){
						
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
			} //while
			
			atomGroupedCoordsList.push_back(H_AtomPoints);
			atomGroupedCoordsList.push_back(C_AtomPoints);
			atomGroupedCoordsList.push_back(N_AtomPoints);
			atomGroupedCoordsList.push_back(O_AtomPoints);
			atomGroupedCoordsList.push_back(S_AtomPoints);
			
			this->atomGroupedCoordsList = atomGroupedCoordsList;
			
			return atomGroupedCoordsList;
		}
	
	//}catch (GeneralException e) {
	//	error_log(e.getMessage());
	//	vtkstd::cout << e.getMessage();
	}catch (vtkstd::exception& e){
		vtkstd::cerr << "exception caught: " << e.what() << '\n';
	}
	
	
	exit(0);
}