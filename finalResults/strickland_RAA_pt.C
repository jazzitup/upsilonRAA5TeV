#include "SONGKYO.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "../cutsAndBin.h"

void draw_RAA_pt_isArrow(bool isArrow=true)
{
  setTDRStyle();
  writeExtraText = true;       // if extra text
  int iPeriod = 101; // 1: pp, 2: pPb, 3: PbPb, 100: RAA vs cent, 101: RAA vs pt or rap
  int iPos = 33;
  
  const int nState = 3; // Y(1S), Y(2S), and Y(3S)
  double xmax = 30.0;
//  double relsys = 0.1;

  double exsys_1s[6] =  {1., 1., 1., 1.5, 1.5, 9.};
  double exsys_2s[3] =  {2., 2.5, 10.5};
  double exsys_3s[2] =  {3., 12.};

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
  int ulstate = 2; //3S
  static const int n3s = 2;
  double boxw = 0.6; // for syst. box (vs cent)
  double lower68[n3s] = {0.,0.};
  double upper68[n3s] = {0.077425873,0.037306442};
  double lower95[n3s] = {0., 0};
  double upper95[n3s] = {0.125605752,0.076217074};
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
    box68per[ipt]->SetLineColor(kGreen+3);
    box68per[ipt]->SetFillColorAlpha(kGreen-6,0.5);
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
  
  //// legend
  //// axis et. al
  gRAA_sys[0]->GetXaxis()->SetTitle("p_{T}^{#mu#mu} (GeV/c)");
  gRAA_sys[0]->GetXaxis()->CenterTitle();
  gRAA_sys[0]->GetYaxis()->SetTitle("R_{AA}");
  gRAA_sys[0]->GetYaxis()->CenterTitle();
  gRAA_sys[0]->GetXaxis()->SetLimits(0.,xmax);
  gRAA_sys[0]->SetMinimum(0.0);
  gRAA_sys[0]->SetMaximum(1.3);


  if (isArrow == true){
        gRAA_sys[2]->SetPoint(0,-10,-10);
        gRAA_sys[2]->SetPointError(0,0,0);
        gRAA_sys[2]->SetPoint(1,-11,-11);
        gRAA_sys[2]->SetPointError(1,0,0);
        gRAA_sys[2]->SetPoint(2,-12,-12);
        gRAA_sys[2]->SetPointError(2,0,0);
        gRAA[2]->SetPoint(0,-10,-10);
        gRAA[2]->SetPointError(0,0,0);
        gRAA[2]->SetPoint(1,-11,-11);
        gRAA[2]->SetPointError(1,0,0);
        gRAA[2]->SetPoint(2,-12,-12);
        gRAA[2]->SetPointError(2,0,0);
        gRAA_sys[2]->GetHistogram()->GetXaxis()->SetLimits(0,30);
        gRAA_sys[2]->GetHistogram()->GetXaxis()->SetRangeUser(0,30);
        gRAA_sys[2]->SetMinimum(0.0);
        gRAA_sys[2]->SetMaximum(1.3);
        gRAA[2]->GetHistogram()->GetXaxis()->SetRangeUser(0,30);
        gRAA[2]->GetHistogram()->GetXaxis()->SetLimits(0,30);
        gRAA[2]->SetMinimum(0.0);
        gRAA[2]->SetMaximum(1.3);
      }
  
  //// draw  
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  for (int is=0; is<nState; is++){
    if ( is==0) {gRAA_sys[is]->Draw("A5");}
    else if(is==ulstate && isArrow==true) {
      for(int ipt=0;ipt<n3s;ipt++){
        box68per[ipt]->Draw("l");
      }
      gRAA_sys[is]->Draw("5");
    }
    else {gRAA_sys[is]->Draw("5");}
  }
  for(int is=0;is<nState;is++){
    if(is==ulstate && isArrow==true) {
      for(int ipt=0;ipt<n3s;ipt++) {
        arr95per[ipt]->Draw();
      }
      gRAA[is]->Draw("P");
    }
    else {gRAA[is]->Draw("P");}
  }
  
  dashedLine(0.,1.,xmax,1.,1,1);
  TLegend *leg= new TLegend(0.57, 0.55, 0.78, 0.75);
  SetLegendStyle(leg);
  TLegend *leg_up= new TLegend(0.57, 0.45, 0.78, 0.55);
  SetLegendStyle(leg_up);

  TArrow *arrLeg = new TArrow(16.,0.51,16.,0.56,0.02,"<-|");
  arrLeg->SetLineColor(kGreen+2);
  arrLeg->SetLineWidth(2);

  if (isArrow==false) { 
    for (int is=0; is<nState; is++){
      leg -> AddEntry(gRAA[is],Form(" #Upsilon(%dS)",is+1),"lp");
    }
  }
  else {
    leg -> AddEntry(gRAA[0]," #Upsilon(1S)","lp");
    leg -> AddEntry(gRAA[1]," #Upsilon(2S)","lp");
//    leg -> AddEntry(gRAA[2]," #Upsilon(3S)","lp");
    TLegendEntry *ent=leg_up->AddEntry("ent"," #Upsilon(3S) 68\% CL","f");
    ent->SetLineColor(kGreen+3);
    ent->SetFillColorAlpha(kGreen-6,0.5);
    ent->SetFillStyle(1001);
    ent=leg_up->AddEntry("ent"," #Upsilon(3S) 95\% CL","f");
    ent->SetLineColor(kWhite);
//    leg_up->SetTextSize(0.03);
    leg->Draw("same");
    leg_up->Draw("same");
    arrLeg->Draw();
  }


  //// draw text
  double sz_init = 0.895; double sz_step = 0.0525;
  globtex->DrawLatex(0.22, sz_init, "p_{T}^{#mu} > 4 GeV/c");
//  globtex->DrawLatex(0.22, sz_init, "p_{T}^{#mu#mu} < 30 GeV/c");
  globtex->DrawLatex(0.22, sz_init-sz_step, "|y|^{#mu#mu} < 2.4");
  globtex->DrawLatex(0.22, sz_init-sz_step*2, "Centrality 0-100%");
  
  //Global Unc.
  double sys_global_val = TMath::Sqrt(lumi_unc_pp*lumi_unc_pp+0.089*0.089+nMB_unc*nMB_unc);
  //double sys_global_val = TMath::Sqrt(lumi_unc_pp*lumi_unc_pp+lumi_unc_aa*lumi_unc_aa);
  double sys_global_y = sys_global_val;
  double sys_global_x = 0.8;
  TBox *globalUncBox = new TBox(xmax-sys_global_x,1-sys_global_y,xmax,1+sys_global_y);
  globalUncBox -> SetLineColor(kBlack);
  globalUncBox -> SetFillColorAlpha(kGray+2,0.6);
  globalUncBox -> SetLineWidth(1);
  globalUncBox -> Draw("l same");
  
  CMS_lumi( c1, iPeriod, iPos );

	c1->Update();
  c1->SaveAs(Form("RAA_vs_pt_isArrow%d.pdf",(int)isArrow));
  c1->SaveAs(Form("RAA_vs_pt_isArrow%d.png",(int)isArrow));

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

