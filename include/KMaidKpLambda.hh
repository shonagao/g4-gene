/*
Kaon MAID 
http://wwwkph.kph.uni-mainz.de/MAID//kaon/
*/

#ifndef KMaidKpLambda_h
#define KMaidKpLambda_h 1

#include "CSTable.hh"

class KMaidKpLambda : public CSTable
{
public:
  KMaidKpLambda();
  virtual ~KMaidKpLambda();

  virtual double CS( double w, double cost ) const;

private:
  const static double CStbl[33][37];
  const static double Wtbl[33], Costtbl[37];


};

#endif
