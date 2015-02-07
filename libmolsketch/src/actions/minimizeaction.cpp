#include "minimizeaction.h"
#include "../minimise.h"
#include "molscene.h"

namespace Molsketch {

  minimizeAction::minimizeAction(MolScene *scene) :
    genericAction(scene)
  {
    setIcon(QIcon(":images/min.png")) ;
    setText(tr("Minimize energy")) ;
  }

  void minimizeAction::mousePressEvent(QGraphicsSceneMouseEvent *event)
  {
    Bond *bond = scene()->bondAt (event ->scenePos());
    if (bond) {
      Molecule *molecule = bond ->molecule();
      Minimise minimise(40 /*m_bondLength*/); // FIXME
      minimise.mirrorBondInMolecule(molecule, bond);
      return;
    }

    Molecule * molecule = scene()->moleculeAt(event->scenePos());
    if (molecule)
    {
      Minimise minimise(40 /*m_bondLength*/); // FIXME
      minimise.conformationalSearchMolecule(molecule);
    }
  }

} // namespace Molsketch