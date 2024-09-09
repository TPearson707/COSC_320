/*
Author: Don Spickler
Creation Date: 1/10/2022
Last Update: 1/22/2024
Description: Example of using a typedef to define a function pointer data type.
*/

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Defines a YesNoFcn as a pointer to a function bringing in two ints and
// outputs a bool.
typedef bool (*YesNoFcn)(int, int);

// Prototypes.
void findMatches(int[], int[], int, YesNoFcn);
bool intEqual(int, int);
bool intGreater(int, int);
bool bothOdd(int, int);

int main() {
  srand(time(0));

  // Arrays for example.
  int arr1[7] = {2, 5, 6, 9, 10, 1, 1};
  int arr2[7] = {4, 4, 2, 9, 0, 3, 4};
  int arr3[7];

  for (int i = 0; i < 7; i++) {
    arr3[i] = rand() % 10 + 1;
  }

  cout << "Calling findMatches() using intEqual() : " << endl;
  findMatches(arr1, arr2, 7, &intEqual);
  cout << endl;

  cout << "Calling findMatches() using bothOdd() : " << endl;
  findMatches(arr1, arr2, 7, &bothOdd);
  cout << endl;

  cout << "Calling findMatches() using intGreater() : " << endl;
  findMatches(arr1, arr2, 7, &intGreater);
  cout << endl;

  cout << "Calling findMatches() using intGreater() : " << endl;
  findMatches(arr1, arr3, 7, &intGreater);
  cout << endl;

  return 0;
}

/*
Description: Function to simply apply the parameter function to each of the
corresponding items in the two input arrays.
Parameters: values1, values2: two input int arrays.
numValues: size of the two arrays.
inFunction: function pointer to a YesNoFcn data type.
Return: None
*/

void findMatches(int values1[], int values2[], int numValues,
                 YesNoFcn inFunction) {
  for (int i = 0; i < numValues; i++) {
    if (inFunction(values1[i], values2[i])) {
      cout << "Match found at position " << i << " (" << values1[i] << ", "
           << values2[i] << ")" << endl;
    }
  }
}

/*
Description: Function that returns true if both input integers are equal and
false otherwise.
Parameters: inItem1, inItem2: two input integers.
Return: true if both input integers are equal and false otherwise.
*/

bool intEqual(int inItem1, int inItem2) { return (inItem1 == inItem2); }

/*
Description: Function that returns true if inItem1 > inItem2 and false
otherwise.
Parameters: inItem1, inItem2: two input integers.
Return: true if inItem1 > inItem2 and false otherwise.
*/

bool intGreater(int inItem1, int inItem2) { return (inItem1 > inItem2); }

/*
Description: Function that returns true if both inItem1 and inItem2 are odd and
false otherwise.
Parameters: inItem1, inItem2: two input integers.
Return: true if both inItem1 and inItem2 and odd and false otherwise.
*/

bool bothOdd(int inItem1, int inItem2) {
  return (inItem1 % 2 == 1 && inItem2 % 2 == 1);
}
