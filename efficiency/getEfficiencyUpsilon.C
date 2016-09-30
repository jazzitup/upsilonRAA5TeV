#include "../commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"
#include "../cutsAndBin.h"
#include "../multiTreeUtil.h"
using namespace std;


//// do NOT use "hadded" ttrees!! (e.g.6-100 GeV) 

TLegend *leg = new TLegend(0.55,0.2, 0.85,0.4,NULL,"brNDC");

void setupMultiTreeTool( multiTreeUtil* mt=0, int UpsState=kPPMCUps1S, bool isGen=true) ;
void getEfficiencyUpsilon(int state = 1) {  // 1S, 2S, 3S
  
  TH1::SetDefaultSumw2();
  //// modify by hand according to the pt range of the sample

  

  
  TCut accCut = Form("(pt1>%f) && (pt2>%f)", (float)glbMuPtCut, (float)glbMuPtCut);
  multiTreeUtil* genAA = new multiTreeUtil();
  multiTreeUtil* recoAA = new multiTreeUtil();
  multiTreeUtil* genPP = new multiTreeUtil();
  multiTreeUtil* recoPP = new multiTreeUtil();

  int nPtBins=0;
  double* ptBin;
  int nCentBins=0;
  double* centBin;

  if ( state == 1 ) { 
    nPtBins = nPtBins1s;    ptBin = ptBin1s;
    nCentBins = nCentBins1s;  centBin = centBin1s;
    setupMultiTreeTool(genAA, kAAMCUps1S, true);  // isGen = 1
    setupMultiTreeTool(recoAA, kAAMCUps1S, false);  
    setupMultiTreeTool(genPP, kPPMCUps1S, true);  // isGen = 1
    setupMultiTreeTool(recoPP, kPPMCUps1S, false);  
  }
  else if ( state == 2 ) { 
    nPtBins = nPtBins2s;    ptBin = ptBin2s;
    nCentBins = nCentBins2s;  centBin = centBin2s;
    setupMultiTreeTool(genAA, kAAMCUps2S, true);  // isGen = 1
    setupMultiTreeTool(recoAA, kAAMCUps2S, false);  
    setupMultiTreeTool(genPP, kPPMCUps2S, true);  // isGen = 1
    setupMultiTreeTool(recoPP, kPPMCUps2S, false);  
  }
  else if ( state == 3 ) { 
    nPtBins = nPtBins3s;    ptBin = ptBin3s;
    nCentBins = nCentBins3s;  centBin = centBin3s;
    setupMultiTreeTool(genAA, kAAMCUps3S, true);  // isGen = 1
    setupMultiTreeTool(recoAA, kAAMCUps3S, false);  
    setupMultiTreeTool(genPP, kPPMCUps3S, true);  // isGen = 1
    setupMultiTreeTool(recoPP, kPPMCUps3S, false);  
  }


  TH1D* hptGenAA[nYBins+1];
  TH1D* hptRecoAA[nYBins+1];
  TH1D* hptGenPP[nYBins+1];
  TH1D* hptRecoPP[nYBins+1];
  
  TH1D* hcentGenAA[nYBins+1];
  TH1D* hcentRecoAA[nYBins+1];
  TH1D* hcentGenPP[nYBins+1];
  TH1D* hcentRecoPP[nYBins+1];
  bool doCent = true; 

  for ( int iy=1 ; iy<=nYBins ; iy++) {
    TCut yCut = Form("(y>=%f) && ( y<%f)", float(yBin[iy-1]), float(yBin[iy]));

    hptGenAA[iy] = new TH1D( Form("hptGenAA_iy%d",iy),"; p_{T} (GeV/c) ; ", nPtBins, ptBin);
    hptRecoAA[iy] = (TH1D*)hptGenAA[iy]->Clone(Form("hptRecoAA_iy%d",iy));
    hptGenPP[iy] = (TH1D*)hptGenAA[iy]->Clone(Form("hptGenPP_iy%d",iy));
    hptRecoPP[iy] = (TH1D*)hptGenAA[iy]->Clone(Form("hptRecoPP_iy%d",iy));
    
    genAA->Draw2( hptGenAA[iy], "pt", accCut && yCut, "weight" ) ;
    recoAA->Draw2( hptRecoAA[iy], "pt", accCut && yCut,"weight" ) ;
    genPP->Draw2( hptGenPP[iy], "pt", accCut && yCut ,"weight") ;
    recoPP->Draw2( hptRecoPP[iy], "pt", accCut && yCut,"weight") ;

    if ( doCent ) { 
      hcentGenAA[iy] = new TH1D( Form("hcentGenAA_iy%d",iy),"; centrality bin ; ", nCentBins, centBin);
      hcentRecoAA[iy] = (TH1D*)hcentGenAA[iy]->Clone(Form("hcentRecoAA_iy%d",iy));
      genAA->Draw2( hcentGenAA[iy], "cBin", accCut && yCut, "weight" ) ;
      recoAA->Draw2( hcentRecoAA[iy], "cBin", accCut && yCut,"weight" ) ;
      
      hcentGenPP[iy] = new TH1D( Form("hcentGenPP_iy%d",iy),"; centrality bin ; ", 1, 0, 200);
      hcentRecoPP[iy] = (TH1D*)hcentGenPP[iy]->Clone(Form("hcentRecoPP_iy%d",iy));
      genPP->Draw2( hcentGenPP[iy], "cBin+100", accCut && yCut, "weight" ) ;
      recoPP->Draw2( hcentRecoPP[iy], "cBin+100", accCut && yCut,"weight" ) ;
    }
  }

  TCanvas* c1 =  new TCanvas("c1","",600,600);
  c1->Divide(2,2);
  
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    c1->cd(iy);
    handsomeTH1(hptGenAA[iy],1);
    handsomeTH1(hptRecoAA[iy],2);
    cleverRange(hptGenAA[iy], 1.3, 0);
    hptGenAA[iy]->SetYTitle("dN/dp_{T}");
    hptGenAA[iy]->Draw("hist");
    hptRecoAA[iy]->Draw("same");
    drawText(Form("PbPb, %.1f < y < %.1f",float(yBin[iy-1]), float(yBin[iy])), 0.3, 0.8, 1, 15);
    
    c1->cd(iy+2);
    handsomeTH1(hptGenPP[iy],1);
    handsomeTH1(hptRecoPP[iy],2);
    cleverRange(hptGenPP[iy], 1.3, 0);
    hptGenPP[iy]->SetYTitle("dN/dp_{T}");
    hptGenPP[iy]->Draw("hist");
    hptRecoPP[iy]->Draw("same");
    drawText(Form("pp, %.1f < y < %.1f",float(yBin[iy-1]), float(yBin[iy])), 0.3, 0.8, 1, 15);
    
  }

  TCanvas* c2 =  new TCanvas("c2","",800,400);
  TH1D* hptEffAA[nYBins];
  TH1D* hptEffPP[nYBins];
  c2->Divide(2,1);
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    c2->cd(iy);
    hptEffAA[iy] = (TH1D*)hptRecoAA[iy]->Clone(Form("hptEffAA_iy%d",iy));
    hptEffAA[iy]->Divide(hptGenAA[iy]);
    hptEffAA[iy]->SetAxisRange(0,1.2,"Y");
    hptEffAA[iy]->SetYTitle("efficiency");
    hptEffAA[iy]->Draw();
    hptEffPP[iy] = (TH1D*)hptRecoPP[iy]->Clone(Form("hptEffPP_iy%d",iy));
    hptEffPP[iy]->Divide(hptGenPP[iy]);
    hptEffPP[iy]->SetAxisRange(0,1.2,"Y");
    hptEffPP[iy]->SetYTitle("efficiency");
    hptEffPP[iy]->SetMarkerStyle(24);
    hptEffPP[iy]->Draw("same");
    TLegend* leg2 = new TLegend(0.4046176,0.3500982,0.8492568,0.5304435,NULL,"brNDC");
    easyLeg(leg2,Form("%.1f < y < %.1f",float(yBin[iy-1]), float(yBin[iy])) );
    leg2->AddEntry(hptEffAA[iy], "PbPb");
    leg2->AddEntry(hptEffPP[iy], "pp");
    leg2->Draw();
    drawText("Accepted muon p_{T} > 4GeV/c",0.25,0.2,1,15); 
    jumSun(0,1,30,1);
  }
  
  
  
  TCanvas* c3;
  TH1D* hcentEffAA[nYBins+1];
  TH1D* hcentEffPP[nYBins+1];
  if ( doCent ) { 
    c3 =  new TCanvas("c3","",800,400);
    c3->Divide(2,1);
    for ( int iy=1 ; iy<=nYBins ; iy++) {
      c3->cd(iy);
      hcentEffAA[iy] = (TH1D*)hcentRecoAA[iy]->Clone(Form("hcentEffAA_iy%d",iy));
      hcentEffAA[iy]->Divide(hcentGenAA[iy]);
      hcentEffPP[iy] = (TH1D*)hcentRecoPP[iy]->Clone(Form("hcentEffPP_iy%d",iy));
      hcentEffPP[iy]->Divide(hcentGenPP[iy]);
      hcentEffAA[iy]->SetAxisRange(0,1.2,"Y");
      hcentEffAA[iy]->SetYTitle("efficiency");
      hcentEffAA[iy]->Draw();
      hcentEffPP[iy]->SetLineColor(2);
      hcentEffPP[iy]->Draw("same hist");
      drawText("Accepted muon p_{T} > 4GeV/c",0.25,0.2,1,15); 
      jumSun(0,1,200,1);
      
      if ( iy == 1)   {
	TLegend* leg2 = new TLegend(0.4046176,0.3500982,0.8492568,0.5304435,NULL,"brNDC");
	easyLeg(leg2,"Efficiency");
	leg2->AddEntry(hcentEffAA[iy], "PbPb");
	leg2->AddEntry(hcentEffPP[iy], "pp","l");
	leg2->Draw();
      }
    }    
  }
  
  
  
  
  
  TFile *fout = new TFile(Form("efficiency_ups%ds.root",state),"recreate");
  for ( int iy=1 ; iy<=nYBins ; iy++) {
    hptGenPP[iy]->Write();
    hptRecoPP[iy]->Write();
    hptEffPP[iy]->Write();
    hptGenAA[iy]->Write();
    hptRecoAA[iy]->Write();
    hptEffAA[iy]->Write();
    
    hcentEffPP[iy]->Write();
    hcentEffAA[iy]->Write();
  }
  fout->Close();


}

