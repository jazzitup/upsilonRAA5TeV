#ifndef PsetCollection_h
#define PsetCollection_h

#include "cutsAndBin.h"


class  PSetUpsAndBkg { 
 public:
 PSetUpsAndBkg() :
  collId(0), muPtCut(0), ptLow(0), ptHigh(0), yLow(0), yHigh(0), cLow(0), cHigh(200),
    n1s_1(-1), n2s_1(0), n3s_1(0),
    n1s_2(0), n2s_2(0), n3s_2(0),
    alpha1s_1(0), alpha2s_1(0), alpha3s_1(0),
    alpha1s_2(0), alpha2s_2(0), alpha3s_2(0),
    sigma1s_1(0), sigma2s_1(0), sigma3s_1(0),
    sigma1s_2(0), sigma2s_2(0), sigma3s_2(0),
    mean1s(0), mean2s(0), mean3s(0),
    f1s(0), f2s(0), f3s(0),
    x1s(0),
    //    MCn(0), MCalpha(0), MCsigma1S(0), MCsigma2S(0), MCsigma3S(0), MCm0(0), MCf(0), MCx(0),
    
    bkg_mu(0), bkg_sigma(0), bkg_lambda(0),
    // Only For Systematics
    bkg_mu1(0), bkg_sigma1(0), bkg_lambda1(0), bkg_mu2(0), bkg_sigma2(0), bkg_lambda2(0), rBkg2over1(0), // double ErrFunction
    ch3_k1(0), ch3_k2(0), ch3_k3(0),
    ch4_k1(0), ch4_k2(0), ch4_k3(0), ch4_k4(0),
    nSignal1s(0), nSignal2s(0), nSignal3s(0), nBkg(0),
    bkg4_mu(0), bkg4_sigma(0), bkg4_lambda(0),  bkg4_lambda2(0), rBkg42over1(0) //bkg4 = exp + err*exp
    
    {}
  
  int collId;
  float muPtCut;
  float ptLow;
  float ptHigh;
  float yLow;
  float yHigh;
  int cLow;
  int cHigh;

  float mean1s;
  float mean2s;  float mean3s;

  float n1s_1;
  float n1s_2;
  float alpha1s_1;
  float alpha1s_2;
  float sigma1s_1;
  float sigma1s_2;
  float n2s_1;
  float n2s_2;
  float alpha2s_1;
  float alpha2s_2;
  float sigma2s_1;
  float sigma2s_2;
  float n3s_1;
  float n3s_2;
  float alpha3s_1;
  float alpha3s_2;
  float sigma3s_1;
  float sigma3s_2;
  float x1s;

  float f1s; 
  float f2s; 
  float f3s; 


  //  float MCn, MCalpha, MCsigma1S, MCsigma2S, MCsigma3S, MCm0, MCf, MCx;
  float bkg_mu, bkg_sigma, bkg_lambda;

  float bkg_mu1, bkg_sigma1, bkg_lambda1, bkg_mu2, bkg_sigma2, bkg_lambda2, rBkg2over1; // double ErrFunction
  float ch3_k1, ch3_k2, ch3_k3 ; 
  float ch4_k1, ch4_k2, ch4_k3, ch4_k4 ; 

  float nSignal1s, nSignal2s, nSignal3s, nBkg;

  float bkg4_mu, bkg4_sigma, bkg4_lambda, bkg4_lambda2, rBkg42over1;

  void setKine(int collId_, float muPtCut_, float ptLow_, float ptHigh_, float yLow_, float yHigh_, int cLow_, int cHigh_)
  {
    collId = collId_;    muPtCut = muPtCut_;
    ptLow  = ptLow_;     ptHigh  = ptHigh_;
    yLow   = yLow_;      yHigh   = yHigh_;
    cLow   = cLow_;      cHigh   = cHigh_;
    cout << " collId : " << getCollID( collId) << endl;
    cout << " pT     : " << ptLow << " - " << ptHigh << "GeV/c" << endl;
    cout << " y      : " << yLow << " - " << yHigh << "" << endl;
    cout << " cBin   : " << cLow << " - " << cHigh << "" << endl;
    cout << " Muon pT > " << muPtCut << endl;
  }

