#include "../commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"
#include "../cutsAndBin.h"
#include "../multiTreeUtil.h"
using namespace std;


//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 

TLegend *leg = new TLegend(0.55,0.2, 0.85,0.4,NULL,"brNDC");

void getSysEff(int state = 1) { 
  
  TH1::SetDefaultSumw2();

  int nPtBins=0;
  double* ptBin;
  int nCentBins=0;
  double* centBin;
  int nYBins=0;
  double *yBin;

  if ( state == 1 ) { 
    nPtBins = nPtBins1s;    ptBin = ptBin1s;
    nYBins = nYBins1S;  yBin = yBin1S;
    nCentBins = nCentBins1s;  centBin = centBin1s;
  }
  else if ( state == 2 ) { 
    nPtBins = nPtBins2s;    ptBin = ptBin2s;
    nCentBins = nCentBins2s;  centBin = centBin2s;
    nYBins = nYBins2S;  yBin = yBin2S;
  }
  else if ( state == 3 ) { 
    nPtBins = nPtBins3s;    ptBin = ptBin3s;
    nCentBins = nCentBins3s;  centBin = centBin3s;
    nYBins = nYBins3S;  yBin = yBin3S;
  }

  TFile* f0 = new TFile(Form("efficiency_ups%ds_useDataWeight0.root",state) );
  TH1D* hptEffPPweight0 = (TH1D*)f0->Get("hptEffPP"); 
  TH1D* hptEffAAweight0 = (TH1D*)f0->Get("hptEffAA");
  TH1D* hrapEffPPweight0 = (TH1D*)f0->Get("hrapEffPP");
  TH1D* hrapEffAAweight0 = (TH1D*)f0->Get("hrapEffAA");
  TH1D* hcentEffAAweight0 = (TH1D*)f0->Get("hcentEffAA");
  TH1D* hcentEffAA_intweight0 = (TH1D*)f0->Get("hcentEffAA_int");
  TH1D* hcentEffPPweight0 = (TH1D*)f0->Get("hcentEffPP"); // Integrated bin for pp.  

  TFile* f1 = new TFile(Form("efficiency_ups%ds_useDataWeight1.root",state) );
  TH1D* hptEffPPweight1 = (TH1D*)f1->Get("hptEffPP"); 
  TH1D* hptEffAAweight1 = (TH1D*)f1->Get("hptEffAA");
  TH1D* hrapEffPPweight1 = (TH1D*)f1->Get("hrapEffPP");
  TH1D* hrapEffAAweight1 = (TH1D*)f1->Get("hrapEffAA");
  TH1D* hcentEffAAweight1 = (TH1D*)f1->Get("hcentEffAA");
  TH1D* hcentEffAA_intweight1 = (TH1D*)f1->Get("hcentEffAA_int");
  TH1D* hcentEffPPweight1 = (TH1D*)f1->Get("hcentEffPP"); // Integrated bin for pp.  

  TH1D* hptEffPPsys = (TH1D*)hptEffPPweight0->Clone("hptEffPPsys");
  TH1D* hptEffAAsys = (TH1D*)hptEffAAweight0->Clone("hptEffAAsys");
  TH1D* hrapEffPPsys = (TH1D*)hrapEffPPweight0->Clone("hrapEffPPsys");
  TH1D* hrapEffAAsys = (TH1D*)hrapEffAAweight0->Clone("hrapEffAAsys");
  TH1D* hcentEffAAsys = (TH1D*)hcentEffAAweight0->Clone("hcentEffAAsys");
  TH1D* hcentEffAA_intsys = (TH1D*)hcentEffAA_intweight0->Clone("hcentEffAA_intsys");
  TH1D* hcentEffPPsys = (TH1D*)hcentEffPPweight0->Clone("hcentEffPPsys");

  hptEffPPsys->Add(hptEffPPweight1, -1 );
  hptEffAAsys->Add(hptEffAAweight1, -1 );
  hrapEffPPsys->Add(hrapEffPPweight1, -1 );
  hrapEffAAsys->Add(hrapEffAAweight1, -1 );
  hcentEffAAsys->Add(hcentEffAAweight1, -1 );
  hcentEffAA_intsys->Add(hcentEffAA_intweight1, -1 );
  hcentEffPPsys->Add(hcentEffPPweight1, -1 );

  hptEffPPsys->Divide(hptEffPPweight1);
  hptEffAAsys->Divide(hptEffAAweight1);
  hrapEffPPsys->Divide(hrapEffPPweight1);
  hrapEffAAsys->Divide(hrapEffAAweight1);
  hcentEffAAsys->Divide(hcentEffAAweight1);
  hcentEffAA_intsys->Divide(hcentEffAA_intweight1);
  hcentEffPPsys->Divide(hcentEffPPweight1);

  hptEffPPsys->SetAxisRange(-0.1,0.1,"Y");;   
  hptEffAAsys->SetAxisRange(-0.1,0.1,"Y");;
  hrapEffPPsys->SetAxisRange(-0.1,0.1,"Y");;   
  hrapEffAAsys->SetAxisRange(-0.1,0.1,"Y");;
  hcentEffAA_intsys->SetAxisRange(-0.1,0.1,"Y");;  
  hcentEffAAsys->SetAxisRange(-0.1,0.1,"Y");;
  hcentEffPPsys->SetAxisRange(-0.1,0.1,"Y");;

  
  TCanvas* c = new TCanvas("c1","",800,800);
  c->Divide(2,4);
  c->cd(1) ; hptEffPPsys->Draw();   c->cd(2) ; hptEffAAsys->Draw();
  c->cd(3) ; hrapEffPPsys->Draw();   c->cd(4) ; hrapEffAAsys->Draw();
  c->cd(5) ; hcentEffAA_intsys->Draw();   c->cd(6) ; hcentEffPPsys->Draw();   
  c->cd(7) ; hcentEffAAsys->Draw();
 
  c->SaveAs(Form("sys_efficiency_ups%d.pdf",state));

  cout << " In order of pp and PbPb in (%)" << endl;
  cout <<" integrated bin"<< int( hcentEffAA_intsys->GetBinContent(1) * 1000.)/10. << "  " << int( hcentEffPPsys->GetBinContent(1) * 10000.) / 100. << endl << endl;

  cout << "pt bin" << endl;
  for (int i =1 ; i<= nPtBins ; i++)  {
    cout << int(hptEffPPsys->GetBinContent(i) * 1000.)/10. << "  " << int(hptEffAAsys->GetBinContent(i) * 10000)/100. << endl;
  }
  
  cout << " rap bin" << endl;
  for (int i =1 ; i<= nYBins ; i++)  {
    cout << int( hrapEffPPsys->GetBinContent(i) * 1000.)/10. << "  " << int(hrapEffAAsys->GetBinContent(i)*1000.)/10. << endl;
   }

  cout << "cent bin" << endl;
  for (int i =1 ; i<= nCentBins ; i++)  {
    cout <<  "N/A    " << int(hcentEffAAsys->GetBinContent(i)*1000.)/10. << endl;
  }
  
  TFile *fout = new TFile(Form("sys_efficiency_ups%d.root",state),"recreate");
  hptEffPPsys->Write();   
  hptEffAAsys->Write();
  hrapEffPPsys->Write();   
  hrapEffAAsys->Write();
  hcentEffAA_intsys->Write();  
  hcentEffAAsys->Write();
  hcentEffPPsys->Write();
    
  fout->Close();

}

