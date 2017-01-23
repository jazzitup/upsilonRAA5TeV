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

void compareSpectra(int state = 2, int collId= kAADATA) {
  cout << "Run getMcSepctra.C before running this macro" << endl;
  
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
    nPtBins = nPtBins1s;    ptBin = ptBin1s;
  }
  
  TH1D* hptMc;
  TH1D* hptSig;
  TH1D* hRatio;   // final Ratio w/ efficiency correctdion


  //  TFile* inf = new TFile(Form("../efficiency/efficiency_ups%ds_MC_noWeight.root",state));
  TFile* inf = new TFile(Form("mcSpectra/efficiency_ups%ds_useDataPtWeight0_tnpWeight1_tnpIdx0.root",state));
  if (collId == kPPDATA ){ 
      hptMc  = (TH1D*)inf->Get("hptRecoPP"); } 
  if (collId == kAADATA ){ 
      hptMc  = (TH1D*)inf->Get("hptRecoAA"); } 
  
  

  TCanvas* c1 =  new TCanvas("c1","",800,800);
  c1->Divide(1,2);
  
  handsomeTH1(hptMc,1);
  // signals :
  hptSig = (TH1D*)  hptMc->Clone("hptSig");
  hptSig->Reset();
  for ( int ipt = 1 ; ipt<= nPtBins ; ipt++) {
    valErr yieldPP;
    yieldPP = getYield(state, collId, ptBin[ipt-1], ptBin[ipt], 0.0,2.4, 0, 200, 0, 100);
    hptSig->SetBinContent( ipt, yieldPP.val ) ;
    hptSig->SetBinError( ipt, yieldPP.err ) ;
  }
  
  
  TF1* funct;

  c1->cd(1) ;
  TH1ScaleByWidth(hptMc);
  TH1ScaleByWidth(hptSig);
  scaleInt(hptMc);
  scaleInt(hptSig);

  handsomeTH1(hptSig,1);
  hptMc->SetAxisRange(0,0.95,"Y");
  hptMc->Draw("hist");
  hptSig->Draw("same");

  c1->cd(2);
  hRatio = (TH1D*)hptSig->Clone("hRatio");
  hRatio ->Divide(hptMc);
  hRatio ->SetAxisRange(0,5,"Y");
  handsomeTH1(hRatio,1);

  // Fit :
  // TF1 *fVar1pp = new TF1("f1srpp",fTsallis1SR,0,30,4);


  if(state==1) funct = new TF1("dataMcRatio",fTsallis1SR, 0,30,4);
  //else if(state==2) funct = new TF1("dataMcRatio","[0]*x+[1]", 0,30);
  else if(state==2) funct = new TF1("dataMcRatio",fTsallis2SR, 0,30,4);

  //PP 1S
