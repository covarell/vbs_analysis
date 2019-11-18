//#include "/afs/cern.ch/work/c/covarell/vbs2017/CMSSW_7_4_7/src/HiggsAnalysis/CombinedLimit/src/ProcessNormalization.cc+"
//#include "VerticalInterpPdf.cc+"

using namespace RooFit;

// highmass = 0 onshell
// highmass = 1 offshell
// highmass = 2 search 
//
//
// cate_vbf =0 ggH
// cate_vbf =1 VBF
// cate_vbf =2 RSE
// cate_vbf =3 TLE
//

void dosomething(TString chan="2e2mu", int cate_vbf=1, int highmass=0,int isDbkg=0,int year=2016){

        float lumi = 35.9;
        if (year == 2017) lumi = 41.5;
	if (year == 2018) lumi = 59.7;
	char filename[200];	

	double parzx_all[5][6]={
		//4e
		1,141.9,21.3,0,0,0,
		//4mu
		1,130.4,15.6,0,0,0,
		//2e2mu
		0.45,131.1,18.1,0.55,133.8,18.9,
		//4e RSE
		0.298623315141,238.804039513,38.5525989967,4.83114145422,-0.0097489713697,0,
		//2e2mu RSE
		0.000171310428786,209.221006175,26.5346636174,11.193766044,-0.00296426709129,0
	};
	double parzx_rse_all[2][8]{
		//4e
		2.18216e+01  ,2.99737e+02   ,-2.48222e+02   ,1.38710e+01   ,2.76729e-03   ,2.02956e+02   ,2.54751e+01   ,4.84386e-05 , 
			//2e2mu RSE
			2.19408e+00   ,-1.25292e+02  ,-8.72399e+01   ,1.50523e+01   ,8.52961e-03   ,2.40365e+02   ,4.26689e+01   ,6.19292e-05   
	};
	double parzx[6]={0.};
	double parzx_rse[8]={0.};

	if(cate_vbf!=2){
		if (chan=="4e") 	{
		  for (int i=0;i<6;i++){parzx[i]=parzx_all[0][i];}
		} 
		if (chan=="4mu")  {
		  for (int i=0;i<6;i++){parzx[i]=parzx_all[1][i];}
		}
		if (chan=="2e2mu") {
		  for (int i=0;i<6;i++){parzx[i]=parzx_all[2][i];}
		} 
	}
	else{
		if (chan=="2e2mu") {
		  for (int i=0;i<8;i++){parzx_rse[i]=parzx_rse_all[1][i];}
		} 
		if (chan=="4e") {
		   for (int i=0;i<8;i++){parzx_rse[i]=parzx_rse_all[0][i];}
		} 
	}
	sprintf(filename,"yields_%d.txt",year);
	ofstream yields(filename,std::fstream::app);

		RooWorkspace w("w");
	//	double recolowarr[3]={105.,104,110};
	//	double recohigharr[3]={140.,1604.,3500};
	//	const int reconbinsarr[3]={35,750,1695};
		double recolowarr[3]={110,160.,300};
		double recohigharr[3]={3500.,1500.,3500.};
		const int reconbinsarr[3]={1695,1670,1600};
	//	const int reconbinsarr[3]={3390,3390,3200};


		const double low_reco=recolowarr[cate_vbf];
		const double high_reco=recohigharr[cate_vbf];
		const int nbins_reco=reconbinsarr[cate_vbf];

		RooRealVar* mreco= new RooRealVar("mreco","M_{ZZ} (GeV)",180,low_reco,high_reco);//125
		if(cate_vbf==2){
			mreco->SetName("mreco_rse");
			mreco->SetTitle("mreco_rse");
		}

		RooRealVar* dbkg= new RooRealVar("dbkg_kin","Dbkg_{kin} ",0.5,0.,1.);
		RooPlot* frame= mreco->frame(low_reco,high_reco) ;
		if(highmass==2){
			mreco->setBins(nbins_reco);
			dbkg->setBins(30);
		}

		//qqzz pdf
		//TChain *tqqzz= new TChain("ZZTree/candTree");

		// simplify: for ggF, this is qqZZ bkg, for VBF, this should be ggZZ bkg
		// simplify: if no systematics wanted, comment out _up and _dn related stuff
		TString treename[4]={"","","_rse","_tle"};
		TChain *tqqzz= new TChain("SelectedTree"+treename[cate_vbf]);

		TH1F *hqqzz= new TH1F ("hqqzz","",nbins_reco,low_reco,high_reco);
		TH1F *hqqzz_up= new TH1F ("hqqzz_up","",nbins_reco,low_reco,high_reco);
		TH1F *hqqzz_dn= new TH1F ("hqqzz_dn","",nbins_reco,low_reco,high_reco);

		//tqqzz->Add("root://lxcms03://data3/Higgs/160225/ZZTo4l/ZZ4lAnalysis.root");
		//	if(cate_vbf!=2)
		//
		//
		//
		sprintf(filename,"./template/root_output_files/qqzz_Moriond_%d.root",year);
		tqqzz->Add(filename);
		//	else
		//	tqqzz->Add("qqzz_80.root");

		int channum=1;
		if(chan=="2e2mu")
			channum=3;
		else if(chan=="4e")
			channum=2;
		else
			channum=1;

		//	tqqzz->Draw("mreco>>hqqzz",Form("weight*(chan==%d&&vbfcate==%d)",channum,cate_vbf));
		//	tqqzz->Draw("mreco>>hqqzz_up",Form("weight_up*(chan==%d&&vbfcate==%d)",channum,cate_vbf));
		//	tqqzz->Draw("mreco>>hqqzz_dn",Form("weight_dn*(chan==%d&&vbfcate==%d)",channum,cate_vbf));


		RooRealVar* wt= new RooRealVar("weight","wt",180,0.000,1000.); //125
		RooRealVar* wt_up= new RooRealVar("weight_up","wt_up",180,0.000,1000.);//125 
		RooRealVar* wt_dn= new RooRealVar("weight_dn","wt_dn",180,0.000,1000.); //125


		float ZZMass;
		float weight, weight_up, weight_dn;
		int channel;
		tqqzz->SetBranchAddress("mreco",&ZZMass);
		
		if(cate_vbf==1){
			tqqzz->SetBranchAddress("weight",&weight);
			tqqzz->SetBranchAddress("weight_up",&weight_up);
			tqqzz->SetBranchAddress("weight_dn",&weight_dn);
			tqqzz->Draw("mreco>>hqqzz",Form("weight*(chan==%d)",channum));
			tqqzz->Draw("mreco>>hqqzz_dn",Form("weight_dn*(chan==%d)",channum));
			tqqzz->Draw("mreco>>hqqzz_up",Form("weight_up*(chan==%d)",channum));
		}
		else{
			tqqzz->SetBranchAddress("weight_vbf",&weight);
			tqqzz->SetBranchAddress("weight_vbf_up",&weight_up);
			tqqzz->SetBranchAddress("weight_vbf_dn",&weight_dn);
			tqqzz->Draw("mreco>>hqqzz",Form("weight_vbf*(chan==%d)",channum));
			tqqzz->Draw("mreco>>hqqzz_dn",Form("weight_vbf_dn*(chan==%d)",channum));
			tqqzz->Draw("mreco>>hqqzz_up",Form("weight_vbf_up*(chan==%d)",channum));
		}

		tqqzz->SetBranchAddress("chan",&channel);


		if(cate_vbf!=2){
			cout<<"test"<<endl;
			cout<<chan<<"\t"<<cate_vbf<<"\t"<<hqqzz->Integral()*lumi*1000.<<endl;
			cout<<"integral is " << hqqzz->Integral()<<endl;
			cout<<"lumi is" << lumi << endl;
			cout<<chan<<"\t"<<cate_vbf<<"\t"<<hqqzz_up->Integral()*lumi*1000.<<endl;
			cout<<chan<<"\t"<<cate_vbf<<"\t"<<hqqzz_dn->Integral()*lumi*1000.<<endl;
		}
		else{
			cout<<chan<<"\t"<<cate_vbf<<"\t"<<hqqzz->Integral()*lumi*1000.<<endl;  /// Remember why 1.6?
			cout<<chan<<"\t"<<cate_vbf<<"\t"<<hqqzz_up->Integral()*lumi*1000<<endl;
			cout<<chan<<"\t"<<cate_vbf<<"\t"<<hqqzz_dn->Integral()*lumi*1000<<endl;
		}

		TTree *cuttree =new TTree("SelectedTree","SelectedTree");
		TString mrecob = Form("%s/F",mreco->GetName());
		cuttree->Branch(mreco->GetName(),&ZZMass,mrecob);
		cuttree->Branch("weight",&weight,"weight/F");
		cuttree->Branch("weight_up",&weight_up,"weight_up/F");
		cuttree->Branch("weight_dn",&weight_dn,"weight_dn/F");
		//	std::cout<< endl << "PROBLEM" << endl;
		for(int i =0;i<tqqzz->GetEntries();i++){
			tqqzz->GetEntry(i);
			if(channel==channum){
				cuttree->Fill();
			}
		}

		//Remember to revert
		double rho =1;
		if(highmass==0)
			rho=4;
		RooDataSet bkgdata ("bkgdata"+chan+Form("_%d",cate_vbf),"",cuttree,RooArgSet(*mreco,*wt),"weight");
		RooKeysPdf qqzzpdf_1d("bkg_qqzz_1d"+chan+Form("_%d",cate_vbf),"",*mreco,bkgdata,RooKeysPdf::MirrorBoth,rho);

		sprintf(filename,"./template/root_output_files/qqzz_Moriond_%d.root",year);
		TFile *ff = new TFile(filename);
		TH2F *temp_zz=(TH2F*)ff->Get("temp_zz_"+chan);

		for(int bx=0;bx<temp_zz->GetNbinsX();bx++){
			for(int by=0;by<temp_zz->GetNbinsY();by++){
				if(temp_zz->GetBinContent(bx+1,by+1)==0){
					temp_zz->SetBinContent(bx+1,by+1,1.0e-10);
				}
			}
		}
		TH1F *temp_1d=(TH1F*)ff->Get("temp_1d_"+chan);

		for(int bx=0;bx<temp_1d->GetNbinsX();bx++){
		  if(temp_1d->GetBinContent(bx+1)==0){
		    temp_1d->SetBinContent(bx+1,1.0e-6);  
		  }
		}

		RooDataHist* template_sig= new RooDataHist("temp_sig_"+chan+Form("_%d",cate_vbf),"",RooArgSet(*mreco,*dbkg),temp_zz);
		RooHistPdf* pdf_2d_sig = new RooHistPdf("pdf_2d_sig_"+chan+Form("_%d",cate_vbf),"",RooArgSet(*mreco,*dbkg),*template_sig);
		RooProdPdf *qqzzpdf_2d= new RooProdPdf("bkg_qqzz_2d_"+chan+Form("_%d",cate_vbf),"",qqzzpdf_1d,Conditional(*pdf_2d_sig,*dbkg));

                RooDataHist* template_sig_1d= new RooDataHist("temp_1d_"+chan+Form("_%d",cate_vbf),"",*dbkg,temp_1d);
		RooHistPdf* pdf_1d_sig = new RooHistPdf("pdf_1d_sig_"+chan+Form("_%d",cate_vbf),"",*dbkg,*template_sig_1d);

// *********************************************************************************************************************************************************

		TF1 *fsum ;
		int parsize =6;
		double exp;
		fsum=new TF1("fsum"+chan,"landau( 0 )+ landau(3)",160,1500);
		if(cate_vbf==2){
			//fsum=new TF1("fsum"+chan,"landau( 0 )*(1 + exp( pol1(3)))",160,1500);
			parsize=8;
			fsum= new TF1("fsum"+chan, "[0]*TMath::Landau(x, [1], [2]) + [7]*(1 + TMath::Exp([3] - [4]*x))*TMath::Landau(x, [5], [6])",160,1500);
		}

		if(cate_vbf!=2)
			fsum->SetParameters(parzx);
		else
			fsum->SetParameters(parzx_rse);

		if(cate_vbf!=2){
			if(chan=="4e")
				exp=9.8*lumi/12.9;
			else if(chan=="2e2mu")
				exp = 20.4*lumi/12.9;
			else
				exp=10.2*lumi/12.9;
		}
		else{
			if(chan=="4e")
				exp =19; 
			else if(chan=="2e2mu")
				exp= 25; 
		}
		//cout <<fsum->GetExpFormula("p")<<endl;
		TString formuO= fsum->GetExpFormula("p");
		cout<<formuO<<endl;
		formuO.ReplaceAll("x",mreco->GetName());
		cout<<formuO<<endl;

		if(cate_vbf==1){
			yields<< chan<< " "<< cate_vbf<<" ZX "<< 0.0762466*exp*fsum->Integral(low_reco,high_reco)/fsum->Integral(160,1500)<<endl;
			cout<< chan<< " "<< cate_vbf<<" ZX "<< 0.0762466*exp*fsum->Integral(low_reco,high_reco)/fsum->Integral(160,1500)<<endl;
		}
		else if(cate_vbf==0){
			yields<< chan<< " "<< cate_vbf<<" ZX "<< (1-0.0762466)*exp*fsum->Integral(low_reco,high_reco)/fsum->Integral(160,1500)<<endl;
			cout<< chan<< " "<< cate_vbf<<" ZX "<< (1-0.0762466)*exp*fsum->Integral(low_reco,high_reco)/fsum->Integral(160,1500)<<endl;
		}
		else{
			cout<< chan<< " "<< cate_vbf<<" ZX "<< exp*fsum->Integral(300,high_reco)/fsum->Integral(160,1500)<<endl;
			yields<< chan<< " "<< cate_vbf<<" ZX "<< exp*fsum->Integral(300,high_reco)/fsum->Integral(160,1500)<<endl;
		}
		fsum->Draw();
		

		RooArgList* parlist_zx=new RooArgList("parlist_zx");
		const int parsize_const = parsize;
		RooConstVar *pars_zx[parsize_const];

		parlist_zx->add(*mreco);
		for (int pa=0; pa<parsize; pa++){ 
			if(cate_vbf!=2)
			pars_zx[pa]=new RooConstVar(Form("par_zx_w%d_%s_%d",pa,chan.Data(),cate_vbf),"",parzx[pa]);	
			else
			pars_zx[pa]=new RooConstVar(Form("par_zx_w%d_%s_%d",pa,chan.Data(),cate_vbf),"",parzx_rse[pa]);	
			cout << pars_zx[pa]->getVal()<<endl;

			parlist_zx->add(*pars_zx[pa]);
		}

               	std::cout<<endl<<"end problem";
//
		//RooGenericPdf 
		TString form="@1*TMath::Landau(@0,@2,@3)+@4*TMath::Landau(@0,@5,@6)";
		if(cate_vbf==2)
			form= "@1*TMath::Landau(@0, @2, @3) + @8*(1 + TMath::Exp(@4 - @5*@0))*TMath::Landau(@0, @6, @7)"; 
//		RooGenericPdf *zjetpdf = new RooGenericPdf("bkg_zjet","bkg_zjet","@1*TMath::Landau(@0,@2,@3)+@4*TMath::Landau(@0,@5,@6)",*parlist_zx);

		RooGenericPdf * zjetpdf_1d;
		zjetpdf_1d=new RooGenericPdf("bkg_zjet_1d"+chan+Form("_%d",cate_vbf),"bkg_zjet_1d",form,*parlist_zx);

		sprintf(filename,"./template/root_output_files/zx%d.root",year);
		TFile *fzjet = new TFile(filename);
		TH2F *temp_zjet=(TH2F*)fzjet->Get("zx_"+chan);
                TH1F *temp_zjet_1d=(TH1F*)fzjet->Get("zx1d_"+chan);

		for(int bx=0;bx<temp_zjet_1d->GetNbinsX();bx++){
		  if(temp_zjet_1d->GetBinContent(bx+1)==0){
		    temp_zjet_1d->SetBinContent(bx+1,1.0e-6);  
		  }
		}

		RooDataHist* template_zx= new RooDataHist("temp_zx_"+chan+Form("_%d",cate_vbf),"",RooArgSet(*mreco,*dbkg),temp_zjet);
		RooHistPdf* pdf_2d_zx= new RooHistPdf("pdf_2d_zx"+chan+Form("_%d",cate_vbf),"",RooArgSet(*mreco,*dbkg),*template_zx);

		RooProdPdf *zjetpdf_2d= new RooProdPdf("bkg_zjet_2d_"+chan+Form("_%d",cate_vbf),"",*zjetpdf_1d,Conditional(*pdf_2d_zx,*dbkg));

		RooDataHist* template_zx_1d= new RooDataHist("temp_1d_"+chan+Form("_%d",cate_vbf),"",*dbkg,temp_zjet_1d);
		RooHistPdf* pdf_1d_zx= new RooHistPdf("pdf_1d_zx"+chan+Form("_%d",cate_vbf),"",*dbkg,*template_zx_1d);

		//zjetpdf_1d->plotOn(frame);
		//frame->Draw();
		//return;
		//	TCanvas *c2=new TCanvas("c2","",800,600);
		//	fsum->Draw("");
		//
		//	return;
		//data
		TChain *tdata = new TChain("SelectedTree"+treename[cate_vbf]);
                sprintf(filename,"./template/root_output_files/data_%d.root",year);
		tdata->Add(filename);
		TTree* reducetree= tdata->CopyTree(Form("chan==%d&&vbfcate==%d",channum,cate_vbf));
		RooDataSet* data_obs_1d= new RooDataSet("data_obs_1d","data_obs_1d",reducetree,*dbkg);
		RooDataSet* data_obs_2d = new RooDataSet("data_obs_2d","data_obs_2d",reducetree,RooArgSet(*mreco,*dbkg));



		// *********************************************************************************************************************************************************
		//GLUON PART



                RooRealVar* g_mreco= new RooRealVar("mreco","M_{ZZ} (GeV)",180,low_reco,high_reco); //125
                if(cate_vbf==2){
                        g_mreco->SetName("mreco_rse");
                        g_mreco->SetTitle("mreco_rse");
                }

                RooRealVar* g_dbkg= new RooRealVar("dbkg_kin","Dbkg_{kin} ",0.5,0.,1.);
                RooPlot* g_frame= g_mreco->frame(low_reco,high_reco) ;
                if(highmass==2){
                        g_mreco->setBins(nbins_reco);
                        g_dbkg->setBins(30);
                }

                //qqzz pdf
                //TChain *tqqzz= new TChain("ZZTree/candTree");

                // simplify: for ggF, this is qqZZ bkg, for VBF, this should be ggZZ bkg
                // simplify: if no systematics wanted, comment out _up and _dn related stuff
                TChain *g_tqqzz= new TChain("SelectedTree"+treename[cate_vbf]);

                TH1F *g_hqqzz= new TH1F ("hggzz","",nbins_reco,low_reco,high_reco);
                TH1F *g_hqqzz_up= new TH1F ("hggzz_up","",nbins_reco,low_reco,high_reco);
                TH1F *g_hqqzz_dn= new TH1F ("hggzz_dn","",nbins_reco,low_reco,high_reco);

                //tqqzz->Add("root://lxcms03://data3/Higgs/160225/ZZTo4l/ZZ4lAnalysis.root");
                //      if(cate_vbf!=2)
                //
                //
                //
		sprintf(filename,"./template/root_output_files/ggzz_Moriond_%d.root",year);
                g_tqqzz->Add(filename);
                //      else
                //      tqqzz->Add("qqzz_80.root");

                int g_channum=1;
                if(chan=="2e2mu")
                       g_channum=3;
                else if(chan=="4e")
                        g_channum=2;
                else
                        g_channum=1;

                //      tqqzz->Draw("mreco>>hqqzz",Form("weight*(chan==%d&&vbfcate==%d)",channum,cate_vbf));
                //      tqqzz->Draw("mreco>>hqqzz_up",Form("weight_up*(chan==%d&&vbfcate==%d)",channum,cate_vbf));
                //      tqqzz->Draw("mreco>>hqqzz_dn",Form("weight_dn*(chan==%d&&vbfcate==%d)",channum,cate_vbf));


                RooRealVar* g_wt= new RooRealVar("weight","wt",180,0.000,1000.); //125
                RooRealVar* g_wt_up= new RooRealVar("weight_up","wt_up",180,0.000,1000.); //125
                RooRealVar* g_wt_dn= new RooRealVar("weight_dn","wt_dn",180,0.000,1000.); //125


                float g_ZZMass;
                float g_weight, g_weight_up, g_weight_dn;
                int g_channel;
                g_tqqzz->SetBranchAddress("mreco",&g_ZZMass);

                if(cate_vbf==1){
                       g_tqqzz->SetBranchAddress("weight",&g_weight);
                       g_tqqzz->SetBranchAddress("weight_up",&g_weight_up);
                       g_tqqzz->SetBranchAddress("weight_dn",&g_weight_dn);
                        g_tqqzz->Draw("mreco>>hggzz",Form("weight*(chan==%d)",g_channum));
                        g_tqqzz->Draw("mreco>>hggzz_dn",Form("weight_dn*(chan==%d)",g_channum));
                        g_tqqzz->Draw("mreco>>hggzz_up",Form("weight_up*(chan==%d)",g_channum));
                }
                else{
                        g_tqqzz->SetBranchAddress("weight_vbf",&g_weight);
                        g_tqqzz->SetBranchAddress("weight_vbf_up",&g_weight_up);
                        g_tqqzz->SetBranchAddress("weight_vbf_dn",&g_weight_dn);
                        g_tqqzz->Draw("mreco>>hggzz",Form("weight_vbf*(chan==%d)",g_channum));
                        g_tqqzz->Draw("mreco>>hggzz_dn",Form("weight_vbf_dn*(chan==%d)",g_channum));
                        g_tqqzz->Draw("mreco>>hggzz_up",Form("weight_vbf_up*(chan==%d)",g_channum));
                }

                g_tqqzz->SetBranchAddress("chan",&g_channel);

		TFile f1("file1.root","RECREATE"); 		
                TTree *g_cuttree =new TTree("SelectedTree","SelectedTree");
                TString g_mrecob = Form("%s/F",g_mreco->GetName());
                g_cuttree->Branch(g_mreco->GetName(),&g_ZZMass,g_mrecob);
                g_cuttree->Branch("weight",&g_weight,"weight/F");
                g_cuttree->Branch("weight_up",&g_weight_up,"weight_up/F");
                g_cuttree->Branch("weight_dn",&g_weight_dn,"weight_dn/F");
                std::cout << endl << "PROBLEM2" << endl;
                for(int g_i =0;g_i<g_tqqzz->GetEntries();g_i++){
                        g_tqqzz->GetEntry(g_i);
                        if(g_channel==g_channum){
                                g_cuttree->Fill();
                        }
                }

                //Remember to revert
                double g_rho =1;
                if(highmass==0)
                       g_rho=4;
                RooDataSet g_bkgdata ("bkgdata"+chan+Form("_%d",cate_vbf),"",g_cuttree,RooArgSet(*g_mreco,*g_wt),"weight");
                RooKeysPdf g_qqzzpdf_1d("bkg_ggzz_1d"+chan+Form("_%d",cate_vbf),"",*g_mreco,g_bkgdata,RooKeysPdf::MirrorBoth,g_rho);

		sprintf(filename,"./template/root_output_files/ggzz_Moriond_%d.root",year);
                TFile *g_ff = new TFile(filename);
                TH2F *g_temp_zz=(TH2F*)g_ff->Get("temp_zz_"+chan);

                for(int bx=0;bx<g_temp_zz->GetNbinsX();bx++){
                        for(int by=0;by<g_temp_zz->GetNbinsY();by++){
                                if(g_temp_zz->GetBinContent(bx+1,by+1)==0){
                                        g_temp_zz->SetBinContent(bx+1,by+1,1.0e-10);
                                }
                        }
                }

		TH1F *g_temp_1d=(TH1F*)g_ff->Get("temp_1d_"+chan);

		for(int bx=0;bx<g_temp_1d->GetNbinsX();bx++){
		  if(g_temp_1d->GetBinContent(bx+1)==0){
		    g_temp_1d->SetBinContent(bx+1,1.0e-6);  
		  }
		}

                RooDataHist* g_template_sig= new RooDataHist("g_temp_sig_"+chan+Form("_%d",cate_vbf),"",RooArgSet(*g_mreco,*g_dbkg),g_temp_zz);
                RooHistPdf* g_pdf_2d_sig = new RooHistPdf("g_pdf_2d_sig_"+chan+Form("_%d",cate_vbf),"",RooArgSet(*g_mreco,*g_dbkg),*g_template_sig);
                RooProdPdf *g_qqzzpdf_2d= new RooProdPdf("bkg_ggzz_2d_"+chan+Form("_%d",cate_vbf),"",g_qqzzpdf_1d,Conditional(*g_pdf_2d_sig,*g_dbkg));

		RooDataHist* g_template_sig_1d= new RooDataHist("g_temp_sig_1d_"+chan+Form("_%d",cate_vbf),"",*g_dbkg,g_temp_1d);
                RooHistPdf* g_pdf_1d_sig = new RooHistPdf("g_pdf_1d_sig_"+chan+Form("_%d",cate_vbf),"",*g_dbkg,*g_template_sig_1d);

// *********************************************************************************************************************************************************

		
               //VBS PART



                RooRealVar* vbs_mreco= new RooRealVar("mreco","M_{ZZ} (GeV)",180,low_reco,high_reco); //125
                if(cate_vbf==2){
                        vbs_mreco->SetName("mreco_rse");
                        vbs_mreco->SetTitle("mreco_rse");
                }

                RooRealVar* vbs_dbkg= new RooRealVar("dbkg_kin","Dbkg_{kin} ",0.5,0.,1.);
                RooPlot* vbs_frame= vbs_mreco->frame(low_reco,high_reco) ;
                if(highmass==2){
                        vbs_mreco->setBins(nbins_reco);
                        vbs_dbkg->setBins(30);
                }

                //qqzz pdf
                //TChain *tqqzz= new TChain("ZZTree/candTree");

                // simplify: for ggF, this is qqZZ bkg, for VBF, this should be ggZZ bkg
                // simplify: if no systematics wanted, comment out _up and _dn related stuff
                TChain *vbs_tqqzz= new TChain("SelectedTree"+treename[cate_vbf]);

                TH1F *vbs_hqqzz= new TH1F ("hggzz","",nbins_reco,low_reco,high_reco);
                TH1F *vbs_hqqzz_up= new TH1F ("hggzz_up","",nbins_reco,low_reco,high_reco);
                TH1F *vbs_hqqzz_dn= new TH1F ("hggzz_dn","",nbins_reco,low_reco,high_reco);

                //tqqzz->Add("root://lxcms03://data3/Higgs/160225/ZZTo4l/ZZ4lAnalysis.root");
                //      if(cate_vbf!=2)
                //
                //
                //
                sprintf(filename,"./template/root_output_files/vbs_Moriond_%d.root",year);
                vbs_tqqzz->Add(filename);
                //      else
                //      tqqzz->Add("qqzz_80.root");

                int vbs_channum=1;
                if(chan=="2e2mu")
                       vbs_channum=3;
                else if(chan=="4e")
                        vbs_channum=2;
                else
                        vbs_channum=1;

                //      tqqzz->Draw("mreco>>hqqzz",Form("weight*(chan==%d&&vbfcate==%d)",channum,cate_vbf));
                //      tqqzz->Draw("mreco>>hqqzz_up",Form("weight_up*(chan==%d&&vbfcate==%d)",channum,cate_vbf));
                //      tqqzz->Draw("mreco>>hqqzz_dn",Form("weight_dn*(chan==%d&&vbfcate==%d)",channum,cate_vbf));


                RooRealVar* vbs_wt= new RooRealVar("weight","wt",180,0.000,1000.);//125
                RooRealVar* vbs_wt_up= new RooRealVar("weight_up","wt_up",180,0.000,1000.);//125
                RooRealVar* vbs_wt_dn= new RooRealVar("weight_dn","wt_dn",180,0.000,1000.);//125


                float vbs_ZZMass;
                float vbs_weight, vbs_weight_up, vbs_weight_dn;
                int vbs_channel;
                vbs_tqqzz->SetBranchAddress("mreco",&vbs_ZZMass);

                if(cate_vbf==1){
                       vbs_tqqzz->SetBranchAddress("weight",&vbs_weight);
                       vbs_tqqzz->SetBranchAddress("weight_up",&vbs_weight_up);
                       vbs_tqqzz->SetBranchAddress("weight_dn",&vbs_weight_dn);
                        vbs_tqqzz->Draw("mreco>>hggzz",Form("weight*(chan==%d)",vbs_channum));
                        vbs_tqqzz->Draw("mreco>>hggzz_dn",Form("weight_dn*(chan==%d)",vbs_channum));
                        vbs_tqqzz->Draw("mreco>>hggzz_up",Form("weight_up*(chan==%d)",vbs_channum));
                }
                else{
                        vbs_tqqzz->SetBranchAddress("weight_vbf",&vbs_weight);
                        vbs_tqqzz->SetBranchAddress("weight_vbf_up",&vbs_weight_up);
                        vbs_tqqzz->SetBranchAddress("weight_vbf_dn",&vbs_weight_dn);
                        vbs_tqqzz->Draw("mreco>>hggzz",Form("weight_vbf*(chan==%d)",vbs_channum));
                        vbs_tqqzz->Draw("mreco>>hggzz_dn",Form("weight_vbf_dn*(chan==%d)",vbs_channum));
                        vbs_tqqzz->Draw("mreco>>hggzz_up",Form("weight_vbf_up*(chan==%d)",vbs_channum));
                }

                vbs_tqqzz->SetBranchAddress("chan",&vbs_channel);

                TFile f2("file1.root","RECREATE");
                TTree *vbs_cuttree =new TTree("SelectedTree","SelectedTree");
                TString vbs_mrecob = Form("%s/F",vbs_mreco->GetName());
                vbs_cuttree->Branch(vbs_mreco->GetName(),&vbs_ZZMass,vbs_mrecob);
                vbs_cuttree->Branch("weight",&vbs_weight,"weight/F");
                vbs_cuttree->Branch("weight_up",&vbs_weight_up,"weight_up/F");
                vbs_cuttree->Branch("weight_dn",&vbs_weight_dn,"weight_dn/F");
                std::cout << endl << "PROBLEM2" << endl;
                for(int vbs_i =0;vbs_i<vbs_tqqzz->GetEntries();vbs_i++){
                        vbs_tqqzz->GetEntry(vbs_i);
                        if(vbs_channel==vbs_channum){
                                vbs_cuttree->Fill();
                        }
                }
		

                //Remember to revert
                double vbs_rho =1;
                if(highmass==0)
                       vbs_rho=4;
                RooDataSet vbs_bkgdata ("bkgdata"+chan+Form("_%d",cate_vbf),"",vbs_cuttree,RooArgSet(*vbs_mreco,*vbs_wt),"weight");
                RooKeysPdf vbs_qqzzpdf_1d("bkg_vbs_1d"+chan+Form("_%d",cate_vbf),"",*vbs_mreco,vbs_bkgdata,RooKeysPdf::MirrorBoth,vbs_rho);

		sprintf(filename,"./template/root_output_files/vbs_Moriond_%d.root",year);
		
                TFile *vbs_ff = new TFile(filename);
                TH2F *vbs_temp_zz=(TH2F*)vbs_ff->Get("temp_zz_"+chan);

                for(int bx=0;bx<vbs_temp_zz->GetNbinsX();bx++){
                        for(int by=0;by<vbs_temp_zz->GetNbinsY();by++){
                                if(vbs_temp_zz->GetBinContent(bx+1,by+1)==0){
                                        vbs_temp_zz->SetBinContent(bx+1,by+1,1.0e-10);
                                }
                        }
                }
		
		TH1F *vbs_temp_1d=(TH1F*)vbs_ff->Get("temp_1d_"+chan);

		for(int bx=0;bx<vbs_temp_1d->GetNbinsX();bx++){
		  if(vbs_temp_1d->GetBinContent(bx+1)==0){
		    vbs_temp_1d->SetBinContent(bx+1,1.0e-6);  
		  }
		}


                 if (channum == 3) {
                        vbs_temp_zz->Draw("colz");
                        gPad->Print("template_check.png");
                 }



                RooDataHist* vbs_template_sig= new RooDataHist("vbs_temp_sig_"+chan+Form("_%d",cate_vbf),"",RooArgSet(*vbs_mreco,*vbs_dbkg),vbs_temp_zz);
                RooHistPdf* vbs_pdf_2d_sig = new RooHistPdf("vbs_pdf_2d_sig_"+chan+Form("_%d",cate_vbf),"",RooArgSet(*vbs_mreco,*vbs_dbkg),*vbs_template_sig);
                RooProdPdf *vbs_qqzzpdf_2d= new RooProdPdf("bkg_vbs_2d_"+chan+Form("_%d",cate_vbf),"",vbs_qqzzpdf_1d,Conditional(*vbs_pdf_2d_sig,*vbs_dbkg));


		RooDataHist* vbs_template_sig_1d= new RooDataHist("vbs_temp_sig_1d_"+chan+Form("_%d",cate_vbf),"",*vbs_dbkg,vbs_temp_1d);
                RooHistPdf* vbs_pdf_1d_sig = new RooHistPdf("vbs_pdf_1d_sig_"+chan+Form("_%d",cate_vbf),"",*vbs_dbkg,*vbs_template_sig_1d);

// *********************************************************************************************************************************************************




// * Remember to revert
		if(isDbkg){
			data_obs_1d->SetNameTitle("data_obs","data_obs");
			pdf_1d_sig->SetNameTitle("bkg_qqzz","bkg_qqzz");
			g_pdf_1d_sig->SetNameTitle("bkg_ggzz","bkg_ggzz");
			pdf_1d_zx->SetNameTitle("bkg_zjet","bkg_zjet");
			vbs_pdf_1d_sig->SetNameTitle("bkg_vbs","bkg_vbs");
			
			w.import(*pdf_1d_sig);
			w.import(*g_pdf_1d_sig);
			w.import(*vbs_pdf_1d_sig);
			w.import(*pdf_1d_zx);
			w.import(*data_obs_1d);
		}
		else{
			data_obs_1d->SetNameTitle("data_obs","data_obs");
			qqzzpdf_1d.SetNameTitle("bkg_qqzz","bkg_qqzz");
			g_qqzzpdf_1d.SetNameTitle("bkg_ggzz","bkg_ggzz");
			vbs_qqzzpdf_1d.SetNameTitle("bkg_vbs","bkg_vbs");
			zjetpdf_1d->SetNameTitle("bkg_zjet","bkg_zjet");
			
			w.import(qqzzpdf_1d);
			w.import(g_qqzzpdf_1d);
			w.import(vbs_qqzzpdf_1d);
			w.import(*zjetpdf_1d);
			w.import(*data_obs_1d);
		}
		//		cout<<data_obs->sumEntries()<<endl;

		//	}

		//	qqzzpdf_2d.setNameTitle("bkg_qqzz","bkg_qqzz");
		//	w.import(qqzzpdf,RecycleConflictNodes());
		//	w.import(*qqzzpdf_2d,RecycleConflictNodes());
		//simplif no systematics, comment out begin
		//	w.import(qqzzpdf_up,RecycleConflictNodes());
		//	w.import(qqzzpdf_dn,RecycleConflictNodes());
		//	w.import(*int_qq,RecycleConflictNodes());
		//w.import(*zjetpdf,RecycleConflictNodes());
		TFile *fwork ;
		if(highmass==0)
		  fwork= new TFile("workspace/1D_vbs4l_"+chan+Form("%dS_%d_13TeV.input_func.root",cate_vbf,year),"recreate");
		if(highmass==1)
		  fwork= new TFile("workspace/1D_vbs4l_"+chan+Form("%dS_%d_13TeV.input_func.root",cate_vbf,year),"recreate");
		if(highmass==2){
		  if(isDbkg)
		    fwork= new TFile("workspace/1D_vbs4l_"+chan+Form("%dS_%d_13TeV.input_func.root",cate_vbf,year),"recreate");
		  else
		    fwork= new TFile("workspace/1D_vbs4l_"+chan+Form("%dS_%d_13TeV.input_func.root",cate_vbf,year),"recreate");
		}
		fwork->cd();
		w.Write();
		fwork->Close();
}

void bkgWorkspace1d(TString chan, int vbfcate, int highmass, int isDbkg,int year){
  dosomething(chan,vbfcate,highmass,isDbkg,year);
}
