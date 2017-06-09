void plotter()
{
    TFile *f=new TFile("20K.root");
    f->cd("MyAnalyzer");

    gStyle->SetOptStat(0);
/*
    //photon_arrival_time
    gStyle->SetOptStat(0);
    TCanvas *c0=new TCanvas("c0","",10,10,600,450);
    photon_arrival_time_30->SetTitle("Cherenkov Photon Arrival PMT Time");
    photon_arrival_time_30->SetLineColor(1);
    photon_arrival_time_30->DrawNormalized();
    photon_arrival_time_31->SetLineColor(2);
    photon_arrival_time_31->DrawNormalized("same");
    photon_arrival_time_32->SetLineColor(3);    
    photon_arrival_time_32->DrawNormalized("same");
    TLine *l01=new TLine(-0.9,0.04,-0.8,0.04);
    TLine *l02=new TLine(-0.9,0.035,-0.8,0.035);
    TLine *l03=new TLine(-0.9,0.03,-0.8,0.03);
    l01->SetLineColor(1);
    l02->SetLineColor(2);
    l03->SetLineColor(3);    
    gStyle->SetLegendBorderSize(0);
    TLegend* leg0=new TLegend(0.6,0.6,0.8,0.8);
    leg0->AddEntry(l01,"#30 right crystal","L");
    leg0->AddEntry(l02,"#31 hit crystal","L");
    leg0->AddEntry(l03,"#32 left crystal","L");
    leg0->Draw("same");
    
    //cos#theta distribution 
    gStyle->SetOptStat(0);
    TCanvas *c1=new TCanvas("c1","",10,10,600,450);

    costheta_31->SetTitle( "cos#theta"); 
    costheta_31->SetLineColor(1);  
    costheta_31->DrawNormalized();
  
    costheta_32->SetLineColor(2);   
    costheta_32->DrawNormalized("same");

    costheta_30->SetLineColor(3);            
    costheta_30->DrawNormalized("same");

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
*/

    //dE vs dT
    TCanvas *c2=new TCanvas("c2","",10,10,700,450);
    gStyle->SetOptStat(0);
    deltaE_vs_deltaT_32_30->Draw("colz"); 

/*
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

/*    c3->cd(2);
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
/*
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

    //shower shape xy xz z
    TCanvas *c4=new TCanvas("c4","c4",0,0,1200,450);
    c4->Divide(3,1,0,0);
 	c4->cd(1);
    gPad->SetLeftMargin(0.15);
    gPad->SetTopMargin(0.075);
	photon_shower_xy_32->GetZaxis()->SetRangeUser(0,10000);
	photon_shower_xy_32->SetTitle("Xtal#32");
    gPad->SetLogz();
    photon_shower_xy_32->Draw("col");
    c4->cd(2);
    gPad->SetTopMargin(0.075);
    photon_shower_xy_31->GetZaxis()->SetRangeUser(0,10000);
    photon_shower_xy_31->SetTitle("Xtal#31");
    gPad->SetLogz();
    photon_shower_xy_31->Draw("col");
	c4->cd(3);
    gPad->SetTopMargin(0.075);
    gPad->SetRightMargin(0.10);
    photon_shower_xy_30->GetZaxis()->SetRangeUser(0,10000);
    photon_shower_xy_30->SetTitle("Xtal#30");
    gPad->SetLogz();
    photon_shower_xy_30->Draw("colz");
    c4_3->Update();
    TPaletteAxis *palette1 = (TPaletteAxis*)photon_shower_xy_30->GetListOfFunctions()->FindObject("palette");
    palette1->SetX1NDC(0.88);
    palette1->SetX2NDC(0.93);
    palette1->SetY1NDC(0.1);
    palette1->SetY2NDC(0.925);
    c4_3->Modified();
    c4_3->Update();   

    TCanvas *c5=new TCanvas("c5","c5",0,0,1200,450);
    c5->Divide(3,1,0,0);
 	c5->cd(1);
    gPad->SetLeftMargin(0.15);
    gPad->SetTopMargin(0.075);
	photon_shower_xz_32->GetZaxis()->SetRangeUser(0,10000);
	photon_shower_xz_32->SetTitle("Xtal#32");
    gPad->SetLogz();
    photon_shower_xz_32->Draw("col");
    c5->cd(2);
    gPad->SetTopMargin(0.075);
    photon_shower_xz_31->GetZaxis()->SetRangeUser(0,10000);
    photon_shower_xz_31->SetTitle("Xtal#31");
    gPad->SetLogz();
    photon_shower_xz_31->Draw("col");
    c5->cd(3);
    gPad->SetTopMargin(0.075);
    gPad->SetRightMargin(0.10);
    photon_shower_xz_30->GetZaxis()->SetRangeUser(0,10000);
    photon_shower_xz_30->SetTitle("Xtal#30");
    gPad->SetLogz();
    photon_shower_xz_30->Draw("colz");
    c5_3->Update();
    TPaletteAxis *palette2 = (TPaletteAxis*)photon_shower_xz_30->GetListOfFunctions()->FindObject("palette");
    palette2->SetX1NDC(0.88);
    palette2->SetX2NDC(0.93);
    palette2->SetY1NDC(0.1);
    palette2->SetY2NDC(0.925);
    c5_3->Modified();
    c5_3->Update();   

    TCanvas *c6=new TCanvas("c6","c6",10,10,700,450);
    photon_shower_depth_32->SetTitle("Cherenkov Photon Creation Depth");
    photon_shower_depth_32->SetXTitle("depth [mm]");
    photon_shower_depth_32->SetLineColor(1);
    photon_shower_depth_32->DrawNormalized();
    photon_shower_depth_31->SetLineColor(2);
    photon_shower_depth_31->DrawNormalized("same");
    photon_shower_depth_30->SetLineColor(3);    
    photon_shower_depth_30->DrawNormalized("same");
    gStyle->SetLegendBorderSize(0);
    TLegend* leg6=new TLegend(0.7,0.7,0.9,0.88);
    leg6->AddEntry(photon_shower_depth_30,"#30 right crystal","L");
    leg6->AddEntry(photon_shower_depth_31,"#31 hit crystal","L");
    leg6->AddEntry(photon_shower_depth_32,"#32 left crystal","L");
    leg6->Draw("same");

*/
    //beam time 
    gStyle->SetOptStat(0);
    TCanvas *c7=new TCanvas("c7","c7",10,10,700,450);
    beam_time_31->SetTitle("Beam Time");
    beam_time_31->SetLineColor(1);
    beam_time_31->DrawNormalized();
    beam_time_32->SetLineColor(2);
    beam_time_32->DrawNormalized("same");
    beam_time_30->SetLineColor(3);    
    beam_time_30->DrawNormalized("same");
    gStyle->SetLegendBorderSize(0);
    TLegend* leg7=new TLegend(0.7,0.7,0.9,0.88);
    leg7->AddEntry(beam_time_30,"#30 right crystal","L");
    leg7->AddEntry(beam_time_31,"#31 hit crystal","L");
    leg7->AddEntry(beam_time_32,"#32 left crystal","L");
    leg7->Draw("same");

    //PDG ID
    TCanvas *c8=new TCanvas("c8","c8",10,10,700,450);
    pdg_id->SetMarkerSize(2);
    pdg_id->Draw("colz text");
  
/*
    //arrival time vs depth
    TCanvas *c9=new TCanvas("c9","c9",10,10,1200,450);
    gStyle->SetOptStat(0); 
    c9->Divide(3,1);
    c9->cd(1);
	gPad->SetLeftMargin(0.15);
    gPad->SetTopMargin(0.075);
    arrival_T_vs_depth_32->GetZaxis()->SetRangeUser(0,10000);
    arrival_T_vs_depth_32->SetTitle("Xtal#32");
    gPad->SetLogz();
    arrival_T_vs_depth_32->Draw("col");
    c9->cd(2);
    gPad->SetTopMargin(0.075);
    arrival_T_vs_depth_31->GetZaxis()->SetRangeUser(0,10000);
    arrival_T_vs_depth_31->SetTitle("Xtal#31");
    gPad->SetLogz();
    arrival_T_vs_depth_31->Draw("col");
    c9->cd(3);
    gPad->SetTopMargin(0.075);
    gPad->SetRightMargin(0.10);
    arrival_T_vs_depth_30->GetZaxis()->SetRangeUser(0,10000);
    arrival_T_vs_depth_30->SetTitle("Xtal#30");
    gPad->SetLogz();
    arrival_T_vs_depth_30->Draw("colz");
    c9_3->Update();
    TPaletteAxis *palette9 = (TPaletteAxis*)arrival_T_vs_depth_30->GetListOfFunctions()->FindObject("palette");
    palette9->SetX1NDC(0.88);
    palette9->SetX2NDC(0.93);
    palette9->SetY1NDC(0.1);
    palette9->SetY2NDC(0.925);
    c9_3->Modified();
    c9_3->Update();  
 
    //creation time vs depth
    TCanvas *c10=new TCanvas("c10","c10",10,10,1200,450);
    c10->Divide(3,1);
    c10->cd(1);
	gPad->SetLeftMargin(0.15);
    gPad->SetTopMargin(0.075);
    creation_T_vs_depth_32->GetZaxis()->SetRangeUser(0,10000);
    creation_T_vs_depth_32->SetTitle("Xtal#32");
    gPad->SetLogz();
    creation_T_vs_depth_32->Draw("col");
    c10->cd(2);
    gPad->SetTopMargin(0.075);
    creation_T_vs_depth_31->GetZaxis()->SetRangeUser(0,10000);
    creation_T_vs_depth_31->SetTitle("Xtal#31");
    gPad->SetLogz();
    creation_T_vs_depth_31->Draw("col");
    c10->cd(3);
    gPad->SetTopMargin(0.075);
    gPad->SetRightMargin(0.10);
    creation_T_vs_depth_30->GetZaxis()->SetRangeUser(0,10000);
    creation_T_vs_depth_30->SetTitle("Xtal#30");
    gPad->SetLogz();
    creation_T_vs_depth_30->Draw("colz");
    c10_3->Update();
    TPaletteAxis *palette10 = (TPaletteAxis*)creation_T_vs_depth_30->GetListOfFunctions()->FindObject("palette");
    palette10->SetX1NDC(0.88);
    palette10->SetX2NDC(0.93);
    palette10->SetY1NDC(0.1);
    palette10->SetY2NDC(0.925);
    c10_3->Modified();
    c10_3->Update();       
*/   
   
    


}
