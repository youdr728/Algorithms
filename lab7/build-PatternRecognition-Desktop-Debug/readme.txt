/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150       0.027 s      00000
    200       0.075 s
    300       0.228 s
    400       0.527 s
    800       4.077 s
   1600      32.236 s      2.555 s
   3200     500.000 s
   6400    2500.000 s
  12800   15000.000 s


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: Worst case : O(n?) eftersom den har 4 for-loopar i varandra

Sortering:
