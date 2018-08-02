// CS341Program3.cpp
// Author: Christian Dominguez
// CS 341: Spring 2018


#include <iostream>
#include <stdlib.h>
#include "stdafx.h"
#include "myvector.h"

using namespace std;

//void sortArray(myvector<int> &V) {

 // sort(V.begin(), V.end(),
//[]())

//}//End of sortArray()


int main()
{
	myvector<int> V;
	
  for (int i = 0; i < 100; i++) {
    if (i % 2 == 0) {
      V.push_back(i);
    }
  }

  int x = V.size();
  cout << V[x-1] << endl;

  cout << V.front() << endl;
  cout << V.back() << endl;

    return 0;
}//End of main()

