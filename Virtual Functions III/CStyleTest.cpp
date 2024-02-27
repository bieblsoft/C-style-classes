#include "CStyle.h"
#include <iostream>
using namespace std;

void main()
{
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

	// Aufruf des virtuellen Destruktors des Objektes b mit einem Pointer der Klasse a
	// Wäre dies nicht gewährleistet, entstünde eine Speicherlücke, da zwar das Objekt a zerstört würde, 
	// nicht aber das umgebende Objekt der Klasse b !
	A_Destructor(pB);
}

