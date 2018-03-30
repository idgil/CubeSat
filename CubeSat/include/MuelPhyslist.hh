#ifndef MuelPhyslist_h
#define MuelPhyslist_h 1

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4VPhysicsConstructor.hh"
#include "globals.hh"
//#include "G4VUserPhysicsList.hh"

class MuelPhyslist : public G4VPhysicsConstructor
{
  public:

    MuelPhyslist(const G4String& name ="EM");
    virtual ~MuelPhyslist();

protected:

  // these methods construct particles
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructBarions();

  // these methods construct physics processes and register them
  void ConstructGeneral();
  void ConstructEM();

  // Construct particle and physics
  void ConstructParticle();
  void ConstructProcess();

    // Construct particle and physics
//    void ConstructParticle();
 //   void ConstructProcess();

};

#endif


/*

protected:

  // these methods construct particles
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructBarions();

  // these methods construct physics processes and register them
  void ConstructGeneral();
  void ConstructEM();

  // Construct particle and physics
  void ConstructParticle();
  void ConstructProcess();
*/
