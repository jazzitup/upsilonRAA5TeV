#void getEfficiencyUpsilon(int state = 1, bool useDataWeight=true, bool useTnpWeight=false, int tnpIdx=0) {  // 1\
#// - Trigger:
#//   * idx = 0:  nominal
#//   * idx = 1..100: toy variations, stat. only
#//   * idx = -1: syst variation, "new_MAX", +1 sigma
#//   * idx = -2: syst variation, "new_MAX", -1 sigma
#//   * idx = -10: binned
#// - MuID, STA:
#//   * only one SF (for systematic uncertainty only)
#double tnp_w
#       idx = 200,   MuID,  
#       idx = 300,   STA


root -l -b <<EOF
.L getEfficiencyUpsilon.C++
.q
EOF

for state in 1 2 3 
do
    root -l -b -q 'getEfficiencyUpsilon.C('$state',1,1,-1)'
    root -l -b -q 'getEfficiencyUpsilon.C('$state',1,1,-2)'
    root -l -b -q 'getEfficiencyUpsilon.C('$state',1,1,-10)'
    root -l -b -q 'getEfficiencyUpsilon.C('$state',1,1,200)'
    root -l -b -q 'getEfficiencyUpsilon.C('$state',1,1,300)'
    for (( i=1 ; i<=100 ; i++ ))
    do
	root -l -b -q 'getEfficiencyUpsilon.C('$state',1,1,'$i')'
    done
done
