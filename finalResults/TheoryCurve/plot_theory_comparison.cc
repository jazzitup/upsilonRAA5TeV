#include <TTree.h>
#include <TFile.h>
#include <TPad.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TF1.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TChain.h>
#include <fstream>
#include <iostream>
using namespace std;

void plot_theory_comparison()
{
  gStyle->SetPalette(1);
  gStyle->SetOptFit(kTRUE);
  gStyle->SetOptStat(0);
  gStyle->SetTextSize(0.01908148);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetTitleXSize(0.04);
  gStyle->SetTitleXOffset(1.3);
  gStyle->SetTitleYSize(0.04);
  gStyle->SetTitleYOffset(2.2);
  gStyle->SetPadBottomMargin(0.18);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetEndErrorSize(0);

  Double_t nPart, pT, rap;
  Double_t RAA_etas_nPart1S[3];
  Double_t RAA_etas_nPart2S[3];
  Double_t RAA_etas_nPart3S[3];
  Double_t RAA_etas_pT1S[3];
  Double_t RAA_etas_pT2S[3];
  Double_t RAA_etas_rap1S[3];
  Double_t RAA_etas_rap2S[3];

  int sNN = 5023;
  //int sNN = 5023;
  TFile *ofile_nPart1S = new TFile(Form("1SXi0_RAA_%d_nPart.root",sNN),"READ");
  TFile *ofile_nPart2S = new TFile(Form("2SXi0_RAA_%d_nPart.root",sNN),"READ");
  TFile *ofile_nPart3S = new TFile(Form("3SXi0_RAA_%d_nPart.root",sNN),"READ");
  TFile *ofile_pT1S = new TFile(Form("1SXi0_RAA_%d_pT.root",sNN),"READ");
  TFile *ofile_pT2S = new TFile(Form("2SXi0_RAA_%d_pT.root",sNN),"READ");
  TFile *ofile_rap1S = new TFile(Form("1SXi0_RAA_%d_rap.root",sNN),"READ");
  TFile *ofile_rap2S = new TFile(Form("2SXi0_RAA_%d_rap.root",sNN),"READ");

  TFile *writeFile = new TFile(Form("StrickLand_RAA_%d.root",sNN),"recreate");

  TTree *tree_nPart1S = (TTree*) ofile_nPart1S -> Get("tree");
  tree_nPart1S->SetBranchAddress("nPart",&nPart);
  tree_nPart1S->SetBranchAddress("RAA_etas_nPart",RAA_etas_nPart1S);
  TTree *tree_nPart2S = (TTree*) ofile_nPart2S -> Get("tree");
  tree_nPart2S->SetBranchAddress("nPart",&nPart);
  tree_nPart2S->SetBranchAddress("RAA_etas_nPart",RAA_etas_nPart2S);
  TTree *tree_nPart3S = (TTree*) ofile_nPart3S -> Get("tree");
  tree_nPart3S->SetBranchAddress("nPart",&nPart);
  tree_nPart3S->SetBranchAddress("RAA_etas_nPart",RAA_etas_nPart3S);
  
  TTree *tree_pT1S = (TTree*) ofile_pT1S -> Get("tree");
  tree_pT1S->SetBranchAddress("pT",&pT);
  tree_pT1S->SetBranchAddress("RAA_etas_pT",RAA_etas_pT1S);
  TTree *tree_pT2S = (TTree*) ofile_pT2S -> Get("tree");
  tree_pT2S->SetBranchAddress("pT",&pT);
  tree_pT2S->SetBranchAddress("RAA_etas_pT",RAA_etas_pT2S);

  TTree *tree_rap1S = (TTree*) ofile_rap1S -> Get("tree");
  tree_rap1S->SetBranchAddress("rap",&rap);
  tree_rap1S->SetBranchAddress("RAA_etas_rap",RAA_etas_rap1S);
  TTree *tree_rap2S = (TTree*) ofile_rap2S -> Get("tree");
  tree_rap2S->SetBranchAddress("rap",&rap);
  tree_rap2S->SetBranchAddress("RAA_etas_rap",RAA_etas_rap2S);

  TGraphErrors *g_nPart_1S[3] ;
  TGraphErrors *g_nPart_2S[3] ;
  TGraphErrors *g_nPart_3S[3] ;
  TGraphErrors *g_pt_1S[3] ;
  TGraphErrors *g_pt_2S[3] ;
  TGraphErrors *g_rap_1S[3] ;
  TGraphErrors *g_rap_2S[3] ;
  for(int i=0;i<3;i++)
  {
    g_nPart_1S[i] = new TGraphErrors();
    g_nPart_2S[i] = new TGraphErrors();
    g_nPart_3S[i] = new TGraphErrors();
    g_pt_1S[i] = new TGraphErrors();
    g_pt_2S[i] = new TGraphErrors();
    g_rap_1S[i] = new TGraphErrors();
    g_rap_2S[i] = new TGraphErrors();
  }

  int nEntries_1s = tree_nPart1S->GetEntries();
  for(int i=0; i<nEntries_1s; i++)
  {
    tree_nPart1S->GetEntry(i);
    g_nPart_1S[0]->SetPoint(i,nPart,RAA_etas_nPart1S[0]);
    g_nPart_1S[0]->SetPointError(i,0,0);
    g_nPart_1S[1]->SetPoint(i,nPart,RAA_etas_nPart1S[1]);
    g_nPart_1S[1]->SetPointError(i,0,0);
    g_nPart_1S[2]->SetPoint(i,nPart,RAA_etas_nPart1S[2]);
    g_nPart_1S[2]->SetPointError(i,0,0);
  }

  int nEntries_2s = tree_nPart2S->GetEntries();
  for(int i=0; i<nEntries_2s; i++)
  {
    tree_nPart2S->GetEntry(i);
    g_nPart_2S[0]->SetPoint(i,nPart,RAA_etas_nPart2S[0]);
    g_nPart_2S[0]->SetPointError(i,0,0);
    g_nPart_2S[1]->SetPoint(i,nPart,RAA_etas_nPart2S[1]);
    g_nPart_2S[1]->SetPointError(i,0,0);
    g_nPart_2S[2]->SetPoint(i,nPart,RAA_etas_nPart2S[2]);
    g_nPart_2S[2]->SetPointError(i,0,0);
  }

  int nEntries_3s = tree_nPart3S->GetEntries();
  for(int i=0; i<nEntries_3s; i++)
  {
    tree_nPart3S->GetEntry(i);
    g_nPart_3S[0]->SetPoint(i,nPart,RAA_etas_nPart3S[0]);
    g_nPart_3S[0]->SetPointError(i,0,0);
    g_nPart_3S[1]->SetPoint(i,nPart,RAA_etas_nPart3S[1]);
    g_nPart_3S[1]->SetPointError(i,0,0);
    g_nPart_3S[2]->SetPoint(i,nPart,RAA_etas_nPart3S[2]);
    g_nPart_3S[2]->SetPointError(i,0,0);

    cout << "npart : " << nPart << endl;
    cout << "RAA 3S[0] : " << RAA_etas_nPart3S[0] << endl;
  }

  nEntries_1s = 0;
  nEntries_1s = tree_rap1S->GetEntries();
  nEntries_2s = 0;
  nEntries_2s = tree_rap2S->GetEntries();
  for(int i=0; i<nEntries_1s; i++)
  {
    tree_rap1S->GetEntry(i);
    g_rap_1S[0]->SetPoint(i,rap,RAA_etas_rap1S[0]);
    g_rap_1S[0]->SetPointError(i,0,0);
    g_rap_1S[1]->SetPoint(i,rap,RAA_etas_rap1S[1]);
    g_rap_1S[1]->SetPointError(i,0,0);
    g_rap_1S[2]->SetPoint(i,rap,RAA_etas_rap1S[2]);
    g_rap_1S[2]->SetPointError(i,0,0);
  }
  for(int i=0; i<nEntries_2s; i++)
  {
    tree_rap2S->GetEntry(i);
    g_rap_2S[0]->SetPoint(i,rap,RAA_etas_rap2S[0]);
    g_rap_2S[0]->SetPointError(i,0,0);
    g_rap_2S[1]->SetPoint(i,rap,RAA_etas_rap2S[1]);
    g_rap_2S[1]->SetPointError(i,0,0);
    g_rap_2S[2]->SetPoint(i,rap,RAA_etas_rap2S[2]);
    g_rap_2S[2]->SetPointError(i,0,0);
  }

  nEntries_1s = 0;
  nEntries_1s = tree_pT1S->GetEntries();
  nEntries_2s = 0;
  nEntries_2s = tree_pT2S->GetEntries();

  double pTBin1s_[6] = {0,2.5,5,8,12,20};
  double pTBin2s_[4] = {0,5,12,20};
  double fpt, fpt0, ipt0; 
  double pT_raa_val_1S_1[5];
  double pT_raa_val_1S_2[5];
  double pT_raa_val_1S_3[5];
  double pT_raa_val_2S_1[3];
  double pT_raa_val_2S_2[3];
  double pT_raa_val_2S_3[3];
  int fnumpt;
  double pT_raa_val_1S_1_;
  double pT_raa_val_1S_2_;
  double pT_raa_val_1S_3_;
  double pT_raa_val_2S_1_;
  double pT_raa_val_2S_2_;
  double pT_raa_val_2S_3_;
  tree_pT1S->GetEntry(0);
  pT_raa_val_1S_1[0] = RAA_etas_pT1S[0];
  pT_raa_val_1S_2[0] = RAA_etas_pT1S[1];
  pT_raa_val_1S_3[0] = RAA_etas_pT1S[2];
  tree_pT1S->GetEntry(1);
  pT_raa_val_1S_1[1] = RAA_etas_pT1S[0];
  pT_raa_val_1S_2[1] = RAA_etas_pT1S[1];
  pT_raa_val_1S_3[1] = RAA_etas_pT1S[2];
  tree_pT1S->GetEntry(2);
  pT_raa_val_1S_1[2] = RAA_etas_pT1S[0];
  pT_raa_val_1S_2[2] = RAA_etas_pT1S[1];
  pT_raa_val_1S_3[2] = RAA_etas_pT1S[2];
  tree_pT1S->GetEntry(3);
  pT_raa_val_1S_1[3] = RAA_etas_pT1S[0];
  pT_raa_val_1S_2[3] = RAA_etas_pT1S[1];
  pT_raa_val_1S_3[3] = RAA_etas_pT1S[2];
  tree_pT1S->GetEntry(4);
  pT_raa_val_1S_1[4] = RAA_etas_pT1S[0];
  pT_raa_val_1S_2[4] = RAA_etas_pT1S[1];
  pT_raa_val_1S_3[4] = RAA_etas_pT1S[2];

  tree_pT2S->GetEntry(0);
  pT_raa_val_2S_1[0] = RAA_etas_pT2S[0];
  pT_raa_val_2S_2[0] = RAA_etas_pT2S[1];
  pT_raa_val_2S_3[0] = RAA_etas_pT2S[2];
  tree_pT2S->GetEntry(1);
  pT_raa_val_2S_1[1] = RAA_etas_pT2S[0];
  pT_raa_val_2S_2[1] = RAA_etas_pT2S[1];
  pT_raa_val_2S_3[1] = RAA_etas_pT2S[2];
  tree_pT2S->GetEntry(2);
  pT_raa_val_2S_1[2] = RAA_etas_pT2S[0];
  pT_raa_val_2S_2[2] = RAA_etas_pT2S[1];
  pT_raa_val_2S_3[2] = RAA_etas_pT2S[2];

  for(int i=0; i<12000; i++)
  {
    if(i>=0 && i<1500) {fpt = pTBin1s_[1]-pTBin1s_[0]; ipt0 = 0; fnumpt=1500; fpt0 = pTBin1s_[0]; pT_raa_val_1S_1_ = pT_raa_val_1S_1[0]; pT_raa_val_1S_2_ = pT_raa_val_1S_2[0]; pT_raa_val_1S_3_=pT_raa_val_1S_3[0];}
    else if(i>=1500 && i<3000) {fpt = pTBin1s_[2]-pTBin1s_[1]; ipt0 = 1500; fnumpt=1500; fpt0 = pTBin1s_[1]; pT_raa_val_1S_1_ = pT_raa_val_1S_1[1]; pT_raa_val_1S_2_ = pT_raa_val_1S_2[1]; pT_raa_val_1S_3_=pT_raa_val_1S_3[1];}
    else if(i>=3000 && i<4800) {fpt = pTBin1s_[3]-pTBin1s_[2]; ipt0 = 3000; fnumpt=1800; fpt0 = pTBin1s_[2]; pT_raa_val_1S_1_ = pT_raa_val_1S_1[2]; pT_raa_val_1S_2_ = pT_raa_val_1S_2[2]; pT_raa_val_1S_3_=pT_raa_val_1S_3[2];}
    else if(i>=4800 && i<2400) {fpt = pTBin1s_[4]-pTBin1s_[3]; ipt0 = 4800; fnumpt=2400; fpt0 = pTBin1s_[3]; pT_raa_val_1S_1_ = pT_raa_val_1S_1[3]; pT_raa_val_1S_2_ = pT_raa_val_1S_2[3]; pT_raa_val_1S_3_=pT_raa_val_1S_3[3];}
    else if(i>=7200 && i<12000) {fpt = pTBin1s_[5]-pTBin1s_[4]; ipt0 = 7200; fnumpt=4800; fpt0 = pTBin1s_[4]; pT_raa_val_1S_1_ = pT_raa_val_1S_1[4]; pT_raa_val_1S_2_ = pT_raa_val_1S_2[4]; pT_raa_val_1S_3_=pT_raa_val_1S_3[4];}


    g_pt_1S[0]->SetPoint(i,fpt0 + (fpt/fnumpt)*(i-ipt0),pT_raa_val_1S_1_);
    g_pt_1S[0]->SetPointError(i,0,0);
    g_pt_1S[1]->SetPoint(i,fpt0+(fpt/fnumpt)*(i-ipt0),pT_raa_val_1S_2_);
    g_pt_1S[1]->SetPointError(i,0,0);
    g_pt_1S[2]->SetPoint(i,fpt0+(fpt/fnumpt)*(i-ipt0),pT_raa_val_1S_3_);
    g_pt_1S[2]->SetPointError(i,0,0);
  }

  for(int i=0; i<12000; i++)
  {
    if(i>=0 && i<3000) {fpt = pTBin2s_[1]-pTBin2s_[0]; fnumpt=3000; ipt0 = 0; fpt0 = pTBin2s_[0]; pT_raa_val_2S_1_ = pT_raa_val_2S_1[0]; pT_raa_val_2S_2_ = pT_raa_val_2S_2[0]; pT_raa_val_2S_3_=pT_raa_val_2S_3[0];}
    else if(i>=3000 && i<7200) {fpt = pTBin2s_[2]-pTBin2s_[1]; fnumpt=4200; ipt0 = 3000; fpt0 = pTBin2s_[1]; pT_raa_val_2S_1_ = pT_raa_val_2S_1[1]; pT_raa_val_2S_2_ = pT_raa_val_2S_2[1]; pT_raa_val_2S_3_=pT_raa_val_2S_3[1];}
    else if(i>=7200 && i<12000) {fpt = pTBin2s_[3]-pTBin2s_[2]; fnumpt=4800; ipt0 = 7200; fpt0 = pTBin2s_[2]; pT_raa_val_2S_1_ = pT_raa_val_2S_1[2]; pT_raa_val_2S_2_ = pT_raa_val_2S_2[2]; pT_raa_val_2S_3_=pT_raa_val_2S_3[2];}

    g_pt_2S[0]->SetPoint(i,fpt0 + (fpt/fnumpt)*(i-ipt0),pT_raa_val_2S_1_);
    g_pt_2S[0]->SetPointError(i,0,0);
    g_pt_2S[1]->SetPoint(i,fpt0+(fpt/fnumpt)*(i-ipt0),pT_raa_val_2S_2_);
    g_pt_2S[1]->SetPointError(i,0,0);
    g_pt_2S[2]->SetPoint(i,fpt0+(fpt/fnumpt)*(i-ipt0),pT_raa_val_2S_3_);
    g_pt_2S[2]->SetPointError(i,0,0);
  }

  writeFile->cd();
  for(int i=0;i<3;i++){
  g_nPart_1S[i]->SetName(Form("RAA_strick_nPart_1S_%d",i));
  g_nPart_2S[i]->SetName(Form("RAA_strick_nPart_2S_%d",i));
  g_nPart_3S[i]->SetName(Form("RAA_strick_nPart_3S_%d",i));
  g_rap_1S[i]->SetName(Form("RAA_strick_rap_1S_%d",i));
  g_rap_2S[i]->SetName(Form("RAA_strick_rap_2S_%d",i));
  g_pt_1S[i]->SetName(Form("RAA_strick_pt_1S_%d",i));
  g_pt_2S[i]->SetName(Form("RAA_strick_pt_2S_%d",i));

  g_nPart_1S[i]->Write();
  g_nPart_2S[i]->Write();
  g_nPart_3S[i]->Write();
  g_rap_1S[i]->Write();
  g_rap_2S[i]->Write();
  g_pt_1S[i]->Write();
  g_pt_2S[i]->Write();
  }
} 

