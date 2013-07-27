//
//  TesterFile.h
//  ResEye
//
//  Created by Renil Lacmane on 1/5/13.
//
//

#ifndef __ResEye__TesterFile__
#define __ResEye__TesterFile__

#include <iostream>

#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

class TesterFile {
    
public:
    void callTester(vtkSmartPointer<vtkRenderer> renderer);
};

#endif /* defined(__ResEye__TesterFile__) */
