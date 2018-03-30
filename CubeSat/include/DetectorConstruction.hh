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
// $Id: DetectorConstruction.hh,v 1.1 2012-09-20 mraine Exp $
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4Region;

class G4GDMLParser;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction(const G4GDMLParser& parser);
  //DetectorConstruction();
    virtual void ConstructSDandField();

  ~DetectorConstruction();

  G4VPhysicalVolume* Construct();

  G4Region* GetTargetRegion()  {return fRegion;}
                         
private:
      const G4GDMLParser& fParser;


  G4double           fWorldSizeX;
  G4double           fWorldSizeY;
  G4double           fWorldSizeZ;

  G4VPhysicalVolume* fPhysiWorld;
  G4LogicalVolume*   fLogicWorld;  
  G4Box*             fSolidWorld;
  G4VPhysicalVolume* ShieldPhysi;
  G4LogicalVolume*   ShieldLogic;

    G4Material*        fSiMaterial;
    G4Material*        fAlMaterial;
    G4Material*        ScintMaterial;
    G4Material*         Wall_material;
    G4Material*           beam;
    G4Material*           air;

    G4double            MainR;
         G4double            MainZ;
         G4double            Det1R;
         G4double            Det1Z;
         G4double            FoilR;
         G4double            FoilZ;
         G4double            FotoR;
         G4double            FotoZ;
         G4double            Det2R;
         G4double            Det2Z;

         G4double            Det3R;
         G4double            Det3Z;
         G4double            Det4R;
         G4double            Det4Z;
         G4double            Gap1R;
         G4double            Gap1Z;
         G4double            Gap2R;
         G4double            Gap2Z;
         G4double            Gap3R;
         G4double            Gap3Z;
         G4double            Gap4R;
         G4double            Gap4Z;
         G4double            Gap5R;
         G4double            Gap5Z;
         G4double            FoilGapR;
         G4double            FoilGapZ;
         G4double            ConeRmin1;
         G4double            ConeRmax1;
         G4double            ConeRmin2;
         G4double            ConeRmax2;
         G4double            ConeDz;
         G4double 			 CapZ;
         G4double 			 CapRmax;
         G4double			 CapRmin;
         G4double			 UpperTube1Z;
         G4double			 UpperTube1Rmin;
         G4double			 UpperTube1Rmax;
         G4double			 UpperTube2Z;
         G4double			 UpperTube2Rmin;
         G4double			 UpperTube2Rmax;
         G4double			 LowTube1Z;
         G4double			 LowTube1Rmin;
         G4double			 LowTube1Rmax;
         G4double			 LowTube2Z;
         G4double			 LowTube2Rmin;
         G4double			 LowTube2Rmax;
         G4double			 LowTube3Z;
         G4double			 LowTube3Rmin;
         G4double			 LowTube3Rmax;
         G4double			 W_shield1Z;
         G4double			 W_shield1Rmax;
         G4double			 W_shield1Rmin;
         G4double			 W_shield2Z;
         G4double			 W_shield2R;
         G4double			 W_shield3Rmin, W_shield3Rmax, W_shield3Z, W_shield3Rmid;



         G4Material*         gapMaterial;
         G4Material*         DuralMaterial;
         G4Material*         Shell_material;
         G4Material*         Cone_dielectric;
    //     G4int               nbOfLayers;
    //     G4double            layerThickness;
//         G4UniformMagField*  magField;
         G4VPhysicalVolume*  pDet1;
         G4VPhysicalVolume*  pDet2;
         G4VPhysicalVolume*  pDet3;
         G4VPhysicalVolume*  pDet4;
         G4VPhysicalVolume*  pVacDet;

         G4VisAttributes* Det1VisAtt;
         G4VisAttributes* Det2VisAtt;
         G4VisAttributes* GapVisAtt;
         G4VisAttributes* FoilVisAtt;
         G4VisAttributes* WVisAtt;
         G4VisAttributes* ConeVisAtt;
         G4VisAttributes* Tube1VisAtt;
         G4VisAttributes* Tube2VisAtt;
         G4VisAttributes* WorldVisAtt;


  G4Region*          fRegion;

  void DefineMaterials();

  G4VPhysicalVolume* ConstructDetector();     
};
#endif
