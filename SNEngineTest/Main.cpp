#pragma comment(lib, "SNEngine.lib")

#define TEST_ENTITIY_COMPONENTS 1
#include "TestEntityComponents.h"

#if TEST_ENTITY_COMPONENTS
#include "TestEntityComponents.h"
#endif //  TEST_ENTITY_COMPONENTS



int main()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	engine_test test{};

	if (test.initialize())
	{
		test.run();
	}
	test.shutdown();
}