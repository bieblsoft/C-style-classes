/*
	CStyle.h

	Realisierung einer C++ Klasse inclusive 
	Membermethoden in C

	3. Teil: Virtuelle Methoden in C
*/
#include <iostream>
using namespace std;

// Prototypendeklaration für struct A
// nicht nötig, wenn vtable als innere struct von A
// deklariert wird
struct A;

// Implementierung der virtuellen Sprungtabelle (vTable)
struct vtable
{
	// mit typedef wird T_pFn defieniert als 
	// Funktionspointer void (* T_pFn) (void)
	typedef void (* T_pFn) ( const A* const _this );
	// Deklaration eines Funktionspointer arrays für drei
	// virtuelle Funktionen - F1, F2, und neu: der virtuelle Destruktor !
	T_pFn fnArr[3];
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
void virtual_F1(A* const _this)
{
	(_this->pVTable->fnArr[1]) (_this);
};

// virtueller call von Funktion X_F2
void virtual_F2(A* const _this)
{
	(_this->pVTable->fnArr[2]) (_this);
};

void A_F1(const A* const _this)
{
	cout << "A::F1()" << endl;
};

void A_F2(const A* const _this)
{
	cout << "A::F2()" << endl;
};

// C Implementierung der Methoden der Klasse A
// Hier: Konstruktor
void A_CTOR(A* const _this, int a)
{
	// Deklaration einer virtuellen Sprungtabelle
	// und Initialisierung mit den Adressen der
	// virtuellen Funktionen F1 und F2
	static const vtable aVTable = { &A_F1, &A_F2 };

	// Zuweisung der vtable an das Objekt
	_this->pVTable = &aVTable;

	_this->a = a;
	_this->counter = 0;
};

// Methode setA
void setA(A* const _this, int a)
{
	_this->a = a;
};

// Methode getA
int getA(const A* const _this)
{
	++((A* const)_this)->counter;
	return _this->a;
};

// Methode getCounter
int getCounter(const A* const _this)
{
	return _this->counter;
};


// Vererbung: Die Klasse B wird von der Klasse A abgeleitet
// Klasse B
struct B
{
	// Wie bei der C++ Instanzierung enthält das B-Objekt
	// ein A-Objekt. Hier als pointer auf das Objekt im Heap.
	// wenn dieses Objekt mittels pointer auf A zerstört würde, ohne dass nachfolgend der Destuktor von B 
	// ausgeführt wird, könnte immer noch über diesen Zeiger auf den Speicherort zugegriffen werden,
	// obwohl das A-Objekt dort schon gar nicht mehr existiert. 
	// Schlimmer noch: dies führt nicht zu einer Exception und das Programm stürzt auch nicht ab !
	A* pObjekt_A;
	int b;
};

// Destruktor der Klasse A
// muss hier auf die Deklaration der strukt B folgen, da der Compiler diese sonst nicht erkennt
void A_Destructor(A* const _this)
{
	cout << "Aufruf des Destruktors der Basis-Klasse" << endl;
	// Da sowohl a als auch counter Member-Variablen primitiver Datentype von A sind,
	// muss hier nichts erledigt werden.
	// Dies wäre nur dann der Fall, wenn a oder counter entweder komplexe Datentypen wären, 
	// oder über pointer referenziert würden. In diesen Fällen müssten die pointer ungültig 
	// (nullptr) gemacht werden nachdem die Destruktoren der komplexen Datentypen aufgerufen wurden

	// Allerdings haben wir hier virtualität vorliegen, es soll also ein Objekt der Klasse b 
	// mit einem Basisklassen-Zeiger zerstört werden.
	// Daher wird der Destruktor-Aufruf über die Virtuelle Sprungtabelle umgeleitet:
	_this->pVTable->fnArr[0]( _this);
	// Dies erledigt auch mal wieder der C++ Compiler für uns
};

void B_F1(const B* const _this)
{
	cout << "B::F1()" << endl;
};

void B_F2(const B* const _this)
{
	cout << "B::F2()" << endl;
};

// C Implementierung der Methoden der Klasse B

// Destruktor von Klasse B
// wird hier vor dem Konstruktor deklariert, sonst wäre eine Prototypen-Deklaration nötig
void B_Destructor(B* const _this)
{
	cout << "Aufruf des Destruktors der abgeleiteten Klasse" << endl;
	// ohne virtuellen Destruktor würde der pointer immer noch auf das jetzt zerstörte Objekt zeigen !
	(A*)_this->pObjekt_A = nullptr;
};

// Hier: Konstruktor
void B_CTOR(B* const _this, int a, int b)
{
	typedef void (*T_pFn) (const A* const _this);
	static const vtable bVTable =
	{
		(T_pFn)(&B_Destructor),
		(T_pFn)(&B_F1),
		(T_pFn)(&B_F2)
	};

	// Instanzierung des A-Objektes im Heap
	//_this->pObjekt_A = new A(); 
	// oder C-Sprech: 
	_this->pObjekt_A = (A*) malloc( sizeof(A) );
	// Benutzung des Konstruktors der Klasse A 
	// zur Initialisierung der Basisklasse
	A_CTOR((A*)_this->pObjekt_A, a);

	// Zuweisung der vtable an das Objekt
	((A*)_this)->pVTable = &bVTable;

	_this->b = b;
};

// Methode setB
void setB(B* const _this, int b)
{
	_this->b = b;
};

// Methode getB
int getB(const B* const _this)
{
	// Nachfolgende Zeile wäre eine nicht-virtuelle Methode
	// es wird der Counter der Basisklasse zurückgegeben
	//++((B * const) _this)->Objekt_A.counter;
	return _this->b;
};

// Methode getCounter
int getCounter(const B* const _this)
{
	return _this->pObjekt_A->counter;
};
