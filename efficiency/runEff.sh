#void getEfficiencyUpsilon(int state = 1, bool useDataWeight=true, bool useTnpWeigt=false, int tnpIdx=0) { 
# - Trigger:
#   * idx = 0:  nominal
#   * idx = 1..100: toy variations, stat. only
#   * idx = -1: syst variation, "new_MAX", +1 sigma
#   * idx = -2: syst variation, "new_MAX", -1 sigma
#   * idx = -10: binned
# - MuID, STA:
#   * only one SF (for systematic uncertainty only)

root -l -b -q 'getEfficiencyUpsilon.C+(1,0,0,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(2,0,0,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(3,0,0,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(1,1,0,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(2,1,0,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(3,1,0,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(1,1,1,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(2,1,1,0)'
root -l -b -q 'getEfficiencyUpsilon.C+(3,1,1,0)'




