#include "main.hpp"

int main(int argc, char* argv[])
{
	bsEngine engine;

	engine.init();	
	
	engine.run();	

	engine.cleanup();	

	return 0;
}