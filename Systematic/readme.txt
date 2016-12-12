This is the area where the systematic uncertainties tables are collected.

*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~
Efficiency : root files are saved in 
../efficiency/sys_efficiency_ups*.root 
TFile**					../efficiency/sys_efficiency_ups1.root
 TFile*						../efficiency/sys_efficiency_ups1.root
  KEY: TH1D					hptEffPPsys;1
  KEY: TH1D					hptEffAAsys;1
  KEY: TH1D					hrapEffPPsys;1
  KEY: TH1D					hrapEffAAsys;1
  KEY: TH1D					hcentEffAA_intsys;1
  KEY: TH1D					hcentEffAAsys;1
  KEY: TH1D					hcentEffPPsys;1

*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~
Acceptance : root files are saved in 
../acceptance/sys_acceptance_ups*.root 
TFile**					sys_acceptance_ups1.root
 TFile*						sys_acceptance_ups1.root
 KEY: TH1F					hptSysPP;1
  KEY: TH1F					hptSysAA;1
  KEY: TH1F					hrapSysPP;1
  KEY: TH1F					hrapSysAA;1
  KEY: TH1F					hcentSysAA_int;1
  KEY: TH1D					hcentSysAA;1
  KEY: TH1F					hcentSysPP;1

*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~
Fit uncertainty due to Signal PDF:    SignalVariation_keep/sys_signalPDFVariaion_*s.root

TFile**		sys_signalPDFVariaion_1s.root
 TFile*			sys_signalPDFVariaion_1s.root
  KEY: TH1D		hptAA;1	 uncertainty vs p_{T}
  KEY: TH1D		hptPP;1	 uncertainty vs p_{T}
  KEY: TH1D		hrapAA;1 uncertainty vs rap
  KEY: TH1D		hrapPP;1 uncertainty vs rap
  KEY: TH1D		hIntPP;1 uncertainty vs integrated bin
  KEY: TH1D		hIntAA;1 uncertainty vs integrated bin
  KEY: TH1D		hcentAA;1	     uncertainty vs cent

*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~
Fit uncertainty due to Background PDF:    backgroundVariation/sys_bkgPDFVariaion_*s.root
 KEY: TH1D	hrapPP;1
  KEY: TH1D	hrapAA;1
  KEY: TH1D	hrapAAoPP;1
  KEY: TH1D	hptPP;1
  KEY: TH1D	hptAA;1
  KEY: TH1D	hptAAoPP;1
  KEY: TH1D	hIntAA;1
  KEY: TH1D	hIntPP;1
  KEY: TH1D	hIntAAoPP;1
  KEY: TH1D	hcentAA;1
  KEY: TH1D	hcentAAoPP;1


