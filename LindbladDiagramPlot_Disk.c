void LindbladDiagramPlot_Disk()
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

  txt_A = "CircularOrbitCurve_Disk.txt";
  txt_B = "Parabola_r1_Disk.txt";
  txt_C = "Parabola_r2_Disk.txt";
  txt_D = "Parabola_r3_Disk.txt";
  txt_E = "Parabola_r4_Disk.txt";
  txt_F = "Parabola_r5_Disk.txt";

  TGraph *A = new TGraph(txt_A.c_str());
  TGraph *B = new TGraph(txt_B.c_str());  
  TGraph *C = new TGraph(txt_C.c_str());
  TGraph *D = new TGraph(txt_D.c_str());
  TGraph *E = new TGraph(txt_E.c_str());  
  TGraph *F = new TGraph(txt_F.c_str());  

  TApplication theApp("App", NULL, NULL);
  TCanvas *c1 = new TCanvas("c1","Title",925,925);
  c1->Connect("Closed()","TApplication",&theApp,"Terminate()");
//  c1 -> SetGrid();
  gStyle->SetOptStat(0);
  
  TLegend *leg = new TLegend(0.25,0.6,0.45,0.8);
  c1 -> Update();
  leg -> SetNColumns( 1 );


  A -> SetLineStyle( 1 ) ;
  A -> SetLineColor( kBlue ) ;
  A -> SetLineWidth( 2 ) ;
  A -> GetXaxis() -> SetTitle( "E_{c}" ) ;
  A -> GetYaxis() -> SetTitle( "L_{c}" ) ;
  A -> SetTitle( "" ) ;
  A -> GetXaxis() -> SetTitleSize( 0.03 );
  A -> GetXaxis() -> SetTitleOffset( 1.3 );
  A -> GetXaxis() -> SetLabelOffset( 0.0 );
  A -> GetXaxis() -> SetLabelSize( 0.03 );
  A -> GetXaxis() -> SetTickSize( 0.01 ) ;
  A -> GetXaxis() -> SetNoExponent( kFALSE ) ;
  A -> GetXaxis() -> SetLabelOffset(0.009) ;
  A -> GetXaxis() -> SetLimits( -1000 , 0 ) ;
  A -> GetYaxis() -> SetTitleSize( 0.03 );
  A -> GetYaxis() -> SetTitleOffset( 1.3 );
  A -> GetYaxis() -> SetLabelOffset( 0.0 );
  A -> GetYaxis() -> SetLabelSize( 0.03 );
  A -> GetYaxis() -> SetTickSize( 0.01 ) ;
  A -> GetYaxis() -> SetRangeUser( 0 , 100 ) ;
  A -> SetMarkerSize(1); 
  A -> Draw( "AC" ) ;
  TGaxis::SetMaxDigits(3);
  leg -> AddEntry( A , "Curv Orb Circ (Disk)" , "l" ) ;
  c1 -> Update() ;

  B -> SetLineStyle( 1 ) ;
  B -> SetLineColor( kGreen+0 ) ;
  B -> SetLineWidth( 2 ) ;
  B -> Draw( "C" ) ;
  leg -> AddEntry( B , "r_{0}=1" , "l" ) ;
  c1 -> Update() ;

  C -> SetLineStyle( 1 ) ;
  C -> SetLineColor( kGreen-4 ) ;
  C -> SetLineWidth( 2 ) ;
  C -> Draw( "C" ) ;
  leg -> AddEntry( C , "r_{0}=2" , "l" ) ;
  c1 -> Update() ;

  D -> SetLineStyle( 1 ) ;
  D -> SetLineColor( kGreen-7 ) ;
  D -> SetLineWidth( 2 ) ;
  D -> Draw( "C" ) ;
  leg -> AddEntry( D , "r_{0}=3" , "l" ) ;
  c1 -> Update() ;

  E -> SetLineStyle( 1 ) ;
  E -> SetLineColor( kGreen-9 ) ;
  E -> SetLineWidth( 2 ) ;
  E -> Draw( "C" ) ;
  leg -> AddEntry( E , "r_{0}=4" , "l" ) ;
  c1 -> Update() ;

  F -> SetLineStyle( 1 ) ;
  F -> SetLineColor( kGreen-10 ) ;
  F -> SetLineWidth( 2 ) ;
  F -> Draw( "C" ) ;
  leg -> AddEntry( F , "r_{0}=5" , "l" ) ;
  c1 -> Update() ;

  leg -> SetTextColor( kBlack ) ;
  leg -> SetTextAlign( 22 ) ;
  leg -> SetTextSize( 0.02 ) ;
  leg -> SetFillColorAlpha( kWhite , 0.3 ) ;
  leg -> SetLineColorAlpha( kWhite , 0.0 ) ;
  leg -> SetLineWidth( 2 ) ;
  leg -> Draw() ;
  c1 -> Update() ;



  return 0;
}
