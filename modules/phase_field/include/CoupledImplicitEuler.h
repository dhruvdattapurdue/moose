#ifndef COUPLEDIMPLICITEULER
#define COUPLEDIMPLICITEULER

#include "Kernel.h"

// Forward Declaration
class CoupledImplicitEuler;

template<>
InputParameters validParams<CoupledImplicitEuler>();

class CoupledImplicitEuler : public Kernel
{
public:

  CoupledImplicitEuler(const std::string & name, InputParameters parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  VariableValue & _v_dot;
  unsigned int _v_var;
  

};
#endif //IMPLICITEULER
