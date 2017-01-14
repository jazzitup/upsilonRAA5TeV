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
    nSignal1s(0), nSignal2s(0), nSignal3s(0), nBkg(0), bkg_mass_res(0), bkg_mu_res(0), bkg_sigma_res(0), bkg_lambda_res(0),
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
  float bkg_mass_res,bkg_mu_res, bkg_sigma_res, bkg_lambda_res;

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
    f1s = MCf_;     f2s= MCf_;    f3s= MCf_;   x1s = MCx_;
  }

  void setToyMCInit(float nSignal1s_, float nSignal2s_, float nSignal3s_, float nBkg_, float bkg_mass_res_, float bkg_mu_res_, float bkg_sigma_res_, float bkg_lambda_res_)
  {
    nSignal1s = nSignal1s_; nSignal2s = nSignal2s_; nSignal3s = nSignal3s_; nBkg = nBkg_;
    bkg_mass_res = bkg_mass_res_; bkg_mu_res = bkg_mu_res_; bkg_sigma_res = bkg_sigma_res_; bkg_lambda_res = bkg_lambda_res_;
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
    nSignal1s=0; nSignal2s=0; nSignal3s=0; nBkg=0; bkg_mass_res=0; bkg_mu_res=0; bkg_sigma_res=0; bkg_lambda_res=0;
    bkg4_mu = 0; bkg4_sigma = 0; bkg4_lambda = 0; bkg4_lambda2 = 0; rBkg42over1=0;
    
  }

  void SetMCSgl();
  void SetMCSgl_CBGaus();
  void SetParPPDATASgl();
  void SetMCBkg();
  void SetToyMCParm();

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
  if ( binMatched( 4, 0, 2, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 2, 4, 0, 2.4) )   { setSignalParMC( 2.54841, 1.6812, 0.066532, 9.45719, 0.553098, 1.98314);} 
  if ( binMatched( 4, 4, 6, 0, 2.4) )   { setSignalParMC( 1.812, 1.77155, 0.0650865, 9.45745, 0.535116, 2.02773);} 
  if ( binMatched( 4, 6, 9, 0, 2.4) )   { setSignalParMC(1.90782, 1.68497, 0.0676252, 9.45505, 0.555618, 1.94159);} 
  if ( binMatched( 4, 9, 12, 0, 2.4) )   { setSignalParMC( 2.49551, 1.69633, 0.0653693, 9.45451, 0.501293, 1.92911);} 
  if ( binMatched( 4, 12, 30, 0, 2.4) )   { setSignalParMC(3.45418, 1.58837, 0.0691117, 9.4553, 0.543504, 1.83387);} 
  if ( binMatched( 4, 0, 4, 0, 2.4) ) { setSignalParMC( 2.30508, 1.84253, 0.0674275, 9.45702, 0.560549, 1.96373 );} 
  if ( binMatched( 4, 4, 9, 0, 2.4) ) { setSignalParMC( 2.38183, 1.7319, 0.0667538, 9.45599, 0.525199, 1.86566 );} 
  if ( binMatched( 4, 9, 30, 0, 2.4) ) { setSignalParMC( 3.67359, 1.64528, 0.0677543, 9.45487, 0.537117, 1.89586 );} 
  if ( binMatched( 4, 0, 6, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 6, 30, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 0, 0.8) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 0.8, 1.6) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 1.6, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 

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
 
  if ( binMatched( 4, 0, 2, 0, 2.4) )   { setSignalParMC( 2.33998, 1.71975, 0.0675697, 9.45611, 0.558206, 2.04994);} 
  if ( binMatched( 4, 2, 4, 0, 2.4) )   { setSignalParMC( 2.24068, 1.73474, 0.0673883, 9.45633, 0.524329, 1.85168);} 
  if ( binMatched( 4, 4, 6, 0, 2.4) )   { setSignalParMC( 3.20392, 1.62361, 0.0746982, 9.45504, 0.708621, 2.03588 );}
  if ( binMatched( 4, 6, 9, 0, 2.4) ) { setSignalParMC( 1.48094, 1.78538, 0.0670799, 9.45596, 0.515644, 1.89523 );}
  if ( binMatched( 4, 9, 12, 0, 2.4) ) { setSignalParMC( 3.30011, 1.53221, 0.0675289, 9.45471, 0.55445, 1.89932 );}
  if ( binMatched( 4, 12, 30, 0, 2.4) ) { setSignalParMC( 3.9619, 1.51001, 0.0722908, 9.45505, 0.600787, 1.85532 );}
  if ( binMatched( 4, 0, 4, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 4, 9, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 9, 30, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 6, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 6, 30, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 0, 0.8) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 0.8, 1.6) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 1.6, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 

  //for pt bin
