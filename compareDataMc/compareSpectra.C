#include "../commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"
#include "../cutsAndBin.h"
using namespace std;


//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 
valErr getYield(int state=0, int collId=0, float ptLow=0, float ptHigh=0, float yLow=0, float yHigh=0, int cLow=0, int cHigh=0, 	float dphiEp2Low=0,  float dphiEp2High=0) ;

Double_t fTsallis1SR(Double_t *x, Double_t *fpar)
{
  Float_t xx = x[0];
  Double_t c = (fpar[0]-1)*(fpar[0]-2)/(fpar[0]*fpar[1]*(fpar[0]*fpar[1]+(fpar[0]-2)*pdgMass.Y1S));
  Double_t mT = TMath::Sqrt(pdgMass.Y1S*pdgMass.Y1S+xx*xx);
  Double_t pow = TMath::Power((1+(mT-pdgMass.Y1S)/(fpar[0]*fpar[1])),-fpar[0]);

  Double_t f = c*xx*pow;


  Double_t c1 = (fpar[2]-1)*(fpar[2]-2)/(fpar[2]*fpar[3]*(fpar[2]*fpar[3]+(fpar[2]-2)*pdgMass.Y1S));
  Double_t mT1 = TMath::Sqrt(pdgMass.Y1S*pdgMass.Y1S+xx*xx);
  Double_t pow1 = TMath::Power((1+(mT1-pdgMass.Y1S)/(fpar[2]*fpar[3])),-fpar[2]);

  Double_t f1 = c1*xx*pow1;

  Double_t fr = f/f1;

                   
  return fr;
}

Double_t fTsallis2SR(Double_t *x, Double_t *fpar)
{
  Float_t xx = x[0];
  Double_t c = (fpar[0]-1)*(fpar[0]-2)/(fpar[0]*fpar[1]*(fpar[0]*fpar[1]+(fpar[0]-2)*pdgMass.Y2S));
  Double_t mT = TMath::Sqrt(pdgMass.Y2S*pdgMass.Y2S+xx*xx);
  Double_t pow = TMath::Power((1+(mT-pdgMass.Y2S)/(fpar[0]*fpar[1])),-fpar[0]);

  Double_t f = c*xx*pow;


  Double_t c1 = (fpar[2]-1)*(fpar[2]-2)/(fpar[2]*fpar[3]*(fpar[2]*fpar[3]+(fpar[2]-2)*pdgMass.Y2S));
  Double_t mT1 = TMath::Sqrt(pdgMass.Y2S*pdgMass.Y2S+xx*xx);
  Double_t pow1 = TMath::Power((1+(mT1-pdgMass.Y2S)/(fpar[2]*fpar[3])),-fpar[2]);

  Double_t f1 = c1*xx*pow1;

  Double_t fr = f/f1;

                   
  return fr;
}

