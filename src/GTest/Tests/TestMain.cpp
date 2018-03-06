#include <gtest\gtest.h>
#include <vector>
#include <list>
#include <set>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>


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

	bool func(int value)
	{
		return value % 2 == 0;
	}

	bool compareElements(int lhs, int rhs)
	{
		return lhs < rhs;
	}

	bool compareElements2(int value)
	{
		return value > 3 && value < 7;
	}

	std::string::size_type sumLengthString(std::string::size_type sum, const std::string& str)
	{
		return sum + str.size();
	}

	struct AdaptFunctor : std::unary_function<int, bool>
	{
		bool operator()(int value) const
		{
			return value % 2 == 0;
		}
	};

	class TestClass
	{
	public:
		TestClass()
			: value(0),
			  statusObject(true)
		{

		}
		~TestClass()
		{

		}

		void testObject()
		{
			if (value == 0)
				statusObject = false;
		}

		bool getStatus() const
		{
			return statusObject;
		}

	private:
		int value;
		bool statusObject;
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

TEST(GetValueMap, Test)
{
	std::map<int, std::string> m;

	m.insert(std::map<int, std::string>::value_type(4, "test"));
	m.insert(std::map<int, std::string>::value_type(3, "test2"));
	m.insert(std::map<int, std::string>::value_type(7, "test4"));

	EXPECT_EQ(m[3], "test2");
	EXPECT_EQ(m[4], "test");
	EXPECT_EQ(m[7], "test4");
}

TEST(AdvanceDistance, Test)
{
	std::vector<int> v = { 2, 4, 6, 8 };
	std::vector<int>::iterator iter = v.begin();
	std::vector<int>::const_iterator constIter = v.begin() + v.size() / 2;

	EXPECT_EQ(*iter, 2);
	EXPECT_EQ(*constIter, 6);

	std::advance(iter, std::distance<std::vector<int>::const_iterator>(iter, constIter));

	EXPECT_EQ(*iter, 6);
}

TEST(BaseFunction, Test)
{
	std::vector<int> v = { 4, 1, 8, 3, 7 };
	std::vector<int>::iterator iter = v.begin() + 3;
	std::vector<int>::reverse_iterator reverseIter = v.rbegin() + 3;

	EXPECT_EQ(*iter, 3);
	EXPECT_EQ(*reverseIter, 1);
	EXPECT_EQ(*(--reverseIter).base(), 3);
}

TEST(TransformVector, Test)
{
	std::vector<int> v = { 4, 7, 2, 5, 9 };
	std::vector<int> result;
	std::vector<int> expectedResult = { 1, 0, 1, 0, 0 };

	std::transform(v.begin(), v.end(), std::back_inserter(result), func);

	EXPECT_EQ(result, expectedResult);
}

TEST(PartialSort, Test)
{
	std::vector<int> v = { 4, 9, 12, 5, 8, 3, 9, 5, 1, 0, 7 };
	std::vector<int> expectedResult = { 0, 1, 3, 4 };

	std::partial_sort(v.begin(), v.begin() + 4, v.end(), compareElements);

	std::vector<int> v2(v.begin(), v.begin() + 4);

	EXPECT_EQ(v2, expectedResult);
}

TEST(NTHElement, Test)
{
	std::vector<int> v = { 4, 9, 12, 5, 8, 3, 9, 5, 1, 0, 7 };
	std::vector<int> expectedResult = { 0, 1, 3, 4 };
	std::vector<int> expectedResult2 = { 0, 1, 3, 4, 5, 5, 7, 8, 9, 9, 12 };

	std::nth_element(v.begin(), v.begin() + 4, v.end(), compareElements);

	std::vector<int> v2(v.begin(), v.begin() + 4);

	EXPECT_EQ(v2, expectedResult);
	EXPECT_EQ(v, expectedResult2);
}

TEST(Partition, Test)
{
	std::vector<int> v = { 4, 9, 12, 5, 8, 3, 9, 5, 1, 0, 7 };
	std::vector<int> expectedResult = { 4, 5, 5 };

	std::partition(v.begin(), v.end(), compareElements2);

	std::vector<int> v2(v.begin(), v.begin() + 3);

	EXPECT_EQ(v2, expectedResult);
}

TEST(Accumulate, Test)
{
	std::vector<double> v = { 0.033, 2.3, 6.1, 0.0034, 0.05, 0.043 };
	double expectedResult = 8.5293999999999992;
	double sum = 0.0;

	sum = std::accumulate(v.begin(), v.end(), 0.0);

	EXPECT_EQ(sum, expectedResult);
}

TEST(Accumulate, Test2)
{
	std::vector<std::string> v = { "test1", "test2", "test3453", "do" };
	std::string::size_type expectedLength = 20;
	
	std::string::size_type actualLength = std::accumulate(v.begin(), v.end(), 0, sumLengthString);

	EXPECT_EQ(expectedLength, actualLength);
}

TEST(FunctorAdapt, Test)
{
	std::vector<int> v = { 1, 5, 8, 3, 4, 2 };
	std::vector<int>::iterator expect = v.begin();
	std::vector<int>::iterator actual = std::find_if(v.begin(), v.end(), std::not1(AdaptFunctor()));

	EXPECT_EQ(expect, actual);
}

TEST(MemFun, Test)
{
	TestClass testObj;
	std::vector<TestClass*> v;
	v.push_back(new TestClass);
	v.push_back(new TestClass);
	v.push_back(new TestClass);

	std::vector<TestClass*> expect;
	expect.push_back(new TestClass);
	expect.push_back(new TestClass);
	expect.push_back(new TestClass);

	expect[0]->testObject();
	expect[1]->testObject();
	expect[2]->testObject();

	std::for_each(v.begin(), v.end(), std::mem_fun(&TestClass::testObject));

	EXPECT_EQ(expect[0]->getStatus(), v[0]->getStatus());
	EXPECT_EQ(expect[1]->getStatus(), v[1]->getStatus());
	EXPECT_EQ(expect[2]->getStatus(), v[2]->getStatus());

	for (int i = 0; i < expect.size(); ++i)
		delete expect[i];

	for (int i = 0; i < v.size(); ++i)
		delete v[i];
}


