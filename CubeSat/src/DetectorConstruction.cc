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
// $Id: DetectorConstruction.cc,v 1.1 2012-09-20 mraine Exp $
// -------------------------------------------------------------------

#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4PhysicalConstants.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4UnionSolid.hh"

#include "G4GDMLParser.hh"
#include "G04SensitiveDetector.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::DetectorConstruction(const G4GDMLParser& parser)
:G4VUserDetectorConstruction(),fParser(parser)
  //fPhysiWorld(NULL), fLogicWorld(NULL), fSolidWorld(NULL)
{}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* DetectorConstruction::Construct()

{
  //DefineMaterials();
  //return ConstructDetector();
    fRegion = new G4Region("Detector");
    G4ProductionCuts* cuts = new G4ProductionCuts();

    G4double defCut = 10.*um;
    cuts->SetProductionCut(defCut,"gamma");
    cuts->SetProductionCut(defCut,"e-");
    cuts->SetProductionCut(defCut,"e+");
    cuts->SetProductionCut(defCut,"proton");

  return fParser.GetWorldVolume();
  G4cout << *(G4Material::GetMaterialTable());  // print the list of materials

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void DetectorConstruction::DefineMaterials()
{ 
  G4double a, z, density;
  G4int nelements;
  G4int natoms;
  G4double fractionmass;
  G4int ncomponents;
  G4bool isotopes = false;
  // Silicon is defined from NIST material database
  G4NistManager * man = G4NistManager::Instance();
 // G4Material * Si = man->FindOrBuildMaterial("G4_Si");

    // Default materials in setup.
  fSiMaterial = man->FindOrBuildMaterial("G4_Si");

  fAlMaterial = man->FindOrBuildMaterial("G4_Al");
  // vacuum

  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
    G4Element* C = new G4Element("Carbon", "C", z=6., a=12.01*g/mole);
    G4Element* Cu  = new G4Element("Copper"  , "Cu" , z= 29., a= 63.54*g/mole);
    G4Element* Mg  = new G4Element("Magnesium"  ,"Mg" , z= 12., a= 24.305*g/mole);
    G4Element* Mn  = new G4Element("Manganese"  ,"Mn" , z= 25., a= 54.94*g/mole);
    G4Element* Al  = new G4Element("Aluminium"  ,"Al" , z= 13., a= 26.98*g/mole);
    G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
    G4Element* Si = new G4Element("Silicium", "Si", z=14 , a=28.086*g/mole);

     man->FindOrBuildMaterial("G4_Si", isotopes);
  //   man->FindOrBuildMaterial("G4_Fe", isotopes);
     man->FindOrBuildMaterial("G4_Cu", isotopes);
  //   man->FindOrBuildMaterial("G4_Ge", isotopes);
  //   man->FindOrBuildMaterial("G4_Mo", isotopes);
  //   man->FindOrBuildMaterial("G4_Ta", isotopes);
 //    man->FindOrBuildMaterial("G4_W" , isotopes);
 //    man->FindOrBuildMaterial("G4_Au", isotopes);
 //    man->FindOrBuildMaterial("G4_Pb", isotopes);
 //    man->FindOrBuildMaterial("G4_PLEXIGLASS", isotopes);
     man->FindOrBuildMaterial("G4_SILICON_DIOXIDE", isotopes);
     man->FindOrBuildMaterial("G4_Al", isotopes);
     man->FindOrBuildMaterial("G4_CESIUM_IODIDE", isotopes);
     man->FindOrBuildMaterial("G4_Galactic", isotopes);
     man->FindOrBuildMaterial("G4_Pb", isotopes);

          air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
          air->AddElement(N, 70.*perCent);
          air->AddElement(O, 30.*perCent);

          // vacuum
          beam =
          new G4Material("Vacuum", density= 1.e-8*g/cm3, nelements=1,
                                 kStateGas, STP_Temperature, 2.e-5*bar);
          beam->AddMaterial(air, fractionmass=1.);

    G4Material* Dural =
    new G4Material("Dural"  , density= 2.700*g/cm3, ncomponents=4);
    Dural->AddElement(Al, fractionmass=0.936);
    Dural->AddElement(Cu, fractionmass=0.044);
    Dural->AddElement(Mg, fractionmass=0.015);
    Dural->AddElement(Mn, fractionmass=0.005);

/*
    //
    //  Nema grade G10 or FR4 - material for PCB
    //
    G4String name        = "NemaG10";
    density     = 1.70*g/cm3;
    ncomponents = 4;
    G4Material* NemaG10 = new G4Material(name,density , ncomponents);
            NemaG10 -> AddElement(Si, natoms=1);
            NemaG10 -> AddElement(O , natoms=2);
            NemaG10 -> AddElement(C , natoms=3);
            NemaG10 -> AddElement(H , natoms=3);
*/
// Used in geometry materials
    gapMaterial = beam;
    DuralMaterial = Dural;
//  	DuralMaterial = man->FindOrBuildMaterial("G4_BRASS", isotopes);

    Cone_dielectric = man->FindOrBuildMaterial("G4_PLEXIGLASS", isotopes);
    ScintMaterial = man->FindOrBuildMaterial("G4_CESIUM_IODIDE", isotopes);
   // Chose main material of detector's walls
    // Dural with Tungsten variant
    Wall_material = Dural;
    Shell_material = man->FindOrBuildMaterial("G4_W", isotopes);
    // Brass without tungsten variant
  //  Wall_material = man->FindOrBuildMaterial("G4_BRASS", isotopes);
  //  Shell_material = man->FindOrBuildMaterial("G4_PLEXIGLASS", isotopes);

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void DetectorConstruction::ConstructSDandField()
{
  //------------------------------------------------
  // Sensitive detectors
  //------------------------------------------------

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  G4String DetSDname = "Detector_SD";
  G04SensitiveDetector* Det1SD =
    new G04SensitiveDetector(DetSDname);
  SDman->AddNewDetector( Det1SD );



  ///////////////////////////////////////////////////////////////////////
  //
  // Example how to retrieve Auxiliary Information for sensitive detector
  //
  const G4GDMLAuxMapType* auxmap = fParser.GetAuxMap();
  G4cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << G4endl << G4endl;
  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++)
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end(); vit++)
    {
      G4cout << "--> Type: " << (*vit).type
                << " Value: " << (*vit).value << G4endl;
    }
  }
  G4cout << G4endl;

  // The same as above, but now we are looking for
  // sensitive detectors setting them for the volumes

  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++)
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end();vit++)
    {
      if ((*vit).type=="SensDet")
      {
        G4cout << "Attaching sensitive detector " << (*vit).value
               << " to volume " << ((*iter).first)->GetName()
               <<  G4endl << G4endl;

        G4VSensitiveDetector* mydet =
          SDman->FindSensitiveDetector((*vit).value);
        if(mydet)
        {
          G4LogicalVolume* myvol = (*iter).first;
          myvol->SetSensitiveDetector(mydet);
        }
        else
        {
          G4cout << (*vit).value << " detector not found" << G4endl;
        }
      }
    }
  }

}
