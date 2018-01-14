#include "Stepper.h"
#include "imports.h"
Stepper::Stepper(const Model* m, double atol, double rtol):model(m){
    this->atol = atol;
    this->rtol = rtol;
    actual_step = 0;
    steps.resize(5);
    time_step.resize(5);
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
        steps[0][r->getVariable()] = evaluate(r->getMath(), steps[0]);
    }
}

double Stepper::evaluate(const ASTNode* n, std::map<std::string, double> state){
    switch(n->getType()){
        case AST_INTEGER:
        case AST_REAL:
            return n->getValue();
        case AST_NAME:
            return state[n->getName()];
        case AST_PLUS:
            return evaluate(n->getLeftChild(), state) + evaluate(n->getRightChild(), state);
        case AST_MINUS:
            return evaluate(n->getLeftChild(), state) - evaluate(n->getRightChild(), state);
        case AST_TIMES:
            return evaluate(n->getLeftChild(), state) * evaluate(n->getRightChild(), state);
        case AST_DIVIDE:
            return evaluate(n->getLeftChild(), state) / evaluate(n->getRightChild(), state);
        case AST_FUNCTION_LN:
            return std::log(evaluate(n->getLeftChild(), state));
        case AST_FUNCTION_POWER:
            return std::pow(evaluate(n->getLeftChild(), state) , evaluate(n->getRightChild(), state));
        default:
            throw("Stronzata exception");
   }
    
}

void Stepper::derivs( std::map<std::string,double> &result, std::map<std::string, double> state){
        for(auto const& element: state)
            result[element.first] = 0.0;
        for(int i = 0; i < model->getNumReactions(); i++){
            const Reaction *r = model->getReaction(i);
            double reaction_val = evaluate(r->getKineticLaw()->getMath(), state);
            for(int j = 0; j < r->getNumReactants(); j++){
                result[r->getReactant(j)->getSpecies()] -= reaction_val*r->getReactant(j)->getStoichiometry();
            }

            for(int j = 0; j < r->getNumProducts(); j++){
                result[r->getProduct(j)->getSpecies()] += reaction_val*r->getProduct(j)->getStoichiometry();
            }
        }
}

void Stepper::init_step(){
        if(steps.size()  == actual_step + 1)
            steps.resize(actual_step*2);
        if(time_step.size()  == actual_step + 1)
            time_step.resize(actual_step*2);
}

void Stepper::finalize_step(){
    actual_step++;
    time_step[actual_step] = time_step[actual_step-1] + h;

}

void Stepper::step(){
    init_step();
    std::map<std::string, double> out1, out2, out3;
    double err;
    do{
        err=0;
        do_step(steps[actual_step], out1, h);

        do_step(steps[actual_step], out2,h/2);
        do_step(out2, out3,h/2);

        for(auto const& element: out1){
            double scale = atol + std::abs(element.second)*rtol;
            err += std::pow((out1[element.first]-out3[element.first])/scale,2);
        }
        err = std::sqrt(err/out1.size());
        if(err > 1){
            h = h*std::pow(1/err,1/k_error);  
                    
        }
    }while(err > 1);

    for(auto const& element: out1){
        steps[actual_step + 1][element.first] = element.second;
    }
    finalize_step();
    h = h*std::pow(1/err,1/k_error);
}