
#include "hzpch.h"
#include "Application.h"

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw_gl3.h"
#include "Hazel/Log.h"

#include <glad\glad.h>


namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled())     // I wrote the Handled function in Event.h
				break;
		}
	}

	



	void Application::Run()
	{	
		// Setup window
		//GLFWwindow* window = glfwCreateWindow(800, 600,"" , NULL, NULL);
		//glfwMakeContextCurrent(window);
		//glfwSwapInterval(1); // Enable vsync
		


		// ImGui init
		//ImGui::CreateContext();
		//ImGui_ImplGlfwGL3_Init(window, true);
		//ImGui::StyleColorsDark();

		//bool show_demo_window = true;
		//bool show_another_window = false;
		//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();

			//ImGui_ImplGlfwGL3_NewFrame();


			

			

			{
				//static float f = 0.0f;
				//static int counter = 0;
				//ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
				//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
				//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
				//ImGui::Checkbox("Another Window", &show_another_window);

				//if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
				//	counter++;
				//ImGui::SameLine();
				//ImGui::Text("counter = %d", counter);

				//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			//if (show_demo_window)
			//{
				//ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
				//ImGui::ShowDemoWindow(&show_demo_window);
			//}

			//Rendering
			
			//ImGui::Render();
			//ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			//glfwSwapBuffers(window);
		}

		
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		// Cleanup
		//ImGui_ImplGlfwGL3_Shutdown();
		//ImGui::DestroyContext();

		return true;
	}

}
