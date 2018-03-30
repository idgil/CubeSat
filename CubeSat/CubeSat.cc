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
// $Id: Microelectronics.cc,v 1.5 2010-11-18 11:48:21 allison Exp $
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifdef G4MULTITHREADED
  #include "G4MTRunManager.hh"
#else
  #include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#include "G4UIExecutive.hh"

#ifdef G4VIS_USE
  #include "G4VisExecutive.hh"
#endif


#include "DetectorConstruction.hh"
#include "G04SensitiveDetector.hh"
#include "PhysicsList.hh"
//#include "EventAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "ActionInitialization.hh"

#include "G4GDMLParser.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int main(int argc,char** argv) 
{
    G4cout << G4endl;
       G4cout << "Usage: CubeSat <intput_gdml_file:mandatory>"
              << G4endl;
       G4cout << G4endl;


  G4UIExecutive* session = NULL;
//  if (argc==1)   // Define UI session for interactive mode.
//  {
//      session = new G4UIExecutive(argc, argv);
//  }
  if (argc<2)
  {
     G4cout << "Error! Mandatory input file is not specified!" << G4endl;
     G4cout << G4endl;
     return -1;
  }
  // Choose the Random engine
  
 // G4Random::setTheEngine(new CLHEP::RanecuEngine);
  // Random from time and ID
    CLHEP::HepRandom::setTheSeed(time(0)+getpid());



    // Detect interactive mode (if only one argument) and define UI session
    //
    G4UIExecutive* ui = 0;
    if ( argc == 2 ) {
      ui = new G4UIExecutive(argc, argv);
    }
    G4GDMLParser parser;
    parser.Read(argv[1]);

  // Construct the default run manager


#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
   runManager->SetNumberOfThreads(1); // Is equal to 2 by default
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory user initialization classes
  DetectorConstruction* detector = new DetectorConstruction(parser);
  runManager->SetUserInitialization(detector);
  
  runManager->SetUserInitialization(new PhysicsList);
  
  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization(detector));
  
  // Initialize G4 kernel
  runManager->Initialize();
  
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  
  // Get the pointer to the User Interface manager 
  G4UImanager* UImanager = G4UImanager::GetUIpointer();  

 // if (argc==1)   // Define UI session for interactive mode.
 // {
 //   UImanager->ApplyCommand("/control/execute Telescope.mac");
 //   session->SessionStart();
 //   delete session;
 // }
  // Process macro or start UI session
  if ( ! ui )   // batch mode
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[2];
    UImanager->ApplyCommand(command+fileName);
  }
  else           // Batch mode
  { 
      UImanager->ApplyCommand("/control/execute CubeSat.mac ");
      ui->SessionStart();
      delete ui;
  }

  delete visManager;

  delete runManager;

  return 0;
}

