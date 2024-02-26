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
	// oder im Heap:
	A* pa = (A*) malloc(sizeof (A));

	// 2. Schritt: Initialisierung ( Objekt wird initialisiert )
	A_CTOR(&a, 100);
	// dasselbe im Heap:
	A_CTOR(pa, 200);

	// Referenz auf Objekt der Klasse A im Stack
	const A& ra = a;
	// oder im Heap_
	const A& rpa = *pa;

	// Daten abrufen
	cout << "Inhalt von a: " << getA ( &ra ) << endl;

	cout << "Funktion getA wird insgesamt 4x aufgerufen" << endl;
	getA ( &ra );
	getA ( &ra );
	getA ( &ra );

	// Funktionszähler beauskunften ( Anzahl der Aufrufe von getA )
	cout << "Anzahl Funktionsaufrufe: " << getCounter ( &ra ) << endl;
}