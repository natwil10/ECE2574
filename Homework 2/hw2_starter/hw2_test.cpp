// HW2 starter code for testing
#define CATCH_CONFIG_MAIN			// this line tells Catch to provide a main() function
#define CATCH_CONFIG_COLOUR_NONE	// this line avoids problems due to color-coding the output
#include "catch.hpp"
#include "Poly.h" 

TEST_CASE("Testing empty polyline", "[Poly]") 
{
	INFO("Hint: testing all methods with an empty polyline");

	Poly<int> p;

	REQUIRE(p.isEmpty());
	REQUIRE(p.getNumberOfPoints() == 0);

	REQUIRE(!p.insert(1, 2, -1));
	REQUIRE(!p.insert(1, 2, 1));
	REQUIRE(!p.remove(-1));
	REQUIRE(!p.remove(0));
	REQUIRE(!p.remove(1));
	REQUIRE(p.getCoordinateX(0) == -1);		
	REQUIRE(p.getCoordinateY(0) == -1);
	REQUIRE(p.getArcLength() == 0.0);
	REQUIRE(!p.translate(1, 2));

	INFO("Hint: testing several methods after clearing an empty polyline");
	p.clear();
	REQUIRE(p.isEmpty());
	REQUIRE(p.getNumberOfPoints() == 0);
	REQUIRE(!p.remove(0));
	REQUIRE(p.insert(1,1,0));
	REQUIRE(p.remove(0));
}

TEST_CASE("Testing polyline with a single node", "[Poly]") 
{
	INFO("Hint: testing all methods on a polyline with 1 node");

	Poly<int> p;	
	REQUIRE(p.insert(1, 2, 0));

	REQUIRE(!p.isEmpty());
	REQUIRE(p.getNumberOfPoints() == 1);
	REQUIRE(p.getCoordinateX(0) == 1);
	REQUIRE(p.getCoordinateY(0) == 2);
	REQUIRE(p.getArcLength() == 0.0);
	REQUIRE(p.translate(3, 4));
	REQUIRE(p.getCoordinateX(0) == 4);
	REQUIRE(p.getCoordinateY(0) == 6);
	REQUIRE(p.getCoordinateX(-1) == -1);
	REQUIRE(p.getCoordinateY(-1) == -1);

	REQUIRE(p.insert(2,3,1));
	REQUIRE(p.remove(1));
	REQUIRE(p.remove(0));
	REQUIRE(p.isEmpty());
	REQUIRE(p.insert(1, 1, 0));
	REQUIRE(!p.insert(1, 1, 3));
	REQUIRE(p.getNumberOfPoints() == 1);

}

TEST_CASE("Testing polyline with multiple nodes", "[Poly]")
{
	INFO("Hint: testing all methods on a polyline with 1 node");

	Poly<int> p;
	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(2, 3, 1));
	REQUIRE(p.insert(3, 4, 2));
	REQUIRE(p.insert(0, 1, 0));
	REQUIRE(p.insert(0, 0 , 2));
	REQUIRE(!p.insert(0, 0, -2));
	REQUIRE(!p.insert(0, 0, 12));

	REQUIRE(!p.isEmpty());
	REQUIRE(p.getNumberOfPoints() == 5);
	REQUIRE(p.getCoordinateX(0) == 0);
	REQUIRE(p.getCoordinateY(0) == 1);
	REQUIRE(p.getArcLength() == 8.67);
	REQUIRE(p.translate(3, 4));
	REQUIRE(p.translate(0, 0));
	REQUIRE(p.getCoordinateX(0) == 3);
	REQUIRE(p.getCoordinateY(0) == 5);
	REQUIRE(p.getCoordinateX(-1) == -1);
	REQUIRE(p.getCoordinateY(-1) == -1);
	REQUIRE(p.translate(-3, -5));
	REQUIRE(p.getCoordinateX(4) == 3);
	REQUIRE(p.getCoordinateY(4) == 4);
	REQUIRE(p.getCoordinateX(5) == -1);
	REQUIRE(p.getCoordinateY(5) == -1);

	REQUIRE(p.remove(0));
	REQUIRE(p.getNumberOfPoints() == 4);
	REQUIRE(p.getCoordinateX(0) == 1);
	REQUIRE(p.getCoordinateY(0) == 2);

	REQUIRE(p.remove(1));
	REQUIRE(p.getNumberOfPoints() == 3);
	REQUIRE(p.getCoordinateX(1) == 2);
	REQUIRE(p.getCoordinateY(1) == 3);

	REQUIRE(p.remove(2));
	REQUIRE(p.getNumberOfPoints() == 2);
	REQUIRE(p.getCoordinateX(2) == -1);
	REQUIRE(p.getCoordinateY(2) == -1);

	REQUIRE(!p.remove(2));
	

	// TO-DO:  add more REQUIRE statements here to test a polyline with 1 node.

}

