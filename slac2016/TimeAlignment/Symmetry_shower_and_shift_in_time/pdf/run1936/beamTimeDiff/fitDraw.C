void fitDraw(){

    TFile *f=new TFile("gm2slac_run01936.root.root");
    const int num=9;
    TH1F *h[9];
    const int channel[9]={34,33,32,25,24,23,16,15,14};
    double h_mean[9],h_rms[9],store_mean[9],store_rms[9];
    TLatex mean[9];
    TF1 *fit[9],*f1[9];

    TCanvas *c=new TCanvas("c","",10,10,1600,1600);
    c->Divide(3,3);
    gStyle->SetOptStat("n");
    gStyle->SetOptFit();
    gStyle->SetStatFontSize(0.08);

    TString title[num];
    for(int i=0;i<num;i++){
        title[i]="beamTimeDiffNum";
        title[i]+=channel[i];
        title[i]+="Num24";
    }
  
    for(int j=0;j<num;j++){
        cout<<" Trying to find 1D "<<title[j]<<" "<<j<<endl;
        h[j]=(TH1F*)f->Get(title[j]);
    }
 
    for(int k=0;k<num;k++){
        c->cd(k+1);
        gPad->SetLogy();
        h[k]->Draw(); 
        //if(k==4) {continue;}
        h_mean[k]=h[k]->GetMean();
        h_rms[k]=h[k]->GetRMS();
   
        h[k]->Fit("gaus","S","",h_mean[k]-2,h_mean[k]+2);
        store_mean[k]=h[k]->Fit("gaus","SQ","",h_mean[k]-2,h_mean[k]+2)->Parameter(1);    
        store_rms[k]=h[k]->Fit("gaus","SQ","",h_mean[k]-2,h_mean[k]+2)->Parameter(2);   
        mean[k].SetTextSize(0.07);
        mean[k].SetTextColor(1);
        //mean[k].DrawLatex(5,1,Form("Mean = %0.2f c.t.",store_mean[k])); 
  

        /*fit[k] = new TF1(Form("fit%d",k),"gaus(0)",h_mean[k]-2,h_mean[k]+2);    
        fit[k]->SetParameters(1000,h_mean[k],h_rms[k]);
        h[k]->Fit(fit[k],"QMER");

        store_mean[k]=fit[k]->GetParameter(1);
        store_rms[k]=fit[k]->GetParameter(2);
        
        cout<<"**********************************"<<endl;
        cout<<k<<"	"<<fit[k]->GetParameter(1)<<"	"<<fit[k]->GetParameter(2)<<endl;

        if(store_rms[k]<0.1)   {continue;}
        f1[k] = new TF1(Form("f1%d",k),"gaus(0)+gaus(3)",h_mean[k]-2,h_mean[k]+2);
        f1[k]->SetParameters(200,-1,0.05,200,1,0.05);
        f1[k]->SetParLimits(0,10,800);
        f1[k]->SetParLimits(1,-2,0);
        f1[k]->SetParLimits(2,0,0.08);
        f1[k]->SetParLimits(3,10,800);
        f1[k]->SetParLimits(4,0,2);
        f1[k]->SetParLimits(5,0,0.08);
        h[k]->Fit(f1[k],"QMER");

        cout<<k<<"	"<<f1[k]->GetParameter(1)<<"	"<<f1[k]->GetParameter(2)<<endl;*/
    }

/*    const int con[5]={1,3,4,5,7};
    TCanvas *cc[5];
    for(int l=0;l<5;l++){
        cc[l]=new TCanvas(Form("cc%d",l),"",10,10,1600,1600);
        gPad->SetLogy();
        h[con[l]]->Draw();

        if(l==2) {continue;}
        h_mean[con[l]]=h[con[l]]->GetMean();
        h_rms[con[l]]=h[con[l]]->GetRMS();
   
        h[con[l]]->Fit("gaus","S","",h_mean[con[l]]-2,h_mean[con[l]]+2);
        store_mean[con[l]]=h[con[l]]->Fit("gaus","SQ","",h_mean[con[l]]-2,h_mean[con[l]]+2)->Parameter(1);    
        store_rms[con[l]]=h[con[l]]->Fit("gaus","SQ","",h_mean[con[l]]-2,h_mean[con[l]]+2)->Parameter(2);   
        mean[con[l]].SetTextSize(0.07);
        mean[con[l]].SetTextColor(1);
        //mean[con[l]].DrawLatex(5,1,Form("Mean = %0.2f c.t.",store_mean[con[l]])); 
  
    }*/
    

}
