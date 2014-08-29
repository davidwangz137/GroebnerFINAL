#pragma once

int size;

class Rational{
public:
	int numer, denom;
	Rational() : numer(1), denom(1) {};
	Rational(int a, int b);
	Rational(int a, int b, bool c);
	string print(int f);
};

Rational operator+ (const Rational& a, const Rational& b)
{
	int gcd = GCD(a.denom, b.denom);
	int newNumer = a.numer*(b.denom / gcd) + b.numer*(a.denom / gcd);
	int newDenom = a.denom*(b.denom / gcd);
	signCheck(newNumer, newDenom);
	return Rational(newNumer, newDenom, true);//Boolean is extra flag to prevent reduction by GCD again
}

Rational operator- (const Rational& a, const Rational& b)
{
	int gcd = GCD(a.denom, b.denom);
	int newNumer = a.numer*(b.denom / gcd) - b.numer*(a.denom / gcd);
	int newDenom = a.denom*(b.denom / gcd);
	signCheck(newNumer, newDenom);
	return Rational(newNumer, newDenom, true);//Boolean is extra flag to prevent reduction by GCD again
}

Rational operator* (const Rational& a, const Rational& b)
{
	int c = GCD(a.numer, b.denom);
	int d = GCD(b.numer, a.denom);
	int newNumer = (a.numer / c)*(b.numer / d);
	int newDenom = (a.denom / d)*(b.denom / c);
	signCheck(newNumer, newDenom);
	return Rational(newNumer, newDenom, true);//Boolean is extra flag to prevent reduction by GCD again
}

Rational operator/ (const Rational& a, const Rational& b)
{
	int c = GCD(a.numer, b.numer);
	int d = GCD(b.denom, a.denom);
	int newNumer = (a.numer / c)*(b.denom / d);
	int newDenom = (a.denom / d)*(b.numer / c);
	signCheck(newNumer, newDenom);
	return Rational(newNumer, newDenom, true);//Boolean is extra flag to prevent reduction by GCD again
}


class Monomial {
public:
	Rational coeff;
	int * powers;
	Monomial(Rational a, int* b){
		coeff = a;
		powers = new int[size];
		for (int i = 0; i < size; i++)
			powers[i] = b[i];
	}
	string print(int f){
		string ret = coeff.print(f) + "[";//Append the coefficient to the front
		for (int i = 0; i < size; i++)
		{
			ret += to_string(powers[i]);
			if (i != size - 1)
				ret += ",";
		}
		return ret + "]";
	}
	string printP(){
		string ret = coeff.print(1);//Append the coefficient to the front
		for (int i = 0; i < size; i++)
		{
			ret += "x" + to_string(i) + "^" + to_string(powers[i]);
		}
		return ret;
	}
};

class Polynomial {
	vector<Monomial> poly;
public:
	Polynomial(vector<Monomial> v){
		poly = v;
		selection(poly, lex);
	}
	void sort(string order){
		if (order == "lex")//Sort monomials according to lexographical order
		{
		}
		if (order == "grl")//Graded lex
		{
		}
		if (order == "grv")//Graded reverse lex order
		{
		}
	}
	string print(){
		string app = "";
		app += poly[0].print(0);
		for (int i = 1; i < poly.size(); i++)
		{
			if (poly[i].coeff.numer < 0)
				app += " - ";
			else
				app += " + ";
			if (poly[i].coeff.numer < 0)//Makes the output prettier by changing + -() into simply -() and inverts - -() into + ()
				app += poly[i].print(1);
			else
				app += poly[i].print(0);
		}
		return app;
	}
};