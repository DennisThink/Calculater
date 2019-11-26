// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
 
 /*
  * File : parse.cpp
  * Date : 2018-04-11
  * Purpose : this file is for parse eval string to tokens and calculate the result 
  * 
  */
 
#include "parse.h"
#include "add_operator.h"
#include "token_number.h"
#include <map>
#include <ctype.h>
#include <iostream>
#include "brackets_operator.h"
#include "sub_operator.h"
#include "mul_operator.h"
#include "div_operator.h"
namespace calculater {
		
OperatorType StrToOperator(const char ch) noexcept {
	switch(ch)
	{
		case '+':
		{
			return OperatorType::ADD_OPERATOR;
		}break;
		case '-':
		{
			return OperatorType::SUB_OPERATOR;
		}break;
		case '*':
		{
			return OperatorType::MUL_OPERATOR;
		}break;
		case '/':
		{
			return OperatorType::DIV_OPERATOR;
		}break;
		case '(':
		{
			return OperatorType::LEFT_BRACKETS;
		}break;
		case ')':
		{
			return OperatorType::RIGHT_BRACKETS;
		}break;
		default:
		{
			return OperatorType::UNKNOWN_OPERATOR;
		}
	}
	return OperatorType::UNKNOWN_OPERATOR;
}

std::string OperatorToStr(OperatorType oper) noexcept {
	switch(oper)
	{
		case OperatorType::ADD_OPERATOR:
		{
			return "+";
		}break;
		case OperatorType::SUB_OPERATOR:
		{
			return "-";
		}break;
		case OperatorType::MUL_OPERATOR:
		{
			return "*";
		}break;
		case OperatorType::DIV_OPERATOR:
		{
			return "/";
		}break;
		case OperatorType::LEFT_BRACKETS:
		{
			return "(";
		}break;
		case OperatorType::RIGHT_BRACKETS:
		{
			return ")";
		}break;
		default:
		{
			return "#";
		}break;
	}
}

std::shared_ptr<TokenOperator> OperatorTypeToToken(const OperatorType type) 
{
	switch(type)
	{
		case OperatorType::ADD_OPERATOR:
		{
			return std::make_shared<AddOperator>();
		}break;
		case OperatorType::SUB_OPERATOR:
		{
			return std::make_shared<SubOperator>();
		}break;
		case OperatorType::MUL_OPERATOR:
		{
			return std::make_shared<MulOperator>();
		}break;
		case OperatorType::DIV_OPERATOR:
		{
			return std::make_shared<DivOperator>();
		}break;
		case OperatorType::LEFT_BRACKETS:
		{
			return std::make_shared<LeftBrackets>();
		}break;
		case OperatorType::RIGHT_BRACKETS:
		{
			return std::make_shared<RightBrackets>();
		}break;
		default:
		{
			return nullptr;
		}
	}
}


TokenPtrVec CParser::Parse(const std::string& str)
{
	TokenPtrVec result;
	auto count = str.size();

	std::string strNumber;
	std::string strOperator;
	result.push_back(std::make_shared<LeftBrackets>());
	for(decltype(count) index=0; index < count ; index ++)
	{
		if(isalnum(str[index]) || str[index] == '.')
		{
			if(strOperator.length() > 0)
			{
				for(std::size_t i = 0 ; i < strOperator.length() ; i++)
				{
					auto operaType = StrToOperator(strOperator[i]);
					auto token = OperatorTypeToToken(operaType);
					if(nullptr != token)
					{
						result.push_back(token);
					}
				}
				strOperator.clear();
			}
			strNumber += str[index];
		}
		else
		{
			if(strNumber.length() > 0 )
			{
				auto number = std::make_shared<TokenNumber>(strNumber);
				result.push_back(number);
				strNumber.clear();
			}
			strOperator += str[index];
		}
	}
	
	if(strOperator.length() > 0)
	{
		auto operLength = strOperator.length();
		for(decltype(operLength) i = 0 ; i < operLength ; i++)
		{
			auto operaType = StrToOperator(strOperator[i]);
			auto token = OperatorTypeToToken(operaType);
			if(nullptr != token)
			{
				result.push_back(token);
			}
		}
		strOperator.clear();
	}
	if(strNumber.length() > 0 )
	{
		auto number = std::make_shared<TokenNumber>(strNumber);
		result.push_back(number);
		strNumber.clear();
	}
	
	result.push_back(std::make_shared<RightBrackets>());
	return result;
}

struct OperatorPriorityPair
{
	OperatorPriority left;
	OperatorPriority right;

