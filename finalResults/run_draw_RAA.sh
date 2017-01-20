root -l -b -q 'draw_RAA_pt_isArrow.C+(1)'
root -l -b -q 'draw_RAA_rap_isArrow.C+(1)'
root -l -b -q 'draw_RAA_cent.C+(1)' # upper limit for 3S (actual)
#root -l -b -q 'draw_RAA_cent.C+(0)' # just point for 3S
#root -l -b -q draw_RAA_cent_noint.C+

rm -f *.so *.d *.pcm
