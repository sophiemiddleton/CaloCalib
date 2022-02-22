#include <fstream>
#include <iostream>
#include <algorithm>
#include "TSystem.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TMath.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TMath.h"
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <time.h>
using namespace RooFit;
TString filepath = "/Users/user/ski_examples/CaloCalib/10M.root";
using namespace std;
using namespace TMath;

//================== Select the sample =========================//
TTree* get_data_tree(){
    TFile *f =  new TFile(filepath);
    TTree *t = (TTree*)f->Get("CaloExample/Calo");
    return t;
}

int main(){

  TTree *ergTree = get_data_tree();

  // set the variable names extracted from the input file.
  float cryEdep[100], cryEtot[100], cryPosX[100], cryPosY[100], cryPosZ[100], cryTime[100];
  int nCry; // nSim;
  int cryId[100];
  float trueEtot[100];

  ergTree->SetBranchAddress("nCry", &nCry);
  ergTree->SetBranchAddress("cryId", cryId);
  ergTree->SetBranchAddress("cryEdep", cryEdep);
  ergTree->SetBranchAddress("cryEtot", cryEtot);
  ergTree->SetBranchAddress("cryTime", cryTime);
  ergTree->SetBranchAddress("cryPosX", &cryPosX);
  ergTree->SetBranchAddress("cryPosY", &cryPosY);
  ergTree->SetBranchAddress("cryPosZ", &cryPosZ);
  ergTree->SetBranchAddress("trueEtot", trueEtot);

 // event list per crystal so length is [1348][nEvents]
 std::vector<int> cryList;
 std::vector<std::vector<double> > cryEnergy;
 std::vector<std::vector<double> > cryTimes;
 std::vector<std::vector<double> > cryRatio;
   // fill crystal lists:
  for(int i = 0; i< 1348; i++){
    std::vector<double> cry;
    cryEnergy.push_back(cry);
    cryTimes.push_back(cry);
    cryList.push_back(i);
    cryRatio.push_back(cry);
  }

  // loop over all events
  for (unsigned int i = 0, N = ergTree->GetEntries(); i < N; ++i) {
    ergTree->GetEntry(i);
    //if(cryEtot[0] !=0)
    cryEnergy[cryId[0]].push_back(cryEtot[0]);
    cryTimes[cryId[0]].push_back(cryTime[0]);

  }

  // loop over all crystals
  for(unsigned int i = 674; i< 684; i++){
    TString CryNum = to_string(i);

    // define file and tree:
    TFile *f = new TFile(CryNum+".root","RECREATE");
    TTree *newTree = new TTree("newTree","newTree");
    Float_t EReco, cryDeltaT, ratio;

    // branches (per event quantities):
    newTree->Branch("EnergyTotal", &EReco,"EReco/F");
    newTree->Branch("CryDeltaTime", &cryDeltaT,"cryDeltaT/F");
    newTree->Branch("ratio", &ratio,"ratio/F");


    for(unsigned int j = 0; j< cryEnergy[i].size(); j++){
      //if(difTime > 20)
      //if (ratio >= 0.8 && difTime < 4)
      EReco = cryEnergy[i][j];
      cryDeltaT = cryTimes[i][j];
      //ratio = cryRatio[i][j];
      newTree->Fill();
    }

  f->cd();
  newTree->Write();
  f->Close();
  }

  return 0;
}