if ( binMatched( 4, 0, 2.5, 0, 2.4) )   { setSignalParMC( 3.45481, 1.59633, 0.0736743, 9.45525, 0.608694, 1.73631 );}
if ( binMatched( 4, 2.5, 5, 0, 2.4) )   { setSignalParMC( 3.40773, 1.62957, 0.0736023, 9.45613, 0.648529, 1.76715 );}
if ( binMatched( 4, 5, 8, 0, 2.4) )     { setSignalParMC( 3.72, 1.69586, 0.0676078, 9.45589, 0.553222, 1.90002 );}
if ( binMatched( 4, 8, 15, 0, 2.4) )    { setSignalParMC( 3.23, 1.51628, 0.0686302, 9.45512, 0.56218, 1.8871 );}
if ( binMatched( 4, 15, 30, 0, 2.4) )   { setSignalParMC( 3.3, 1.56701, 0.0734659, 9.45512, 0.612436, 1.85341 );}
if ( binMatched( 4, 0, 30, 0, 2.4) )    { setSignalParMC( 3.19451, 1.55708, 0.0684966, 9.45589, 0.560898, 1.90076 );}
if ( binMatched( 4, 0, 5, 0, 2.4) )     { setSignalParMC( 3.714, 1.70183, 0.0736797, 9.45614, 0.55781, 1.61859 );}
if ( binMatched( 4, 5, 15, 0, 2.4) )    { setSignalParMC( 3.72, 1.52551, 0.0683189, 9.45571, 0.563272, 1.89665 );}
//for eta bin
if ( binMatched( 4, 0, 30, 0, 0.4) )    { setSignalParMC( 1.53865, 1.88391, 0.0702923, 9.45862, 0.545296, 0.685079 );}
if ( binMatched( 4, 0, 30, 0.4, 0.8) )  { setSignalParMC( 1.92388, 1.84344, 0.0951642, 9.45858, 0.328146, 0.6797 );}
if ( binMatched( 4, 0, 30, 0.8, 1.2) )  { setSignalParMC( 3.49665, 1.75969, 0.071481, 9.45411, 0.335342, 1.49306 );}
if ( binMatched( 4, 0, 30, 1.2, 1.6) )  { setSignalParMC( 3.54659, 1.79847, 0.107393, 9.45, 0.87389, 1.59254 );}
if ( binMatched( 4, 0, 30, 1.6, 2.0) )  { setSignalParMC( 1.65287, 2.063, 0.0727294, 9.45, 0.0836645, 1.94962 );}
if ( binMatched( 4, 0, 30, 2.0, 2.4) )  { setSignalParMC( 1.22102, 2.05874, 0.0874083, 9.4581, 0.0987932, 1.99991 );}
if ( binMatched( 4, 0, 30, 0, 1.2) )    { setSignalParMC( 1.92198, 1.75, 0.0971168, 9.45798, 0.437838, 0.611932 );}
if ( binMatched( 4, 0, 30, 1.2, 2.4) )  { setSignalParMC( 3.73744, 1.45492, 0.0980838, 9.45048, 0.40192, 1.47978 );}

    }
}

void PSetUpsAndBkg::SetMCSgl_CBGaus() 
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
  if ( binMatched( 4, 0, 2, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 2, 4, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 4, 6, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 6, 9, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 9, 12, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 12, 30, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 4, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 4, 9, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 9, 30, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 6, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 6, 30, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 0, 0.8) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 0.8, 1.6) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 1.6, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  
  //Bin for 1S 
