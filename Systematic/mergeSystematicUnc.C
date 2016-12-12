#include "../commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"
#include "../cutsAndBin.h"
#include "../multiTreeUtil.h"
using namespace std;


//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 

TLegend *leg = new TLegend(0.55,0.2, 0.85,0.4,NULL,"brNDC");
void mergeFourInQuad( TH1D* h0=0, TH1D* h1=0, TH1D* h2=0, TH1D* h3=0, TH1D* h4=0);
void mergeTwoInQuad( TH1D* h0=0, TH1D* h1=0, TH1D* h2=0);
void mergeTwoInQuadCent( TH1D* h0=0, TH1D* hAA=0, TH1D* hPP=0);
void subtractTwo( TH1D* h0=0, TH1D* h1=0, TH1D* h2=0);
void subtractTwoCent( TH1D* h0=0, TH1D* hAA=0, TH1D* hPP=0);

void mergeSystematicUnc(int state = 1) { 
  
  TH1::SetDefaultSumw2();

  cout << "Make sure to make the soft link to acceptance and efficiency directory before running this macro!!" << endl;
  cout << "  ln -s ../acceptance" << endl;
  cout << "  ln -s ../efficiency" << endl;
  
  
  TH1D* hptPP[10];
  TH1D* hptAA[10];
  TH1D* hrapPP[10];
  TH1D* hrapAA[10];
  TH1D* hcentAA[10];
  TH1D* hintAA[10];
  TH1D* hintPP[10];

  TH1D* hptRAA[10];
  TH1D* hrapRAA[10];
  TH1D* hcentRAA[10];
  TH1D* hintRAA[10];
  

  // 1 : efficiency
  TFile* f1 = new TFile(Form("../efficiency/sys_efficiency_ups%d.root",state) );
  hptPP[1] = (TH1D*)f1->Get("hptEffPPsys");
  hptAA[1] = (TH1D*)f1->Get("hptEffAAsys");
  hrapPP[1] = (TH1D*)f1->Get("hrapEffPPsys");
  hrapAA[1] = (TH1D*)f1->Get("hrapEffAAsys");
  hintPP[1] = (TH1D*)f1->Get("hcentEffPPsys");
  hintAA[1] = (TH1D*)f1->Get("hcentEffAA_intsys");
  hcentAA[1]= (TH1D*)f1->Get("hcentEffAAsys");

  hptRAA[1] = (TH1D*)hptAA[1]->Clone("hptRAA_1");   hptRAA[1]->Reset();
  hrapRAA[1] = (TH1D*)hrapAA[1]->Clone("hrapRAA_1");   hrapRAA[1]->Reset();
  hcentRAA[1] = (TH1D*)hcentAA[1]->Clone("hcentRAA_1");    hcentRAA[1]->Reset();
  hintRAA[1] = (TH1D*)hintAA[1]->Clone("hintRAA_1");    hintRAA[1]->Reset();
  
  mergeTwoInQuad( hptRAA[1], hptAA[1], hptPP[1] );
  mergeTwoInQuad( hrapRAA[1], hrapAA[1], hrapPP[1] );
  mergeTwoInQuadCent( hcentRAA[1], hcentAA[1], hintPP[1] );
  mergeTwoInQuad( hintRAA[1], hintAA[1], hintPP[1] );
  


  // 2 : acceptance
  TFile* f2 = new TFile(Form("../acceptance/sys_acceptance_ups%d.root",state));
  hptPP[2] = (TH1D*)f2->Get("hptSysPP");
  hptAA[2] = (TH1D*)f2->Get("hptSysAA");
  hrapPP[2] = (TH1D*)f2->Get("hrapSysPP");
  hrapAA[2] = (TH1D*)f2->Get("hrapSysAA");
  hcentAA[2]= (TH1D*)f2->Get("hcentSysAA");
  hintAA[2] = (TH1D*)f2->Get("hcentSysAA_int");
  hintPP[2] = (TH1D*)f2->Get("hcentSysPP");

  hptRAA[2] = (TH1D*)hptAA[2]->Clone("hptRAA_1");   hptRAA[2]->Reset();
  hrapRAA[2] = (TH1D*)hrapAA[2]->Clone("hrapRAA_1");   hrapRAA[2]->Reset();
  hcentRAA[2] = (TH1D*)hcentAA[2]->Clone("hcentRAA_1");    hcentRAA[2]->Reset();
  hintRAA[2] = (TH1D*)hintAA[2]->Clone("hintRAA_1");    hintRAA[2]->Reset();

  mergeTwoInQuad( hptRAA[2], hptAA[2], hptPP[2] );
  mergeTwoInQuad( hrapRAA[2], hrapAA[2], hrapPP[2] );
  mergeTwoInQuadCent( hcentRAA[2], hcentAA[2], hintPP[2] );
  mergeTwoInQuad( hintRAA[2], hintAA[2], hintPP[2] );

  // 3 : signal PDF
  TFile* f3 = new TFile(Form("SignalVariation_keep/sys_signalPDFVariaion_%ds.root",state));
  hptPP[3] = (TH1D*)f3->Get("hptPP"); hptPP[3]->SetName("hptPPsig");
  hptAA[3] = (TH1D*)f3->Get("hptAA"); hptAA[3]->SetName("hptAAsig");
  hrapPP[3] = (TH1D*)f3->Get("hrapPP"); hrapPP[3]->SetName("hrapPPsig");
  hrapAA[3] = (TH1D*)f3->Get("hrapAA"); hrapAA[3]->SetName("hrapAAsig");
  hcentAA[3]= (TH1D*)f3->Get("hcentAA"); hcentAA[3]->SetName("hcentAAsig");
  hintAA[3] = (TH1D*)f3->Get("hIntAA"); hintAA[3]->SetName("hintAAsig");
  hintPP[3] = (TH1D*)f3->Get("hIntPP"); hintPP[3]->SetName("hintPPsig");

  hptRAA[3] = (TH1D*)hptAA[3]->Clone("hptRAA_1");   hptRAA[3]->Reset();
  hrapRAA[3] = (TH1D*)hrapAA[3]->Clone("hrapRAA_1");   hrapRAA[3]->Reset();
  hcentRAA[3] = (TH1D*)hcentAA[3]->Clone("hcentRAA_1");    hcentRAA[3]->Reset();
  hintRAA[3] = (TH1D*)hintAA[3]->Clone("hintRAA_1");    hintRAA[3]->Reset();

  mergeTwoInQuad( hptRAA[2], hptAA[2], hptPP[2] );
  mergeTwoInQuad( hrapRAA[2], hrapAA[2], hrapPP[2] );
  mergeTwoInQuadCent( hcentRAA[2], hcentAA[2], hintPP[2] );
  mergeTwoInQuad( hintRAA[2], hintAA[2], hintPP[2] );

  // 4 : background PDF 
  TFile* f4 = new TFile(Form("backgroundVariation/sys_bkgPDFVariaion_%ds.root",state));
  hptPP[4] = (TH1D*)f4->Get("hptPP"); hptPP[4]->SetName("hptPPsig");
  hptAA[4] = (TH1D*)f4->Get("hptAA"); hptAA[4]->SetName("hptAAsig");
  hrapPP[4] = (TH1D*)f4->Get("hrapPP"); hrapPP[4]->SetName("hrapPPsig");
  hrapAA[4] = (TH1D*)f4->Get("hrapAA"); hrapAA[4]->SetName("hrapAAsig");
  hcentAA[4]= (TH1D*)f4->Get("hcentAA"); hcentAA[4]->SetName("hcentAAsig");
  hintAA[4] = (TH1D*)f4->Get("hIntAA"); hintAA[4]->SetName("hintAAsig");
  hintPP[4] = (TH1D*)f4->Get("hIntPP"); hintPP[4]->SetName("hintPPsig");
  
  hptRAA[4] = (TH1D*)hptAA[4]->Clone("hptRAA_1");   hptRAA[4]->Reset();
  hrapRAA[4] = (TH1D*)hrapAA[4]->Clone("hrapRAA_1");   hrapRAA[4]->Reset();
  hcentRAA[4] = (TH1D*)hcentAA[4]->Clone("hcentRAA_1");    hcentRAA[4]->Reset();
  hintRAA[4] = (TH1D*)hintAA[4]->Clone("hintRAA_1");    hintRAA[4]->Reset();

  subtractTwo( hptRAA[4], hptAA[4], hptPP[4] );
  subtractTwo( hrapRAA[4], hrapAA[4], hrapPP[4] );
  subtractTwoCent( hcentRAA[4], hcentAA[4], hintPP[4] );
  subtractTwo( hintRAA[4], hintAA[4], hintPP[4] );


  // Merge uncertainties for cross-section 
  hptPP[0] = (TH1D*)hptPP[1]->Clone("hptPP_merged"); hptPP[0]->Reset();
  hptAA[0] = (TH1D*)hptAA[1]->Clone("hptAA_merged"); hptAA[0]->Reset();
  hrapPP[0] = (TH1D*)hrapPP[1]->Clone("hrapPP_merged"); hrapPP[0]->Reset();
  hrapAA[0] = (TH1D*)hrapAA[1]->Clone("hrapAA_merged"); hrapAA[0]->Reset();
  hcentAA[0] = (TH1D*)hcentAA[1]->Clone("hcentAA_merged"); hcentAA[0]->Reset();
  hintAA[0] = (TH1D*)hintAA[1]->Clone("hintAA_merged"); hintAA[0]->Reset();
  hintPP[0] = (TH1D*)hintPP[1]->Clone("hintPP_merged"); hintPP[0]->Reset();

  mergeFourInQuad( hptPP[0], hptPP[1], hptPP[2], hptPP[3], hptPP[4] );
  mergeFourInQuad( hrapPP[0], hrapPP[1], hrapPP[2], hrapPP[3], hrapPP[4] );
  mergeFourInQuad( hptAA[0], hptAA[1], hptAA[2], hptAA[3], hptAA[4] );
  mergeFourInQuad( hrapAA[0], hrapAA[1], hrapAA[2], hrapAA[3], hrapAA[4] );
  mergeFourInQuad( hcentAA[0], hcentAA[1], hcentAA[2], hcentAA[3], hcentAA[4] );
  mergeFourInQuad( hintAA[0], hintAA[1], hintAA[2], hintAA[3], hintAA[4] );
  mergeFourInQuad( hintPP[0], hintPP[1], hintPP[2], hintPP[3], hintPP[4] );

  // Merge uncertainties for RAA
  hptRAA[0] = (TH1D*)hptRAA[1]->Clone("hptRAA_merged"); hptRAA[0]->Reset();
  hrapRAA[0] = (TH1D*)hrapRAA[1]->Clone("hrapRAA_merged"); hrapRAA[0]->Reset();  
  hcentRAA[0] = (TH1D*)hcentRAA[1]->Clone("hcentRAA_merged"); hcentRAA[0]->Reset();
  hintRAA[0] = (TH1D*)hintRAA[1]->Clone("hintRAA_merged"); hintRAA[0]->Reset();
  
  mergeFourInQuad( hptRAA[0], hptRAA[1], hptRAA[2], hptRAA[3], hptRAA[4] );
  mergeFourInQuad( hrapRAA[0], hrapRAA[1], hrapRAA[2], hrapRAA[3], hrapRAA[4] );
  mergeFourInQuad( hcentRAA[0], hcentRAA[1], hcentRAA[2], hcentRAA[3], hcentRAA[4] );
  mergeFourInQuad( hintRAA[0], hintRAA[1], hintRAA[2], hintRAA[3], hintRAA[4] );
  
  
  
  TCanvas* c1= new TCanvas("c1","",800,800);
  c1->Divide(2,4);
  c1->cd(1);
  hptPP[0]->Draw();
  c1->cd(2);
  hptAA[0]->Draw();
  c1->cd(3);
  hrapPP[0]->Draw();
  c1->cd(4);
  hrapAA[0]->Draw();
  c1->cd(5);
  hintPP[0]->Draw();
  c1->cd(6);
  hintAA[0]->Draw();
  c1->cd(7);
  hcentAA[0]->Draw();
   
  TCanvas* c2= new TCanvas("c2","",800,800);
  c2->Divide(2,2);
  c2->cd(1);
  hptRAA[0]->Draw();
  c2->cd(2);
  hrapRAA[0]->Draw();
  c2->cd(3);
  hcentRAA[0]->Draw();
  c2->cd(4);
  hintRAA[0]->Draw();


  TFile* fout = new TFile(Form("mergedSys_ups%ds.root",state),"recreate" );
  hptPP[0]->Write();
  hptAA[0]->Write();
  hrapPP[0]->Write();
  hrapAA[0]->Write();
  hintPP[0]->Write();
  hintAA[0]->Write();
  hcentAA[0]->Write();

  hptRAA[0]->Write();
  hrapRAA[0]->Write();
  hcentRAA[0]->Write();
  hintRAA[0]->Write();
  fout->Close();

}


