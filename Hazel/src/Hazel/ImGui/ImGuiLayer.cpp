#include "hzpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Hazel\Platform\OpenGL\ImGuiOpenGLRenderer.h"

// Temporary
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Hazel\keyboard.h"
#include "Hazel\Application.h"

namespace Hazel {


	ImGuiLayer::ImGuiLayer() // Creates an Imgui layer- constructor
		: Layer("ImGuiLayer")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}

	/* const char* ImGui_ImplGlfw_GetClipboardText(void* user_data)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
		//io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
		glfwGetClipboardString((GLFWwindow*)user_data);
		return false;
	}

	 void ImGui_ImplGlfw_SetClipboardText(void* user_data, const char* text)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
		//io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
		glfwSetClipboardString((GLFWwindow*)user_data, text);

	}*/

	

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		

		// Temporary: should eventually use Hazel key codes Have implemented Hazel codes
		io.KeyMap[ImGuiKey_Tab] = HAZEL_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = HAZEL_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = HAZEL_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = HAZEL_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = HAZEL_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = HAZEL_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = HAZEL_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = HAZEL_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = HAZEL_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = HAZEL_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = HAZEL_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = HAZEL_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = HAZEL_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = HAZEL_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = HAZEL_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = HAZEL_KEY_A;
		io.KeyMap[ImGuiKey_C] = HAZEL_KEY_C;
		io.KeyMap[ImGuiKey_V] = HAZEL_KEY_V;
		io.KeyMap[ImGuiKey_X] = HAZEL_KEY_X;
		io.KeyMap[ImGuiKey_Y] = HAZEL_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = HAZEL_KEY_Z;

		//io.SetClipboardTextFn = 0; //ImGui_ImplGlfw_SetClipboardText;
		//io.GetClipboardTextFn = 0; // ImGui_ImplGlfw_GetClipboardText;
		//io.ClipboardUserData = app.GetWindow();

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		

		

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time - time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		

		// Poll for and process events
		//HAZELPollEvents();
		
		
		
	}

	void ImGuiLayer::OnEvent(Event & event)
	{
		
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
		

	}

	/* const char* ImGui_ImplGlfw_GetClipboardText(void* user_data)
	{
		ImGuiIO& io = ImGui::GetIO();
		//io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
		io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
		glfwGetClipboardString((GLFWwindow*)user_data);
		return false;
	}

	 void ImGui_ImplGlfw_SetClipboardText(void* user_data, const char* text)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
		//io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
		glfwSetClipboardString((GLFWwindow*)user_data, text);
		
	}*/

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown [HAZEL_KEY_LEFT_CONTROL] || io.KeysDown[HAZEL_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[HAZEL_KEY_LEFT_SHIFT] || io.KeysDown[HAZEL_KEY_RIGHT_SHIFT];
		io.KeyAlt= io.KeysDown[HAZEL_KEY_LEFT_ALT] || io.KeysDown[HAZEL_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[HAZEL_KEY_LEFT_SUPER] || io.KeysDown[HAZEL_KEY_RIGHT_SUPER];

		 

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	

	
	
}