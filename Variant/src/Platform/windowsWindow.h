#pragma once
#include "Variant/core/Window.h"
#include "Variant/core/core.h"
#include "Variant/Renderer/GraphicsContext.h"
namespace Variant {
	
	GraphicsContext* m_context;

	struct windowProps
	{
		windowProps(unsigned int width = 1920, unsigned int height = 1080, std::string name = "Variant")
			:width(width), height(height), name(name) {}
		unsigned int width, height;
		std::string name;

	};

	class windowsWindow : public Window
	{
		struct windowData
		{
			std::string name;
			unsigned int width, height;
			windowCallFn callback;
			bool Vsync;
		};
		windowData m_data;
		void isVsync();
	  public:
		  windowsWindow();
		  ~windowsWindow();

		  unsigned int getwidth()override;
		  unsigned int getheight()override;
		  void setVsync(bool isOn);
		  void setEventCallBack(windowCallFn callback)override
		  {
			  m_data.callback = callback;
		  }

		  void init(windowProps& props = windowProps(1240,720));
		  void update()override;
	};
}
