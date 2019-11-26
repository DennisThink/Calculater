/*
 *    Copyright (c) 2018 Dennis Mi
 *    email: dennismi1024@gmail.com
 *    Blog : https://www.dennisthink.com/
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * 
 */

#include <iostream>
#include "parse.h"
#include "token_number.h"
#include "add_operator.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
namespace calculater {

TEST_CASE("PARSE_NUMBER") {
	SUBCASE("0") {
		TokenNumber number = TokenNumber("0");
		CHECK(0 == number.getValue());
	}
	
	SUBCASE("1") {
		TokenNumber number = TokenNumber("1");
		CHECK(1 == number.getValue());
	}
	
	SUBCASE("-1") {
		TokenNumber number = TokenNumber("-1");
		CHECK(-1 == number.getValue());
	}
	
	SUBCASE("0.0") {
		TokenNumber number = TokenNumber("0.0");
		CHECK(0.0 == number.getValue());
	}
}


TEST_CASE("ParseOperator") {
	SUBCASE("AddOperator") {
		AddOperator opera = AddOperator();
		TokenNumber num1 = TokenNumber(1);
		TokenNumber num2 = TokenNumber(2);
		CHECK(3 == opera.compute(num1,num2).getValue());
	}
}

TEST_CASE("Add") {
	SUBCASE("SimpleAdd") {
		std::string strExpress="2+2";
		TokenNumber numResult = TokenNumber(4);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}
	SUBCASE("ManyAdd") {
		std::string strExpress="2+2+4+6+8";
		TokenNumber numResult = TokenNumber(22);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}	
}

TEST_CASE("Sub") {
	SUBCASE("SimpleSub") {
		std::string strExpress="4-2";
		TokenNumber numResult = TokenNumber(2);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}
	SUBCASE("ManySub") {
		std::string strExpress="22-2-4-2";
		TokenNumber numResult = TokenNumber(14);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}	
	SUBCASE("NegativeSub") {
		std::string strExpress="2-4";
		TokenNumber numResult = TokenNumber(-2);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}	
}

TEST_CASE("Mul") {
	SUBCASE("SimpleMul") {
		std::string strExpress="4*2";
		TokenNumber numResult = TokenNumber(8);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}
	SUBCASE("ManyMul") {
		std::string strExpress="2*3*4*5";
		TokenNumber numResult = TokenNumber(120);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}	
	SUBCASE("NegativeMul") {
		std::string strExpress="2*(0-4)";
		TokenNumber numResult = TokenNumber(-8);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}	
}
TEST_CASE("NegativeMul") {
		std::string strExpress="2*(0-4)";
		TokenNumber numResult = TokenNumber(-8);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
}

TEST_CASE("MixOperator") {
	SUBCASE("AddSub") {
		std::string strExpress="2+3-4";
		TokenNumber numResult = TokenNumber(1);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}

	SUBCASE("AddMul") {
		std::string strExpress="2+3*4";
		TokenNumber numResult = TokenNumber(14);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}
	
	SUBCASE("AddDiv") {
		std::string strExpress="2+8/4";
		TokenNumber numResult = TokenNumber(4);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}
	
	SUBCASE("AddDiv") {
		std::string strExpress="8/2+8";
		TokenNumber numResult = TokenNumber(12);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}
	
	SUBCASE("SubMul") {
		std::string strExpress="2-3*4";
		TokenNumber numResult = TokenNumber(-10);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		auto calcResult = dynamic_cast<TokenNumber*>(result.get());
		CHECK(nullptr != calcResult);
		CHECK(numResult.toString() == calcResult->toString());
	}			
}

	
TEST_CASE("CalcuMulAndAdd") {
	std::string strExpress="2+2*3";
	TokenNumber numResult = TokenNumber(8);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	CHECK(nullptr != calcResult);
	CHECK(numResult.toString() == calcResult->toString());
}

TEST_CASE("Negative") {
	std::string strExpress="2+(0-3)";
	TokenNumber numResult = TokenNumber(-1);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	CHECK(nullptr != calcResult);
	CHECK(numResult.toString() == calcResult->toString());
}

TEST_CASE("FloatTest") {
	std::string strExpress="2.2+2.2";
	TokenNumber numResult = TokenNumber(4.4);
	auto tokens = CParser::Parse(strExpress);
	auto result = CParser::Calculate(tokens);
	auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	CHECK(nullptr != calcResult);
	CHECK(numResult.toString() == calcResult->toString());
}

}