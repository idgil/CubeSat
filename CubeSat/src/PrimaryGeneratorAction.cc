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
// $Id: PrimaryGeneratorAction.cc,v 1.1 2012-09-21 mraine Exp $
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PrimaryGeneratorAction::PrimaryGeneratorAction()
//PrimaryGeneratorGPS::PrimaryGeneratorGPS()
    :G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
  //G4int n_particle = 1;
  //fParticleGun  = new G4ParticleGun(n_particle);
   fParticleGun  = new G4GeneralParticleSource();

  // default gun parameters
 // fParticleGun->SetParticleEnergy(14.*MeV);
 //
 // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  //fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-100.*um));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PrimaryGeneratorAction::~PrimaryGeneratorAction()
//PrimaryGeneratorGPS::~PrimaryGeneratorGPS()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
//void PrimaryGeneratorGPS::PrimaryGeneratorGPS(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
