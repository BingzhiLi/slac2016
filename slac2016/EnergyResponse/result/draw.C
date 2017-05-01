void draw()
{
   //打开root file
   TFile *f=new TFile("XtalEnergyRes.root");
   //读取tree
   TTree *tree = (TTree*)f->Get("tree");
   Float_t x, y,m[54],n[54],sumY=0,meanY;
   tree->SetBranchAddress("x",&x);
   tree->SetBranchAddress("y",&y);
   Int_t nentries = (Int_t)tree->GetEntries();
   for (Int_t i=0; i<nentries; i++) {
      tree->GetEntry(i);
      m[i]=x;
      n[i]=y;
      sumY=sumY+n[i];
   }
   //计算平均值
   meanY=sumY/54;
   //cout<<meanY<<endl;
   //画平均值上下5%和10%范围线
   TLine *l1=new TLine(-0.5,meanY*0.95,59,meanY*0.95);
   TLine *l2=new TLine(-0.5,meanY*1.05,59,meanY*1.05);
   TLine *l3=new TLine(-0.5,meanY*0.9,59,meanY*0.9);
   TLine *l4=new TLine(-0.5,meanY*1.1,59,meanY*1.1);
   //定义graph和画布
   TGraph *g=new TGraph(54,m,n);
   TCanvas *c=new TCanvas("c","",10,10,900,900);
   //定义数据点的形状
   g->SetMarkerStyle(20);
   //设置坐标范围与标题
   g->GetYaxis()->SetRangeUser(0,2500);
   g->GetXaxis()->SetRangeUser(-2,60);
   g->GetXaxis()->SetTitle("xtal Num");
   g->GetYaxis()->SetTitle("xtal response [#photon]");
   g->SetTitle("Xtal Energy Response");
   //画出graph与line，设置线型线宽颜色
   g->Draw("AP");  
   l1->SetLineColor(2);
   l2->SetLineColor(2);
   l3->SetLineColor(4);
   l4->SetLineColor(4);
   l1->SetLineWidth(3);
   l2->SetLineWidth(3);
   l3->SetLineWidth(3);
   l4->SetLineWidth(3); 
   l1->SetLineStyle(5);
   l2->SetLineStyle(5);
   l3->SetLineStyle(7);
   l4->SetLineStyle(7);
   l1->Draw("same");
   l2->Draw("same");
   l3->Draw("same");
   l4->Draw("same");
   //设置图例
   gStyle->SetLegendBorderSize(0);//去除图例边框
   g->GetYaxis()->SetTitleOffset(1.2);//设置坐标轴与坐标轴标题的距离
   TLegend* leg=new TLegend(0.7,0.2,0.85,0.4);//设置图例位置
   leg->AddEntry(l1,"#pm 5%","L");
   leg->AddEntry(l3,"#pm 10%","L");
   leg->Draw("");
   g->GetYaxis()->SetTitleOffset(1.2);//设置坐标轴与坐标轴标题的距离

   //创建画布
   TCanvas *c1=new TCanvas("c1","",10,10,1200,1200);
   TH2F *h=new TH2F("h","xtalEnergy",9,0,9,6,0,6);
   h->GetXaxis()->SetTitle("xtal column [xtal8-xtal0]");
   h->GetYaxis()->SetTitle("xtal row [xtal8-xtal53]");
   gStyle->SetOptStat(0);
   gPad->SetGrid();
   for(int r=0;r<6;r++){
       for(int col=0;col<9;col++){
           h->Fill(col+0.5,r+0.5,n[9*(r+1)-col-1]); 

       }
   }
   h->Draw("TEXT COLZ");
   gStyle->SetPalette(1);
   

}
