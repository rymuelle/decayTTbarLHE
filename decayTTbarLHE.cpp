// c++ -o decayTTbarLHE `root-config --glibs --cflags` -lm decayTTbarLHE.cpp
#include "LHEF.h"
#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"

using namespace std ;


int main(int argc, char ** argv) 
{

  int maxEvents = 10;
  std::ifstream ifs (argv[1]) ;
  std::ifstream ifs2 (argv[2]) ;
  std::ifstream ifs3 (argv[3]) ;
  LHEF::Reader reader (ifs) ;
  LHEF::Reader reader2 (ifs2) ;
  LHEF::Reader reader3 (ifs3) ;

//  ofstream outputStream (argv[2]) ;
  ofstream outputStream ("out.lhe") ;
  LHEF::Writer writer (outputStream) ;

  writer.headerBlock() << reader.headerBlock ;
  writer.initComments() << reader.initComments ;
  writer.heprup = reader.heprup ;
  writer.init () ;



  TVector3 boost_vector;
  int stop_counter = 0;
  int i = 0;

  while (reader.readEvent ()) 
    {
        i = i +1;
      if ( reader.outsideBlock.length ()) std::cout << reader.outsideBlock;
      // loop over particles in the event

      for (int iPart = 0 ; iPart < reader.hepeup.IDUP.size (); ++iPart) 
        {
            //std::cout << "clustering: " << reader.hepeup.clustering[iPart].p1 << " " << reader.hepeup.clustering[iPart].p2 << " " << reader.hepeup.clustering[iPart].p0 << " " << reader.hepeup.clustering[iPart].scale << " " << reader.hepeup.clustering[iPart].alphas <<  std::endl;
           TLorentzVector boost (
                reader.hepeup.PUP.at (iPart).at (0), // px
                reader.hepeup.PUP.at (iPart).at (1), // py
                reader.hepeup.PUP.at (iPart).at (2), // pz
                reader.hepeup.PUP.at (iPart).at (3) // E
              ) ; 

            if(reader.hepeup.IDUP.at (iPart) == 1000006 and reader.hepeup.ISTUP.at (iPart) == 1) 
            {
                reader.hepeup.ISTUP.at (iPart) = 2;

                if(reader2.readEvent())
                {
                       reader.hepeup.addHEPUP(reader2.hepeup, boost.BoostVector(), iPart);
                        std::cout << iPart << std::endl;
                }

            }

            if(reader.hepeup.IDUP.at (iPart) == -1000006)
            {
                reader.hepeup.ISTUP.at (iPart) = 2;
                if(reader2.readEvent())
                {
                       reader.hepeup.addHEPUP(reader2.hepeup, boost.BoostVector(), iPart);
                        std::cout << iPart << std::endl;
                }
            }
            


            //std::cout << reader.hepeup.IDUP.size() << std::endl;            
        }
    writer.eventComments() << reader.eventComments;
    writer.hepeup = reader.hepeup;
    writer.writeEvent();
    }


return 0;
}

