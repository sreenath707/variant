#pragma once

extern Variant::Application* Variant::CreateApplication();

//--------log macros-----------------
#define VR_client_warn(...) Variant::log::getClientLogger()->warn(__VA_ARGS__) 
#define VR_client_info(...) Variant::log::getClientLogger()->info(__VA_ARGS__) 
#define VR_client_error(...) Variant::log::getClientLogger()->error(__VA_ARGS__) 
		   
#define VR_core_warn(...)  Variant::log::getCoreLogger()->warn(__VA_ARGS__) 
#define VR_core_info(...)  Variant::log::getCoreLogger()->info(__VA_ARGS__) 
#define VR_core_error(...) Variant::log::getCoreLogger()->error(__VA_ARGS__) 
		   
 
int main()
{
	Variant::log::init();
	VR_client_error("This is error!!");
	VR_core_warn("This is warn!!");
	VR_core_info("This is info!!");

}