if ( binMatched( 4, 0, 2.5, 0, 2.4) ) { setSignalParMC( 2.54917, 1.42834, 0.0635914, 9.45874, 0.550769, 1.97849 );}
if ( binMatched( 4, 2.5, 5, 0, 2.4) ) { setSignalParMC( 2.25675, 1.52031, 0.0678987, 9.45834, 0.604787, 1.93158 );}
if ( binMatched( 4, 5, 8, 0, 2.4) ) { setSignalParMC( 2.32471, 1.46647, 0.069625, 9.45746, 0.623759, 1.87018 );}
if ( binMatched( 4, 8, 15, 0, 2.4) ) { setSignalParMC( 2.96275, 1.37205, 0.068278, 9.45618, 0.590451, 1.84018 );}
if ( binMatched( 4, 15, 30, 0, 2.4) ) { setSignalParMC( 1.26121, 1.71552, 0.0694964, 9.45629, 0.579887, 1.8375 );}
if ( binMatched( 4, 0, 5, 0, 2.4) ) { setSignalParMC( 2.42309, 1.47628, 0.0660568, 9.45852, 0.581272, 1.9476 );}
if ( binMatched( 4, 5, 15, 0, 2.4) ) { setSignalParMC( 2.17838, 1.48911, 0.0681602, 9.45644, 0.584384, 1.84755 );}
if ( binMatched( 4, 0, 30, 0, 2.4) ) { setSignalParMC( 2.38608, 1.46817, 0.0677718, 9.45744, 0.59193, 1.88768 );}
if ( binMatched( 4, 0, 30, 0, 0.4) ) { setSignalParMC( 3.26941, 1.00226, 0.0814565, 9.45797, 0.306372, 0.649771 );}
if ( binMatched( 4, 0, 30, 0.4, 0.8) ) { setSignalParMC( 6.0228, 1.10246, 0.0915191, 9.45847, 0.392614, 0.693605 );}
if ( binMatched( 4, 0, 30, 0.8, 1.2) ) { setSignalParMC( 1.45606, 1.76583, 0.0805061, 9.45651, 0.584548, 1.39205 );}
if ( binMatched( 4, 0, 30, 1.2, 1.6) ) { setSignalParMC( 5.4975, 1.75295, 0.103362, 9.4511, 0.773069, 1.42089 );}
if ( binMatched( 4, 0, 30, 1.6, 2.0) ) { setSignalParMC( 1.29178, 1.1729, 0.0739975, 9.45059, 0.132347, 1.85865 );}
if ( binMatched( 4, 0, 30, 2, 2.4) ) { setSignalParMC( 1.04519, 1.39037, 0.0668717, 9.45001, 0.04459, 2.45326 );}
if ( binMatched( 4, 0, 30, 0, 1.2) ) { setSignalParMC( 5.93553, 1.3038, 0.0929776, 9.45749, 0.545774, 0.612201 );}
if ( binMatched( 4, 0, 30, 1.2, 2.4) ) { setSignalParMC( 2.44464, 1.8087, 0.105676, 9.45, 0.568479, 1.47023 );}

}

