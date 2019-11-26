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

#ifndef _MUL_OPERATOR_H_
#define _MUL_OPERATOR_H_
#include "token_operator.h"
namespace calculater {

class MulOperator:public TokenOperator
{
public:
	explicit MulOperator(){};
	virtual ~MulOperator(){}
	virtual OperatorType getOperatorType() override final{ return OperatorType::MUL_OPERATOR;}
	virtual OperatorPriority getOperatorPriority() override final { return OperatorPriority::MUL_LEVEL; }
	virtual TokenNumber compute(const TokenNumber& lhs,const TokenNumber& rhs) override final;
	virtual std::string toString() override final;
};

}
#endif