////////////////////////////////////////////////////////
// ECE 2574, Homework 1, starter code
//
// File name:	hw1_main.cpp
// Description: Test a modified bag ADT to ensure that the replace method and parameterized constructor work properly for all conceived cases.
// Date:		2/9/2018

#define CATCH_CONFIG_MAIN			// this line tells Catch to provide a main() function
#define CATCH_CONFIG_COLOUR_NONE	// this line avoids problems due to color-coding the output
#include "catch.hpp"

#include "ArrayBag.h" 

// The following tests need to be expanded, as described in the specification
TEST_CASE("Test the 'replace' method", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());
	b.add(1);
	b.add(2);
	b.add(3);

	REQUIRE(b.replace(1, 100));	//tests a simple case to see if replace works
}

TEST_CASE("Test for empty", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());
	REQUIRE(!b.replace(1, 100)); //tests to see if replace works when the array is empty
}

TEST_CASE("Test for removal", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());
	b.add(1);
	b.add(2);
	b.add(3);

	REQUIRE(b.replace(1, 4));
	REQUIRE(!b.contains(1));	//makes sure 1 was removed
	REQUIRE(b.contains(4));		//makes sure 1 was replaced with 4

}

TEST_CASE("Test for multiple appearances", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());
	b.add(1);
	b.add(2);
	b.add(3);
	b.add(3);
	b.add(3);

	REQUIRE(b.replace(3, 4));
	REQUIRE(b.getFrequencyOf(4) == 3);		//makes sure all instances of 3 were replaced
}

TEST_CASE("Test for an item that was already in the bag", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());
	b.add(1);
	b.add(2);
	b.add(3);

	REQUIRE(b.replace(1, 3));
	REQUIRE(b.getFrequencyOf(1) == 0);	//makes sure 1 was replaced
	REQUIRE(b.getFrequencyOf(3) == 2);	//makes sure that there are now 2 3s in the array

}

TEST_CASE("Test to make sure other items are unaffected", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());
	b.add(1);
	b.add(2);
	b.add(3);

	REQUIRE(b.replace(1, 3));
	REQUIRE(b.getFrequencyOf(2) == 1);		//makes sure 2 was unaffected

}

TEST_CASE("Test to make sure the size remained the same", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());
	b.add(1);
	b.add(2);
	b.add(3);

	REQUIRE(b.replace(1, 4));
	REQUIRE(b.getCurrentSize() == 3);		//compares the current size to the original size

}

TEST_CASE("Test the case where all items are the same", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());
	b.add(1);
	b.add(1);
	b.add(1);
	b.add(1);
	b.add(1);
	b.add(1);

	REQUIRE(b.replace(1, 2));
	REQUIRE(b.getFrequencyOf(2) == 6);		//makes sure all items were replaced
	REQUIRE(!b.contains(1));
}

TEST_CASE("Test the case when the array is full of different items", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());
	b.add(1);
	b.add(2);
	b.add(3);
	b.add(4);
	b.add(5);
	b.add(6);

	REQUIRE(b.replace(1, 7));
	REQUIRE(b.contains(7));			//makes sure 1 was replaced with 7
	REQUIRE(!b.contains(1));
	REQUIRE(b.getCurrentSize() == 6);
}

TEST_CASE("Tests to make sure iterative cases run correctly", "[ArrayBag]") {

	ArrayBag<int> b;
	REQUIRE(b.isEmpty());

	b.add(1);
	b.add(2);
	b.add(3);
	b.add(4);
	b.add(5);
	b.add(6);

	REQUIRE(b.replace(1, 2));
	REQUIRE(b.getFrequencyOf(2) == 2);		//makes sure 1 was replaced with 2
	REQUIRE(!b.contains(1));
	REQUIRE(b.replace(2, 3));
	REQUIRE(b.getFrequencyOf(3) == 3);		//makes sure 2s were replaced with 3s
	REQUIRE(!b.contains(2));
	REQUIRE(b.replace(3, 4));
	REQUIRE(b.getFrequencyOf(4) == 4);		//makes sure 3s were replaced with 4s
	REQUIRE(!b.contains(3));
	REQUIRE(b.replace(4, 5));
	REQUIRE(b.getFrequencyOf(5) == 5);		//makes sure 4s were replaced with 5s
	REQUIRE(!b.contains(4));
	REQUIRE(b.replace(5, 6));
	REQUIRE(b.getFrequencyOf(6));			//makes sure 5s were replaced with 6s
	REQUIRE(!b.contains(5));

}

