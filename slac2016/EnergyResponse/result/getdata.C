void getdata()
{ 
    ifstream in;
    in.open("xtalEnergyRes.dat");
    Float_t x,y;
    Int_t nl=0;
    TFile *f=new TFile("XtalEnergyRes.root","create");
    TTree *tree=new TTree("tree","");
    tree->Branch("x",&x,"x/F");
    tree->Branch("y",&y,"y/F");

    while(1)
    {
        in>>x>>y;
        if(!in.good()) break;
        if(nl<55)                    
            tree->Fill();
            nl++;
    }
    in.close();
    f->Write();

}
