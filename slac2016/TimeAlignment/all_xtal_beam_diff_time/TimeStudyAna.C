#include "TimeStudyAna.h"
#include <iostream>
#include <numeric> 

void TimeStudyAna::Loop(string filename){

    //find hit xtal and side xtal
    int runlist[54] = {
        3295,3296,3297,3369,3300,3301,3302,3303,3368,
	    3244,3245,3246,3247,3248,3249,3250,3251,3252,
	    3240,3239,3238,3237,3236,3235,3232,3234,3233,
	    3267,3266,3265,3263,3258,3257,3256,3254,3253,
	    3268,3272,3274,3275,3276,3277,3278,3281,3283,
        3294,3293,3292,3289,3288,3287,3286,3285,3284};  
    for(int i=0;i<54;i++)
    {        
//        if(i%9==0 || i%9==8) continue; 
//        if(i<9 || i>44) continue;
        if(strcmp(filename.c_str() , Form("gm2slac_run0%4d.root",runlist[i]) )==0){
            cout<<filename.c_str()<<"\tXtal:"<<i<<endl;
            const int channel[5]={i+9,i+1,i,i-1,i-9};
            initialize(filename,channel[2]);
            
            if (fChain == 0) return;
            Long64_t nentries = fChain->GetEntriesFast();
            Int_t nbytes = 0, nb = 0;
            for (Long64_t jentry=0; jentry<nentries;jentry++) {
                Long64_t ientry = LoadTree(jentry);
                if (ientry < 0) break;
                nb = fChain->GetEntry(jentry);   nbytes += nb;
                execute(channel[2]);
            }
            finalize(filename);
        }
    }   
}

void TimeStudyAna::initialize(string &filename,int q){

            cout << "Initializing! Analyzing " << filename << endl;     
 
            
            const int channel[4]={q+9,q+1,q-1,q-9};
   	        //create root file
    		file = new TFile(Form("%s.xtal%d.root",filename.c_str(),q),"recreate");  

   		    //create beam time diff hist
		    for(int l=0;l<3;l++){
		        for(int p=l+1;p<4;p++){
                        if(channel[l]>=0&&channel[p]>=0){
    		        TString title1(Form("beamTimeDiffNum%02dNum%02d",channel[l],channel[p]));
    		        beamTimeDiff[l][p] = new TH1D(title1,title1,1300,-3,3);
    		        beamTimeDiff[l][p]->GetXaxis()->SetTitle(Form("beamT_{%2d}-beamT_{%2d}",channel[l],channel[p]));}
    		    }
    		}
    	
 			//create beam time hist
    		/*for(int k=0;k<5;k++){
    		    TString title2(Form("beamTime%02d",channel[k]));
    		    beamTime[k] = new TH1D(title2,title2,500,1300,1700);
    		    beamTime[k]->GetXaxis()->SetTitle("time [c.t.]");    
    		}*/
	
    		//create deltaE vs deltaT hist
    		for(int m=0;m<3;m++){
    		    for(int n=m+1;n<4;n++){
    		        if(channel[n]>=0&&channel[m]>=0){
                        TString title4(Form("beam_deltaE_deltaT_Num%02d_Num%02d",channel[m],channel[n]));
    		        beamTimeDiffEnergy[m][n] = new TH2D(title4,title4,100,-10,10,100,-500,500);}
    		        //beamTimeDiffEnergy[m][m]->SetCanExtend(kTRUE);
    		    }
    		}
}	

void TimeStudyAna::execute(int e){

  //    cout << "--> execute(), EventNum: " << EventNum <<endl;

  const int channel[4]={e+9,e+1,e-1,e-9};

  //store right left up down and hit xtal time and energy
  double beamT[4] = {};
  double beamE[4] = {};


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
        /*for(int k=0;k<5;k++){
          if(XtalHit_XtalNum->at(iF1)==channel[k]){
            beamTime[k]->Fill(XtalHit_Time->at(iF1));  
          }
        }*/ 
        for(int l=0;l<4;l++){
          if(XtalHit_XtalNum->at(iF1)==channel[l]){
            beamT[l]=XtalHit_Time->at(iF1); 
            beamE[l]=XtalHit_Energy->at(iF1);
            /*****************************************
            if(l==0) {beamT_[0]=beamT[l];beamE_[0]=beamE[l];}   
            if(l==1) {beamT_[1]=beamT[l];beamE_[1]=beamE[l];}
            if(l==3) {beamT_[2]=beamT[l];beamE_[2]=beamE[l];}
            if(l==4) {beamT_[3]=beamT[l];beamE_[3]=beamE[l];} 
            *****************************************/     
          }
        }      
      }
    }
    
    for(int w=0;w<3;w++){
      for(int r=w+1;r<4;r++){
        if(channel[r]>=0&&channel[w]>=0){
        if(beamT[w]!=0 && beamT[r]!=0 /*&& (abs(beamT[w]-beamT[r])<2) && beamE[w]>20 && beamE[r]>20*/ ){
          beamTimeDiff[w][r]->Fill(beamT[w]-beamT[r]);
        }
        }
      }
    }
    //*****************************************
    for(int m=0;m<3;m++){
      for(int n=m+1;n<4;n++){
        if(channel[m]>=0&&channel[n]>=0){
        if(beamT[m]!=0 && beamT[n]!=0 /*&& (abs(beamT[m]-beamT[n])<2) && beamE[m]>20 && beamE[n]>20*/ ){
          beamTimeDiffEnergy[m][n]->Fill(beamT[m]-beamT[n], beamE[m]-beamE[n]);
        }
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
