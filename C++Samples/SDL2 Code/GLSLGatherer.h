#pragma once
#include "Gatherer.h"
#include <string>
#include <vector>
class GLSLGatherer :
	public Gatherer
{
public:
	GLSLGatherer();
	~GLSLGatherer();
	virtual void say(std::string words);
private:
	//Identify GLSL files within project assets
	virtual void searchForItems();
	//Divide collectables amongst new pool of collection threads
	virtual void strategizeCollection();
	//pack GLSL code from collection threads into a map of shader types, and source code to be processed by a GLSL compiler
	virtual void collectItems();
	//Read GLSL code from disk and Identify shader type before returning tuple as string of glsl source and type of program
	virtual void collectionTask();
	virtual std::string collectFile(std::string glslTarget, std::string* storage);
	std::vector<std::string> glslShaderLocations;

};

