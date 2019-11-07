// #include "external_cConstants.h"
#include <TSpline.h>
#include <TString.h>
#include <memory>

TH2F* rebinTemplate(TH2F* orig, int year=2016, int itype=0) {

  char filename[300];    char pname[30];
  if (itype == 0) sprintf(pname,"qqzz");
  if (itype == 1) sprintf(pname,"ggzz");
  if (itype == 2) sprintf(pname,"vbs");

  TH2F* tempt = (TH2F*)orig->Clone();
   for(int binx=0;binx<tempt->GetXaxis()->GetNbins();binx++){
     double inttmp1 = tempt->Integral(binx+1,binx+1);
     for(int biny=0;biny<tempt->GetNbinsY();biny++){
	if(inttmp1!=0 )
	  tempt->SetBinContent(binx+1, biny+1, tempt->GetBinContent(binx+1,biny+1)/inttmp1);
      }
   }      
   tempt->Smooth();
   int nbinsfinal=230;
   double xbinfinal[231]={
      160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,258,260,262,264,266,268,270,272,274,276,278,280,282,284,286,288,290,292,294,296,298,300,302,304,306,308,310,312,314,316,318,320,322,324,326,328,330,332,334,336,338,340,342,344,346,348,350,352,354,356,358,360,362,364,366,368,370,372,374,376,378,380,382,384,386,388,390,392,394,396,398,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,1000,1010,1020,1030,1040,1050,1060,1070,1080,1090,1100,1110,1120,1130,1140,1150,1160,1170,1180,1190,1200,1210,1220,1230,1240,1250,1260,1270,1280,1290,1300,1310,1320,1330,1340,1350,1360,1370,1380,1390,1400,1410,1420,1430,1440,1450,1460,1470,1480,1490,1500
    };
   TH2F *result = new TH2F(orig->GetName(),orig->GetTitle(),nbinsfinal,xbinfinal,40,0.,1.);
    
   for(int binx=0;binx<result->GetXaxis()->GetNbins();binx++){
      int b = tempt->GetXaxis()->FindBin(result->GetXaxis()->GetBinCenter(binx+1));
      for(int biny=0;biny<40;biny++){
	float bc = tempt->GetBinContent(b,biny+1);
	result->SetBinContent(binx+1,biny+1,bc);

      }
    }

   result->Draw("colz");
   sprintf(filename,"template/plots/%s_%s_%d.png",orig->GetName(),pname,year);
   gPad->Print(filename);
   return result;    
}

