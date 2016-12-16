#include "../commonUtility.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"
#include "../cutsAndBin.h"
#include "../multiTreeUtil.h"
using namespace std;


// - Trigger:
//   * idx = 0:  nominal
//   * idx = 1..100: toy variations, stat. only
//   * idx = -1: syst variation, "new_MAX", +1 sigma
//   * idx = -2: syst variation, "new_MAX", -1 sigma
//   * idx = -10: binned
// - MuID, STA:
//   * only one SF (for systematic uncertainty only)
//double tnp_w
//      idx = 200,   MuID,
//       idx = 300,   STA

TLegend *leg = new TLegend(0.55,0.2, 0.85,0.4,NULL,"brNDC");

void addInQuad ( TH1D* h0=0, TH1D* h1=0) ;
void getDevRatio ( TH1D* h0=0, TH1D* h1=0) ;
void getMaxTH1D ( TH1D* h0=0, TH1D* h1=0, TH1D* h2=0) ;
void addInQuadFive ( TH1D* h0=0, TH1D* h1=0, TH1D* h2=0, TH1D* h3=0, TH1D* h4=0, TH1D* h5=0);
void addInQuadSix ( TH1D* h0=0, TH1D* h1=0, TH1D* h2=0, TH1D* h3=0, TH1D* h4=0, TH1D* h5=0, TH1D* h6=0);
void getEffSys(int state =1, int Nsamples=100) { 
  TH1::SetDefaultSumw2();

  TFile* f1 = new TFile(Form("efficiencyTable/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx0.root",state) );
  TH1D* eff1 = (TH1D*)f1->Get("hptEffPP");
  TH1D* eff2 = (TH1D*)f1->Get("hptEffAA");
  TH1D* eff3 = (TH1D*)f1->Get("hrapEffPP");
  TH1D* eff4 = (TH1D*)f1->Get("hrapEffAA");
  TH1D* eff5 = (TH1D*)f1->Get("hcentintEffPP");
  TH1D* eff6 = (TH1D*)f1->Get("hcentintEffAA");
  TH1D* eff7 = (TH1D*)f1->Get("hcentEffAA");

  TH1D* eff1sys = (TH1D*)eff1->Clone("hptEffPPSys"); eff1sys->Reset();
  TH1D* eff2sys = (TH1D*)eff2->Clone("hptEffAASys"); eff2sys->Reset();
  TH1D* eff3sys = (TH1D*)eff3->Clone("hrapEffPPSys"); eff3sys->Reset();
  TH1D* eff4sys = (TH1D*)eff4->Clone("hrapEffAASys"); eff4sys->Reset();
  TH1D* eff5sys = (TH1D*)eff5->Clone("hcentintEffPPSys"); eff5sys->Reset();
  TH1D* eff6sys = (TH1D*)eff6->Clone("hcentintEffAASys"); eff6sys->Reset();
  TH1D* eff7sys = (TH1D*)eff7->Clone("hcentEffAASys"); eff7sys->Reset();

  // sys. tnp variaiton 
  TH1D* eff1sysVar = (TH1D*)eff1sys->Clone("hptEffPPSysVar"); 
  TH1D* eff2sysVar = (TH1D*)eff2sys->Clone("hptEffAASysVar"); 
  TH1D* eff3sysVar = (TH1D*)eff3sys->Clone("hrapEffPPSysVar");
  TH1D* eff4sysVar = (TH1D*)eff4sys->Clone("hrapEffAASysVar");
  TH1D* eff5sysVar = (TH1D*)eff5sys->Clone("hcentintEffPPSysVar"); 
  TH1D* eff6sysVar = (TH1D*)eff6sys->Clone("hcentintEffAASysVar"); 
  TH1D* eff7sysVar = (TH1D*)eff7sys->Clone("hcentEffAASysVar");
  // stat. fluc.
  TH1D* eff1stat = (TH1D*)eff1sys->Clone("hptEffPPStat"); 
  TH1D* eff2stat = (TH1D*)eff2sys->Clone("hptEffAAStat"); 
  TH1D* eff3stat = (TH1D*)eff3sys->Clone("hrapEffPPStat");
  TH1D* eff4stat = (TH1D*)eff4sys->Clone("hrapEffAAStat");
  TH1D* eff5stat = (TH1D*)eff5sys->Clone("hcentintEffPPStat"); 
  TH1D* eff6stat = (TH1D*)eff6sys->Clone("hcentintEffAAStat"); 
  TH1D* eff7stat = (TH1D*)eff7sys->Clone("hcentEffAAStat");

  // sys.var_1
  TFile* fid_1 = new TFile(Form("efficiencyTableSys/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx-1.root",state) );
  TH1D* relDevVar1_1 = (TH1D*)fid_1->Get("hptEffPP");
  TH1D* relDevVar2_1 = (TH1D*)fid_1->Get("hptEffAA");
  TH1D* relDevVar3_1 = (TH1D*)fid_1->Get("hrapEffPP");
  TH1D* relDevVar4_1 = (TH1D*)fid_1->Get("hrapEffAA");
  TH1D* relDevVar5_1 = (TH1D*)fid_1->Get("hcentintEffPP");
  TH1D* relDevVar6_1 = (TH1D*)fid_1->Get("hcentintEffAA");
  TH1D* relDevVar7_1 = (TH1D*)fid_1->Get("hcentEffAA");
  relDevVar1_1->Add( eff1, -1 );     relDevVar1_1->Divide( eff1);
  relDevVar2_1->Add( eff2, -1 );     relDevVar2_1->Divide( eff2);
  relDevVar3_1->Add( eff3, -1 );     relDevVar3_1->Divide( eff3);
  relDevVar4_1->Add( eff4, -1 );     relDevVar4_1->Divide( eff4);
  relDevVar5_1->Add( eff5, -1 );     relDevVar5_1->Divide( eff5);
  relDevVar6_1->Add( eff6, -1 );     relDevVar6_1->Divide( eff6);
  relDevVar7_1->Add( eff7, -1 );     relDevVar7_1->Divide( eff7);
  // sys.var_2
  TFile* fid_2 = new TFile(Form("efficiencyTableSys/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx-2.root",state) );
  TH1D* relDevVar1_2 = (TH1D*)fid_2->Get("hptEffPP");
  TH1D* relDevVar2_2 = (TH1D*)fid_2->Get("hptEffAA");
  TH1D* relDevVar3_2 = (TH1D*)fid_2->Get("hrapEffPP");
  TH1D* relDevVar4_2 = (TH1D*)fid_2->Get("hrapEffAA");
  TH1D* relDevVar5_2 = (TH1D*)fid_2->Get("hcentintEffPP");
  TH1D* relDevVar6_2 = (TH1D*)fid_2->Get("hcentintEffAA");
  TH1D* relDevVar7_2 = (TH1D*)fid_2->Get("hcentEffAA");
  relDevVar1_2->Add( eff1, -1 );     relDevVar1_2->Divide( eff1);
  relDevVar2_2->Add( eff2, -1 );     relDevVar2_2->Divide( eff2);
  relDevVar3_2->Add( eff3, -1 );     relDevVar3_2->Divide( eff3);
  relDevVar4_2->Add( eff4, -1 );     relDevVar4_2->Divide( eff4);
  relDevVar5_2->Add( eff5, -1 );     relDevVar5_2->Divide( eff5);
  relDevVar6_2->Add( eff6, -1 );     relDevVar6_2->Divide( eff6);
  relDevVar7_2->Add( eff7, -1 );     relDevVar7_2->Divide( eff7);
  // get Max deviation of each bin:
  // sys. variation
  getMaxTH1D(eff1sysVar, relDevVar1_1, relDevVar1_2);
  getMaxTH1D(eff2sysVar, relDevVar2_1, relDevVar2_2);
  getMaxTH1D(eff3sysVar, relDevVar3_1, relDevVar3_2);
  getMaxTH1D(eff4sysVar, relDevVar4_1, relDevVar4_2);
  getMaxTH1D(eff5sysVar, relDevVar5_1, relDevVar5_2);
  getMaxTH1D(eff6sysVar, relDevVar6_1, relDevVar6_2);
  getMaxTH1D(eff7sysVar, relDevVar7_1, relDevVar7_2);


  // SF from binnined table:
  TFile* fid_10 = new TFile(Form("efficiencyTableSys/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx-10.root",state) );
  TH1D* eff1binned = (TH1D*)fid_10->Get("hptEffPP");
  TH1D* eff2binned = (TH1D*)fid_10->Get("hptEffAA");
  TH1D* eff3binned = (TH1D*)fid_10->Get("hrapEffPP");
  TH1D* eff4binned = (TH1D*)fid_10->Get("hrapEffAA");
  TH1D* eff5binned = (TH1D*)fid_10->Get("hcentintEffPP");
  TH1D* eff6binned = (TH1D*)fid_10->Get("hcentintEffAA");
  TH1D* eff7binned = (TH1D*)fid_10->Get("hcentEffAA");
  eff1binned ->SetName("hptRelSysBinnedPP");
  eff2binned ->SetName("hptRelSysBinnedAA");
  eff3binned ->SetName("hrapRelSysBinnedPP");
  eff4binned ->SetName("hrapRelSysBinnedAA");
  eff5binned ->SetName("hcentintRelSysBinnedPP");
  eff6binned ->SetName("hcentintRelSysBinnedAA");
  eff7binned ->SetName("hcentRelSysBinnedAA");
  eff1binned->Add( eff1, -1 );     eff1binned->Divide( eff1);
  eff2binned->Add( eff2, -1 );     eff2binned->Divide( eff2);
  eff3binned->Add( eff3, -1 );     eff3binned->Divide( eff3);
  eff4binned->Add( eff4, -1 );     eff4binned->Divide( eff4);
  eff5binned->Add( eff5, -1 );     eff5binned->Divide( eff5);
  eff6binned->Add( eff6, -1 );     eff6binned->Divide( eff6);
  eff7binned->Add( eff7, -1 );     eff7binned->Divide( eff7);

  // pT reweight (nothing to do with TNP
  TFile* fid_ptw = new TFile(Form("efficiencyTable/efficiency_ups%ds_useDataPtWeight0_tnpWeight1_tnpIdx0.root",state) );
  TH1D* eff1ptw = (TH1D*)fid_ptw->Get("hptEffPP");
  TH1D* eff2ptw = (TH1D*)fid_ptw->Get("hptEffAA");
  TH1D* eff3ptw = (TH1D*)fid_ptw->Get("hrapEffPP");
  TH1D* eff4ptw = (TH1D*)fid_ptw->Get("hrapEffAA");
  TH1D* eff5ptw = (TH1D*)fid_ptw->Get("hcentintEffPP");
  TH1D* eff6ptw = (TH1D*)fid_ptw->Get("hcentintEffAA");
  TH1D* eff7ptw = (TH1D*)fid_ptw->Get("hcentEffAA");
  eff1ptw ->SetName("hptRelSysPtwPP");
  eff2ptw ->SetName("hptRelSysPtwAA");
  eff3ptw ->SetName("hrapRelSysPtwPP");
  eff4ptw ->SetName("hrapRelSysPtwAA");
  eff5ptw ->SetName("hcentintRelSysPtwPP");
  eff6ptw ->SetName("hcentintRelSysPtwAA");
  eff7ptw ->SetName("hcentRelSysPtwAA");
  eff1ptw->Add( eff1, -1 );     eff1ptw->Divide( eff1);
  eff2ptw->Add( eff2, -1 );     eff2ptw->Divide( eff2);
  eff3ptw->Add( eff3, -1 );     eff3ptw->Divide( eff3);
  eff4ptw->Add( eff4, -1 );     eff4ptw->Divide( eff4);
  eff5ptw->Add( eff5, -1 );     eff5ptw->Divide( eff5);
  eff6ptw->Add( eff6, -1 );     eff6ptw->Divide( eff6);
  eff7ptw->Add( eff7, -1 );     eff7ptw->Divide( eff7);

  // Muon ID
  TFile* fid_200 = new TFile(Form("efficiencyTableSys/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx200.root",state) );
  TH1D* eff1muid = (TH1D*)fid_200->Get("hptEffPP");
  TH1D* eff2muid = (TH1D*)fid_200->Get("hptEffAA");
  TH1D* eff3muid = (TH1D*)fid_200->Get("hrapEffPP");
  TH1D* eff4muid = (TH1D*)fid_200->Get("hrapEffAA");
  TH1D* eff5muid = (TH1D*)fid_200->Get("hcentintEffPP");
  TH1D* eff6muid = (TH1D*)fid_200->Get("hcentintEffAA");
  TH1D* eff7muid = (TH1D*)fid_200->Get("hcentEffAA");
  eff1muid ->SetName("hptRelSysMuIdPP");
  eff2muid ->SetName("hptRelSysMuIdAA");
  eff3muid ->SetName("hrapRelSysMuIdPP");
  eff4muid ->SetName("hrapRelSysMuIdAA");
  eff5muid ->SetName("hcentintRelSysMuIdPP");
  eff6muid ->SetName("hcentintRelSysMuIdAA");
  eff7muid ->SetName("hcentRelSysMuIdAA");
  eff1muid->Add( eff1, -1 );     eff1muid->Divide( eff1);
  eff2muid->Add( eff2, -1 );     eff2muid->Divide( eff2);
  eff3muid->Add( eff3, -1 );     eff3muid->Divide( eff3);
  eff4muid->Add( eff4, -1 );     eff4muid->Divide( eff4);
  eff5muid->Add( eff5, -1 );     eff5muid->Divide( eff5);
  eff6muid->Add( eff6, -1 );     eff6muid->Divide( eff6);
  eff7muid->Add( eff7, -1 );     eff7muid->Divide( eff7);

  // STA
  TFile* fid_300 = new TFile(Form("efficiencyTableSys/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx300.root",state) );
  TH1D* eff1sta = (TH1D*)fid_300->Get("hptEffPP");
  TH1D* eff2sta = (TH1D*)fid_300->Get("hptEffAA");
  TH1D* eff3sta = (TH1D*)fid_300->Get("hrapEffPP");
  TH1D* eff4sta = (TH1D*)fid_300->Get("hrapEffAA");
  TH1D* eff5sta = (TH1D*)fid_300->Get("hcentintEffPP");
  TH1D* eff6sta = (TH1D*)fid_300->Get("hcentintEffAA");
  TH1D* eff7sta = (TH1D*)fid_300->Get("hcentEffAA");
  eff1sta ->SetName("hptRelSysStaPP");
  eff2sta ->SetName("hptRelSysStaAA");
  eff3sta ->SetName("hrapRelSysStaPP");
  eff4sta ->SetName("hrapRelSysStaAA");
  eff5sta ->SetName("hcentintRelSysStaPP");
  eff6sta ->SetName("hcentintRelSysStaAA");
  eff7sta ->SetName("hcentRelSysStaAA");

  eff1sta->Add( eff1, -1 );     eff1sta->Divide( eff1);
  eff2sta->Add( eff2, -1 );     eff2sta->Divide( eff2);
  eff3sta->Add( eff3, -1 );     eff3sta->Divide( eff3);
  eff4sta->Add( eff4, -1 );     eff4sta->Divide( eff4);
  eff5sta->Add( eff5, -1 );     eff5sta->Divide( eff5);
  eff6sta->Add( eff6, -1 );     eff6sta->Divide( eff6);
  eff7sta->Add( eff7, -1 );     eff7sta->Divide( eff7);
  
  // Stat fluctuation : 

  for ( int idx=1 ; idx<= Nsamples ; idx++) {
    cout <<"Reading "  << idx<<"th file..." << endl;
    TFile* fid = new TFile(Form("efficiencyTableSys/efficiency_ups%ds_useDataPtWeight1_tnpWeight1_tnpIdx%d.root",state,idx) );
    TH1D* relativeDev1 = (TH1D*)fid->Get("hptEffPP");
    TH1D* relativeDev2 = (TH1D*)fid->Get("hptEffAA");
    TH1D* relativeDev3 = (TH1D*)fid->Get("hrapEffPP");
    TH1D* relativeDev4 = (TH1D*)fid->Get("hrapEffAA");
    TH1D* relativeDev5 = (TH1D*)fid->Get("hcentintEffPP");
    TH1D* relativeDev6 = (TH1D*)fid->Get("hcentintEffAA");
    TH1D* relativeDev7 = (TH1D*)fid->Get("hcentEffAA");
    
    relativeDev1->Add( eff1, -1 );     relativeDev1->Divide( eff1);
    relativeDev2->Add( eff2, -1 );     relativeDev2->Divide( eff2);
    relativeDev3->Add( eff3, -1 );     relativeDev3->Divide( eff3);
    relativeDev4->Add( eff4, -1 );     relativeDev4->Divide( eff4);
    relativeDev5->Add( eff5, -1 );     relativeDev5->Divide( eff5);
    relativeDev6->Add( eff6, -1 );     relativeDev6->Divide( eff6);
    relativeDev7->Add( eff7, -1 );     relativeDev7->Divide( eff7);

    addInQuad( eff1stat, relativeDev1 ) ;
    addInQuad( eff2stat, relativeDev2 ) ;
    addInQuad( eff3stat, relativeDev3 ) ;
    addInQuad( eff4stat, relativeDev4 ) ;
    addInQuad( eff5stat, relativeDev5 ) ;
    addInQuad( eff6stat, relativeDev6 ) ;
    addInQuad( eff7stat, relativeDev7 ) ;
    fid->Close();
  }
  eff1stat->Scale( 1./sqrt( float(Nsamples) ) );
  eff2stat->Scale( 1./sqrt( float(Nsamples) ) );
  eff3stat->Scale( 1./sqrt( float(Nsamples) ) );
  eff4stat->Scale( 1./sqrt( float(Nsamples) ) );
  eff5stat->Scale( 1./sqrt( float(Nsamples) ) );
  eff6stat->Scale( 1./sqrt( float(Nsamples) ) );
  eff7stat->Scale( 1./sqrt( float(Nsamples) ) );

  // Merge them! 
  addInQuadSix( eff1sys,  eff1sysVar, eff1binned, eff1sta, eff1muid, eff1stat, eff1ptw );
  addInQuadSix( eff2sys,  eff2sysVar, eff2binned, eff2sta, eff2muid, eff2stat, eff2ptw );
  addInQuadSix( eff3sys,  eff3sysVar, eff3binned, eff3sta, eff3muid, eff3stat, eff3ptw );
  addInQuadSix( eff4sys,  eff4sysVar, eff4binned, eff4sta, eff4muid, eff4stat, eff4ptw );
  addInQuadSix( eff5sys,  eff5sysVar, eff5binned, eff5sta, eff5muid, eff5stat, eff5ptw );
  addInQuadSix( eff6sys,  eff6sysVar, eff6binned, eff6sta, eff6muid, eff6stat, eff6ptw );
  addInQuadSix( eff7sys,  eff7sysVar, eff7binned, eff7sta, eff7muid, eff7stat, eff7ptw );
  
  
  TFile* fout = new TFile(Form("sys_tnp_ups%d.root",state),"recreate");
  eff1sys->Write(); // eff1sysVar->Write(); eff1binned->Write(); eff1sta->Write(); eff1muid->Write(); eff1stat->Write(); eff1ptw->Write();
  eff2sys->Write(); // eff2sysVar->Write(); eff2binned->Write(); eff2sta->Write(); eff2muid->Write(); eff2stat->Write(); eff2ptw->Write();
  eff3sys->Write(); // eff3sysVar->Write(); eff3binned->Write(); eff3sta->Write(); eff3muid->Write(); eff3stat->Write(); eff3ptw->Write();
  eff4sys->Write(); // eff4sysVar->Write(); eff4binned->Write(); eff4sta->Write(); eff4muid->Write(); eff4stat->Write(); eff4ptw->Write();
  eff5sys->Write();  //eff5sysVar->Write(); eff5binned->Write(); eff5sta->Write(); eff5muid->Write(); eff5stat->Write(); eff5ptw->Write();
  eff6sys->Write();  //eff6sysVar->Write(); eff6binned->Write(); eff6sta->Write(); eff6muid->Write(); eff6stat->Write(); eff6ptw->Write();
  eff7sys->Write();  //eff7sysVar->Write(); eff7binned->Write(); eff7sta->Write(); eff7muid->Write(); eff7stat->Write(); eff7ptw->Write();


}

