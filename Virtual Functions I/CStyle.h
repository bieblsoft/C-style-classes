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

	3. Teil: Virtuelle Methoden in C
*/
#include <iostream>
using namespace std;

// Implementierung der virtuellen Sprungtabelle (vTable)
struct vtable
{
	// mit typedef wird T_pFn defieniert als 
	// Funktionspointer void (* T_pFn) (void)
	typedef void (* T_pFn) ();
	// Deklaration eines Funktionsarrays für zwei
	// virtuelle Funktionen
	T_pFn fnArr[2];
};

// Implementierung der A Klasse in C Syntax
struct A
{
	const vtable* pVTable;
	int a;
	int counter;
};

// Die in der virtuellen Sprungtabelle gespeicherten Funktionspointer
// werden benutzt, um die zugehörigen Funktionen aufzurufen
// virtueller call von Funktion X_F1
void virtual_F1 ( A* const _this )
{
	( _this->pVTable->fnArr[0] ) ();
}

// virtueller call von Funktion X_F2
void virtual_F2 ( A* const _this )
{
	( _this->pVTable->fnArr[1] ) ();
}

void A_F1()
{
	cout << "A::F1()" << endl;
}

void A_F2()
{
	cout << "A::F2()" << endl;
}

// C Implementierung der Methoden der Klasse A
// Hier: Konstruktor
void A_CTOR ( A * const _this, int a )
{
	// Deklaration einer virtuellen Sprungtabelle
	// und Initialisierung mit den Adressen der
	// virtuellen Funktionen F1 und F2
	static const vtable aVTable = { &A_F1, &A_F2 };
	// Zuweisung der vtable an das Objekt
	_this->pVTable = &aVTable;

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
	// ein A-Objekt
	A Objekt_A;
	int b;
};

void B_F1()
{
	cout << "B::F1()" << endl;
}

void B_F2()
{
	cout << "B::F2()" << endl;
}

// C Implementierung der Methoden der Klasse A
// Hier: Konstruktor
void B_CTOR ( B * const _this, int b )
{
	// Deklaration einer virtuellen Sprungtabelle
	// und Initialisierung mit den Adressen der
	// virtuellen Funktionen F1 und F2
	static const vtable bVTable = { &B_F1, &B_F2 };
	// Zuweisung der vtable an das Objekt
	((A*)_this)->pVTable = &bVTable;

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
