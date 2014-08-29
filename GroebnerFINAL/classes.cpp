#include "classes.h"

int size;

string Rational::print(int f){
	if (f == 1)//Pretty print so that it looks good
	{
		if (denom == 1)
			return to_string(-numer);
		return to_string(-numer) + "/" + to_string(denom);
	}
	if (denom == 1)
		return to_string(numer);
	return to_string(numer) + "/" + to_string(denom);
}

Rational::Rational(){
	numer = 1;
	denom = 1;
}

Rational::Rational(int a, int b, bool c){
	numer = a;
	denom = b;
}

Rational::Rational(int a, int b){
	numer = a;
	denom = b;
	if (a < 0 && b < 0)
	{
		numer *= -1;
		denom *= -1;
		a *= -1;
		b *= -1;
	}
	if (a < 0)//Just finding the GCD of the integers and then dividing. Don't have to multiply end result by -1
		a *= -1;
	if (b < 0)
	{
		b *= -1;
		numer *= -1;//Flip the signs so numerator is negative instead of denominator
		denom *= -1;
	}
	while (true)
	{
		if (a == 0)
		{
			a = b;
			break;
		}
		if (b == 0)
			break;
		if (a > b)
			a = a%b;
		else
			b = b%a;
	}
	numer /= a;
	denom /= a;
}

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

Monomial::Monomial(Rational a, vector<int> b){
	coeff = a;
	for (int i = 0; i < size; i++)
		powers.push_back(b[i]);
}

//Tests if Monomial a can be divided by b
bool divis (Monomial a, Monomial b)
{
	for (int i = 0; i < size; i++)
	{
		if (a.powers[i] < b.powers[i])
			return false;
	}
	return true;
}

bool equal(Monomial a, Monomial b)
{
	for (int i = 0; i < size; i++)
	{
		if (a.powers[i] != b.powers[i])
			return false;
	}
	return true;
}

Monomial operator+ (Monomial a, Monomial b)
{
	Rational rat = a.coeff + b.coeff;
	Monomial c(rat, a.powers);
	return c;//Return the new monomial
}

Monomial operator- (Monomial a, Monomial b)
{
	Rational rat = a.coeff - b.coeff;
	Monomial c(rat, a.powers);
	return c;//Return the new monomial
}

Monomial operator* (Monomial a, Monomial b)
{
	Rational rat = a.coeff*b.coeff;
	Monomial c(rat, a.powers);
	for (int i = 0; i < size; i++)
	{
		c.powers[i] += b.powers[i];
	}
	return c;//Return the new monomial
}

Monomial operator/ (Monomial a, Monomial b)
{
	Rational rat = a.coeff/b.coeff;
	Monomial c(rat, a.powers);
	for (int i = 0; i < size; i++)
	{
		c.powers[i] -= b.powers[i];
	}
	return c;//Return the new monomial
}

string Monomial::print(int f){
	string ret = coeff.print(f) + "[";//Append the coefficient to the front
	for (int i = 0; i < size; i++)
	{
		ret += to_string(powers[i]);
		if (i != size - 1)
			ret += ",";
	}
	return ret + "]";
}

string Monomial::printP(){
	string ret = coeff.print(1);//Append the coefficient to the front
	for (int i = 0; i < size; i++)
	{
		ret += "x" + to_string(i) + "^" + to_string(powers[i]);
	}
	return ret;
}

Monomial GCD(Monomial a, Monomial b)
{
	Rational rat(1,1);
	Monomial c(rat, a.powers);
	for (int i = 0; i < size; i++)
	{
		if (a.powers[i] > b.powers[i])
			c.powers[i] = b.powers[i];
	}
	return c;//Return the new monomial
}

Monomial LCM(Monomial a, Monomial b)
{
	Rational rat(1, 1);
	Monomial c(rat, a.powers);
	for (int i = 0; i < size; i++)
	{
		if (a.powers[i] < b.powers[i])
			c.powers[i] = b.powers[i];
	}
	return c;//Return the new monomial
}

Polynomial::Polynomial(vector<Monomial> v)
{
	poly = v;
}

Polynomial::Polynomial(vector<Monomial> v, int(*compar)(const Monomial, const Monomial))
{
	poly = v;
	selection(v,compar);
}

