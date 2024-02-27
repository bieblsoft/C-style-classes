/*
	CStyle.h

	Realisierung einer C++ Klasse inclusive 
	Membermethoden in C

	Die Zugeh�rigkeit der Methoden zur Klasse wird durch 
	den this-Zeiger dokumentiert, der in C++ implizit als erstes
	Argument an eine Methode �bergeben wird.
	Da der this-Zeiger nicht ver�ndert werden darf, wird er const
	vom Datentyp A deklariert.

	Das C �quivalent einer C++ Klasse ist ein struct.
	Ein struct verf�gt aber weder �ber Methoden noch �ber Konstruktoren
	oder Destruktoren.
	Daher k�nnen diese nicht als Bestandteil des structs, sondern nur extern 
	deklariert werden.

	3. Teil: Virtuelle Methoden in C
*/
#include <iostream>
using namespace std;

// Prototypendeklaration f�r struct A
// nicht n�tig, wenn vtable als innere struct von A
// deklariert wird
struct A;

// Implementierung der virtuellen Sprungtabelle (vTable)
struct vtable
{
	// mit typedef wird T_pFn defieniert als 
	// Funktionspointer void (* T_pFn) (void)
	typedef void (* T_pFn) ( const A* const _this );
	// Deklaration eines Funktionsarrays f�r drei
	// virtuelle Funktionen - F1, F2, und der virtuelle Destruktor !
	T_pFn fnArr[3];
};

// Implementierung der A Klasse in C Syntax
struct A
{
	/*
	// Implementierung der virtuellen Sprungtabelle (vTable)
	// als Bestandteil der Klase A
	struct vtable
	{
		// mit typedef wird T_pFn defieniert als 
		// Funktionspointer void (* T_pFn) (void)
		typedef void (* T_pFn) ( const A* const _this );
		// Deklaration eines Funktionsarrays f�r zwei
		// virtuelle Funktionen
		T_pFn fnArr[3];
	};
	*/

	const vtable* pVTable;
	int a;
	int counter;
};

// Die in der virtuellen Sprungtabelle gespeicherten Funktionspointer
// werden benutzt, um die zugeh�rigen Funktionen aufzurufen
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

	// wenn vtable als innere struct von A
	// deklariert wird:
	// static const A::vtable aVTable = { &A_F1, &A_F2};

	// sonst:
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
	// Wie bei der C++ Instanzierung enth�lt das B-Objekt
	// ein A-Objekt
	A Objekt_A;
	int b;
};

// Destruktor der Klasse A
// muss hier auf die Deklaration der strukt B folgen, da der Compiler diese sonst nicht erkennt
void A_Destructor(A* const _this)
{
	cout << "Aufruf des Destruktors der Basis-Klasse" << endl;
	// Da sowohl a als auch counter Member-Variablen primitiver Datentype von A sind,
	// muss hier nichts erledigt werden.
	// Dies w�re nur dann der Fall, wenn a oder counter entweder komplexe Datentypen w�ren, 
	// oder �ber pointer referenziert w�rden. In diesen F�llen m�ssten die pointer ung�ltig 
	// (nullptr) gemacht werden nachdem die Destruktoren der komplexen Datentypen aufgerufen wurden

	// Allerdings haben wir hier virtualit�t vorliegen, es soll also ein Objekt der Klasse b 
	// mit einem Basisklassen-Zeiger zerst�rt werden.
	// Daher wird der Destruktor-Aufruf �ber die Virtuelle Sprungtabelle umgeleitet:
	_this->pVTable->fnArr[0](_this);
	// Dies erledigt auch mal wieder der C++ Compiler f�r uns
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
// wird hier vor dem Konstruktor deklariert, sonst w�re eine Prototypen-Deklaration n�tig
void B_Destructor(B* const _this)
{
	cout << "Aufruf des Destruktors der abgeleiteten Klasse" << endl;
};

// Hier: Konstruktor
void B_CTOR(B* const _this, int a, int b)
{
	// Deklaration einer virtuellen Sprungtabelle
	// und Initialisierung mit den Adressen der
	// virtuellen Funktionen F1 und F2
	// F�r die �bergabe eines this-Zeigers des B-Objektes
	// muss ein Typecast f�r den Funktionstyp vorgenommen werden:

	// wenn vtable als innere struct von A
	// deklariert wird:
	// static const A::vtable bVTable = { 
	//	(A::vtable::T_pFn) (&B_F1), 
	//	(A::vtable::T_pFn) (&B_F2) };
	// sonst:
	//static const vtable bVTable = { 
	//	(vtable::T_pFn) (&B_F1), 
	//	(vtable::T_pFn) (&B_F2) };

	// Das funktioniert so nur mit einem C++/C Compiler; wenn man einen
	// alten pure C Compiler hat, kennt der nat�rlich keine Namespaces und kann mit dem
	// scope resolution operator nichts anfangen ! Daher:
	typedef void (*T_pFn) (const A* const _this);
	static const vtable bVTable =
	{
		(T_pFn)(&B_Destructor),
		(T_pFn)(&B_F1),
		(T_pFn)(&B_F2)
	};

	// Benutzung des Konstruktors der Klasse A 
	// zur Initialisierung der Basisklasse
	A_CTOR((A*)_this, a);

	// Zuweisung der vtable an das Objekt
	((A*)_this)->pVTable = &bVTable;

	_this->Objekt_A.a = a;
	_this->b = b;
	_this->Objekt_A.counter = 0;
};

// Methode setA
void setB(B* const _this, int b)
{
	_this->b = b;
};

// Methode getB
int getB(const B* const _this)
{
	// Nachfolgende Zeile w�re eine nicht-virtuelle Methode
	// es wird der Counter der Basisklasse zur�ckgegeben
	//++((B * const) _this)->Objekt_A.counter;
	return _this->b;
};

// �berschriebene Methode
// Methode getCounter
int getCounter(const B* const _this)
{
	return _this->Objekt_A.counter;
};
