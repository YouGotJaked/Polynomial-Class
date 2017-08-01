/* 
 * File:   main.cpp
 * Author: jakeday
 *
 * Created on May 2, 2017, 8:38 PM
 */

#include <cstdlib>
#include <iostream>
#include "poly2.h"

using namespace std;

int main(int argc, char** argv) {    
	coen70_lab4_2::polynomial p1(1, 1);

	cout << p1 << endl; // x

	p1.assign_coef(3, 0);

	cout << p1 << endl; // x + 3
	
	p1.add_to_coef(-5, 1);
	
	cout << p1 << endl; // -4x + 3

	cout << p1.antiderivative() << endl; // -2x^2 + 3x
	cout << p1.derivative() << endl; // -4

	cout << p1.coefficient(1) << endl; // -4

	cout << p1.definite_integral(1, 2) << endl; // -3

	cout << p1.degree() << endl; // 1

	cout << p1.eval(2) << endl; // -5
	cout << p1.is_zero() << endl; // 0

	p1.assign_coef(4, 3);

	cout << p1.next_term(1) << endl; // 3
	cout << p1.previous_term(1) << endl; // 0

	cout << p1.next_term(10) << endl; // 0
	p1.assign_coef(-4, 1); 
        p1.assign_coef(0,0);
	cout << p1 << endl; // 4x^3 - 4x
	cout << p1.previous_term(1) << endl; // UINT_MAX

	cout << p1(2) << endl; // 24

	coen70_lab4_2::polynomial p2(1, 2);
	p2.assign_coef(1, 0);
	p2.assign_coef(2, 1);
	cout << "p1: " << p1 << endl; // 4x^3 - 4x
	cout << "p2: " << p2 << endl; // x^2 + 2x + 1
	cout << "----" << endl;
        coen70_lab4_2::polynomial p3(p1);
        //p3 = p1;
        cout << "p3: " << p3 << endl;
	cout << "p1 + p2: " << p1 + p2 << endl; // 4x^3 + x^2 - 2x + 1
	cout << "p2 - p1: " << p2 - p1 << endl; // -4x^3 + x^2 + 6x + 1
	cout << "p1 * p2: " << p1 * p2 << endl; // 4x^5 + 8x^4 - 8x^2  - 4x

	p1.clear();
	cout << p1 << endl; // Nothing

	p1.assign_coef(0.1, 0);
	p1.assign_coef(5.23, 1);
	p1.assign_coef(2.1, 2);
	cout << p1 << endl; // 2.1x^2 + 5.23x + 0.1
}