TEST_CASE("Testing the copy constructor", "[Poly]")
{
	INFO("Hint: testing the copy constructor");

	Poly<int> a;
	Poly<int>b(a);
	REQUIRE(b.isEmpty());


	Poly<int> p;
	REQUIRE(p.insert(1, 2, 0));
	Poly<int>x(p);

	REQUIRE(x.getArcLength() == p.getArcLength());
	REQUIRE(x.getCoordinateX(0) == p.getCoordinateX(0));
	REQUIRE(x.getCoordinateY(0) == p.getCoordinateY(0));
	REQUIRE(x.getNumberOfPoints() == p.getNumberOfPoints());
	REQUIRE(!x.isEmpty());

	Poly<int> q;
	REQUIRE(q.insert(1, 2, 0));
	REQUIRE(q.insert(3, 4, 1));
	REQUIRE(q.insert(5, 6, 2));
	REQUIRE(q.insert(7, 8, 0));
	Poly<int>r(q);
	REQUIRE(r.getArcLength() == q.getArcLength());
	REQUIRE(r.getCoordinateX(0) == q.getCoordinateX(0));
	REQUIRE(r.getCoordinateY(0) == q.getCoordinateY(0));
	REQUIRE(r.getNumberOfPoints() == q.getNumberOfPoints());
	REQUIRE(r.getArcLength() == q.getArcLength());
	REQUIRE(q.insert(1, 2, 5));
	REQUIRE(!r.isEmpty());

}

TEST_CASE("Testing the isEmpty method", "[Poly]")
{
	INFO("Hint: testing the copy constructor");

	Poly<int> p;

	REQUIRE(p.isEmpty());

	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));

	REQUIRE(!p.isEmpty());

	p.clear();
	REQUIRE(p.isEmpty());
}

TEST_CASE("Testing the getNumberOfPoints method", "[Poly]")
{
	INFO("Hint: testing the copy constructor");

	Poly<int> p;
	REQUIRE(p.getNumberOfPoints() == 0);
	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.getNumberOfPoints() == 1);
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.getNumberOfPoints() == 2);
	REQUIRE(p.insert(7, 8, 0));

	REQUIRE(p.remove(0));
	REQUIRE(p.getNumberOfPoints() == 2);

	p.clear();
	REQUIRE(p.getNumberOfPoints() == 0);

}

TEST_CASE("Testing the insert method", "[Poly]")
{
	INFO("Hint: testing the insert method");

	Poly<int> p;

	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));
	REQUIRE(p.insert(9, 10, 1));
	REQUIRE(!p.insert(1, 2, -1));
	REQUIRE(!p.insert(1, 2, 50));

	p.clear();
	REQUIRE(p.isEmpty());

	REQUIRE(!p.insert(1, 2, -1));
	REQUIRE(!p.insert(1, 2, 50));

}

