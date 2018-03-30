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
// -------------------------------------------------------------------
// $Id: SteppingAction.cc,v 1.1 2012-09-21 mraine Exp $
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "Analysis.hh"

#include "SteppingAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "stddef.h"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

SteppingAction::SteppingAction(RunAction* RuAct,EventAction* event)
: G4UserSteppingAction(), runAction(RuAct), eventAction(event)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void SteppingAction::UserSteppingAction(const G4Step* step)
{ 
     G4double flagParticle=0.;
     G4double energydep = 0.;
     G4double kinenergy = 0.;
     G4double PartType = 0.;
     G4double momentumx = 0.;
     G4double momentumy = 0.;
     G4double momentumz= 0.;
 //    G4double momentum2 = 0.;
 //    G4double angz = 0.;
 //    G4int colimflag = 0;
 //    G4double edep = 0.;
     G4double chg = 0;
     G4int detNo = -1.;
 //    G4int lineNo = -1;
 //    G4double pi  = 3.14159265358979323846;

// In which volume point is located

  G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetPhysicalVolume();
  G4String name = volume->GetName();

  G4StepPoint* point1 = step->GetPreStepPoint();
  G4TouchableHandle touch1 = point1->GetTouchableHandle();

  G4StepPoint* point2 = step->GetPostStepPoint();
  G4TouchableHandle touch2 = point2->GetTouchableHandle();

 // G4int CopyNo = volume->GetCopyNo();
 // G4String MatName = volume->GetLogicalVolume()->GetMaterial()->GetName();
 // G4cout << "name =  " << "  " << name << "  copy = " << CopyNo << "  Metrial =" << MatName<< G4endl;


  const G4Track* track = step->GetTrack();
  if ( track->GetParentID() == 0 )
      {
      PartType = 1.; //Primary
      // Check if the particle just borned and is not a secondary
      if ( track->GetCurrentStepNumber() == 1)
         {
      energydep = step->GetTotalEnergyDeposit();
      kinenergy = step->GetTrack()->GetKineticEnergy();
      kinenergy = energydep+kinenergy;
      eventAction->AddInitSpectrum(kinenergy); //primary energy in current event
      //G4cout << "energy =  " << "  " << kinenergy << G4endl;
         }


      }

 // Detector number with signal
     chg = step->GetTrack()->GetDynamicParticle()->GetCharge(); // get particle charge
     if ( chg != 0)
      {
         //Get detector number
         if (name == "Detector1_PV") detNo = 0;
         if (name == "Detector2_PV") detNo = 1;
         if (name == "Detector3_PV") detNo = 2;

    if (detNo >= 0 && point1->GetStepStatus() == fGeomBoundary) //particle entered detector
     {
        eventAction->AddDetChg(detNo, 1.*chg);
    }
    if (detNo >= 0 && point2->GetStepStatus() == fGeomBoundary) // particle exited detector
    {
        eventAction->AddDetChg(detNo, -1.*chg);
    }

    }

}    
