#include "Sandbox.h"

namespace gameSandbox {
	std::vector<float> vertices =
	{
		  0.0f,	   0.0f,	 0.0f, 0.0f,
		200.0f,	   0.0f,	 1.0f, 0.0f,
		200.0f,	 200.0f,	 1.0f, 1.0f,
		  0.0f,	 200.0f,	 0.0f, 1.0f
	};


	std::vector<GLuint> indices =
	{
		0, 1, 2,
		2, 3, 0
	};

	Sandbox::Sandbox()
		:tr_X(0.0f), tr_Y(0.0f), WindowSize(1280, 720), m_proj(glm::ortho(0.0f, WindowSize.x, 0.0f, WindowSize.y, -1.0f, 1.0f)), m_view(glm::translate(glm::mat4(1.0f), glm::vec3(tr_X, tr_Y, 0.0f))), m_model(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))), windowShouldClose(0)
	{
		if (!glfwInit()) { glfwTerminate(); }
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		window = glfwCreateWindow(WindowSize.x, WindowSize.y, "Pathways", NULL, NULL);
		if (!window) { glfwTerminate(); }
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK) { std::cout << "OPENGL GLEW ERROR!!"; }

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();


		m_MVP = m_proj * m_view * m_model;

		___(m_layout = std::make_unique<VertexBufferLayout>());
		___(m_layout->Push<float>(2));
		___(m_layout->Push<float>(2));
		___(m_layout->i_Push(1));
		___(m_texture = std::make_unique<Texture>("res/textures/black.jpg"));
		___(m_shader = std::make_unique<Shader>("res/shaders/Shader.shader"));
		___(m_renderer = std::make_unique<Renderer>());
		___(m_vbo = std::make_unique<VertexBuffer>(&vertices[0], sizeof(vertices)));
		___(m_vao = std::make_unique<VertexArray>());
		___(m_ibo = std::make_unique<IndexBuffer>(&indices[0], m_layout->GetCount()));
		___(m_vao->AddBuffer(*m_vbo, *m_layout));
		___(m_ibo->Bind());
		___(m_vbo->Bind());
		___(m_vao->Bind());
		___(m_shader->Bind());
		___(m_texture->Bind());

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}


	Sandbox::~Sandbox()
	{
		m_ibo->Unbind();
		m_vbo->Unbind();
		m_vao->Unbind();
		m_shader->Unbind();
		m_texture->Unbind();

		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}

	void Sandbox::OnUpdate()
	{
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Sandbox::OnRender()
	{
		m_model = glm::translate(glm::mat4(1.0f), glm::vec3(tr_X, tr_Y, 0));
		m_MVP = m_proj * m_view * m_model;
		___(m_shader->Bind());
		___(m_shader->SetUniform1i("u_Texture", 0));
		___(m_shader->SetUniformMat4f("u_MVP", m_MVP));
		m_renderer->Draw(*m_vao, *m_ibo, *m_shader);
	}

	void Sandbox::OnImGuiRender()
	{
		ImGui_ImplGlfwGL3_NewFrame();

		ImGui::SliderFloat("Translation x", &tr_X, -200.0f, 1480.0f);
		ImGui::SliderFloat("Translation y", &tr_Y, -200.0f, 920.0f);
		if (ImGui::Button("Drag"))
			did_click_button = !did_click_button;

		if (did_click_button)
		{
			tr_X = ImGui::GetMousePos().x - 100.0f; tr_Y = WindowSize.y - ImGui::GetMousePos().y - 100.0f;
		}

		if (ImGui::IsMouseClicked(0))
			did_click_button = !did_click_button;

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Sandbox::OnEnd()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}