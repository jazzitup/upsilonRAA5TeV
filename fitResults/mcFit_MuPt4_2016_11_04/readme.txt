
//////////////////////////////////////////////////
//  Directory name: mcFit_MuPt4_2016_11_04      //
//  Created on Nov 30th by Jaebom Park          //
//////////////////////////////////////////////////

Files exist in KU server /home/samba/UpsilonAnalysis/fitResultFiles/mcFit_MuPt4_2016_11_04
Excute this command : mcFit_MuPt4_2016_11_04
cp /home/samba/UpsilonAnalysis/fitResultFiles/mcFit_MuPt4_2016_11_04/*.root .

Signal PDF : 
- parameters are fixed by MC samples.  https://github.com/jazzitup/upsilonRAA5TeV/commit/2bf06dfa491af16dec97008b873f140185f4c7b9
- Free parameters : Yields of 1S, 2S, 3S and the mass of 1S 

Background PDF :
- Exp function for differential pT bins where ptLow > 5GeV.
- Erf*Exp function used for all other bins 

Binning :
-pt-
const int nPtBins1s  = 5;   double ptBin1s[nPtBins1s+1] = {0,2.5,5,8,15,30};
const int nPtBins2s  = 3;   double ptBin2s[nPtBins2s+1] = {0,5,15,30};
const int nPtBins3s  = 3;   double ptBin3s[nPtBins3s+1] = {0,5,15,30};
-y-
const int nYBins1S  = 6;   double yBin1S[nYBins1S+1] ={0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};
const int nYBins2S  = 2;   double yBin2S[nYBins2S+1] ={0, 1.2, 2.4};
const int nYBins3S  = 2;   double yBin3S[nYBins3S+1] ={0, 1.2, 2.4};
-centrality-
const int nCentBins1s  = 9;   double centBin1s[nCentBins1s+1] = {0,10,20,40,60,80,100,120,140,200};
const int nCentBins2s  = 9;   double centBin2s[nCentBins2s+1] = {0,10,20,40,60,80,100,120,140,200};
const int nCentBins3s  = 4;   double centBin3s[nCentBins3s+1] = {0,20,60,100,200};
