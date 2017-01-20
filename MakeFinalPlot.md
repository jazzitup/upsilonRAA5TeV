To make the final plots!

Before begin, make sure you have 6 root files

finalResults/Ups_1_RAA.root
finalResults/Ups_2_RAA.root
finalResults/Ups_3_RAA.root
Systematic/mergedSys_ups1s.root
Systematic/mergedSys_ups2s.root
Systematic/mergedSys_ups3s.root

and header files
finalResults/SONGKYO.h
finalResults/CMS_lumi.h
finalResults/CMS_lumi.C
finalResults/tdrstyle.C

Now drawing the final plots!

1. cd finalResults/
2. ./run_draw_RAA.sh   :  RAA Plots
3. ./run_draw_CrossSection.sh   : CrossSection Plots
4. ./run_compare.sh   :  RAA comparison plots with 2.76 TeV
5. ./run_strickland.sh  :  RAA theory curve comparison plots


Making the systematic table
1. cd Systematic/   
2. ./runMerge.sh

