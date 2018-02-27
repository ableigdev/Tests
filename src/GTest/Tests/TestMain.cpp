#include <gtest\gtest.h>
#include <vector>
#include <list>
#include <set>
#include <cstdlib>
#include <ctime>


namespace
{
	bool isWholeNumbers(int value)
	{
		return value % 2 == 0;
	}

	struct CompareString : public std::binary_function<std::string, std::string, bool>
	{
		// TODO: wriet operator()
	};

	struct TestStruct
	{
		int a;
		std::string b;
	};

	std::vector<TestStruct> getFullVector()
	{
		std::srand(time(0));
		TestStruct test;
		std::vector<TestStruct> temp;
		temp.reserve(5);

		for (int i = 0; i < 5; ++i)
		{
			if (i % 2 == 0)
				test.a = 4 + rand() % 3;
			else
				test.a = 5;
			
			test.b = "test";
			temp.push_back(test);
		}

		return temp;
	}

	struct find_a : std::unary_function<TestStruct, bool>
	{
		bool operator()(const TestStruct& value)
		{
			return value.a == 5;
		}
	};
}

TEST(IntervalFunction, VectorInsert)
{
	const int size = 5;
	int data[size] = { 2, 5, 8, 9, 3 };
	std::vector<int> expectResult = { 2, 5, 8, 9, 3 };

	std::vector<int> vec;

	vec.insert(vec.begin(), data, data + size);

	EXPECT_EQ(vec.size(), expectResult.size());
	EXPECT_EQ(vec, expectResult);
}

TEST(IntervalFunction, VectorErase)
{
	std::vector<int> v = { 3, 5, 7, 8, 1 };

	v.erase(v.begin(), v.end());

	EXPECT_TRUE(v.empty());
}

TEST(IntervalFunction, VectorAssign)
{
	std::vector<int> expectResult = { 4, 4, 4 };
	std::vector<int> v;
	v.assign(3, 4);

	EXPECT_EQ(expectResult, v);
	EXPECT_EQ(expectResult.size(), v.size());
}

TEST(RemoveErase, Vector)
{
	std::vector<int> v = { 3, 5, 7, 8, 1 };
	std::vector<int> expectResult = { 3, 5, 8, 1 };

	v.erase(std::remove(v.begin(), v.end(), 7), v.end());

	EXPECT_EQ(expectResult, v);
	EXPECT_EQ(expectResult.size(), v.size());
}

TEST(RemoveErase, List)
{
	std::list<int> v = { 3, 5, 7, 8, 1 };
	std::list<int> expectResult = { 3, 5, 8, 1 };

	v.remove(7);

	EXPECT_EQ(expectResult, v);
	EXPECT_EQ(expectResult.size(), v.size());
}

TEST(RemoveErase, Set)
{
	std::set<int> v = { 3, 5, 7, 8, 1 };
	std::set<int> expectResult = { 3, 5, 8, 1 };

	v.erase(7);

	EXPECT_EQ(expectResult, v);
	EXPECT_EQ(expectResult.size(), v.size());
}

TEST(RemoveIf, Vector)
{
	std::vector<int> v = { 3, 5, 7, 8, 1 };
	std::vector<int> expectResult = { 3, 5, 7, 1 };

	v.erase(std::remove_if(v.begin(), v.end(), isWholeNumbers), v.end());

	EXPECT_EQ(expectResult, v);
	EXPECT_EQ(expectResult.size(), v.size());
}

TEST(RemoveIf, List)
{
	std::list<int> v = { 3, 5, 7, 8, 1 };
	std::list<int> expectResult = { 3, 5, 7, 1 };

	v.remove_if(isWholeNumbers);

	EXPECT_EQ(expectResult, v);
	EXPECT_EQ(expectResult.size(), v.size());
}

TEST(RemoveIf, Set)
{
	std::set<int> v = { 3, 5, 7, 8, 1 };
	std::set<int> expectResult = { 3, 5, 7, 1 };
	std::set<int> temp;

	std::remove_copy_if(v.begin(), v.end(), std::inserter(temp, temp.end()), isWholeNumbers);
	v.swap(temp);	

	EXPECT_EQ(expectResult, v);
	EXPECT_EQ(expectResult.size(), v.size());
}

TEST(SwapRemove, Vector)
{
	std::vector<int> v = { 3, 8, 1, 4 };

	v.erase(std::remove(v.begin(), v.end(), 1), v.end());

	EXPECT_EQ(v.capacity(), 4);

	std::vector<int>(v).swap(v);

	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v.capacity(), 3);
}

TEST(InsertInMiddleVector, Test)
{
	std::vector<int> first = { 1, 3, 5, 9, 2, 4 };
	std::vector<int> second = { 4, 8, 1 };
	std::vector<int> expectResult = { 1, 3, 5, 4, 8, 1, 9, 2, 4 };

	first.insert(first.begin() + first.size() / 2, second.begin(), second.end());

	EXPECT_EQ(first, expectResult);
	EXPECT_EQ(first.size(), expectResult.size());
}

TEST(InsertStrcutInVector, Test)
{
	std::vector<TestStruct> v = getFullVector();

	std::vector<TestStruct>::iterator it = std::find_if(v.begin(), v.end(), find_a());
	
	EXPECT_EQ(it->a, 5);
}

TEST(MapInsert, Test)
{
	std::map<int, std::string> m;
	std::map<int, std::string> expectResult = { { 4, "test" }, { 3, "test2" }, { 7, "test4"} };

	m.insert(std::map<int, std::string>::value_type(4, "test"));
	m.insert(std::map<int, std::string>::value_type(3, "test2"));
	m.insert(std::map<int, std::string>::value_type(7, "test4"));

	EXPECT_EQ(m, expectResult);
	EXPECT_EQ(m.size(), expectResult.size());
}

TEST(MapUpdate, Test)
{
	std::map<int, std::string> m;
	std::map<int, std::string> expectResult = { { 4, "test" }, { 3, "test6" }, { 7, "test111"} };

	m.insert(std::map<int, std::string>::value_type(4, "test"));
	m.insert(std::map<int, std::string>::value_type(3, "test2"));
	m.insert(std::map<int, std::string>::value_type(7, "test4"));

	m[3] = "test6";
	m[7] = "test111";

	EXPECT_EQ(m, expectResult);
	EXPECT_EQ(m.size(), expectResult.size());
}

TEST(AdvanceDistance, Test)
{
	std::vector<int> v;
	typedef std::vector<int>::iterator iter;
	typedef std::vector<int>::const_iterator constIter;

	constIter cIter;
	iter i;
	// TODO: coplete properies
}

