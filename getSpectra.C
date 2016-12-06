#include "commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TStyle.h"
#include "TFile.h"
#include "TColor.h"
#include "cutsAndBin.h"
#include "multiTreeUtil.h"
using namespace std;

TString ResultDir  = "nominalFits";


//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 
valErr getYield(int state=0, int collId=0, float ptLow=0, float ptHigh=0, float yLow=0, float yHigh=0, int cLow=0, int cHigh=0, 	float dphiEp2Low=0,  float dphiEp2High=0) ;


void getSpectra(int state = 1, bool doAccCorr=false ) {
  

  TH1::SetDefaultSumw2();
  //// modify by hand according to the pt range of the sample

  gStyle->SetEndErrorSize(0);
  gStyle->SetOptStat(0);
  int nPtBins=0;
  int nYBins=0;
  double* ptBin;
  double* yBin;
  int nCentBins=0;
  double* centBin;
  double* nPart;  // In order from peripheral to central 
  double* nColl;  // In order from central to peripheral 
  //  double nColl1s[nCentBins] = {1819,1432,1005,606,349,186,90.7,40.1,7.67};
  //  double nPart1s[nCentBins] = {15.47,30.59,53.85,86.95,131.4,189.2,264.3,333.4,384.4};



  if ( state == 1 ) { 
    nPtBins = nPtBins1s;    ptBin = ptBin1s;
    nYBins = nYBins1S;    yBin = yBin1S; 
    nCentBins = nCentBins1s;  centBin = centBin1s; nPart = nPart1s; nColl = nColl1s;
  }
  else if ( state == 2 ) { 
    nPtBins = nPtBins2s;    ptBin = ptBin2s;
    nYBins = nYBins2S;    yBin = yBin2S; 
    nCentBins = nCentBins2s;  centBin = centBin2s; nPart = nPart2s; nColl = nColl2s;
  }
  else if ( state == 3 ) { 
    nPtBins = nPtBins3s;    ptBin = ptBin3s;
    nYBins = nYBins3S;    yBin = yBin3S; 
    nCentBins = nCentBins3s;  centBin = centBin3s; nPart = nPart3s; nColl = nColl3s;
  }
  
  double ptMin = ptBin[0];    double ptMax = ptBin[nPtBins];  
  double yMin = yBin[0];    double yMax = yBin[nYBins];  
  double centMin = centBin[0];    double centMax = centBin[nCentBins];  
 
  
  
  TH1D* hrapEffAA;
  TH1D* hrapEffPP;
  TH1D* hrapSigAA;
  TH1D* hrapSigPP;

  TH1D* hptEffAA;
  TH1D* hptEffPP;
  TH1D* hptSigAA;
  TH1D* hptSigPP;

  TH1D* hcentEffAA;
  TH1D* hcentEffPP;
  TH1D* hcentSigAA;
  TH1D* hcentSigPP;  // There is only one bin for pp. 


  // ##################################
  // ~*~*~*~*~* Rapidity ~*~*~*~*~*~*~*
  // ##################################
  TFile* inf = new TFile(Form("efficiency/efficiency_ups%ds_MCDATA.root",state));
  hrapEffAA  = (TH1D*)inf->Get("hrapEffAA");
  hrapEffPP  = (TH1D*)inf->Get("hrapEffPP");
  
  TCanvas* c_rap_eff =  new TCanvas("c_rap_eff","",400,400);
  c_rap_eff->cd();
  cleverRange(hrapEffAA, 1.3, 0);
  handsomeTH1(hrapEffAA,2);
  handsomeTH1(hrapEffPP,2);
  hrapEffAA->Draw();
  hrapEffPP->SetMarkerStyle(24);
  hrapEffPP->Draw("same");
  
  // ############################
  // ~*~*~*~*~* Pt ~*~*~*~*~*~*~*
  // ############################
  hptEffAA  = (TH1D*)inf->Get("hptEffAA");
  hptEffPP  = (TH1D*)inf->Get("hptEffPP");
  
  TCanvas* c1 =  new TCanvas("c1","",400,400);
  c1->cd();
  cleverRange(hptEffAA, 1.3, 0);
  handsomeTH1(hptEffAA,2);
  handsomeTH1(hptEffPP,2);
  hptEffAA->Draw();
  hptEffPP->SetMarkerStyle(24);
  hptEffPP->Draw("same");
  
  
  // ############################
  // ~*~*~*~*~* Cent ~*~*~*~*~*~*
  // ############################
  hcentEffAA = (TH1D*) inf -> Get("hcentEffAA");
  hcentEffPP = (TH1D*) inf -> Get("hcentEffPP");

  hcentSigAA = (TH1D*) hcentEffAA -> Clone("hcentSigAA_cent");
  hcentSigPP = (TH1D*) hcentEffPP -> Clone("hcentSigPP");
  hcentSigAA -> Reset(); 
  hcentSigPP -> Reset(); 
  
  TH1D *hSetBin;
  hSetBin = (TH1D*) hcentSigAA ->Clone("hSetBin");
  TH1D *hcentEffAA_int = (TH1D*) inf -> Get("hcentEffAA_int");
  TH1D *hcentSigAA_int = (TH1D*) hcentEffAA_int -> Clone("hcentSigAA_int");
  hcentSigAA_int->Reset();



  // signals :
  TH1D* hRAA_rap;   // raw RAA w/o efficiency correction
  TH1D* hRAA_rap_effcor;   // raw RAA w/ efficiency correction
  TH1D* hptRAAeffUnCorr;   // raw RAA w/o efficiency correction
  TH1D* hptRAA;   // raw RAA w/o efficiency correction
  TH1D* hRAA_cent; 
  TH1D* hRAA3;   // final cent RAA w/ efficiency correction
  TH1D* hRAA;   // final RAA w/ efficiency correctdion

  //***Rapidity***
  hrapSigAA = (TH1D*)  hrapEffAA->Clone("hrapSigAA");
  hrapSigPP = (TH1D*)  hrapEffPP->Clone("hrapSigPP");
  hrapSigAA->Reset();
  hrapSigPP->Reset();
    for ( int iy = 1 ; iy<= nYBins ; iy++) {
      valErr yieldPP = getYield(state, kPPDATA, ptMin, ptMax, yBin[iy-1], yBin[iy], centMin, centMax, 0, 100);
      valErr yieldAA = getYield(state, kAADATA, ptMin, ptMax, yBin[iy-1], yBin[iy], centMin, centMax, 0, 100);
      hrapSigAA->SetBinContent( iy, yieldAA.val ) ;
      hrapSigAA->SetBinError( iy, yieldAA.err ) ;
      hrapSigPP->SetBinContent( iy, yieldPP.val ) ;
      hrapSigPP->SetBinError( iy, yieldPP.err ) ;
    }
    
  
  //*****RAA Rap ******
  TCanvas* cRAA_rap =  new TCanvas("cRAA_rap","",400,400);
  hRAA_rap = (TH1D*)hrapSigAA->Clone("hRAA_rap");
  hRAA_rap->Divide( hrapSigPP );
  hRAA_rap->Scale( 26000000. / 351 ) ;   // pp : 26pb-1,  PbPb : 351 microBarn-1
  hRAA_rap->Scale( 1./ (208.*208) );
  hRAA_rap->SetAxisRange(0,1.2,"Y");
  hRAA_rap->SetYTitle("R_{AA} (efficiency UNcorrected)");
  hRAA_rap->Draw();
  jumSun(0,1,30,1);
  
  TCanvas* cRAA_rap_effcor =  new TCanvas("cRAA_rap_effcor","",400,400);
  hRAA_rap_effcor = (TH1D*)hRAA_rap->Clone("hRAA_rap_effcor");

  TH1D* relativeEff_rap = (TH1D*)hrapEffAA->Clone("relEffAA_rap");
  relativeEff_rap->Divide(hrapEffPP);
  hRAA_rap_effcor->Divide( relativeEff_rap ) ;
  hRAA_rap_effcor->SetAxisRange(0,1.2,"Y");
  hRAA_rap_effcor->SetYTitle("R_{AA}");
  hRAA_rap_effcor->Draw();
  jumSun(0,1,30,1);

  
  cRAA_rap->SaveAs(Form("raa_vs_rap_%ds.pdf",state));

  //***Pt***
  TCanvas* c2 =  new TCanvas("c2","",400,400);
  hptSigAA = (TH1D*)  hptEffAA->Clone("hptSigAA");
  hptSigPP = (TH1D*)  hptEffPP->Clone("hptSigPP");
  hptSigAA->Reset();
  hptSigPP->Reset();  hptSigPP->SetYTitle("Raw yields");
    for ( int ipt = 1 ; ipt<= nPtBins ; ipt++) {
      valErr yieldPP = getYield(state, kPPDATA, ptBin[ipt-1], ptBin[ipt], yMin, yMax , centMin, centMax , 0, 100);
      valErr yieldAA = getYield(state, kAADATA, ptBin[ipt-1], ptBin[ipt], yMin, yMax , centMin, centMax , 0, 100);
      hptSigAA->SetBinContent( ipt, yieldAA.val ) ;
      hptSigAA->SetBinError( ipt, yieldAA.err ) ;
      hptSigPP->SetBinContent( ipt, yieldPP.val ) ;
      hptSigPP->SetBinError( ipt, yieldPP.err ) ;
    }
    
  //*****Pt Yield***** 
  hptSigPP->SetAxisRange(10,1e5,"Y");
  hptSigAA->SetAxisRange(10,1e5,"Y");
  //    cleverRange(hptSigPP[iy], 1.3, 1);
  handsomeTH1(hptSigPP,2);
  handsomeTH1(hptSigAA,2);
  hptSigPP->SetMarkerStyle(24);
  
  hptSigPP->Draw();
  gPad->SetLogy();
  hptSigAA->Draw("same");
  
  TCanvas* cptRAA1 =  new TCanvas("cRAA_ptUnCorr","",400,400);
  cptRAA1->cd();
  hptRAAeffUnCorr = (TH1D*)hptSigAA->Clone("hptRAAeffUnCorr");
  hptRAAeffUnCorr->Divide( hptSigPP );
  hptRAAeffUnCorr->Scale( 26000000. / 351 ) ;   // pp : 26pb-1,  PbPb : 351 microBarn-1
  hptRAAeffUnCorr->Scale( 1./ (208.*208) );
  hptRAAeffUnCorr->SetAxisRange(0,1.2,"Y");
  hptRAAeffUnCorr->SetYTitle("R_{AA} (efficiency UNcorrected)");
  hptRAAeffUnCorr->Draw();
  jumSun(0,1,30,1);
  
  TCanvas* cPtRAA =  new TCanvas("cRAA_pt","",400,400);
  hptRAA = (TH1D*)hptRAAeffUnCorr->Clone("raa_vs_pt");

  TH1D* relativeEff = (TH1D*)hptEffAA->Clone("relEffAA");
  relativeEff->Divide(hptEffPP);
  hptRAA->Divide( relativeEff ) ;
  hptRAA->SetAxisRange(0,1.2,"Y");
  hptRAA->SetYTitle("R_{AA}");
  hptRAA->Draw();
  jumSun(0,1,30,1);
  
  cPtRAA->SaveAs(Form("raa_vs_pt_%ds.pdf",state));
  
 

  //******RAA vs Centrality *****
  TCanvas* cRAACent =  new TCanvas("cRAACent","",400,400);
  for(int icent=1; icent<=nCentBins;icent++)
  {
    valErr yCentAA = getYield(state,kAADATA,ptMin,ptMax,yMin,yMax, (int) centBin[icent-1],(int) centBin[icent],0,100); 
    valErr yCentPP = getYield(state,kPPDATA,ptMin,ptMax,yMin,yMax, 0, 200, 0,100);
    hSetBin -> SetBinContent(icent,(double)((centBin[icent]-centBin[icent-1])*nColl[icent-1]));
    hcentSigAA -> SetBinContent(icent,yCentAA.val);
    hcentSigAA -> SetBinError(icent,yCentAA.err);
  }
  valErr yCentAA_int = getYield(state,kAADATA,0,30,0,2.4,0,200,0,100);
  valErr yCentPP = getYield(state,kPPDATA,0,30,0,2.4,0,200,0,100);
  hcentSigAA_int -> SetBinContent(1,yCentAA_int.val);
  hcentSigAA_int -> SetBinError(1,yCentAA_int.err);
  hcentSigPP -> SetBinContent(1,yCentPP.val);
  hcentSigPP -> SetBinError(1,yCentPP.err);

  //****RAA CENTRALITY 0-100%****
  TH1D *hRAA_int;
  hRAA_int = (TH1D*) hcentSigAA_int->Clone("hRAA_centint");
  hRAA_int ->Divide(hcentSigPP);
  hRAA_int ->Scale( 26000000. / 351 ) ;   // pp : 26pb-1,  PbPb : 351 microBarn-1
  hRAA_int ->Scale( 1./(208*208));

  // Ratio of efficiency 
  hcentEffAA_int->Divide( hcentEffPP );

  hRAA_int ->Divide(hcentEffAA_int);
  hRAA_int ->SetAxisRange(0,1.6,"Y");
  hRAA_int ->SetYTitle("R_{AA}");
  
  TGraphErrors *gre_int = new TGraphErrors();
  gre_int->SetName("raa_integratedBin");
  gre_int->SetTitle("gre_int");
  gre_int->SetPoint(0,1,hRAA_int->GetBinContent(1));
  gre_int->SetPointError(0,0,hRAA_int->GetBinError(1));



  
  hRAA_cent = (TH1D*) hcentSigAA->Clone("hRAA_cent");
  TH1D* htempPP = (TH1D*)hRAA_cent->Clone("htempPP_cent"); 
  htempPP->Reset();
  for(int icent=1; icent<=nCentBins;icent++) {
    htempPP->SetBinContent( icent, yCentPP.val );
    htempPP->SetBinError( icent, yCentPP.err );
  }
  hRAA_cent->Divide(htempPP); 

  hRAA_cent ->Divide(hSetBin);
  hRAA_cent ->Scale( 26000000. / 351 ) ;   // pp : 26pb-1,  PbPb : 351 microBarn-1
  hRAA_cent ->Scale( 1./(208*208));
  hRAA_cent ->Scale(200.*392.);
  hRAA_cent ->SetAxisRange(0,1.2,"Y");
  hRAA_cent ->SetYTitle("R_{AA} (efficiency UNcorrected)");
  hRAA_cent ->Draw();
  jumSun(0,1,30,1);
  
   
  TCanvas* cRAACentEffCor =  new TCanvas("cRAACentEffCor","",400,400);
  TGraphErrors *gre1 = new TGraphErrors(nCentBins);
  gre1->SetName("raa_vs_npart");
  gre1->SetTitle("Graph");

  Int_t cii;      // for color index setting
  TColor *color; // for color definition with alpha
  cii = TColor::GetColor("#6699ff");
  gre1->SetFillColor(cii);
  gre1->SetMarkerStyle(20);
  for(int ibin=0;ibin<nCentBins;ibin++){
<<<<<<< HEAD
    gre1->SetPoint(ibin,nPart[ibin],hRAA_cent->GetBinContent(nCentBins-ibin));
    gre1->SetPointError(ibin,10,hRAA_cent->GetBinError(nCentBins-ibin));}
  gre1->Draw();
  
  for(int ibin = 1; ibin<nCentBins+1; ibin++)
    {
      cout << "yield at " << ibin<<"th bin: "<< hRAA_cent->GetBinContent(ibin) << endl;
    }
  
=======
  gre1->SetPoint(ibin,nPart[ibin],hRAA_cent->GetBinContent(nCentBins-ibin));
  gre1->SetPointError(ibin,10,hRAA_cent->GetBinError(nCentBins-ibin));}
