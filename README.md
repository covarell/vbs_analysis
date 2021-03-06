The repository contains the principal files used in the analysis.

<b> 4l channel, ZX data driven MC </b>

For this part the following CMSSW version was used: CMSSW_8_0_26_patch1

The folder data_driven_MC must be included in the src directory. The discriminant is defined in src/run_makeZX.cpp 
and all changes must be done in this file.

The following instructions are necessary to run:

cd ext

sh compile_ext.sh

cd ..

source set_library.sh

make run_makeZX

./run_makeZX &lt;year&gt; &lt;enrichment&gt;

The enrichment variable refers to the selection: 0 = baseline, 1 = VBS-enriched (loose), 2 = VBS-enriched (tight with DeltaEta), 3 = background enriched, 4 = tighter pTjet cut (50 GeV), 5 = VBS-enriched (tight with mjj). 

The necessary variables (ZZMass, dbkg_kin, weight etc.) will be stored in the file ZX(+suffix).root

<b> Main analysis </b>

plotterAndTemplateMaker.c -> The file reads 4l MC + data (from relevant repositories), together with the data driven zx component, contained in the ZX(+suffix).root file. It performs relevant selection, mela cuts, kin_variable generation. The output is:
- 1D pictures portraying all contributions (&lt;directory&gt;/&lt;variable&gt;-allaMCatNLO-&lt;year&gt;.png)
- 1D templates, selected trees and their pictures (in template/root_output_files/ divided by MC/data contributions) 
- event yields for MC and data (MC/datayields_&lt;year&gt;.txt, to be copied in the combine cards) 

Run with: plotterAndTemplateMaker(&lt;year&gt;,1,&lt;enrichment&gt;)  <- check above for the several enrichment options

The drawSummedHistos.c macro can be used to plot summed histos for the 3 years.

plotterSystXXX.c -> Evaluates normalization systematics (by a constant fit to up and down variations of systematic
effect XXX and if needed, stores alternative templates in template/root_output_files/.

Run with: plotterSystXXX(&lt;year&gt;,&lt;MC sample&gt;) .
MC sample: 0 = qqZZ, 1 = ggZZ, 2 = EWK ZZ, 4 = ttbarZ+WWZ

bkg_Workspace1d.c -> Generation of workspaces for signal and background (devided by component: vbs, qqZZ etc..). 
The templates are created and named to follow combine and saved accordingly in workspace/&lt;workspace_name_channel&gt;.root.

The code is run with:

source runbkg.sh (in bash)

<b> Combine </b>

All cards can be found in the COMBINATION_FOLDER, with sub-directory 4l. Use CMSSW 10_2_13 for this part.

To combine multiple cards: 

combineCards.py Name1=old_card1.txt Name2=old_card2.txt .... > new_card.txt

To run the likelihood analysis (expected, without systematics): 

- combine -M Significance card_name.txt -t -1 --expectSignal=1 --freezeParameters=allConstrainedNuisances
- combine -M MultiDimFit card_name.txt --cl=0.68 --algo singles -t -1 --expectSignal=1 --freezeParameters=allConstrainedNuisances (may add --robustFit 1)

To run the likelihood analysis (expected, with systematics): 

- combine -M Significance card_name.txt -t -1 --expectSignal=1
- combine -M MultiDimFit card_name.txt --cl=0.68 --algo singles -t -1 --expectSignal=1 (may add --robustFit 1)

To run the likelihood analysis (observed significance): 

- combine -M Significance card_name.txt 
- combine -M MultiDimFit card_name.txt --cl=0.68 --algo singles (may add --robustFit 1)

To run the likelihood analysis (observed, with theory systematics removed to obtain cross-section rather than mu): 

- combine -M MultiDimFit card_name.txt --cl=0.68 --algo singles --freezeNuisanceGroups=^theory (may add --robustFit 1)

To run fits for signal strength and impacts follow instructions in the combine gitbook to install the new scripts
combineTool.py and plotImpacts.py

https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/#combine-tool

For full fits of mu and nuisance parameters follow:

https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/part3/nonstandard/#nuisance-parameter-impacts

(adding -t -1 and --expectSignal=1 for the expected values)

<b> Note by Connor </b>

These are the single files, and the most complete version I was able to find. However I've included .tar compressed file of the complete directories here: https://www.dropbox.com/sh/mahvupqcauchx53/AAAhKMKCSfl-Bhsw1uwJo5HQa?dl=0 (quite messy, but containing a long list of different file versions, data cards, plots and so on). It may be useful in case there is some file not included in the above list, but which is used somewhere in the code.

The Meng.txt contains the instructions that Meng gave me at our CERN meeting last Spring. 