void addInQuad ( TH1D* h0, TH1D* h1) { 
  if ( h0->GetNbinsX() != h1->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  for ( int i=1 ;  i<=h0->GetNbinsX(); i++) {
    float x0 =  h0->GetBinContent(i);
    float x1 =  h1->GetBinContent(i);
    h0->SetBinContent(i,  sqrt ( x0*x0 + x1*x1 ) );
  }
}
void addInQuadFive ( TH1D* h0, TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, TH1D* h5) { 
  if ( h0->GetNbinsX() != h1->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h2->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h3->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h4->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h5->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  for ( int i=1 ;  i<=h0->GetNbinsX(); i++) {
    float x1 =  h1->GetBinContent(i);
    float x2 =  h2->GetBinContent(i);
    float x3 =  h3->GetBinContent(i);
    float x4 =  h4->GetBinContent(i);
    float x5 =  h5->GetBinContent(i);
    h0->SetBinContent(i,  sqrt ( x1*x1 + x2*x2 + x3*x3 + x4*x4 + x5*x5 ) );
  }
}
void addInQuadSix ( TH1D* h0, TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, TH1D* h5, TH1D* h6) { 
  if ( h0->GetNbinsX() != h1->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h2->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h3->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h4->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h5->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h6->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  for ( int i=1 ;  i<=h0->GetNbinsX(); i++) {
    float x1 =  h1->GetBinContent(i);
    float x2 =  h2->GetBinContent(i);
    float x3 =  h3->GetBinContent(i);
    float x4 =  h4->GetBinContent(i);
    float x5 =  h5->GetBinContent(i);
    float x6 =  h6->GetBinContent(i);
    h0->SetBinContent(i,  sqrt ( x1*x1 + x2*x2 + x3*x3 + x4*x4 + x5*x5 * x6*x6) );
  }
}
void getMaxTH1D ( TH1D* h0, TH1D* h1, TH1D* h2) {
  if ( h0->GetNbinsX() != h1->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;
  if ( h0->GetNbinsX() != h2->GetNbinsX() )   cout << " Bin numbers are not consistent!" << endl;

  for ( int i=1 ;  i<=h0->GetNbinsX(); i++) {
    float x1 =  fabs(h1->GetBinContent(i));
    float x2 =  fabs(h2->GetBinContent(i));
    if ( x1 > x2 ) 
      h0->SetBinContent(i, x1 );
    else
      h0->SetBinContent(i, x2 );
  }
  
}
