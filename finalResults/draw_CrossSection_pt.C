#include "SONGKYO.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"

void draw_CrossSection_pt(int ppAA=1) //1=pp, 2=AA
{
  setTDRStyle();
  writeExtraText = true;       // if extra text
  //int iPeriod; // 1: pp, 2: pPb, 3: PbPb, 100: RAA vs cent, 101: RAA vs pt or rap
  int iPos = 33;
  
  int nState = 2; // Y(1S), Y(2S), and Y(3S)
  if(ppAA==1) nState=3;
  double xmax = 30.0;
//  double relsys = 0.1;

  double exsys_1s[6] =  {1., 1., 1., 1.5, 1.5, 9.};
  double exsys_2s[3] =  {2., 2.5, 10.5};
  double exsys_3s[2] =  {3.,12.};

  TString sz_ppAA;
  if (ppAA==1) { sz_ppAA = "PP";}
  else if (ppAA==2) { sz_ppAA = "AA";}
  else { cout << "ERROR!! Select ppAA==1 or 2!!!"<< endl; return; }

  ////////////////////////////////////////////////////////////////
  //// read input file : value & stat.
  TFile* fIn[nState];
	TGraphErrors* gCrossSection[nState];
	TGraphErrors* gCrossSection_sys[nState];
  for (int is=0; is<nState; is++){
  	fIn[is] = new TFile(Form("Ups_%d_RAA.root",is+1),"READ");
    gCrossSection[is]=(TGraphErrors*)fIn[is]->Get(Form("gCrossSection_pt_%s",sz_ppAA.Data()));
    gCrossSection_sys[is]=(TGraphErrors*)fIn[is]->Get(Form("gCrossSection_pt_%s",sz_ppAA.Data()));
    //cout << "gCrossSection["<<is<<"] = " <<gCrossSection[is] << endl;
  }
  //// read input file : syst.
  TFile* fInSys[nState];
  TH1D* hSys[nState];
  int npoint[nState];
  for (int is=0; is<nState; is++){
    fInSys[is] = new TFile(Form("../Systematic/mergedSys_ups%ds.root",is+1),"READ");
    hSys[is]=(TH1D*)fInSys[is]->Get(Form("hpt%s_merged",sz_ppAA.Data()));
    npoint[is] = hSys[is]->GetSize()-2;
    cout << "*** Y("<<is+1<<") : # of point = " << npoint[is] << endl;
  }  
  
  //// set bin width and calculate systematic uncertainties
  double pxtmp, pytmp, extmp, eytmp;
  double relsys;  
  for (int is=0; is<nState; is++){
    cout << is+1 <<"th state***************" << endl;
    if (npoint[is] != gCrossSection[is]->GetN()) {cout << "Error!! data file and syst. file have different binnig!" << endl; return; }
    for (int ipt=0; ipt< npoint[is] ; ipt++) { //bin by bin
      pxtmp=0; pytmp=0; extmp=0; eytmp=0; relsys=0;
      gCrossSection[is]->GetPoint(ipt, pxtmp, pytmp);
      extmp=gCrossSection[is]->GetErrorX(ipt);
      eytmp=gCrossSection[is]->GetErrorY(ipt);
      relsys=hSys[is]->GetBinContent(ipt+1);
      cout << ipt <<"th bin CrossSection value = " << pytmp << endl;
      cout << ipt <<"th bin stat. = " << eytmp << endl;
      //cout << ipt <<"th bin rel. syst. = " << relsys << endl;
      cout << ipt <<"th bin syst. = " << pytmp*relsys << endl; 
      // 1) remove ex from gCrossSection
      gCrossSection[is]->SetPointError(ipt, 0, eytmp);
      // 2) set ey for gCrossSection_sys
      //gCrossSection_sys[is]->SetPointError(ipt, extmp, pytmp*relsys);
      if (is==0) gCrossSection_sys[is]->SetPointError(ipt, exsys_1s[ipt], pytmp*relsys);
      else if (is==1) gCrossSection_sys[is]->SetPointError(ipt, exsys_2s[ipt], pytmp*relsys);
      else if (is==2 && ppAA==1) gCrossSection_sys[is]->SetPointError(ipt, exsys_3s[ipt], pytmp*relsys);
      else if (is==2) gCrossSection_sys[is]->SetPointError(ipt, 0, 0);
      //else gCrossSection_sys[is]->SetPointError(ipt, exsys_3s[ipt], pytmp*relsys);
    }
  }
 
  ////////////////////////////////////////////////////////////////

  //// graph style 
  for (int is=0; is<nState; is++){
    SetGraphStyle(gCrossSection[is], is, is); 
    SetGraphStyleSys(gCrossSection_sys[is], is); 
	}
  
  //// latex for text
  TLatex* globtex = new TLatex();
  globtex->SetNDC();
  globtex->SetTextAlign(12); //left-center
  globtex->SetTextFont(42);
  globtex->SetTextSize(0.038);
  
  //// legend
  TLegend *leg= new TLegend(0.75, 0.55, 0.95, 0.75);
  SetLegendStyle(leg);
  for (int is=0; is<nState; is++){
    leg -> AddEntry(gCrossSection[is],Form("#Upsilon(%dS)",is+1),"lp");
  }
  
  //// axis et. al
  gCrossSection_sys[0]->GetXaxis()->SetTitle("p_{T}^{#mu#mu} (GeV/c)");
  gCrossSection_sys[0]->GetXaxis()->CenterTitle();
  if (ppAA==1) gCrossSection_sys[0]->GetYaxis()->SetTitle("B #frac{d#sigma}{#Deltaydp_{T}} (nb/ GeV/c)");
  else gCrossSection_sys[0]->GetYaxis()->SetTitle("B #frac{1}{T_{AA}} #frac{dN}{#Deltaydp_{T}} (nb/ GeV/c)");
  gCrossSection_sys[0]->GetYaxis()->CenterTitle();
  gCrossSection_sys[0]->GetYaxis()->SetTitleOffset(2.0);
  gCrossSection_sys[0]->GetYaxis()->SetTitleSize(0.045);
  gCrossSection_sys[0]->GetXaxis()->SetLimits(0.,xmax);
  gCrossSection_sys[0]->SetMinimum(0.00005);
  //gCrossSection_sys[0]->SetMinimum(0.0000001);
  gCrossSection_sys[0]->SetMaximum(1.);
 
  //// draw  
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  gPad->SetLogy(1); // for cross section
  for (int is=0; is<nState; is++){
    if ( is==0) gCrossSection_sys[is]->Draw("A5");
    else gCrossSection_sys[is]->Draw("5");
    gCrossSection[is]->Draw("P");
	}
  leg->Draw();
  gPad->SetLeftMargin(0.23);

  //// draw text
  double sz_init = 0.895; double sz_step = 0.0525;
  double sz_shift;
  if (ppAA==1) sz_shift=0.6;
  else sz_shift=0.0;
  globtex->DrawLatex(0.27, sz_init-sz_shift, "p_{T}^{#mu} > 4 GeV/c");
//  globtex->DrawLatex(0.22, sz_init, "p_{T}^{#mu#mu} < 30 GeV/c");
  globtex->DrawLatex(0.27, sz_init-sz_shift-sz_step, "|y|^{#mu#mu} < 2.4");
  globtex->DrawLatex(0.48, sz_init-sz_shift+0.005, "|#eta^{#mu}| < 2.4");
  if(ppAA==2) globtex->DrawLatex(0.48, sz_init-sz_shift-sz_step+0.005, "Cent. 0-100%");
  
  CMS_lumi( c1, ppAA, iPos );

	c1->Update();
  c1->SaveAs(Form("CrossSection_vs_pt_%s.pdf",sz_ppAA.Data()));
  c1->SaveAs(Form("CrossSection_vs_pt_%s.png",sz_ppAA.Data()));

/*
	///////////////////////////////////////////////////////////////////
	//// save as a root file
	TFile *outFile = new TFile("CrossSection_vs_pt.root", "RECREATE");
	outFile->cd();
	for (int is=0; is<nState; is++){
		gCrossSection_sys[is]->Write();	
		gCrossSection[is]->Write();	
	}
	outFile->Close();
*/	
	return;

} // end of main func.