else if (collId == kAADATA ) 
{ 
  if ( binMatched( 4, 0, 2, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 2, 4, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 4, 6, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 6, 9, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 9, 12, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 12, 30, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 4, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 4, 9, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 9, 30, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 6, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 6, 30, 0, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 0, 0.8) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 0.8, 1.6) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
  if ( binMatched( 4, 0, 30, 1.6, 2.4) )   { setSignalParMC( 3.76996, 1.70039, 0.062522, 9.45683, 0.491621, 2.03249);} 
 
//for pt bin
if ( binMatched( 4, 0, 30, 0, 2.4) )   { setSignalParMC( 2.84517, 1.36894, 0.0684228, 9.45737, 0.602446, 1.85621 );}
if ( binMatched( 4, 0, 2.5, 0, 2.4) )   { setSignalParMC( 2.51572, 1.36038, 0.0660054, 9.45828, 0.575459, 1.94671 );}
if ( binMatched( 4, 2.5, 5, 0, 2.4) ) { setSignalParMC( 2.63763, 1.42659, 0.0689422, 9.45728, 0.604498, 1.80244 );}
if ( binMatched( 4, 5, 8, 0, 2.4) )  { setSignalParMC( 4.01878, 1.32223, 0.0681323, 9.45799, 0.612437, 1.87951 );}
if ( binMatched( 4, 8, 15, 0, 2.4) ) { setSignalParMC( 2.75442, 1.31236, 0.0681348, 9.45692, 0.605204, 1.85662 );}
if ( binMatched( 4, 15, 30, 0, 2.4) ) { setSignalParMC( 2.63653, 1.46321, 0.0735693, 9.45612, 0.645267, 1.80864 );}
if ( binMatched( 4, 0, 5, 0, 2.4) ) { setSignalParMC( 2.47191, 1.40481, 0.0673622, 9.45771, 0.584689, 1.86278 );}
if ( binMatched( 4, 5, 15, 0, 2.4) ) { setSignalParMC( 3.15578, 1.3226, 0.0681048, 9.45737, 0.607122, 1.86533 );}

if ( binMatched( 4, 0, 30, 0, 0.4) )   { setSignalParMC( 3.05697, 1.06017, 0.0754069, 9.45866, 0.326219, 0.715251 );}
if ( binMatched( 4, 0, 30, 0.4, 0.8) ) { setSignalParMC( 1.27276, 1.84114, 0.0648444, 9.4588, 0.694488, 1.46609 );}
if ( binMatched( 4, 0, 30, 0.8, 1.2) )   { setSignalParMC( 1.90975, 1.5204, 0.0761292, 9.45537, 0.471149, 1.42498 );}
if ( binMatched( 4, 0, 30, 1.2, 1.6) )   { setSignalParMC( 6.01133, 1.00139, 0.0839045, 9.45273, 0.297959, 1.44207 );}
if ( binMatched( 4, 0, 30, 1.6, 2) ) { setSignalParMC( 6.01654, 1.63034, 0.122955, 9.45, 0.734874, 1.34836 );}
if ( binMatched( 4, 0, 30, 2, 2.4) )   { setSignalParMC( 1.00114, 1.00121, 0.0677261, 9.44797, 0.11848, 2.49903 );}
if ( binMatched( 4, 0, 30, 0, 1.2) )   { setSignalParMC( 5.96691, 1.39766, 0.0877459, 9.45737, 0.664216, 0.602696 );}
if ( binMatched( 4, 0, 30, 1.2, 2.4) ) { setSignalParMC( 1.0824, 1.00126, 0.0534197, 9.45014, 0.108649, 2.46433 );}


    }
}

void PSetUpsAndBkg::SetToyMCParm() 
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
    
