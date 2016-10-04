#include "commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TStyle.h"
#include "TFile.h"
#include "TColor.h"
#include "cutsAndBin.h"
#include "multiTreeUtil.h"
using namespace std;


//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 
valErr getYield(int state=0, int collId=0, float ptLow=0, float ptHigh=0, float yLow=0, float yHigh=0, int cLow=0, int cHigh=0, 	float dphiEp2Low=0,  float dphiEp2High=0) ;


void getSpectra(int state = 1 ) {
  
  TH1::SetDefaultSumw2();
  //// modify by hand according to the pt range of the sample

  gStyle->SetEndErrorSize(0);
  gStyle->SetOptStat(0);
  int nPtBins=0;
  double* ptBin;
  int nCentBins=0;
  double* centBin;

  TFile *wf = new TFile(Form("Ups_%d_RAA.root",state),"recreate");


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
  
  hcentEffAA[0] = (TH1D*) inf -> Get("hcentEffAA_iy1");
  hcentEffPP[0] = (TH1D*) inf -> Get("hcentEffPP_iy1");

  for(int ibin=1;ibin<10;ibin++)
  {
   hcentEffPP[0]->SetBinContent(ibin,hcentEffPP[0]->GetBinContent(1)); 
   hcentEffPP[0]->SetBinError(ibin,hcentEffPP[0]->GetBinError(1)); 
  }
  hcentSigAA[0] = (TH1D*) hcentEffAA[0]->Clone("hcentSigAA_cent");
  hcentSigPP[0] = (TH1D*) hcentEffPP[0]->Clone("hcentSigPP_cent");
  hcentSigAA[0] -> Reset(); 
  hcentSigPP[0] -> Reset(); 
  
  TH1D *hSetBin;
  hSetBin = (TH1D*) hcentSigAA[0] ->Clone("hSetBin");
  TH1D *hcentEffAA_int = (TH1D*) inf -> Get("hcentEffAA_int");
  TH1D *hcentEffPP_int = (TH1D*) inf -> Get("hcentEffPP_int");
  TH1D *hcentSigAA_int = (TH1D*) hcentEffAA_int -> Clone("hcentSigAA_int");
  TH1D *hcentSigPP_int = (TH1D*) hcentEffAA_int -> Clone("hcentSigPP_int");
  hcentSigAA_int->Reset();
  hcentSigPP_int->Reset();

  // signals :

  double nColl1[9] = {1819,1432,1005,606,349,186,90.7,40.1,7.67};
  double nSetBin[9]={0.};
  for(int icent=1; icent<=nCentBins;icent++)
  {
    valErr yCentAA = getYield(state,kAADATA,0,30,0,2.4,centBin[icent-1],centBin[icent],0,100); 
    valErr yCentPP = getYield(state,kPPDATA,0,30,0,2.4,centBin[icent-1],centBin[icent],0,100);
    hSetBin -> SetBinContent(icent,(double)((centBin[icent]-centBin[icent-1])*nColl1[icent-1]));
    hcentSigAA[0] -> SetBinContent(icent,yCentAA.val);
    hcentSigAA[0] -> SetBinError(icent,yCentAA.err);
    hcentSigPP[0] -> SetBinContent(icent,yCentPP.val);
    hcentSigPP[0] -> SetBinError(icent,yCentPP.err);
  }
  valErr yCentAA_int = getYield(state,kAADATA,0,30,0,2.4,0,200,0,100);
  valErr yCentPP_int = getYield(state,kPPDATA,0,30,0,2.4,0,200,0,100);
  hcentSigAA_int -> SetBinContent(1,yCentAA_int.val);
  hcentSigAA_int -> SetBinError(1,yCentAA_int.err);
  hcentSigPP_int -> SetBinContent(1,yCentPP_int.val);
  hcentSigPP_int -> SetBinError(1,yCentPP_int.err);
  
  TH1D *hRAA_int;
  hRAA_int = (TH1D*) hcentSigAA_int->Clone("hRAA_centint");
  hRAA_int ->Divide(hcentSigPP_int);
  hRAA_int ->Scale( 26000000. / 351 ) ;   // pp : 26pb-1,  PbPb : 351 microBarn-1
  hRAA_int ->Scale( 1./(208*208));
  hcentEffAA_int->Divide(hcentEffPP_int);
  hRAA_int ->Divide(hcentEffAA_int);
  hRAA_int ->SetAxisRange(0,1.6,"Y");
  hRAA_int ->SetYTitle("R_{AA} (efficiency UNcorrected)");
  
  TGraphErrors *gre_int = new TGraphErrors();
  gre_int->SetName("gre_int");
  gre_int->SetTitle("gre_int");
  gre_int->SetPoint(0,1,hRAA_int->GetBinContent(1));
  gre_int->SetPointError(0,0,hRAA_int->GetBinError(1));


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
  TH1D* hRAA2;   // raw RAA w/o efficiency correction
  TH1D* hRAA3;   // final cent RAA w/ efficiency correction
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

  TCanvas* cRAA2 =  new TCanvas("cRAA2","",800,400);
  cRAA2->cd();
  hRAA2 = (TH1D*) hcentSigAA[0]->Clone("hRAA_cent");
  hRAA2 ->Divide(hcentSigPP[0]);
  hRAA2 ->Divide(hSetBin);
  hRAA2 ->Scale( 26000000. / 351 ) ;   // pp : 26pb-1,  PbPb : 351 microBarn-1
  hRAA2 ->Scale( 1./(208*208));
  hRAA2 ->Scale(200.*392.);
  hRAA2 ->SetAxisRange(0,1.2,"Y");
  hRAA2 ->SetYTitle("R_{AA} (efficiency UNcorrected)");
//  hRAA2 ->Draw();
  jumSun(0,1,30,1);
  
  TGraphErrors *gre1 = new TGraphErrors(9);
  gre1->SetName("Graph0");
  gre1->SetTitle("Graph");

  Int_t cii;      // for color index setting
  TColor *color; // for color definition with alpha
  cii = TColor::GetColor("#6699ff");
  double nPart[9] = {15.47,30.59,53.85,86.95,131.4,189.2,264.3,333.4,384.4};
  gre1->SetFillColor(cii);
  gre1->SetMarkerStyle(20);
  for(int ibin=0;ibin<9;ibin++){
  gre1->SetPoint(ibin,nPart[ibin],hRAA2->GetBinContent(9-ibin));
  gre1->SetPointError(ibin,10,hRAA2->GetBinError(9-ibin));}
  gre1->Draw();

  for(int ibin = 1; ibin<10; ibin++)
  {
    cout << "dsad : " << hRAA2->GetBinContent(ibin) << endl;
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

  TCanvas* cRAA3 =  new TCanvas("cRAA3","",800,400);
  cRAA3->cd();
  hRAA3 = (TH1D*) hRAA2 ->Clone("hRAA_cent_final");
  TH1D* relativeEff_cent = (TH1D*) hcentEffAA[0] -> Clone("relativeEff_cent");
  relativeEff_cent -> Divide(hcentEffPP[0]);
  hRAA3 -> Divide(relativeEff_cent);
  hRAA3 -> SetAxisRange(0,1.2,"Y");
  hRAA3 -> SetTitle("R_{AA} (efficiency corrected)");
  
  TGraphErrors *gre = new TGraphErrors(9);
  gre->SetName("Graph0");
  gre->SetTitle("Graph");

  Int_t ci;
  ci = TColor::GetColor("#6699ff");
  gre->SetFillColor(ci);
  gre->SetMarkerStyle(10);
  for(int ibin=0;ibin<9;ibin++){
  gre->SetPoint(ibin,nPart[ibin],hRAA3->GetBinContent(9-ibin));
  gre->SetPointError(ibin,0,hRAA3->GetBinError(9-ibin));}
  jumSun(0,1,420,1);

  
  TPad *padl = new TPad("padl","padl", 0, 0., 0.9, 1);
  TPad *padr = new TPad("padr","padr", 0.9, 0., 1, 1);
//  padl->SetBottomMargin(0);
//  padr->SetBottomMargin(0);
  
  padl->Draw();
  padl->cd();
  TH1D *htemp = new TH1D("htemp",";N_{Part};RAA",420,0,420);
  TH1D *htempFull = new TH1D("htempfull","",1,0,2);
  handsomeTG1(gre,1);
  htemp->SetAxisRange(0,1.6,"Y");
  htemp->SetYTitle("RAA");
  htemp->DrawCopy();
  gre->Draw("P same");

  drawText("|y| < 2.4",0.3,0.80,2,20);
  drawText("p_{T}^{#mu} > 4 GeV", 0.3,0.72,2,18);
  
  padr->SetFrameBorderMode(0);
  padr->SetBorderMode(0);
  padr->SetBorderSize(0);
  padr->SetTicks(0,0);
  padr->Draw();
  padr->cd();
  handsomeTG1(gre_int,1);
  htempFull->SetAxisRange(0,2.0,"Y");
  htempFull->GetXaxis()->SetLabelOffset(999);
  htempFull->GetXaxis()->SetLabelSize(0);
  htempFull->GetYaxis()->SetTickLength(0.);
  htempFull->GetXaxis()->SetTickLength(0.);
  htempFull->Draw();
  gre_int->GetHistogram()->GetXaxis()->SetLabelOffset(999);
  gre_int->GetHistogram()->GetXaxis()->SetLabelSize(0);
  gre_int->GetHistogram()->GetYaxis()->SetLimits(0,1.6);
  gre_int->GetHistogram()->GetYaxis()->SetRangeUser(0,1.6);
  gre_int->GetHistogram()->GetXaxis()->SetLimits(0,2);
  gre_int->GetHistogram()->GetXaxis()->SetRangeUser(0,2);
  gre_int->SetMarkerColor(1);
  gre_int->SetMarkerSize(1);
  gre_int->SetMarkerStyle(10);
  gre_int->Draw("P same");


  wf->cd();
  gre->Write();
  gre_int->Write();
  hRAA[1]->Write();
  hRAA[2]->Write();

  
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
