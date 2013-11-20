//
//  main.cpp
//  KevinSort
//
//  Created by Kevin Beason on 11/19/13.
//  Copyright (c) 2013 embooglement. All rights reserved.
//

#include <iostream>
#include "kevin_sort.h"

int main(int argc, const char * argv[])
{
	std::vector<int> v = { 3, 2, 1 };
	
	kevin_sort(std::begin(v), std::end(v));
	
	std::cout << "Is sorted: " << std::boolalpha << std::is_sorted(std::begin(v), std::end(v)) << std::endl;

    return 0;
}

