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

	2. Teil: Vererbung in C

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


// Vererbung: Die Klasse B wird von der Klasse A abgeleitet
// Klasse B
struct B
{
	// Wie bei der C++ Instanzierung enthält das B-Objekt
	// ein A-Objekt ( Containment )
	A Objekt_A;
	int b;
};

// C Implementierung der Methoden der Klasse A
// Hier: Konstruktor
void B_CTOR ( B * const _this, int b )
{
	_this->b = b;
	_this->Objekt_A.counter = 0;
}

// Methode setA
void setB ( B * const _this, int b )
{
	_this->b = b;
}

// Methode getB
int getB ( const B * const _this )
{
	// Nachfolgende Zeile wäre eine nicht-virtuelle Methode
	// es wird der Counter der Basisklasse zurückgegeben
	//++((B * const) _this)->Objekt_A.counter;
	return _this->b;
}

// Überschriebene Methode
// Methode getCounter
int getCounter ( const B * const _this )
{
	return _this->Objekt_A.counter;
}
