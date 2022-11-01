/*	This program was created to practice interacting with r-subsets with those subsets being in lexicographic order.
	Date of creation: November 1, 2022
	The program asks the user for the two inputs: size of the subsets, maximum value of the elements
*/
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Takes a string name and asks for an integer input which it then verifies and returns
int getIntInput(string integerName) {
	int outputInt = 0;

	do {
		cout << "Please enter an integer for " << integerName << endl;
		cin >> outputInt;
		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid integer! Please try again" << endl;
			continue;
		}
		else break;
	} while (true);
	
	return outputInt;
}

// Takes in a vector of integers e.g. [1,2,3] and returns a string e.g. "{1,2,3}"
string vectToString(vector<int> inputVector) {
	ostringstream oss;

	oss << '{';
	for (int i = 0; i < inputVector.size(); i++) {
		oss << inputVector.at(i);
		if (i != inputVector.size() - 1) {
			oss << ',';
		}
	}
	oss << '}';

	return (oss.str());
}

// Initializes a vector of n elements to be [1, 2, ..., n-1, n]
void initVector(vector<int>& inputVector) {
	for (int i = 0; i < inputVector.size(); i++) {
		inputVector.at(i) = i + 1;
	}
	return;
}

// Takes a maxValue and subset and increments the subset to the next lexicographic subset
bool NextSubset(int maxValue, vector<int>& subset) {
	bool isSubsetMaxed = false;
	int vectorSize = subset.size();

	for (int i = vectorSize - 1; i >= 0; i--) {
		if (i == 0 && subset.at(i) == maxValue - vectorSize + 1) { // If the first value is at its maximum, then the subset is at its maximum.
			isSubsetMaxed = true;
			break;
		}
		if (subset.at(i) < maxValue - vectorSize + i + 1) { // Is element < maximum value for its index
			subset.at(i) += 1;
			if (i < vectorSize - 1) { // If i is not the last index in the vector
				for (int j = i + 1; j < vectorSize; j++) { // for each element after vector[i]
					subset.at(j) = subset.at(j - 1) + 1; // each following element is assigned to 1 + its preceding element
				}
			}
			break;
		}
	}

	return (isSubsetMaxed);
}

// Ask the user for the size of a subset and the maximum value of the elements
// Output the subsets to a file in lexicographic order 
int main() {
	ofstream myfile;
	myfile.open("output.txt");

	int elementCount = getIntInput("number of elements in the subset");
	myfile << "elementCount: " << elementCount << endl;
	int elementMax = getIntInput("maximum value of an element");
	myfile << "elementMax: " << elementMax << endl << endl;

	vector<int> subset(elementCount); // If elementCount was 5, subset is the vector [0,0,0,0,0]
	initVector(subset); // Change [0,0,0,0,0] to [1,2,3,4,5]
	myfile << vectToString(subset) << endl;

	while (!NextSubset(elementMax, subset)) {
		myfile << vectToString(subset) << endl;
	}

	myfile.close();
	return (0);
}