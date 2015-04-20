/**
 * Heap Sort implementation
 * 
 * This was found on an old drive and provided as is.
 *
 *
 * Thomas Gouverneur - 2003
 */
#include <stdio.h>
#include "llu.h"

template < class t > void paterner(LLU <t>*ips, int inf, int sup)
{
    int ipere = inf;
    int ifils = ipere * 2;

    while (ifils <= sup) {
	if (ifils < sup
	    && (ips->Get(ifils + 1) > ips->Get(ifils)))
	    ifils++;

	if (ips->Get(ifils) > ips->Get(ipere)) {
	    ips->Swap(ipere, ifils);

	    ipere = ifils;
	    ifils = ipere * 2;
	} else
	    break;
    }
    return;
}


template < class t > void heapsort(LLU <t>*llu, int n)
{
    for (int i = n / 2; i >= 1; i--)
	paterner(llu, i, n);

    llu->Swap(1, n);
    for (int i = n - 1; i; i--) {
	paterner(llu, 1, i);
	llu->Swap(1, i);
    }
    return;
}

int main (void) {
  LLU<int> test;
  test.Push(42);
  test.Push(128);
  test.Push(412);
  test.Push(645);
  test.Push(99);
  test.Push(32);
  test.Push(12);
  test.Push(23);
  test.Push(76);
  test.Push(2);
  test.Push(472);
  test.Push(918);
  test.Push(24);
  test.Push(76);
  test.Push(52);
  test.Push(12);
  test.Push(372);
  for (int i=0;i<test.Size(); i++) {
    printf("test[%d]: %d\n", i, test[i]);
  }
  heapsort(&test, test.Size()-1);
  for (int i=0;i<test.Size(); i++) {
    printf("test[%d]: %d\n", i, test[i]);
  }
  
  return 0;
}
