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
// $Id: PhysicsList.cc,v 1.1 2012-09-21 mraine Exp $
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "PhysicsList.hh"
#include "G4SystemOfUnits.hh"
#include "MuelPhyslist.hh"
#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>
#include "G4UnitsTable.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonQMDPhysics.hh"
// particles

   #include "G4BosonConstructor.hh"
   #include "G4LeptonConstructor.hh"
   #include "G4MesonConstructor.hh"
   #include "G4BosonConstructor.hh"
   #include "G4BaryonConstructor.hh"
   #include "G4IonConstructor.hh"
   #include "G4ShortLivedConstructor.hh"
    #include "OpticalPhysics.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PhysicsList::PhysicsList():  G4VModularPhysicsList()
{
  defaultCutValue = 10.*micrometer;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;
  cutForProton    = defaultCutValue;

  G4int verb = 0.;
  SetVerboseLevel(verb);
  // EM Physics
   //RegisterPhysics( new MuelPhyslist("micro EM"));
   RegisterPhysics( new G4EmStandardPhysics_option3);

  //RegisterPhysics( new G4EmLivermorePhysics);
    // Cerenkov Radiation Physics
  //RegisterPhysics(new OpticalPhysics("Optics"));
 //  RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP);
     // hadron inelsctis
   //     RegisterPhysics(new G4HadronPhysicsQGSP_BERT_HP(verb));
     //   RegisterPhysics(new G4HadronPhysicsINCLXX);
        // photo-nuclear?
//        RegisterPhysics(new G4EmExtraPhysics(verb));
        // Hadron elastic
  //      RegisterPhysics(new G4HadronElasticPhysics(verb));
        //Ion Elastic
 //       RegisterPhysics(new G4IonElasticPhysics(verb));
        // smth else
 //       RegisterPhysics(new G4StoppingPhysics(verb));
     // Ion inelactic
        //   RegisterPhysics(new G4IonBinaryCascadePhysics);
  //      RegisterPhysics(new G4IonQMDPhysics(verb));
    // Neutron cut
  //      RegisterPhysics(new G4NeutronTrackingCut(verb));


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PhysicsList::~PhysicsList()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

 void PhysicsList::ConstructParticle()
   {
     G4BosonConstructor  pBosonConstructor;
     pBosonConstructor.ConstructParticle();

     G4LeptonConstructor pLeptonConstructor;
     pLeptonConstructor.ConstructParticle();

     G4MesonConstructor pMesonConstructor;
     pMesonConstructor.ConstructParticle();

     G4BaryonConstructor pBaryonConstructor;
     pBaryonConstructor.ConstructParticle();

     G4IonConstructor pIonConstructor;
     pIonConstructor.ConstructParticle();

     G4ShortLivedConstructor pShortLivedConstructor;
     pShortLivedConstructor.ConstructParticle();
   }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PhysicsList::SetCuts()
{
  if (verboseLevel >0)
  {
    G4cout << "PhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }  
  
  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma 
  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");
  SetCutValue(cutForProton, "proton");
  
  if (verboseLevel>0) { DumpCutValuesTable(); }
}
void PhysicsList::SetNbOfPhotonsCerenkov(G4int maxNumber)
{
   fOpticalPhysics->SetNbOfPhotonsCerenkov(maxNumber);
}

void PhysicsList::SetVerbose(G4int verbose)
{
   fOpticalPhysics->GetCerenkovProcess()->SetVerboseLevel(verbose);
   fOpticalPhysics->GetScintillationProcess()->SetVerboseLevel(verbose);
   fOpticalPhysics->GetAbsorptionProcess()->SetVerboseLevel(verbose);
   fOpticalPhysics->GetRayleighScatteringProcess()->SetVerboseLevel(verbose);
   fOpticalPhysics->GetMieHGScatteringProcess()->SetVerboseLevel(verbose);
   fOpticalPhysics->GetBoundaryProcess()->SetVerboseLevel(verbose);
}
