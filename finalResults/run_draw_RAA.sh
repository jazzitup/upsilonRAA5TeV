root -l -b -q draw_RAA_pt.C+
root -l -b -q draw_RAA_rap.C+
root -l -b -q 'draw_RAA_cent.C+(1)' # upper limit for 3S (actual)
#root -l -b -q 'draw_RAA_cent.C+(0)' # just point for 3S
#root -l -b -q draw_RAA_cent_noint.C+

rm -f *.so *.d *.pcm
