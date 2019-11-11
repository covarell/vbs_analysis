// #include "external_cConstants.h"
#include <TSpline.h>
#include <TString.h>
#include <memory>

void drawSummedHistos(){
  
        float lumi = 137.1;

	static const int vars = 6;
        string titlex[vars] = {"K_{D}","M_{4l} [GeV]","M_{jj} [GeV]","#Delta #eta_{jj}","p_{T,j}","#eta_{j}"};        
        string titley[vars] = {"Events/0.025","Events/16 GeV","Events/22.5 GeV","Events/0.175","Events/5 GeV","Events/0.25"};     
	string namegif[vars] = {"Dbkgkin","m4l","mjj","detajj","ptj","etaj"};
        int bins[vars] = {20,20,20,20,30,20};
        float xmin[vars] = {0.,160.,100.,0.,0.,-5.};
	float xmax[vars] = {1.,800.,1000.,8.,300.,5.};	
	bool drawSignal[vars] = {false,false,true,true,true,true};

	TH1F *hdata[vars]; //data, because we are hiding higher energies in this phase
	TH1F *hqqzz[vars]; //ew+zx -> real ew
	TH1F *hggzz[vars]; //gg
	TH1F *hvbs[vars]; //vbs
	TH1F *hsum1[vars]; //gg+ew -> real gg
	TH1F *hsum2[vars]; //gg+ew+vbs
	TH1F *httzwwz[vars];//ttz + wwz
	TH1F *hzx[vars]; 

	//histogram stack
        char filename[300]; char filetitle[300];
	THStack *hs[vars];
        for(int iv = 0; iv < vars; iv++){
	  sprintf(filename,"hs%d",iv);   
	  sprintf(filetitle,"CMS Preliminary                %2.1f fb^{-1};%s;%s",lumi,titlex[iv].c_str(),titley[iv].c_str());  
	  hs[iv] = new THStack(filename,filetitle);

	  TFile fdata("template/root_output_files/data.root");
	  sprintf(filename,"hdata_%d",iv); 
	  hdata[iv] = (TH1F*)((fdata.Get(filename))->Clone());
	  if (iv == 0) {for (int ibin=18; ibin < 21; ibin++) hdata[iv]->SetBinContent(ibin,0.);}
	  sprintf(filename,"hzx%d",iv); 
	  hzx[iv] = (TH1F*)((fdata.Get(filename))->Clone());

	  TFile fqqzz("template/root_output_files/qqzz_Moriond.root");
	  sprintf(filename,"hqqzz_%d",iv); 
	  hqqzz[iv] = (TH1F*)((fqqzz.Get(filename))->Clone());
	  sprintf(filename,"httzwwz_%d",iv); 
	  httzwwz[iv] = (TH1F*)((fqqzz.Get(filename))->Clone());
	  
	  TFile fggzz("template/root_output_files/ggzz_Moriond.root");
	  sprintf(filename,"hggzz_%d",iv); 
	  hggzz[iv] = (TH1F*)((fggzz.Get(filename))->Clone());

	  TFile fvbs("template/root_output_files/vbs_Moriond.root");
	  sprintf(filename,"hvbs_%d",iv); 
	  hvbs[iv] = (TH1F*)((fvbs.Get(filename))->Clone());
	  hsum1[iv] = (TH1F*)((fvbs.Get(filename))->Clone());
	  hsum2[iv] = (TH1F*)((fvbs.Get(filename))->Clone());

	  cout << "OK here" << endl;
	  
	  //HISTOGRAMS ADDED TO STACK
	  hzx[iv]->SetFillColor(kGreen);
          httzwwz[iv]->Add(httzwwz[iv],hzx[iv],1,1);    //tt
	  httzwwz[iv]->SetFillColor(kYellow);
	  // if (useMCatNLO == 0) hqqzz[iv]->Add(httzwwz[iv],hqqzz_powheg[iv],1,1); //real ew
	  hqqzz[iv]->Add(httzwwz[iv],hqqzz[iv],1,1); //real ew
	  hqqzz[iv]->SetFillColor(kCyan);
	  hsum1[iv]->Add(hqqzz[iv],hggzz[iv],1,1); //real gg
	  hsum1[iv]->SetFillColor(kBlue);
	  hsum2[iv]->Add(hsum1[iv],hvbs[iv],1,1);    //real vbs
	  hsum2[iv]->SetFillColor(kMagenta);
	  
	  //add histograms to stack
	  hs[iv]->Add(hsum2[iv],"hist");
	  hs[iv]->Add(hsum1[iv],"hist");
	  hs[iv]->Add(hqqzz[iv],"hist");
          hs[iv]->Add(httzwwz[iv],"hist");
	  hs[iv]->Add(hzx[iv],"hist");
	  TH1F *hdatadivide = (TH1F*)hdata[iv]->Clone();
	  hs[iv]->Add(hdata[iv],"E1");
	  
	  // draw the legend
	  TLegend *legend=new TLegend(0.6,0.55,0.85,0.88);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.04);
	  legend->AddEntry(hzx[iv],"Z+X","f");
          legend->AddEntry(httzwwz[iv],"t#bar{t}Z, WWZ","f");
	  legend->AddEntry(hqqzz[iv],"q#bar{q}#rightarrowZZ","f");
	  legend->AddEntry(hsum1[iv],"gg#rightarrowZZ","f");
	  legend->AddEntry(hsum2[iv],"VBS","f");
	  legend->AddEntry(hdata[iv],"Data","lep");
	  legend->SetBorderSize(0);
	  
	  //GRAPHICS
	  //hs->GetXaxis()->SetTitle("K_{D}");
	  //hs->GetXaxis()->SetTitleSize(.15);
	  //hs->GetYaxis()->SetTitle("Events/0.05");
	  //hs->GetYaxis()->SetTitleSize(.15);
	  
	  //RATIO PLOT
	  //canvas
	  TCanvas *c1 = new TCanvas("c1","example",800,1000);
	  //pad1
	  float eps =0;// 0.006;
	  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1,0);
	  pad1->SetBottomMargin(0);
	  pad1->Draw();
	  pad1->cd();
	  //top plot
	  hs[iv]->SetMaximum(30.*lumi/35.9);
          if (iv == 0 || iv > 3) hs[iv]->SetMaximum(45.*lumi/35.9);
	  hs[iv]->Draw("nostack"); //old
	  if (drawSignal[iv]) {
	    TH1F* h77 = (TH1F*)hvbs[iv]->Clone();
	    h77->SetLineWidth(3);
	    h77->SetLineColor(kMagenta);
	    h77->SetFillStyle(0);
	    h77->Scale(30);   
	    legend->AddEntry(h77,"VBS (x30)","l");
	    h77->Draw("histsame");
	  }
	  hs[iv]->GetXaxis()->SetTitle(titlex[iv].c_str());
	  legend->Draw("same");
	  //switch?
	  c1->cd();
	  //pad2
	  TPad *pad2 = new TPad("pad2","pad2",0,0.1,1,0.3+eps,0); //old position
	  pad2->SetTopMargin(0);
	  pad2->SetBottomMargin(0.15);
	  //make bottom pad transparent
	  //pad2->SetFrameFillColor(0);
	  //pad2->SetFrameBorderMode(0);
	  //pad2->SetFrameFillColor(0);
	  //pad2->SetFrameBorderMode(0);
	  
	  pad2->Draw();
	  pad2->cd();
	  //bottom plot
	  TH1F *hdatacopy = (TH1F*) hdatadivide->Clone();
	  //axis labels
	  hdatacopy->GetXaxis()->SetLabelFont(59);//change this for font type
	  hdatacopy->GetXaxis()->SetLabelSize(22);
	  hdatacopy->GetYaxis()->SetLabelFont(59);//change this for font type
	  hdatacopy->GetYaxis()->SetLabelSize(22);
	  //axis titles
	  hdatacopy->GetXaxis()->SetTitleFont(59); //change this for font type
	  hdatacopy->GetXaxis()->SetTitleSize(22);
	  hdatacopy->GetYaxis()->SetTitleFont(59); //change this for font type
	  hdatacopy->GetYaxis()->SetTitleSize(22);
	  hdatacopy->GetXaxis()->SetTitleOffset(4.5);
	  hdatacopy->GetYaxis()->SetTitleOffset(1.7);
	  hdatacopy->GetYaxis()->SetRangeUser(-1.,3.);
	  
	  hdatacopy->Sumw2();
	  hdatacopy->SetStats(0); //clear stat box
	  hdatacopy->Divide(hsum2[iv]); //invert divide
	  hdatacopy->SetMarkerStyle(20);
	  string title = " ;"+titlex[iv]+"; Data/MC";
	  hdatacopy->SetTitle(title.c_str());
	  //hdatacopy->GetXaxis()->SetTitleSize(50);
	  //hdatacopy->GetXaxis()->SetLabelSize(35);
	  //hdatacopy->GetYaxis()->SetTitleSize(15);
	  //hdatacopy->GetYaxis()->SetLabelSize(15);
	  
	  //gStyle->SetLabelSize(2,"x").
	  hdatacopy->Draw("ep");
	  
	  //Orizontal line
	  TLine *line = new TLine(xmin[iv],1,xmax[iv],1);
	  line->SetLineColor(kRed);
	  line->SetLineStyle(2);
	  line->Draw("same");
	  
	  //close and print on file
	  c1->cd();
	  sprintf(filename,"noScaleZX/%s_plot_allMCatNLO_allyears.png",namegif[iv].c_str());     
	  gPad->Print(filename);
	}
}
