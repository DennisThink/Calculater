#include "gtest/gtest.h"
#include "parse.h"
#include "token_number.h"
#include "add_operator.h"
using namespace calculater;
TEST(ParseNumber,MyTest){
	{
		TokenNumber number = TokenNumber("0");
		EXPECT_EQ(0.0,number.getValue());
	}

	{
		TokenNumber number = TokenNumber("1");
		EXPECT_EQ(1 , number.getValue());
	}
	
	{
		TokenNumber number = TokenNumber("-1");
		EXPECT_EQ(-1 , number.getValue());
	}
	
	{
		TokenNumber number = TokenNumber("0.0");
		EXPECT_EQ(0.0 , number.getValue());
	}
}



TEST(AddOperatorTest,FirstCase) 
{
	AddOperator opera = AddOperator();
	TokenNumber num1 = TokenNumber(1);
	TokenNumber num2 = TokenNumber(2);
	EXPECT_EQ(3 ,opera.compute(num1,num2).getValue());
}

TEST(AddOperatorTest,StringCase) {
	std::string strExpress="2+2";
	TokenNumber numResult = TokenNumber(4);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_FALSE(nullptr==calcResult);
	EXPECT_EQ(numResult.toString(), calcResult->toString());
}

TEST(AddOperatorTest,TooManyNumbers){
	std::string strExpress="2+2+4+6+8";
	TokenNumber numResult = TokenNumber(22);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_FALSE(nullptr == calcResult);
	EXPECT_EQ(numResult.toString(),calcResult->toString());
}

TEST(SubOperatorTest,SimpleSub) 
{
	std::string strExpress="4-2";
	TokenNumber numResult = TokenNumber(2);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_TRUE(nullptr != calcResult);
	EXPECT_TRUE(numResult.toString() == calcResult->toString());
}
TEST(SubOperatorTest,ManySub) 
{
	std::string strExpress="22-2-4-2";
	TokenNumber numResult = TokenNumber(14);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_TRUE(nullptr != calcResult);
	EXPECT_TRUE(numResult.toString() == calcResult->toString());
}	

TEST(SubOperatorTest,NegativeSub) 
{
	std::string strExpress="2-4";
	TokenNumber numResult = TokenNumber(-2);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_TRUE(nullptr != calcResult);
	EXPECT_TRUE(numResult.toString() == calcResult->toString());
}

TEST(Mul,SimpleMul) 
{
		std::string strExpress="4*2";
		TokenNumber numResult = TokenNumber(8);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		EXPECT_TRUE(nullptr != calcResult);
		EXPECT_TRUE(numResult.toString() == calcResult->toString());
	}
TEST(Mul,ManyMul) {
	std::string strExpress="2*3*4*5";
	TokenNumber numResult = TokenNumber(120);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_TRUE(nullptr != calcResult);
	EXPECT_TRUE(numResult.toString() == calcResult->toString());
}	
TEST(Mul,NegativeMul) {
	std::string strExpress="2*(0-4)";
	TokenNumber numResult = TokenNumber(-8);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_TRUE(nullptr != calcResult);
	EXPECT_TRUE(numResult.toString() == calcResult->toString());
}	



TEST(MixOperator,AddSub) {
		std::string strExpress="2+3-4";
		TokenNumber numResult = TokenNumber(1);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		EXPECT_TRUE(nullptr != calcResult);
		EXPECT_TRUE(numResult.toString() == calcResult->toString());
	}

	TEST(MixOperator,AddMul) {
		std::string strExpress="2+3*4";
		TokenNumber numResult = TokenNumber(14);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		EXPECT_TRUE(nullptr != calcResult);
		EXPECT_TRUE(numResult.toString() == calcResult->toString());
	}
	
	TEST(MixOperator,AddDiv) {
		std::string strExpress="2+8/4";
		TokenNumber numResult = TokenNumber(4);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		EXPECT_TRUE(nullptr != calcResult);
		EXPECT_TRUE(numResult.toString() == calcResult->toString());
	}
	
	TEST(MixOperator,AddDiv2) {
		std::string strExpress="8/2+8";
		TokenNumber numResult = TokenNumber(12);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		EXPECT_TRUE(nullptr != calcResult);
		EXPECT_TRUE(numResult.toString() == calcResult->toString());
	}
	
	TEST(MixOperator,SubMul) {
		std::string strExpress="2-3*4";
		TokenNumber numResult = TokenNumber(-10);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		EXPECT_TRUE(nullptr != calcResult);
		EXPECT_TRUE(numResult.toString() == calcResult->toString());
	}			


	
TEST(MixOperator,CalcuMulAndAdd)
{
	std::string strExpress="2+2*3";
	TokenNumber numResult = TokenNumber(8);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_TRUE(nullptr != calcResult);
	EXPECT_TRUE(numResult.toString() == calcResult->toString());
}

TEST(MixOperator,Negative) 
{
	std::string strExpress="2+(0-3)";
	TokenNumber numResult = TokenNumber(-1);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_TRUE(nullptr != calcResult);
	EXPECT_TRUE(numResult.toString() == calcResult->toString());
}

TEST(MixOperator,FloatTest) 
{
	std::string strExpress="2.2+2.2";
	TokenNumber numResult = TokenNumber(4.4);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	EXPECT_TRUE(nullptr != calcResult);
	EXPECT_TRUE(numResult.toString() == calcResult->toString());
}

int main(int argc,char * argv[])
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}