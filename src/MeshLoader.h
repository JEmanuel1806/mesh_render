#pragma once 

#include <iostream>
#include <fstream>     
#include <sstream> 

#include "Mesh.h"

class MeshLoader {
public:
	Mesh loadMesh(std::string filepath);
private:
};