#include <cmath>
#include <cassert>
#include "poly1.h"

using namespace std;

namespace coen70_lab4 {

    // HELPER FUNCTION

    void polynomial::update_current_degree() {
        for (int i = 0; i < MAXIMUM_DEGREE; i++) {
            if (coef[i] != 0) {
                current_degree = i;
            }
        }
    }

    // CONSTRUCTOR     

    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        clear();
        coef[exponent] = c;
        update_current_degree();
    }

    // MODIFICATION MEMBER FUNCTIONS     

    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] = coefficient;
        update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] += amount;
        update_current_degree();
    }

    void polynomial::clear() {
        for (int i = 0; i < MAXIMUM_DEGREE; i++) {
            coef[i] = 0;
        }
        update_current_degree();
    }

    // CONSTANT MEMBER FUNCTIONS         

    polynomial polynomial::antiderivative() const {
        assert(degree() < MAXIMUM_DEGREE);

        polynomial anti;

        for (int i = MAXIMUM_DEGREE; i > 0; i--) {
            anti.assign_coef(coef[i - 1] / i, i);
        }
        anti.assign_coef(0, 0);
        return anti;
    }

    double polynomial::coefficient(unsigned int exponent) const {
        if (exponent > MAXIMUM_DEGREE) {
            return 0;
        }
        return coef[exponent];
    }

    double polynomial::definite_integral(double x0, double x1) const {
        return (antiderivative().eval(x1) - antiderivative().eval(x0));
    }

    polynomial polynomial::derivative() const {
        polynomial deriv;

        for (int i = 0; i < MAXIMUM_DEGREE; i++) {
            deriv.assign_coef(coef[i + 1] * (i + 1), i);
        }
        return deriv;
    }

    double polynomial::eval(double x) const {
        double value = 0;

        for (int i = 0; i <= MAXIMUM_DEGREE; i++) {
            value += coef[i] * std::pow(x, i);
        }
        return value;
    }

    bool polynomial::is_zero() const {
        return (degree() == 0 && coef[0] == 0);
    }

    unsigned int polynomial::next_term(unsigned int e) const {
        //start at e + 1 since exponent has to be larger than e
        for (int i = e + 1; i <= MAXIMUM_DEGREE; i++) {
            if (coef[i] != 0) {
                return i;
            }
        }
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const {
        //start at e - 1 since exponent has to be smaller than e
        for (int i = e - 1; i >= 0; i--) {
            if (coef[i] != 0) {
                return i;
            }
        }
        return UINT_MAX;
    }

    // NON-MEMBER BINARY OPERATORS     

    polynomial operator+(const polynomial& p1, const polynomial& p2) {
        polynomial p3;

        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++) {
            p3.add_to_coef(p1.coefficient(i), i);
            p3.add_to_coef(p2.coefficient(i), i);
        }
        return p3;
    }

    polynomial operator-(const polynomial& p1, const polynomial& p2) {
        polynomial p3;

        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++) {
            p3.add_to_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        return p3;
    }

    polynomial operator*(const polynomial& p1, const polynomial& p2) {
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);

        polynomial p3;

        for (int i = 0; i <= p1.degree(); i++) {
            for (int j = 0; j <= p2.degree(); j++) {
                p3.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
            }
        }
        return p3;
    }

    // NON-MEMBER OUTPUT FUNCTIONS     

    std::ostream& operator<<(std::ostream& out, const polynomial& p) {
        if (p.is_zero()) {
            out << 0.00;
        } else {
            bool first = true;

            for (int i = p.degree(); i >= 0; i--) {
                if (p.coefficient(i) != 0) {
                    //don't print a "+" for the first coefficient
                    if (!first) {
                        out << ((p.coefficient(i) < 0) ? " - " : " + ");
                        out << std::abs(p.coefficient(i));
                    } else {
                        out << p.coefficient(i);
                    }

                    //don't print x^0
                    if (i > 0) {
                        out << "x";
                        //don't print a exponent for x^1
                        if (i > 1) {
                            out << "^" << i;
                        }
                    }

                    if (first) {
                        first = false;
                    }
                }
            }
        }
        return out;
    }
}