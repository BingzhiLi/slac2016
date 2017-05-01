#include "SLAC2016Ana.h"
#include <iostream>
#include <iomanip>

void SLAC2016Ana::Loop(string &filename){

    initialize();

    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Int_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;

	execute();

    }

    finalize();

}
void SLAC2016Ana::initialize(){

    //cout << "initialize()" << endl;

    file_ = new TFile("test.root","recreate");
    
    for(int i=0;i<54;i++){

        //TString title4(Form("beamTime%02d",i));
        //beamTime[i] = new TH1D(title4,title4,500,1300,1700);
        //beamTime[i]->GetXaxis()->SetTitle("time [c.t.]");

        TString title5(Form("beamEnergy%02d",i));
        beamEnergy[i] = new TH1D(title5,title5,100,0,3000);
        beamEnergy[i]->GetXaxis()->SetTitle("energy [#photons]");

        //TString title6(Form("beamTimeEnergy%02d",i));
        //beamTimeEnergy[i] = new TH2D(title6,title6,200,1300,1700,300,0,3000);
        //beamTimeEnergy[i]->GetXaxis()->SetTitle("time [c.t.]");
        //beamTimeEnergy[i]->GetYaxis()->SetTitle("energy [#photons]");

    }
    
}

void SLAC2016Ana::execute(){

    //cout << "--> execute(), EventNum: " << EventNum <<endl;

    double beamT[54]={};
    double beamE[54]={};
    int entry[54]={0};

    bool isSingleElec=false;
    int islandNum=0;
    for(size_t iC=0;iC<Cluster_EventNum->size();iC++){  
        if(Cluster_Energy->at(iC)<3000 && Cluster_Energy->at(iC)>1000 && Cluster_Time->at(iC)<2000 ) {
            isSingleElec = true; 
            islandNum = Cluster_IslandNum->at(iC); // store the islandNum here, loop through xtal with this islandNum
            //cout<<"\tCluster Energy: "<<Cluster_Energy->at(iC)<<", Time: "<<Cluster_Time->at(iC)<<endl;
        }
    }

    if(isSingleElec) {
        for(size_t iF=0;iF<XtalHit_EventNum->size();iF++){  

            // continue if this xtal hit does not belong to the interested cluster
            if(XtalHit_IslandNum->at(iF) != islandNum) continue;

            if(/*XtalHit_Energy->at(iF)>1500 &&*/ XtalHit_Time->at(iF)>1000 && XtalHit_Time->at(iF)<2000) {
                //beamT[XtalHit_XtalNum->at(iF)] = XtalHit_Time->at(iF); 
                //beamE[XtalHit_XtalNum->at(iF)] = XtalHit_Energy->at(iF); 
                //beamTime[XtalHit_XtalNum->at(iF)]->Fill(XtalHit_Time->at(iF));
                beamEnergy[XtalHit_XtalNum->at(iF)]->Fill(XtalHit_Energy->at(iF));
                //beamTimeEnergy[XtalHit_XtalNum->at(iF)]->Fill(XtalHit_Time->at(iF),XtalHit_Energy->at(iF));
            }
        }
    }

}

void SLAC2016Ana::finalize(){

    double mean[54];
    //cout << "\tfinalize()" << endl;
    for(int l=0;l<54;l++){
        entry[l] = beamEnergy[l]->GetEntries();
        /*if(entry[l]>100){
            //beamEnergy[l]->Fit("gaus","S");
            mean[l]=beamEnergy[l]->Fit("gaus","SQ")->Parameter(1);        
            if(mean[l]>1000){
                cout<<l<<"	"<<mean[l]<<endl;
                //cout<<"xtalNum="<<l<<"	"<<entry[l]<<"	"<<"energyRes="<<mean[l]<<endl;
            }
            //gStyle->SetOptFit();
        }//else {cout<<"xtalNum="<<l<<"      "<<entry[l]<<endl;}*/
        if(entry[l]>0){
            mean[l]=beamEnergy[l]->Fit("gaus","SQ")->Parameter(1);
            cout<<"xtalNum="<<setw(2)<<l<<"	"<<"Entry="<<setw(4)<<entry[l]<<"	"<<"energyRes="<<mean[l]<<endl;
        }else{cout<<"xtalNum="<<setw(2)<<l<<"     "<<"Entry="<<setw(4)<<entry[l]<<endl;}

    }
    file_->Write();
    file_->Close();

}
