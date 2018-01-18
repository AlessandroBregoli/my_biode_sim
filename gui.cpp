#include "imports.h"
#include "gui.h"
#include "Euler_stepper.h"
#include "RK4_stepper.h"
#define n_points 100
#define THRESHOLD 1024
void species_plot(Stepper &s){
    Gnuplot gp;
    gp << "set autoscale\nplot";


    for(int i = 0; i < s.get_model()->getNumSpecies(); i++){
        std::vector<boost::tuple<double, double> > xy_pts;
        const Species *sp = s.get_model()->getSpecies(i);
        for(int j = 0; j < s.get_actual_step(); j++){
            xy_pts.push_back(boost::make_tuple(s.time_step[j], s.steps[j][sp->getId()]));
        }
        
        //gp.send1d(xy_pts);
        if(i != 0)
            gp<<", ";
        gp << gp.binFile1d(xy_pts,"record")<<"with lines title '"<<s.get_model()->getSpecies(i)->getName()<<"'";
    }
    gp<<"\n";
}

void species_csv(Stepper &s, std::string file_name){
    std::ofstream csv;
    
    char buf[THRESHOLD];
    csv.rdbuf()->pubsetbuf(buf,sizeof(buf));
    csv.open(file_name);

    
    csv<<"time";
    std::vector<std::string> id_specie;
    for(int i = 0; i < s.get_model()->getNumSpecies(); i++){
        
        csv<<","<<s.get_model()->getSpecies(i)->getName();
        id_specie.push_back(s.get_model()->getSpecies(i)->getId());
    }

    csv<<"\n";

    for(int i = 0; i < s.get_actual_step(); i++){
        csv<<s.time_step[i];
        for(int j = 0; j < s.get_model()->getNumSpecies(); j++){
            csv<<","<< s.steps[i][id_specie[j]];
        }
    }
    csv.close();

}

void gui(){
    std::string m;
    char c;
    double atol = 1.0;
    double rtol = 1.0;
    double h = 1;
    double max_time;

    Model* model;
    SBMLReader reader;
    SBMLDocument *doc;
    Stepper *stepper;
        while(true){
        std::cout<<"Inerire il path del modello: "<<std::flush;
        std::cin>>m;
        std::cout<<"Inserire la tolleranza assoluta: "<<std::flush;
        std::cin>>atol;
        std::cout<<"Inserire la tolleranza relativa: "<<std::flush;
        std::cin>>rtol;
        std::cout<<"Inserire il passo massimo: "<<std::flush;
        std::cin>>h;
        std::cout<<"Inserire il tempo di esecuzione: "<<std::flush;
        std::cin>>max_time;
        do{
            std::cout<<"Inserire (E) per usare il metodo di Eulero o " 
                     <<"(R) per Runge-Kutta4: "<<std::flush;
            std::cin>>c;
        }while(c != 'e' && c != 'E' && c != 'r' && c != 'R');
        doc  = reader.readSBML(m);
        model  = doc->getModel();
        free(doc);
        switch(c){
            case 'e':
            case 'E':
                stepper = new Euler_stepper(model,h,atol,rtol);
                break;
            case 'r':
            case 'R':
                stepper = new RK4_stepper(model,h,atol,rtol);
                break;
        }
        do{
            stepper->step();
        }while(stepper->time_step[stepper->get_actual_step()] < max_time);
        species_plot(*stepper);
        species_csv(*stepper, "dati.csv");
        while((std::getchar())!='\n');
        std::cout<<"Premere c per continuare: "<<std::endl;
        c = std::getchar();
        if(c != 'c' && c != 'C')
            break;



    }
}
