#include "SONGKYO.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"

void draw_RAA_cent_noint()
{
  setTDRStyle();
  writeExtraText = true;       // if extra text
  int iPeriod = 100; // 1: pp, 2: pPb, 3: PbPb, 100: RAA vs cent, 101: RAA vs pt or rap
  int iPos = 33;
  
  const int nState = 3; // Y(1S), Y(2S), and Y(3S)
  double xmax = 420.0;
  double boxw = 6.5; // for syst. box (vs cent only)
  double relsys = 0.1;

  //// read the inut file and TGraph
  TFile* fIn[nState];
	TGraphErrors* gRAA[nState];
  for (int is=0; is<nState; is++){
  	fIn[is] = new TFile(Form("Ups_%d_RAA.root",is+1),"READ");
    gRAA[is]=(TGraphErrors*)fIn[is]->Get("gRAA_cent");
    //cout << "gRAA["<<is<<"] = " <<gRAA[is] << endl;
  }
  
  //// systematic uncertainties (temp)
	TGraphErrors* gRAA_sys[nState];
  int npoint[nState];
  double pxtmp, pytmp, extmp, eytmp;
  for (int is=0; is<nState; is++){
    gRAA_sys[is]=(TGraphErrors*)fIn[is]->Get("gRAA_cent");
    npoint[is] = gRAA_sys[is]->GetN();
    //cout << "*** Y("<<is+1<<") : # of point = " << npoint[is] << endl;
    for (int ipt=0; ipt< npoint[is] ; ipt++) {
      pxtmp=0; pytmp=0; extmp=0; eytmp=0;
      gRAA_sys[is]->GetPoint(ipt, pxtmp, pytmp);
      extmp=gRAA_sys[is]->GetErrorX(ipt);
      eytmp=gRAA_sys[is]->GetErrorY(ipt);
      // 1) remove ex from gRAA
      gRAA[is]->SetPointError(ipt, 0, eytmp);
      // 2) set ey for gRAA_sys (assign 10% temporarily)
      //gRAA_sys[is]->SetPointError(ipt, extmp, pytmp*relsys);
      gRAA_sys[is]->SetPointError(ipt, boxw, pytmp*relsys); //extemp fixed
    }
  }
  
  //// graph style 
  for (int is=0; is<nState; is++){
    SetGraphStyle(gRAA[is], is, is); 
    SetGraphStyleSys(gRAA_sys[is], is); 
	}
  
  //// latex for text
  TLatex* globtex = new TLatex();
  globtex->SetNDC();
  globtex->SetTextAlign(12); //left-center
  globtex->SetTextFont(42);
  globtex->SetTextSize(0.038);
  
  // legend
  TLegend *leg= new TLegend(0.75, 0.50, 0.95, 0.70);
  SetLegendStyle(leg);
  for (int is=0; is<nState; is++){
    leg -> AddEntry(gRAA[is],Form("#Upsilon(%dS)",is+1),"lp");
  }

  //// draw  
  gRAA_sys[0]->GetXaxis()->SetTitle("N_{part}");
  gRAA_sys[0]->GetXaxis()->CenterTitle();
  gRAA_sys[0]->GetYaxis()->SetTitle("R_{AA}");
  gRAA_sys[0]->GetYaxis()->CenterTitle();
  gRAA_sys[0]->GetXaxis()->SetLimits(0.,xmax);
  gRAA_sys[0]->SetMinimum(0.0);
  gRAA_sys[0]->SetMaximum(1.3);
  //// for cent
  gRAA_sys[0]->GetXaxis()->SetTitleSize(0.06*1.0);
  gRAA_sys[0]->GetYaxis()->SetTitleSize(0.06*1.0);
  gRAA_sys[0]->GetXaxis()->SetLabelSize(0.05*1.0);
  gRAA_sys[0]->GetYaxis()->SetLabelSize(0.05*1.0);
  
 
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  for (int is=0; is<nState; is++){
    if ( is==0) gRAA_sys[is]->Draw("A5");
    else gRAA_sys[is]->Draw("5");
    gRAA[is]->Draw("P");
	}
  dashedLine(0.,1.,xmax,1.,1,1);
  leg->Draw();

  //// Text
  double sz_init = 0.895; double sz_step = 0.0525;
  globtex->DrawLatex(0.22+0.04, sz_init, "p_{T}^{#mu} > 4 GeV/c");
  globtex->DrawLatex(0.22+0.04, sz_init-sz_step, "p_{T}^{#mu#mu} < 30 GeV/c");
  globtex->DrawLatex(0.22+0.04, sz_init-sz_step*2, "|y|^{#mu#mu} < 2.4");
//  globtex->DrawLatex(0.22, sz_init-sz_step*2, "Centrality 0-100%");
  
  CMS_lumi( c1, iPeriod, iPos );

	c1->Update();
  c1->SaveAs("RAA_vs_cent_noint.pdf");
  c1->SaveAs("RAA_vs_cent_noint.png");

/*
	///////////////////////////////////////////////////////////////////
	//// save as a root file
	TFile *outFile = new TFile("RAA_vs_cent_noint.root", "RECREATE");
	outFile->cd();
	for (int is=0; is<nState; is++){
		gRAA_sys[is]->Write();	
		gRAA[is]->Write();	
	}
	outFile->Close();
*/	
	return;

} // end of main func.