//  gre1->Draw();

  for(int ibin = 1; ibin<nCentBins+1; ibin++)
  {
    cout << "yield at " << ibin<<"th bin: "<< hRAA_cent->GetBinContent(ibin) << endl;
  }


>>>>>>> origin
  hRAA3 = (TH1D*) hRAA_cent ->Clone("hRAA_cent_final");
  TH1D* relativeEff_cent = (TH1D*) hcentEffAA -> Clone("relativeEff_cent");
  // Efficiency ratio : 
  double ppIntEff = hcentEffPP->GetBinContent ( 1 ) ; 
  for(int icent=1; icent<=nCentBins;icent++) {
    relativeEff_cent -> SetBinContent(  icent,   hcentEffAA->GetBinContent( icent ) / ppIntEff ) ;
  }
  
  hRAA3 -> Divide(relativeEff_cent);
  hRAA3 -> SetAxisRange(0,1.2,"Y");
  hRAA3 -> SetTitle("R_{AA}");
  
  TGraphErrors *gre = new TGraphErrors(nCentBins);
  gre->SetName("Graph0");
  gre->SetTitle("Graph");

  Int_t ci;
  ci = TColor::GetColor("#6699ff");
  gre->SetFillColor(ci);
  gre->SetMarkerStyle(10);
  for(int ibin=0;ibin<nCentBins;ibin++){
  gre->SetPoint(ibin,nPart[ibin],hRAA3->GetBinContent(nCentBins-ibin));
  gre->SetPointError(ibin,0,hRAA3->GetBinError(nCentBins-ibin));}
