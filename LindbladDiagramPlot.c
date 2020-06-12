void LindbladDiagramPlot()
{

// M. Osorio & J. Serna. 2020.
// jmosorio@astro.unam.mx 
// j_serna@ciencias.unam.mx

  string txt_A;  
  string txt_B;  
  string txt_C;  
  string txt_D;  
  string txt_E;  
  string txt_F;  
  string txt_G;  
  string txt_H;  
  string txt_I;  
  string txt_J;  
  string txt_K;  
  string txt_L;  
  string txt_M;  
  string txt_N;  
  string txt_O;  
  string txt_P;  
  string txt_Q;  
  string txt_R;  
  string txt_S;  
  string txt_T; 
  string txt_U;  
  string txt_V;  
  string txt_W;   
  string txt_X;  
  string txt_Y;  
  string txt_Z;  
  string txt_AA;  
  string txt_BB;  
  string txt_CC; 
  string txt_DD;  
  string txt_EE;  

  txt_A = "Parabola_r1_Total.txt";
  txt_B = "Parabola_r2_Total.txt";
  txt_C = "Parabola_r3_Total.txt";
  txt_D = "Parabola_r4_Total.txt";
  txt_E = "Parabola_r5_Total.txt";
  txt_F = "Parabola_r6_Total.txt";
  txt_G = "Parabola_r7_Total.txt";
  txt_H = "Parabola_r8_Total.txt";
  txt_I = "Parabola_r9_Total.txt";
  txt_J = "Parabola_r10_Total.txt";
  txt_K = "Parabola_r11_Total.txt";
  txt_L = "Parabola_r12_Total.txt";
  txt_M = "Parabola_r13_Total.txt";
  txt_N = "Parabola_r14_Total.txt";
  txt_O = "Parabola_r15_Total.txt";
  txt_P = "Parabola_r16_Total.txt";
  txt_Q = "Parabola_r17_Total.txt";
  txt_R = "Parabola_r18_Total.txt";
  txt_S = "Parabola_r19_Total.txt";
  txt_T = "Parabola_r20_Total.txt";
  txt_U = "Parabola_r21_Total.txt";
  txt_V = "Parabola_r22_Total.txt";
  txt_W = "Parabola_r23_Total.txt";
  txt_X = "Parabola_r24_Total.txt";
  txt_Y = "Parabola_r25_Total.txt";
  txt_Z = "Parabola_r26_Total.txt";
  txt_AA = "Parabola_r27_Total.txt";
  txt_BB = "Parabola_r28_Total.txt";
  txt_CC = "Parabola_r29_Total.txt";
  txt_DD = "Parabola_r30_Total.txt";
  txt_EE = "CircularOrbitCurve_Total.txt";

  TGraph *A = new TGraph(txt_A.c_str());
  TGraph *B = new TGraph(txt_B.c_str());  
  TGraph *C = new TGraph(txt_C.c_str());
  TGraph *D = new TGraph(txt_D.c_str());
  TGraph *E = new TGraph(txt_E.c_str());  
  TGraph *F = new TGraph(txt_F.c_str());  
  TGraph *G = new TGraph(txt_G.c_str());
  TGraph *H = new TGraph(txt_H.c_str());
  TGraph *I = new TGraph(txt_I.c_str());
  TGraph *J = new TGraph(txt_J.c_str());  
  TGraph *K = new TGraph(txt_K.c_str());  
  TGraph *L = new TGraph(txt_L.c_str());
  TGraph *M = new TGraph(txt_M.c_str());
  TGraph *N = new TGraph(txt_N.c_str());
  TGraph *O = new TGraph(txt_O.c_str());
  TGraph *P = new TGraph(txt_P.c_str());  
  TGraph *Q = new TGraph(txt_Q.c_str());
  TGraph *R = new TGraph(txt_R.c_str());
  TGraph *S = new TGraph(txt_S.c_str());
  TGraph *T = new TGraph(txt_T.c_str());
  TGraph *U = new TGraph(txt_U.c_str());  
  TGraph *V = new TGraph(txt_V.c_str());
  TGraph *W = new TGraph(txt_W.c_str());
  TGraph *X = new TGraph(txt_X.c_str());
  TGraph *Y = new TGraph(txt_Y.c_str());
  TGraph *Z = new TGraph(txt_Z.c_str());  
  TGraph *AA = new TGraph(txt_AA.c_str());
  TGraph *BB = new TGraph(txt_BB.c_str());
  TGraph *CC = new TGraph(txt_CC.c_str());
  TGraph *DD = new TGraph(txt_DD.c_str());
  TGraph *EE = new TGraph(txt_EE.c_str());  

  TApplication theApp("App", NULL, NULL);
  TCanvas *c1 = new TCanvas("c1","Title",925,925);
  c1->Connect("Closed()","TApplication",&theApp,"Terminate()");
  c1 -> SetGrid();
  gStyle->SetOptStat(0);

  TLegend *leg = new TLegend(0.15,0.6,0.6,0.8);
  c1->Update();
  leg->SetNColumns( 5 );

  TLegend *leg1 = new TLegend(0.15,0.8,0.6,0.85);
  c1 -> Update();
  leg1 -> SetNColumns( 1 );

  A -> SetLineStyle( 1 ) ;
  A -> SetLineColor( kRed+0 ) ;
  A -> SetLineWidth( 2 ) ;
  A -> GetXaxis() -> SetTitle( "#frac{E_{c}}{G}" ) ;
  A -> GetYaxis() -> SetTitle( "#frac{L_{c}}{#sqrt{G}}" ) ;
  A -> SetTitle( "" ) ;
  A -> GetXaxis() -> SetTitleSize( 0.03 );
  A -> GetXaxis() -> SetTitleOffset( 1.3 );
  A -> GetXaxis() -> SetLabelOffset( 0.0 );
  A -> GetXaxis() -> SetLabelSize( 0.03 );
  A -> GetXaxis() -> SetTickSize( 0.01 ) ;
  A -> GetXaxis() -> SetNoExponent( kFALSE ) ;
  A -> GetXaxis() -> SetLabelOffset(0.009) ;
  A -> GetXaxis() -> SetLimits( -3e3 , 0 ) ;
  A -> GetYaxis() -> SetTitleSize( 0.03 );
  A -> GetYaxis() -> SetTitleOffset( 1.3 );
  A -> GetYaxis() -> SetLabelOffset( 0.01 );
  A -> GetYaxis() -> SetLabelSize( 0.03 );
  A -> GetYaxis() -> SetTickSize( 0.01 ) ;
  A -> GetYaxis() -> SetRangeUser( 0 , 1e3 ) ;
  A -> SetMarkerSize(1); 
  A -> Draw( "AC" ) ;
  TGaxis::SetMaxDigits(3);
  leg -> AddEntry( A , "r_{0}=1" , "l" ) ;
  c1 -> Update() ;

  B -> SetLineStyle( 1 ) ;
  B -> SetLineColor( kRed-4 ) ;
  B -> SetLineWidth( 2 ) ;
  B -> Draw( "C" ) ;
  leg -> AddEntry( B , "r_{0}=2" , "l" ) ;
  c1 -> Update() ;

  C -> SetLineStyle( 1 ) ;
  C -> SetLineColor( kRed-7 ) ;
  C -> SetLineWidth( 2 ) ;
  C -> Draw( "C" ) ;
  leg -> AddEntry( C , "r_{0}=3" , "l" ) ;
  c1 -> Update() ;

  D -> SetLineStyle( 1 ) ;
  D -> SetLineColor( kRed-9 ) ;
  D -> SetLineWidth( 2 ) ;
  D -> Draw( "C" ) ;
  leg -> AddEntry( D , "r_{0}=4" , "l" ) ;
  c1 -> Update() ;

  E -> SetLineStyle( 1 ) ;
  E -> SetLineColor( kRed-10 ) ;
  E -> SetLineWidth( 2 ) ;
  E -> Draw( "C" ) ;
  leg -> AddEntry( E , "r_{0}=5" , "l" ) ;
  c1 -> Update() ;

  F -> SetLineStyle( 1 ) ;
  F -> SetLineColor( kYellow-10 ) ;
  F -> SetLineWidth( 2 ) ;
  F -> Draw( "C" ) ;
  leg -> AddEntry( F , "r_{0}=6" , "l" ) ;
  c1 -> Update() ;

  G -> SetLineStyle( 1 ) ;
  G -> SetLineColor( kYellow-9 ) ;
  G -> SetLineWidth( 2 ) ;
  G -> Draw( "C" ) ;
  leg -> AddEntry( G , "r_{0}=7" , "l" ) ;
  c1 -> Update() ;

  H -> SetLineStyle( 1 ) ;
  H -> SetLineColor( kYellow-7 ) ;
  H -> SetLineWidth( 2 ) ;
  H -> Draw( "C" ) ;
  leg -> AddEntry( H , "r_{0}=8" , "l" ) ;
  c1 -> Update() ;

  I -> SetLineStyle( 1 ) ;
  I -> SetLineColor( kYellow-4 ) ;
  I -> SetLineWidth( 2 ) ;
  I -> Draw( "C" ) ;
  leg -> AddEntry( I , "r_{0}=9" , "l" ) ;
  c1 -> Update() ;

  J -> SetLineStyle( 1 ) ;
  J -> SetLineColor( kYellow+0 ) ;
  J -> SetLineWidth( 2 ) ;
  J -> Draw( "C" ) ;
  leg -> AddEntry( J , "r_{0}=10" , "l" ) ;
  c1 -> Update() ;

  K -> SetLineStyle( 1 ) ;
  K -> SetLineColor( kGreen+0 ) ;
  K -> SetLineWidth( 2 ) ;
  K -> Draw( "C" ) ;
  leg -> AddEntry( K , "r_{0}=11" , "l" ) ;
  c1 -> Update() ;

  L -> SetLineStyle( 1 ) ;
  L -> SetLineColor( kGreen-4 ) ;
  L -> SetLineWidth( 2 ) ;
  L -> Draw( "C" ) ;
  leg -> AddEntry( L , "r_{0}=12" , "l" ) ;
  c1 -> Update() ;

  M -> SetLineStyle( 1 ) ;
  M -> SetLineColor( kGreen-7 ) ;
  M -> SetLineWidth( 2 ) ;
  M -> Draw( "C" ) ;
  leg -> AddEntry( M , "r_{0}=13" , "l" ) ;
  c1 -> Update() ;

  N -> SetLineStyle( 1 ) ;
  N -> SetLineColor( kGreen-9 ) ;
  N -> SetLineWidth( 2 ) ;
  N -> Draw( "C" ) ;
  leg -> AddEntry( N , "r_{0}=14" , "l" ) ;
  c1 -> Update() ;

  O -> SetLineStyle( 1 ) ;
  O -> SetLineColor( kGreen-10 ) ;
  O -> SetLineWidth( 2 ) ;
  O -> Draw( "C" ) ;
  leg -> AddEntry( O , "r_{0}=15" , "l" ) ;
  c1 -> Update() ;

  P -> SetLineStyle( 1 ) ;
  P -> SetLineColor( kCyan-10 ) ;
  P -> SetLineWidth( 2 ) ;
  P -> Draw( "C" ) ;
  leg -> AddEntry( P , "r_{0}=16" , "l" ) ;
  c1 -> Update() ;

  Q -> SetLineStyle( 1 ) ;
  Q -> SetLineColor( kCyan-9 ) ;
  Q -> SetLineWidth( 2 ) ;
  Q -> Draw( "C" ) ;
  leg -> AddEntry( Q , "r_{0}=17" , "l" ) ;
  c1 -> Update() ;

  R -> SetLineStyle( 1 ) ;
  R -> SetLineColor( kCyan-7 ) ;
  R -> SetLineWidth( 2 ) ;
  R -> Draw( "C" ) ;
  leg -> AddEntry( R , "r_{0}=18" , "l" ) ;
  c1 -> Update() ;

  S -> SetLineStyle( 1 ) ;
  S -> SetLineColor( kCyan-4 ) ;
  S -> SetLineWidth( 2 ) ;
  S -> Draw( "C" ) ;
  leg -> AddEntry( S , "r_{0}=19" , "l" ) ;
  c1 -> Update() ;

  T -> SetLineStyle( 1 ) ;
  T -> SetLineColor( kCyan+0 ) ;
  T -> SetLineWidth( 2 ) ;
  T -> Draw( "C" ) ;
  leg -> AddEntry( T , "r_{0}=20" , "l" ) ;
  c1 -> Update() ;

  U -> SetLineStyle( 1 ) ;
  U -> SetLineColor( kBlue+0 ) ;
  U -> SetLineWidth( 2 ) ;
  U -> Draw( "C" ) ;
  leg -> AddEntry( U , "r_{0}=21" , "l" ) ;
  c1 -> Update() ;

  V -> SetLineStyle( 1 ) ;
  V -> SetLineColor( kBlue-4 ) ;
  V -> SetLineWidth( 2 ) ;
  V -> Draw( "C" ) ;
  leg -> AddEntry( V , "r_{0}=22" , "l" ) ;
  c1 -> Update() ;

  W -> SetLineStyle( 1 ) ;
  W -> SetLineColor( kBlue-7 ) ;
  W -> SetLineWidth( 2 ) ;
  W -> Draw( "C" ) ;
  leg -> AddEntry( W , "r_{0}=23" , "l" ) ;
  c1 -> Update() ;

  X -> SetLineStyle( 1 ) ;
  X -> SetLineColor( kBlue-9 ) ;
  X -> SetLineWidth( 2 ) ;
  X -> Draw( "C" ) ;
  leg -> AddEntry( X , "r_{0}=24" , "l" ) ;
  c1 -> Update() ;

  Y -> SetLineStyle( 1 ) ;
  Y -> SetLineColor( kBlue-10 ) ;
  Y -> SetLineWidth( 2 ) ;
  Y -> Draw( "C" ) ;
  leg -> AddEntry( Y , "r_{0}=25" , "l" ) ;
  c1 -> Update() ;

  Z -> SetLineStyle( 1 ) ;
  Z -> SetLineColor( kMagenta-10 ) ;
  Z -> SetLineWidth( 2 ) ;
  Z -> Draw( "C" ) ;
  leg -> AddEntry( Z , "r_{0}=26" , "l" ) ;
  c1 -> Update() ;

  AA -> SetLineStyle( 1 ) ;
  AA -> SetLineColor( kMagenta-9 ) ;
  AA -> SetLineWidth( 2 ) ;
  AA -> Draw( "C" ) ;
  leg -> AddEntry( AA , "r_{0}=27" , "l" ) ;
  c1 -> Update() ;

  BB -> SetLineStyle( 1 ) ;
  BB -> SetLineColor( kMagenta-7 ) ;
  BB -> SetLineWidth( 2 ) ;
  BB -> Draw( "C" ) ;
  leg -> AddEntry( BB , "r_{0}=28" , "l" ) ;
  c1 -> Update() ;

  CC -> SetLineStyle( 1 ) ;
  CC -> SetLineColor( kMagenta-4 ) ;
  CC -> SetLineWidth( 2 ) ;
  CC -> Draw( "C" ) ;
  leg -> AddEntry( CC , "r_{0}=29" , "l" ) ;
  c1 -> Update() ;

  DD -> SetLineStyle( 1 ) ;
  DD -> SetLineColor( kMagenta+0 ) ;
  DD -> SetLineWidth( 2 ) ;
  DD -> Draw( "C" ) ;
  leg -> AddEntry( DD , "r_{0}=30" , "l" ) ;
  c1 -> Update() ;

  EE -> SetLineStyle( 1 ) ;
  EE -> SetLineColor( kBlack+0 ) ;
  EE -> SetLineWidth( 2 ) ;
  EE -> Draw( "C" ) ;
  leg1 -> AddEntry( EE , "Curva de Orbitas Circulares" , "l" ) ;
  c1 -> Update() ;

  leg1 -> SetTextColor( kBlack ) ;
  leg1 -> SetTextAlign( 22 ) ;
  leg1 -> SetTextSize( 0.02 ) ;
  leg1 -> SetFillColorAlpha( kWhite , 1.0 ) ;
  leg1 -> SetLineColorAlpha( kBlack , 1.0 ) ;
  leg1 -> SetLineWidth( 2 ) ;
  leg1 -> Draw() ;
  c1 -> Update() ;

  leg -> SetTextColor( kBlack ) ;
  leg -> SetTextAlign( 22 ) ;
  leg -> SetTextSize( 0.02 ) ;
  leg -> SetFillColorAlpha( kWhite , 1.0 ) ;
  leg -> SetLineColorAlpha( kBlack , 1.0 ) ;
  leg -> SetLineWidth( 2 ) ;
  leg -> Draw() ;
  c1 -> Update() ;



















  return 0;
}
