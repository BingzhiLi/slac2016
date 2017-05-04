void plotter()
{
    TFile *f=new TFile("../art_output_root/center.root");
    f->cd("MyAnalyzer");

    //cos#theta distribution 
    gStyle->SetOptStat(0);
    TCanvas *c1=new TCanvas("c1","",10,10,600,450);

    cos#theta_31->SetTitle( "cos#theta"); 
    cos#theta_31->SetLineColor(1);  
    cos#theta_31->DrawNormalized();
  
    cos#theta_32->SetLineColor(2);   
    cos#theta_32->DrawNormalized("same");

    cos#theta_30->SetLineColor(3);            
    cos#theta_30->DrawNormalized("same");

    TLine *l1=new TLine(-0.9,0.04,-0.8,0.04);
    TLine *l2=new TLine(-0.9,0.035,-0.8,0.035);
    TLine *l3=new TLine(-0.9,0.03,-0.8,0.03);
    l1->SetLineColor(1);
    l2->SetLineColor(2);
    l3->SetLineColor(3);
    
    gStyle->SetLegendBorderSize(0);
    TLegend* leg=new TLegend(0.2,0.6,0.35,0.8);
    leg->AddEntry(l3,"#30 cos#theta","L");
    leg->AddEntry(l1,"#31 cos#theta","L");
    leg->AddEntry(l2,"#32 cos#theta","L");
    leg->Draw("same");

    //dE vs dT
    TCanvas *c2=new TCanvas("c2","",10,10,700,450);
    gStyle->SetOptStat();
    deltaE_vs_deltaT_#32#30->Draw("colz"); 

    //create time vs arrival time
    TCanvas *c3=new TCanvas("c3","",10,10,1200,450);
    gStyle->SetOptStat(0); 
    c3->Divide(3,1);

        c3->cd(1);
	gPad->SetLeftMargin(0.15);
        gPad->SetTopMargin(0.075);
        h_creationT_vs_arrivalT_32->GetZaxis()->SetRangeUser(0,10000);
        h_creationT_vs_arrivalT_32->SetTitle("Xtal#32");
        gPad->SetLogz();
        h_creationT_vs_arrivalT_32->Draw("col");
        /*c3_1->Update();
        TPaletteAxis *palette1 = (TPaletteAxis*)h_creationT_vs_arrivalT_32->GetListOfFunctions()->FindObject("palette");
        palette1->SetX1NDC(0.88);
        palette1->SetX2NDC(0.93);
        palette1->SetY1NDC(0.1);
        palette1->SetY2NDC(0.9);
        c3_1->Modified();
        c3_1->Update();*/

        c3->cd(2);
        gPad->SetTopMargin(0.075);
        h_creationT_vs_arrivalT_31->GetZaxis()->SetRangeUser(0,10000);
        h_creationT_vs_arrivalT_31->SetTitle("Xtal#31");
        gPad->SetLogz();
        h_creationT_vs_arrivalT_31->Draw("col");
        /*c3_2->Update();
        TPaletteAxis *palette2 = (TPaletteAxis*)h_creationT_vs_arrivalT_31->GetListOfFunctions()->FindObject("palette");
        palette2->SetX1NDC(0.88);
        palette2->SetX2NDC(0.93);
        palette2->SetY1NDC(0.1);
        palette2->SetY2NDC(0.9);
        c3_2->Modified();
        c3_2->Update();*/

        c3->cd(3);
        gPad->SetTopMargin(0.075);
        gPad->SetRightMargin(0.10);
        h_creationT_vs_arrivalT_30->GetZaxis()->SetRangeUser(0,10000);
        h_creationT_vs_arrivalT_30->SetTitle("Xtal#30");
        gPad->SetLogz();
        h_creationT_vs_arrivalT_30->Draw("colz");
        c3_3->Update();
        TPaletteAxis *palette3 = (TPaletteAxis*)h_creationT_vs_arrivalT_30->GetListOfFunctions()->FindObject("palette");
        palette3->SetX1NDC(0.88);
        palette3->SetX2NDC(0.93);
        palette3->SetY1NDC(0.1);
        palette3->SetY2NDC(0.925);
        c3_3->Modified();
        c3_3->Update();   

}
