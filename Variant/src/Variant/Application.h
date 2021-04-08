#pragma once

namespace Variant {

	class  __declspec(dllexport) Application
	{
	public:
		Application();

		virtual ~Application();

		void run();

	};

	Application* CreateApplication();


}
