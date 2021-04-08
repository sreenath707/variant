#pragma once
#include "core.h"

namespace Variant {

	class VR_API Application
	{
	public:
		Application();

		virtual ~Application();

		void run();

	};

	Application* CreateApplication();


}
