# Strain Formulations in Tensor Mechanics

The tensor mechanics module offers three different types of strain calculation: Small linearized total strain, small linearized incremental strain, and finite incremental strain.

## Small Linearized Total Strain

For linear elasticity problems, the Tensor Mechanics module includes a small strain and total strain material [ComputeSmallStrain](/ComputeSmallStrain.md).  This material is useful for verifying material models with hand calculations because of the simplified strain calculations.

Linearized small strain theory assumes that the gradient of displacement with respect to position is much smaller than unity, and the squared displacement gradient term is neglected in the small strain definition to give:
\begin{equation}
\epsilon = \frac{1}{2} \left( u \nabla + \nabla u \right) \quad when \quad \frac{\partial u}{ \partial x} << 1
\end{equation}
For more details on the linearized small strain assumption and derivation, see a Continuum Mechanics text such as [cite:malvern1969introduction] or [cite:bower2009applied], specifically [Chapter 2](http://solidmechanics.org/Text/Chapter2_1/Chapter2_1.php#Sect2_1_7).

Total strain theories are path independent: in MOOSE, path independence means that the total strain, from the beginning of the entire simulation, is used to calculate stress and other material properties.  Incremental theories, on the other hand, use the increment of strain at timestep to calculate stress.  Because the total strain formulation `ComputeSmallStrain` is path independent, no old values of strain or stress from the previous timestep are stored in MOOSE.  For a comparison of total strain vs incremental strain theories with experimental data, see [cite:shammamy1967incremental].

The input file syntax for small strain is

!listing modules/tensor_mechanics/tutorials/basics/part_1.1.i block=Modules/TensorMechanics/Master
end=stress

## Incremental Small Strains

Applicable for small linearized strains, MOOSE includes an incremental small strain material, [ComputeIncrementalSmallStrain](/ComputeIncrementalSmallStrain.md).  As in the small strain material, the incremental small strain class assumes the gradient of displacement with respect to position is much smaller than unity, and the squared displacement gradient term is neglected in the small strain definition to give:
\begin{equation}
\epsilon = \frac{1}{2} \left( u \nabla + \nabla u \right) \quad when \quad \frac{\partial u}{ \partial x} << 1
\end{equation}
As the class name suggests, `ComputeIncrementalSmallStrain` is an incremental formulation.  The stress increment is calculated from the current strain increment at each time step.  In this class, the rotation tensor is defined to be the rank-2 Identity tensor: no rotations are allowed in the model. Stateful properties, including `strain_old` and `stress_old`, are stored. This incremental small strain material is useful as a component of verifying more complex finite incremental strain-stress calculations.

The input file syntax for incremental small strain is

!listing modules/tensor_mechanics/test/tests/thermal_expansion/constant_expansion_coeff.i block=Modules/TensorMechanics


## Finite Large Strains

For finite strains, use [ComputeFiniteStrain](/ComputeFiniteStrain.md) in which an incremental form is employed such that the strain increment and the rotation increment are calculated.

### Incremental Deformation Gradient

The finite strain mechanics approach used in the MOOSE tensor_mechanics module is the incremental corotational form from [cite:rashid1993incremental]. In this form, the generic time increment under consideration is such that $t \in [t_n, t_{n+1}]$. The
configurations of the material element under consideration at $t = t_n$ and $t = t_{n+1}$ are denoted
by $\kappa_n$, and $\kappa_{n + 1}$, respectively. The incremental motion over the time increment is
assumed to be given in the form of the inverse of the deformation gradient $\hat{\mathbf{F}}$ of
$\kappa_{n + 1}$ with respect to $\kappa_n$, which may be written as

\begin{equation}
\hat{\mathbf{F}}^{-1} = 1 - \frac{\partial \hat{\mathbf{u}}}{\partial \mathbf{x}},
\end{equation}
where $\hat{\mathbf{u}}(\mathbf{x})$ is the incremental displacement field for the time step, and
$\mathbf{x}$ is the position vector of materials points in $\kappa_{n+1}$. Note that
$\hat{\mathbf{F}}$ is NOT the deformation gradient, but rather the incremental deformation gradient
of $\kappa_{n+1}$ with respect to $\kappa_n$. Thus,
\begin{equation}
\hat{\mathbf{F}} = \mathbf{F}_{n+1} \mathbf{F}_n^{-1}
\end{equation}
where $\mathbf{F}_n$ is the total deformation gradient at time $t_n$.

For this form, we assume
\begin{equation}
\begin{aligned}
\dot{\mathbf{F}} \mathbf{F}^{-1} =& \mathbf{D}\ \mathrm{(constant\ and\ symmetric),\ } t_n<t<t_{n+1}\\
\mathbf{F}(t^{-}_{n+1}) =& \hat{\mathbf{U}}\ \mathrm{(symmetric\ positive\ definite)}\\
\mathbf{F}(t_{n+1}) =& \hat{\mathbf{R}} \hat{\mathbf{U}} = \hat{\mathbf{F}}\ (\hat{\mathbf{R}}\ \mathrm{proper\ orthogonal})
\end{aligned}
\end{equation}

In tensor mechanics, there are two decomposition options to obtain the strain increment: TaylorExpansion and EigenSolution, with the default set to TaylorExpansion. See the
[ComputeFiniteStrain](/ComputeFiniteStrain.md) for a description of both decomposition options.

### Volumetric Locking Correction

In [ComputeFiniteStrain](/ComputeFiniteStrain.md) $\hat{\mathbf{F}}$ is calculated and can optionally include a volumetric locking correction following the B-bar method:
\begin{equation}
\hat{\mathbf{F}}_{corr} = \hat{\mathbf{F}} \left( \frac{|\mathrm{av}_{el}(\hat{\mathbf{F}})|}{|\hat{\mathbf{F}}|} \right)^{\frac{1}{3}},
\end{equation}
where $\mathrm{av}_{el}()$ is the average value for the entire element.

Once the strain increment is calculated, it is added to the total strain from $t_n$. The total strain from $t_{n+1}$ must then be rotated using the rotation increment.

The input file syntax for a finite incremental strain material is

!listing modules/tensor_mechanics/test/tests/finite_strain_elastic/finite_strain_elastic_new_test.i block=Modules/TensorMechanics

!bibtex bibliography
