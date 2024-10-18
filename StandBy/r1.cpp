#include "lista.h"

int lcm(TElem e1, TElem e2, TElem a, TElem b);

int lcmmultiple(PNod nod) {
	if (nod == nullptr){
		return 0;
	}

	if (nod->urm == nullptr)
	{
		return nod->e;
	}
	
	int res = lcmmultiple(nod->urm);
	return lcm(nod->e, res, nod->e, res);

}

int lcm(TElem e1, TElem e2, TElem a, TElem b) {
	if (e1 < e2) {
		lcm(e1 + a, e2, a, b);
	}
	else if (e1 > e2){
		lcm(e1, e2 + b, a, b);
	}
	else {
		return e1;
	}
}

