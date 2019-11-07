// #include "external_cConstants.h"
#include <TSpline.h>
#include <TString.h>
#include <memory>
#include <TH1.h>

using namespace std;

void compare_VBS(){
  
        float lumi = 35.9;
 
	static const int vars = 8;
        string titlex[vars] = {"K_{D}","M_{4l} [GeV]","M_{jj} [GeV]","#Delta #eta_{jj}","p_{T,j}","#eta_{j}","M_{Z1} [GeV]","M_{Z2} [GeV]"};        
        string titley[vars] = {"Events/0.025","Events/16 GeV","Events/22.5 GeV","Events/0.175","Events/5 GeV","Events/0.25","Events/4 GeV","Events/4 GeV"};     
	string namegif[vars] = {"Dbkgkin","m4l","mjj","detajj","ptj","etaj","mz1","mz2"};
        int bins[vars] = {20,20,20,20,30,20,20,20};
	float xmin[vars] = {0.,160.,150.,0.,0.,-5.,50.,50.};
	float xmax[vars] = {1.,800.,1200.,8.,300.,5.,130.,130.};	

	//histogram stack
        char filename[300]; char filetitle[300];
	
        lumi *= 1000;

        //histograms

	TH1F *h_complete_data[vars]; //all data
	TH1F *h00[vars]; //bkg_kin<0.7 cut full background plot
	TH1F *h0[vars]; //data, because we are hiding higher energies in this phase
	TH1F *h1[vars]; //ew
	TH1F *h1bis[vars]; //ew+zx -> real ew
	TH1F *h2[vars]; //gg
	TH1F *h3[vars]; //vbs
	TH1F *h4[vars]; //gg+ew -> real gg
	TH1F *h5[vars]; //gg+ew+vbs
	TH1F *h6[vars]; //gg+ew+vbs+zx ->real vbs
	TH1F *h7[vars]; //qqzz e
	TH1F *h8[vars]; //qqzz mu
	TH1F *h9[vars]; //qqzz e mu
	TH1F *h10[vars];//ggzz e
	TH1F *h11[vars];//ggzz mu
	TH1F *h12[vars]; //ggzz e mu
	TH1F *h13[vars];//vbs e
	TH1F *h14[vars];//vbs mu
	TH1F *h15[vars];//vbs e mu
	TH1F *h0_ee[vars];//vbs e
	TH1F *h0_mm[vars];//vbs mu
	TH1F *h0_em[vars];//vbs e mu
	TH1F *hnum[vars];//for 2018 rescale
	TH1F *hden[vars];//for 2018 rescale

	for(int iv = 0; iv < vars; iv++){
	  sprintf(filename,"hcd%d",iv);   h_complete_data[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //all data
	  sprintf(filename,"h00_%d",iv);   h00[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //bkg_kin<0.7 cut full background plot
	  sprintf(filename,"h0_%d",iv);   h0[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //data, because we are hiding higher energies in this phase
	  sprintf(filename,"h1_%d",iv);   h1[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //ew
	  sprintf(filename,"h1bis_%d",iv);   h1bis[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //ew+zx -> real ew
	  sprintf(filename,"h2_%d",iv);   h2[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //gg
	  sprintf(filename,"h3_%d",iv);   h3[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //vbs
	  sprintf(filename,"h4_%d",iv);   h4[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //gg+ew -> real gg
	  sprintf(filename,"h5_%d",iv);   h5[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //gg+ew+vbs
	  sprintf(filename,"h6_%d",iv);   h6[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //gg+ew+vbs+zx ->real vbs
	  sprintf(filename,"h7_%d",iv);   h7[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //qqzz e
	  sprintf(filename,"h8_%d",iv);   h8[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //qqzz mu
	  sprintf(filename,"h9_%d",iv);   h9[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //qqzz e mu
	  sprintf(filename,"h10_%d",iv);   h10[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//ggzz e
	  sprintf(filename,"h11_%d",iv);   h11[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//ggzz mu
	  sprintf(filename,"h12_%d",iv);  h12[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //ggzz e mu
	  sprintf(filename,"h13_%d",iv); h13[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//vbs e
	  sprintf(filename,"h14_%d",iv); h14[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//vbs mu
	  sprintf(filename,"h15_%d",iv); h15[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//vbs e mu
	  sprintf(filename,"h0ee_%d",iv); h0_ee[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//vbs e
	  sprintf(filename,"h0mm_%d",iv); h0_mm[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//vbs mu
	  sprintf(filename,"h0em_%d",iv); h0_em[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//vbs e mu
	  sprintf(filename,"hnum_%d",iv); hnum[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//for 2018 rescale
	  sprintf(filename,"hden_%d",iv); hden[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//for 2018 rescale
	  
	}   
	gStyle->SetPalette(1);
	TFile *input_file;

	float c_constant = 8.5;
        // if (year == 2017) c_constant = 3.5;
	// if (year == 2018) c_constant = 3.5; 
	TFile* f_ = TFile::Open("/afs/cern.ch/work/c/covarell/vbs2017/CMSSW_10_2_15_slc7/src/ZZAnalysis/AnalysisStep/data/cconstants/SmoothKDConstant_m4l_DjjVBF13TeV.root");
	TSpline3* ts = (TSpline3*)(f_->Get("sp_gr_varReco_Constant_Smooth")->Clone());
	f_->Close();

        // find available samples  
	int nSamp = 0;  
	TString rootname[40];
 	sprintf(filename,"newsamples_compareVBS.txt");

	ifstream parInput(filename);
        
	if (parInput.is_open()) {
	  while ( parInput.good() ) {
	    parInput >> rootname[nSamp]; 
            cout << nSamp << " " <<  rootname[nSamp] << endl; 
	    nSamp++;
	  }
	  parInput.close();
	} 

	//for loop for different samples
	for(int is = 0; is < nSamp-1; is++){

	  //print cycle
	  std::cout << endl << is << endl;
	  
          TFile* input_file = TFile::Open(rootname[is].Data()); 
	  TH1F *hCounters= (TH1F*)input_file->Get("ZZTree/Counters");
	  float gen_sum_weights = hCounters->GetBinContent(40);
	  std::cout<<endl<<is<<"  "<< gen_sum_weights<<endl;
	  
	  //tchain and add function for multiple input files
	  TChain *tqqzz= new TChain("ZZTree/candTree");
	  tqqzz->Add(rootname[is].Data());
          
          //process class
          int j = 0;   // qqzz powheg
	  if (rootname[is].Contains("madgraph")) j = 1;      
	
	  //histogram declaration
	  //TH1F *kin_zz = new TH1F("kin_zz","",bins,xmin,xmax); //was 100 bins
	  
	  //original variable declarations
	  float ZZPt,ZZMass,Z1Mass,Z2Mass,DiJetMass,DiJetDEta;
	  float xsec,KFactorEWKqqZZ,overallEventWeight,L1prefiringWeight,KFactorQCDqqZZ_M;
	  vector<float> *LepPt=new vector<float>;
	  vector<float> *JetPt=new vector<float>;
          vector<float> *JetEta=new vector<float>;
	  short Z1Flav,Z2Flav;
	  short nCleanedJetsPt30;
	  float pvbf_VAJHU_old;
	  float phjj_VAJHU_old;
	  float bkg_VAMCFM,p0plus_VAJHU;
	  short ZZsel;
	  vector<short> *LepLepId=0;
	  short nExtraLep;
	  short nCleanedJetsPt30BTagged_bTagSF;
	  
	  //new variable declarations
	  float p_JJEW_BKG_MCFM_JECNominal; //not in use
	  float p_JJQCD_BKG_MCFM_JECNominal;
	  float p_JJVBF_BKG_MCFM_JECNominal;
	  float KFactorQCDggzz_Nominal;
	  //	float lumi = 35.9E03;
	  float my_sum = 0;
	  float mc_integral;
	  float data_integral;
	  //original brach addresses
	  tqqzz->SetBranchAddress("nExtraLep",&nExtraLep);
	  tqqzz->SetBranchAddress("nCleanedJetsPt30BTagged_bTagSF",&nCleanedJetsPt30BTagged_bTagSF);
	  tqqzz->SetBranchAddress("p_JJVBF_SIG_ghv1_1_JHUGen_JECNominal",&pvbf_VAJHU_old);
	  tqqzz->SetBranchAddress("p_JJQCD_SIG_ghg2_1_JHUGen_JECNominal",&phjj_VAJHU_old);
	  tqqzz->SetBranchAddress("p_GG_SIG_ghg2_1_ghz1_1_JHUGen",&p0plus_VAJHU);
	  tqqzz->SetBranchAddress("p_QQB_BKG_MCFM",&bkg_VAMCFM);
	  tqqzz->SetBranchAddress("ZZPt",&ZZPt);
	  tqqzz->SetBranchAddress("ZZMass",&ZZMass);
	  tqqzz->SetBranchAddress("Z1Flav",&Z1Flav);
	  tqqzz->SetBranchAddress("Z2Flav",&Z2Flav);
	  tqqzz->SetBranchAddress("Z1Mass",&Z1Mass);
	  tqqzz->SetBranchAddress("Z2Mass",&Z2Mass);
	  tqqzz->SetBranchAddress("KFactor_EW_qqZZ",&KFactorEWKqqZZ);
	  tqqzz->SetBranchAddress("xsec",&xsec);
	  tqqzz->SetBranchAddress("ZZsel",&ZZsel);
	  tqqzz->SetBranchAddress("LepLepId",&LepLepId);
	  tqqzz->SetBranchAddress("LepPt",&LepPt);
          tqqzz->SetBranchAddress("JetPt",&JetPt);
          tqqzz->SetBranchAddress("JetEta",&JetEta);
	  tqqzz->SetBranchAddress("overallEventWeight",&overallEventWeight);	
	  tqqzz->SetBranchAddress("L1prefiringWeight",&L1prefiringWeight);
	  tqqzz->SetBranchAddress("KFactor_QCD_qqZZ_M",&KFactorQCDqqZZ_M);
	  tqqzz->SetBranchAddress("nCleanedJetsPt30",&nCleanedJetsPt30);
	  
	  //new branch addresses
	  tqqzz->SetBranchAddress("p_JJEW_BKG_MCFM_JECNominal",&p_JJEW_BKG_MCFM_JECNominal);
	  tqqzz->SetBranchAddress("p_JJVBF_BKG_MCFM_JECNominal",&p_JJVBF_BKG_MCFM_JECNominal);
	  tqqzz->SetBranchAddress("p_JJQCD_BKG_MCFM_JECNominal",&p_JJQCD_BKG_MCFM_JECNominal);
	  tqqzz->SetBranchAddress("DiJetMass",&DiJetMass);
          tqqzz->SetBranchAddress("DiJetDEta",&DiJetDEta);
	  tqqzz->SetBranchAddress("KFactor_QCD_ggZZ_Nominal",&KFactorQCDggzz_Nominal);
	  //additional and output variable declarations
	  float weight, weight_up, weight_dn;
	  float weight_vbf, weight_vbf_up, weight_vbf_dn;
	  int chan;
	  int vbfcate = 0;
	  float dbkg_kin;
	  
	  //output branches
	  TTree *tnew = new TTree("SelectedTree","SelectedTree");
	  tnew->Branch("mreco",&ZZMass,"mreco/F");
	  tnew->Branch("dbkg_kin",&dbkg_kin,"dbkg_kin/F");
	  tnew->Branch("weight",&weight,"weight/F");
	  tnew->Branch("weight_up",&weight_up,"weight_up/F");
	  tnew->Branch("weight_dn",&weight_dn,"weight_dn/F");
	  tnew->Branch("weight_vbf",&weight_vbf,"weight_vbf/F");
	  tnew->Branch("weight_vbf_up",&weight_vbf_up,"weight_vbf_up/F");
	  tnew->Branch("weight_vbf_dn",&weight_vbf_dn,"weight_vbf_dn/F");
	  tnew->Branch("chan",&chan,"chan/I");
	  tnew->Branch("vbfcate",&vbfcate,"vbfcate/I");
	  
	  //loop on entries
	  int enne = tqqzz->GetEntries();
  
	  for(int i=0;i<enne;i++){
	    tqqzz->GetEntry(i);
	    
	    //unique selection condition (see paper page 8) & DiJetMass condition  
	    //unique selection
	    //	if(nExtraLep==0 && (((nCleanedJetsPt30==2||nCleanedJetsPt30==3)&&nCleanedJetsPt30BTagged_bTagSF<=1)||(nCleanedJetsPt30>=4&&nCleanedJetsPt30BTagged_bTagSF==0))){
	    
	    //set vbf_category
	    vbfcate=1;
	    //weight definition
	    //KFactorEWKqqZZ = 1;
	    //KFactorQCDqqZZ_M = 1;
	    //weight=1;
	    weight= (xsec*overallEventWeight*L1prefiringWeight*lumi)/(gen_sum_weights);
	    
	    //division in channels
	    if(abs(Z1Flav)==abs(Z2Flav) && abs(Z1Flav)==121) chan=2;
	    else if (abs(Z1Flav)==abs(Z2Flav) && abs(Z1Flav)!=121) chan=1;
	    else chan=3;
	    
	    //kin variable
	    if(ZZMass > 160 && Z1Mass < 120 && Z1Mass > 60 && Z2Mass < 120 && Z2Mass > 60){

	      for(int il = 0; il < vars+2; il++){
		
		int iv = il; 
                
		if ( !(il == 1 || il > 7) ) continue;
		if (il == 1) dbkg_kin = ZZMass;
    		if (il == 8) {dbkg_kin = Z1Mass;   iv = 6;}
		if (il == 9) {dbkg_kin = Z2Mass;   iv = 7;}
		
   	      
		//1D kin var hist fill
		//this is the normalization histogram

		if (j==0){                     
		  h1[iv]->Fill(dbkg_kin,weight);
		  
		  if (chan == 1) h8[iv]->Fill(dbkg_kin,weight); //mu
		  if (chan == 2) h7[iv]->Fill(dbkg_kin,weight); //e
		  if (chan == 3)  h9[iv]->Fill(dbkg_kin,weight);          //mu+e
		}
		if (j==1){                              //gg
		  h2[iv]->Fill(dbkg_kin,weight);
		  
		  if (chan == 1) h11[iv]->Fill(dbkg_kin,weight); //mu
		  if (chan == 2) h10[iv]->Fill(dbkg_kin,weight); //e
		  if (chan == 3)  h12[iv]->Fill(dbkg_kin,weight);          //mu+e
		}
		
	      }
	    }

	    if(ZZMass > 160 && Z1Mass < 120 && Z1Mass > 60 && Z2Mass < 120 && Z2Mass > 60 && DiJetMass>150 && nExtraLep==0 &&  (((nCleanedJetsPt30==2||nCleanedJetsPt30==3)&&nCleanedJetsPt30BTagged_bTagSF<=1)||(nCleanedJetsPt30>=4&&nCleanedJetsPt30BTagged_bTagSF==0))){

	      for(int il = 0; il < vars+2; il++){
		
		int iv = il; 
                
		if (il == 1 || il > 7) continue;
	      
		float c_mzz = c_constant*ts->Eval(ZZMass);
		if (il == 0) dbkg_kin = p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+ p_JJQCD_BKG_MCFM_JECNominal*c_mzz);
		if (il == 2) dbkg_kin = DiJetMass;
		if (il == 3) dbkg_kin = fabs(DiJetDEta);
		if (il == 4) dbkg_kin = JetPt->at(0);
		if (il == 5) dbkg_kin = JetEta->at(0);
		if (il == 6) {dbkg_kin = JetPt->at(1);   iv = 4;}
		if (il == 7) {dbkg_kin = JetEta->at(1);   iv = 5;}
		  
		if (j==0){                     
		  h1[iv]->Fill(dbkg_kin,weight);
		  
		  if (chan == 1) h8[iv]->Fill(dbkg_kin,weight); //mu
		  if (chan == 2) h7[iv]->Fill(dbkg_kin,weight); //e
		  if (chan == 3) h9[iv]->Fill(dbkg_kin,weight);          //mu+e
		}
		if (j==1){                              //gg
		  h2[iv]->Fill(dbkg_kin,weight);
		  
		  if (chan == 1) h11[iv]->Fill(dbkg_kin,weight); //mu
		  if (chan == 2) h10[iv]->Fill(dbkg_kin,weight); //e
		  if (chan == 3)  h12[iv]->Fill(dbkg_kin,weight);          //mu+e
		}		
	      }
	    }
	  }//entries loop  end
	  
	}//file loop  end

	for(int iv = 0; iv < vars; iv++){
	  cout << "Integral check" << endl;
	  cout <<"ggzz old,         integral is " << h1[iv]->Integral() << endl;
          cout <<"ggzz new,         integral is " << h2[iv]->Integral() << endl;
	  	 
	  //data normalisation
	  float data_integral = h1[iv]->Integral();
	  float mc_integral = h2[iv]->Integral();
	  // h2[iv]->Scale(data_integral/mc_integral);

	  h1[iv]->SetLineColor(kRed);
          h1[iv]->SetLineWidth(3);
	  h2[iv]->SetMarkerStyle(20);

	  // TH1F *h1divide = (TH1F*)h1[iv]->Clone();
		  
	  // draw the legend
	  TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.04);
	  legend->AddEntry(h1[iv],"VBS (Phantom)","l");
	  legend->AddEntry(h2[iv],"VBS (MadGraph)","lep");
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
	  h2[iv]->SetMinimum(0.);
          h1[iv]->Draw("hist");
          h2[iv]->Draw("epsame");
	  h2[iv]->GetXaxis()->SetTitle(titlex[iv].c_str());
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
	  TH1F *h1copy = (TH1F*)h1[iv]->Clone();
          
	  //axis labels
	  h1copy->GetXaxis()->SetLabelFont(59);//change this for font type
	  h1copy->GetXaxis()->SetLabelSize(22);
	  h1copy->GetYaxis()->SetLabelFont(59);//change this for font type
	  h1copy->GetYaxis()->SetLabelSize(22);
	  //axis titles
	  h1copy->GetXaxis()->SetTitleFont(59); //change this for font type
	  h1copy->GetXaxis()->SetTitleSize(22);
	  h1copy->GetYaxis()->SetTitleFont(59); //change this for font type
	  h1copy->GetYaxis()->SetTitleSize(22);
	  h1copy->GetXaxis()->SetTitleOffset(4.5);
	  h1copy->GetYaxis()->SetTitleOffset(1.7);
	  h1copy->GetYaxis()->SetRangeUser(-0.75,2.25);
	  
	  // h1copy->Sumw2();
	  h1copy->SetStats(0); //clear stat box
	  h1copy->Divide(h2[iv]); //invert divide
	  h1copy->SetMarkerStyle(20);
	  string title = " ;"+titlex[iv]+"; MCFM/MadG";
	  h1copy->SetTitle(title.c_str());
	  //h0copy->GetXaxis()->SetTitleSize(50);
	  //h0copy->GetXaxis()->SetLabelSize(35);
	  //h0copy->GetYaxis()->SetTitleSize(15);
	  //h0copy->GetYaxis()->SetLabelSize(15);
	  
	  //gStyle->SetLabelSize(2,"x").
	  h1copy->Draw("ep");
	  
	  //Orizontal line
	  TLine *line = new TLine(xmin[iv],1,xmax[iv],1);
	  line->SetLineColor(kRed);
	  line->SetLineStyle(2);
	  line->Draw("same");
	  
	  //close and print on file
	  c1->cd();
	  sprintf(filename,"comparevbs/%s_plot_compare.png",namegif[iv].c_str());
	  gPad->Print(filename);
	}
}
