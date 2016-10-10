#pragma once
#ifndef _Integrators_c_interface_
#define _Integrators_c_interface_

#include "main.h"

#define MAX_STATE_SIZE 55 //It is hard embedded into code.
                          //Hence, only state size below this value are allowed

//Differentiation function type
typedef void (__cdecl * DFUN) (const void*, const double*, double*, const double*);

//Integrator types. Commented ones require more complex interface
enum STEPPER_TYPE_ID
    {
        BOOST_EXPLICIT_EULER          = 0,
        BOOST_MODIFIED_MIDPOINT       = 1,
        BOOST_RUNGE_KUTTA4            = 2,
        BOOST_RUNGE_KUTTA_CASH_KARP54 = 3,
        BOOST_RUNGE_KUTTA_DOPRI5      = 4,
        BOOST_RUNGE_KUTTA_FEHLBERG78  = 5,
        //BOOST_ADAMS_BASHFORTH         = 6,
        //BOOST_ADAMS_BASHFORTH_MOULTON = 7,
        //BOOST_ADAMS_MOULTON           = 8,
        RUNGE_KUTTA4                  = 9,
        RUNGE_KUTTA2                  = 10,
        UNSUPPORTED_TYPE              = 0xFF
    };

#ifdef __cplusplus
extern "C"
{
#endif
/*Exported functions:*/
    void* create_integrator_interface
    (
        unsigned long state_size,  //State is a contiguous vector of doubles in memory
        STEPPER_TYPE_ID stepper_id, //Stepper type
        const void* pObj,           //Object holds the model parameters, it should be
                                    //the first one parameter of a DFUN
        DFUN diff_fun               //Function returns derivatives of state variables:
                                    //diff_fun(pObj, state_pointer, dxdt_pointer, time)
    );

    void delete_integrator_interface(void* ptr_integrator_interface);

    void do_integrator_step
    (
        void* ptr_integrator_interface, //Pointer to an integrator created with
                                        //create_integrator_interface
        double* state,                  //State
        const double* time,             //time
        const double* dt                //numeric time-step
    );
#ifdef __cplusplus
}
#endif


#endif // _Integrators_c_interface_
