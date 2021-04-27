#pragma once

extern Variant::Application* Variant::CreateApplication();
 
int main()
{
	Variant::log::init();
	auto* app = Variant::CreateApplication();
	app->run();
	delete app;
}
