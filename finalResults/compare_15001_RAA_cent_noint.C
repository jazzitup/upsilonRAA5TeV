#include "SONGKYO.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"

void compare_15001_RAA_cent_noint(int istate=1) //1 or 2 (1S or 2S)
{
  setTDRStyle();
  writeExtraText = true;       // if extra text
  int iPeriod = 100; // 1: pp, 2: pPb, 3: PbPb, 100: RAA vs cent, 101: RAA vs pt or rap
  int iPos = 33;
  
  const int nfile = 2; // 0: 15001, 1: ours
  double xmax = 420;
  double boxw = 6.5; // for syst. box (vs cent only)
//  double relsys = 0.1;
  
  //// 15001 values
  const int cn_1s =  8;
  double cpx_1s[cn_1s] =  {8.8, 42.0, 86.3, 130, 187, 261, 329, 381};
  double cpy_1s[cn_1s] =  {1.22, 0.813, 0.604, 0.546, 0.476, 0.442, 0.408, 0.330};
  double cex_1s[cn_1s] =  {0., 0., 0., 0., 0., 0., 0., 0.};
  double cey_1s[cn_1s] =  {0.22, 0.082, 0.065, 0.047, 0.035, 0.027, 0.033, 0.029};
  double cexsys_1s[cn_1s] =  {boxw, boxw, boxw, boxw, boxw, boxw, boxw, boxw};
  double ceysys_1s_1[cn_1s] =  {0.32, 0.134, 0.119, 0.084, 0.056, 0.055, 0.057, 0.052};
  double ceysys_1s_2[cn_1s] =  {0.077, 0.051, 0.038, 0.034, 0.030, 0.028, 0.025, 0.021};
  double ceysys_1s[cn_1s];
  for (int it=0; it < cn_1s ; it++) {
    ceysys_1s[it] = TMath::Sqrt(ceysys_1s_1[it]*ceysys_1s_1[it]+ceysys_1s_2[it]*ceysys_1s_2[it]);
  }

  const int cn_2s =  4;
  double cpx_2s[cn_2s] =  {22.1, 108, 224, 355};
  double cpy_2s[cn_2s] =  {0.226, 0.294, 0.091, 0.076};
  double cex_2s[cn_2s] =  {0., 0., 0., 0.};
  double cey_2s[cn_2s] =  {0.149, 0.079, 0.043, 0.044};
  double cexsys_2s[cn_2s] =  {boxw, boxw, boxw, boxw};
  double ceysys_2s_1[cn_2s] =  {0.106, 0.081, 0.052, 0.035};
  double ceysys_2s_2[cn_2s] =  {0.015, 0.019, 0.006, 0.005};
  double ceysys_2s[cn_2s];
  for (int it=0; it < cn_2s ; it++) {
    ceysys_2s[it] = TMath::Sqrt(ceysys_2s_1[it]*ceysys_2s_1[it]+ceysys_2s_2[it]*ceysys_2s_2[it]);
  }

  ////////////////////////////////////////////////////////////////
  //// read input file : value & stat.
	TGraphErrors* gRAA[nfile];
	TGraphErrors* gRAA_sys[nfile];
  //// 1) 15001
  if (istate==1) {
    gRAA[0] = new TGraphErrors(cn_1s, cpx_1s, cpy_1s, cex_1s, cey_1s); 
    gRAA_sys[0] = new TGraphErrors(cn_1s, cpx_1s, cpy_1s, cexsys_1s, ceysys_1s); 
  } 
  else {
    gRAA[0] = new TGraphErrors(cn_2s, cpx_2s, cpy_2s, cex_2s, cey_2s); 
    gRAA_sys[0] = new TGraphErrors(cn_2s, cpx_2s, cpy_2s, cexsys_2s, ceysys_2s); 
  } 
  //// 2) ours
  TFile* fIn = new TFile(Form("Ups_%d_RAA.root",istate),"READ");
  gRAA[1]=(TGraphErrors*)fIn->Get("gRAA_cent");
  gRAA_sys[1]=(TGraphErrors*)fIn->Get("gRAA_cent");
  //// read input file : syst.
  TFile* fInSys = new TFile(Form("../Systematic/mergedSys_ups%ds.root",istate),"READ");
  TH1D* hSys = (TH1D*)fInSys->Get("hcentRAA_merged");
  int npoint = hSys->GetSize()-2;
  cout << "*** Y("<<istate<<") : # of point = " << npoint << endl; 

  //// set bin width and calculate systematic uncertainties 
  double pxtmp, pytmp, extmp, eytmp;
  double relsys;
  if (npoint != gRAA[1]->GetN()) {cout << "Error!! data file and syst. file have different binnig!" << endl; return; }
  for (int ipt=0; ipt< npoint; ipt++) {
    pxtmp=0; pytmp=0; extmp=0; eytmp=0; relsys=0;
    gRAA[1]->GetPoint(ipt, pxtmp, pytmp);
    extmp=gRAA[1]->GetErrorX(ipt);
    eytmp=gRAA[1]->GetErrorY(ipt);
    relsys=hSys->GetBinContent(ipt+1);
    // 1) remove ex from gRAA
    gRAA[1]->SetPointError(ipt, 0, eytmp);
    // 2) set ey for gRAA_sys
    //if (istate==1) gRAA_sys[1]->SetPointError(ipt, exsys_1s[ipt], pytmp*relsys);
    //else gRAA_sys[1]->SetPointError(ipt, exsys_2s[ipt], pytmp*relsys);
    if (istate==1) gRAA_sys[1]->SetPointError(ipt, boxw, pytmp*relsys);
    else gRAA_sys[1]->SetPointError(ipt, boxw, pytmp*relsys);
  }
  
  ////////////////////////////////////////////////////////////////
  
  //// graph style 
  SetGraphStyle(gRAA[0], 4, 4); 
  SetGraphStyleSys(gRAA_sys[0], 4); 
  SetGraphStyle(gRAA[1], 0, 0); 
  SetGraphStyleSys(gRAA_sys[1], 0); 
  
  //// latex for text
  TLatex* globtex = new TLatex();
  globtex->SetNDC();
  globtex->SetTextAlign(12); //left-center
  globtex->SetTextFont(42);
  globtex->SetTextSize(0.038);
  
  //// legend
  TLegend *leg= new TLegend(0.55, 0.46, 0.95, 0.63);
  SetLegendStyle(leg);
  leg -> SetHeader(Form("#Upsilon(%dS)",istate));
  leg -> AddEntry(gRAA[0],"#surd s_{NN} = 2.76 TeV","lp");
  leg -> AddEntry(gRAA[1],"#surd s_{NN} = 5.02 TeV","lp");

  //// axis et. al
  gRAA_sys[0]->GetXaxis()->SetTitle("N_{part}");
  gRAA_sys[0]->GetXaxis()->CenterTitle();
  gRAA_sys[0]->GetYaxis()->SetTitle("R_{AA}");
  gRAA_sys[0]->GetYaxis()->CenterTitle();
  gRAA_sys[0]->GetXaxis()->SetLimits(0.,xmax);
  gRAA_sys[0]->SetMinimum(0.0);
//  gRAA_sys[0]->SetMaximum(1.3);
  gRAA_sys[0]->SetMaximum(1.6);
  //// for cent
  gRAA_sys[0]->GetXaxis()->SetTitleSize(0.06*1.0);
  gRAA_sys[0]->GetYaxis()->SetTitleSize(0.06*1.0);
  gRAA_sys[0]->GetXaxis()->SetLabelSize(0.05*1.0);
  gRAA_sys[0]->GetYaxis()->SetLabelSize(0.05*1.0);
 
  //// draw  
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  for (int is=0; is<nfile; is++){
    if ( is==0) gRAA_sys[is]->Draw("A5");
    else gRAA_sys[is]->Draw("5");
    gRAA[is]->Draw("P");
	}
  dashedLine(0.,1.,xmax,1.,1,1);
  leg->Draw();

  //// draw text
  double sz_init = 0.895; double sz_step = 0.0525;
//  globtex->DrawLatex(0.22, sz_init, "p_{T}^{#mu} > 4 GeV/c");
  globtex->DrawLatex(0.22, sz_init-sz_step, "p_{T}^{#mu#mu} < 30 GeV/c");
  globtex->DrawLatex(0.22, sz_init-sz_step*2, "|y|^{#mu#mu} < 2.4");
//  globtex->DrawLatex(0.22, sz_init-sz_step*2, "Centrality 0-100%");
  
  CMS_lumi( c1, iPeriod, iPos );

	c1->Update();
  c1->SaveAs(Form("%dS_comp15001_RAA_vs_cent_noint.pdf",istate));
  c1->SaveAs(Form("%dS_comp15001_RAA_vs_cent_noint.png",istate));

/*
	///////////////////////////////////////////////////////////////////
	//// save as a root file
	TFile *outFile = new TFile("RAA_vs_cent_noint.root", "RECREATE");
	outFile->cd();
	for (int is=0; is<nfile; is++){
		gRAA_sys[is]->Write();	
		gRAA[is]->Write();	
	}
	outFile->Close();
*/	
	return;

} // end of main func.

