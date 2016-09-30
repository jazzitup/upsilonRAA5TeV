#include "commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"
#include "cutsAndBin.h"
using namespace std;

int kNoWeight=0;
int kPP = 1;
int kAA = 2;

int k1S = 1; 
int k2S = 2; 
int k3S = 3; 

int kNoVar = 0;
int kPtPlus = 1;
int kPtMinus = 2;
int kYPlus = 3;
int kYMinus = 4;
//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 

float getAcceptanceSingleBin(int state=k1S, int icoll=kNoWeight, TString kineCut="", int varianceID=0);
void getAcceptance(int bin = 1) {

  TH1::SetDefaultSumw2();
  //// modify by hand according to the pt range of the sample
  int nPtBins;  double* ptBin;  int nYBins;  double *yBin;
  const int nPtBins1 = 1;   double ptBin1[nPtBins1+1] = {0,30};  const int nYBins1 = 1;   double yBin1[nYBins1+1] = {0,2.4};
  const int nPtBins2 = 3;   double ptBin2[nPtBins2+1] = {0,5,12,30};  const int nYBins2 = 1;   double yBin2[nYBins2+1] = {0,2.4};
  const int nPtBins3 = 1;   double ptBin3[nPtBins3+1] = {0,30};  const int nYBins3 = 2;   double yBin3[nYBins3+1] = {0, 1.2, 2.4};
  
  if ( bin==1 ) {
    nPtBins = nPtBins1;  ptBin=ptBin1;     nYBins = nYBins1; yBin=yBin1;
  }
  else if ( bin==2 ) {
    nPtBins = nPtBins2;  ptBin=ptBin2;     nYBins = nYBins2; yBin=yBin2;
  }
  else if ( bin==3 ) {
    nPtBins = nPtBins3;  ptBin=ptBin3;     nYBins = nYBins3; yBin=yBin3;
  }

  for ( int ipt = 1 ; ipt<=nPtBins ; ipt++ ) { 
    for ( int iy =1 ; iy<=nYBins ; iy++) {
      TString kRange = Form("pt>%f && pt<%f && abs(y)>%f && abs(y)<%f",(float)ptBin[ipt-1],(float)ptBin[ipt], (float)yBin[iy-1], (float)yBin[iy] ) ;
      cout << "*===*===*===*===*  " << kRange << "  *===*===*===*===*" << endl;
      float y1s_noRwt = getAcceptanceSingleBin( 1, kNoWeight, kRange,kNoVar);
      float y1s_ppRwt = getAcceptanceSingleBin( 1, kPP, kRange,kNoVar);
      float y1s_ppRwt_ptPlus  = getAcceptanceSingleBin( 1, kPP, kRange, kPtPlus);
      float y1s_ppRwt_ptMinus = getAcceptanceSingleBin( 1, kPP, kRange, kPtMinus);
      float y1s_ppRwt_yPlus  = getAcceptanceSingleBin( 1, kPP, kRange, kYPlus);
      float y1s_ppRwt_yMinus = getAcceptanceSingleBin( 1, kPP, kRange, kYMinus);

      float y2s_noRwt = getAcceptanceSingleBin( 2, kNoWeight, kRange,kNoVar);
      float y2s_ppRwt = getAcceptanceSingleBin( 2, kPP, kRange,kNoVar);
      float y2s_ppRwt_ptPlus  = getAcceptanceSingleBin( 2, kPP, kRange, kPtPlus);
      float y2s_ppRwt_ptMinus = getAcceptanceSingleBin( 2, kPP, kRange, kPtMinus);
      float y2s_ppRwt_yPlus  = getAcceptanceSingleBin( 2, kPP, kRange, kYPlus);
      float y2s_ppRwt_yMinus = getAcceptanceSingleBin( 2, kPP, kRange, kYMinus);

      float err1s_ppPt = max ( abs(y1s_ppRwt_ptPlus/y1s_ppRwt-1), abs(y1s_ppRwt_ptMinus/y1s_ppRwt-1) ) ;
      float err2s_ppPt = max ( abs(y2s_ppRwt_ptPlus/y2s_ppRwt-1), abs(y2s_ppRwt_ptMinus/y2s_ppRwt-1) ) ;
      float err1s_ppY = max ( abs(y1s_ppRwt_yPlus/y1s_ppRwt-1), abs(y1s_ppRwt_yMinus/y1s_ppRwt-1) ) ;
      float err2s_ppY = max ( abs(y2s_ppRwt_yPlus/y2s_ppRwt-1), abs(y2s_ppRwt_yMinus/y2s_ppRwt-1) ) ;

      float y1s_aaRwt = getAcceptanceSingleBin( 1, kAA, kRange,kNoVar);
      float y1s_aaRwt_ptPlus  = getAcceptanceSingleBin( 1, kAA, kRange, kPtPlus);
      float y1s_aaRwt_ptMinus = getAcceptanceSingleBin( 1, kAA, kRange, kPtMinus);
      float y1s_aaRwt_yPlus  = getAcceptanceSingleBin( 1, kAA, kRange, kYPlus);
      float y1s_aaRwt_yMinus = getAcceptanceSingleBin( 1, kAA, kRange, kYMinus);

      float y2s_aaRwt = getAcceptanceSingleBin( 2, kAA, kRange,kNoVar);
      float y2s_aaRwt_ptPlus  = getAcceptanceSingleBin( 2, kAA, kRange, kPtPlus);
      float y2s_aaRwt_ptMinus = getAcceptanceSingleBin( 2, kAA, kRange, kPtMinus);
      float y2s_aaRwt_yPlus  = getAcceptanceSingleBin( 2, kAA, kRange, kYPlus);
      float y2s_aaRwt_yMinus = getAcceptanceSingleBin( 2, kAA, kRange, kYMinus);

      float err1s_aaPt = max ( abs(y1s_aaRwt_ptPlus/y1s_aaRwt-1), abs(y1s_aaRwt_ptMinus/y1s_aaRwt-1) ) ;
      float err2s_aaPt = max ( abs(y2s_aaRwt_ptPlus/y2s_aaRwt-1), abs(y2s_aaRwt_ptMinus/y2s_aaRwt-1) ) ;
      float err1s_aaY = max ( abs(y1s_aaRwt_yPlus/y1s_aaRwt-1), abs(y1s_aaRwt_yMinus/y1s_aaRwt-1) ) ;
      float err2s_aaY = max ( abs(y2s_aaRwt_yPlus/y2s_aaRwt-1), abs(y2s_aaRwt_yMinus/y2s_aaRwt-1) ) ;
      
      cout << "Un-weighed acceptance : (1S) = " << y1s_noRwt << ",   (2S) = " << y2s_noRwt << endl;
      cout << "Re-weighed Acceptance : " << "pp(1S) = " << y1s_ppRwt << ",  PbPb(1S) = " << y1s_aaRwt ;
      cout << " pp(2S) = " << y2s_ppRwt << ",  PbPb(2S) = " << y2s_aaRwt ;
      cout << ",     (2S/1S,AA/pp) acc. ratio = " <<  (y2s_aaRwt/y2s_ppRwt) /(y1s_aaRwt/y1s_ppRwt)  << endl;
      
      cout << int(1000*y1s_noRwt)*0.001 << " & " << int(1000*y1s_ppRwt)*0.001<< " & " << int(1000*y1s_aaRwt)*0.001<< " & " ;
      cout << int(1000*y2s_noRwt)*0.001 << " & " << int(1000*y2s_ppRwt)*0.001<< " & " << int(1000*y2s_aaRwt)*0.001 << " & ";
      cout << int(1000* (y2s_aaRwt/y2s_ppRwt) / (y1s_aaRwt/y1s_ppRwt) )*0.001 << endl; // Final correction
      cout << int(1000*err1s_ppPt)*0.1 << "\% & " << int(1000*err1s_aaPt)*0.1 << "\% & " ;
      cout << int(1000*err2s_ppPt)*0.1 << "\% & " << int(1000*err2s_aaPt)*0.1 << "\% & " ;
      cout << int(1000*err1s_ppY)*0.1 << "\% & " << int(1000*err1s_aaY)*0.1 << "\% & " ;
      cout << int(1000*err2s_ppY)*0.1 << "\% & " << int(1000*err2s_aaY)*0.1 << "\% & " ;
      cout << int(1000*sqrt( err1s_ppPt*err1s_ppPt +  err2s_ppPt* err2s_ppPt + err1s_ppY*err1s_ppY + err2s_ppY*err2s_ppY + err1s_aaPt*err1s_aaPt +  err2s_aaPt* err2s_aaPt + err1s_aaY*err1s_aaY + err2s_aaY*err2s_aaY ) ) *0.1 << "\%" << endl;
    }
  }
}