/*  funct->SetParameters(0.06123,1.023,2.123,1);
  funct->SetParLimits(0,-1.,1.3);
  funct->SetParLimits(1, 0.001,3.1);
  funct->SetParLimits(2,0.12,6);
  funct->SetParLimits(3,-1.,20);
  */

  //AA 1S
  
  funct->SetParameters(0.06123,1.023,2.123,1);
  funct->SetParLimits(0,-1.,4.3);
  funct->SetParLimits(1, 0.00,5.1);
  funct->SetParLimits(2,0.1,6);
  funct->SetParLimits(3,-1.,20);
  

  //2S
 /* funct->SetParameters(5,5,5,5);
  funct->SetParLimits(0,0.,150.3);
  funct->SetParLimits(1, 0.0,150.1);
  funct->SetParLimits(2,0.0,150);
  funct->SetParLimits(3,0.,150);
  */
  hRatio->Fit ( funct, "REM");
  hRatio->Draw();
  jumSun(0,1,30,1);

  if(state==1)
  { 
    cout << "TF1* weightFunction = new TF1(@weightCurve@,@(([0]-1)*([0]-2)*([2]*[3]*([2]*[3]+([2]-2)*9.460))*TMath::Power((1+(TMath::Sqrt(9.460*9.460+x*x)-9.460)/([0]*[1])),-[0])/(([0]*[1]*([0]*[1]+([0]-2)*9.460))*(([2]-1)*([2]-2))*TMath::Power((1+(TMath::Sqrt(9.460*9.460+x*x)-9.460)/([2]*[3])),-[2]))));" << endl;   cout << " weightFunction->SetParameters( " ;
    for ( int i=0 ; i<4 ; i++) 
    { 
      if ( i!=3 ) 
        cout << funct->GetParameter(i) << ", " ;
      else   cout << funct->GetParameter(i) << "); "<< endl ;
    }
  }
  else if(state==2)
  {
    //cout << "TF1* weightFunction = new TF1(@weightCurve@,@[0]*x+[1]);" << endl;   cout << " weightFunction->SetParameters( " ;
    cout << "TF1* weightFunction = new TF1(@weightCurve@,@(([0]-1)*([0]-2)*([2]*[3]*([2]*[3]+([2]-2)*10.023))*TMath::Power((1+(TMath::Sqrt(10.023*10.023+x*x)-10.023)/([0]*[1])),-[0])/(([0]*[1]*([0]*[1]+([0]-2)*10.023))*(([2]-1)*([2]-2))*TMath::Power((1+(TMath::Sqrt(10.032*10.023+x*x)-10.023)/([2]*[3])),-[2]))));" << endl;   cout << " weightFunction->SetParameters( " ;
    for ( int i=0 ; i<4 ; i++) 
    { 
      if ( i!=3 ) 
        cout << funct->GetParameter(i) << ", " ;
      else   cout << funct->GetParameter(i) << "); "<< endl ;
    }
  }

  //  cout << " This macro MUST be ran on ROOT5!!!! " << endl;

  TString fcollId;
  if(collId == kPPDATA) fcollId = "PP";
  else if(collId == kAADATA) fcollId = "AA";

  TF1 *funct_write;

  if(state==1) funct_write = new TF1(Form("f_%s_1sstate",fcollId.Data()),"([0]-1)*([0]-2)*([2]*[3]*([2]*[3]+([2]-2)*9.460))*TMath::Power((1+(TMath::Sqrt(9.460*9.460+x*x)-9.460)/([0]*[1])),-[0])/(([0]*[1]*([0]*[1]+([0]-2)*9.460))*(([2]-1)*([2]-2))*TMath::Power((1+(TMath::Sqrt(9.460*9.460+x*x)-9.460)/([2]*[3])),-[2]))",0,30);
  //else if(state==2) funct_write = new TF1(Form("f_%s_2sstate",fcollId.Data()),"[0]*x+[1]",0,30);
  else if(state==2) funct_write = new TF1(Form("f_%s_2sstate",fcollId.Data()),"([0]-1)*([0]-2)*([2]*[3]*([2]*[3]+([2]-2)*10.023))*TMath::Power((1+(TMath::Sqrt(10.023*10.023+x*x)-10.023)/([0]*[1])),-[0])/(([0]*[1]*([0]*[1]+([0]-2)*10.023))*(([2]-1)*([2]-2))*TMath::Power((1+(TMath::Sqrt(10.032*10.023+x*x)-10.023)/([2]*[3])),-[2]))",0,30);

  funct_write -> FixParameter(0,funct->GetParameter(0));
  funct_write -> FixParameter(1,funct->GetParameter(1));
  funct_write -> FixParameter(2,funct->GetParameter(2));
  funct_write -> FixParameter(3,funct->GetParameter(3));

  c1->SaveAs(Form("dNdpT_dataMC_%s_DATA_%dsState.png",fcollId.Data(),state));
  TFile* outf = new TFile(Form("ratioDataMC_%s_%dsState.root",getCollID(collId).Data(), state),"recreate");
  hRatio->Write();
  hptSig->SetName("hData");
  hptMc->SetName("hMC");
  hptSig->Write();
  hptMc->Write();
  funct->Write();

  outf->Write();

}


valErr getYield(int state, int collId, float ptLow, float ptHigh, float yLow, float yHigh, int cLow, int cHigh,
    float dphiEp2Low,  float dphiEp2High) {
  TString kineLabel = getKineLabel (collId, ptLow, ptHigh, yLow, yHigh, glbMuPtCut, cLow, cHigh, dphiEp2Low, dphiEp2High) ;
  TString SignalCB = "Double";
  //  TFile* inf = new TFile(Form("../fitResults/nominalFits/fitresults_upsilon_%sCB_%s.root",SignalCB.Data(),kineLabel.Data()));
  TFile* inf = new TFile(Form("../fitResults/ptDependence/PAS_fitresults_upsilon_%sCB_%s.root",SignalCB.Data(),kineLabel.Data()));
  //  TFile* inf = new TFile(Form("/home/deathold/work/CMS/analysis/Upsilon_RAA/upsilonRAA5TeV/TEST_newNom/PAS_fitresults_upsilon_%sCB_%s.root",SignalCB.Data(),kineLabel.Data()));
  TH1D* fitResults = (TH1D*)inf->Get("fitResults");
  valErr ret; 
  ret.val = fitResults->GetBinContent(state);
  ret.err = fitResults->GetBinError(state);
  cout << kineLabel << ": " << ret.val << " +/- " << ret.err << endl; 
  return ret;
}