if ( collId == kPPDATA) 
{
if ( binMatched(4, 0.0, 2.5, 0.0, 2.4) ) { setToyMCInit( 8787.60156, 2714.99487, 1255.42358, 41374.85156, 9.45212, 8.94308, 0.59839, 4.74625);}
if ( binMatched(4, 2.5, 5.0, 0.0, 2.4) ) { setToyMCInit( 7920.85693, 2454.31494, 1179.68262, 37354.02344, 9.44922, 9.11122, 1.43811, 7.78604);}
if ( binMatched(4, 5.0, 8.0, 0.0, 2.4) ) { setToyMCInit( 7403.49609, 2248.46240, 1231.33862, 22024.79102, 9.44812, 0.00000, 0.00000, 30.00000);}
if ( binMatched(4, 8.0, 15.0, 0.0, 2.4) ) { setToyMCInit( 7946.65771, 2658.01050, 1505.69031, 18422.22852, 9.44962, 0.00000, 0.00000, 8.86557);}
if ( binMatched(4, 15.0, 30.0, 0.0, 2.4) ) { setToyMCInit( 2167.16113, 902.20294, 594.43304, 3285.24683, 9.44965, 0.00000, 0.00000, 8.30815);}
if ( binMatched(4, 0.0, 5.0, 0.0, 2.4) ) { setToyMCInit( 16715.07617, 5104.46094, 2342.41479, 78879.31250, 9.45068, 8.89156, 0.79458, 6.70718);}
if ( binMatched(4, 5.0, 15.0, 0.0, 2.4) ) { setToyMCInit( 15338.05469, 4891.37646, 2713.35229, 40497.90234, 9.44887, 0.00000, 0.00000, 14.99958);}

if ( binMatched(4, 0.0, 30.0, 0.0, 1.2) ) { setToyMCInit( 20260.52344, 6568.66992, 3492.37793, 78148.62500, 9.45233, 8.43426, 1.11866, 12.35094);}
if ( binMatched(4, 0.0, 30.0, 1.2, 2.4) ) { setToyMCInit( 14102.41992, 4503.78613, 2300.70898, 44050.91406, 9.44133, 8.54914, 0.97597, 4.93268);}

if ( binMatched(4, 0.0, 30.0, 0.0, 0.4) ) { setToyMCInit( 6587.65625, 2284.13452, 1191.21753, 26131.11523, 9.45249, 8.45934, 1.31364, 15.59483);}
if ( binMatched(4, 0.0, 30.0, 0.4, 0.8) ) { setToyMCInit( 6856.31543, 2181.42944, 1224.52417, 25960.85938, 9.45248, 8.44031, 1.09974, 12.58109);}
if ( binMatched(4, 0.0, 30.0, 0.8, 1.2) ) { setToyMCInit( 7063.11133, 2196.58789, 1123.73132, 25669.88086, 9.45090, 8.51231, 1.06307, 9.49988);}
if ( binMatched(4, 0.0, 30.0, 1.2, 1.6) ) { setToyMCInit( 6625.74561, 2055.74390, 1064.58093, 23680.09766, 9.44437, 8.49683, 1.01357, 6.78753);}
if ( binMatched(4, 0.0, 30.0, 1.6, 2.0) ) { setToyMCInit( 5449.15234, 1727.12720, 887.16187, 15629.86035, 9.43935, 8.75694, 0.97742, 3.61041);}
if ( binMatched(4, 0.0, 30.0, 2.0, 2.4) ) { setToyMCInit( 2046.47583, 767.99402, 357.53378, 4666.95654, 9.43000, 8.42560, 0.85059, 3.44582);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4) ) { setToyMCInit( 34294.19141, 11084.77441, 5811.50146, 122239.96875, 9.44997, 8.45268, 1.03453, 8.33689);}
}