void mergeFourInQuad( TH1D* h0, TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4) {
  for ( int i=1 ; i<= h0->GetNbinsX() ;i++){ 
    float a1 = h1->GetBinContent(i);
    float a2 = h2->GetBinContent(i);
    float a3 = h3->GetBinContent(i);
    float a4 = h4->GetBinContent(i);
    float a0 = sqrt( a1*a1 + a2*a2 + a3*a3 + a4*a4 );
    h0->SetBinContent( i, a0);
  } 
}

void mergeTwoInQuad( TH1D* h0, TH1D* h1, TH1D* h2) {
  for ( int i=1 ; i<= h0->GetNbinsX() ;i++){ 
    float a1 = h1->GetBinContent(i);
    float a2 = h2->GetBinContent(i);
    float a0 = sqrt( a1*a1 + a2*a2);
    h0->SetBinContent( i, a0);
  } 
}

void subtractTwo( TH1D* h0, TH1D* h1, TH1D* h2) {
  if ( ( h0->GetNbinsX() != h1->GetNbinsX() ) ) {
    cout << "Inconsistent bin numbers!! ERROR" << endl;
  }
  else {
    for ( int i=1 ; i<= h0->GetNbinsX() ;i++){ 
      float a1 = h1->GetBinContent(i);
      float a2 = h2->GetBinContent(i);
      float a0 = (1. + a1) / ( 1. + a2) - 1; 
      h0->SetBinContent( i, a0);
    } 
  }
}
void mergeTwoInQuadCent( TH1D* h0, TH1D* hAA, TH1D* hPP) {
  if ( (hPP->GetNbinsX() != 1 ) )  {
    cout << "Number of hPP bins are not 1!! ERROR" << endl;
  }
  else if ( ( h0->GetNbinsX() != hAA->GetNbinsX() ) ) {
    cout << "Inconsistent bin numbers!! ERROR" << endl;
  }
  else  {
    for ( int i=1 ; i<= h0->GetNbinsX() ;i++){
      float a1 = hAA->GetBinContent(i);
      float a2 = hPP->GetBinContent(1);
      float a0 = sqrt( a1*a1 + a2*a2); 
      h0->SetBinContent( i, a0);
    }
  }
}

void subtractTwoCent( TH1D* h0, TH1D* hAA, TH1D* hPP) {
  if ( (hPP->GetNbinsX() != 1 ) )  {
    cout << "Number of hPP bins are not 1!! ERROR" << endl;
  }
  else if ( ( h0->GetNbinsX() != hAA->GetNbinsX() ) ) {
    cout << "Inconsistent bin numbers!! ERROR" << endl;
  }
  else  {
    for ( int i=1 ; i<= h0->GetNbinsX() ;i++){
      float a1 = hAA->GetBinContent(i);
      float a2 = hPP->GetBinContent(1);
      float a0 = (1. + a1) / ( 1. + a2) - 1;
      h0->SetBinContent( i, a0);
    }
  }
}