TEST_CASE("Testing the remove method", "[Poly]")
{
	INFO("Hint: testing the remove method");

	Poly<int> p;

	REQUIRE(!p.remove(0));	//remove from empty

	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));

	REQUIRE(p.remove(0));		//remove from beginning
	REQUIRE(p.getCoordinateX(0) == 1);

	REQUIRE(p.remove(1));
	REQUIRE(p.getCoordinateX(1) == 5);

	REQUIRE(!p.remove(5));
	REQUIRE(p.remove(0));
	REQUIRE(p.remove(0));
	REQUIRE(!p.remove(0));

	p.clear();
	REQUIRE(p.isEmpty());

	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));

	REQUIRE(p.remove(1));		//remove from middle
	REQUIRE(p.remove(1));
	REQUIRE(p.remove(1));
	REQUIRE(!p.remove(1));
	REQUIRE(p.remove(0));
	REQUIRE(p.isEmpty());

	REQUIRE(p.insert(1, 2, 0));		//remove from end
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));
	REQUIRE(p.remove(3));
	REQUIRE(p.remove(2));
	REQUIRE(!p.remove(2));
	REQUIRE(p.remove(1));
	REQUIRE(p.remove(0));
	REQUIRE(!p.remove(-1));

}

TEST_CASE("Testing the clear method", "[Poly]")
{
	INFO("Hint: testing the copy constructor");

	Poly<int> p;
	p.clear();		//clear empty

	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));

	p.clear();		//clear full
	REQUIRE(p.isEmpty());

	
}

TEST_CASE("Testing the getCoordinateX method", "[Poly]")
{
	INFO("Hint: testing the remove method");

	Poly<int> p;
	REQUIRE(p.getCoordinateX(0) == -1); //when empty

	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));

	REQUIRE(p.getCoordinateX(0) == 7);	//test beginning
	REQUIRE(p.getCoordinateX(1) == 1);	//test middle
	REQUIRE(p.getCoordinateX(2) == 3);	//test end
	REQUIRE(p.getCoordinateX(3) == 5);	//test end
	REQUIRE(p.getCoordinateX(4) == -1);	//test invalid
	REQUIRE(p.getCoordinateX(-1) == -1);

}

TEST_CASE("Testing the getCoordinateY method", "[Poly]")
{
	INFO("Hint: testing the remove method");

	Poly<int> p;
	REQUIRE(p.getCoordinateY(0) == -1); //when empty

	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));

	REQUIRE(p.getCoordinateY(0) == 8);	//test beginning
	REQUIRE(p.getCoordinateY(1) == 2);	//test middle
	REQUIRE(p.getCoordinateY(2) == 4);	//test end
	REQUIRE(p.getCoordinateY(3) == 6);	//test end
	REQUIRE(p.getCoordinateY(4) == -1);	//test invalid
	REQUIRE(p.getCoordinateY(-1) == -1);
}

TEST_CASE("Testing the overloaded assignment operator", "[Poly]")
{
	INFO("Hint: testing the overloaded assignment operator");

	Poly<int> p;

	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));

	Poly<int> x;

	x.operator=(p);

	REQUIRE(!x.isEmpty());
	REQUIRE(x.getNumberOfPoints() == 4);
	REQUIRE(x.insert(9, 10, 4));
	REQUIRE(x.getCoordinateX(0) == p.getCoordinateX(0));
	REQUIRE(x.getCoordinateY(0) == p.getCoordinateY(0));
	REQUIRE(x.getCoordinateX(4) == 9);
	REQUIRE(x.getCoordinateY(4) == 10);
	REQUIRE(x.remove(4));
	REQUIRE(x.getArcLength() == p.getArcLength());
	REQUIRE(x.translate(1, 1));

	x.clear();
}

TEST_CASE("Testing the getArcLength method", "[Poly]")
{
	INFO("Hint: testing the remove method");

	Poly<int> p;
	REQUIRE(p.getArcLength() == 0.0);	//empty

	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.getArcLength() == 0.0);	//one point

	REQUIRE(p.insert(2, 3, 1));			//two points
	REQUIRE(p.getArcLength() == 1.4);

	REQUIRE(p.insert(3, 4, 2));			//multiple points
	REQUIRE(p.insert(5, 6, 3));
	REQUIRE(p.getArcLength() == 4.2);

}