  void setParBkg(float bkg_mu_, float bkg_sigma_, float bkg_lambda_)
  {
    bkg_mu = bkg_mu_; bkg_sigma = bkg_sigma_; bkg_lambda = bkg_lambda_;
  }
  
  void setSignalParMC(float MCn_, float MCalpha_, float MCsigma1S_, float MCm0_, float MCf_, float MCx_)
  {
    n1s_1 = MCn_ ;    n2s_1 = MCn_ ;    n3s_1 = MCn_ ;
    n1s_2 = MCn_ ;    n2s_2 = MCn_ ;    n3s_2 = MCn_ ;
    alpha1s_1 = MCalpha_ ;     alpha2s_1 = MCalpha_ ;     alpha3s_1 = MCalpha_ ; 
    alpha1s_2 = MCalpha_ ;     alpha2s_2 = MCalpha_ ;     alpha3s_2 = MCalpha_ ; 
    sigma1s_1 = MCsigma1S_ ;         sigma2s_1 = MCsigma1S_ * (pdgMass.Y2S/pdgMass.Y1S) ;     sigma3s_1 = MCsigma1S_ * (pdgMass.Y3S/pdgMass.Y1S) ; 
    sigma1s_2 = sigma1s_1*MCx_ ;     sigma2s_2 = sigma2s_1*MCx_ ;  sigma3s_2 = sigma3s_1*MCx_  ;
    mean1s  = MCm0_ ;   mean2s  = MCm0_ * (pdgMass.Y2S/pdgMass.Y1S);  mean3s  = MCm0_ * (pdgMass.Y3S/pdgMass.Y1S); 
    f1s = MCf_;     f2s= MCf_;    f3s= MCf_;
  }

  void setSignalParPPDATA(float MCn_, float MCalpha_, float MCsigma1S_, float MCm0_, float MCf_, float MCx_)
  {
    n1s_1 = MCn_ ;
    alpha1s_1 = MCalpha_ ;  sigma1s_1 = MCsigma1S_ ;  sigma2s_1 = MCsigma1S_ * (pdgMass.Y2S/pdgMass.Y1S) ;  sigma3s_1 = MCsigma1S_ * (pdgMass.Y3S/pdgMass.Y1S) ; 
    sigma1s_2 = sigma1s_1*MCx_ ;     sigma2s_2 = sigma2s_1*MCx_ ;      sigma3s_2 = sigma3s_1*MCx_  ;
    mean1s  = MCm0_ ;   mean2s  = MCm0_ * (pdgMass.Y2S/pdgMass.Y1S);  mean3s  = MCm0_ * (pdgMass.Y3S/pdgMass.Y1S); 
    f1s = MCf_;     f2s= MCf_;    f3s= MCf_;
    x1s = MCx_;
  }

  void setParBkg2ErrExp(float bkg_mu1_, float bkg_sigma1_, float bkg_lambda1_, float bkg_mu2_, float bkg_sigma2_, float bkg_lambda2_, float rBkg2over1_)
  {
    bkg_mu1 = bkg_mu1_;  bkg_sigma1 = bkg_sigma1_;  bkg_lambda1 = bkg_lambda1_;
    bkg_mu2 = bkg_mu2_;  bkg_sigma2 = bkg_sigma2_;  bkg_lambda2 = bkg_lambda2_; rBkg2over1 = rBkg2over1_;
  }

  void setParBkgErrExpExp(float bkg4_mu_, float bkg4_sigma_, float bkg4_lambda_, float bkg4_lambda2_, float rBkg42over1_)
  {
    bkg4_mu = bkg4_mu_;  bkg4_sigma = bkg4_sigma_;  bkg4_lambda = bkg4_lambda_;
    bkg4_lambda2 = bkg4_lambda2_; rBkg42over1 = rBkg42over1_;
  }
  
  void setParBkgPol3(float k1_, float k2_, float k3_) 
  {
    ch3_k1 = k1_ ;      ch3_k2 = k2_ ;       ch3_k3 = k3_ ;
  }

  void setParBkgPol4(float k1_, float k2_, float k3_, float k4_) 
  {
    ch4_k1 = k1_ ;      ch4_k2 = k2_ ;       ch4_k3 = k3_ ;   ch4_k4 = k4_;
  }

