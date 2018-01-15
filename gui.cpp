#include "imports.h"
#include "gui.h"
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
    std::cout<<"POTA"<<std::endl;
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




