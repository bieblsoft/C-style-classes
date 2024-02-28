#include "CStyle.h"
#include <iostream>
using namespace std;

void main()
{
	// Instanzierung eines Objektes der von A abstammenden Klasse B
	B b;
	B_CTOR(&b, 2, 5);

	// Aufruf des virtuellen Destruktors des Objektes b mit einem Pointer der Klasse a
	// Wäre dies nicht gewährleistet, entstünde eine Speicherlücke, da zwar das Objekt a zerstört würde, 
	// nicht aber das umgebende Objekt der Klasse b !
	A_Destructor((A*) &b);
}

