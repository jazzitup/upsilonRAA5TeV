#void getEfficiencyUpsilon(int state = 1, bool useDataWeight=true, bool useTnpWeigt=false) {  // 1S, 2S, 3S

root -l -b -q 'getEfficiencyUpsilon.C+(1,0,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(2,0,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(3,0,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(1,1,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(2,1,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(3,1,0)'
