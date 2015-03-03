/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef POLYCRYSTALVARIABLESACTION_H
#define POLYCRYSTALVARIABLESACTION_H

#include "InputParameters.h"
#include "Action.h"

/**
 * Automatically generates all variables to model a polycrystal with op_num orderparameters
 */
class PolycrystalVariablesAction: public Action
{
public:
  PolycrystalVariablesAction(const std::string & name, InputParameters params);

  virtual void act();

private:
  static const Real _abs_zero_tol;

  unsigned int _op_num;
  std::string _var_name_base;
};

template<>
InputParameters validParams<PolycrystalVariablesAction>();

#endif //POLYCRYSTALVARIABLESACTION_H
