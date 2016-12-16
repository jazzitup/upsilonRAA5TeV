#include "../commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"
#include "../cutsAndBin.h"
#include "../multiTreeUtil.h"
using namespace std;


//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 

TLegend *leg = new TLegend(0.55,0.2, 0.85,0.4,NULL,"brNDC");

void addInQuad ( TH1D* h0=0, TH1D* h1=0) ;
void getDevRatio ( TH1D* h0=0, TH1D* h1=0) ;

void getTnpSys(int state =1, int Nsamples=100) { 
  TH1::SetDefaultSumw2();

  TFile* f1 = new TFile(Form("efficiencyTable/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx0.root",state) );
  TH1D* eff1 = (TH1D*)f1->Get("hptEffPP");
  TH1D* eff2 = (TH1D*)f1->Get("hptEffAA");
  TH1D* eff3 = (TH1D*)f1->Get("hrapEffPP");
  TH1D* eff4 = (TH1D*)f1->Get("hrapEffAA");
  TH1D* eff5 = (TH1D*)f1->Get("hcentintEffPP");
  TH1D* eff6 = (TH1D*)f1->Get("hcentintEffAA");
  TH1D* eff7 = (TH1D*)f1->Get("hcentEffAA");

  TH1D* eff1sys = (TH1D*)eff1->Clone("hptEffPPSys"); eff1sys->Reset();
  TH1D* eff2sys = (TH1D*)eff2->Clone("hptEffAASys"); eff2sys->Reset();
  TH1D* eff3sys = (TH1D*)eff3->Clone("hrapEffPPSys"); eff3sys->Reset();
  TH1D* eff4sys = (TH1D*)eff4->Clone("hrapEffAASys"); eff4sys->Reset();
  TH1D* eff5sys = (TH1D*)eff5->Clone("hcentintEffPPSys"); eff5sys->Reset();
  TH1D* eff6sys = (TH1D*)eff6->Clone("hcentintEffAASys"); eff6sys->Reset();
  TH1D* eff7sys = (TH1D*)eff7->Clone("hcentEffAASys"); eff7sys->Reset();
  
  // Stat fluctuation : 
  for ( int idx=1 ; idx<= Nsamples ; idx++) {
    cout <<"Reading "  << idx<<"th file..." << endl;
    TFile* fid = new TFile(Form("efficiencyTableSys/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx%d.root",state,idx) );
    TH1D* relativeDev1 = (TH1D*)fid->Get("hptEffPP");
    TH1D* relativeDev2 = (TH1D*)fid->Get("hptEffAA");
    TH1D* relativeDev3 = (TH1D*)fid->Get("hrapEffPP");
    TH1D* relativeDev4 = (TH1D*)fid->Get("hrapEffAA");
    TH1D* relativeDev5 = (TH1D*)fid->Get("hcentintEffPP");
    TH1D* relativeDev6 = (TH1D*)fid->Get("hcentintEffAA");
    TH1D* relativeDev7 = (TH1D*)fid->Get("hcentEffAA");
    
    relativeDev1->Add( eff1, -1 );     relativeDev1->Divide( eff1);
    relativeDev2->Add( eff2, -1 );     relativeDev2->Divide( eff2);
    relativeDev3->Add( eff3, -1 );     relativeDev3->Divide( eff3);
    relativeDev4->Add( eff4, -1 );     relativeDev4->Divide( eff4);
    relativeDev5->Add( eff5, -1 );     relativeDev5->Divide( eff5);
    relativeDev6->Add( eff6, -1 );     relativeDev6->Divide( eff6);
    relativeDev7->Add( eff7, -1 );     relativeDev7->Divide( eff7);

    addInQuad( eff1sys, relativeDev1 ) ;
    addInQuad( eff2sys, relativeDev2 ) ;
    addInQuad( eff3sys, relativeDev3 ) ;
    addInQuad( eff4sys, relativeDev4 ) ;
    addInQuad( eff5sys, relativeDev5 ) ;
    addInQuad( eff6sys, relativeDev6 ) ;
    addInQuad( eff7sys, relativeDev7 ) ;
    fid->Close();
  }
  eff1sys->Scale( 1./sqrt( float(Nsamples) ) );
  eff2sys->Scale( 1./sqrt( float(Nsamples) ) );
  eff3sys->Scale( 1./sqrt( float(Nsamples) ) );
  eff4sys->Scale( 1./sqrt( float(Nsamples) ) );
  eff5sys->Scale( 1./sqrt( float(Nsamples) ) );
  eff6sys->Scale( 1./sqrt( float(Nsamples) ) );
  eff7sys->Scale( 1./sqrt( float(Nsamples) ) );
  TFile* fout = new TFile(Form("sys_tnp_ups%d.root",state),"recreate");
  eff1sys->Write();
  eff2sys->Write();
  eff3sys->Write();
  eff4sys->Write();
  eff5sys->Write();
  eff6sys->Write();
  eff7sys->Write();
  
}

void addInQuad ( TH1D* h0, TH1D* h1) { 
  if ( h0->GetNbinsX() != h1->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  for ( int i=1 ;  i<=h0->GetNbinsX(); i++) {
    float x0 =  h0->GetBinContent(i);
    float x1 =  h1->GetBinContent(i);
    h0->SetBinContent(i,  sqrt ( x0*x0 + x1*x1 ) );
  }
}
