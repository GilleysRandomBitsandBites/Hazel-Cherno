
#include "hzpch.h"
#include "Application.h"


#include "Hazel/Log.h"
#include "Render\Shader.h"

#include <glad\glad.h>
#include "GLFW\glfw3.h"
#include "Render\Renderer.h"
#include "Render\VertexBufferLayout.h"
#include "Render\IndexBuffer.h"
#include "Render\VertexBuffer.h"
#include "Render\VertexArray.h"


namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	 Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		
		
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
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

	// Need filepath to shader Shader shader(filepath);
	Renderer renderer;


	void Application::Run()
	{	
				

		while (m_Running)
		{
			//glClearColor(1, 0, 1, 1);
			renderer.Clear();

			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			void* positions;
			VertexArray va;
			VertexBuffer vb(positions, 4 * 2 * sizeof(float));

			VertexBufferLayout layout;
			layout.Push<float>(2);
			va.AddBuffer(vb, layout);

			IndexBuffer ib(indices, 6);

			//shader.Bind();
			//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

			va.Unbind();
			vb.Unbind();
			ib.Unbind();
			//shader.Unbind();

			//VertexArray vb(positions, 4 * 2 * sizeof(float));
			
			//renderer.Draw(va, ib, shader);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();			
			
			
			
		}

		
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		

		return true;
	}

}
