#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace engine
{
	class Window
	{
	public:
		static Window& getInstance();
		std::shared_ptr<sf::RenderWindow> getWindow() const;
		void setWindow(std::shared_ptr<sf::RenderWindow> window);
	private:
		std::shared_ptr<sf::RenderWindow> m_window;
		Window() = default;
	};
}
