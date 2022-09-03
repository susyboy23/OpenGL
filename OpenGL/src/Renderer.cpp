#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	// keep looping until glGetError has no more error to throw
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* name, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << name << " " << file << " "
			<< line << "\n";
		return false;
	}
	return true;
}
