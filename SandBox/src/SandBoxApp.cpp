#include "..\..\Variant\src\Variant\core\Application.h"
#include <variant.h>


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