<<<<<<< HEAD
  jumSun(0,1,420,1);

=======
>>>>>>> origin

  
  TPad *padl = new TPad("padl","padl", 0, 0., 0.9, 1);
  TPad *padr = new TPad("padr","padr", 0.9, 0., 1, 1);
//  padl->SetBottomMargin(0);
//  padr->SetBottomMargin(0);

  cRAACentEffCor->cd();  
  padl->Draw();
  padl->cd();
  TH1D *htemp = new TH1D("htemp",";N_{Part};RAA",420,0,420);
  TH1D *htempFull = new TH1D("htempfull","",1,0,2);
  handsomeTG1(gre,2);
  htemp->SetAxisRange(0,1.6,"Y");
  htemp->SetYTitle("R_{AA}");
  handsomeTH1(htemp);
  htemp->DrawCopy();

  gre->Draw("P same");

  drawText(Form("#Upsilon(%dS),  |y| < 2.4",state),0.45,0.87,1,16);
  drawText("p_{T}^{#mu} > 4 GeV", 0.45,0.80,1,16);
  jumSun(0,1,420,1);
  
  padr->SetFrameBorderMode(0);
  padr->SetBorderMode(0);
  padr->SetBorderSize(0);
  padr->SetTicks(0,0);
  padr->Draw();
  padr->cd();
  handsomeTG1(gre_int,2);
  htempFull->SetAxisRange(0,1.6,"Y");
  htempFull->GetXaxis()->SetLabelOffset(999);
  htempFull->GetXaxis()->SetLabelSize(0);
  htempFull->GetYaxis()->SetTickLength(0.);
  htempFull->GetXaxis()->SetTickLength(0.);
  handsomeTH1(htempFull);
  htempFull->DrawCopy();
  gre_int->GetHistogram()->GetXaxis()->SetLabelOffset(999);
  gre_int->GetHistogram()->GetXaxis()->SetLabelSize(0);
  gre_int->GetHistogram()->GetYaxis()->SetLimits(0,1.6);
  gre_int->GetHistogram()->GetYaxis()->SetRangeUser(0,1.6);
  gre_int->GetHistogram()->GetXaxis()->SetLimits(0,2);
  gre_int->GetHistogram()->GetXaxis()->SetRangeUser(0,2);
  gre_int->SetFillColor(ci);
  gre_int->SetMarkerStyle(20);
  gre_int->Draw("P same");

  cRAACentEffCor->SaveAs(Form("raa_vs_cent_%ds.pdf",state));

  TFile *wf = new TFile(Form("finalResults/Ups_%d_RAA.root",state),"recreate");
  gre->Write();
  gre_int->Write();
  hptRAA->Write();
  wf->Close();

  
}

valErr getYield(int state, int collId, float ptLow, float ptHigh, float yLow, float yHigh, int cLow, int cHigh,
		float dphiEp2Low,  float dphiEp2High) {
  TString kineLabel = getKineLabel (collId, ptLow, ptHigh, yLow, yHigh, glbMuPtCut, cLow, cHigh, dphiEp2Low, dphiEp2High) ;
  TString SignalCB = "Double";
  TFile* inf = new TFile(Form("fitResults/%s/fitresults_upsilon_%sCB_%s.root",ResultDir.Data(), SignalCB.Data(),kineLabel.Data()));
  TH1D* fitResults = (TH1D*)inf->Get("fitResults");
  valErr ret; 
  ret.val = fitResults->GetBinContent(state);
  ret.err = fitResults->GetBinError(state);
  cout << kineLabel << ": " << ret.val << " +/- " << ret.err << endl; 
  return ret;
}
