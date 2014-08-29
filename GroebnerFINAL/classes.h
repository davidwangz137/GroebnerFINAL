#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

extern int size;

class Rational{
public:
	int numer, denom;
	Rational();
	Rational(int a, int b);
	Rational(int a, int b, bool c);
	string print(int f);
};

class Monomial {
public:
	Rational coeff;
	vector<int> powers;
	Monomial::Monomial(Rational a, vector<int> b);
	string print(int f);
	string printP();
};

class Polynomial {
public:
	vector<Monomial> poly;
	Polynomial(vector<Monomial> v);//No sorting required
	Polynomial(vector<Monomial> v, int(*compar)(const Monomial, const Monomial));
	void sort(string order);//Sort using string argument
	string print();
};

class Ideal {
public:
	vector<Polynomial> gen;
	string ord;
	int(*compar)(const Monomial, const Monomial);
	Ideal(vector<Polynomial> p, string order);
	void changeOrder(string order);
	vector<Polynomial> div(Polynomial p);
	Polynomial divR(Polynomial p);
	vector<Polynomial> divide(Polynomial p, int(*compar)(const Monomial, const Monomial));
	Polynomial Ideal::divideR(Polynomial p, int(*compar)(const Monomial, const Monomial));//Returns only the remainder instead of the polynomial coefficients as well
	void Groebner1();//Generates the groebner basis using buchberger's algorithm without any improvements
	void Groebner2();//Buchberger with simple improvements
	void print();
	//TODO
	//Ideal equality by computing reduced Groebner basis. Since this is unique for each ideal, can compare to see if equal
	//Compute minimal Groebner basis
	//Buchberger with optimizations
	//Polynomial equation solving
};

int GCD(int a, int b);
void signCheck(int& a, int&b);
int lex(const Monomial a, const Monomial b);
int grl(const Monomial a, const Monomial b);
int grv(const Monomial a, const Monomial b);
void selection(vector<Monomial> &poly, int(*compar)(const Monomial, const Monomial));
void mPrint(vector<Monomial> poly);
void pPrint(vector<Polynomial> vec);
Polynomial syzygy(Polynomial a, Polynomial b, int(*compar)(const Monomial, const Monomial));
bool equal(Monomial a, Monomial b);
bool equal(Polynomial a, Polynomial b);
Monomial LCM(Monomial a, Monomial b);
Monomial GCD(Monomial a, Monomial b);