TEST_CASE("Testing the translate method", "[Poly]")
{
	INFO("Hint: testing the translate method");

	Poly<int> p;
	REQUIRE(!p.translate(1, 1));		//when empty

	REQUIRE(p.insert(0, 0, 0));			//one point
	REQUIRE(p.translate(1, 1));
	REQUIRE(p.getCoordinateX(0) == 1);
	REQUIRE(p.getCoordinateY(0) == 1);
	REQUIRE(p.translate(-1, -1));
	REQUIRE(p.getCoordinateX(0) == 0);
	REQUIRE(p.getCoordinateY(0) == 0);

	p.clear();

	REQUIRE(p.insert(0, 0, 0));		//more than one point
	REQUIRE(p.insert(1,1,1));
	REQUIRE(p.translate(1, 1));
	REQUIRE(p.getCoordinateX(0) == 1);
	REQUIRE(p.getCoordinateY(0) == 1);
	REQUIRE(p.getCoordinateX(1) == 2);
	REQUIRE(p.getCoordinateY(1) == 2);
	REQUIRE(p.translate(-1, -1));
	REQUIRE(p.getCoordinateX(0) == 0);
	REQUIRE(p.getCoordinateY(0) == 0);
	REQUIRE(p.getCoordinateX(1) == 1);
	REQUIRE(p.getCoordinateY(1) == 1);
}

TEST_CASE("Testing the overloaded plus operator", "[Poly]")
{
	INFO("Hint: testing the overloaded plus operator");

	Poly<int> a;
	Poly<int> b;

	b.operator+(b);					//empty plus empty
	REQUIRE(b.isEmpty());

	Poly<int> c;						//one point plus empty polyline
	Poly<int> d;
	REQUIRE(c.insert(0, 0, 0));
	d.operator+(c);
	REQUIRE(d.getCoordinateX(0) == 0);
	REQUIRE(d.getCoordinateY(0) == 0);
	REQUIRE(d.getNumberOfPoints() == 1);

	Poly<int> e;						//2 polylines with 1 point each
	Poly<int> f;
	REQUIRE(e.insert(0,0,0));
	REQUIRE(f.insert(0, 1, 0));
	e.operator+(f);
	REQUIRE(d.getCoordinateX(0) == 0);
	REQUIRE(d.getCoordinateY(0) == 0);
	REQUIRE(d.getCoordinateX(1) == 0);
	REQUIRE(d.getCoordinateY(1) == 1);
	REQUIRE(d.getNumberOfPoints() == 2);

	Poly<int> g;						//1 empty poly and 1 poly of multiple points
	Poly<int> h;
	REQUIRE(h.insert(0, 0, 0));
	REQUIRE(h.insert(0, 1, 1));
	h.operator+(g);
	REQUIRE(h.getCoordinateX(0) == 0);
	REQUIRE(h.getCoordinateY(0) == 0);
	REQUIRE(h.getCoordinateX(1) == 0);
	REQUIRE(h.getCoordinateY(1) == 1);
	REQUIRE(h.getNumberOfPoints() == 2);

	Poly<int> p;					//two polys of multiple points
	REQUIRE(p.insert(1, 2, 0));
	REQUIRE(p.insert(3, 4, 1));
	REQUIRE(p.insert(5, 6, 2));
	REQUIRE(p.insert(7, 8, 0));
	Poly<int> x;
	REQUIRE(x.insert(1, 2, 0));
	REQUIRE(x.insert(3, 4, 1));
	REQUIRE(x.insert(5, 6, 2));
	REQUIRE(x.insert(7, 8, 0));
	x.operator+(p);

	REQUIRE(x.getCoordinateX(4) == p.getCoordinateX(0));
	REQUIRE(x.getCoordinateX(5) == p.getCoordinateX(1));
	REQUIRE(x.getCoordinateX(6) == p.getCoordinateX(2));
	REQUIRE(x.getCoordinateX(7) == p.getCoordinateX(3));
	REQUIRE(x.getNumberOfPoints() == 8);
}



