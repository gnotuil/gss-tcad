/*****************************************************************************/
/*                                                                           */
/*              8888888         88888888         88888888                    */
/*            8                8                8                            */
/*           8                 8                8                            */
/*           8                  88888888         88888888                    */
/*           8      8888                8                8                   */
/*            8       8                 8                8                   */
/*              888888         888888888        888888888                    */
/*                                                                           */
/*       A Two-Dimensional General Purpose Semiconductor Simulator.          */
/*                                                                           */
/*  GSS material database Version 0.4                                        */
/*  Last update: Feb 17, 2006                                                */
/*                                                                           */
/*  Gong Ding                                                                */
/*  gdiso@ustc.edu                                                           */
/*  NINT, No.69 P.O.Box, Xi'an City, China                                   */
/*                                                                           */
/*****************************************************************************/
//
// Material Type: InN

#include "PMI.h"

class GSS_InN_Avalanche : public PMIS_Avalanche
{
private:
  
  PetscScalar a_n;
  PetscScalar a_p;
  PetscScalar b_n;
  PetscScalar b_p;
  PetscScalar hbarOmega;
  PetscScalar T300;
  
  void 	Avalanche_Init()
  {
    //Source: data base of DESSIS
    a_n	= 2.9e+08/cm ;
    a_p = 1.3400e+08/cm ;
    b_n	= 3.4e+07*V/cm ;
    b_p = 2.0300e+07*V/cm ;
    hbarOmega = 0.035*eV;
    T300 = 300*K;
  }
public:
  //---------------------------------------------------------------------------
  // Electron Impact Ionization rate for DDM 
  PetscScalar ElecGenRate (const PetscScalar &Tl,const PetscScalar &Ep,const PetscScalar &Eg) const
  {
    if (Ep < 1*V/cm)
    {
      return 0;
    }
    else
    {
      PetscScalar gamma = tanh(hbarOmega/(2*kb*T300)) / tanh(hbarOmega/(2*kb*Tl));
      return gamma*a_n*exp(-b_n*gamma/Ep);
    }
  }
  AutoDScalar ElecGenRate (const AutoDScalar &Tl,const AutoDScalar &Ep,const AutoDScalar &Eg) const
  {
    if (Ep < 1*V/cm)
    {
      return 0;
    }
    else
    {
      AutoDScalar gamma = tanh(hbarOmega/(2*kb*T300)) / tanh(hbarOmega/(2*kb*Tl));
      return gamma*a_n*exp(-b_n*gamma/Ep);
    }
  }
  
  //---------------------------------------------------------------------------
  // Hole Impact Ionization rate for DDM 
  PetscScalar HoleGenRate (const PetscScalar &Tl,const PetscScalar &Ep,const PetscScalar &Eg) const
  {
    if (Ep < 1*V/cm)
    {
      return 0;
    }
    else
    {
      PetscScalar gamma = tanh(hbarOmega/(2*kb*T300)) / tanh(hbarOmega/(2*kb*Tl));
      return gamma*a_p*exp(-b_p*gamma/Ep);
    }
  }
  AutoDScalar HoleGenRate (const AutoDScalar &Tl,const AutoDScalar &Ep,const AutoDScalar &Eg) const
  {
    if (Ep < 1*V/cm)
    {
      return 0;
    }
    else
    {
      AutoDScalar gamma = tanh(hbarOmega/(2*kb*T300)) / tanh(hbarOmega/(2*kb*Tl));
      return gamma*a_p*exp(-b_p*gamma/Ep);
    }
  }

  //---------------------------------------------------------------------------
  // Electron Impact Ionization rate for EBM
  PetscScalar ElecGenRateEBM (const PetscScalar &Tn,const PetscScalar &Tl,const PetscScalar &Eg) const
  {
    return 0;
  }
  AutoDScalar ElecGenRateEBM (const AutoDScalar &Tn,const AutoDScalar &Tl,const AutoDScalar &Eg) const
  {
    return 0;
  }
  
  //---------------------------------------------------------------------------
  // Hole Impact Ionization rate for EBM
  PetscScalar HoleGenRateEBM (const PetscScalar &Tp,const PetscScalar &Tl,const PetscScalar &Eg) const
  {
    return 0;
  }
  AutoDScalar HoleGenRateEBM (const AutoDScalar &Tp,const AutoDScalar &Tl,const AutoDScalar &Eg) const
  {
    return 0;
  }
  
 
//----------------------------------------------------------------
// constructor and destructor
public:  
  GSS_InN_Avalanche(const PMIS_Environment &env):PMIS_Avalanche(env)
  {
    Avalanche_Init();
  }
  ~GSS_InN_Avalanche()
  {
  }

}
;

extern "C"
{
  PMIS_Avalanche* PMIS_InN_Avalanche_Default (const PMIS_Environment& env)
  {
    return new GSS_InN_Avalanche(env);
  }
}
