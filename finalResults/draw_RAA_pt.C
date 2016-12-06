#include "SONGKYO.h"

void draw_RAA_pt()
{
  const int nState = 3;

  //// read the graph
  TFile* fIn[nState];
	TGraphErrors* gRAA[nState];
  for (int is=0; is<nState; is++){
  	fIn[is] = new TFile(Form("Ups_%d_RAA.root",is+1),"READ");
    gRAA[is]=(TGraphErrors*)fIn[is]->Get("gRAA_pt");
    cout << "gRAA["<<is<<"] = " <<gRAA[is] << endl;
  }
  
  //// syst. uncer. (temp)
	TGraphErrors* gRAA_sys[nState];
  int npoint[nState];
  double pxtmp, pytmp;
  for (int is=0; is<nState; is++){
    gRAA_sys[is]=(TGraphErrors*)fIn[is]->Get("gRAA_pt");
    npoint[is] = gRAA_sys[is]->GetN();
    for (int ipt=0; ipt< npoint[is] ; ipt++) {
      gRAA_sys[is]->GetPoint(ipt, pxtmp, pytmp);
      gRAA_sys[is]->SetPointError(ipt, pxtmp, pytmp*0.1);
    }
  }
 
 
  //// style 
  SetGraphStyleFinal(gRAA[0], 1, 0); 
	SetGraphStyleFinal(gRAA[1], 2, 3); 
	SetGraphStyleFinal(gRAA[2], 0, 5); 
	gRAA[0]->SetMarkerSize(1.4);
	gRAA[1]->SetMarkerSize(1.4);
	gRAA[2]->SetMarkerSize(2.6);
  
  gRAA_sys[0]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  gRAA_sys[0]->GetXaxis()->CenterTitle();
  gRAA_sys[0]->GetYaxis()->SetTitle("R_{AA}");
  gRAA_sys[0]->GetYaxis()->CenterTitle();
  gRAA_sys[0]->GetXaxis()->SetLimits(0.,30.0);
  gRAA_sys[0]->SetMinimum(0.0);
  gRAA_sys[0]->SetMaximum(1.2);
  
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  gRAA_sys[0]->Draw("A5");
  gRAA[0]->Draw("P");
  gRAA[1]->Draw("P");
  gRAA[2]->Draw("P");
	dashedLine(0.,1.,30.,1.,1,1);

/*	
  TLegendEntry *le1=legBR->AddEntry("le1",Form("  %s", rapAbsArr[2].Data()),"lpf");
	le1->SetFillColorAlpha(kBlue-10,0.5);
	le1->SetFillStyle(1001);
	le1->SetLineColor(kBlue-3);
	le1->SetMarkerStyle(kFullCircle);
	le1->SetMarkerColor(kBlue-3);
	le1->SetMarkerSize(2.1);
	TLegendEntry *le2=legBR->AddEntry("le2",Form("  %s", rapAbsArr[1].Data()),"lpf");
	le2->SetFillColorAlpha(kRed-10,0.5);
	le2->SetFillStyle(1001);
	le2->SetLineColor(kPink-6);
	le2->SetMarkerStyle(kFullSquare);
	le2->SetMarkerColor(kPink-6);
	le2->SetMarkerSize(2.1);
	TLegendEntry *le3=legBR->AddEntry("le3",Form("  %s", rapAbsArr[0].Data()),"lpf");
	le3->SetFillColorAlpha(kGreen-10,0.5);
	le3->SetFillStyle(1001);
	le3->SetLineColor(kGreen+3);
	le3->SetMarkerStyle(kFullDiamond);
	le3->SetMarkerColor(kGreen+3);
	le3->SetMarkerSize(3.3);

	//legBR->Draw();
*/
  //globtex->SetTextAlign(22);
	//globtex->SetTextFont(42);
  //globtex->SetTextSize(0.05);
 // globtex->DrawLatex(0.57, 0.30, rapAbsArr[0].Data());
	
	//globtex->SetTextAlign(32); 
	//globtex->SetTextSize(0.048);
	//globtex->SetTextFont(42);
	//if (isPrompt) globtex->DrawLatex(0.92, 0.77, "Prompt J/#psi");
	//else globtex->DrawLatex(0.92, 0.77, "Nonprompt J/#psi");

	//CMS_lumi( c1, isPA, iPos );
	//c1->Update();
  
    //c1->SaveAs(Form("plot_RFB/RFB_pt_isPrompt%d_rap1.pdf",(int)isPrompt));
    //c1->SaveAs(Form("plot_RFB/RFB_pt_isPrompt%d_rap1.png",(int)isPrompt));
/*
	///////////////////////////////////////////////////////////////////
	//// save as a root file
	TFile *outFile;
  if (noPtWeight) outFile = new TFile(Form("plot_RFB/RFB_pt_isPrompt%d_noPtWeight.root",(int)isPrompt),"RECREATE");
  else outFile = new TFile(Form("plot_RFB/RFB_pt_isPrompt%d.root",(int)isPrompt),"RECREATE");
	outFile->cd();
	for (int iy=0; iy<nRapRFB; iy++){
		gRFB_sys[iy]->Write();	
		gRFB[iy]->Write();	
	}
	outFile->Close();
*/	
	return;

} // end of main func.

