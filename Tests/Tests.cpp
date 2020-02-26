#include "CppUnitTest.h"
#include "Stdafx.h"
#include "Utils.h"
#include "Assets.h"

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

	TEST_METHOD(TestSquare)
	{
		Assert::AreEqual(Square(5.0f), 25.0f);
		Assert::AreEqual(Square(1.0f), 1.0f);
		Assert::AreEqual(Square(-1.0f), 1.0f);
	}

	TEST_METHOD(TestMul)
	{
		Vector2f a(2.0f, 2.0f);
		Vector2f b(3.0f, 3.0f);

		Vector2f c = Mul(a, b);

		Assert::AreEqual(c.x, 6.0f);
		Assert::AreEqual(c.y, 6.0f);
	}

	TEST_METHOD(TestRandomInRange)
	{
		for (int i = 0; i < 256; ++i)
		{
			int r = randomInRange(0, 10);
			Assert::IsTrue(r >= 0 && r <= 10);
		}
	}
};