else if (collId == kAADATA ) 
{ 
 
if ( binMatched(4, 0.0, 2.5, 0.0, 2.4, 0, 200) ) { setToyMCInit( 1190.03918, 168.89725, 88.25835, 23413.43750, 9.45282, 8.74222, 0.55795, 4.00166);}
if ( binMatched(4, 2.5, 5.0, 0.0, 2.4, 0, 200) ) { setToyMCInit( 1338.39221, 96.82811, 0.00012, 26309.92773, 9.45062, 8.28619, 1.29782, 5.43255);}
if ( binMatched(4, 5.0, 8.0, 0.0, 2.4, 0, 200) ) { setToyMCInit( 1254.41064, 162.45538, 3.75126, 25627.37695, 9.44322, 0.00000, 0.00000, 8.10481);}
if ( binMatched(4, 8.0, 15.0, 0.0, 2.4, 0, 200) ) { setToyMCInit( 1496.21875, 75.90561, 0.00003, 26781.83398, 9.45326, 0.00000, 0.00000, 9.50293);}
if ( binMatched(4, 15.0, 30.0, 0.0, 2.4, 0, 200) ) { setToyMCInit( 426.04391, 55.72250, 62.72536, 2129.63477, 9.44886, 0.00000, 0.00000, 14.86901);}
if ( binMatched(4, 0.0, 5.0, 0.0, 2.4, 0, 200) ) { setToyMCInit( 2536.39185, 240.36009, 23.34357, 49805.93750, 9.45078, 8.58516, 0.80494, 4.69116);}
if ( binMatched(4, 5.0, 15.0, 0.0, 2.4, 0, 200) ) { setToyMCInit( 2754.81616, 240.02965, 0.00070, 45952.50000, 9.44886, 0.00000, 0.00000, 8.75293);}

if ( binMatched(4, 0.0, 30.0, 0.0, 1.2, 0, 200) ) { setToyMCInit( 3574.91675, 394.41763, 19.84396, 76392.34375, 9.45242, 7.88447, 1.22887, 7.75138);}
if ( binMatched(4, 0.0, 30.0, 1.2, 2.4, 0, 200) ) { setToyMCInit( 2220.61328, 147.74796, 14.26492, 27918.38281, 9.44208, 8.22186, 1.02833, 3.35326);}

if ( binMatched(4, 0.0, 30.0, 0.0, 0.4, 0, 200) ) { setToyMCInit( 1172.02649, 132.71912, 0.00008, 27590.14062, 9.45096, 7.91838, 1.55620, 8.12529);}
if ( binMatched(4, 0.0, 30.0, 0.4, 0.8, 0, 200) ) { setToyMCInit( 1179.43250, 100.41032, 0.20346, 26158.93164, 9.45188, 7.86820, 1.18595, 8.08189);}
if ( binMatched(4, 0.0, 30.0, 0.8, 1.2, 0, 200) ) { setToyMCInit( 1236.29150, 185.00047, 107.79778, 22518.39062, 9.45368, 7.88839, 1.00946, 6.83274);}
if ( binMatched(4, 0.0, 30.0, 1.2, 1.6, 0, 200) ) { setToyMCInit( 1091.84973, 64.07359, 0.00000, 17667.20898, 9.44885, 8.25432, 1.17677, 3.84679);}
if ( binMatched(4, 0.0, 30.0, 1.6, 2.0, 0, 200) ) { setToyMCInit( 864.19781, 54.48868, 95.25758, 8329.44629, 9.42236, 8.27825, 0.96929, 2.61211);}
if ( binMatched(4, 0.0, 30.0, 2.0, 2.4, 0, 200) ) { setToyMCInit( 287.67551, 16.78840, 1.05452, 1829.47534, 9.46317, 8.12417, 0.63216, 2.59114);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 0, 10) ) { setToyMCInit( 1071.36096, 35.23704, 83.48944, 24048.41406, 9.45774, 7.81975, 1.09240, 6.47837);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 10, 20) ) { setToyMCInit( 890.11407, 107.06542, 0.00023, 20182.05273, 9.45242, 7.84810, 1.33217, 5.50051);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 20, 40) ) { setToyMCInit( 1303.96606, 129.63358, 0.00019, 28731.91992, 9.44772, 7.96815, 0.96562, 5.92300);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 40, 60) ) { setToyMCInit( 997.81274, 129.39378, 0.00005, 15994.65625, 9.44987, 7.91178, 1.00067, 6.56250);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 60, 80) ) { setToyMCInit( 861.29767, 110.54973, 17.59483, 10362.75098, 9.44879, 8.16214, 1.28001, 5.38930);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 80, 100) ) { setToyMCInit( 505.76639, 70.65038, 33.65207, 4756.90186, 9.44150, 8.19575, 1.20930, 6.85483);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 100, 120) ) { setToyMCInit( 289.34979, 31.88326, 13.84716, 2238.90454, 9.45788, 8.27656, 0.96654, 6.66548);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 120, 140) ) { setToyMCInit( 149.04852, 22.40486, 9.56378, 706.95563, 9.44439, 8.27722, 0.32195, 30.78772);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 140, 200) ) { setToyMCInit( 76.96704, 12.22682, 0.00007, 769.81995, 9.44692, 8.92681, 0.77991, 5.59290);}

if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 0, 20) ) { setToyMCInit( 1957.01099, 143.13011, 82.97806, 44235.91406, 9.45510, 7.82386, 1.17986, 6.04606);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 20, 60) ) { setToyMCInit( 2301.28125, 258.44260, 0.00001, 44727.33594, 9.44858, 7.94886, 0.97593, 6.14106);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 60, 100) ) { setToyMCInit( 1365.77600, 182.89503, 53.19883, 15116.88477, 9.44600, 8.16519, 1.25404, 5.80887);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 100, 200) ) { setToyMCInit( 572.66302, 84.55088, 16.16200, 4238.73096, 9.45480, 8.43898, 0.85570, 6.96881);}
if ( binMatched(4, 0.0, 30.0, 0.0, 2.4, 0, 200) ) { setToyMCInit( 5798.51025, 575.80280, 52.37277, 104256.17969, 9.45014, 7.94834, 1.09675, 6.05613);}


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
