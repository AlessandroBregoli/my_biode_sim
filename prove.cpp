#include <iostream>
#include <sbml/SBMLTypes.h>
#include <sbml/SBMLTransforms.h>
using namespace std;
LIBSBML_CPP_NAMESPACE_USE
void
printFunctionDefinition (unsigned int n, const FunctionDefinition* fd)
{
  const ASTNode* math;
  char* formula;
  if ( fd->isSetMath() )
  {
    cout << "FunctionDefinition " << n << ", " << fd->getId();
    math = fd->getMath();
    /* Print function arguments. */
    if (math->getNumChildren() > 1)
    {
      cout << "(" << ( math->getLeftChild() )->getName();
      for (n = 1; n < math->getNumChildren() - 1; ++n)
      {
        cout <<", " << ( math->getChild(n) )->getName();
      }
    }
    cout <<") := ";
    /* Print function body. */
    if (math->getNumChildren() == 0)
    {
      cout << "(no body defined)";
    }
    else
    {
      math    = math->getChild(math->getNumChildren() - 1);
      formula = SBML_formulaToString(math);
      cout << formula << endl;
      free(formula);
    }
  }
}
void
printRuleMath (unsigned int n, const Rule* r, const Model* m)
{
  char* formula;
  const ASTNode* node = r->getMath();
  if ( r->isSetMath() )
  {
    formula = SBML_formulaToString( r->getMath() );
    if (r->getVariable().length() > 0)
    {
      cout << "Rule " << n << ", formula: "
       << r->getVariable() << " = " << formula << "=" << SBMLTransforms::evaluateASTNode(node, m)<<endl;
    }
    else
    {
      cout << "Rule " << n << ", formula: "
       << formula << " = 0" << endl;
    }
    free(formula);
  }
}
void
printReactionMath (unsigned int n, const Reaction* r, const Model* m)
{
  char* formula;
  const KineticLaw* kl;
  if (r->isSetKineticLaw())
  {
    kl = r->getKineticLaw();
    if ( kl->isSetMath() )
    {
      formula = SBML_formulaToString( kl->getMath() );
      cout << "Reaction " << n << ", formula: " << formula << "="<< SBMLTransforms::evaluateASTNode(kl->getMath(), m)<<endl;
      free(formula);
    }
  }
}
void
printEventAssignmentMath (unsigned int n, const EventAssignment* ea)
{
  std::string variable;
  char* formula;
  if ( ea->isSetMath() )
  {
    variable = ea->getVariable();
    formula  = SBML_formulaToString( ea->getMath() );
    cout <<"  EventAssignment " << n
         << ", trigger: " << variable << " = " << formula << endl;
    free(formula);
  }
}
void
printEventMath (unsigned int n, const Event* e)
{
  char* formula;
  unsigned int i;
  if ( e->isSetDelay() )
  {
    formula = SBML_formulaToString( e->getDelay()->getMath() );
    cout << "Event " << n << " delay: " << formula << endl;
    free(formula);
  }
  if ( e->isSetTrigger() )
  {
    formula = SBML_formulaToString( e->getTrigger()->getMath() );
    cout << "Event " << n << " trigger: " << formula << endl;
    free(formula);
  }
  for (i = 0; i < e->getNumEventAssignments(); ++i)
  {
    printEventAssignmentMath(i + 1, e->getEventAssignment(i));
  }
  cout << endl;
}
void
printMath (const Model* m)
{
  unsigned int  n;
 
  for (n = 0; n < m->getNumRules(); ++n)
  {
    printRuleMath(n + 1, m->getRule(n), m);
  }
  cout << endl;
  for (n = 0; n < m->getNumReactions(); ++n)
  {
    printReactionMath(n + 1, m->getReaction(n), m);
  }
  cout << endl;
  for (n = 0; n < m->getNumEvents(); ++n)
  {
    printEventMath(n + 1, m->getEvent(n));
  }
}
int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cout << endl << "Usage: printMath filename" << endl << endl;
    return 1;
  }
  const char* filename   = argv[1];
  SBMLDocument* document = readSBML(filename);
  if (document->getNumErrors() > 0)
  {
    cerr << "Encountered the following SBML errors:" << endl;
    document->printErrors(cerr);
    return 1;
  }

  Model* model = document->getModel();
  if (model == 0)
  {
    cout << "No model present." << endl;
    return 1;
  }
  printMath(model);
  cout << endl;
  for(int i= 0; i < model->getNumParameters(); i++){
      const Parameter* p = model->getParameter(i);
      if(p->getMath())
        cout << p->getName()<<":"<<SBMLTransforms::evaluateASTNode(p->getMath(), model)<<endl;
      else
        cout << p->getId()<<":"<<p->getValue()<<endl;
  }
  delete document;
  return 0;
}