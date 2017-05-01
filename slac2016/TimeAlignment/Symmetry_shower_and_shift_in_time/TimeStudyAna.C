#include "TimeStudyAna.h"
#include <iostream>
#include <numeric> 

void TimeStudyAna::Loop(string filename){

    initialize(filename);

    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();
    Int_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;

        execute();

    }

    finalize(filename);

}
void TimeStudyAna::initialize(string &filename){

    cout << "Initializing! Analyzing " << filename << endl;

    file = new TFile(Form("%s.root",filename.c_str()),"recreate");  

    const int channel_i[9] = {34,33,32,25,24,23,16,15,14};
    for(int l=0;l<9;l++){
        TString title1(Form("beamTimeDiffNum%02dNum24",channel_i[l]));
        beamTimeDiff[l] = new TH1D(title1,title1,1300,-3,10);
        beamTimeDiff[l]->GetXaxis()->SetTitle(Form("beamT_{%2d}-beamT_{24}",channel_i[l]));
    }

    const int channel_j[5] = {33,25,24,23,15};
    for(int k=0;k<5;k++){
        TString title2(Form("beamTime%02d",channel_j[k]));
        beamTime[k] = new TH1D(title2,title2,500,1300,1700);
        beamTime[k]->GetXaxis()->SetTitle("time [c.t.]");    

        TString title3(Form("syncTime%02d",channel_j[k]));
        syncTime[k] = new TH1D(title3,title3,500,-50,50);
        syncTime[k]->GetXaxis()->SetTitle("time [c.t.]");
    }
//*****************************************
    //deltaE vs deltaT
    for(int m=0;m<4;m++){
        for(int n=m+1;n<5;n++){
            TString title4(Form("beam_deltaE_deltaT_Num%02d_Num%02d",channel_j[m],channel_j[n]));
            beamTimeDiffEnergy[m][n] = new TH2D(title4,title4,100,-2,5,100,-500,500);
            //beamTimeDiffEnergy[m][m]->SetCanExtend(kTRUE);
        }
    }
//*****************************************
}

void TimeStudyAna::execute(){

  //    cout << "--> execute(), EventNum: " << EventNum <<endl;

  double beamT[9] = {};
  double beamE[9] = {};
  double beamT24;
  double beamE24;
//*****************************************
  double beamT_[5] = {};
  double beamE_[5] = {};
//*****************************************
  const int channel_i[9] = {34,33,32,25,24,23,16,15,14};
  const int channel_j[5] = {33,25,24,23,15};

  // Collect time for the sync pulses after correction (aka calibration xtal hit)
  for(size_t iF=0;iF<XtalHit_EventNum->size();iF++){  
    if(XtalHit_Time->at(iF)<1000) {     
      for(int k=0;k<5;k++){
        if(XtalHit_XtalNum->at(iF)==channel_j[k]){
          syncTime[k]->Fill(XtalHit_Time->at(iF));          
        }
      }
    }
  }

  // Collect single electron events only for the beam pulses
  bool isSingleElec=false;
  int islandNum=0;
  for(size_t iC=0;iC<Cluster_EventNum->size();iC++){  
    if(Cluster_Energy->at(iC)<3000 && Cluster_Energy->at(iC)>1000 && Cluster_Time->at(iC)<2000 ) {
      isSingleElec = true; 
      islandNum = Cluster_IslandNum->at(iC); // store the islandNum here, loop through xtal with this islandNum
    }
  }

  // Only store the information if it is a single electron event
  if(isSingleElec) {

    for(size_t iF1=0;iF1<XtalHit_EventNum->size();iF1++){  
      // continue if this xtal hit does not belong to the interested cluster
      if(XtalHit_IslandNum->at(iF1) != islandNum) continue;
      if(XtalHit_Time->at(iF1)>1000 && XtalHit_Time->at(iF1)<2000) {
        for(int k=0;k<5;k++){
          if(XtalHit_XtalNum->at(iF1)==channel_j[k]){
            beamTime[k]->Fill(XtalHit_Time->at(iF1));  
            //cout<<channel_j[k]<<"	"<<XtalHit_Time->at(iF1)<<endl; 
          }
        } 
        for(int l=0;l<9;l++){
          if(XtalHit_XtalNum->at(iF1)==channel_i[l]){
            beamT[l]=XtalHit_Time->at(iF1); 
            beamE[l]=XtalHit_Energy->at(iF1);
            //*****************************************
            if(l==1) {beamT_[0]=beamT[l];beamE_[0]=beamE[l];}   
            if(l==3) {beamT_[1]=beamT[l];beamE_[1]=beamE[l];}
            if(l==4) {beamT_[2]=beamT[l];beamE_[2]=beamE[l];}
            if(l==5) {beamT_[3]=beamT[l];beamE_[3]=beamE[l];}
            if(l==7) {beamT_[4]=beamT[l];beamE_[4]=beamE[l];} 
            //*****************************************     
          }
          if(XtalHit_XtalNum->at(iF1)==24){
            beamT24=XtalHit_Time->at(iF1);
            beamE24=XtalHit_Energy->at(iF1);
          }
        }      
      }
    }
    
    for(int w=0;w<9;w++){
      if(beamT[w]!=0 && beamT24!=0 && (abs(beamT[w]-beamT24)<2) && beamE[w]>20 && beamE24>20 ){
        beamTimeDiff[w]->Fill(beamT[w]-beamT24);
      }
    }
    //*****************************************
    for(int m=0;m<5;m++){
      for(int n=m+1;n<5;n++){
        if(beamT_[m]!=0 && beamT_[n]!=0 /*&& (abs(beamT_[m]-beamT_[n])<2) && beamE_[m]>20 && beamE_[n]>20*/ ){
          beamTimeDiffEnergy[m][n]->Fill(beamT_[m]-beamT_[n], beamE_[m]-beamE_[n]);
        }
      }
    }
    //*****************************************
  }

}

void TimeStudyAna::finalize(string &filename){


  cout << "\tfinalize(): " << filename<< endl;
  file->Write();
  file->Close();
}