void compareSpectra(int state = 1, int collId= kPPDATA) {
  
  TH1::SetDefaultSumw2();
  //// modify by hand according to the pt range of the sample

  int nPtBins=0;
  double* ptBin;

  if ( state == 1 ) { 
    nPtBins = nPtBins1s;    ptBin = ptBin1s;
  }
  else if ( state == 2 ) { 
    nPtBins = nPtBins1s;    ptBin = ptBin1s;
  }
  else if ( state == 3 ) { 
    nPtBins = nPtBins3s;    ptBin = ptBin3s;
  }
  
  TH1D* hptMc[nYBins+1];
  TH1D* hptSig[nYBins+1];
  TH1D* hRatio[nYBins+1];   // final Ratio w/ efficiency correctdion


  TFile* inf = new TFile(Form("../efficiency/efficiency_ups%ds_MCDATA.root",state));
  for ( int iy=0 ; iy<=nYBins ; iy++) {
    if (collId == kPPDATA ){ 
      hptMc[iy]  = (TH1D*)inf->Get(Form("hptRecoPP_iy%d",iy)); } 
    if (collId == kAADATA ){ 
      hptMc[iy]  = (TH1D*)inf->Get(Form("hptRecoAA_iy%d",iy)); } 
  }
  

  TCanvas* c1 =  new TCanvas("c1","",800,800);
  c1->Divide(nYBins+1,2);
  
  for ( int iy=0 ; iy<=nYBins ; iy++) {
//    c1->cd(iy);
  cout << "ASDas" << endl;
    handsomeTH1(hptMc[iy],1);
    // signals :
    hptSig[iy] = (TH1D*)  hptMc[iy]->Clone(Form("hptSig_iy%d",iy));
    hptSig[iy]->Reset();
    for ( int ipt = 1 ; ipt<= nPtBins ; ipt++) {
      valErr yieldPP;
      if(iy==0) yieldPP = getYield(state, collId, ptBin[ipt-1], ptBin[ipt], 0.0,2.4, 0, 200, 0, 100);
      else yieldPP = getYield(state, collId, ptBin[ipt-1], ptBin[ipt], yBin[iy-1], yBin[iy], 0, 200, 0, 100);
      hptSig[iy]->SetBinContent( ipt, yieldPP.val ) ;
      hptSig[iy]->SetBinError( ipt, yieldPP.err ) ;
    }
  }
  
  TF1* funct[nYBins+1];

  for ( int iy=0 ; iy<=nYBins ; iy++) {
    c1->cd(iy+1) ;
    TH1ScaleByWidth(hptMc[iy]);
    TH1ScaleByWidth(hptSig[iy]);
    scaleInt(hptMc[iy]);
    scaleInt(hptSig[iy]);

    handsomeTH1(hptSig[iy],1);
    hptMc[iy]->SetAxisRange(0,0.35,"Y");
    hptMc[iy]->Draw("hist");
    hptSig[iy]->Draw("same");

    c1->cd(iy+2+nYBins);
    hRatio[iy] = (TH1D*)hptSig[iy]->Clone(Form("hRatio_iy%d",iy));
    hRatio[iy]->Divide(hptMc[iy]);
    hRatio[iy]->SetAxisRange(0,5,"Y");
    handsomeTH1(hRatio[iy],1);
  
    // Fit :
    // TF1 *fVar1pp = new TF1("f1srpp",fTsallis1SR,0,30,4);

  
    if(state==1) funct[iy] = new TF1(Form("dataMcRatio_iy%d",iy),fTsallis1SR, 0,30,4);
    else if(state==2) funct[iy] = new TF1(Form("dataMcRatio_iy%d",iy),fTsallis2SR, 0,30,4);
    
    funct[iy]->SetParameters(5,5,5,5);
    funct[iy]->SetParLimits(0,0.,120);
    funct[iy]->SetParLimits(1,0.,100);
    funct[iy]->SetParLimits(2,0.,150);
    funct[iy]->SetParLimits(3,0.,100);

    hRatio[iy]->Fit ( funct[iy], "R");

    hRatio[iy]->Draw();
    jumSun(0,1,30,1);
    
    cout << "TF1* weightFunction = new TF1(@weightCurve@,@([0] + [1]*x + [2]*x*x + [3]*x*x*x) * ( 1 - TMath::Erf((x-7.5)/2)) + [4] + [5]*x@,0,30);" << endl;   cout << " weightFunction->SetParameters( " ;
    for ( int i=0 ; i<4 ; i++) { 
      if ( i!=3 ) 
        cout << funct[iy]->GetParameter(i) << ", " ;
      else   cout << funct[iy]->GetParameter(i) << "); "<< endl ;
    }
    
  }
  //  cout << " This macro MUST be ran on ROOT5!!!! " << endl;
 
  TString fcollId;
  if(collId == kPPDATA) fcollId = "PP";
  else if(collId == kAADATA) fcollId = "AA";
  
  TF1 *funct_write[nYBins+1];

  for(int iff=0;iff<=nYBins;iff++)
  {
    if(state==1) funct_write[iff] = new TF1(Form("f_%s_1sstate",fcollId.Data()),"([0]-1)*([0]-2)*([2]*[3]*([2]*[3]+([2]-2)*9.460))*TMath::Power((1+(TMath::Sqrt(9.460*9.460+x*x)-9.460)/([0]*[1])),-[0])/(([0]*[1]*([0]*[1]+([0]-2)*9.460))*(([2]-1)*([2]-2))*TMath::Power((1+(TMath::Sqrt(9.460*9.460+x*x)-9.460)/([2]*[3])),-[2]))",0,30);
    else if(state==2) funct_write[iff] = new TF1(Form("f_%s_2sstate",fcollId.Data()),"([0]-1)*([0]-2)*([2]*[3]*([2]*[3]+([2]-2)*10.023))*TMath::Power((1+(TMath::Sqrt(10.023*10.023+x*x)-10.023)/([0]*[1])),-[0])/(([0]*[1]*([0]*[1]+([0]-2)*10.023))*(([2]-1)*([2]-2))*TMath::Power((1+(TMath::Sqrt(10.032*10.023+x*x)-10.023)/([2]*[3])),-[2]))",0,30);

    funct_write[iff] -> FixParameter(0,funct[iff]->GetParameter(0));
    funct_write[iff] -> FixParameter(1,funct[iff]->GetParameter(1));
    funct_write[iff] -> FixParameter(2,funct[iff]->GetParameter(2));
    funct_write[iff] -> FixParameter(3,funct[iff]->GetParameter(3));
  }

  

  c1->SaveAs(Form("dNdpT_dataMC_%s_DATA_%dsState.png",fcollId.Data(),state));
  TFile* outf = new TFile(Form("ratioDataMC_%s_%dsState.root",getCollID(collId).Data(), state),"recreate");
  for ( int iy=0 ; iy<=nYBins ; iy++) {
    hRatio[iy]->Write();
    hptSig[iy]->SetName(Form("hData_iy%d",iy));
    hptMc[iy]->SetName(Form("hMC_iy%d",iy));
    hptSig[iy]->Write();
    hptMc[iy]->Write();
    funct[iy]->Write();
  }
  
  outf->Write();
  
}


valErr getYield(int state, int collId, float ptLow, float ptHigh, float yLow, float yHigh, int cLow, int cHigh,
		float dphiEp2Low,  float dphiEp2High) {
  TString kineLabel = getKineLabel (collId, ptLow, ptHigh, yLow, yHigh, glbMuPtCut, cLow, cHigh, dphiEp2Low, dphiEp2High) ;
  TString SignalCB = "Double";
  TFile* inf = new TFile(Form("../fitResults/dataFit_fixParam1MuPt4_2016_08_30/fitresults_upsilon_%sCB_%s.root",SignalCB.Data(),kineLabel.Data()));
  TH1D* fitResults = (TH1D*)inf->Get("fitResults");
  valErr ret; 
  ret.val = fitResults->GetBinContent(state);
  ret.err = fitResults->GetBinError(state);
  cout << kineLabel << ": " << ret.val << " +/- " << ret.err << endl; 
  return ret;
}
