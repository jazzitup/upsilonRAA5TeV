#include "SONGKYO.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"

void strickland_RAA_pt()
{
  setTDRStyle();
  writeExtraText = true;       // if extra text
  int iPeriod = 101; // 1: pp, 2: pPb, 3: PbPb, 100: RAA vs cent, 101: RAA vs pt or rap
  int iPos = 33;
  
  const int nState = 3; // Y(1S), Y(2S), and Y(3S)
  double xmax = 30.0;
//  double relsys = 0.1;

  double exsys_1s[5] =  {1.25, 1.25, 1.5, 3.5, 7.5};
  double exsys_2s[3] =  {2.5, 5., 7.5};
  double exsys_3s[3] =  {2.5, 5., 7.5};

  ////////////////////////////////////////////////////////////////
  //// read input file : value & stat.
  TFile* fIn[nState];
	TGraphErrors* gRAA[nState];
	TGraphErrors* gRAA_sys[nState];
  for (int is=0; is<nState; is++){
  	fIn[is] = new TFile(Form("Ups_%d_RAA.root",is+1),"READ");
    gRAA[is]=(TGraphErrors*)fIn[is]->Get("gRAA_pt");
    gRAA_sys[is]=(TGraphErrors*)fIn[is]->Get("gRAA_pt");
    //cout << "gRAA["<<is<<"] = " <<gRAA[is] << endl;
  }
  //// read input file : syst.
  TFile* fInSys[nState];
  TH1D* hSys[nState];
  int npoint[nState];
  for (int is=0; is<nState; is++){
  	fInSys[is] = new TFile(Form("../Systematic/mergedSys_ups%ds.root",is+1),"READ");
    hSys[is]=(TH1D*)fInSys[is]->Get("hptRAA_merged");
    npoint[is] = hSys[is]->GetSize()-2;
    cout << "*** Y("<<is+1<<") : # of point = " << npoint[is] << endl;
  } 
  
  //// set bin width and calculate systematic uncertainties
  double pxtmp, pytmp, extmp, eytmp;
  double relsys;

  for (int is=0; is<nState; is++){
    cout << is+1 <<"th state***************" << endl;
    if (npoint[is] != gRAA[is]->GetN()) {cout << "Error!! data file and syst. file have different binnig!" << endl; return; }
    for (int ipt=0; ipt< npoint[is] ; ipt++) { //bin by bin
      pxtmp=0; pytmp=0; extmp=0; eytmp=0; relsys=0;
      gRAA[is]->GetPoint(ipt, pxtmp, pytmp);
      extmp=gRAA[is]->GetErrorX(ipt);
      eytmp=gRAA[is]->GetErrorY(ipt);
      relsys=hSys[is]->GetBinContent(ipt+1);
      cout << ipt <<"th bin RAA value = " << pytmp << endl;
      cout << ipt <<"th bin stat. = " << eytmp << endl;
      //cout << ipt <<"th bin rel. syst. = " << relsys << endl;
      cout << ipt <<"th bin syst. = " << pytmp*relsys << endl; 
      //// 1) remove ex from gRAA
      gRAA[is]->SetPointError(ipt, 0, eytmp);
      //// 2) set ey for gRAA_sys
      //gRAA_sys[is]->SetPointError(ipt, extmp, pytmp*relsys);
      if (is==0) gRAA_sys[is]->SetPointError(ipt, exsys_1s[ipt], pytmp*relsys);
      else if (is==1) gRAA_sys[is]->SetPointError(ipt, exsys_2s[ipt], pytmp*relsys);
      else gRAA_sys[is]->SetPointError(ipt, exsys_3s[ipt], pytmp*relsys);
    }
  }
 
  ////////////////////////////////////////////////////////////////

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
  
  //// legend
  TLegend *leg= new TLegend(0.75, 0.50, 0.95, 0.70);
  SetLegendStyle(leg);
  for (int is=0; is<nState; is++){
    leg -> AddEntry(gRAA[is],Form("#Upsilon(%dS)",is+1),"lp");
  }

  //// axis et. al
  gRAA_sys[0]->GetXaxis()->SetTitle("p_{T}^{#mu#mu} (GeV/c)");
  gRAA_sys[0]->GetXaxis()->CenterTitle();
  gRAA_sys[0]->GetYaxis()->SetTitle("R_{AA}");
  gRAA_sys[0]->GetYaxis()->CenterTitle();
  gRAA_sys[0]->GetXaxis()->SetLimits(0.,xmax);
  gRAA_sys[0]->SetMinimum(0.0);
  gRAA_sys[0]->SetMaximum(1.3);
 
  //// draw  
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  for (int is=0; is<nState; is++){
    if ( is==0) gRAA_sys[is]->Draw("A5");
    else gRAA_sys[is]->Draw("5");
    gRAA[is]->Draw("P");
	}
  dashedLine(0.,1.,xmax,1.,1,1);
  leg->Draw();

  //// draw text
  double sz_init = 0.895; double sz_step = 0.0525;
  globtex->DrawLatex(0.22, sz_init, "p_{T}^{#mu} > 4 GeV/c");
//  globtex->DrawLatex(0.22, sz_init, "p_{T}^{#mu#mu} < 30 GeV/c");
  globtex->DrawLatex(0.22, sz_init-sz_step, "|y|^{#mu#mu} < 2.4");
  globtex->DrawLatex(0.22, sz_init-sz_step*2, "Centrality 0-100%");

  TFile *fstrickland = new TFile("TheoryCurve/StrickLand_RAA.root","READ");
  
  TGraphErrors *gRAA_1S_strickland[3]; 
  TGraphErrors *gRAA_2S_strickland[3]; 
  
  for(int i=0;i<3;i++)
  {
    gRAA_1S_strickland[i] = (TGraphErrors*) fstrickland-> Get(Form("RAA_strick_pt_1S_%d",i));
    gRAA_2S_strickland[i] = (TGraphErrors*) fstrickland-> Get(Form("RAA_strick_pt_2S_%d",i));
    gRAA_1S_strickland[i] -> SetLineWidth(2.5);
    gRAA_2S_strickland[i] -> SetLineWidth(3.0);
  }
  gRAA_1S_strickland[0]->SetLineColor(kOrange+9);
  gRAA_1S_strickland[1]->SetLineColor(kBlack);
  gRAA_1S_strickland[2]->SetLineColor(kBlue+1);
  
  gRAA_2S_strickland[0]->SetLineColor(kOrange+9);
  gRAA_2S_strickland[1]->SetLineColor(kBlack);
  gRAA_2S_strickland[2]->SetLineColor(kBlue+1);

  gRAA_2S_strickland[0]->SetLineStyle(2);
  gRAA_2S_strickland[1]->SetLineStyle(2);
  gRAA_2S_strickland[2]->SetLineStyle(2);

  for(int i=0;i<3;i++){
    gRAA_1S_strickland[i]->Draw("same");
    gRAA_2S_strickland[i]->Draw("same");
  }
   
  TLegend *leg_strick= new TLegend(0.4, 0.50, 0.6, 0.70);
  SetLegendStyle(leg_strick);
  leg_strick->AddEntry(gRAA_1S_strickland[0],"4#pi#eta/s=1","l");
  leg_strick->AddEntry(gRAA_1S_strickland[1],"4#pi#eta/s=2","l");
  leg_strick->AddEntry(gRAA_1S_strickland[2],"4#pi#eta/s=3","l");

  leg_strick->Draw("same");

  //Global Unc.
  double sys_global_val = lumi_unc_pp;
  //double sys_global_val = TMath::Sqrt(lumi_unc_pp*lumi_unc_pp+lumi_unc_aa*lumi_unc_aa);
  double sys_global_y = sys_global_val/2;
  double sys_global_x = 0.8;
  TBox *globalUncBox = new TBox(xmax-sys_global_x,1-sys_global_y,xmax,1+sys_global_y);
  globalUncBox -> SetLineColor(kBlack);
  globalUncBox -> SetFillColorAlpha(kGray+2,0.6);
  globalUncBox -> SetLineWidth(1);
  globalUncBox -> Draw("l same");

  CMS_lumi( c1, iPeriod, iPos );

	c1->Update();
  c1->SaveAs("Strickland_RAA_vs_pt.pdf");
  c1->SaveAs("Strickland_RAA_vs_pt.png");

/*
	///////////////////////////////////////////////////////////////////
	//// save as a root file
	TFile *outFile = new TFile("RAA_vs_pt.root", "RECREATE");
	outFile->cd();
	for (int is=0; is<nState; is++){
		gRAA_sys[is]->Write();	
		gRAA[is]->Write();	
	}
	outFile->Close();
*/	
	return;

} // end of main func.

