#include <iostream>
#include "TROOT.h"
#include "TSystem.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
  const int N_nPart = 407;
  const int N_pT1S = 5;
  const int N_pT2S = 3;
  const int N_rap = 35;

  Double_t nPart, rap, pT;
  Double_t RAA_etas_nPart[3];
  Double_t RAA_etas_pT[3];
  Double_t RAA_etas_rap[3];
  int sNN = 2760;
 
  fstream openFile_nPart1S(Form("Y1SNpart%dXi0.tsv",sNN));
  fstream openFile_nPart2S(Form("Y2SNpart%dXi0.tsv",sNN));
  
  fstream openFile_pT1S(Form("Y1Spt%dXi0.tsv",sNN));
  fstream openFile_pT2S(Form("Y2Spt%dXi0.tsv",sNN));
  
  fstream openFile_rap1S(Form("Y1Srapidity%dXi0.tsv",sNN));
  fstream openFile_rap2S(Form("Y2Srapidity%dXi0.tsv",sNN));

  TFile *wfile_nPart1S = new TFile(Form("1SXi0_RAA_%d_nPart.root",sNN),"recreate");
  TTree *tree_nPart1S = new TTree("tree","1S Xi0 tree");
         tree_nPart1S -> Branch("nPart",&nPart,"nPart/D");
         tree_nPart1S -> Branch("RAA_etas_nPart",&RAA_etas_nPart,"RAA_etas_nPart[3]/D");
  
  TFile *wfile_nPart2S = new TFile(Form("2SXi0_RAA_%d_nPart.root",sNN),"recreate");
  TTree *tree_nPart2S = new TTree("tree","2S Xi0 tree");
         tree_nPart2S -> Branch("nPart",&nPart,"nPart/D");
         tree_nPart2S -> Branch("RAA_etas_nPart",&RAA_etas_nPart,"RAA_etas_nPart[3]/D");
  
  TFile *wfile_pT1S = new TFile(Form("1SXi0_RAA_%d_pT.root",sNN),"recreate");
  TTree *tree_pT1S = new TTree("tree","1S Xi0 tree");
         tree_pT1S -> Branch("pT",&pT,"pT/D");
         tree_pT1S -> Branch("RAA_etas_pT",&RAA_etas_pT,"RAA_etas_pT[3]/D");
  
  TFile *wfile_pT2S = new TFile(Form("2SXi0_RAA_%d_pT.root",sNN),"recreate");
  TTree *tree_pT2S = new TTree("tree","2S Xi0 tree");
         tree_pT2S -> Branch("pT",&pT,"pT/D");
         tree_pT2S -> Branch("RAA_etas_pT",&RAA_etas_pT,"RAA_etas_pT[3]/D");
  
  TFile *wfile_rap1S = new TFile(Form("1SXi0_RAA_%d_rap.root",sNN),"recreate");
  TTree *tree_rap1S = new TTree("tree","1S Xi0 tree");
         tree_rap1S -> Branch("rap",&rap,"rap/D");
         tree_rap1S -> Branch("RAA_etas_rap",&RAA_etas_rap,"RAA_etas_rap[3]/D");
  
  TFile *wfile_rap2S = new TFile(Form("2SXi0_RAA_%d_rap.root",sNN),"recreate");
  TTree *tree_rap2S = new TTree("tree","2S Xi0 tree");
         tree_rap2S -> Branch("rap",&rap,"rap/D");
         tree_rap2S -> Branch("RAA_etas_rap",&RAA_etas_rap,"RAA_etas_rap[3]/D");
  

  for(int i=0; i<N_nPart; i++)
  {
    openFile_nPart1S >> nPart >> RAA_etas_nPart[0] >> RAA_etas_nPart[1] >> RAA_etas_nPart[2];
    tree_nPart1S->Fill();
  }
  
  openFile_nPart1S.close();
  wfile_nPart1S->cd();
  tree_nPart1S->Write();
  wfile_nPart1S->Close();

  nPart = 0;
  RAA_etas_nPart[0]=0.;
  RAA_etas_nPart[1]=0.;
  RAA_etas_nPart[2]=0.;


  for(int i=0; i<N_nPart; i++)
  {
    openFile_nPart2S >> nPart >> RAA_etas_nPart[0] >> RAA_etas_nPart[1] >> RAA_etas_nPart[2];
    tree_nPart2S->Fill();
  }
  
  openFile_nPart2S.close();
  wfile_nPart2S->cd();
  tree_nPart2S->Write();
  wfile_nPart2S->Close();


  for(int i=0; i<N_pT1S; i++)
  {
    openFile_pT1S >> pT >> RAA_etas_pT[0] >> RAA_etas_pT[1] >> RAA_etas_pT[2];
    tree_pT1S->Fill();
  }
  
  openFile_pT1S.close();
  wfile_pT1S->cd();
  tree_pT1S->Write();
  wfile_pT1S->Close();

  pT = 0;
  RAA_etas_pT[0]=0.;
  RAA_etas_pT[1]=0.;
  RAA_etas_pT[2]=0.;

  for(int i=0; i<N_pT2S; i++)
  {
    openFile_pT2S >> pT >> RAA_etas_pT[0] >> RAA_etas_pT[1] >> RAA_etas_pT[2];
    tree_pT2S->Fill();
  }
  
  openFile_pT2S.close();
  wfile_pT2S->cd();
  tree_pT2S->Write();
  wfile_pT2S->Close();
  
  pT = 0;
  RAA_etas_pT[0]=0.;
  RAA_etas_pT[1]=0.;
  RAA_etas_pT[2]=0.;


  for(int i=0; i<N_rap; i++)
  {
    openFile_rap1S >> rap >> RAA_etas_rap[0] >> RAA_etas_rap[1] >> RAA_etas_rap[2];
    tree_rap1S->Fill();
  }

  openFile_rap1S.close();
  wfile_rap1S->cd();
  tree_rap1S->Write();
  wfile_rap1S->Close();

  rap = 0;
  RAA_etas_rap[0]= 0.;
  RAA_etas_rap[1]= 0.;
  RAA_etas_rap[2]= 0.;

  for(int i=0; i<N_rap; i++)
  {
    openFile_rap2S >> rap >> RAA_etas_rap[0] >> RAA_etas_rap[1] >> RAA_etas_rap[2];
    tree_rap2S->Fill();
  }

  openFile_rap2S.close();
  wfile_rap2S->cd();
  tree_rap2S->Write();
  wfile_rap2S->Close();

  rap = 0;
  RAA_etas_rap[0]= 0.;
  RAA_etas_rap[1]= 0.;
  RAA_etas_rap[2]= 0.;



  /*delete wfile_nPart1S;
  delete wfile_nPart2S;
  delete wfile_pT1S;
  delete wfile_pT2S;
  delete wfile_rap1S;
  delete wfile_rap2S;
  delete tree_nPart1S;
  delete tree_nPart2S;
  delete tree_pT1S;
  delete tree_pT2S;
  delete tree_rap1S;
  delete tree_rap2S;
*/
  return 0;
}
   
