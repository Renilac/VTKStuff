/*=========================================================================
 
 Program:   Visualization Toolkit
 Module:    vtkPDBReader.h
 
 Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 All rights reserved.
 See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
 
 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.
 
 =========================================================================*/
// .NAME vtkPDBReader - read Molecular Data files
// .SECTION Description
// vtkPDBReader is a source object that reads Molecule files
// The FileName must be specified
//
// .SECTION Thanks
// Dr. Jean M. Favre who developed and contributed this class

#ifndef __vtkPDBReaderExample_h
#define __vtkPDBReaderExample_h

#include "vtkMoleculeReaderBase.h"


class VTK_IO_EXPORT vtkPDBReaderExample : public vtkMoleculeReaderBase
{
public:
    vtkTypeMacro(vtkPDBReaderExample,vtkMoleculeReaderBase);
    void PrintSelf(ostream& os, vtkIndent indent);
    
    static vtkPDBReaderExample *New();
    
protected:
    vtkPDBReaderExample();
    ~vtkPDBReaderExample();
    
    void ReadSpecificMolecule(FILE* fp);
    
private:
    vtkPDBReaderExample(const vtkPDBReaderExample&);  // Not implemented.
    void operator=(const vtkPDBReaderExample&);  // Not implemented.
};

#endif
