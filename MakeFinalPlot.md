To make the final plots!


1. Before begin, make sure you have 6 root files (in point of home directory)

finalResults/Ups_1_RAA.root
finalResults/Ups_2_RAA.root
finalResults/Ups_3_RAA.root
Systematic/mergedSys_ups1s.root
Systematic/mergedSys_ups2s.root
Systematic/mergedSys_ups3s.root

and header files
./CMS_lumi.C
./CMS_lumi.h
./tdrstyle.C
./SONGKYO.h
finalResults/SONGKYO.h
finalResults/CMS_lumi.h
finalResults/CMS_lumi.C
finalResults/CMS_lumi_raaCent.h
finalResults/CMS_lumi_raaCent.C
finalResults/CMS_lumi_overlay.h
finalResults/CMS_lumi_overlay.C
finalResults/tdrstyle.C

2. Go to finalResults

3. Now drawing the final plots!

  a. ./run_draw_RAA.sh   :  RAA Plots
  b. ./run_draw_CrossSection.sh   : CrossSection Plots
  c. ./run_compare.sh   :  RAA comparison plots with 2.76 TeV
  d. ./run_strickland.sh  :  RAA theory curve comparison plots
  d. ./run_massPlot.sh  :  Mass Plot & overlay Plot (will take some time & you need the skimmed files)


Making the systematic table
1. cd Systematic/   
2. ./runMerge.sh