  void setSig1sF21NBkg(float sig1s_, float f21_, float nBkg_)
  {
    nSignal1s = sig1s_;
    nSignal2s = sig1s_ * f21_;
    nBkg = nBkg_;
  }
  
  
  
  void reset() {
    n1s_1 = -1 ;  n1s_2 = 0 ;  n2s_1 = 0 ;  n2s_2 = 0 ;  n3s_1 = 0 ;  n3s_2 =0 ; 
    alpha1s_1 = 0 ;  alpha1s_2 = 0 ;  alpha2s_1 = 0 ;  alpha2s_2 = 0 ;  alpha3s_1 = 0 ;  alpha3s_2 = 0 ;
    sigma1s_1 = 0 ;  sigma1s_2 = 0 ;  sigma2s_1 = 0 ;  sigma2s_2 = 0 ;  sigma3s_1 = 0 ;  sigma3s_2 = 0 ;
    //    MCn = 0 ;  MCalpha = 0 ;  MCsigma1S = 0 ;  MCsigma2S = 0 ;  MCsigma3S = 0 ;  MCm0 = 0 ;  MCf = 0 ;  MCx = 0 ;
    bkg_mu = 0; bkg_sigma = 0; bkg_lambda = 0;
    bkg_mu1 = 0; bkg_sigma1 = 0; bkg_lambda1 = 0; bkg_mu2 = 0; bkg_sigma2 = 0; bkg_lambda2=0; rBkg2over1=0; // double ErrFunction
    ch3_k1 = 0; ch3_k2 = 0; ch3_k3=0 ;
    ch4_k1 = 0; ch4_k2 = 0; ch4_k3=0 ; ch4_k4=0;
    nSignal1s=0; nSignal2s=0; nSignal3s=0; nBkg=0;
    bkg4_mu = 0; bkg4_sigma = 0; bkg4_lambda = 0; bkg4_lambda2 = 0; rBkg42over1=0;
    
  }

  void SetMCSgl();
  void SetParPPDATASgl();
  void SetMCBkg();
  bool binMatched( float muonPtCut_, float ptLow_, float ptHigh_, float yLow_, float yHigh_, int cLow_=-1, int cHigh_=-1); 
  
};


PSetUpsAndBkg getUpsilonPsets( int collId = kPPDATA,
			       float ptLow=5, float ptHigh=100,
			       float yLow=1.2, float yHigh=2.4,
			       int cLow=0, int cHigh=200,
			       float muPtCut=4
			       )
{ 
  PSetUpsAndBkg ret;
  ret.setKine( collId, muPtCut, ptLow, ptHigh, yLow, yHigh, cLow, cHigh) ;
  return ret;
}


void PSetUpsAndBkg::SetMCBkg() {
  if(collId == kPPDATA || collId == kPPMC || collId == kPPMCUps1S || collId == kPPMCUps2S || collId == kPPMCUps3S)   {
    //Integrated Bin // No centrlaity dependence 
    if ( (muPtCut==4) && (ptLow == 0 ) && (ptHigh == 30 ) && (yLow == 0 ) && (yHigh == 2.4 ) )      
      {      setParBkg(8.52,1.28,7.95);    }

    else 
      {      setParBkg(7.86,1.02,6.08);}

  }
  else {  // pp
    if ( (muPtCut==4) && (ptLow == 0 ) && (ptHigh == 30 ) && (yLow == 0 ) && (yHigh == 2.4 ) )      
      {      setParBkg(7.86,1.02,6.08);}
    else 
      {      setParBkg(7.86,1.02,6.08);}
  }


}

void PSetUpsAndBkg::SetParPPDATASgl() {

    cout << " ///////////////////////////////////////////" << endl;
    cout << " Fixing the Parameters from PP Data..." << endl;
    cout << " ///////////////////////////////////////////" << endl;
    cout << " muPtCut = " << muPtCut << endl;
    cout << " ptLow = " << ptLow << endl;
    cout << " ptHigh = " << ptHigh << endl;
    cout << " yLow = " << yLow << endl;
    cout << " yHigh = " << yHigh << endl;

    if ( collId == kAADATA) {

if ( binMatched( 4, 0, 2, 0, 1.2) )   { setSignalParPPDATA( 1.62853, 1.88891, 0.113022, 9.4588, 0.276787, 0.534744 );} 
    }
}


