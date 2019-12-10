//#include "HiggsAnalysis/CombinedLimit/src/VerticalInterpHistPdf.cc+"
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

void dosomething(TString chan="2e2mu", int year=2016){

        char filename[300];

        static const int samples = 5;
        string namesamp[samples] = {"vbs","zjet","qqzz","ggzz","ttzwzz"}; 
	static const int systs = 4;   //4
        string namesyst[systs] = {"scale","PDF","JES","JER"};	
	bool hasShape[samples][systs] = {{true,false,true,false},
					 {false,false,false,false},
					 {false,false,true,false},
					 {false,false,true,false},
					 {false,false,false,false}};
	string newnamesyst[systs] = {"ShapeQCDscale","ShapePDF","ShapeJES","ShapeJER"};
	float normalizations[samples][3];

	TH1F *temp_1d[samples];
	TH1F *temp_1d_jup[samples][systs];
	TH1F *temp_1d_jdown[samples][systs];

	int channum=1;
	if(chan=="2e2mu")
	  channum=3;
	else if(chan=="4e")
	  channum=2;
	else if(chan=="4mu")
	  channum=1;

	for (int is = 0; is < samples; is++) {

	  if (is==1) continue;    // zx later!
	  sprintf(filename,"./template/root_output_files/%s_Moriond_%d.root",namesamp[is].c_str(),year);
	  TFile *ff = new TFile(filename);
	  temp_1d[is]=(TH1F*)ff->Get("temp_1d_"+chan);
	  
	  for(int bx=0;bx<temp_1d[is]->GetNbinsX();bx++){
	    if(temp_1d[is]->GetBinContent(bx+1)<=0.){
	      temp_1d[is]->SetBinContent(bx+1,1.0e-6);  
	    }
	  }
	
	  sprintf(filename,"bkg_%s",namesamp[is].c_str());
	  temp_1d[is]->SetNameTitle(filename,filename);

	  for (int isy = 0; isy < systs; isy++) {

	    if (hasShape[is][isy]) {
	      // Insert here shape variations
	      sprintf(filename,"./template/root_output_files/%s_Moriond_%s_%d.root",namesamp[is].c_str(),namesyst[isy].c_str(),year);

	      TFile *ffj = new TFile(filename);
	      temp_1d_jup[is][isy]=(TH1F*)ffj->Get("temp_1d_"+chan+"_0");
	
	      for(int bx=0;bx<temp_1d_jup[is][isy]->GetNbinsX();bx++){
		if(temp_1d_jup[is][isy]->GetBinContent(bx+1)<=0.){
		  temp_1d_jup[is][isy]->SetBinContent(bx+1,1.0e-6);  
		}
		if(temp_1d_jup[is][isy]->GetBinContent(bx+1)-temp_1d[is]->GetBinContent(bx+1) < 0.000001){
		  temp_1d_jup[is][isy]->SetBinContent(bx+1,temp_1d_jup[is][isy]->GetBinContent(bx+1)+0.00001);  
		}
	      }
	      sprintf(filename,"bkg_%s_%sUp",namesamp[is].c_str(),newnamesyst[isy].c_str());
	      temp_1d_jup[is][isy]->SetNameTitle(filename,filename);
	      
	      temp_1d_jdown[is][isy]=(TH1F*)ffj->Get("temp_1d_"+chan+"_1");
	      
	      for(int bx=0;bx<temp_1d_jdown[is][isy]->GetNbinsX();bx++){
		if(temp_1d_jdown[is][isy]->GetBinContent(bx+1)<=0.){
		  temp_1d_jdown[is][isy]->SetBinContent(bx+1,1.0e-6);  
		}
		if(temp_1d[is]->GetBinContent(bx+1)-temp_1d_jdown[is][isy]->GetBinContent(bx+1) < 0.000001){
		  temp_1d_jdown[is][isy]->SetBinContent(bx+1,temp_1d_jdown[is][isy]->GetBinContent(bx+1)+0.00001);  
		}
	      }
	      
	      sprintf(filename,"bkg_%s_%sDown",namesamp[is].c_str(),newnamesyst[isy].c_str());
	      temp_1d_jdown[is][isy]->SetNameTitle(filename,filename);
	    }
	  }
	}
	// normalize histos, otherwise combine complains...
	sprintf(filename,"MCyields_%d.txt",year);
        ifstream parInput(filename);

	if (parInput.is_open()) {
	  while ( parInput.good() ) {
	    parInput >> normalizations[0][0] >> normalizations[1][0] >> normalizations[2][0] >> normalizations[3][0] >> normalizations[4][0] >>
	      normalizations[0][1] >> normalizations[1][1] >> normalizations[2][1] >> normalizations[3][1] >> normalizations[4][1] >>
	      normalizations[0][2] >> normalizations[1][2] >> normalizations[2][2] >> normalizations[3][2] >> normalizations[4][2];   
	  }
	  parInput.close();
	}

	//zx
	TChain *t=new TChain("candTree");
	//t->Add("/afs/cern.ch/work/c/cthorbur/VBF_ANALYSIS/CMSSW_8_0_24_patch1/src/HZZ4l-plotter/ZXinput_mjj.root");
        sprintf(filename,"/afs/cern.ch/work/c/covarell/vbs2017/CMSSW_8_0_26_patch1/src/data_driven_MC/ZX%d_noCut.root", year);
	t->Add(filename);
	TH1F* zx1d = new TH1F("zx1d","",50,0.,1.);
	t->Draw("dbkg_kin>>zx1d","(dbkg_kin > 0.)*weight");   // use the same for 3 final states (not enough stats)
	zx1d->SetNameTitle("bkg_zjet","bkg_zjet");

	//data
	TChain *tdata = new TChain("SelectedTree");
	sprintf(filename,"./template/root_output_files/data_%d.root",year);
	tdata->Add(filename);
	TH1F* data_1d = new TH1F("data_1d","",50,0.,1.);
	sprintf(filename,"chan==%d && vbfcate==1",channum);
	tdata->Draw("dbkg_kin>>data_1d",filename);	
	data_1d->SetNameTitle("data_obs","data_obs");

	TFile *fwork ;
	float theScale = 0;
	fwork= new TFile("workspace/1D_vbs4lSyst_"+chan+Form("1S_%d.input_func.root",year),"recreate");
	fwork->cd();
	for (int is = 0; is < samples; is++) {
	  if (is==1) continue;    // zx later!
	  theScale = normalizations[is][channum-1]/temp_1d[is]->Integral();
	  temp_1d[is]->Scale(theScale);
	  temp_1d[is]->Write();
	  for (int isy = 0; isy < systs; isy++) {
	    if (hasShape[is][isy]) {
	      theScale = normalizations[is][channum-1]/temp_1d_jup[is][isy]->Integral();
	      temp_1d_jup[is][isy]->Scale(theScale);
	      temp_1d_jup[is][isy]->Write();
	      theScale = normalizations[is][channum-1]/temp_1d_jdown[is][isy]->Integral();
	      temp_1d_jdown[is][isy]->Scale(theScale);
	      temp_1d_jdown[is][isy]->Write();
	    }
	  }
	}
	theScale = normalizations[1][channum-1]/zx1d->Integral();
	zx1d->Scale(theScale);  
	zx1d->Write();
	data_1d->Write();
	fwork->Close();
}

void bkgWorkspace1d(TString chan, int year){
  dosomething(chan,year);
}
