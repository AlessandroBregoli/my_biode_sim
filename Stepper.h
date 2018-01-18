//Header della classe padre di tutti gli stepper
#ifndef STEPPER
#define STEPPER
#include "imports.h"
class Stepper{
    protected:
        //Passo del simulatore
        double h;
        //passo massimo del simulatore
        double h_max;        
        //Modello SB;L
        const Model* model;
        //Tolleranza assoluta del modello
        double atol;
        //Tolleranza relativa del modello
        double rtol;
        //Ordine dell'errore del modello(Utilizzato per il passo adattivo)
        double k_error;
    public:
        //Step attuale
        int actual_step;
        //Mappa contentente tutti gli step
        std::vector<std::map<std::string, double> > steps;
        //Vettore contenente tutti i "timestamp"
        std::vector<double> time_step;
        //Funzione per eseguire lo step
        void step();
        void init_step();
        void finalize_step();

        const Model* get_model(){return model;}
        virtual void do_step(std::map<std::string, double> in,
                                std::map<std::string, double> &out, double h)
                                {return;};
        Stepper(const Model*, double h, double atol, double rtol);
        
        //Metodo per valutare Funzioni rappresentate da AST
        double evaluate(const ASTNode *n, std::map<std::string, double> state);
        //Metodo per calcolare le derivate
        void derivs(std::map<std::string,double> &result, 
                        std::map<std::string, double> state);
        int get_actual_step(){return actual_step;}

};

#endif