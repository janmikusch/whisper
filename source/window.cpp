#include "stdafx.h"
#include "window.h"


namespace engine
{
	Window& Window::getInstance()
	{
		static Window m_instance;
		return m_instance;
	}

	std::shared_ptr<sf::RenderWindow> Window::getWindow() const
	{
		return m_window;
	}

	void Window::setWindow(std::shared_ptr<sf::RenderWindow> window)
	{
		m_window = window;
	}

}
