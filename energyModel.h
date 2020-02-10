#ifndef ENERGYMODEL_H
#define ENERGYMODEL_H

class energyModel {
 private:
  unsigned long P; // the model power [W]
  unsigned long E0; // the energy at the beginning of the estimation period [Wh]
  unsigned long t0; // the time at the beginning of the estimation period (SMA time) [s]
  unsigned long Elast; // last measurement energy [Wh]
  unsigned long tlast; // last measurement time (SMA time) [s]


 public:
  energyModel(void) { P=0; E0=0; t0=0; Elast=0; tlast=0; };
  ~energyModel(void) { };
  void init(unsigned long ti, unsigned long Ei, unsigned long Pi);
  bool isInitialized();
  bool checkAccuracy(unsigned long tc, unsigned long Ec);
  void updateLast(unsigned long tc, unsigned long Ec);
  bool checkAccuracyAndUpdateLast(unsigned long tc, unsigned long Ec);
  void update( unsigned long t1, unsigned long E1);
  unsigned long getP() { return P; }
};
  

#endif
