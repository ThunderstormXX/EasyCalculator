#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <exception>
using namespace std;

class Rational {
private:
  int p = 0;
  int q = 1;
int mod(int a) {return( (a > 0)? a : -a);}
public:

  Rational(){};
  Rational(int numerator, int denominator) {
    if( denominator == 0 ) {
      throw invalid_argument("Invalid argument");
    }
    int a = mod(numerator) , b = mod(denominator) , nod;
    while (a > 0 && b > 0) {
      if (a > b) {
        a %= b;
      } else {
        b %= a;
      }
    }
    nod = a + b;
    p = numerator / nod ;
    q = denominator / nod;
    if( p == 0) q = 1;
    if( q < 0 ) {
      p = -p;
      q = -q;
    }
  }
  string Print() const {
    return to_string(p) + "/" + to_string(q);
  }
  int Numerator() const {
    return p;
  };
  int Denominator() const {
    return q;
  };
  
  Rational operator +( Rational x ) const {
    return Rational(x.Numerator()*q + x.Denominator()*p, x.Denominator()*q);
  }
  Rational operator -( Rational x ) const {
    return Rational(-x.Numerator()*q + x.Denominator()*p, x.Denominator()*q);
  }
  Rational operator *( Rational x ) const {
    return Rational(p*x.Numerator() , q*x.Denominator());
  }
  Rational operator /( Rational x ) const {
    if( x.Numerator() == 0) {
      throw domain_error("Division by zero");
    }
    return Rational(p*x.Denominator(),q*x.Numerator());
  }
  bool operator == ( Rational x) const {
    return ((x.Numerator() == p) &&( x.Denominator() == q));
  }
  bool operator< (Rational x) const {
    return(p*x.Denominator() < x.Numerator()*q);
  }
  bool operator> (Rational x) const {
    return(p*x.Denominator() > x.Numerator()*q);
  }
    
};

istream& operator>>( istream& stream , Rational& x) {
  int p = 0 , q = 1 ;
  char c;
  if((stream >> p) &&(stream >> c )&& (stream >> q)&& (c == '/') ) {
    x = {p,q};
  }
  return stream;
}

ostream& operator<<( ostream& stream , const Rational& r) {
  stream << r.Numerator() << "/" << r.Denominator();
  return stream;
}

void OperationTwoRational (char c , const Rational& x , const Rational& y) {
    switch(c) {
      case '+':
        cout << x + y ;
        break;
      case '*':
        cout << x * y ;
        break;
      case '/':
        cout << x / y ;
        break;
      case '-':
        cout << x - y ;
        break;
    }
}

int main() {
  try {
    Rational x , y ;
    char c ;
    cin >> x >> c >> y; ;
    OperationTwoRational(c , x , y );
  }
  catch( exception& ex ) {
    cout << ex.what();
  }
  return 0;
}
