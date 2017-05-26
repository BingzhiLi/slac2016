////////////////////////////////////////////////////////////////////////
// Class:       creationT_vs_arrivalT
// Plugin Type: analyzer (art v2_03_00)
// File:        creationT_vs_arrivalT_module.cc
//
// Generated at Mon Apr 24 01:53:40 2017 by Bingzhi Li using cetskelgen
// from cetlib version v1_19_01.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
//#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

//XtalPhoton,PhotodetectorPhoton,Xtal Art Record
//#include "gm2dataproducts/mc/calo/XtalPhotonArtRecord.hh"
//#include "gm2dataproducts/mc/calo/PhotodetectorPhotonArtRecord.hh"
//#include "gm2dataproducts/mc/calo/XtalArtRecord.hh"
#include "gm2ringsim/calo/XtalPhotonArtRecord.hh"
#include "gm2ringsim/calo/PhotodetectorPhotonArtRecord.hh"
#include "gm2ringsim/calo/XtalArtRecord.hh"

// Physical Volume Store Includes
#include "artg4/pluginActions/physicalVolumeStore/PhysicalVolumeStoreData.hh"
#include "artg4/pluginActions/physicalVolumeStore/physicalVolumeStore_service.hh"
#include "artg4/util/DataFromRunOrService.hh"

//ROOT
#include "TTree.h"
#include "TString.h"
#include "TH2.h"
#include "TH1.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "cetlib/exception.h"

//C++
using namespace std;
#include<vector>

class creationT_vs_arrivalT;


