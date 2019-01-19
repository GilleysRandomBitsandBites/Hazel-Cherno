#pragma once

#include "hzpch.h"

//#include "Hazel\Platform\Windows\WindowsWindow.h"
//#include "Hazel\Platform\OpenGL\ImGuiOpenGLRenderer.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>


#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); \
     x;\
     ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
