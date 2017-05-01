#ifndef SLAC2016Ana_h
#define SLAC2016Ana_h

#include "EventCollection.h"
#include <stdio.h>
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TGraph.h"
#include <iostream>
#include <fstream>
#include "TStyle.h"
#include "TFitResult.h"

class SLAC2016Ana : public EventCollection {
 public:
  SLAC2016Ana(TTree *tree=0):EventCollection(tree){};
  ~SLAC2016Ana() {};
  virtual void Loop(string &filename);
  void initialize();
  void execute();
  void finalize();
  void clear();

 private:
 TFile *file_; 
 TH1D *energy_;
 TH1D *beamEnergy[54];
 TH1D *beamTime[54];
 TH2D *beamTimeEnergy[54];
 int entry[54];
 int l;
};
#endif
