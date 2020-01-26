#include "energyModel.h"

/****f* 
  *  NAME
  *    init -- initalializes the energy model
  *  SYNOPSIS
  *   init(t, E, P);
  *  FUNCTION
  *    initializes the internal data
  *  INPUTS
  *    t      - SMA time stamp of the measurement [s]
  *    E      - initial energy [Wh]
  *    P      - initial power [W]
  *  RESULT
  *    total number of minutes
   ******
*/
int energyModdel::init(unsigned long ti, unsigned long Ei, unsigned long Pi){
  this->P=Pi;
  this->E0=Ei;
  this->t0=ti;
  this->Elast=Ei;
  this->tlast=ti;
}

/****f* 
  *  NAME
  *    checkAccuracy - checks if an update of the web values is required but doesn't change any internal values
  *  SYNOPSIS
  *   bool doUpdate=checkAccuracy(t,E);
  *  FUNCTION
  *    checks if the difference between the estimated value and the actual value require an update to the web value. 
  *    It does neither update the model parameters nor the last measurement
  *    The last measurement is used to compute P for a new period
  *  INPUTS
  *    tc       - SMA time of the latest measurement (time current)
  *    Ec       - Energy of the latest measurement (Energy current)
  *  RESULT
  *    true if update required
   ******
*/
void energyModel:checkAccuracy(unsigned long tc, unsigned long Ec){
  unsigned long current_estimate=(tc-t0)*P; // estimated energy in current period
  unsigned_long Ep=Ec-E0; // real energy in current period
  unsigned long delta=abs(current_estimate-Ep);
  unsigned long error_permill=(delta*1000)/Ep;
  if(delta > 1000 || error_percent>50)
    return true;
  else
    return false;
}

/****f* 
  *  NAME
  *    updateLast - updates the last measurement
  *  SYNOPSIS
  *   bool doUpdate=updateLast(t,E);
  *  FUNCTION
  *    Updates the last measurements but NOT the model parameters.
  *    the last measurement is used to calculate the power for a new period
  *  INPUTS
  *    tc       - SMA time of the latest measurement (time current)
  *    Ec       - Energy of the latest measurement (Energy current)
  *  RESULT
  *    --
   ******
*/
void energyModel:updateLast(unsigned long tc, unsigned long Ec){
  this->Elast=Ec;
  this->tlast=tc;
}


/****f* 
  *  NAME
  *    checkAccuracyAndUpdateLast - checks if an update of the web values is required and updates the last measurements
  *  SYNOPSIS
  *   bool doUpdate=checkAccuracyAndUpdateLast(t,E);
  *  FUNCTION
  *    checks if the difference between the estimated value and the actual value require an update to the web value. And updates the last measurements.
  *    But NOT the model parameters
  *  INPUTS
  *    tc       - SMA time of the latest measurement (time current)
  *    Ec       - Energy of the latest measurement (Energy current)
  *  RESULT
  *    true if update required
   ******
*/
void energyModel:checkAccuracyAndUpdateLast(unsigned long tc, unsigned long Ec){
  bool u=checkAccuracy(tc, Ec);
  updateLast(tc, Ec);
  return u;
}

/****f* 
  *  NAME
  *    update -- updates the model values
  *  SYNOPSIS
  *   update(t,E);
  *  FUNCTION
  *    updates the internal model values
  *  INPUTS
  *    t      - SMA time [s]
  *    E      - the energy
  *  RESULT
  *    --
   ******
*/
long energyModel::update( unsigned long t1, unsigned long E1){
  this->t0=t1;
  this->E0=E1;
  this->P=(E1-this->Elast)/(t1-this->tlast);
  this->Elast = E1;
  this->tlast = t0;
}
