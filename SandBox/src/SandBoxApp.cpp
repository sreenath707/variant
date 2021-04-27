#include "..\..\Variant\src\Variant\Application.h"
#include <variant.h>


class SandBox : public Variant::Application
{
public:
	SandBox()
	{
		pushOverlay(new Variant::imguiLayer);
		VR_client_info("Imgui layer pushed!");
	}
	~SandBox()
	{

	}
};


Variant::Application* Variant::CreateApplication()
{
	return new SandBox();
}


