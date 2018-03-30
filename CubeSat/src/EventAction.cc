 //
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: EventAction.cc,v 1.2 2006/06/29 16:40:15 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"

#include "RunAction.hh"
#include "EventActionMessenger.hh"
//#include "HistoManager.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include <fstream> 
#include "G4SystemOfUnits.hh"
#include "Analysis.hh"
//#include "g4csv_defs.hh"
#include "g4root_defs.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* run)
:runAct(run), drawFlag("none"), printModulo(10000),
HIST_MAX(10*MeV),
HIST_MIN(0 *MeV)

{
  eventMessenger = new EventActionMessenger(this);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
  delete eventMessenger;
 //   std::ofstream file_out("spectrum.dat");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* evt)
{
 G4int evtNb = evt->GetEventID();
    InitEnergy = 0.;
 //   totalEdep = 0.;
 //   SumDetEdep = 0.;
    // collomator flag - for check if the particle came from collimator
 //   FoilCame = 0;
    StartAngle = 0.;
    signal  = 0;
 //   gammsignal = 0;
    for(int i = 0; i<NODET; i++)
    {
         totalChargeDep[i] = 0.;
    }
 //printing survey
 //if (evtNb%printModulo == 0)
 //   G4cout << "\n---> Begin of Event: " << evtNb << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{

    //get event number
    G4int evtNb = evt->GetEventID();
    G4int bin = 0;

     //printing survey
     if (evtNb%printModulo == 0)
        G4cout << "\n---> Begin of Event: " << evtNb << G4endl;

     // init spectrum
     double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
     if (InitEnergy > 0.)
      {
        int index = int(floor((InitEnergy-HIST_MIN)/bin_width));
        if(index >= 0 && index < NOBINS)
        runAct->AddInitSpectrum(index);
 //           histogram1[index]++;
      }

  //   G4Root::G4AnalysisManager* RootManager = G4Root::G4AnalysisManager::Instance();
  //   RootManager->FillH1(0,InitEnergy,1.0);
    // get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // check if there is any signal in detectors
//    for (i=1;i<NODET;i++)
//    {
//        for (j=1;j<NODET;j++)
//        {
//        if (totalDetEdep[i][j] > 0.) signal = 1;
//        }
  //      if (totalDetEGamm[i] > 0.) gammsignal = 1;
//    }

    // fill ntuple with all non-zero signals

    for (i=0;i<NODET;i++)
    {

            if (totalChargeDep[i] != 0.)
            {
    analysisManager->FillNtupleIColumn(1,0, evtNb);
    analysisManager->FillNtupleDColumn(1,1, InitEnergy/keV);
    analysisManager->FillNtupleIColumn(1,2,i+1);
    analysisManager->FillNtupleDColumn(1,3, totalChargeDep[i]);
    analysisManager->AddNtupleRow(1);
        runAct->AddTotalCharge(i,totalChargeDep[i]);

        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


