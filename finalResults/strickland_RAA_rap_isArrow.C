#include "SONGKYO.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "../cutsAndBin.h"

void strickland_RAA_rap_isArrow(bool isArrow=true)
{
  setTDRStyle();
  writeExtraText = true;       // if extra text
  int iPeriod = 101; // 1: pp, 2: pPb, 3: PbPb, 100: RAA vs cent, 101: RAA vs pt or rap
  int iPos = 33;
  
  const int nState = 3; // Y(1S), Y(2S), and Y(3S)
  double xmax = 2.4;
//  double relsys = 0.1;

  double exsys_1s[6] =  {0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
  double exsys_2s[3] =  {0.4, 0.4,0.4};
  double exsys_3s[2] =  {0.6, 0.6};

  ////////////////////////////////////////////////////////////////
  //// read input file : value & stat.
  TFile* fIn[nState];
	TGraphErrors* gRAA[nState];
	TGraphErrors* gRAA_sys[nState];
  for (int is=0; is<nState; is++){
  	fIn[is] = new TFile(Form("Ups_%d_RAA.root",is+1),"READ");
    gRAA[is]=(TGraphErrors*)fIn[is]->Get("gRAA_rap");
    gRAA_sys[is]=(TGraphErrors*)fIn[is]->Get("gRAA_rap");
    //cout << "gRAA["<<is<<"] = " <<gRAA[is] << endl;
  }
  //// read input file : syst.
  TFile* fInSys[nState];
  TH1D* hSys[nState];
  int npoint[nState];
  for (int is=0; is<nState; is++){
  	fInSys[is] = new TFile(Form("../Systematic/mergedSys_ups%ds.root",is+1),"READ");
    hSys[is]=(TH1D*)fInSys[is]->Get("hrapRAA_merged");
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
  int ulstate = 2; //3S
  static const int n3s = 2;
  double boxw = 0.05; // for syst. box (vs cent)
  double lower68[n3s] = {0.,0.};
  double upper68[n3s] = {0.050402958,0.060631106};
  double lower95[n3s] = {0., 0.};
  double upper95[n3s] = {0.088932491,0.108333619};
  if (n3s != npoint[ulstate]) {cout<<"ERROR!! # of bins for UL is wrong!!"<<endl;return;} 

  //// --- vs centrality
  TBox *box68per[n3s];
  TArrow *arr95per[n3s];
  for (int ipt=0; ipt< n3s ; ipt++) { //bin by bin
    pxtmp=0; pytmp=0; extmp=0; eytmp=0; 
    //lower68=0; upper68=0; lower95=0; upper95=0; 
    gRAA[ulstate]->GetPoint(ipt, pxtmp, pytmp);
    box68per[ipt] = new TBox(pxtmp-boxw,lower68[ipt],pxtmp+boxw,upper68[ipt]);
    arr95per[ipt] = new TArrow(pxtmp,lower95[ipt],pxtmp,upper95[ipt],0.027,"<-|"); //95%
    box68per[ipt]->SetLineColor(kGreen+2);
    box68per[ipt]->SetFillColorAlpha(kGreen-10,0.5);
    box68per[ipt]->SetLineWidth(1);
    arr95per[ipt]->SetLineColor(kGreen+2);
    arr95per[ipt]->SetLineWidth(2);
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
  
  //// axis et. al
  gRAA_sys[0]->GetXaxis()->SetTitle("|y^{#mu#mu}|");
  gRAA_sys[0]->GetXaxis()->CenterTitle();
  gRAA_sys[0]->GetYaxis()->SetTitle("R_{AA}");
  gRAA_sys[0]->GetYaxis()->CenterTitle();
  gRAA_sys[0]->GetXaxis()->SetLimits(0.,xmax);
  gRAA_sys[0]->SetMinimum(0.0);
  gRAA_sys[0]->SetMaximum(1.3);
  /// for rap
  gRAA_sys[0]->GetXaxis()->SetNdivisions(505);
 
  //// draw  
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  //// syst
  for (int is=0; is<nState; is++){
    if ( is==0) { gRAA_sys[is]->Draw("A5"); }
    else if (is==ulstate && isArrow==true) { 
      for (int ipt=0; ipt< n3s ; ipt++) { //bin by bin
        box68per[ipt]->Draw("l"); 
      }
    }
    else { gRAA_sys[is]->Draw("5"); }
	}
  //// point
  for (int is=0; is<nState; is++){
    if (is==ulstate && isArrow==true) {
      for (int ipt=0; ipt< n3s ; ipt++) { //bin by bin
        arr95per[ipt]->Draw();
      }
    }
    else { gRAA[is]->Draw("P"); }
	}
  dashedLine(0.,1.,xmax,1.,1,1);
  
  //// legend
  TLegend *leg= new TLegend(0.65, 0.45, 0.85, 0.70);
  SetLegendStyle(leg);
  TArrow *arrLeg = new TArrow(1.52,0.51,1.52,0.58,0.023,"<-|");
  arrLeg->SetLineColor(kGreen+2);
  arrLeg->SetLineWidth(2);
  
  if (isArrow==false) { 
    for (int is=0; is<nState; is++){
      leg -> AddEntry(gRAA[is],Form(" #Upsilon(%dS)",is+1),"lp");
      leg->Draw();
    }
  }
  else {
    leg -> AddEntry(gRAA[0]," #Upsilon(1S)","lp");
    leg -> AddEntry(gRAA[1]," #Upsilon(2S)","lp");
    TLegendEntry *ent=leg->AddEntry("ent"," #Upsilon(3S) 68\% CL","f");
    ent->SetLineColor(kGreen+2);
    ent->SetFillColorAlpha(kGreen-10,0.5);
    ent->SetFillStyle(1001);
    ent=leg->AddEntry("ent"," #Upsilon(3S) 95\% CL","f");
    ent->SetLineColor(kWhite);
    leg->Draw("same");
    arrLeg->Draw();
  }


  //// draw text
  double sz_init = 0.895; double sz_step = 0.0525;
  globtex->DrawLatex(0.22, sz_init, "p_{T}^{#mu} > 4 GeV/c");
  globtex->DrawLatex(0.22, sz_init-sz_step, "p_{T}^{#mu#mu} < 30 GeV/c");
//  globtex->DrawLatex(0.22, sz_init-sz_step, "|y|^{#mu#mu} < 2.4");
  globtex->DrawLatex(0.22, sz_init-sz_step*2, "Centrality 0-100%");
  
  TFile *fstrickland = new TFile("TheoryCurve/StrickLand_RAA.root","READ");
  
  TGraphErrors *gRAA_1S_strickland[3]; 
  TGraphErrors *gRAA_2S_strickland[3]; 
  
  for(int i=0;i<3;i++)
  {
    gRAA_1S_strickland[i] = (TGraphErrors*) fstrickland-> Get(Form("RAA_strick_rap_1S_%d",i));
    gRAA_2S_strickland[i] = (TGraphErrors*) fstrickland-> Get(Form("RAA_strick_rap_2S_%d",i));
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
  double sys_global_val = TMath::Sqrt(lumi_unc_pp*lumi_unc_pp+0.089*0.089+nMB_unc*nMB_unc);
  //double sys_global_val = TMath::Sqrt(lumi_unc_pp*lumi_unc_pp+lumi_unc_aa*lumi_unc_aa);
  double sys_global_y = sys_global_val;
  double sys_global_x = 0.06;
  TBox *globalUncBox = new TBox(xmax-sys_global_x,1-sys_global_y,xmax,1+sys_global_y);
  globalUncBox -> SetLineColor(kBlack);
  globalUncBox -> SetFillColorAlpha(kGray+2,0.6);
  globalUncBox -> SetLineWidth(1);
  globalUncBox -> Draw("l same");
  
  CMS_lumi( c1, iPeriod, iPos );

	c1->Update();
  c1->SaveAs(Form("Strickland_RAA_vs_rap_isArrow%d.pdf",(int)isArrow));
  c1->SaveAs(Form("Strickland_RAA_vs_rap_isArrow%d.png",(int)isArrow));

/*
	///////////////////////////////////////////////////////////////////
	//// save as a root file
	TFile *outFile = new TFile("RAA_vs_rap.root", "RECREATE");
	outFile->cd();
	for (int is=0; is<nState; is++){
		gRAA_sys[is]->Write();	
		gRAA[is]->Write();	
	}
	outFile->Close();
*/	
	return;

} // end of main func.

