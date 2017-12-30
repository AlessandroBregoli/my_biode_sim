#include "Stepper.h"
#include "imports.h"
Stepper::Stepper(const Model* m):model(m){
    actual_step = 0;
    steps.resize(5);
    for(int i= 0; i < model->getNumParameters(); i++){
        const Parameter* p = model->getParameter(i);
        steps[0][p->getId()] = p->getValue();
    }
    for(int i = 0; i < model->getNumSpecies(); i++){
        const Species *s = model->getSpecies(i);
        steps[0][s->getId()] = s->getInitialAmount();

    } 
    for(int i=0; i < model->getNumRules(); i++){
        const Rule* r = model->getRule(i);
        steps[0][r->getVariable()] = evaluate(r->getMath());
    }
}

double Stepper::evaluate(const ASTNode* n){
    switch(n->getType()){
        case AST_INTEGER:
        case AST_REAL:
            return n->getValue();
        case AST_NAME:
            return steps[actual_step][n->getName()];
        case AST_PLUS:
            return evaluate(n->getLeftChild()) + evaluate(n->getRightChild());
        case AST_MINUS:
            return evaluate(n->getLeftChild()) - evaluate(n->getRightChild());
        case AST_TIMES:
            return evaluate(n->getLeftChild()) * evaluate(n->getRightChild());
        case AST_DIVIDE:
            return evaluate(n->getLeftChild()) / evaluate(n->getRightChild());
        case AST_FUNCTION_LN:
            return std::log(evaluate(n->getLeftChild()));
        case AST_FUNCTION_POWER:
            return std::pow(evaluate(n->getLeftChild()) , evaluate(n->getRightChild()));
        default:
            throw("Stronzata exception");
   }
    
}

void Stepper::derivs( std::map<std::string,double> &result){
        for(auto const& element: steps[actual_step])
            result[element.first] = 0.0;
        for(int i = 0; i < model->getNumReactions(); i++){
            const Reaction *r = model->getReaction(i);
            double reaction_val = evaluate(r->getKineticLaw()->getMath());
            for(int j = 0; j < r->getNumReactants(); j++){
                result[r->getReactant(j)->getSpecies()] -= reaction_val*r->getReactant(j)->getStoichiometry();
            }

            for(int j = 0; j < r->getNumProducts(); j++){
                result[r->getProduct(j)->getSpecies()] += reaction_val*r->getProduct(j)->getStoichiometry();
            }
        }
}