Polynomial operator* (Monomial a, Polynomial b)
{
	for (int i = 0; i < b.poly.size(); i++)
	{
		b.poly[i] = b.poly[i]*a;//Multiply by the monomial
	}
	return b;//Return the new polynomial
}

Polynomial add(Polynomial a, Monomial b, int(*compar)(const Monomial, const Monomial))
{
	Rational c;//Used for checking zeroes
	vector<Monomial> vec;//Holds the polynomial list
	int num = a.poly.size();
	int inc = 0;
	bool added = false;//Checks if b was added
	while (true)
	{
		if (inc == num && added)
			break;
		if (inc == num)//Check if all of "a" added
		{
			vec.push_back(b);
			added = true;
		}
		else
		{
			if (added)//Check if b already added
			{
				vec.push_back(a.poly[inc]);
				inc++;
			}
			else
			{
				switch (compar(a.poly[inc], b))
				{
				case 0:
					c = a.poly[inc].coeff + b.coeff;
					if (c.numer != 0)
						vec.push_back(a.poly[inc] + b);
					inc++, added = true;
					break;
				case 1:
					vec.push_back(a.poly[inc]);
					inc++;
					break;
				case -1:
					vec.push_back(b);
					added = true;
					break;
				}
			}
		}
	}
	return Polynomial(vec);
}

Polynomial add (Polynomial a, Polynomial b, int(*compar)(const Monomial, const Monomial))
{
	Rational c;//Used for checking zeroes
	vector<Monomial> vec;//Holds the polynomial list
	int num1 = a.poly.size();
	int num2 = b.poly.size();
	int inc1 = 0;
	int inc2 = 0;
	while (true)
	{
		if (inc1 == num1 && inc2 == num2)//If all the polynomials are emptied out then break
			break;
		if (inc1 == num1)//Check if at limit first
		{
			vec.push_back(b.poly[inc2]);
			inc2++;
		}
		else
		{
			if (inc2 == num2)//Check if at limit first
			{
				vec.push_back(a.poly[inc1]);
				inc1++;
			}
			else
			{
				switch (compar(a.poly[inc1], b.poly[inc2]))
				{
				case 0:
					c = a.poly[inc1].coeff + b.poly[inc2].coeff;
					if (c.numer != 0)
						vec.push_back(a.poly[inc1] + b.poly[inc2]);
					inc1++, inc2++;
					break;
				case 1:
					vec.push_back(a.poly[inc1]);
					inc1++;
					break;
				case -1:
					vec.push_back(b.poly[inc2]);
					inc2++;
					break;
				}
			}
		}
	}
	return Polynomial(vec);
}

Polynomial mul(Polynomial a, Polynomial b, int(*compar)(const Monomial, const Monomial))
{
	vector<Monomial> vec;
	Polynomial ret(vec);
	for (int i = 0; i < a.poly.size(); i++)
	{
		ret = add(ret, a.poly[i] * b, compar);//Append the new terms from multiplication
	}
	return ret;
}

bool equal(Polynomial a, Polynomial b)
{
	if (a.poly.size() != b.poly.size())
		return false;
	for (int i = 0; i < a.poly.size(); i++)
	{
		if (!equal(a.poly[i], b.poly[i]))
			return false;
	}
	return true;
}

//Computes the S-polynomial of two polynomials and returns it
Polynomial syzygy(Polynomial a, Polynomial b, int(*compar)(const Monomial, const Monomial))
{
	Monomial gcd = LCM(a.poly[0], b.poly[0]);
	Monomial neg = gcd;
	neg.coeff.numer = -1;
	Polynomial ret = add(gcd / a.poly[0] * a, neg / b.poly[0] * b, compar);
	return ret;
}

void Polynomial::sort(string order)
{
	if (order == "lex")//Sort monomials according to lexographical order
		selection(poly, lex);
	if (order == "grl")//Graded lex
		selection(poly, grl);
	if (order == "grv")//Graded reverse lex order
		selection(poly, grv);
}

