# define the project
PROJECT(ResEye)

# find VTK
FIND_PACKAGE(VTK)
IF(VTK_FOUND)
	INCLUDE(${VTK_USE_FILE})
ELSE(VTK_FOUND)
	MESSAGE(FATAL_ERROR
		"Cannot build the executable without VTK. Please set the VTK_DIR")
ENDIF(VTK_FOUND)

# define the executable
ADD_EXECUTABLE(ResEye MACOSX_BUNDLE 
		main.cxx
		Atoms.h
		AtomsBallAndStickStructure.h
		AtomsVanDerWallsStructure.h
		ChunkManager.h
		FileReader.h
		GeneralException.h
		InfoManager.h
		InputDataManager.h
		InteractionStyles.h
		LODManager.h
		MouseEvents.h
		ProjectionManager.h
		TesterFile.h
		TypesManager.h
		Utils.h
		vtkPDBReaderExample.h

		Atoms.cpp
		AtomsBallAndStickStructure.cpp
		AtomsVanDerWallsStructure.cpp
		ChunkManager.cpp
		FileReader.cpp
		GeneralException.cpp
		InfoManager.cpp
		InputDataManager.cpp
		InteractionStyles.cpp
		LODManager.cpp
		MouseEvents.cpp
		ProjectionManager.cpp
		TesterFile.cpp
		TypesManager.cpp
		Utils.cpp
		vtkPDBReaderExample.cpp
		)

#define libraries
IF(VTK_LIBRARIES)
  TARGET_LINK_LIBRARIES(ResEye ${VTK_LIBRARIES})
ELSE()
  TARGET_LINK_LIBRARIES(ResEye 
    	vtkCommon
	vtkGraphics
	vtkIO
	vtkRendering
	vtkHybrid
  )
ENDIF()