TEST_CASE("Test for different data types", "[ArrayBag]") {

	ArrayBag<char> b;
	b.isEmpty();
	b.add('a');
	b.add('b');
	b.add('c');

	REQUIRE(b.replace('a', 'd'));			//tests replace for char data type
	REQUIRE(b.contains('d'));
	REQUIRE(!b.contains('a'));

	ArrayBag<double> c;
	c.isEmpty();
	c.add(1.1);
	c.add(1.2);
	c.add(1.3);

	REQUIRE(c.replace(1.1, 1.4));			//tests replace for double data type
	REQUIRE(c.contains(1.4));
	REQUIRE(!c.contains(1.1));
}

TEST_CASE("Test for multiple replacements of one item and clear", "[ArrayBag]") {


	ArrayBag<int> b;
	b.isEmpty();
	b.add(1);
	b.add(2);
	b.add(3);
	b.add(4);
	b.add(5);
	b.add(6);

	REQUIRE(b.replace(1, 7));
	REQUIRE(!b.replace(1, 7));		//tests to make sure that the replace method won't return true for trying to replace 1 with 7 again

	b.clear();
	REQUIRE(!b.replace(0, 1));		//tests what happens when replacing comes after clear
}

TEST_CASE("Test for what happens when replace takes place after removed", "[ArrayBag]") {

	ArrayBag<int> b;
	b.isEmpty();
	b.add(1);
	b.add(2);
	b.add(3);
	b.add(4);
	b.add(5);
	b.add(6);

	REQUIRE(b.replace(1, 2));
	REQUIRE(b.remove(2));			//test to make sure 2 was removed
	REQUIRE(b.getFrequencyOf(2) == 1);		//makes sure 2 is present
	REQUIRE(b.replace(2, 3));
	REQUIRE(b.getFrequencyOf(3) == 2);		//makes sure 2 was replaced and the original 3 was unaffected
}

TEST_CASE("Test the new constructor", "[ArrayBag]") {

	int arr[3] = {1,2,3};

	ArrayBag<int> b(arr, 3);

	REQUIRE(b.replace(1,4));
	REQUIRE(b.getCurrentSize() == 3);	//makes sure the array size translated throught the constructor
	REQUIRE(b.contains(4));				//makes sure the replacement worked
	REQUIRE(!b.contains(1));

	double arra[3]{ 1.1,1.2,1.3 };

	ArrayBag<double> c(arra,3);
	c.isEmpty();
	c.add(1.1);
	c.add(1.2);
	c.add(1.3);

	REQUIRE(c.replace(1.1, 1.4));			//tests replace for double data type
	REQUIRE(c.contains(1.4));
	REQUIRE(!c.contains(1.1));


	int ar[6]{ 1,2,3,4,5,6 };
	ArrayBag<int> d(ar, 6);

	REQUIRE(d.replace(1, 2));
	REQUIRE(d.getFrequencyOf(2) == 2);		//makes sure 1 was replaced with 2
	REQUIRE(!d.contains(1));
	REQUIRE(d.replace(2, 3));
	REQUIRE(d.getFrequencyOf(3) == 3);		//makes sure 2s were replaced with 3s
	REQUIRE(!d.contains(2));
	REQUIRE(d.replace(3, 4));
	REQUIRE(d.getFrequencyOf(4) == 4);		//makes sure 3s were replaced with 4s
	REQUIRE(!d.contains(3));
	REQUIRE(d.replace(4, 5));
	REQUIRE(d.getFrequencyOf(5) == 5);		//makes sure 4s were replaced with 5s
	REQUIRE(!d.contains(4));
	REQUIRE(d.replace(5, 6));
	REQUIRE(d.getFrequencyOf(6));			//makes sure 5s were replaced with 6s
	REQUIRE(!d.contains(5));
}
