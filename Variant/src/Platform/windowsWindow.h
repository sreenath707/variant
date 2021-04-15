#pragma once
#include "Variant/Window.h"
#include "Variant/core.h"
namespace Variant {

	struct windowProps
	{
		windowProps(unsigned int width = 1280, unsigned int height = 720, std::string name = "Variant")
			:width(width), height(height), name(name) {}
		unsigned int width, height;
		std::string name;
	};

	class windowsWindow : public Window
	{
	  public:
		  windowsWindow();
		  ~windowsWindow();

		  unsigned int getwidth()override;
		  unsigned int getheight()override;

		  
		  void init(windowProps& props = windowProps(1280, 720, "Variant"));
		  void update()override;
	};
}
