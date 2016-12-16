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

void getTnpSys(int state =1, int Nsamples=10) { 
  TH1::SetDefaultSumw2();

  TFile* f1 = new TFile(Form("efficiencyTable/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx0.root",state) );
  TH1D* hptEffPP = (TH1D*)f1->Get("hptEffPP");
  TH1D* hptEffAA = (TH1D*)f1->Get("hptEffAA");
  TH1D* hrapEffPP = (TH1D*)f1->Get("hrapEffPP");
  TH1D* hrapEffAA = (TH1D*)f1->Get("hrapEffAA");
  TH1D* hcentintEffPP = (TH1D*)f1->Get("hcentintEffPP");
  TH1D* hcentintEffAA = (TH1D*)f1->Get("hcentintEffAA");
  TH1D* hcentEffAA = (TH1D*)f1->Get("hcentEffAA");

  TH1D* hptEffPPsys = (TH1D*)hptEffPP->Clone("hptEffPPSys"); hptEffPPsys->Reset();
  TH1D* hptEffAAsys = (TH1D*)hptEffAA->Clone("hptEffAASys"); hptEffAAsys->Reset();
  TH1D* hrapEffPPsys = (TH1D*)hrapEffPP->Clone("hrapEffPPSys"); hrapEffPPsys->Reset();
  TH1D* hrapEffAAsys = (TH1D*)hrapEffAA->Clone("hrapEffAASys"); hrapEffAAsys->Reset();
  TH1D* hcentintEffPPsys = (TH1D*)hcentintEffPP->Clone("hcentintEffPPSys"); hcentintEffPPsys->Reset();
  TH1D* hcentintEffAAsys = (TH1D*)hcentintEffAA->Clone("hcentintEffAASys"); hcentintEffAAsys->Reset();
  TH1D* hcentEffAAsys = (TH1D*)hcentEffAA->Clone("hcentEffAASys"); hcentEffAAsys->Reset();
  
  // Stat fluctuation : 
  for ( int idx=1 ; idx<= Nsamples ; idx++) {
    TFile* fid = new TFile(Form("efficiencyTableSys/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx%d.root",state,idx) );
    TH1D* hptDevRatPP = (TH1D*)fid->Get("hptEffPP");
    TH1D* hptDevRatAA = (TH1D*)fid->Get("hptEffAA");
    TH1D* hrapDevRatPP = (TH1D*)fid->Get("hrapEffPP");
    TH1D* hrapDevRatAA = (TH1D*)fid->Get("hrapEffAA");
    TH1D* hcentintDevRatPP = (TH1D*)fid->Get("hcentintEffPP");
    TH1D* hcentintDevRatAA = (TH1D*)fid->Get("hcentintEffAA");
    TH1D* hcentDevRatAA = (TH1D*)fid->Get("hcentEffAA");
    
    hptDevRatPP->Add( hptEffPP, -1 );     hptDevRatPP->Divide( hptEffPP);
    hptDevRatAA->Add( hptEffAA, -1 );    hptDevRatAA->Divide( hptEffAA);
    hrapDevRatPP->Add( hrapEffPP, -1 );     hrapDevRatPP->Divide( hrapEffPP);
    hrapDevRatAA->Add( hrapEffAA, -1 );     hrapDevRatAA->Divide( hrapEffAA);
    hcentintDevRatPP->Add( hcentintEffPP, -1 );    hcentintDevRatPP->Divide( hcentintEffPP);
    hcentintDevRatAA->Add( hcentintEffAA, -1 );    hcentintDevRatAA->Divide( hcentintEffAA);
    hcentDevRatAA->Add( hcentEffAA, -1 );          hcentDevRatAA->Divide( hcentEffAA);

    addInQuad( hptEffPPsys, hptDevRatPP ) ;
    addInQuad( hptEffAAsys, hptDevRatAA ) ;
    addInQuad( hrapEffPPsys, hrapDevRatPP ) ;
    addInQuad( hrapEffAAsys, hrapDevRatAA ) ;
    addInQuad( hcentintEffPPsys, hcentintDevRatPP ) ;
    addInQuad( hcentintEffAAsys, hcentintDevRatAA ) ;
    addInQuad( hcentEffAAsys, hcentDevRatAA ) ;
    fid->Close();
  }


}

void addInQuad ( TH1D* h0, TH1D* h1) { 
  if ( h0->GetNbinsX() != h1->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  for ( int i=1 ;  i<=h0->GetNbinsX(); i++) {
    float x0 =  h0->GetBinContent(i);
    float x1 =  h1->GetBinContent(i);
    h0->SetBinContent(i,  sqrt ( x0*x0 + x1*x1 ) );
  }
}
