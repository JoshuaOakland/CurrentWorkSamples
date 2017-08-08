#pragma once
#include<glew.h>
#include <SDL.h>
#include <GL/gl.h>
#include <queue>
#include "Model.h"
#include <iostream>
class GraphicsProcessor
{
public:
	GraphicsProcessor();
	~GraphicsProcessor();
	SDL_Window* window_ptr;
	SDL_GLContext context;
	std::queue<SDL_Event> eventQueue;
	void render();
	void enqueueInput();
	SDL_Event event;
	std::vector<Model*>renderableArray;
public:
	void loadModel(Model* model);
};

