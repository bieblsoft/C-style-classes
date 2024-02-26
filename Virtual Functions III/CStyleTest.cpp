#include "CStyle.h"
#include <iostream>
using namespace std;

void main()
{
	// Anlegen eines Objektes der Klasse A
	// Die beiden Schritte entsprechen dem normalen
	// C++ Instanzierungsvorgang
	// 1. Schritt: Definition ( Speicher wird zugewiesen )
	A a;
	// 2. Schritt: Initialisierung ( Objekt wird initialisiert )
	A_CTOR(&a, 100);

	// Referenz auf Objekt der Klasse A
	const A& ra = a;

	// Neu: Aufruf der virtuellen Funktionen
	A* pA = &a;

	virtual_F1( pA );
	virtual_F2( pA );

	// Daten abrufen
	cout << "Inhalt von a: " << getA ( &ra ) << endl;

	cout << "Funktion getA wird insgesamt 4x aufgerufen" << endl;
	getA ( &ra );
	getA ( &ra );
	getA ( &ra );

	// Funktionszähler beauskunften ( Anzahl der Aufrufe von getA )
	cout << "Anzahl Funktionsaufrufe: " << getCounter ( &ra ) << endl;

	// Instanzierung eines Objektes der von A abstammenden Klasse B
	B b;
	B_CTOR(&b, 2, 5);

	// Referenz auf Objekt der Klasse B
	const B& rb = b;

	// Aufruf der virtuellen Funktionen
	A* pB = (A*) &b;

	virtual_F1( pB );
	virtual_F2( pB );

	// Daten abrufen
	cout << "Inhalt von a: " << getA ( (A*) &rb ) << endl;
	cout << "Inhalt von b: " << getB ( &rb ) << endl;

	cout << "3x Aufruf der Funktion getA des in B enthaltenen A Objektes" << endl;

	// Aufruf der Methode A::getA ( A* _this, int a )
	// der typecast wandelt b explizit in Typ A um
	getA ( (A*) &rb );
	getA ( (A*) &rb );

	// Funktionszähler beauskunften ( Anzahl der Aufrufe von getA )
	cout << "Anzahl Funktionsaufrufe in b: " << getCounter ( &rb ) << endl;

}