	OperatorPriorityPair(OperatorPriority left,OperatorPriority right){this->left = left;this->right=right;}

	bool operator<(const OperatorPriorityPair& rhs) const  
    {
		if(this->left != rhs.left)
		{
			return this->left  < rhs.left;
		}
		if(this->right != rhs.right)
		{
			return this->right < rhs.right;
		}
		return false;
    }  
};

enum class CompareResult{
	ERROR,
	LEFT_HIGHER,
	EQUAL,
	RIGHT_HIGHER,
};

const static std::map<OperatorPriorityPair,CompareResult> operatorPriorityMap=
{
	{{OperatorPriority::ADD_LEVEL,OperatorPriority::ADD_LEVEL},CompareResult::LEFT_HIGHER}, 	// + > +
	{{OperatorPriority::ADD_LEVEL,OperatorPriority::MUL_LEVEL},CompareResult::RIGHT_HIGHER}, 	// + < *
	{{OperatorPriority::ADD_LEVEL,OperatorPriority::LEFT_BRACKETS_LEVEL},CompareResult::RIGHT_HIGHER}, // + < (
	{{OperatorPriority::ADD_LEVEL,OperatorPriority::RIGHT_BRACKETS_LEVEL},CompareResult::LEFT_HIGHER}, // + > )
	
	
	{{OperatorPriority::MUL_LEVEL,OperatorPriority::ADD_LEVEL},CompareResult::LEFT_HIGHER}, 	// * > +
	{{OperatorPriority::MUL_LEVEL,OperatorPriority::MUL_LEVEL},CompareResult::LEFT_HIGHER}, 	// * > *
	{{OperatorPriority::MUL_LEVEL,OperatorPriority::LEFT_BRACKETS_LEVEL},CompareResult::RIGHT_HIGHER}, // * < (
	{{OperatorPriority::MUL_LEVEL,OperatorPriority::RIGHT_BRACKETS_LEVEL},CompareResult::LEFT_HIGHER}, // * > )
	
	
	{{OperatorPriority::LEFT_BRACKETS_LEVEL,OperatorPriority::ADD_LEVEL},CompareResult::RIGHT_HIGHER}, 	// / > +
	{{OperatorPriority::LEFT_BRACKETS_LEVEL,OperatorPriority::MUL_LEVEL},CompareResult::RIGHT_HIGHER}, 	// / > *
	{{OperatorPriority::LEFT_BRACKETS_LEVEL,OperatorPriority::LEFT_BRACKETS_LEVEL},CompareResult::RIGHT_HIGHER}, // / < (
	{{OperatorPriority::LEFT_BRACKETS_LEVEL,OperatorPriority::RIGHT_BRACKETS_LEVEL},CompareResult::EQUAL}, // / > )
	
	{{OperatorPriority::RIGHT_BRACKETS_LEVEL,OperatorPriority::ADD_LEVEL},CompareResult::LEFT_HIGHER}, 	// / > +
	{{OperatorPriority::RIGHT_BRACKETS_LEVEL,OperatorPriority::MUL_LEVEL},CompareResult::LEFT_HIGHER}, 	// / > *
	{{OperatorPriority::RIGHT_BRACKETS_LEVEL,OperatorPriority::LEFT_BRACKETS_LEVEL},CompareResult::ERROR},   // / < (
	{{OperatorPriority::RIGHT_BRACKETS_LEVEL,OperatorPriority::RIGHT_BRACKETS_LEVEL},CompareResult::LEFT_HIGHER},   // / > )	
};

TokenPtrVec SimpleTokens(const TokenPtrVec& tokens)
{
	TokenPtrVec results;
	auto nCount = tokens.size();
	if(nCount >= 3)
	{
		for(std::size_t i = 1 ; i < nCount - 1 ; i++)
		{
			if(TokenType::NUMBER == tokens[i]->getTokenType() )
			{
				auto left = dynamic_cast<TokenOperator*>(tokens[i-1].get());
				auto right = dynamic_cast<TokenOperator*>(tokens[i+1].get());
				if( (left && OperatorType::LEFT_BRACKETS == left->getOperatorType() ) &&
				    (right && OperatorType::RIGHT_BRACKETS == right->getOperatorType() ) )
				{
					for(std::size_t index = 0 ; index < i-1 ; index++)
					{
						results.push_back(tokens[index]);
					}
					
					results.push_back(tokens[i]);
					for(std::size_t index = i+2 ; index < nCount ; index++)
					{
						results.push_back(tokens[index]);
					}
					return results;
				}
			}
		}
	}
	return tokens;
}


TokenPtr CParser::Calculate(TokenPtrVec tokens)
{
	do
	{
		auto resultTokens = SimpleTokens(tokens);
		if(resultTokens.size() == tokens.size())
		{
			break;
		}
		else
		{
			tokens=std::move(resultTokens);
		}
	}while(true);
	
	if( tokens.size() ==1)
	{
		return tokens[0];
	}
	else
	{
		int arrayIndex[5]={0};
		bool notComputed = true;
		TokenPtrVec newTokens;
		TokenOperator * left = nullptr;
		TokenOperator * medium = nullptr;
		TokenOperator * right = nullptr;
		while(tokens.size() >= 5 && notComputed)
		{
			right = dynamic_cast<TokenOperator*>(tokens[arrayIndex[4]].get());
			while( !left || !medium || !right)
			{
				if(right)
				{
					left=medium;
					arrayIndex[0]=arrayIndex[2];
						
					medium = right;
					arrayIndex[2]=arrayIndex[4];
				}
				arrayIndex[4]++;
				right = dynamic_cast<TokenOperator*>(tokens[arrayIndex[4]].get());	
			}
			if(true)
			{
				//std::cout<<"Get Operator"<<std::endl;
				OperatorPriorityPair leftCompareKey(left->getOperatorPriority(),medium->getOperatorPriority());
				OperatorPriorityPair rightCompareKey(medium->getOperatorPriority(),right->getOperatorPriority());
				//std::cout<<"Before Left:"<<leftCompareKey.toString()<<std::endl;
				//std::cout<<"Before Right:"<<rightCompareKey.toString()<<std::endl;
				auto leftResult = operatorPriorityMap.find(leftCompareKey);
				auto rightResult = operatorPriorityMap.find(rightCompareKey);
				
				if(leftResult != operatorPriorityMap.end() && rightResult != operatorPriorityMap.end())
				{
					//std::cout<<"LEFT: "<<leftResult->first.toString()<<" "<<static_cast<int>(leftResult->second)<<std::endl;
					//std::cout<<"RIGHT: "<<rightResult->first.toString() <<" "<<static_cast<int>(rightResult->second)<<std::endl;
					if(leftResult->second == CompareResult::RIGHT_HIGHER && rightResult->second == CompareResult::LEFT_HIGHER)
					{
						auto lhs = dynamic_cast<TokenNumber*>((tokens[arrayIndex[2]-1]).get());
						auto rhs = dynamic_cast<TokenNumber*>((tokens[arrayIndex[4]-1]).get());
						if(rhs&&lhs)
						{
							TokenNumber result = medium->compute(*lhs,*rhs);
							//std::cout<<lhs->toString() << medium->toString() << rhs->toString() << "=" <<result.toString()<<std::endl;
							
							for(int i = 0 ; i < arrayIndex[2]-1 ; i++)
							{
								newTokens.push_back(tokens[i]);
							}
							
							newTokens.push_back(std::make_shared<TokenNumber>(result.getValue()));
							for(std::size_t i = arrayIndex[4] ; i < tokens.size() ; i++)
							{
								newTokens.push_back(tokens[i]);
							}
							notComputed = false;
						}
					}
					else
					{
						left = medium;
						arrayIndex[0] = arrayIndex[2];
						
						medium = right;
						arrayIndex[2] = arrayIndex[4];
						
						arrayIndex[4]++;
						right = dynamic_cast<TokenOperator*>(tokens[arrayIndex[4]].get());
						
						//std::cout<<"Left "<<static_cast<int>(leftResult->second) <<"  Right "<< static_cast<int>(rightResult->second)<<std::endl;
					}
				}
				else
				{
					
				}
			}
		}
		return Calculate(newTokens);
	}
	return std::make_shared<TokenNumber>(0);
}

}