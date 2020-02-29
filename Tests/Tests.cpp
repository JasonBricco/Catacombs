#include "CppUnitTest.h"
#include "Stdafx.h"
#include "Utils.h"
#include "Assets.h"
#include "Collision.cpp"

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

TEST_CLASS(TestCollision)
{
	TEST_METHOD(TestAABBCreate)
	{
		AABB a = AABBFromCorner(Vector2f(0.0f, 0.0f), Vector2f(5.0f, 5.0f));

		Assert::IsTrue(a.center == Vector2f(2.5f, 2.5f));
		Assert::IsTrue(a.radius == Vector2f(2.5f, 2.5f));

		AABB b = AABBFromMinMax(Vector2f(0.0f, 0.0f), Vector2f(5.0f, 5.0f));

		Assert::IsTrue(a.center == Vector2f(2.5f, 2.5f));
		Assert::IsTrue(a.radius == Vector2f(2.5f, 2.5f));

		AABB c = AABBFromCenter(Vector2f(2.5f, 2.5f), Vector2f(2.5f, 2.5f));

		Assert::IsTrue(a.center == Vector2f(2.5f, 2.5f));
		Assert::IsTrue(a.radius == Vector2f(2.5f, 2.5f));

		AABB d = AABBFromBottomCenter(Vector2f(2.5f, 0.0f), Vector2f(5.0f, 5.0f));

		Assert::IsTrue(a.center == Vector2f(2.5f, 2.5f));
		Assert::IsTrue(a.radius == Vector2f(2.5f, 2.5f));
	}

	TEST_METHOD(TestAABBOverlap)
	{
		AABB a = AABBFromMinMax(Vector2f(0.0f, 0.0f), Vector2(5.0f, 5.0f));

		AABB b = AABBFromMinMax(Vector2f(0.0f, 0.0f), Vector2f(5.0f, 5.0f));
		Assert::IsTrue(TestOverlap(a, b));

		b = AABBFromMinMax(Vector2f(2.5f, 2.5f), Vector2f(10.0f, 10.0f));
		Assert::IsTrue(TestOverlap(a, b));

		b = AABBFromMinMax(Vector2f(6.0f, 6.0f), Vector2f(10.0f, 10.0f));
		Assert::IsTrue(!TestOverlap(a, b));

		b = AABBFromMinMax(Vector2f(5.0f, 5.0f), Vector2f(7.5f, 7.5f));
		Assert::IsTrue(TestOverlap(a, b));

		b = AABBFromMinMax(Vector2f(-5.0f, -5.0f), Vector2f(0.0f, 0.0f));
		Assert::IsTrue(TestOverlap(a, b));
	}

	TEST_METHOD(TestTestWall)
	{
		Vector2f delta = Vector2f(5.0f, 2.0f);
		Vector2f p = Vector2f(0.0f, 0.0f);
		float wallP = 2.0f;
		Vector2f wMin = Vector2f(2.0f, 0.0f);
		Vector2f wMax = Vector2f(2.0f, 6.0f);

		float tMin = 1.0f;
		Assert::IsTrue(TestWall(delta, p, wallP, wMin, wMax, 0, 1, tMin));

		wallP = 6.0f;
		wMin = Vector2f(6.0f, 0.0f);
		wMax = Vector2f(6.0f, 6.0f);

		Assert::IsTrue(!TestWall(delta, p, wallP, wMin, wMax, 0, 1, tMin));
	}
};
