/*
	CStyle.h

	Realisierung einer C++ Klasse inclusive 
	Membermethoden in C

	Die Zugehörigkeit der Methoden zur Klasse wird durch 
	den this-Zeiger dokumentiert, der in C++ implizit als erstes
	Argument an eine Methode übergeben wird.
	Da der this-Zeiger nicht verändert werden darf, wird er const
	vom Datentyp A deklariert.

	Das C Äquivalent einer C++ Klasse ist ein struct.
	Ein struct verfügt aber weder über Methoden noch über Konstruktoren
	oder Destruktoren.
	Daher können diese nicht als Bestandteil des structs, sondern nur extern 
	deklariert werden.

	Autor: Gerhard Biebl
*/

// Implementierung der A Klasse in C Syntax
struct A
{
	int a;
	int counter;
};

// C Implementierung der Methoden der Klasse A
// Hier: Konstruktor
void A_CTOR ( A * const _this, int a )
{
	_this->a = a;
	_this->counter = 0;
}

// Methode setA
void setA ( A * const _this, int a )
{
	_this->a = a;
}

// Methode getA
// Umsetzung von C++ mutable Attribut durch const casting
int getA ( const A * const _this )
{
	++((A * const) _this)->counter;
	return _this->a;
}

// Methode getCounter
int getCounter ( const A * const _this )
{
	return _this->counter;
}
