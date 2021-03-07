#pragma once

#include "Renderer.h"

#include "Abstraction/VertexBufferLayout.h"
#include "Abstraction/VertexBuffer.h"
#include "Abstraction/Texture.h"

#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
typedef glm::vec2 GLWindowSize;

namespace gameSandbox {

	class Sandbox 
	{
		bool did_click_button = 0;
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::mat4 m_model;

		glm::mat4 m_MVP;

		float tr_X;
		float tr_Y;

		std::unique_ptr<Texture> m_texture;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<VertexBuffer> m_vbo;
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<IndexBuffer> m_ibo;
		std::unique_ptr<VertexBufferLayout> m_layout;
	public:
		Sandbox();
		~Sandbox();

		void OnUpdate();
		void OnRender();
		void OnImGuiRender();
		void OnEnd();

		GLWindowSize WindowSize;
		GLFWwindow* window;
		bool windowShouldClose;
	};
}
