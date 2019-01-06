#include "imgui/imgui.h"
#include "imgui/imconfig.h"
#include "imgui/imgui_impl_glfw_gl3.h"

//#include <GL/glew.h>    // This example is using glew to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
//#include <GLFW/glfw3.h>

namespace ImGui {

	//int CreateContext();
	ImGui_ImplGlfwGl3_Init(window, true);

	StyleColorsDark();

}