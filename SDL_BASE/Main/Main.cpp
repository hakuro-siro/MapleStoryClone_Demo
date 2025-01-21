// ----------------------------------------------------------------
// SDL BASE - 1
// ----------------------------------------------------------------
#define SDL_MAIN_HANDLED

#include "System/Process/Processer.h"

int main(int argc, char** argv)
{
	Processer* processer = &Singleton<Processer>::GetInstance();

	bool success = processer->Initialize();
	if (success)
	{
		processer->Update(0);
	}
	processer->Finalize();
	return 0;
}
