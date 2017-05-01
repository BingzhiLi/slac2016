void fitDraw(){

    TFile *f=new TFile("gm2slac_run01937.root.root");

    TH2D *h[10];
    TCanvas *c[10];
    TLine *l1[10]={}; 
    TLine *l2[10]={};
   
    TString t[10]={};
    t[0]="beam_deltaE_deltaT_Num33_Num25";
    t[1]="beam_deltaE_deltaT_Num33_Num24";
    t[2]="beam_deltaE_deltaT_Num33_Num23";
    t[3]="beam_deltaE_deltaT_Num33_Num15";
    t[4]="beam_deltaE_deltaT_Num25_Num24";
    t[5]="beam_deltaE_deltaT_Num25_Num23";
    t[6]="beam_deltaE_deltaT_Num25_Num15";
    t[7]="beam_deltaE_deltaT_Num24_Num23";
    t[8]="beam_deltaE_deltaT_Num24_Num15";
    t[9]="beam_deltaE_deltaT_Num23_Num15";
    
    const int num[10]= {33,33,33,33,25,25,25,24,24,23};
    const int num1[10]={25,24,23,15,24,23,15,23,15,15};

    for(int i=0;i<10;i++){
        h[i]=(TH2D*)f->Get(t[i]);
        c[i]=new TCanvas(Form("c%d",i),"",10,10,800,450);
        h[i]->SetXTitle(Form("#Deltat [c.t.]"));
        h[i]->SetYTitle(Form("#DeltaE [#photo]"));
        h[i]->Draw("colz");
        l1[i]=new TLine(-2,h[i]->GetMean(2),5,h[i]->GetMean(2));   
        l2[i]= new TLine(h[i]->GetMean(1),-500,h[i]->GetMean(1),500); 
    	l1[i]->SetLineStyle(5);
    	l1[i]->SetLineWidth(3);
    	l2[i]->SetLineStyle(5);
    	l2[i]->SetLineWidth(3);
    	l1[i]->Draw();
    	l2[i]->Draw("same");
        cout<<i<<endl;
        c[i]->Print(Form("run1937_deltaE_vs_deltaT_%d_%d.png",num[i],num1[i]));
    }

    
}
