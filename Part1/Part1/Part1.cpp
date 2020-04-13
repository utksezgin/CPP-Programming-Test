#include "pch.h"
#include <iostream>

//Assuming the input points have cartesian coordinates.
struct point
{
	float x;
	float y;
	float z;
};

//Returns a vector from p1 to p2.
point vectorBetween2Points(point p1, point p2);
//Checks whether a point is inside the spherical triangle. Detailed explanation can be found inside the function.
bool isPointIn(point P1, point P2, point P3, point C, float R, point P);
// Determinant of 3 vectors gives us the signed volume of a parallelepiped of the 3 vectors.
// This is also called Scalar Triple Product which is a dot product of one of the vectors with the cross product of other two.
// Example: p1.(p2xp3) where . means dot product and x means cross product.
float signedVolume(point p1, point p2, point p3);

int main()
{
	//Simple test case. Points were created on unreal engine.
	point p { -0.6749f, 0.595314f, 0.436016f };
	point p1{ -0.757916f, 0.126212f, -0.640026f };
	point p2{ 0.552854f, 0.814936f, -0.173872f };
	point p3{ 0.302548f, -0.238078f, 0.922921f };
	point C{ 0.0f, 0.0f, 0.0f };
	float r = 1.0f;


	std::cout <<  isPointIn(p1, p2, p3, C, r, p) << std::endl;

}


bool isPointIn(point P1, point P2, point P3, point C, float R, point P) {
	bool b1, b2, b3;

	//Calculating vectors between given points and the center of the sphere.
	//It's important that all the vectors must be from the center to a point.
	point v = vectorBetween2Points(C, P); //CP Vector
	point v1 = vectorBetween2Points(C, P1); //CP1 Vector
	point v2 = vectorBetween2Points(C, P2); //CP2 Vector
	point v3 = vectorBetween2Points(C, P3); //CP3 Vector

	//On a planar triangle point test, we check whether point is on the same side of an edge between 2 vertices as the 3rd vertex which is 3 checks, is p on the same side of AB as C,
	//BC as A and CA as B. If all of them are same then the point is inside the triangle.

	//3 Points on a sphere surface would create 2 spherical triangles inner and outer.

	//If all the signed volume's are same sign, that means the point is inside the spherical triangle. It's mathematicaly impossible to have a point inside the spherical triangle
	//If one of the signs is different. The bool it calculates is by checking whether if the signedVolume is less than zero but this could also work if all the checks are done by
	//greater than operator which is why it doesn't matter whether the point is inside the inner or outer triangle, if all the signedVolume's signs are same, they're within the given 3 points.
	b1 = signedVolume(v, v1, v2) < 0.0f;
	b2 = signedVolume(v, v2, v3) < 0.0f;
	b3 = signedVolume(v, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

//Returns vector from point 1 to point 2.
point vectorBetween2Points(point p1, point p2) {
	point v;
	v.x = p1.x - p2.x;
	v.y = p1.y - p2.y;
	v.z = p1.z - p2.z;
	return v;
}


float signedVolume(point p1, point p2, point p3) {
	return p1.x*p2.y*p3.z + p1.y*p2.z*p3.x + p1.z*p2.x*p3.y - p1.z*p2.y*p3.x - p1.x*p2.z*p3.y - p1.y*p2.x*p3.z;
}