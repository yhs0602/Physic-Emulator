#include "physics.h"
Object *objects[MAX_OBJECTS];

void update(Object *everything,Object *o){
     Vector impact,gravity,distancesquare,electroforce;
     int i;
     distancesquare.x=0;
     distancesquare.y=0;
     distancesquare.z=0;
     distancesquare.total=0;
     
     for(i=0;i<MAX_OBJECTS;i++){                                                //��� ��¥�� ��� 
             if(everything[i]==NULL)
                     continue;
             distancesquare=(*Calc_distance_square(&everything[i],o));
             impact=*calc_impact(everything[i],o,distancesquare);
             gravity=*calc_gravity(everything[i],o,distancesquare);
             electroforce=*calc_electroforce(everything[i],o,distancesquare);
             AddVector(&(o->f_net),impact);
             AddVector(&(o->f_net),gravity);
             AddVector(&(o->f_net),electroforce);
             SubVector(&(everything[i]->f_net),impact);
             SubVector(&(everything[i]->f_net),gravity);
             SubVector(&(everything[i]->f_net),electroforce);
     }
     AddVector(&(o->acceleration),DivVectorNum(&(o->f_net),o->mass));              //F=ma 
     AddVector(&(o->velocity),MulVectorNum(&(o->acceleration),timer_interval)));    //����
     (o->x)+=(((o->velocity)).x)*timer_interval;
     (o->y)+=(((o->velocity)).y)*timer_interval;
     (o->z)+=(((o->velocity)).z)*timer_interval;
     return;
}
     
             
     
BOOL KillObject(int i){
     if(objects[i]!=NULL)
     {
             free(objects[i]);
             objects[i]=NULL;
             return TRUE;
     }
     return FALSE;
}

BOOL KillAll(){
     int i;
     for(i=0;i<MAX_OBJECTS;i++){
             KillObject(i);
     }
}


Object *AllocObject(unsigned double mass,double charge, int x, int y, int z, unsigned int xsize, unsigned int ysize, unsigned int zsize, double vx,double vy, double vz,double elasticity,ObjectType type){
       Object *o=(Object *)mallloc(sizeof(object));
       int i=0;
       if(o!=NULL){
                   for(;i<MAX_OBJECTS;i++){
                           if(objects[i]==NULL){
                                                objects[i]=o;
                                                goto success;
                           }
                   }
                   return NULL;
       success:
                   o->mass=mass;
                   o->charge=charge;
                   o->x=x;
                   o->y=y;
                   o->z=z;
                   o->xsize=xsize;
                   o->ysize=ysize;
                   o->zsize=zsize;
                   o->velocity.x=vx;
                   o->velocity.y=vy;
                   o->velocity.z=vz;
                   o->elasticity=elasticity;
                   o->type=type;
                   return o;
       }
       return NULL;
}
                   
       
