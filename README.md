B# vbs_analysis
The repository contains the principal files used in the analysis.

<b> 4l channel, ZX data driven MC </b>

For this part the following CMSSW version was used: CMSSW_8_0_26_patch1

The folder data_driven_MC must be included in the src directory. The discriminant is defined in src/run_makeZX.cpp 
and all changes must be done in this file.

The following instructions are necessary to run:

cd ext/

sh compile_ext.sh

cd ..

source set_library.sh

make run_makeZX

./run_makeZX

The necessary variables (ZZMass, dbkg_kin, weight etc.) will be stored in ZX(+suffix).root

<b> Main analysis </b>

plotterAndTemplateMaker.c -> The file reads 4l MC + data (from relevant repositories), together with the data driven zx component, contained in the ZX(+suffix).root file. It performs relevant selection, mela cuts, kin_variable generation. The output is:
- 1D pictures portraying all contributions (&lt;directory&gt;/&lt;variable&gt;_allaMCatNLO_&lt;year&gt;.png)
- 1D templates, selected trees and their pictures (in template/root_output_files/ divided by MC/data contributions) 
- yields for MC and data (MC/datayields_&lt;year&gt;.txt, to be copied in the combine cards) 

Run with: plotterAndTemplateMaker(&lt;year&gt;,1,&lt;ifVBSenriched&gt;)  <- last option not available yet

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

To run fits for signal strength and impacts follow instructions in the combine gitbook to install the new scripts
combineTool.py and plotImpacts.py

https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/#combine-tool

For full fits of mu and nuisance parameters follow:

https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/part3/nonstandard/#nuisance-parameter-impacts

(adding -t -1 and --expectSignal=1 for the expected values)

<b> Note by Connor </b>

These are the single files, and the most complete version I was able to find. However I've included .tar compressed file of the complete directories here: https://www.dropbox.com/sh/mahvupqcauchx53/AAAhKMKCSfl-Bhsw1uwJo5HQa?dl=0 (quite messy, but containing a long list of different file versions, data cards, plots and so on). It may be useful in case there is some file not included in the above list, but which is used somewhere in the code.

The Meng.txt contains the instructions that Meng gave me at our CERN meeting last Spring. 