void PSetUpsAndBkg::SetMCSgl() 
{
  
  /*    cout << " ///////////////////////////////////////////" << endl;
    cout << " MC signal PDFs are not defined for this bin" << endl; 
    cout << " ///////////////////////////////////////////" << endl;
  */
    cout << " ///////////////////////////////////////////" << endl;
    cout << " Fixing the Parameters..." << endl;
    cout << " ///////////////////////////////////////////" << endl;
    cout << " muPtCut = " << muPtCut << endl;
    cout << " ptLow = " << ptLow << endl;
    cout << " ptHigh = " << ptHigh << endl;
    cout << " yLow = " << yLow << endl;
    cout << " yHigh = " << yHigh << endl;
    
// mcFit_MuPt4_2016_11_30
if ( collId == kPPDATA) 
{
  //Bin for 1S 
  if ( binMatched( 4, 0, 2.5, 0, 2.4) )   { setSignalParMC( 3.4916, 1.564, 0.0656761, 9.45756, 0.54466, 1.97011);} 
  if ( binMatched( 4, 2.5, 5, 0, 2.4) )   { setSignalParMC( 3.35845, 1.63789, 0.0716633, 9.45802, 0.63576, 1.9029);} 
  if ( binMatched( 4, 5, 8, 0, 2.4) )   { setSignalParMC(  3.19046  ,  1.43575  ,  0.0730977  ,  9.45723  ,  0.639965  ,  1.78201);} 
  if ( binMatched( 4, 8, 15, 0, 2.4) )   { setSignalParMC(3.29824  ,  1.60905  ,  0.0678905  ,  9.45453  ,  0.537631  ,  1.87837 );} 
  if ( binMatched( 4, 15, 30, 0, 2.4) )   { setSignalParMC(3.25139  ,  1.60934  ,  0.0676854  ,  9.45591  ,  0.520767  ,  1.86066 );} 
  if ( binMatched( 4, 0, 30, 0, 0.4) )   { setSignalParMC(1.36109,  1.90884  ,  0.0889045  ,  9.4581  ,  0.189231  ,  0.608914 );} 
  if ( binMatched( 4, 0, 30, 0.4, 0.8) )   { setSignalParMC(2.30895  ,  1.75606  ,  0.0942427  ,  9.45866  ,  0.355442  ,  0.664363 );} 
  if ( binMatched( 4, 0, 30, 0.8, 1.2) )   { setSignalParMC(1.62317  ,  1.98761  ,  0.0777123  ,  9.45557  ,  0.497941  ,  1.45039 );} 
  if ( binMatched( 4, 0, 30, 1.2, 1.6) )   { setSignalParMC(1.38009  ,  2.12727  ,  0.0781824  ,  9.45002  ,  0.239506  ,  1.61113 );} 
  if ( binMatched( 4, 0, 30, 1.6, 2.0) )   { setSignalParMC(1.77962  ,  1.98774  ,  0.0726482  ,  9.45001  ,  0.0954821  ,  1.92647 );} 
  if ( binMatched( 4, 0, 30, 2.0, 2.4) )   { setSignalParMC(1.77998  ,  2.03591  ,  0.0864709  ,  9.45  ,  0.0852784  ,  1.99843 );} 
  if ( binMatched( 4, 0, 30, 0, 2.4) )   { setSignalParMC(3.30732  ,  1.60069  ,  0.0667393  ,  9.45626  ,  0.535528  ,  1.92417 );} 
  //Bin for 2S & 3S 
  if ( binMatched( 4, 0, 5, 0, 2.4) )   { setSignalParMC( 3.76, 1.59235, 0.0648477, 9.45739, 0.521473, 1.97614);} 
  if ( binMatched( 4, 5, 15, 0, 2.4) )   { setSignalParMC( 3.78201, 1.54632, 0.128471, 9.45551, 0.446142, 0.531346);} 
  if ( binMatched( 4, 0, 30, 0, 1.2) )   { setSignalParMC( 2.99101, 1.65623, 0.0981835, 9.45822, 0.419242, 0.605439);} 
  if ( binMatched( 4, 0, 30, 1.2, 2.4) )   { setSignalParMC(2.54509, 1.89829, 0.107104, 9.44942, 0.609942, 1.55899);} 
}

else if (collId == kAADATA ) 
{ 

  if ( binMatched( 4, 0, 2, 0, 1.2, 0, 200) )   { setSignalParMC( 1.87382, 1.7535, 0.133795, 9.45903, 0.176018, 0.47446 );} 
  if ( binMatched( 4, 0, 2, 0, 2.4, 0, 200) )   { setSignalParMC( 3.00077, 1.56049, 0.147722, 9.45643, 0.387037, 0.468021 );} 
  if ( binMatched( 4, 0, 2, 1.2, 2.4, 0, 200) )   { setSignalParMC( 2.84835, 1.81252, 0.107225, 9.44812, 0.569859, 1.57698 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 0, 10) )   { setSignalParMC( 1.4, 1.8848, 0.209259, 9.45428, 0.0546851, 0.367979 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 0, 200) )   { setSignalParMC( 1.4, 1.87599, 0.140632, 9.45751, 0.143446, 0.488646 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 0, 20) )   { setSignalParMC( 1.4, 1.8987, 0.18483, 9.45527, 0.0811643, 0.404133 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 100, 140) )   { setSignalParMC( 1.4, 1.8812, 0.126496, 9.45783, 0.171577, 0.535507 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 100, 200) )   { setSignalParMC( 1.4, 1.87403, 0.124636, 9.45791, 0.192826, 0.53197 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 10, 20) )   { setSignalParMC( 1.4, 1.91788, 0.172778, 9.45614, 0.105539, 0.420515 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 140, 200) )   { setSignalParMC( 1.43896, 1.8496, 0.123806, 9.45804, 0.204764, 0.527356 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 20, 40) )   { setSignalParMC( 1.4, 1.83787, 0.167216, 9.45625, 0.101862, 0.424696 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 20, 60) )   { setSignalParMC( 1.42304, 1.84753, 0.168195, 9.4568, 0.103706, 0.421217 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 40, 60) )   { setSignalParMC( 1.4725, 1.84621, 0.169442, 9.4574, 0.104732, 0.417121 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 60, 100) )   { setSignalParMC( 1.43643, 1.87768, 0.12819, 9.45827, 0.198853, 0.517033 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 60, 80) )   { setSignalParMC( 1.4, 1.90558, 0.129942, 9.4582, 0.190331, 0.518027 );} 
  if ( binMatched( 4, 0, 30, 0, 1.2, 80, 100) )   { setSignalParMC( 1.80361, 1.70733, 0.129831, 9.45904, 0.177319, 0.507051 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 0, 10) )   { setSignalParMC( 1.4, 1.9122, 0.191621, 9.45206, 0.173891, 0.440485 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 0, 200) )   { setSignalParMC( 1.69964, 1.77511, 0.0755651, 9.45531, 0.689178, 2 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 0, 20) )   { setSignalParMC( 1.52928, 1.8635, 0.177054, 9.45295, 0.224649, 0.462429 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 100, 140) )   { setSignalParMC( 1.79531, 1.72637, 0.150678, 9.45585, 0.296962, 0.500357 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 100, 120) )   { setSignalParMC( 1.74884, 1.71142, 0.151646, 9.45659, 0.287537, 0.502704 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 120, 140) )   { setSignalParMC( 8.09813, 1.83774, 0.112249, 9.46768, 0.684498, 0.596525 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 140, 200) )   { setSignalParMC( 1.88489, 1.71471, 0.151802, 9.45646, 0.314014, 0.480043 );}
if ( binMatched( 4, 0, 30, 0, 2.4, 100, 200) )   { setSignalParMC( 1.83326, 1.72439, 0.15152, 9.45617, 0.305819, 0.488636 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 10, 20) )   { setSignalParMC( 1.80275, 1.76528, 0.166017, 9.45408, 0.277986, 0.475633 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 140, 200) )   { setSignalParMC( 1.88489, 1.71471, 0.151802, 9.45646, 0.314014, 0.480043 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 20, 40) )   { setSignalParMC( 1.4, 1.87189, 0.154638, 9.45424, 0.353324, 0.477214 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 20, 60) )   { setSignalParMC( 1.43695, 1.87175, 0.158526, 9.45439, 0.315429, 0.476002 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 40, 60) )   { setSignalParMC( 1.80796, 1.74444, 0.164314, 9.45509, 0.266865, 0.469177 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 60, 100) )   { setSignalParMC( 1.8286, 1.74716, 0.151205, 9.45527, 0.321917, 0.487219 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 60, 80) )   { setSignalParMC( 1.41857, 1.90465, 0.145864, 9.45456, 0.373455, 0.495038 );} 
if ( binMatched( 4, 0, 30, 0, 2.4, 80, 100) )   { setSignalParMC( 2.34323, 1.59446, 0.158451, 9.45607, 0.269753, 0.472772 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 0, 10) )   { setSignalParMC( 1.73494, 1.92527, 0.209248, 9.44639, 0.242522, 0.535901 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 0, 200) )   { setSignalParMC( 1.41003, 2.00629, 0.112223, 9.44742, 0.711461, 1.6666 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 0, 20) )   { setSignalParMC( 1.57642, 1.98232, 0.112863, 9.44539, 0.68162, 1.69033 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 100, 140) )   { setSignalParMC( 1.60785, 1.94118, 0.114232, 9.44649, 0.737047, 1.61103 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 100, 200) )   { setSignalParMC( 1.68845, 1.9192, 0.112558, 9.44864, 0.752671, 1.70174 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 10, 20) )   { setSignalParMC( 1.40001, 2.0564, 0.175533, 9.44412, 0.440965, 0.637109 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 140, 200) )   { setSignalParMC( 1.71388, 1.91604, 0.197062, 9.45013, 0.238797, 0.565235 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 20, 40) )   { setSignalParMC( 1.4, 1.93748, 0.117229, 9.4502, 0.666467, 1.50969 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 20, 60) )   { setSignalParMC( 1.4, 1.98012, 0.121742, 9.44832, 0.836787, 1.73336 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 40, 60) )   { setSignalParMC( 1.4, 2.02126, 0.221548, 9.44666, 0.151224, 0.540242 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 60, 100) )   { setSignalParMC( 1.4, 2.02613, 0.18111, 9.44519, 0.338002, 0.604519 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 60, 80) )   { setSignalParMC( 1.4, 1.99449, 0.163884, 9.44534, 0.484761, 0.640275 );} 
if ( binMatched( 4, 0, 30, 1.2, 2.4, 80, 100) )   { setSignalParMC( 1.4, 2.06813, 0.197481, 9.44499, 0.272148, 0.559502 );} 
if ( binMatched( 4, 0, 8, 0, 1.2, 0, 200) )   { setSignalParMC( 1.44553, 1.87602, 0.138536, 9.45848, 0.152025, 0.481029 );} 
if ( binMatched( 4, 0, 8, 0, 2.4, 0, 200) )   { setSignalParMC( 1.83812, 1.75308, 0.0750351, 9.45597, 0.684583, 2 );} 
if ( binMatched( 4, 0, 8, 1.2, 2.4, 0, 200) )   { setSignalParMC( 1.43453, 2.02868, 0.112486, 9.44779, 0.738093, 1.68743 );} 
if ( binMatched( 4, 12, 16, 0, 1.2, 0, 200) )   { setSignalParMC( 1.4, 1.828, 0.142583, 9.45534, 0.120182, 0.51278 );} 
if ( binMatched( 4, 12, 16, 0, 2.4, 0, 200) )   { setSignalParMC( 1.49314, 1.8165, 0.151598, 9.45351, 0.308639, 0.505341 );} 
if ( binMatched( 4, 12, 16, 1.2, 2.4, 0, 200) )   { setSignalParMC( 1.59404, 1.91437, 0.173434, 9.44724, 0.402789, 0.631758 );} 
if ( binMatched( 4, 16, 30, 0, 1.2, 0, 200) )   { setSignalParMC( 1.4, 1.88285, 0.135616, 9.45659, 0.145197, 0.533648 );} 
if ( binMatched( 4, 16, 30, 0, 2.4, 0, 200) )   { setSignalParMC( 1.57051, 1.8165, 0.156268, 9.45472, 0.299207, 0.497759 );} 
if ( binMatched( 4, 16, 30, 1.2, 2.4, 0, 200) )   { setSignalParMC( 1.4, 1.95689, 0.18684, 9.44768, 0.31283, 0.619659 );} 
if ( binMatched( 4, 2, 4, 0, 1.2, 0, 200) )   { setSignalParMC( 1.54606, 1.84952, 0.151525, 9.45972, 0.113304, 0.449174 );} 
if ( binMatched( 4, 2, 4, 0, 2.4, 0, 200) )   { setSignalParMC( 2.1189, 1.69287, 0.163553, 9.45683, 0.249224, 0.470955 );} 
if ( binMatched( 4, 2, 4, 1.2, 2.4, 0, 200) )   { setSignalParMC( 1.61126, 2.00828, 0.116676, 9.44802, 0.870378, 2 );} 
if ( binMatched( 4, 4, 6, 0, 1.2, 0, 200) )   { setSignalParMC( 1.4, 1.87247, 0.135808, 9.45678, 0.166981, 0.483843 );} 
if ( binMatched( 4, 4, 6, 0, 2.4, 0, 200) )   { setSignalParMC( 1.56872, 1.83577, 0.159341, 9.45443, 0.280195, 0.474883 );} 
if ( binMatched( 4, 4, 6, 1.2, 2.4, 0, 200) )   { setSignalParMC( 1.4, 2.05417, 0.109823, 9.4469, 0.683026, 1.67064 );} 
if ( binMatched( 4, 6, 8, 0, 1.2, 0, 200) )   { setSignalParMC( 1.45507, 1.83642, 0.141928, 9.45903, 0.121286, 0.49349 );} 
if ( binMatched( 4, 6, 8, 0, 2.4, 0, 200) )   { setSignalParMC( 1.40816, 1.84988, 0.148261, 9.45638, 0.330225, 0.498801 );} 
if ( binMatched( 4, 6, 8, 1.2, 2.4, 0, 200) )   { setSignalParMC( 1.4, 1.88845, 0.178737, 9.44968, 0.304058, 0.621711 );} 
if ( binMatched( 4, 8, 12, 0, 1.2, 0, 200) )   { setSignalParMC( 1.4, 1.84154, 0.152212, 9.45613, 0.115213, 0.471258 );} 
if ( binMatched( 4, 8, 12, 0, 2.4, 0, 200) )   { setSignalParMC( 1.5064, 1.79577, 0.15858, 9.45429, 0.281655, 0.47772 );} 
if ( binMatched( 4, 8, 12, 1.2, 2.4, 0, 200) )   { setSignalParMC( 1.4, 1.94074, 0.109719, 9.44621, 0.655788, 1.66955 );} 
if ( binMatched( 4, 8, 30, 0, 1.2, 0, 200) )   { setSignalParMC( 1.4, 1.8467, 0.146437, 9.45603, 0.120394, 0.493926 );} 
if ( binMatched( 4, 8, 30, 0, 2.4, 0, 200) )   { setSignalParMC( 1.5144, 1.8069, 0.156276, 9.45417, 0.291956, 0.489308 );} 
if ( binMatched( 4, 8, 30, 1.2, 2.4, 0, 200) )   { setSignalParMC( 1.4, 1.95467, 0.181023, 9.44673, 0.355888, 0.612626 );} 
if ( binMatched( 4, 15, 30, 0, 2.4, 0, 200) )   { setSignalParMC( 1.53263, 1.81915, 0.157427, 9.45439, 0.289664, 0.497107 );} 
 
 

    }
}



bool PSetUpsAndBkg::binMatched( float muonPtCut_, float ptLow_, float ptHigh_, float yLow_, float yHigh_, int cLow_, int cHigh_) {
  if ( (float)muonPtCut_ != (float)muPtCut )
    return false;
  if  ( (float)ptLow_ != (float)ptLow )
    return false;
  if ( (float)ptHigh_ != (float)ptHigh ) 
    return false;
  if ( (float)yLow_ != (float)yLow )
    return false;
  if ( (float)yHigh_ != (float)yHigh ) 
    return false;
  if ( (cLow_>0) &&  ( (int)cLow_ != (int)cLow ) )
    return false;
  if ( (cHigh_>0) && ( (int)cHigh_ != (int)cHigh ) ) 
    return false;

  return true;

    
}

#endif


