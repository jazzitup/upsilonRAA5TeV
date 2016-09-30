#include "commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"
#include "cutsAndBin.h"
using namespace std;


//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 
valErr getYield(int state=0, int collId=0, float ptLow=0, float ptHigh=0, float yLow=0, float yHigh=0, int cLow=0, int cHigh=0, 	float dphiEp2Low=0,  float dphiEp2High=0) ;


void compareSpectra(int state = 1, int collId= kPPDATA) {
  
  TH1::SetDefaultSumw2();
  //// modify by hand according to the pt range of the sample

  int nPtBins=0;
  double* ptBin;

  if ( state == 1 ) { 
    nPtBins = nPtBins1s;    ptBin = ptBin1s;
  }
  else if ( state == 2 ) { 
    nPtBins = nPtBins2s;    ptBin = ptBin2s;
  }
  else if ( state == 3 ) { 
    nPtBins = nPtBins3s;    ptBin = ptBin3s;
  }
  
  TH1D* hptMc[nYBins+1];
  TH1D* hptSig[nYBins+1];
  TH1D* hRatio[nYBins+1];   // final Ratio w/ efficiency correctdion


  TFile* inf = new TFile(Form("efficiency/efficiency_ups%ds.root",state));
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    if (collId == kPPDATA ){ 
      hptMc[iy]  = (TH1D*)inf->Get(Form("hptRecoPP_iy%d",iy)); } 
    if (collId == kAADATA ){ 
      hptMc[iy]  = (TH1D*)inf->Get(Form("hptRecoAA_iy%d",iy)); } 
  }
  
  
  TCanvas* c1 =  new TCanvas("c1","",800,800);
  c1->Divide(nYBins,2);
  
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    c1->cd(iy);
    handsomeTH1(hptMc[iy],1);
    // signals :
    hptSig[iy] = (TH1D*)  hptMc[iy]->Clone(Form("hptSig_iy%d",iy));
    hptSig[iy]->Reset();
    for ( int ipt = 1 ; ipt<= nPtBins ; ipt++) {
      valErr yieldPP = getYield(state, collId, ptBin[ipt-1], ptBin[ipt], yBin[iy-1], yBin[iy], 0, 200, 0, 100);
      hptSig[iy]->SetBinContent( ipt, yieldPP.val ) ;
      hptSig[iy]->SetBinError( ipt, yieldPP.err ) ;
    }
  }
  
  TF1* funct[nYBins+1];

  for ( int iy=1 ; iy<=nYBins ; iy++) {
    c1->cd(iy) ;
    TH1ScaleByWidth(hptMc[iy]);
    TH1ScaleByWidth(hptSig[iy]);
    scaleInt(hptMc[iy]);
    scaleInt(hptSig[iy]);

    handsomeTH1(hptSig[iy],1);
    hptMc[iy]->SetAxisRange(0,0.35,"Y");
    hptMc[iy]->Draw("hist");
    hptSig[iy]->Draw("same");

    c1->cd(iy+nYBins);
    hRatio[iy] = (TH1D*)hptSig[iy]->Clone(Form("hRatio_iy%d",iy));
    hRatio[iy]->Divide(hptMc[iy]);
    hRatio[iy]->SetAxisRange(0,2,"Y");
    handsomeTH1(hRatio[iy],1);
  
    // Fit :
    funct[iy] = new TF1(Form("dataMcRatio_iy%d",iy),
			//			"([0] + [1]*x + [2]*x*x + [3]*x*x*x) * ( 1 - TMath::Erf((x-7.5)/3)) + [4] + [5]*x", 0,30);
			"([0] + [1]*x + [2]*x*x + [3]*x*x*x) * ( 1 - TMath::Erf((x-7.5)/2)) + [4] + [5]*x", 0,30);
    
    funct[iy]->SetParameters(1, 1, 0.1,0.1,0.1);
    //    hRatio[iy]->Fit ( funct[iy]->GetName(), "R");
    hRatio[iy]->Fit ( funct[iy], "R");

    hRatio[iy]->Draw();
    jumSun(0,1,30,1);
    
    cout << "TF1* weightFunction = new TF1(@weightCurve@,@([0] + [1]*x + [2]*x*x + [3]*x*x*x) * ( 1 - TMath::Erf((x-7.5)/2)) + [4] + [5]*x@,0,30);" << endl;   cout << " weightFunction->SetParameters( " ;
    for ( int i=0 ; i<=5 ; i++) { 
      if ( i!=5 ) 
	cout << funct[iy]->GetParameter(i) << ", " ;
      else   cout << funct[iy]->GetParameter(i) << "); "<< endl ;
    }
    
  }
  //  cout << " This macro MUST be ran on ROOT5!!!! " << endl;
  c1->SaveAs(Form("dNdpT_dataMC_%s_%dsState.png",getCollID(collId).Data(), state));
  
  /*
  TFile* outf = new TFile(Form("ratioDataMC_%s_%dsState.root",getCollID(collId).Data(), state),"recreate");
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    hRatio[iy]->Write();
    hptSig[iy]->SetName(Form("hData_iy%d",iy));
    hptMc[iy]->SetName(Form("hMC_iy%d",iy));
    funct[iy]->SetName(Form("fitFunction_iy%d",iy));
    hptSig[iy]->Write();
    hptMc[iy]->Write();
    funct[iy]->Write();
  }
  */
  //  outf->Write();
  
}

valErr getYield(int state, int collId, float ptLow, float ptHigh, float yLow, float yHigh, int cLow, int cHigh,
		float dphiEp2Low,  float dphiEp2High) {
  TString kineLabel = getKineLabel (collId, ptLow, ptHigh, yLow, yHigh, glbMuPtCut, cLow, cHigh, dphiEp2Low, dphiEp2High) ;
  TString SignalCB = "Double";
  TFile* inf = new TFile(Form("fitResults/dataFit_fixParam1MuPt4_2016_08_12/fitresults_upsilon_%sCB_%s.root",SignalCB.Data(),kineLabel.Data()));
  TH1D* fitResults = (TH1D*)inf->Get("fitResults");
  valErr ret; 
  ret.val = fitResults->GetBinContent(state);
  ret.err = fitResults->GetBinError(state);
  cout << kineLabel << ": " << ret.val << " +/- " << ret.err << endl; 
  return ret;
}
