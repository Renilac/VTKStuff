//
//  ProjectionManager.h
//  ResEye
//
//  Created by Renil Lacmane on 12/30/12.
//
//

#ifndef __ResEye__ProjectionManager__
#define __ResEye__ProjectionManager__

#include <iostream>

#include "vtkRenderer.h"
#include "vtkSmartPointer.h"

class ProjectionManager{
  
public:
    vtkSmartPointer<vtkRenderer> InitializeCanvas();
    void RenderProjection(vtkSmartPointer<vtkRenderer> renderer);
};

#endif /* defined(__ResEye__ProjectionManager__) */
