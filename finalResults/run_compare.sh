root -l -b -q 'compare_15001_RAA_pt.C+(1)' #1S
root -l -b -q 'compare_15001_RAA_pt.C+(2)' #2S
root -l -b -q 'compare_15001_RAA_rap.C+(1)'
root -l -b -q 'compare_15001_RAA_rap.C+(2)'
root -l -b -q 'compare_15001_RAA_cent.C+(1)'
root -l -b -q 'compare_15001_RAA_cent.C+(2)'
root -l -b -q 'compare_15001_RAA_cent_newglobal.C+(1)'
root -l -b -q 'compare_15001_RAA_cent_newglobal.C+(2)'
#root -l -b -q 'compare_15001_RAA_cent_noint.C+(1)'
#root -l -b -q 'compare_15001_RAA_cent_noint.C+(2)'

rm -f *.so *.d *.pcm
