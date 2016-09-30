#include "commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"
#include "cutsAndBin.h"
#include "multiTreeUtil.h"
using namespace std;


//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 
valErr getYield(int state=0, int collId=0, float ptLow=0, float ptHigh=0, float yLow=0, float yHigh=0, int cLow=0, int cHigh=0, 	float dphiEp2Low=0,  float dphiEp2High=0) ;


void getSpectra(int state = 1 ) {
  
  TH1::SetDefaultSumw2();
  //// modify by hand according to the pt range of the sample

  int nPtBins=0;
  double* ptBin;
  int nCentBins=0;
  double* centBin;



  if ( state == 1 ) { 
    nPtBins = nPtBins1s;    ptBin = ptBin1s;
    nCentBins = nCentBins1s;  centBin = centBin1s;
  }
  else if ( state == 2 ) { 
    nPtBins = nPtBins2s;    ptBin = ptBin2s;
    nCentBins = nCentBins2s;  centBin = centBin2s;
  }
  else if ( state == 3 ) { 
    nPtBins = nPtBins3s;    ptBin = ptBin3s;
    nCentBins = nCentBins3s;  centBin = centBin3s;
  }
  

  TH1D* hptEffAA[nYBins+1];
  TH1D* hptEffPP[nYBins+1];
  TH1D* hptSigAA[nYBins+1];
  TH1D* hptSigPP[nYBins+1];

  TH1D* hcentEffAA[nCentBins+1];
  TH1D* hcentEffPP[nCentBins+1];
  TH1D* hcentSigAA[nCentBins+1];
  TH1D* hcentSigPP[nCentBins+1];


  TFile* inf = new TFile(Form("efficiency/efficiency_ups%ds.root",state));
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    hptEffAA[iy]  = (TH1D*)inf->Get(Form("hptEffAA_iy%d",iy));
    hptEffPP[iy]  = (TH1D*)inf->Get(Form("hptEffPP_iy%d",iy));
  }
  
  
  TCanvas* c1 =  new TCanvas("c1","",800,400);
  c1->Divide(2,1);
  
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    c1->cd(iy);
    cleverRange(hptEffAA[iy], 1.3, 0);
    handsomeTH1(hptEffAA[iy],2);
    handsomeTH1(hptEffPP[iy],2);
    hptEffAA[iy]->Draw();
    hptEffPP[iy]->SetMarkerStyle(24);
    hptEffPP[iy]->Draw("same");
  }

  // signals :
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    hptSigAA[iy] = (TH1D*)  hptEffAA[iy]->Clone(Form("hptSigAA_iy%d",iy));
    hptSigPP[iy] = (TH1D*)  hptEffPP[iy]->Clone(Form("hptSigPP_iy%d",iy));
    hptSigAA[iy]->Reset();
    hptSigPP[iy]->Reset();
    for ( int ipt = 1 ; ipt<= nPtBins ; ipt++) {
      valErr yieldPP = getYield(state, kPPDATA, ptBin[ipt-1], ptBin[ipt], yBin[iy-1], yBin[iy], 0, 200, 0, 100);
      valErr yieldAA = getYield(state, kAADATA, ptBin[ipt-1], ptBin[ipt], yBin[iy-1], yBin[iy], 0, 200, 0, 100);
      hptSigAA[iy]->SetBinContent( ipt, yieldAA.val ) ;
      hptSigAA[iy]->SetBinError( ipt, yieldAA.err ) ;
      hptSigPP[iy]->SetBinContent( ipt, yieldPP.val ) ;
      hptSigPP[iy]->SetBinError( ipt, yieldPP.err ) ;
    }
    
  }

  
  TCanvas* c2 =  new TCanvas("c2","",800,400);
  c2->Divide(2,1);
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    c2->cd(iy);
    hptSigPP[iy]->SetAxisRange(10,1e5,"Y");
    hptSigAA[iy]->SetAxisRange(10,1e5,"Y");
    //    cleverRange(hptSigPP[iy], 1.3, 1);
    handsomeTH1(hptSigPP[iy],2);
    handsomeTH1(hptSigPP[iy],2);
    hptSigPP[iy]->SetMarkerStyle(24);
    hptSigPP[iy]->Draw();
    gPad->SetLogy();
    hptSigAA[iy]->Draw("same");
  }
  
  TH1D* hRAA1[nYBins+1];   // raw RAA w/o efficiency correction
  TH1D* hRAA[nYBins+1];   // final RAA w/ efficiency correctdion

  TCanvas* cRAA1 =  new TCanvas("cRAA1","",800,400);
  cRAA1->Divide(2,1);
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    cRAA1->cd(iy);
    hRAA1[iy] = (TH1D*)hptSigAA[iy]->Clone(Form("hRAA1_iy%d",iy));
    hRAA1[iy]->Divide( hptSigPP[iy] );
    hRAA1[iy]->Scale( 26000000. / 351 ) ;   // pp : 26pb-1,  PbPb : 351 microBarn-1
    hRAA1[iy]->Scale( 1./ (208.*208) );
    hRAA1[iy]->SetAxisRange(0,1.2,"Y");
    hRAA1[iy]->SetYTitle("R_{AA} (efficiency UNcorrected)");
    hRAA1[iy]->Draw();
    jumSun(0,1,30,1);
  }

  TCanvas* cRAA =  new TCanvas("cRAA","",800,400);
  cRAA->Divide(2,1);
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    cRAA->cd(iy);
    hRAA[iy] = (TH1D*)hRAA1[iy]->Clone(Form("hRAA_iy%d",iy));
    
    TH1D* relativeEff = (TH1D*)hptEffAA[iy]->Clone(Form("relEffAA_iy%d",iy));
    relativeEff->Divide(hptEffPP[iy]);
    hRAA[iy]->Divide( relativeEff ) ;
    hRAA[iy]->SetAxisRange(0,1.2,"Y");
    hRAA[iy]->SetYTitle("R_{AA} (efficiency corrected)");
    hRAA[iy]->Draw();
    jumSun(0,1,30,1);
  }



  
  
}

valErr getYield(int state, int collId, float ptLow, float ptHigh, float yLow, float yHigh, int cLow, int cHigh,
		float dphiEp2Low,  float dphiEp2High) {
  TString kineLabel = getKineLabel (collId, ptLow, ptHigh, yLow, yHigh, glbMuPtCut, cLow, cHigh, dphiEp2Low, dphiEp2High) ;
  TString SignalCB = "Double";
  TFile* inf = new TFile(Form("fitResults/dataFit_fixParam1MuPt4_2016_08_30/fitresults_upsilon_%sCB_%s.root",SignalCB.Data(),kineLabel.Data()));
  TH1D* fitResults = (TH1D*)inf->Get("fitResults");
  valErr ret; 
  ret.val = fitResults->GetBinContent(state);
  ret.err = fitResults->GetBinError(state);
  cout << kineLabel << ": " << ret.val << " +/- " << ret.err << endl; 
  return ret;
}