float getAcceptanceSingleBin(int state, int icoll, TString kineCut, int varianceID) {
  
  TH1::SetDefaultSumw2();
  
  float muPtCut = 4; // for acceptance 
  float muEtaCut = 2.4;
  
  TH1D* hGen; // in rapidity bins, centrality bins
  TH1D* hGenAcc; // in rapidity bins, centrality bins
  TH1D* hAcc; // Acceptance rate : in rapidity bins, centrality bins 
  
  TFile* f;
  if ( state == k1S) 
    f = new TFile("skimmedFiles/yskimGenOnly_Ups1s_20163291723_ce55c767c54219323f3792d6721775226aba4c74.root");
  else if ( state == k2S) 
    f = new TFile("skimmedFiles/yskimGenOnly_Ups2s_20163291725_ce55c767c54219323f3792d6721775226aba4c74.root");
  TTree* mmGen = (TTree*)f->Get("mmGen");
  TString accCut = "pt1>4 && pt2>4 && abs(eta1)<2.4 && abs(eta2)<2.4";
  
  TString ptWeight;
  if ( icoll == kNoWeight ) ptWeight = "1";
  else if ( icoll == kPP ) { 
    if (state == k1S)  ptWeight = "1.09 - 0.022*pt";
    if (state == k2S)  ptWeight = "0.69 + 0.073*pt";
  }    
  else if ( icoll == kAA ) { 
    if (state == k1S)  ptWeight = "1.08 - 0.015*pt";
    if (state == k2S)  ptWeight = "0.68 + 0.1*pt";
  }    

  if ( varianceID == kPtPlus ) 
    ptWeight = "("+ptWeight+")* (0.8 + 0.0133*pt)" ;
  else if ( varianceID == kPtMinus ) 
    ptWeight = "("+ptWeight+")* (1.2 - 0.0133*pt)" ;
  else if ( varianceID == kYPlus ) 
    ptWeight = "("+ptWeight+")* (0.8 + 0.167*abs(y))" ;
  else if ( varianceID == kYMinus ) 
    ptWeight = "("+ptWeight+")* (1.2 - 0.167*abs(y))" ;
  //  cout << " ptWeight = " << ptWeight << endl;
  
  hGen = new TH1D(Form("hGen_state%d_icoll%d",state,icoll),";Rapidity;",1,-2.4,2.4);
  hGenAcc = (TH1D*)hGen->Clone(Form("hGenAcc_state%d_icoll%d",state,icoll));
  //// all GEN
  mmGen->Draw(Form("y>>%s",hGen->GetName()), Form("(%s)*(%s)", kineCut.Data(), ptWeight.Data()));
  //// GEN with sglMuAccCut 
  mmGen->Draw(Form("y>>%s",hGenAcc->GetName()), Form("((%s)&&(%s))*(%s)", kineCut.Data(), accCut.Data(), ptWeight.Data()));
  handsomeTH1(hGenAcc,1);
  //// --- Acceptance rate : 
  hAcc = (TH1D*)hGenAcc->Clone(Form("hAcc_state%d_icoll%d",state,icoll));
  hAcc->Divide(hGen);
  
  /*
  TCanvas* c1 = new TCanvas("c1","",400,400);
  hGen->Draw("hist");
  hGenAcc->Draw("same e");
  
  TCanvas* c2 = new TCanvas("c2","",400,400);
  hAcc->SetAxisRange(0,1,"Y");
  hAcc->Draw();
  */  
  return hAcc->GetBinContent(1);
}


