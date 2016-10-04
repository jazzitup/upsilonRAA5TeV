#include "commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TStyle.h"
#include "TFile.h"
#include "TColor.h"
#include "cutsAndBin.h"
#include "multiTreeUtil.h"
using namespace std;

void drawSpectra()
{
  TH1::SetDefaultSumw2();
  
  gStyle->SetEndErrorSize(0);
  gStyle->SetOptStat(0);
  
  TFile* f1 = new TFile("Ups_1_RAA.root","READ");
  TFile* f2 = new TFile("Ups_2_RAA.root","READ");

  TH1D* hRAA_pt1[2];
  TH1D* hRAA_pt2[2];
  hRAA_pt1[0] = (TH1D*) f1 -> Get("hRAA_iy1");
  hRAA_pt1[1] = (TH1D*) f1 -> Get("hRAA_iy2");
  hRAA_pt2[0] = (TH1D*) f2 -> Get("hRAA_iy1");
  hRAA_pt2[1] = (TH1D*) f2 -> Get("hRAA_iy2");

  TGraphErrors *gre1;
  TGraphErrors *gre2;
  TGraphErrors *gre1_int;
  TGraphErrors *gre2_int;

  gre1 = (TGraphErrors*) f1->Get("Graph0");
  gre2 = (TGraphErrors*) f2->Get("Graph0");
  gre1_int = (TGraphErrors*) f1->Get("gre_int");
  gre2_int = (TGraphErrors*) f2->Get("gre_int");



  TCanvas* cRAA1 =  new TCanvas("cRAA1","",800,400);
  cRAA1->Divide(2,1);
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    cRAA1->cd(iy);
//    hRAA_pt1[iy-1]->SetMarkerStyle(20);
//    hRAA_pt2[iy-1]->SetMarkerStyle(20);
    cout << "asdas: " << endl;
    hRAA_pt1[iy-1]->Draw("P");
    hRAA_pt2[iy-1]->Draw("P same");
    hRAA_pt1[iy-1]->SetAxisRange(0,1.4,"Y");
    hRAA_pt1[iy-1]->SetLineColor(1);
    hRAA_pt1[iy-1]->SetMarkerColor(1);
    hRAA_pt2[iy-1]->SetLineColor(2);
    hRAA_pt2[iy-1]->SetMarkerColor(2);
    jumSun(0,1,30,1);
    cout << "asdas: " << endl;
  }

  TCanvas* cRAA =  new TCanvas("cRAA","",800,400);
    cout << "asdas: " << endl;
  cRAA->cd();
  TPad *padl = new TPad("padl","padl", 0, 0., 0.9, 1);
  TPad *padr = new TPad("padr","padr", 0.9, 0., 1, 1);
//  padl->SetBottomMargin(0);
//  padr->SetBottomMargin(0);
  
  padl->Draw();
  padl->cd();
  TH1D *htemp = new TH1D("htemp",";N_{Part};RAA",420,0,420);
  TH1D *htempFull = new TH1D("htempfull","",1,0,2);
  handsomeTG1(gre1,1);
  handsomeTG1(gre2,2);
  htemp->SetAxisRange(0,1.6,"Y");
  htemp->SetYTitle("RAA");
  htemp->DrawCopy();
  gre1->Draw("P same");
  gre2->Draw("P same");

  drawText("|y| < 2.4",0.3,0.80,2,20);
  drawText("p_{T}^{#mu} > 4 GeV", 0.3,0.72,2,18);
  
  padr->SetFrameBorderMode(0);
  padr->SetBorderMode(0);
  padr->SetBorderSize(0);
  padr->SetTicks(0,0);
  padr->Draw();
  padr->cd();
  handsomeTG1(gre1_int,1);
  handsomeTG1(gre2_int,2);
  htempFull->SetAxisRange(0,1.6,"Y");
  htempFull->GetXaxis()->SetLabelOffset(999);
  htempFull->GetXaxis()->SetLabelSize(0);
  htempFull->GetYaxis()->SetTickLength(0.);
  htempFull->GetXaxis()->SetTickLength(0.);
  htempFull->Draw();
  gre1_int->Draw("P same");
  gre2_int->Draw("P same");
}

