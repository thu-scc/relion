/***************************************************************************
 *
 * Author: "Sjors H.W. Scheres"
 * MRC Laboratory of Molecular Biology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * This complete copyright notice must be included in any revised version of the
 * source code. Additional authorship citations may be added, but existing
 * author citations must be preserved.
 ***************************************************************************/
#ifndef COMPLEX_H_
#define COMPLEX_H_
#include <iostream>
#include <cmath>
#include "src/macros.h"

class Complex
{

	public:

	RFLOAT real;
	RFLOAT imag;

    // Constructor
	Complex(RFLOAT _r = 0.0, RFLOAT _i = 0.0) {
	    real = _r, imag = _i;
	}

    Complex operator+(Complex &op) {
        return Complex(real + op.real, imag + op.imag);
	}

    void operator+=(Complex &op) {
        real += op.real;
        imag += op.imag;
	}

    Complex operator-(Complex &op) {
        return Complex(real - op.real, imag - op.imag);
	}

    void operator-=(Complex &op) {
        real -= op.real;
        imag -= op.imag;
	}

    Complex operator*(Complex &op) {
        return Complex((real * op.real) - (imag * op.imag), (real * op.imag) + (imag * op.real));
	}

    void operator*=(RFLOAT op) {
        real *= op;
        imag *= op;
	}

    Complex operator*(RFLOAT op) {
        return Complex(real*op, imag*op);
	}

    Complex operator/(Complex &op) {
        RFLOAT cd = op.norm();
        RFLOAT realval = real*op.real + imag*op.imag;
        RFLOAT imagval = imag*op.real - real*op.imag;
        return Complex(realval/cd, imagval/cd);
	}

    Complex operator/(RFLOAT op) {
        return Complex(real/op, imag/op);
	}

    void operator/=(RFLOAT op) {
        real /= op;
        imag /= op;
	}

    // Complex conjugated
    Complex conj() {
        return Complex(real, -imag);
    }

    // Abs value: sqrt(real*real+imag*imag)
    RFLOAT abs() {
        return sqrt(real*real + imag*imag);
    }

    // Norm value: real*real+imag*imag
    RFLOAT norm() {
        return real*real + imag*imag;
    }

    // Phase angle: atan2(imag,real)
    RFLOAT arg() {
        return atan2(imag, real);
    }


};

inline Complex conj(const Complex& op) {
    return Complex(op.real, -op.imag);
}
inline RFLOAT abs(const Complex& op) {
    return sqrt(op.real*op.real + op.imag*op.imag);
}
inline RFLOAT norm(const Complex& op) {
    return op.real*op.real + op.imag*op.imag;
}
inline RFLOAT arg(const Complex& op) {
    return atan2(op.imag, op.real);
}

inline Complex operator+(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.real + rhs.real, lhs.imag + rhs.imag);
}
inline Complex operator-(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.real - rhs.real, lhs.imag - rhs.imag);
}
inline Complex operator*(const Complex& lhs, const Complex& rhs) {
    return Complex((lhs.real * rhs.real) - (lhs.imag * rhs.imag), (lhs.real * rhs.imag) + (lhs.imag * rhs.real));
}
inline Complex operator*(const Complex& lhs, const RFLOAT& val) {
    return Complex(lhs.real * val , lhs.imag * val);
}
inline Complex operator*(const RFLOAT& val, const Complex& rhs) {
    return Complex(rhs.real * val , rhs.imag * val);
}
inline Complex operator/(const Complex& lhs, const RFLOAT& val) {
    return Complex(lhs.real / val , lhs.imag / val);
}

inline void operator+=(Complex& lhs, const Complex& rhs) {
    lhs.real += rhs.real;
    lhs.imag += rhs.imag;
}

inline void operator-=(Complex& lhs, const Complex& rhs) {
    lhs.real -= rhs.real;
    lhs.imag -= rhs.imag;
}

#endif