void setupMultiTreeTool( multiTreeUtil* mt, int UpsState, bool isGen) { 
  TString treeName = "mm";
  if ( isGen) treeName = "mmGen";

  if ( UpsState == kPPMCUps1S) {    
    //    mt->addFile("../skimmedFiles/yskimPP_MC_Ups1S_Trig-L1DoubleMu0_OpSign_EP-OppositeHF_20168121653_ce8f82aaf8e612dcd1c7c161216161d988fbf9a6.root",treeName,""); } // No pT weight
    mt->addFile("../skimmedFiles/yskimPP_MC_Ups1S_Trig-L1DoubleMu0_OpSign_EP-OppositeHF_20168142115_3c54df0419c4813e2d7256dc8952ac699405d027.root",treeName,""); }// pT weighted 
  else if ( UpsState == kPPMCUps2S) { 
    mt->addFile("../skimmedFiles/yskimPP_MC_Ups2S_Trig-L1DoubleMu0_OpSign_EP-OppositeHF_20168121655_ce8f82aaf8e612dcd1c7c161216161d988fbf9a6.root",treeName,"");  }
  else if ( UpsState == kPPMCUps3S) { 
    mt->addFile("../skimmedFiles/yskimPP_MC_Ups3S_Trig-L1DoubleMu0_OpSign_EP-OppositeHF_20168121658_ce8f82aaf8e612dcd1c7c161216161d988fbf9a6.root",treeName,"");  }
  
  else if ( UpsState == kAAMCUps1S) { 
    //    mt->addFile("../skimmedFiles/yskimAA_MC_Ups1S_Trig-L1DoubleMu0_OpSign_EP-OppositeHF_2016812170_ce8f82aaf8e612dcd1c7c161216161d988fbf9a6.root",treeName,""); // No pT weight
    mt->addFile("../skimmedFiles/yskimAA_MC_Ups1S_Trig-L1DoubleMu0_OpSign_EP-OppositeHF_20168142122_3c54df0419c4813e2d7256dc8952ac699405d027.root",treeName,"");  } // Weighted
    
  else if ( UpsState == kAAMCUps2S) { 
    mt->addFile("../skimmedFiles/yskimAA_MC_Ups2S_Trig-L1DoubleMu0_OpSign_EP-OppositeHF_2016812171_ce8f82aaf8e612dcd1c7c161216161d988fbf9a6.root",treeName,"");
  }
  else if ( UpsState == kAAMCUps3S) {
    mt->addFile("../skimmedFiles/yskimAA_MC_Ups3S_Trig-L1DoubleMu0_OpSign_EP-OppositeHF_2016812172_ce8f82aaf8e612dcd1c7c161216161d988fbf9a6.root",treeName,"");
  }
  
}


