// #include "external_cConstants.h"
#include <TSpline.h>
#include <TString.h>
#include <memory>

void plotterSystPDF(int year = 2018, int whichSample = 1){
  
       //whichSample = 0 : use just qqZZ
       //whichSample = 1 : use just ggZZ
       //whichSample = 2 : use just VBS
    
        float lumi = 35.9;
        if (year == 2017) lumi = 41.5;
	if (year == 2018) lumi = 59.7;

	//scale vars
	static const int vars = 3;

        string titlex = "K_{D}";        
        string titley = "Events/0.025";     
	string namegif = "Dbkgkin";
        int bins = 20;
        float xmin = 0.;
	float xmax = 1.;
	float variations[vars];

	//histogram stack
        char filename[300]; char filetitle[300]; 

        //histograms
	TH1F *h1[vars+2]; //ew
	TH1F *hratio[vars+2]; //ew

	for(int iv = 0; iv < vars+2; iv++){
	  sprintf(filename,"h1_%d",iv);
	  sprintf(filetitle,"CMS Preliminary                %2.1f fb^{-1};%s;%s",lumi,titlex.c_str(),titley.c_str()); 
	  h1[iv] = new TH1F(filename,filetitle,bins,xmin,xmax); //ew
	  h1[iv]->Sumw2();
	  sprintf(filename,"hratio_%d",iv);
	  hratio[iv] = new TH1F(filename,filetitle,bins,xmin,xmax); //ew
	  hratio[iv]->Sumw2();
	}
	lumi *= 1000;
   
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
 	sprintf(filename,"newsamples%d_withMGggZZandVBS.txt",year);

	ifstream parInput(filename);
        
	if (parInput.is_open()) {
	  while ( parInput.good() ) {
	    parInput >> rootname[nSamp]; 
            cout << nSamp << " " <<  rootname[nSamp] << endl; 
	    nSamp++;
	  }
	  parInput.close();
	} 

	//original variable declarations
	float ZZPt,ZZMass,Z1Mass,Z2Mass,DiJetMass,DiJetDEta;
	float xsec,KFactorEWKqqZZ,overallEventWeight,L1prefiringWeight,genHEPMCweight,KFactorQCDqqZZ_M;
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
	float LHEweight_PDFVariation_Up, LHEweight_PDFVariation_Dn;
	
	//new variable declarations
	float p_JJEW_BKG_MCFM_JECNominal; //not in use
	float p_JJQCD_BKG_MCFM_JECNominal;
	float p_JJVBF_BKG_MCFM_JECNominal;
	float KFactorQCDggzz_Nominal;

	//additional and output variable declarations
	float weight, weight_up, weight_dn;
	float weight_vbf, weight_vbf_up, weight_vbf_dn;
	int chan;
	int vbfcate = 0;
	float dbkg_kin, theVar; 
	
	//output branches
	/* TTree *tnew[4]; 
	TFile *fnew[4];
	//template declarations (1D) 
	TH1F *temp_1d_4e[4];
	TH1F *temp_1d_4mu[4];
	TH1F *temp_1d_2e2mu[4];
	//template declarations (2D) 
	TH2F *temp_zz_4e[4];
	TH2F *temp_zz_4mu[4];
	TH2F *temp_zz_2e2mu[4];

	for (int it=0; it < 4; it++) {
	  if (it==0) sprintf(filename,"template/root_output_files/qqzz_Moriond_%d.root",year); 
	  if (it==1) sprintf(filename,"template/root_output_files/ggzz_Moriond_%d.root",year); 
	  if (it==2) sprintf(filename,"template/root_output_files/vbs_Moriond_%d.root",year); 
	  if (it==3) sprintf(filename,"template/root_output_files/data_%d.root",year); 
	  fnew[it] = new TFile(filename,"recreate");
	  tnew[it] = new TTree("SelectedTree","SelectedTree");
	  tnew[it]->Branch("mreco",&ZZMass,"mreco/F");
	  tnew[it]->Branch("dbkg_kin",&dbkg_kin,"dbkg_kin/F");
	  tnew[it]->Branch("weight",&weight,"weight/F");
	  tnew[it]->Branch("weight_up",&weight_up,"weight_up/F");
	  tnew[it]->Branch("weight_dn",&weight_dn,"weight_dn/F");
	  tnew[it]->Branch("chan",&chan,"chan/I");
	  tnew[it]->Branch("vbfcate",&vbfcate,"vbfcate/I");
	  temp_zz_4e[it] = new TH2F("temp_zz_4e","",nbins,xbin,40,0.,1.);
	  temp_zz_4mu[it] = new TH2F("temp_zz_4mu","",nbins,xbin,40,0.,1.);
	  temp_zz_2e2mu[it] = new TH2F("temp_zz_2e2mu","",nbins,xbin,40,0.,1.);
	  temp_1d_4e[it] = new TH1F("temp_1d_4e","",50,0.,1.);
	  temp_1d_4mu[it] = new TH1F("temp_1d_4mu","",50,0.,1.);
	  temp_1d_2e2mu[it] = new TH1F("temp_1d_2e2mu","",50,0.,1.);
	  }  */
	
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
          bool process = false;
          process = (((rootname[is].Contains("ggTo") || rootname[is].Contains("ggZZnew")) && whichSample==1) || (rootname[is].Contains("VBFTo") && whichSample==2) || (rootname[is].Contains("amcatnlo") && whichSample==0));
	  if (!process) continue;

          j = whichSample;
	  //histogram declaration
	  //TH1F *kin_zz = new TH1F("kin_zz","",bins,xmin,xmax); //was 100 bins
	  
	
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
	  tqqzz->SetBranchAddress("genHEPMCweight",&genHEPMCweight);
	  tqqzz->SetBranchAddress("L1prefiringWeight",&L1prefiringWeight);
	  tqqzz->SetBranchAddress("KFactor_QCD_qqZZ_M",&KFactorQCDqqZZ_M);
	  tqqzz->SetBranchAddress("nCleanedJetsPt30",&nCleanedJetsPt30);
	  
	  //new branch addresses
	  tqqzz->SetBranchAddress("p_JJEW_BKG_MCFM_JECNominal",&p_JJEW_BKG_MCFM_JECNominal);
	  tqqzz->SetBranchAddress("p_JJVBF_BKG_MCFM_JECNominal",&p_JJVBF_BKG_MCFM_JECNominal);
	  tqqzz->SetBranchAddress("p_JJQCD_BKG_MCFM_JECNominal",&p_JJQCD_BKG_MCFM_JECNominal);
	  tqqzz->SetBranchAddress("LHEweight_PDFVariation_Up",&LHEweight_PDFVariation_Up);
          tqqzz->SetBranchAddress("LHEweight_PDFVariation_Dn",&LHEweight_PDFVariation_Dn);	  
	  tqqzz->SetBranchAddress("DiJetMass",&DiJetMass);
          tqqzz->SetBranchAddress("DiJetDEta",&DiJetDEta);
	  tqqzz->SetBranchAddress("KFactor_QCD_ggZZ_Nominal",&KFactorQCDggzz_Nominal);

	  //loop on entries
	  int enne = tqqzz->GetEntries();

	  // preliminary loop to fix MG wrong weights (only VBS 2017-18)
	  float resum = gen_sum_weights;
	  float sum = hCounters->GetBinContent(1);
          if (j==2 && year>2016) resum = hCounters->GetBinContent(1);
  
	  for(int iv=0;iv<vars;iv++){

	    for(int i=0;i<enne;i++){
	    tqqzz->GetEntry(i);
	    
	   	    //unique selection condition (see paper page 8) & DiJetMass condition
	    // if(DiJetMass>100 && nExtraLep==0 && ZZMass > 160 &&(((nCleanedJetsPt30==2||nCleanedJetsPt30==3)&&nCleanedJetsPt30BTagged_bTagSF<=1)||(nCleanedJetsPt30>=4&&nCleanedJetsPt30BTagged_bTagSF==0))){
	    
	    if(DiJetMass>100 && ZZMass > 180 && nCleanedJetsPt30>1 && Z1Mass < 120 && Z1Mass > 60 && Z2Mass < 120 && Z2Mass > 60){
	    
	      // if(DiJetMass>100 && ZZMass > 180 && nCleanedJetsPt30>1 && Z1Mass < 120 && Z1Mass > 60 && Z2Mass < 120 && Z2Mass > 60 && JetPt->at(0) > 50 && JetPt->at(1) > 50){
	      
	      //set vbf_category
	      vbfcate=1;
	      //weight definition
	      //KFactorEWKqqZZ = 1;
	      //KFactorQCDqqZZ_M = 1;
	      //weight=1;
	      
	      weight= (sum*KFactorEWKqqZZ*overallEventWeight*KFactorQCDqqZZ_M*L1prefiringWeight*lumi)/(resum);
	      // correct k-factor for NNLO/NLO?
	      if (j==1) weight= (sum*overallEventWeight*KFactorQCDggzz_Nominal*L1prefiringWeight*lumi)/(resum);
	      //if (j==1) weight /=1.7;
              if (j==2 && year==2016) weight= (sum*overallEventWeight*L1prefiringWeight*lumi)/(resum);
              if (j==2 && year>2016) weight= (sum*overallEventWeight*L1prefiringWeight*lumi)/(genHEPMCweight*resum);             
	    
	      if (iv == 1) weight *= LHEweight_PDFVariation_Up;
              if (iv == 2) weight *= LHEweight_PDFVariation_Dn;
	   
	      //TEMPORARY FOR MISSING 2e2mu SAMPLE
	      //if (j==2 && year==2017) weight *= 2.;

	      //division in channels
	      if(abs(Z1Flav)==abs(Z2Flav) && abs(Z1Flav)==121) chan=2;
	      else if (abs(Z1Flav)==abs(Z2Flav) && abs(Z1Flav)!=121) chan=1;
	      else chan=3;
	      
	      //kin variable
              float c_mzz = c_constant*ts->Eval(ZZMass);
	      dbkg_kin = p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+ p_JJQCD_BKG_MCFM_JECNominal*c_mzz);
	      if (dbkg_kin < 0.00 || dbkg_kin > 1.00) continue;

	      // fill templates
	      /* if ((useMCatNLO > 0 && j==4) || j==5) {
		tnew[0]->Fill();
		if(chan==1) { temp_zz_4mu[0]->Fill(ZZMass,dbkg_kin,weight); temp_1d_4mu[0]->Fill(dbkg_kin,weight); } 
		else if(chan==2) { temp_zz_4e[0]->Fill(ZZMass,dbkg_kin,weight); temp_1d_4e[0]->Fill(dbkg_kin,weight); }
	        else { temp_zz_2e2mu[0]->Fill(ZZMass,dbkg_kin,weight); temp_1d_2e2mu[0]->Fill(dbkg_kin,weight); }
	      } else if ((useMCatNLO == 0 && j==0) || j==5) {
		tnew[0]->Fill();
		if(chan==1) { temp_zz_4mu[0]->Fill(ZZMass,dbkg_kin,weight); temp_1d_4mu[0]->Fill(dbkg_kin,weight); }
		else if(chan==2) { temp_zz_4e[0]->Fill(ZZMass,dbkg_kin,weight);  temp_1d_4e[0]->Fill(dbkg_kin,weight); }
	        else { temp_zz_2e2mu[0]->Fill(ZZMass,dbkg_kin,weight); temp_1d_2e2mu[0]->Fill(dbkg_kin,weight); }
	      } else if (j==1) {
		tnew[1]->Fill();
		temp_zz_4mu[1]->Fill(ZZMass,dbkg_kin,weight);  temp_1d_4mu[1]->Fill(dbkg_kin,weight);
		temp_zz_4e[1]->Fill(ZZMass,dbkg_kin,weight);  temp_1d_4e[1]->Fill(dbkg_kin,weight);
	        temp_zz_2e2mu[1]->Fill(ZZMass,dbkg_kin,weight);  temp_1d_2e2mu[1]->Fill(dbkg_kin,weight);
	      } else {
		tnew[j]->Fill();
		if(chan==1) { temp_zz_4mu[j]->Fill(ZZMass,dbkg_kin,weight);  temp_1d_4mu[j]->Fill(dbkg_kin,weight); }
		else if(chan==2) { temp_zz_4e[j]->Fill(ZZMass,dbkg_kin,weight); temp_1d_4e[j]->Fill(dbkg_kin,weight); } 
	        else { temp_zz_2e2mu[j]->Fill(ZZMass,dbkg_kin,weight);  temp_1d_2e2mu[j]->Fill(dbkg_kin,weight); }
		}  */

             
	      h1[iv]->Fill(dbkg_kin,weight);
	    }
	  }//entries loop  end
	}//file loop  end
       
	  /* for (int it=0; it < 4; it++) {
	  fnew[it]->cd();
	  if (it < 3) {
	    TH2F* final_4e = rebinTemplate(temp_zz_4e[it],year,it);
	    final_4e->Write();
	    temp_1d_4e[it]->Write();
	    TH2F* final_4mu = rebinTemplate(temp_zz_4mu[it],year,it);
	    final_4mu->Write();
	    temp_1d_4mu[it]->Write();
	    TH2F* final_2e2mu = rebinTemplate(temp_zz_2e2mu[it],year,it);
	    final_2e2mu->Write();
	    temp_1d_2e2mu[it]->Write();
	  }
	  tnew[it]->Write();
	  fnew[it]->Close();
	} */
	  for(int iv=0;iv<vars;iv++){
            hratio[iv]->Add(h1[iv],h1[0],1,-1);
	    hratio[iv]->Divide(hratio[iv],h1[0]);
	  } 
	  
	  for(int binx=1;binx<hratio[0]->GetXaxis()->GetNbins()+1;binx++){
	    float theMax = 0;   float theMin = 0;
	    for(int iv=1;iv<vars;iv++){  
	      if (hratio[iv]->GetBinContent(binx) > theMax) {
		hratio[vars]->SetBinContent(binx, hratio[iv]->GetBinContent(binx));  
		hratio[vars]->SetBinError(binx, hratio[iv]->GetBinError(binx));
		theMax = hratio[iv]->GetBinContent(binx); 
	      }
	      if (hratio[iv]->GetBinContent(binx) < theMin) {
		hratio[vars+1]->SetBinContent(binx, hratio[iv]->GetBinContent(binx));  
		hratio[vars+1]->SetBinError(binx, hratio[iv]->GetBinError(binx));
		theMin = hratio[iv]->GetBinContent(binx);
	      } 
	    }
	  } 
	  
	  hratio[0]->SetLineColor(1);
	  hratio[vars]->SetLineColor(2);
	  hratio[vars+1]->SetLineColor(4);
	
	  // draw the legend
	  TLegend *legend=new TLegend(0.6,0.75,0.85,0.88);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.04);
	 
	  legend->AddEntry(hratio[0],"nominal","lep");
	  legend->AddEntry(hratio[vars],"up","lep");
	  legend->AddEntry(hratio[vars+1],"down","lep");
	  legend->SetBorderSize(0);
	  
	  //GRAPHICS
	  //hs->GetXaxis()->SetTitle("K_{D}");
	  //hs->GetXaxis()->SetTitleSize(.15);
	  //hs->GetYaxis()->SetTitle("Events/0.05");
	  //hs->GetYaxis()->SetTitleSize(.15);
	  
	  //RATIO PLOT
	  //canvas
	  TCanvas *c1 = new TCanvas("c1","example",800,800);
	  //pad1
	  /* float eps =0;// 0.006;
	  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1,0);
	  pad1->SetBottomMargin(0);
	  pad1->Draw();
	  pad1->cd();  */
	  //top plot
	  hratio[0]->GetXaxis()->SetTitle(titlex.c_str());
	  hratio[0]->SetMaximum(0.8);
          hratio[0]->SetMinimum(-0.8);
	  hratio[0]->Draw(); //old
          hratio[vars]->Fit("pol0","","e1same");
          hratio[vars+1]->Fit("pol0","","e1same");
	  legend->Draw("same");
	  TLine *line = new TLine(xmin,0.,xmax,0.);
	  line->SetLineColor(kBlack);
	  line->SetLineStyle(2);
	  line->Draw("same");
	  //switch?
	  
	  //close and print on file
	  // c1->cd();
	  if (whichSample == 0) sprintf(filename,"syst/%s_qqZZ_SystPDF_%d.png",namegif.c_str(),year);      
	  if (whichSample == 1) sprintf(filename,"syst/%s_ggZZ_SystPDF_%d.png",namegif.c_str(),year);
	  if (whichSample == 2) sprintf(filename,"syst/%s_VBS_SystPDF_%d.png",namegif.c_str(),year);
	  c1->Print(filename);
	}
}
