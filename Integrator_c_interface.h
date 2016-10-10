#pragma once
#ifndef _Integrators_c_interface_
#define _Integrators_c_interface_

#include "main.h"
#include "Integrators.h"

#define MAX_STATE_SIZE 55 //It is hard embedded into code

#ifdef __cplusplus
extern "C"
{
#endif

    DLL_EXPORT void* create_integrator_interface
    (
        unsigned long state_size,
        math::STEPPER_TYPE_ID stepper_id,
        const void* pObj,
        void (__cdecl *diff_fun)(const void*, const double*, double*, const double*)
    );

    DLL_EXPORT void delete_integrator_interface(void* ptr_integrator_interface);

    DLL_EXPORT void do_integrator_step
    (
        void* ptr_integrator_interface,
        double* state,
        const double* time,
        const double* dt
    );
#ifdef __cplusplus
}
#endif


#endif // _Integrators_c_interface_