void plotterAndTemplateMaker(int year = 2018, int useMCatNLO = 1){
  
       //useMCatNLO = 0 : use just POWHEG
       //useMCatNLO = 1 : use just aMCatNLO
       //useMCatNLO = 2 : use aMCatNLO for shape, POWHEG for integral

        float lumi = 35.9;
        if (year == 2017) lumi = 41.5;
	if (year == 2018) lumi = 59.7;

	static const int vars = 6;
        string titlex[vars] = {"K_{D}","M_{4l} [GeV]","M_{jj} [GeV]","#Delta #eta_{jj}","p_{T,j}","#eta_{j}"};        
        string titley[vars] = {"Events/0.025","Events/16 GeV","Events/22.5 GeV","Events/0.175","Events/5 GeV","Events/0.25"};     
	string namegif[vars] = {"Dbkgkin","m4l","mjj","detajj","ptj","etaj"};
        int bins[vars] = {20,20,20,20,30,20};
        float xmin[vars] = {0.,160.,100.,0.,0.,-5.};
	float xmax[vars] = {1.,800.,1000.,8.,300.,5.};	
	bool drawSignal[vars] = {false,false,true,true,true,true};

	//histogram stack
        char filename[300]; char filetitle[300];
	THStack *hs[vars];
        for(int iv = 0; iv < vars; iv++){
	  sprintf(filename,"hs%d",iv);   
	  sprintf(filetitle,"CMS Preliminary                %2.1f fb^{-1};%s;%s",lumi,titlex[iv].c_str(),titley[iv].c_str());  
	  hs[iv] = new THStack(filename,filetitle);
	}  

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
	TH1F *h2bis[vars];//for 2018 rescale
	TH1F *h3bis[vars];//for 2018 rescale

	for(int iv = 0; iv < vars; iv++){
	  sprintf(filename,"hcd%d",iv);   h_complete_data[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //all data
	  sprintf(filename,"h00_%d",iv);   h00[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //bkg_kin<0.7 cut full background plot
	  sprintf(filename,"h0_%d",iv);   h0[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //data, because we are hiding higher energies in this phase
	  sprintf(filename,"h1_%d",iv);   h1[iv] = new TH1F(filename,"h1;xtitle;ytitle",bins[iv],xmin[iv],xmax[iv]); //ew
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
	  sprintf(filename,"h2bis_%d",iv); h2bis[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//for 2018 rescale
	  sprintf(filename,"h3bis_%d",iv); h3bis[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]);//for 2018 rescale
	}   
	gStyle->SetPalette(1);
	TFile *input_file;
        int nbins=17;
	double xbin[18]={
	  160,166,170,176,182,188,194,
	  200,208,216,224,234,246,260,278,302,338,1500
	}; 

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
	TTree *tnew[4]; 
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
	  if (rootname[is].Contains("AllData")) j = 3;   
	  if (rootname[is].Contains("ggTo") || rootname[is].Contains("ggZZnew")) j = 1;      
          if (rootname[is].Contains("VBFTo")) j = 2;
	  if (rootname[is].Contains("amcatnlo")) j = 4;
	  if (rootname[is].Contains("WWZ") || rootname[is].Contains("TTZ")) j = 5;   
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
	  tqqzz->SetBranchAddress("DiJetMass",&DiJetMass);
          tqqzz->SetBranchAddress("DiJetDEta",&DiJetDEta);
	  tqqzz->SetBranchAddress("KFactor_QCD_ggZZ_Nominal",&KFactorQCDggzz_Nominal);

	  //loop on entries
	  int enne = tqqzz->GetEntries();

	  // preliminary loop to fix MG wrong weights (only VBS 2017-18)
	  float resum = gen_sum_weights;
          if (j==2 && year>2016) resum = hCounters->GetBinContent(1);
  
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

	      
	      weight= (xsec*KFactorEWKqqZZ*overallEventWeight*KFactorQCDqqZZ_M*L1prefiringWeight*lumi)/(resum);
	      // correct k-factor for NNLO/NLO?
	      if (j==1) weight= (xsec*overallEventWeight*KFactorQCDggzz_Nominal*L1prefiringWeight*lumi)/(resum);
	      if (j==1 && useMCatNLO==1) weight /=1.7;
              if (j==2 && year==2016) weight= (xsec*overallEventWeight*L1prefiringWeight*lumi)/(resum);
              if (j==2 && year>2016) weight= (xsec*overallEventWeight*L1prefiringWeight*lumi)/(genHEPMCweight*resum);             
	      if (j==5) weight= (xsec*overallEventWeight*L1prefiringWeight*lumi)/(resum);
	      if (j==3) weight=1.; 

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
	      if ((useMCatNLO > 0 && j==4) || j==5) {
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
	      }

              // fill plots
	      for(int il = 0; il < vars+2; il++){
                int iv = il; 
		if (il == 0) theVar = dbkg_kin;
		if (il == 1) theVar = ZZMass;
		if (il == 2) theVar = DiJetMass;
		if (il == 3) theVar = fabs(DiJetDEta);
                if (il == 4) theVar = JetPt->at(0);
                if (il == 5) theVar = JetEta->at(0);
                if (il == 6) {theVar = JetPt->at(1);   iv = 4;}
		if (il == 7) {theVar = JetEta->at(1);   iv = 5;}
   	      
		//1D kin var hist fill
		//this is the normalization histogram
		if (j<3){
		  if (theVar <= 1.1) h00[iv]->Fill(theVar,weight);    
		  h_complete_data[iv]->Fill(theVar,weight);
		}
		
		if (j==3){
		  if (iv > 0 || theVar < 0.75 || year == 2016) h0[iv]->Fill(theVar);
		  else cout << "Blinded event!" << endl;
		  h0[iv]->SetMarkerStyle(20);
		  if (chan == 2) h0_ee[iv]->Fill(theVar);
		  if (chan == 1) h0_mm[iv]->Fill(theVar);
		  if (chan == 3) h0_em[iv]->Fill(theVar);
		}
		if (j==0){                              //qqzz
		  h1[iv]->Fill(theVar,weight);
		  
		  /* if (chan == 1) h8[iv]->Fill(theVar,weight); //mu
		  if (chan == 2) h7[iv]->Fill(theVar,weight); //e
		  if (chan == 3)  h9[iv]->Fill(theVar,weight);  */        //mu+e
		}
		if (j==1){                              //gg
		  h2[iv]->Fill(theVar,weight);
		  h2[iv]->SetFillColor(kBlue);
		  
		  if (chan == 1) h11[iv]->Fill(theVar,weight); //mu
		  if (chan == 2) h10[iv]->Fill(theVar,weight); //e
		  if (chan == 3)  h12[iv]->Fill(theVar,weight);          //mu+e
		  
		}
		if (j==2){                              //vbs
		  h3[iv]->Fill(theVar,weight);
		  h3[iv]->SetFillColor(kMagenta);

		  if (chan == 1) h14[iv]->Fill(theVar,weight); //mu
		  if (chan == 2) h13[iv]->Fill(theVar,weight); //e
		  if (chan == 3) h15[iv]->Fill(theVar,weight);          //mu+e
		  
		}
		if (j==4) {
		  h2bis[iv]->Fill(theVar,weight);

		  if (chan == 1) h8[iv]->Fill(theVar,weight); //mu
		  if (chan == 2) h7[iv]->Fill(theVar,weight); //e
		  if (chan == 3)  h9[iv]->Fill(theVar,weight);
		}
		if (j==5) h3bis[iv]->Fill(theVar,weight);
		//kin_zz->GetYaxis()->SetTitle("Events/0.05");
		//add histogram to stack
		//for cycle ends here
	      }
	    }
	  }//entries loop  end
	}//file loop  end
       
        for (int it=0; it < 4; it++) {
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
	}

	//ZX CONTRIBUTION
	  
	TChain *tqqzz_zx= new TChain("candTree");
	sprintf(filename,"/afs/cern.ch/work/c/covarell/vbs2017/CMSSW_8_0_26_patch1/src/data_driven_MC/ZX%d_noCut.root",year); 
	tqqzz_zx->Add(filename);
	
	//histogram declaration
	TH1F *kin_zz_zx[vars]; 
	for(int iv = 0; iv < vars; iv++){
	  sprintf(filename,"kinzz%d",iv);   kin_zz_zx[iv] = new TH1F(filename,"",bins[iv],xmin[iv],xmax[iv]); //full histogram
	}
	
	//new variable declarations
	float var_zx, dbkg_kin_zx, ZZMass_zx, DiJetMass_zx, DiJetDEta_zx;
	float ptjet1_zx,ptjet2_zx,etajet1_zx,etajet2_zx; 
	float weight_zx;
	
	//original branch addresses
	tqqzz_zx->SetBranchAddress("dbkg_kin",&dbkg_kin_zx);
	tqqzz_zx->SetBranchAddress("ZZMass",&ZZMass_zx);
	tqqzz_zx->SetBranchAddress("DiJetMass",&DiJetMass_zx);
	tqqzz_zx->SetBranchAddress("DiJetDEta",&DiJetDEta_zx);
	tqqzz_zx->SetBranchAddress("weight",&weight_zx);
	tqqzz_zx->SetBranchAddress("ptjet1",&ptjet1_zx); 
	tqqzz_zx->SetBranchAddress("ptjet2",&ptjet2_zx);   
	tqqzz_zx->SetBranchAddress("etajet1",&etajet1_zx); 
	tqqzz_zx->SetBranchAddress("etajet2",&etajet2_zx);

	//entries loop
	for(int i=0;i<tqqzz_zx->GetEntries();i++){
	  tqqzz_zx->GetEntry(i);
	  
	  //1D kin var hist fill
	  for(int il = 0; il < vars+2; il++){
            int iv = il; 
	    if (iv == 0) var_zx = dbkg_kin_zx;
	    if (iv == 1) var_zx = ZZMass_zx;
	    if (iv == 2) var_zx = DiJetMass_zx;
	    if (iv == 3) var_zx = fabs(DiJetDEta_zx);
	    if (il == 4) var_zx = ptjet1_zx;
	    if (il == 5) var_zx = etajet1_zx;
	    if (il == 6) {var_zx = ptjet2_zx;   iv = 4;}
	    if (il == 7) {var_zx = etajet2_zx;   iv = 5;}
	    if (fabs(weight_zx) < 100000.) {
	      kin_zz_zx[iv]->Fill(var_zx,weight_zx);
	    }
	    if (var_zx<=0.7) h00[iv]->Fill(var_zx,weight_zx);
	    
	  }
	}
	
	//INTEGRAL CHECK
	sprintf(filename,"MCyields_%d.txt",year);
	ofstream yields(filename,std::fstream::app);
        sprintf(filename,"datayields_%d.txt",year);
	ofstream yields2(filename,std::fstream::app);
	sprintf(filename,"MCyields_highMELA_%d.txt",year);
	ofstream yields3(filename,std::fstream::app);
        sprintf(filename,"datayields_highMELA_%d.txt",year);
	ofstream yields4(filename,std::fstream::app);

	for(int iv = 0; iv < vars; iv++){
	  cout << "Integral check" << endl;
	  cout <<"qqzz,         integral is " << h1[iv]->Integral() << endl;
          cout <<"qqzz alternative,         integral is " << h2bis[iv]->Integral() << endl;
	  cout <<"qqzz (4e),    integral is " << h7[iv]->Integral() << endl;
	  cout <<"qqzz (4mu),   integral is " << h8[iv]->Integral() << endl;
	  cout <<"qqzz (2e2mu), integral is " << h9[iv]->Integral() << endl;
	  cout <<"ggzz,         integral is " << h2[iv]->Integral() << endl;
	  cout <<"ggzz (4e),    integral is " << h10[iv]->Integral() << endl;
	  cout <<"ggzz (4mu),   integral is " << h11[iv]->Integral() << endl;
	  cout <<"ggzz (2e2mu), integral is " << h12[iv]->Integral() << endl;
	  cout <<"vbs,          integral is " << h3[iv]->Integral() << endl;
	  cout <<"vbs (4e),     integral is " << h13[iv]->Integral() << endl;
	  cout <<"vbs (4mu),    integral is " << h14[iv]->Integral() << endl;
	  cout <<"vbs (2e2mu),  integral is " << h15[iv]->Integral() << endl;
	  cout <<"data,          integral is " << h0[iv]->Integral() << endl;
	  cout <<"data (4e),     integral is " << h0_ee[iv]->Integral() << endl;
	  cout <<"data (4mu),    integral is " << h0_mm[iv]->Integral() << endl;
	  cout <<"data (2e2mu),  integral is " << h0_em[iv]->Integral() << endl;
	
	  if (iv == 0) { 
	    float vbsee  = h13[iv]->Integral();
	    float vbsemu = h15[iv]->Integral();
            float vbsmumu = h14[iv]->Integral();
	    float vbsee_high  = h13[iv]->Integral(19,20);
	    float vbsemu_high = h15[iv]->Integral(19,20);
            float vbsmumu_high = h14[iv]->Integral(19,20);

	    // TEMPORARY MISSING SAMPLE
	    /* if (year == 2017) {
	      vbsemu_high = (vbsee_high+vbsmumu_high)/2.;
	      vbsee_high /= 2.;       vbsmumu_high /= 2.;
	      vbsemu = (vbsee+vbsmumu)/2.;
	      vbsee /= 2.;       vbsmumu /= 2.;
	      } */
	    
	    yields << vbsmumu << "\t zx4mu \t" << h8[iv]->Integral()*(1. + h3bis[iv]->Integral()/h2bis[iv]->Integral()) << "\t" << h11[iv]->Integral() << "\t" << vbsee << "\t zx4e \t" <<  h7[iv]->Integral()*(1. + h3bis[iv]->Integral()/h2bis[iv]->Integral()) << "\t" << h10[iv]->Integral() << "\t" << vbsemu << "\t zx2e2mu \t" << h9[iv]->Integral()*(1. + h3bis[iv]->Integral()/h2bis[iv]->Integral()) << "\t" << h12[iv]->Integral() << endl;
	    yields2 << h0_mm[iv]->Integral() << "\t" << h0_ee[iv]->Integral() << "\t" << h0_em[iv]->Integral() << endl;
	    yields3 << vbsmumu_high << "\t" << kin_zz_zx[iv]->Integral(19,20)/kin_zz_zx[iv]->Integral() << "\t zx4mu \t" << h8[iv]->Integral(19,20)*(1. + h3bis[iv]->Integral(19,20)/h2bis[iv]->Integral(19,20)) << "\t" << h11[iv]->Integral(19,20) << "\t" << vbsee_high << "\t" << kin_zz_zx[iv]->Integral(19,20)/kin_zz_zx[iv]->Integral() << "\t zx4e \t" <<  h7[iv]->Integral(19,20)*(1. + h3bis[iv]->Integral(19,20)/h2bis[iv]->Integral(19,20)) << "\t" << h10[iv]->Integral(19,20) << "\t" << vbsemu_high << "\t" << kin_zz_zx[iv]->Integral(19,20)/kin_zz_zx[iv]->Integral() << "\t zx2e2mu \t" << h9[iv]->Integral(19,20)*(1. + h3bis[iv]->Integral(19,20)/h2bis[iv]->Integral(19,20)) << "\t" << h12[iv]->Integral(19,20) << endl;
	    yields4 << h0_mm[iv]->Integral(19,20) << "\t" << h0_ee[iv]->Integral(19,20) << "\t" << h0_em[iv]->Integral(19,20) << endl;
	  }
	  
	  float zx_integral = (2.00933+1.97468+3.96839)*lumi/35.9E03;
          const float powheg_integral = h1[iv]->Integral();
	  
	  /* if (year == 2018 && useMCatNLO > 0) {
	    h1[iv]->Multiply(h1[iv],h2bis[iv]);
	    h1[iv]->Divide(h1[iv],h3bis[iv]);
	    }  */
	  //kin_zz_zx[iv]->Scale(zx_integral/kin_zz_zx[iv]->Integral());
	  
	  //data normalisation
	  float data_integral = 1.;// h5->Integral();
	  float mc_integral = 1.; //h_complete_data->Integral();
	  kin_zz_zx[iv]->Scale(data_integral/mc_integral);
	  h1[iv]->Scale(data_integral/mc_integral);
	  h4[iv]->Scale(data_integral/mc_integral);
	  h5[iv]->Scale(data_integral/mc_integral);
	  h2bis[iv]->Scale(data_integral/mc_integral);
          h3bis[iv]->Scale(data_integral/mc_integral);
	  if (useMCatNLO == 2) {
	    // if (year == 2018) h1[iv]->Scale(powheg_integral/h1[iv]->Integral());
	    // else 
	    h2bis[iv]->Scale(powheg_integral/h2bis[iv]->Integral());
	  }
	  
	  //HISTOGRAMS ADDED TO STACK
	  kin_zz_zx[iv]->SetFillColor(kGreen);
          h3bis[iv]->Add(h3bis[iv],kin_zz_zx[iv],1,1);    //tt
	  h3bis[iv]->SetFillColor(kYellow);
	  if (useMCatNLO == 0) h1bis[iv]->Add(h3bis[iv],h1[iv],1,1); //real ew
	  else h1bis[iv]->Add(h3bis[iv],h2bis[iv],1,1); //real ew
	  h1bis[iv]->SetFillColor(kCyan);
	  h4[iv]->Add(h1bis[iv],h2[iv],1,1); //real gg
	  h4[iv]->SetFillColor(kBlue);
	  h5[iv]->Add(h4[iv],h3[iv],1,1);    //real vbs
	  h5[iv]->SetFillColor(kMagenta);
	  
	  //add histograms to stack
	  hs[iv]->Add(h5[iv],"hist");
	  hs[iv]->Add(h4[iv],"hist");
	  hs[iv]->Add(h1bis[iv],"hist");
          hs[iv]->Add(h3bis[iv],"hist");
	  hs[iv]->Add(kin_zz_zx[iv],"hist");
	  TH1F *h0divide = (TH1F*)h0[iv]->Clone();
	  hs[iv]->Add(h0[iv],"E1");
	  
	  // draw the legend
	  TLegend *legend=new TLegend(0.6,0.55,0.85,0.88);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.04);
	  legend->AddEntry(kin_zz_zx[iv],"Z+X","f");
          legend->AddEntry(h3bis[iv],"t#bar{t}Z, WWZ","f");
	  legend->AddEntry(h1bis[iv],"q#bar{q}#rightarrowZZ","f");
	  legend->AddEntry(h4[iv],"gg#rightarrowZZ","f");
	  legend->AddEntry(h5[iv],"VBS","f");
	  legend->AddEntry(h0[iv],"Data","lep");
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
	  hs[iv]->SetMaximum(30.*lumi/35.9E3);
          if (iv == 0 || iv > 3) hs[iv]->SetMaximum(45.*lumi/35.9E3);
	  hs[iv]->Draw("nostack"); //old
	  if (drawSignal[iv]) {
	    TH1F* h77 = (TH1F*)h3[iv]->Clone();
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
	  TH1F *h0copy = (TH1F*) h0divide->Clone();
	  //axis labels
	  h0copy->GetXaxis()->SetLabelFont(59);//change this for font type
	  h0copy->GetXaxis()->SetLabelSize(22);
	  h0copy->GetYaxis()->SetLabelFont(59);//change this for font type
	  h0copy->GetYaxis()->SetLabelSize(22);
	  //axis titles
	  h0copy->GetXaxis()->SetTitleFont(59); //change this for font type
	  h0copy->GetXaxis()->SetTitleSize(22);
	  h0copy->GetYaxis()->SetTitleFont(59); //change this for font type
	  h0copy->GetYaxis()->SetTitleSize(22);
	  h0copy->GetXaxis()->SetTitleOffset(4.5);
	  h0copy->GetYaxis()->SetTitleOffset(1.7);
	  h0copy->GetYaxis()->SetRangeUser(-1.,3.);
	  
	  h0copy->Sumw2();
	  h0copy->SetStats(0); //clear stat box
	  h0copy->Divide(h5[iv]); //invert divide
	  h0copy->SetMarkerStyle(20);
	  string title = " ;"+titlex[iv]+"; Data/MC";
	  h0copy->SetTitle(title.c_str());
	  //h0copy->GetXaxis()->SetTitleSize(50);
	  //h0copy->GetXaxis()->SetLabelSize(35);
	  //h0copy->GetYaxis()->SetTitleSize(15);
	  //h0copy->GetYaxis()->SetLabelSize(15);
	  
	  //gStyle->SetLabelSize(2,"x").
	  h0copy->Draw("ep");
	  
	  //Orizontal line
	  TLine *line = new TLine(xmin[iv],1,xmax[iv],1);
	  line->SetLineColor(kRed);
	  line->SetLineStyle(2);
	  line->Draw("same");
	  
	  //close and print on file
	  c1->cd();
	  if (useMCatNLO == 0) sprintf(filename,"noScaleZX/%s_plot_allPOWHEG_%d.png",namegif[iv].c_str(),year);      
	  if (useMCatNLO == 1) sprintf(filename,"noScaleZX/%s_plot_allMCatNLO_%d.png",namegif[iv].c_str(),year);     
	  if (useMCatNLO == 2) sprintf(filename,"noScaleZX/%s_plot_MCatNLOshape_POWHEGint_%d.png",namegif[iv].c_str(),year);
	  gPad->Print(filename);
	}
}