class creationT_vs_arrivalT : public art::EDAnalyzer {
public:
  explicit creationT_vs_arrivalT(fhicl::ParameterSet const & p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  creationT_vs_arrivalT(creationT_vs_arrivalT const &) = delete;
  creationT_vs_arrivalT(creationT_vs_arrivalT &&) = delete;
  creationT_vs_arrivalT & operator = (creationT_vs_arrivalT const &) = delete;
  creationT_vs_arrivalT & operator = (creationT_vs_arrivalT &&) = delete;

  // Required functions.
  void analyze(art::Event const & e) override;

private:

  // Declare member data here.
  std::string caloModuleLabel_;
  std::string caloInstanceLabel_;

  TH1F *h_arrivalT[3];//photon arrival SiPM time
  TH2F *h_creationT_vs_arrivalT[3];//photon creation time vs arrival SiPM time
  TH2F *h_deltaE_vs_deltaT;//#23 #25 energy and time difference relation
  TH1F *h_cos_theta[3];//photon creation cos theat in xtal
  TH2F *h_xy[3];//photon creation location x vs y
  TH2F *h_xz[3];//photon creation location x vs z
  TH1F *h_z[3];//photon creation depth
  TH1F *h_speed[3];//photon creation depth divide the creation time
  TH2F *h_speed_z[3];//h_speed vs photon creation depth
  TH1F *h_beamT[3];//beam arrive xtal time
  TH2F *h_pdg;//pdg id for diff xtal
  TH2F *h_arrivalT_vs_z[3];//photon arrival time vs creation depth
  TH2F *h_creationT_vs_z[3];//photon creation time vs creation depth

  int Event=0;//the total events num
};


creationT_vs_arrivalT::creationT_vs_arrivalT(fhicl::ParameterSet const & p)
  :
  EDAnalyzer(p)  ,
  caloModuleLabel_(p.get<std::string>("caloModuleLabel", "artg4")),
  caloInstanceLabel_(p.get<std::string>("caloInstanceLabel", "calorimeter"))
 // More initializers here.
{
  art::ServiceHandle<art::TFileService> tfs;
  art::TFileDirectory histDir = *tfs;

  for(int i=0;i<3;i++){
    h_arrivalT[i]=histDir.make<TH1F>(Form("photon_arrival_time_#%d",i+30),"",200,0.4,2.4);
    h_arrivalT[i]->SetXTitle("time [ns]");
  }

  for(int i=0;i<3;i++){
    h_creationT_vs_arrivalT[i]=histDir.make<TH2F>(Form("h_creationT_vs_arrivalT_%d",i+30),"",240,0,0.6,360,0,9);
    h_creationT_vs_arrivalT[i]->SetYTitle("arrival time [ns]");
    h_creationT_vs_arrivalT[i]->SetXTitle("creation time [ns]");
  }

  h_deltaE_vs_deltaT=histDir.make<TH2F>("deltaE_vs_deltaT_#32#30","",160,-2,2,200,-500,500);
  h_deltaE_vs_deltaT->SetYTitle("#Delta E");
  h_deltaE_vs_deltaT->SetXTitle("#Delta T");

  for(int i=0;i<3;i++){
    h_cos_theta[i]=histDir.make<TH1F>(Form("cos#theta_%d",i+30),"",100,-1,1);
    h_cos_theta[i]->SetXTitle("cos#theta");
  }

  for(int i=0;i<3;i++){
    h_xy[i]=histDir.make<TH2F>(Form("photon_shower_xy_#%d",i+30),"",250,-12.5,12.5,250,-12.5,12.5);
    h_xy[i]->SetYTitle("y [mm]");
    h_xy[i]->SetXTitle("x [mm]");
  }

  for(int i=0;i<3;i++){
    h_xz[i]=histDir.make<TH2F>(Form("photon_shower_xz_#%d",i+30),"",250,-12.5,12.5,140,0,140);
    h_xz[i]->SetYTitle("z [mm]");
    h_xz[i]->SetXTitle("x [mm]");
  }

  for(int i=0;i<3;i++){
    h_z[i]=histDir.make<TH1F>(Form("photon_shower_depth_#%d",i+30),"",140,0,140);
    h_z[i]->SetXTitle("x [mm]");
  }

  for(int i=0;i<3;i++){
    h_speed[i]=histDir.make<TH1F>(Form("z/t_#%d",i+30),"",110,0,1.1);
    h_speed[i]->SetXTitle("#frac{z [mm]}{t [ns]}");
    h_speed[i]->GetXaxis()->SetTitleOffset(1.2);
  }

  for(int i=0;i<3;i++){
    h_speed_z[i]=histDir.make<TH2F>(Form("z/t_vs_z_#%d",i+30),"",110,0,1.1,140,0,140);
    h_speed_z[i]->SetXTitle("#frac{z [mm]}{t [ns]}");
    h_speed_z[i]->GetXaxis()->SetTitleOffset(1.2);
    h_speed_z[i]->SetYTitle("z [mm]");
  }

  for(int i=0;i<3;i++){
    h_beamT[i]=histDir.make<TH1F>(Form("beam_time_#%d",i+30),"",100,0,1);
    h_beamT[i]->SetXTitle("beam time [ns]");
  }

  h_pdg=histDir.make<TH2F>("pdg_id","",3,30,33,2,0,2);
  h_pdg->SetTitle("pdg ID");
  h_pdg->GetXaxis()->SetLabelSize(0.1);
  h_pdg->GetXaxis()->SetBinLabel(1,"xtal#32");
  h_pdg->GetXaxis()->SetBinLabel(2,"xtal#31");
  h_pdg->GetXaxis()->SetBinLabel(3,"xtal#30");
  h_pdg->GetYaxis()->SetLabelSize(0.1);
  h_pdg->GetYaxis()->SetBinLabel(1,"e-");
  h_pdg->GetYaxis()->SetBinLabel(2,"#gamma");

  for(int i=0;i<3;i++){
    h_arrivalT_vs_z[i]=histDir.make<TH2F>(Form("arrival_T_vs_depth_%d",i+30),"",140,0,140,360,0,9);
    h_arrivalT_vs_z[i]->SetXTitle("depth [mm]");
    h_arrivalT_vs_z[i]->SetYTitle("arrival time [ns]");
  }

  for(int i=0;i<3;i++){
    h_creationT_vs_z[i]=histDir.make<TH2F>(Form("creation_T_vs_depth_%d",i+30),"",140,0,140,240,0,0.6);
    h_creationT_vs_z[i]->SetXTitle("depth [mm]");
    h_creationT_vs_z[i]->SetYTitle("creation time [ns]");
  }

}

void creationT_vs_arrivalT::analyze(art::Event const & e)
{
  // Implementation of required member function here.
  art::Handle< gm2ringsim::XtalPhotonArtRecordCollection > XtalPhotonHitDataHandle;
  e.getByLabel("artg4", "calorimeter", XtalPhotonHitDataHandle);
  gm2ringsim::XtalPhotonArtRecordCollection const & XtalPhotonHits = *XtalPhotonHitDataHandle;

  art::Handle< gm2ringsim::PhotodetectorPhotonArtRecordCollection > PhotodetectorPhotonHitDataHandle;
  e.getByLabel(caloModuleLabel_, caloInstanceLabel_, PhotodetectorPhotonHitDataHandle);
  gm2ringsim::PhotodetectorPhotonArtRecordCollection const & PhotodetectorPhotonHits = *PhotodetectorPhotonHitDataHandle;  

  art::Handle< gm2ringsim::XtalArtRecordCollection > XtalHitDataHandle;
  e.getByLabel("artg4", "calorimeter", XtalHitDataHandle);
  gm2ringsim::XtalArtRecordCollection const & XtalHits = *XtalHitDataHandle;

  Event++;
  std::cout<<"///////////////////////////////////"<<std::endl;
  std::cout<<"//"<<std::endl;
  std::cout<<"//  "<<"The Event Num is : "<<Event<<std::endl;//print the Event num
  std::cout<<"//"<<std::endl;
  std::cout<<"///////////////////////////////////"<<std::endl;
  //double aTcount[3]={0},cTcount[3]={0};//aTcount is the Num of arrival photon, cTcount is for creation photon
  //double aT[3]={0},cT[3]={0}; //aT is arrival time, cT is creation time

  vector<double> aT30,aT31,aT32,cT30,cT31,cT32; //use vector to store the arrival and creation time
  aT30.clear(); aT31.clear(); aT32.clear(); cT30.clear(); cT31.clear(); cT32.clear(); //clear the previous data before this event run

  vector<double> z30,z31,z32;//use vector to store the photon creation depth
  z30.clear();z31.clear();z32.clear();//clear the previous data before this event run
 
  double edep30=0,edep31=0,edep32=0;//the energy deposited in xtal #30 #31 #32 
  double t30=0,t31=0,t32=0;//the xtal hit time

  //photodetectorPhoton
  for(auto det : PhotodetectorPhotonHits) {
    //photon arrival time in xtal 30\31\32
    if(det.photodetectorNum==30&&det.accepted==1) {h_arrivalT[0]->Fill(det.time-200.43);}
    if(det.photodetectorNum==31&&det.accepted==1) {h_arrivalT[1]->Fill(det.time-200.43);}
    if(det.photodetectorNum==32&&det.accepted==1) {h_arrivalT[2]->Fill(det.time-200.43);}

    //get the arrival time and the Num
    //if(det.photodetectorNum==30&&det.accepted==1) {aT[0]=det.time-200.43; aTcount[0]++;}
    //if(det.photodetectorNum==31&&det.accepted==1) {aT[1]=det.time-200.43; aTcount[1]++;}
    //if(det.photodetectorNum==32&&det.accepted==1) {aT[2]=det.time-200.43; aTcount[2]++;}

    //get the arrival time using vector
    if(det.photodetectorNum==30&&det.accepted==1) {aT30.push_back(det.time-200.43);}
    if(det.photodetectorNum==31&&det.accepted==1) {aT31.push_back(det.time-200.43);}
    if(det.photodetectorNum==32&&det.accepted==1) {aT32.push_back(det.time-200.43);}
  }
   
  //print the arrival photon num in this event
  //std::cout<<"the Num of arrival Xtal #30 Photon is : "<<aTcount[0]<<std::endl;
  //std::cout<<"the Num of arrival Xtal #30 Photon is : "<<aTcount[1]<<std::endl;
  //std::cout<<"the Num of arrival Xtal #30 Photon is : "<<aTcount[2]<<std::endl;

  //xtalphoton
  for(auto xtalp : XtalPhotonHits){
    //shower x vs y
    if(xtalp.xtalNum==30&&xtalp.detected==1&&xtalp.transmitted==1) {h_xy[0]->Fill(-xtalp.x,xtalp.y);}
    if(xtalp.xtalNum==31&&xtalp.detected==1&&xtalp.transmitted==1) {h_xy[1]->Fill(-xtalp.x,xtalp.y);}
    if(xtalp.xtalNum==32&&xtalp.detected==1&&xtalp.transmitted==1) {h_xy[2]->Fill(-xtalp.x,xtalp.y);}

    //shower z vs x
    if(xtalp.xtalNum==30&&xtalp.detected==1&&xtalp.transmitted==1) {h_xz[0]->Fill(-xtalp.x,xtalp.depth);}
    if(xtalp.xtalNum==31&&xtalp.detected==1&&xtalp.transmitted==1) {h_xz[1]->Fill(-xtalp.x,xtalp.depth);}
    if(xtalp.xtalNum==32&&xtalp.detected==1&&xtalp.transmitted==1) {h_xz[2]->Fill(-xtalp.x,xtalp.depth);}

    //cos theta
    if(xtalp.xtalNum==30&&xtalp.detected==1&&xtalp.transmitted==1) {h_cos_theta[0]->Fill(xtalp.costheta);}
    if(xtalp.xtalNum==31&&xtalp.detected==1&&xtalp.transmitted==1) {h_cos_theta[1]->Fill(xtalp.costheta);}
    if(xtalp.xtalNum==32&&xtalp.detected==1&&xtalp.transmitted==1) {h_cos_theta[2]->Fill(xtalp.costheta);}
 
    //depth
    if(xtalp.xtalNum==30&&xtalp.detected==1&&xtalp.transmitted==1) {h_z[0]->Fill(xtalp.depth);}
    if(xtalp.xtalNum==31&&xtalp.detected==1&&xtalp.transmitted==1) {h_z[1]->Fill(xtalp.depth);}
    if(xtalp.xtalNum==32&&xtalp.detected==1&&xtalp.transmitted==1) {h_z[2]->Fill(xtalp.depth);}
 
    //depth divide time
    if(xtalp.xtalNum==30&&xtalp.detected==1&&xtalp.transmitted==1) {h_speed[0]->Fill(xtalp.depth/(xtalp.time-200.43)/300);}    
    if(xtalp.xtalNum==31&&xtalp.detected==1&&xtalp.transmitted==1) {h_speed[1]->Fill(xtalp.depth/(xtalp.time-200.43)/300);} 
    if(xtalp.xtalNum==32&&xtalp.detected==1&&xtalp.transmitted==1) {h_speed[2]->Fill(xtalp.depth/(xtalp.time-200.43)/300);} 

    //depth divide time vs depth
    if(xtalp.xtalNum==30&&xtalp.detected==1&&xtalp.transmitted==1) {h_speed_z[0]->Fill(xtalp.depth/(xtalp.time-200.43)/300,xtalp.depth);}
    if(xtalp.xtalNum==31&&xtalp.detected==1&&xtalp.transmitted==1) {h_speed_z[1]->Fill(xtalp.depth/(xtalp.time-200.43)/300,xtalp.depth);}
    if(xtalp.xtalNum==32&&xtalp.detected==1&&xtalp.transmitted==1) {h_speed_z[2]->Fill(xtalp.depth/(xtalp.time-200.43)/300,xtalp.depth);}
  
    //get the creation time and the num
    //if(xtalp.xtalNum==30&&xtalp.detected==1&&xtalp.transmitted==1) {cT[0]=xtalp.time-200.43; cTcount[0]++;}
    //if(xtalp.xtalNum==31&&xtalp.detected==1&&xtalp.transmitted==1) {cT[1]=xtalp.time-200.43; cTcount[1]++;}
    //if(xtalp.xtalNum==32&&xtalp.detected==1&&xtalp.transmitted==1) {cT[2]=xtalp.time-200.43; cTcount[2]++;}

    //get the creation time using vector
    if(xtalp.xtalNum==30&&xtalp.detected==1&&xtalp.transmitted==1) {cT30.push_back(xtalp.time-200.43);}
    if(xtalp.xtalNum==31&&xtalp.detected==1&&xtalp.transmitted==1) {cT31.push_back(xtalp.time-200.43);}
    if(xtalp.xtalNum==32&&xtalp.detected==1&&xtalp.transmitted==1) {cT32.push_back(xtalp.time-200.43);}

    //get the creation depth using vector
    if(xtalp.xtalNum==30&&xtalp.detected==1&&xtalp.transmitted==1) {z30.push_back(xtalp.depth);}
    if(xtalp.xtalNum==31&&xtalp.detected==1&&xtalp.transmitted==1) {z31.push_back(xtalp.depth);}
    if(xtalp.xtalNum==32&&xtalp.detected==1&&xtalp.transmitted==1) {z32.push_back(xtalp.depth);}
  }

  //print the creation photon num in this event 
  //std::cout<<std::endl;
  //std::cout<<"the Num of creation Xtal #30 Photon is : "<<cTcount[0]<<std::endl;
  //std::cout<<"the Num of creation Xtal #30 Photon is : "<<cTcount[1]<<std::endl;
  //std::cout<<"the Num of creation Xtal #30 Photon is : "<<cTcount[2]<<std::endl;  

  //creation time vs arrival time #30 (and depth)
  for(vector<double>::size_type i=0;i<aT30.size();i++){
    for(vector<double>::size_type j=0;j<cT30.size();j++){
      if(i==j) {h_creationT_vs_arrivalT[0]->Fill(cT30[i],aT30[j]); h_arrivalT_vs_z[0]->Fill(z30[i],aT30[j]); h_creationT_vs_z[0]->Fill(z30[i],cT30[j]);}
    }
  }

  //creation time vs arrival time #31 (and depth)
  for(vector<double>::size_type i=0;i<aT31.size();i++){
    for(vector<double>::size_type j=0;j<cT31.size();j++){
      if(i==j) {h_creationT_vs_arrivalT[1]->Fill(cT31[i],aT31[j]); h_arrivalT_vs_z[1]->Fill(z31[i],aT31[j]); h_creationT_vs_z[1]->Fill(z31[i],cT31[j]);}
    }
  }

  //creation time vs arrival time #32 (and depth)
  for(vector<double>::size_type i=0;i<aT32.size();i++){
    for(vector<double>::size_type j=0;j<cT32.size();j++){
      if(i==j) {h_creationT_vs_arrivalT[2]->Fill(cT32[i],aT32[j]); h_arrivalT_vs_z[2]->Fill(z32[i],aT32[j]); h_creationT_vs_z[2]->Fill(z32[i],cT32[j]);}
    }
  }

  //xtal 
  for(auto xtal : XtalHits){
    //xtal deposited energy vs time
    if(xtal.xtalNum==30) {edep30+=xtal.edep;t30=xtal.time;h_beamT[0]->Fill(t30-200.43);}
    if(xtal.xtalNum==31) {edep31+=xtal.edep;t31=xtal.time;h_beamT[1]->Fill(t31-200.43);}
    if(xtal.xtalNum==32) {edep32+=xtal.edep;t32=xtal.time;h_beamT[2]->Fill(t32-200.43);}

    //pdg id
    if(xtal.xtalNum==30) {h_pdg->Fill(32,xtal.pdgID/11-1);}
    if(xtal.xtalNum==31) {h_pdg->Fill(31,xtal.pdgID/11-1);}
    if(xtal.xtalNum==32) {h_pdg->Fill(30,xtal.pdgID/11-1);}
       
  }
  //xtal deposited energy vs time
  //cout<<"diff t:"<<t32-t30<<endl;
  //cout<<"diff e:"<<edep32-edep30<<endl; 
  h_deltaE_vs_deltaT->Fill(t32-t30,edep32-edep30);
  
}

DEFINE_ART_MODULE(creationT_vs_arrivalT)
