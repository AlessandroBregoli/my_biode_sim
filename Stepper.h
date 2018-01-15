#ifndef STEPPER
#define STEPPER
//#include "Bio_ode_system.h"
#include "imports.h"
class Stepper{
    protected:
        double h;
        double h_max;

        
        const Model* model;
        double atol;
        double rtol;
        double k_error;
    public:
        //Bio_ode_system ode_system;
        int actual_step;
        std::vector<std::map<std::string, double> > steps;
        std::vector<double> time_step;
        void step();
        void init_step();
        void finalize_step();
        const Model* get_model(){return model;}
        virtual void do_step(std::map<std::string, double> in,std::map<std::string, double> &out, double h){return;};
        Stepper(const Model*, double h, double atol, double rtol);
        
        
        double evaluate(const ASTNode *n, std::map<std::string, double> state);
        void derivs( std::map<std::string,double> &result, std::map<std::string, double> state);
        int get_actual_step(){return actual_step;}

};

#endif