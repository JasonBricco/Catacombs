#include "CppUnitTest.h"
#include "Stdafx.h"
#include "Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(Utils)
{
public:
		
	TEST_METHOD(TestTilePos)
	{
		Vector2f p(4.5f, 3.5f);
		Vector2i result = TilePos(p);

		Assert::AreEqual(result.x, 4);
		Assert::AreEqual(result.y, 3);

		Vector2f p2(4.1f, 3.9f);
		Vector2i result2 = TilePos(p2);

		Assert::AreEqual(result.x, 4);
		Assert::AreEqual(result.y, 3);
	}
};
