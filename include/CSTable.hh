/*
CSTable.hh

*/

#ifndef CSTable_h 
#define CSTable_h 1

#include <string>

class CSTable
{
public:
  CSTable( const std::string name )
    : ModelName_(name) {}
  virtual ~CSTable() {}

  const std::string & ModelName( void ) const { return ModelName_; }

  virtual double CS( double w, double cost ) const = 0;
//  virtual double CS( double w, double cost );

private:
  std::string ModelName_;
};

#endif