string Polynomial::print()
{
	string app = "";
	if (poly.size() == 0)//If empty polynomial
		return "0";//All ideals that are not generated have 0 in them anyways
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

Ideal::Ideal(vector<Polynomial> p, string order)
{
	gen = p;
	ord = order;
	if (order == "lex")//Sort monomials according to lexographical order
		compar = lex;
	if (order == "grl")//Graded lex
		compar = grl;
	if (order == "grv")//Graded reverse lex order
		compar = grv;
}

//Changes the order of the ideal and sorts the polynomials using that order
void Ideal::changeOrder(string order)
{
	ord = order;
	for (int i = 0; i < gen.size(); i++)
	{
		gen[i].sort(order);
	}
	if (order == "lex")//Sort monomials according to lexographical order
		compar = lex;
	if (order == "grl")//Graded lex
		compar = grl;
	if (order == "grv")//Graded reverse lex order
		compar = grv;
}

void Ideal::print()
{
	cout << endl << "The ideal contains " << gen.size() << " polynomial generators" << endl;
	for (int i = 0; i < gen.size(); i++)
	{
		cout << gen[i].print() << endl;
	}
}

vector<Polynomial> Ideal::div(Polynomial p)
{
	if (ord == "lex")//Sort monomials according to lexographical order
		return divide(p, lex);
	if (ord == "grl")//Graded lex
		return divide(p, grl);
	else//Graded reverse lex order
		return divide(p, grv);
}

Polynomial Ideal::divR(Polynomial p)
{
	if (ord == "lex")//Sort monomials according to lexographical order
		return divideR(p, lex);
	if (ord == "grl")//Graded lex
		return divideR(p, grl);
	else//Graded reverse lex order
		return divideR(p, grv);
}

vector<Polynomial> Ideal::divide(Polynomial p, int(*compar)(const Monomial, const Monomial))
{
	vector<Polynomial> vec;//Holds the polynomials from the division
	int leng = gen.size();
	for (int i = 0; i < leng + 1; i++)//An extra one for the remainder
	{
		vector<Monomial> a;
		vec.push_back(Polynomial(a));
	}
	while (p.poly.size() > 0)
	{
		bool divided = false;//Checks if a division occured
		for (int i = 0; i < leng && divided == false; i++)
		{
			//cout << "here" << i;
			if (divis(p.poly[0], gen[i].poly[0]))
			{
				Monomial div = p.poly[0] / gen[i].poly[0];
				//cout << div.print(0);
				vec[i] = add(vec[i], div, compar);
				div.coeff.numer *= -1;//Now make it minus
				Polynomial minus = div*gen[i];
				//cout << endl << p.print() << endl;
				//cout << minus.print() << endl;
				p = add(p, minus, compar);
				//cout << p.print() << endl;
				divided = true;
			}
		}
		//cout << "HERE";
		if (divided == false)//The leading term could not be divided
		{
			vec[leng] = add(vec[leng],p.poly[0],compar);
			p.poly.erase(p.poly.begin());
		}
	}
	//Print the results
	/*cout << endl << "Results" << endl;
	for (int i = 0; i < leng; i++)
	{
		cout << "f" << i << ": " << vec[i].print() << " * (" << gen[i].print() << ")" << endl;
	}
	cout << "Remainder: " << vec[leng].print() << endl;
	cout << endl << "Returning..." << endl;*/
	return vec;
}

Polynomial Ideal::divideR(Polynomial p, int(*compar)(const Monomial, const Monomial))
{
	vector<Polynomial> vec;//Holds the polynomials from the division
	int leng = gen.size();
	for (int i = 0; i < leng + 1; i++)//An extra one for the remainder
	{
		vector<Monomial> a;
		vec.push_back(Polynomial(a));
	}
	while (p.poly.size() > 0)
	{
		bool divided = false;//Checks if a division occured
		for (int i = 0; i < leng && divided == false; i++)
		{
			//cout << "here" << i;
			if (divis(p.poly[0], gen[i].poly[0]))
			{
				Monomial div = p.poly[0] / gen[i].poly[0];
				//cout << div.print(0);
				vec[i] = add(vec[i], div, compar);
				div.coeff.numer *= -1;//Now make it minus
				Polynomial minus = div*gen[i];
				//cout << endl << p.print() << endl;
				//cout << minus.print() << endl;
				p = add(p, minus, compar);
				//cout << p.print() << endl;
				divided = true;
			}
		}
		//cout << "HERE";
		if (divided == false)//The leading term could not be divided
		{
			vec[leng] = add(vec[leng], p.poly[0], compar);
			p.poly.erase(p.poly.begin());
		}
	}
	//Print the results
	/*cout << endl << "Results" << endl;
	for (int i = 0; i < leng; i++)
	{
		cout << "f" << i << ": " << vec[i].print() << " * (" << gen[i].print() << ")" << endl;
	}
	cout << "Remainder: " << vec[leng].print() << endl;
	cout << endl << "Returning..." << endl;*/
	return vec[leng];
}

//Generates the groebner basis using buchberger's algorithm without any improvements (i.e. polynomial pruning to create minimal or reduced groebner basis)
//Create a list of pairs, one for each combination of polynomial's.
//Then compute the syzygy polynomial. Divide it by the ideal polynomials. If the remainder is not zero, then add the polynomial and the new pairs into the list.
void Ideal::Groebner1()
{
	int t = gen.size();
	queue<int> l1, l2;
	for (int i = 0; i < t; i++)
	{
		for (int j = i; j < t; j++)
		{
			l1.push(i);
			l2.push(j);
		}
	}
	//The selection of the pair is just iterative, using a queue
	int inc = 0;//Increment this over the size of the list to obtain all pairs
	while (l1.size() > 0)
	{
		Polynomial p1 = gen[l1.front()];
		Polynomial p2 = gen[l2.front()];
		l1.pop(), l2.pop();//Pop the pair
		Monomial l = LCM(p1.poly[0], p2.poly[0]);
		Monomial m = p1.poly[0] * p2.poly[0];
		if (!equal(m, l))
		{
			Polynomial s = syzygy(p1, p2, compar);
			Polynomial rem = divR(s);
			if (rem.poly.size() != 0)
			{
				for (int i = 0; i < t; i++)
				{
					l1.push(i);
					l2.push(t);
				}
				gen.push_back(rem);
				t++;//There is now another polynomial
			}
		}
		
	}
}

//Buchberger with simple improvements
void Ideal::Groebner2()
{

}

//A selection sort to sort the monomials
//Used because monomial chains do not get too large
void selection(vector<Monomial> &poly, int(*compar)(const Monomial, const Monomial))
{
	int length = poly.size();
	for (int i = 0; i < length - 1; i++)//Last selection selects itself... so the array is already sorted by then
	{
		for (int j = i + 1; j < length; j++)
		{
			if (compar(poly[i], poly[j]) == -1)
			{
				Monomial swap = poly[j];
				poly[j] = poly[i];
				poly[i] = swap;
			}
		}
	}
}

//Lexographical comparison of monomials
int lex(const Monomial a, const Monomial b)
{
	for (int i = 0; i < size; i++)
	{
		if (a.powers[i] > b.powers[i])
		{
			return 1;
		}
		if (a.powers[i] < b.powers[i])
		{
			return -1;
		}
	}
return 0;//This never hits unless monomials equal degrees
}

int grl(const Monomial a, const Monomial b)
{
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < size; i++)
	{
		sum1 += a.powers[i];
		sum2 += b.powers[i];
	}
	if (sum1 > sum2)
		return 1;
	if (sum2 > sum1)
		return -1;
	return lex(a, b);//If total order is the same, then do a lex check on them
}

int grv(const Monomial a, const Monomial b)
{
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < size; i++)
	{
		sum1 += a.powers[i];
		sum2 += b.powers[i];
	}
	if (sum1 > sum2)
		return 1;
	if (sum2 > sum1)
		return -1;
	for (int i = size - 1; i >= 0; i--)//Now do a graded reverse lexographical comparison
	{
		if (a.powers[i] > b.powers[i])
		{
			return -1;
		}
		if (a.powers[i] < b.powers[i])
		{
			return 1;
		}
	}
	return 0;
}

void mPrint(vector<Monomial> poly){
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
	std::cout << app << endl;
}

int GCD(int a, int b)
{
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	while (true)
	{
		if (a == 0)
		{
			return b;
		}
		if (b == 0)
			return a;
		if (a > b)
			a = a%b;
		else
			b = b%a;
	}
}

//Flips signs of fractions numer and denom if appropriate
void signCheck(int& a, int&b)
{
	if (b < 0)
	{
		a *= -1;
		b *= -1;
		return;
	}
}

void pPrint(vector<Polynomial> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i].print() << " ";
	}
}