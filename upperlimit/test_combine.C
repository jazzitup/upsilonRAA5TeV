#include "functions.C"
#include "RooGlobalFunc.h"
#include "RooWorkspace.h"

RooWorkspace* test_combine(const char* name_pbpb="../fitResults/fitresults_upsilon_DoubleCB_AA_DATA_pt4.0-6.0_y0.0-1.2_muPt4.0_centrality0-200_dphiEp_0.00PI_100.00PI.root", const char* name_pp="../fitResults/fitresults_upsilon_DoubleCB_PP_DATA_pt4.0-6.0_y0.0-1.2_muPt4.0.root")
{
   //Load necessary files
   TFile *f = new TFile(name_pbpb) ;
   TFile *f_pp = new TFile(name_pp) ;

   // Retrieve workspace from files and rename ws (PbPb) and ws_pp (PP)
   RooWorkspace* ws = (RooWorkspace*) f->Get("workspace");
   RooWorkspace* ws_pp = (RooWorkspace*) f_pp->Get("workspace");

   // RooRealVar *theVar; 
   RooDataSet *data; RooAbsPdf *pdf;
   RooRealVar *theVar_pp; RooDataSet *data_pp; RooAbsPdf *pdf_pp;

   // theVar = ws->var(poiname);
   // pdf = ws->pdf("pdf");
   data =(RooDataSet *) ws->data("dataset");
   pdf_pp = ws_pp->pdf("pdf");
   data_pp =(RooDataSet *) ws_pp->data("dataset");

	RooCategory dataCat("dataCat", "dataCat");
	dataCat.defineType("hi");
	dataCat.defineType("pp");

	RooRealVar muppt("pt1" ,"#mu+ pt",0,100,"GeV/c"); 
	RooRealVar mumpt("pt2","#mu- pt",0,100,"GeV/c"); 
	RooRealVar dimuPt("pt","p_{T}(#Upsilon)",0.,30,"GeV/c");
	RooRealVar dimuRapidity("y", "upsRapidity",0.);
	RooCategory QQsign("QQsign", "QQsign");
	QQsign.defineType("PlusMinus", 0);
	QQsign.defineType("PlusPlus", 1);
	QQsign.defineType("MinusMinus", 2);
	RooRealVar * mass = ws->var("invariantMass");
        //currently not in my Workspace, to be revisited
	//RooRealVar vProb("vProb","vProb",0.05,1);
	//   RooRealVar upsEta("upsEta","#eta(#Upsilon)",0.,"");
	//RooRealVar Centrality("Centrality", "Centrality", 0.);
	
         
	if (!mass) {
		mass = new RooRealVar("invariantMass", "#mu#mu mass", mmin, mmax, 
				"GeV/c^{2}");
	}

        //Forming the data set combined
	RooArgSet cols(*mass, muppt, mumpt, dimuPt, dimuRapidity, QQsign);
	RooDataSet data_combo("data", "data", cols, RooFit::Index(dataCat),RooFit::Import("hi", *data), RooFit::Import("pp", *data_pp));
        RooWorkspace *wcombo = new RooWorkspace("wcombo","workspace for PbPb + pp");
        wcombo->import(data_combo);

        //renaming pp variable and pdfs ... with _pp
	wcombo->import(*pdf_pp, RooFit::RenameAllNodes("pp"),
			RooFit::RenameAllVariablesExcept("pp",
				"invariantMass"
				//"prior,"
				//"mean,"
				//"turnOn,"
				//"f23,f3o2,"
				//"x23,x3o2,"
				//"alpha,"
				//"sigma1"
				), 
			RooFit::RecycleConflictNodes());

   // // create the combined variable 
   RooAbsPdf *sig1S = ws->pdf("cb1s");
   RooAbsPdf *sig2S = ws->pdf("cb2s");
   RooAbsPdf *sig3S = ws->pdf("cb3s");
   RooAbsPdf *pdf_combinedbkgd = ws->pdf("bkgLowPt");
   
   //RooRealVar *f2Svs1S   = ws->var("R_{#frac{2S}{1S}}");
   //RooRealVar *f3Svs1S   = ws->var("R_{#frac{3S}{1S}}");
   RooRealVar *nsig1f = ws->var("nSig1s");
   RooRealVar *nbkgd = ws->var("nBkg");
   //RooFormulaVar *nsig2f = new RooFormulaVar("N_{ #varUpsilon(2S)}","@0*@1", RooArgList(*nsig1f,*f2Svs1S));
   //RooFormulaVar *nsig2f = (RooFormulaVar*)ws->function("N_{#varUpsilon(2S)}");
   //RooFormulaVar *nsig3f = (RooFormulaVar*)ws->function("N_{#varUpsilon(3S)}");
   RooFormulaVar *nsig2f = (RooFormulaVar*)ws->function("nSig2s");
   RooFormulaVar *nsig3f = (RooFormulaVar*)ws->function("nSig3s");
   //RooFormulaVar *nsig3f = new RooFormulaVar("N_{ #varUpsilon(3S)}","@0*@1", RooArgList(*nsig1f,*f3Svs1S));
  
   //Currently unused for this analysis
   //RooRealVar *nsig2f = ws->var("N_{#Upsilon(2S)}");
   // RooRealVar *nsig3f = ws->var("N_{#Upsilon(3S)}");
   // RooRealVar *x3raw = new RooRealVar("x3raw","x3raw",7e-4,-10,10);
   // RooRealVar *nsig3f_pp = ws_pp->var("N_{#Upsilon(3S)}"); nsig3f_pp->SetName("N_{#Upsilon(3S)}_pp");
   // RooFormulaVar *nsig3f_new = new RooFormulaVar("N_{#Upsilon(3S)}","@0*@1",RooArgList(*nsig3f_pp,*x3raw));

   RooAbsPdf *pdf_new = new RooAddPdf ("pdf","new total p.d.f.",
         RooArgList(*sig1S,*sig2S,*sig3S,*pdf_combinedbkgd),
         RooArgList(*nsig1f,*nsig2f,*nsig3f,*nbkgd));
	wcombo->import(*pdf_new, RooFit::RenameAllNodes("hi"),
			RooFit::RenameAllVariablesExcept("hi",
				"mass"
				//"prior,"
				//"mean,"
				//"turnOn,"
            // "f23,f3o2,"
				//"x23,x3o2,"
				//"alpha,"
				//"sigma1,"
            //"x3raw,N_{#Upsilon(3S)}_pp"
				), 
			RooFit::RecycleConflictNodes());
   wcombo->Print();
   RooSimultaneous* simPdf = buildSimPdf(*wcombo,dataCat);
   wcombo->Print();

   // not sure this is really needed s
   // ince we will fit again in the later workspace creation
   RooFitResult* fit_2nd;// fit results
   fit_2nd = simPdf->fitTo(data_combo,
         // RooFit::Constrained(),
         RooFit::Save(kTRUE),
         RooFit::Extended(kTRUE),
         RooFit::Minos(kTRUE),
         RooFit::NumCPU(4));


   // fix all other variables in model:
   // everything except observables, POI, and nuisance parameters
   // must be constant
   wcombo->var("#alpha_{CB}_hi")->setConstant(true);
   wcombo->var("#alpha_{CB}_pp")->setConstant(true);
   wcombo->var("#sigma_{CB1}_hi")->setConstant(true);
   wcombo->var("#sigma_{CB1}_pp")->setConstant(true);
   wcombo->var("#sigma_{CB2}/#sigma_{CB1}_hi")->setConstant(true);
   wcombo->var("#sigma_{CB2}/#sigma_{CB1}_pp")->setConstant(true);
   wcombo->var("nSig1s_hi")->setConstant(true);
   wcombo->var("nSig1s_pp")->setConstant(true);
   wcombo->var("nSig2s_hi")->setConstant(true);
   wcombo->var("nSig2s_pp")->setConstant(true);
   wcombo->var("nSig3s_hi")->setConstant(true);
   wcombo->var("nSig3s_pp")->setConstant(true);
   wcombo->var("R_{#frac{2S}{1S}}_hi")->setConstant(true); 
   wcombo->var("R_{#frac{2S}{1S}}_pp")->setConstant(true); 
   wcombo->var("R_{#frac{3S}{1S}}_pp")->setConstant(true);
   //wcombo->var("R_{#frac{3S}{1S}}_hi")->setConstant(true); // this is parameter of interest do not set constant.
   wcombo->var("decay_hi")->setConstant(true);
   wcombo->var("decay_pp")->setConstant(true);
   wcombo->var("m_{ #varUpsilon(1S)}_hi")->setConstant(true);
   wcombo->var("m_{ #varUpsilon(1S)}_pp")->setConstant(true); 
   wcombo->var("nBkg_hi")->setConstant(true);
   wcombo->var("nBkg_pp")->setConstant(true);
   wcombo->var("n_{CB}_hi")->setConstant(true);
   wcombo->var("n_{CB}_pp")->setConstant(true);
   wcombo->var("sigmaFraction_hi")->setConstant(true);
   wcombo->var("sigmaFraction_pp")->setConstant(true);
   wcombo->var("turnOn_hi")->setConstant(true);
   wcombo->var("turnOn_pp")->setConstant(true);
   wcombo->var("width_hi")->setConstant(true);
   wcombo->var("width_pp")->setConstant(true);

   //currently unused for this analysis
   //wcombo->var("N_{#Upsilon(2S)}_hi")->setConstant(true);
   //wcombo->var("N_{#Upsilon(2S)}_pp")->setConstant(true);
   //wcombo->var("N_{#Upsilon(3S)}_pp")->setConstant(true); 


   //wcombo->writeToFile("fitresult_combo.root");
   return wcombo;
}
