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
// $Id: EventAction.hh,v 1.2 2006/06/29 16:39:25 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include <fstream> 

class RunAction;
class EventActionMessenger;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction*);
   ~EventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void   EndOfEventAction(const G4Event*);

    void AddInitSpectrum (G4double energy)		{InitEnergy = energy;}
    void AddEnergyDeposit(G4int i, G4double edep) {Edep[i] += edep;}

    void SetDrawFlag(G4String val) {drawFlag = val;}
    void SetPrintModulo(G4int val) {printModulo = val;}

    void AddEdep(G4double edep) {totalEdep += edep;};
    void AddDetChg (G4int i, G4double chg)        { totalChargeDep[i] += chg;};
    void AddTotalEdep (G4double edep)        { SumDetEdep += edep;};
    void AddDetEPrim (G4int i, G4double edep)        { totalDetEPrim[i] += edep;};
    // Gamma loss energy
    void AddDetEGamm (G4int i, G4double edep)        { totalDetEGamm[i] += edep;};
    // Secondary particles loss energy
    void AddDetESec (G4int i, G4double edep)        { totalDetESec[i] += edep;};
    // energy loss from particles not from collimator
    void AddDetBack (G4int i, G4double edep)        { totalDetBack[i] += edep;};
    void SetCollimator(G4int flag) {FoilCame = flag;};
    // start angle of primary particle
    void SetStartAngle(G4double angle) {StartAngle = angle;};
       G4double GetStartAngle() {return StartAngle;}
   //     void AddSpectrum (G4double edep)		{InitEnergy = edep;};
    

  private:
    RunAction*             runAct;
    G4double               bin_width,InitEnergy;
    G4int 					i, j, k;
    G4String               drawFlag;
    G4int                  printModulo;

    EventActionMessenger*  eventMessenger;

    static const int NODET = 3;
    static const int NOBINS = 100;
    const double HIST_MAX;
    const double HIST_MIN;
    
    G4double               totalEdep;
    G4double               totalChargeDep[NODET];
    G4double               Edep[NODET];
    G4double               SumDetEdep;
    G4double               totalDetEPrim[NODET];
    G4double               totalDetEGamm[NODET];
    G4double               totalDetESec[NODET];
    G4double               totalDetBack[NODET];
    G4double			   StartAngle;
    G4int 				   FoilCame;
    G4double               signal, gammsignal ;
 //   int histogram1[NOBINS];

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
