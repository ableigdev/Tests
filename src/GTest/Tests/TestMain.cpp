#include <gtest\gtest.h>
#include <vector>
#include <list>
#include <set>


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

