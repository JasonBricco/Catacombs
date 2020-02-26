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
		float Test = 2;
		float result = 4;
		Assert::AreEqual(Square(Test), result);
		Test = 0;
		result = 0;
		Assert::AreEqual(Square(Test), result);
	}

	TEST_METHOD(TestMul)
	{
		Vector2f TestA(1.0f, 1.0f);
		Vector2f TestB(5.0f, 3.0f);
		Vector2f result1 = Mul(TestA, TestB);

		Assert::AreEqual(result1.x, 5.0f);
		Assert::AreEqual(result1.y, 3.0f);

		Vector2f TestC(0.0f, 2.0f);
		Vector2f TestD(100.0f, 5.0f);
		Vector2f result2 = Mul(TestC, TestD);

		Assert::AreEqual(result2.x, 0.0f);
		Assert::AreEqual(result2.y, 10.0f);

		Vector2f TestE(0.5f, 1.5f);
		Vector2f TestF(5.0f, 3.0f);
		Vector2f result3 = Mul(TestE, TestF);

		Assert::AreEqual(result3.x, 2.5f);
		Assert::AreEqual(result3.y, 4.5f);
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
