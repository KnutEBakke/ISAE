#include "particles.h"
#include "libs.h"


// Auxiliary Functions //

double scalaire(double* a, double* b){
    return (a[0] * b[0] + a[1] * b[1]);
}
double* diff(double* a, double* b){
    double* delta = malloc(2*sizeof(double));
    delta[0] = b[0] - a[0];
    delta[1] = b[1] - a[1];
    return delta;
}

// END //
    
particle* nil_particle(){
    particle* p_nil = malloc(sizeof(particle));
    p_nil->position = malloc(2*sizeof(double));
    p_nil->velocity = malloc(2*sizeof(double));
    return p_nil;
}

void deallocate_particle(particle* p_p) {
    free(p_p->position);
    free(p_p->velocity);
    free(p_p);
}

void print_particle(particle* p_p) {
    printf(" Pos: (%f, %f) \n Vel: (%f, %f) \n Mass: %f \n Radius: %f \n ", (p_p->position)[0], (p_p->position)[1], (p_p->velocity)[0], (p_p->velocity)[1], p_p->mass, p_p->radius);
}

void pos_up(particle* p_p, double dt, int mode) {
    if (mode == 5) { //Position update in case of gravity
        double g = 10;
        (p_p->position)[0] = (p_p->position)[0] + (p_p->velocity)[0]*dt;
        (p_p->position)[1] = (p_p->position)[1] + (p_p->velocity)[1]*dt - (g * pow(dt,2)/2.0) ;
        (p_p->velocity)[1] = (p_p->velocity)[1] - g * dt;
    }
    else {
        (p_p->position)[0] = (p_p->position)[0] + (p_p->velocity)[0]*dt;
        (p_p->position)[1] = (p_p->position)[1] + (p_p->velocity)[1]*dt;
    }
}
    
double t_v_wall_collision(particle* p_p){
    if ((p_p->velocity)[0] > 1E-18) {
        return ((1.0-(p_p->position)[0] - p_p->radius)/ (p_p->velocity)[0]);
    }
    else if ((p_p->velocity)[0] < -1E-18) {
        return ((p_p->radius - (p_p->position)[0])/ (p_p->velocity)[0]);
    }
    else {
        return INFINITY;
    }
}
        
double t_h_wall_collision(particle* p_p, int mode){
    if (mode == 5) {  //Calculates t in case of gravity
        double g = 10;
        double delta;
        double t1= INFINITY;
        double t2 = INFINITY;
        delta = pow((p_p->velocity[1]/g),2) - 2*(1 - p_p->radius - (p_p->position)[1])/g ;
        if (delta > 1E-18) {
            t1 = p_p->velocity[1]/g - sqrt(delta);
        }
        delta = pow((p_p->velocity[1]/g),2) - 2*(p_p->radius - (p_p->position)[1])/g;
        if (delta > 1E-18) {
            t2 = p_p->velocity[1]/g + sqrt(delta);
        }
        if ( (t1 > 1E-18) && (t1 < t2)) {
            return t1;
        }
        else {
            return t2;
        }
    }
    else {    
        if ((p_p->velocity)[1] > 1E-18) {
            return ((1.0-(p_p->position)[1] - p_p->radius)/ (p_p->velocity)[1]);
        }
        else if ((p_p->velocity)[1] < -1E-18) {
            return ((p_p->radius - (p_p->position)[1])/ (p_p->velocity)[1]);
        }
        else {
            return INFINITY;
        }
    }
}

void v_v_wall_collision_up(particle* p_p){    
    (p_p->velocity)[0] = -(p_p->velocity)[0];
    p_p->collision_nb++;
}
    

void v_h_wall_collision_up(particle* p_p){

    (p_p->velocity)[1] = -(p_p->velocity)[1];
    p_p->collision_nb++;

}

double t_particle_collision(particle* p_p1,particle* p_p2){ //Uses the formula provided
    double *delta_p = diff(p_p1->position, p_p2->position);
    double *delta_v = diff(p_p1->velocity, p_p2->velocity);
    double delta = 4*pow(scalaire(delta_p, delta_v), 2) - 4 * scalaire(delta_v, delta_v) *  (scalaire(delta_p, delta_p) - pow(p_p1->radius + p_p2->radius, 2));
    if (delta < 1E-18) {
        free(delta_v);
        free(delta_p);
        return INFINITY;
    }
    double delta_t = -((scalaire(delta_p, delta_v)
    + sqrt(pow(scalaire(delta_p, delta_v),2)
    - scalaire(delta_v, delta_v)*(scalaire(delta_p, delta_p)
    - pow(p_p1->radius + p_p2->radius,2)))))
    /scalaire(delta_v, delta_v);
    free(delta_v);
    free(delta_p);
    if (delta_t < 1E-18) {
        return INFINITY;
    }
    else {
        return delta_t;
    }
}


void v_collision_up(particle* p_p1,particle* p_p2, int mode){
    double *delta_p = diff(p_p1->position, p_p2->position);
    double *delta_v = diff(p_p1->velocity, p_p2->velocity);
    (p_p1->velocity)[0] = (p_p1->velocity)[0] + ((2*p_p2->mass * scalaire(delta_p, delta_v))
                                / ((p_p1->mass + p_p2->mass)* pow((p_p1->radius + p_p2->radius),2))) *delta_p[0] ;
    (p_p1->velocity)[1] = (p_p1->velocity)[1] + ((2*p_p2->mass * scalaire(delta_p, delta_v))
                                / ((p_p1->mass + p_p2->mass)* pow((p_p1->radius + p_p2->radius),2))) *delta_p[1] ;
    (p_p2->velocity)[0] = (p_p2->velocity)[0] - ((2*p_p1->mass * scalaire(delta_p, delta_v))
                                / ((p_p1->mass + p_p2->mass)* pow((p_p1->radius + p_p2->radius),2))) *delta_p[0] ;
    (p_p2->velocity)[1] = (p_p2->velocity)[1] - ((2*p_p1->mass * scalaire(delta_p, delta_v))
                                / ((p_p1->mass + p_p2->mass)* pow((p_p1->radius + p_p2->radius),2))) *delta_p[1] ;
    free(delta_v);
    free(delta_p);
    p_p1->collision_nb++;
    p_p2->collision_nb++;
    if (mode ==3) { //Mode specific
        p_p1->color  = (p_p1->color  % 7) + 1;
        p_p2->color  = (p_p2->color  % 7) + 1;
    }
}
