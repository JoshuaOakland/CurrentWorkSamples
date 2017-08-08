#include "GraphicsProcessor.h"



GraphicsProcessor::GraphicsProcessor()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	window_ptr = SDL_CreateWindow("Hello SDL from VS 2015!", 100, 100, 1280, 1024, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window_ptr);
	//glewExperimental = GL_TRUE;
	glewInit();
	eventQueue = {};
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	renderableArray = {};
}


GraphicsProcessor::~GraphicsProcessor()
{
}

void GraphicsProcessor::enqueueInput()
{
	while (SDL_PollEvent(&event))
	{
		eventQueue.push(event);
	}

}

void GraphicsProcessor::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Model* model : renderableArray)
	{
		model->draw();
	}
	SDL_GL_SwapWindow(window_ptr);
	return;
}
void GraphicsProcessor::loadModel(Model* model)
{
	model->init();
	renderableArray.push_back(model);
}