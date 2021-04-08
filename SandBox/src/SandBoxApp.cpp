#include "variant.h"

class _declspec(dllimport) Variant::Application;

	class SandBox : public Variant::Application
	{ 
	public:
		SandBox()
		{

		}
		~SandBox()
		{

		}
	};


Variant::Application* Variant::CreateApplication()
{
	return new SandBox();
}

