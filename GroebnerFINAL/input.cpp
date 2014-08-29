#include "classes.h"

Ideal idealParse(string fileName);
Polynomial polyParse(string fileName);
Ideal idealParse(string fileName, string order);
Polynomial polyParse(string fileName, string order);
Monomial monomialParse(string line);

int main(){

	/*Polynomial p = polyParse("p1.txt");
	Polynomial q = polyParse("p2.txt");
	Polynomial s = syzygy(p, q, grl);
	cout << p.print() << endl;
	cout << q.print() << endl;
	cout << s.print() << endl;*/

	Ideal ide1 = idealParse("i1.txt");
	ide1.print();
	ide1.Groebner1();
	ide1.print();

	Ideal ide2 = idealParse("i2.txt");
	ide2.Groebner1();
	ide2.print();

	/*Monomial m1 = LCM(p.poly[0], p.poly[1]);
	Monomial m2 = GCD(p.poly[0], p.poly[1]);

	cout << m1.print(1) << endl << m2.print(1) << endl;*/

	//Polynomial d = polyParse("d1.txt");

	//vector<Polynomial> res = ide.div(d);
	//vector<Polynomial> res2 = ide.div(p);

	//Polynomial res3 = ide.divR(d);
	//Polynomial res4 = ide.divR(p);

	//cout << res4.poly.size() << endl;

	cout << "End of Program" << endl;

	cin.ignore();

}

//Creates an ideal from a file
Ideal idealParse(string fileName)
{
	vector<Polynomial> vec;
	string line, order;
	ifstream myfile(fileName);

	if (myfile.is_open())
	{
		getline(myfile, order);//Get the ordering of the monomials
		getline(myfile, line);//Retrieve number of variables in field
		int newSize = stoi(line);
		if (newSize != size)
		{
			//cout << "Setting/Different variable number!\n";
		}
		getline(myfile, line);//Retrieve whether to change the number
		int setSize = stoi(line);
		if (setSize == 1)
			size = newSize;
		while (!myfile.eof())
		{
			getline(myfile, line);//Retrieve variables in field
			vector<Monomial> poly;
			while (line != "")
			{
				Monomial a = monomialParse(line);
				poly.push_back(a);
				if (myfile.eof())//Break after adding the monomial to the vector
					break;
				getline(myfile, line);//Retrieve new Monomial
			}
			Polynomial p(poly);
			vec.push_back(p);//Add the new polynomial
		}
		myfile.close();
	}
	return Ideal(vec, order);
}

//Creates a polynomial from a file
Polynomial polyParse(string fileName)
{
	vector<Monomial> poly;
	string line;
	ifstream myfile(fileName);

	if (myfile.is_open())
	{
		getline(myfile, line);//Retrieve number of variables in field
		int newSize = stoi(line);
		if (newSize != size)
		{
			//cout << "Setting/Different variable number!\n";
		}
		getline(myfile, line);//Retrieve whether to change the number
		int setSize = stoi(line);
		if (setSize == 1)
			size = newSize;
		while (getline(myfile, line))
		{
			Monomial a = monomialParse(line);
			poly.push_back(a);
		}
		myfile.close();
	}
	return Polynomial(poly);
}


//Creates an ideal from a file
Ideal idealParse(string fileName, string ord)
{
	vector<Polynomial> vec;
	string line, order;
	ifstream myfile(fileName);

	if (myfile.is_open())
	{
		getline(myfile, order);//Get the ordering of the monomials
		getline(myfile, line);//Retrieve number of variables in field
		int newSize = stoi(line);
		if (newSize != size)
		{
			//cout << "Setting/Different variable number!\n";
		}
		getline(myfile, line);//Retrieve whether to change the number
		int setSize = stoi(line);
		if (setSize == 1)
			size = newSize;
		while (!myfile.eof())
		{
			getline(myfile, line);//Retrieve variables in field
			vector<Monomial> poly;
			while (line != "")
			{
				Monomial a = monomialParse(line);
				poly.push_back(a);
				if (myfile.eof())//Break after adding the monomial to the vector
					break;
				getline(myfile, line);//Retrieve new Monomial
			}
			Polynomial p(poly);
			p.sort(order);
			vec.push_back(p);//Add the new polynomial
		}
		myfile.close();
	}
	return Ideal(vec, order);
}

//Creates a polynomial from a file
Polynomial polyParse(string fileName, string ord)
{
	vector<Monomial> poly;
	string line;
	ifstream myfile(fileName);

	if (myfile.is_open())
	{
		getline(myfile, line);//Retrieve number of variables in field
		int newSize = stoi(line);
		if (newSize != size)
		{
			//cout << "Setting/Different variable number!\n";
		}
		getline(myfile, line);//Retrieve whether to change the number
		int setSize = stoi(line);
		if (setSize == 1)
			size = newSize;
		while (getline(myfile, line))
		{
			Monomial a = monomialParse(line);
			poly.push_back(a);
		}
		myfile.close();
	}
	Polynomial p(poly);
	p.sort(ord);
	return p;
}

//Returns a monomial from the line parsed
Monomial monomialParse(string line)
{
	int inc = 0;//Position of the reader
	string a, b;//The fractions
	char cur;//Current value
	bool frac = false, neg = false;
	while (true)
	{
		cur = line[inc];
		inc++;
		if (cur == ' ')//The coefficient is read
			break;
		if (cur == '/')
			frac = true;
		if ((cur >= '0' && cur <= '9') || cur == '-')
		{
			if (frac)
				b += cur;
			else
				a += cur;
		}
	}
	int numer = stoi(a), denom;
	if (frac)//If the input number was a fraction
		denom = stoi(b);
	else
		denom = 1;
	Rational rat(numer, denom);
	vector<int> powers;
	string conv;//Holds the value to convert to an int
	while (true)
	{
		if (inc == line.size())
		{
			powers.push_back(stoi(conv));
			break;
		}
		cur = line[inc];
		inc++;
		if (cur == ' ')//The coefficient is read
		{
			powers.push_back(stoi(conv));
			conv = "";//Make it the null string again
		}
		if (cur >= '0' && cur <= '9')
			conv += cur;
	}
	return Monomial(rat, powers);//Add this to the vector of monomials, to create the polynomial
}
