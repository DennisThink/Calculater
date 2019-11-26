// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef _H_BRACKETS_H_
#define _H_BRACKETS_H_
#include "token_operator.h"
namespace calculater {	
#define UNUSED_WARN(X)   (X.getValue())
class LeftBrackets:public TokenOperator
{
public:
	explicit LeftBrackets(){};
	virtual ~LeftBrackets(){};
	virtual OperatorType getOperatorType() override final {return OperatorType::LEFT_BRACKETS;};
	virtual std::string toString() override final { return "(";}
	virtual OperatorPriority getOperatorPriority() override final { return OperatorPriority::LEFT_BRACKETS_LEVEL; }
	virtual TokenNumber compute(const TokenNumber& lhs,const TokenNumber& rhs) override final {UNUSED_WARN(rhs);return lhs;}
};

class RightBrackets:public TokenOperator
{
public:
	explicit RightBrackets(){};
	virtual ~RightBrackets(){};
	virtual OperatorType getOperatorType() override final{return OperatorType::RIGHT_BRACKETS;};
	virtual std::string toString() override final { return ")";}
	virtual OperatorPriority getOperatorPriority() override final { return OperatorPriority::RIGHT_BRACKETS_LEVEL; }
	virtual TokenNumber compute(const TokenNumber& lhs,const TokenNumber& rhs) override final {UNUSED_WARN(rhs);return lhs;}
};

}
#endif