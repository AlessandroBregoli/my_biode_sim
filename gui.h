#include "imports.h"
#define n_points 100
void species_plot(Stepper &s){
    Gnuplot gp;
    gp << "set autoscale\nplot";


    for(int i = 0; i < s.get_model()->getNumSpecies(); i++){
        std::vector<boost::tuple<double, double> > xy_pts;
        const Species *sp = s.get_model()->getSpecies(i);
        for(int j = 0; j < s.get_actual_step(); j++){
            if( s.get_actual_step()/n_points > 0 && j % (s.get_actual_step()/n_points) != 0)
                continue;
            xy_pts.push_back(boost::make_tuple(s.get_time_step()[j], s.get_steps()[j][sp->getId()]));
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
    csv.open(file_name);
    csv<<"time";
    for(int i = 0; i < s.get_model()->getNumSpecies(); i++)
        csv<<","<<s.get_model()->getSpecies(i)->getName();

    csv<<std::endl;
    
    for(int i = 0; i < s.get_actual_step(); i++){
        csv<<s.get_time_step()[i];
        for(int j = 0; j < s.get_model()->getNumSpecies(); j++){
            csv<<","<< s.get_steps()[i][s.get_model()->getSpecies(j)->getId()];
        }
        csv<<std::endl;
    }
    csv.close();

}