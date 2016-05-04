# decayTTbarLHE
Code to decay the products of one LHE file by adding in events from a second and third and boosting them.


Must be contained within a CMSSW/src folder (I used 7_6_5)!

    cmsrel CMSSW_7_6_5
    cd CMSSW_7_6_5/src/
    cmsenv
    git clone https://github.com/rymuelle/decayTTbarLHE.git
    cd decayTTbarLHE


Compile with:

    c++ -o decayTTbarLHE `root-config --glibs --cflags` -lm decayTTbarLHE.cpp

Then run with:

    ./decayTTbarLHE t1t1bar_unweighted_events.lhe t1decay_unweighted_events.lhe t1barDecay_unweighted_events.lhe

It should produce an out.lhe file as in this repo. Order of input lhe files matters!

Things I am unsure of:

first line of event block. NUP is updated but not other weights or params. Clustering needs to be added. PDF info needs to be added.
