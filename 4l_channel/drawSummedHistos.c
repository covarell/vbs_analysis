// #include "external_cConstants.h"
#include <TSpline.h>
#include <TString.h>
#include <TStyle.h>
#include <memory>

void drawSummedHistos(){
  
        float lumi = 137.1;

	static const int vars = 6;
        string titlex[vars] = {"K_{D}","M_{4l} [GeV]","M_{jj} [GeV]","#Delta #eta_{jj}","p_{T,j}","#eta_{j}"};
        string titley[vars] = {"Events/0.025","Events/16 GeV","Events/40 GeV","Events/0.175","Events/5 GeV","Events/0.33"};
        string namegif[vars] = {"Dbkgkin","m4l","mjj","detajj","ptj","etaj"};
        int bins[vars] = {20,25,30,20,40,30};
        float xmin[vars] = {0.,150.,100.,0.,0.,-5.};
        float xmax[vars] = {1.,1400.,1300.,8.,400.,5.};
        bool drawSignal[vars] = {false,false,true,true,true,true};

	TH1F *hdata[vars]; //data, because we are hiding higher energies in this phase
	TH1F *hqqzz[vars]; //ew+zx -> real ew
	TH1F *hggzz[vars]; //gg
	TH1F *hvbs[vars]; //vbs
	TH1F *hsum1[vars]; //gg+ew -> real gg
	TH1F *hsum2[vars]; //gg+ew+vbs
	TH1F *httzwzz[vars];//ttz + wwz
	TH1F *hzx[vars]; 

	//histogram stack
        char filename[300]; char filetitle[300];
	THStack *hs[vars];
	gStyle->SetOptStat(0);

        for(int iv = 0; iv < vars; iv++){
	  sprintf(filename,"hs%d",iv);   
	  sprintf(filetitle,"CMS Preliminary                %2.1f fb^{-1};%s;%s",lumi,titlex[iv].c_str(),titley[iv].c_str());  
	  hs[iv] = new THStack(filename,filetitle);

	  TFile fdata("template/root_output_files/data.root");
	  sprintf(filename,"hdata_%d",iv); 
	  hdata[iv] = (TH1F*)((fdata.Get(filename))->Clone());
	  // if (iv == 0) {for (int ibin=16; ibin < 21; ibin++) hdata[iv]->SetBinContent(ibin,0.);}    // blind MELA > 0.75
	  sprintf(filename,"hzx%d",iv); 
	  hzx[iv] = (TH1F*)((fdata.Get(filename))->Clone());

	  TFile fqqzz("template/root_output_files/qqzz_Moriond.root");
	  sprintf(filename,"hqqzz_%d",iv); 
	  hqqzz[iv] = (TH1F*)((fqqzz.Get(filename))->Clone());

	  TFile fttzwzz("template/root_output_files/ttzwzz_Moriond.root");
	  sprintf(filename,"httzwzz_%d",iv); 
	  httzwzz[iv] = (TH1F*)((fttzwzz.Get(filename))->Clone());
	  
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
          httzwzz[iv]->Add(httzwzz[iv],hzx[iv],1,1);    //tt
	  httzwzz[iv]->SetFillColor(kYellow);
	  // if (useMCatNLO == 0) hqqzz[iv]->Add(httzwzz[iv],hqqzz_powheg[iv],1,1); //real ew
	  hqqzz[iv]->Add(httzwzz[iv],hqqzz[iv],1,1); //real ew
	  hqqzz[iv]->SetFillColor(kCyan);
	  hsum1[iv]->Add(hqqzz[iv],hggzz[iv],1,1); //real gg
	  hsum1[iv]->SetFillColor(kBlue);
	  hsum2[iv]->Add(hsum1[iv],hvbs[iv],1,1);    //real vbs
	  hsum2[iv]->SetFillColor(kMagenta);
	  
	  //add histograms to stack
	  hs[iv]->Add(hsum2[iv],"hist");
	  hs[iv]->Add(hsum1[iv],"hist"); 
	  hs[iv]->Add(hqqzz[iv],"hist");
          hs[iv]->Add(httzwzz[iv],"hist");
	  hs[iv]->Add(hzx[iv],"hist");
	  hdata[iv]->SetLineColor(1);
	  hs[iv]->Add(hdata[iv],"E1");
	  TH1F *hdatadivide = (TH1F*)hdata[iv]->Clone();
          hs[iv]->SetHistogram(new TH1F("hstot","",hdatadivide->GetNbinsX(),hdatadivide->GetBinLowEdge(1),hdatadivide->GetBinLowEdge(hdatadivide->GetNbinsX()+1)));
          
 	  
	  // draw the legend
	  TLegend *legend=new TLegend(0.6,0.55,0.85,0.88);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.05);
	  legend->AddEntry(hzx[iv],"Z+X","f");
          legend->AddEntry(httzwzz[iv],"t#bar{t}Z, VVZ","f");
	  legend->AddEntry(hqqzz[iv],"q#bar{q} #rightarrow ZZ","f");
	  legend->AddEntry(hsum1[iv],"gg #rightarrow ZZ","f");
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
	  pad1->SetLeftMargin(0.25);
	  pad1->Draw();
	  pad1->cd();
	  //top plot
	  hs[iv]->GetHistogram()->GetYaxis()->SetLabelSize(0.045);
	  hs[iv]->GetHistogram()->GetYaxis()->SetTitleSize(0.045); 
	  hs[iv]->GetHistogram()->GetYaxis()->SetTitleOffset(1.4);
	  hs[iv]->SetMaximum(25.*lumi/35.9);
          if (iv == 0 || iv > 3) hs[iv]->SetMaximum(45.*lumi/35.9);
          // hs[iv]->GetXaxis()->SetLabelSize(0.06);
	  // hs[iv]->GetXaxis()->SetTitleSize(0.06);
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
	  pad2->SetLeftMargin(0.25);
	  pad2->SetTopMargin(0);
	  pad2->SetBottomMargin(0.19);
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
	  hdatacopy->GetXaxis()->SetLabelSize(0.15);
	  hdatacopy->GetXaxis()->SetTitleSize(0.15);
	  hdatacopy->GetYaxis()->SetLabelSize(0.15);
	  hdatacopy->GetYaxis()->SetTitleSize(0.15);
	  hdatacopy->GetXaxis()->SetTitleOffset(1.2);
	  hdatacopy->GetYaxis()->SetTitleOffset(0.4);
	  //hdatacopy->GetYaxis()->SetTitleOffset(1.7);
	  hdatacopy->GetYaxis()->SetRangeUser(-0.25,2.25);
	  
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
	  
	 
	  hdatacopy->Draw("e1p");
	  
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
