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

#ifndef _CALC_TYPE_DEFINE_H_
#define _CALC_TYPE_DEFINE_H_
namespace calculater {

enum class TokenType
{
    OPERATOR,
    NUMBER,
    UNKNOWN,
};

enum class OperatorType 
{
	UNKNOWN_OPERATOR=0,
    ADD_OPERATOR=1,
    SUB_OPERATOR=2,
    MUL_OPERATOR=3,
    DIV_OPERATOR=4,
    LEFT_BRACKETS=5,
    RIGHT_BRACKETS=6,
	OTHER_OPERATOR=7,
};

enum class OperatorPriority
{
	UNKNOWN_LEVEL=0,
    ADD_LEVEL=1,
    MUL_LEVEL=2,
    LEFT_BRACKETS_LEVEL=3,
    RIGHT_BRACKETS_LEVEL=4,
};

}
#endif