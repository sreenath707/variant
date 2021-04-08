#pragma once

#include<iostream>
extern Variant::Application* Variant::CreateApplication();
 
int main(int argc , char** argv)
{
	auto* app = Variant::CreateApplication();
	app->run();
	std::cout << "app is running" << std::endl;
	delete app;
}
