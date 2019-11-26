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


#include <iostream>
#include "parse.h"
	
int main(int argc,char * argv[])
{
	std::cout<<argc<<argv[0]<<std::endl;
	using namespace calculater;
	{
		std::string strExpress;
		std::cout<<"Please Input the Express:"<<std::endl;
		std::cin>>strExpress;
		//TokenNumber numResult = TokenNumber(-8);
		auto tokens = CParser::Parse(strExpress);
		auto result = CParser::Calculate(tokens);
		std::cout<<"Result "<<result->toString()<<std::endl;
		//auto calcResult = dynamic_cast<TokenNumber*>(result.get());
	}
	if(argc > 9)
	{
	}
	else
	{
		std::cout<<"error"<<std::endl;
	}
		
	int i = 0;
	std::cout<<i<<std::endl;
    return 0;
}