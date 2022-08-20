 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.c
 *
 * Description:  Det stores the development errors reported by other modules.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Det.h"
#include <assert.h>


/* Variables to store last DET error */
uint16 Det_ModuleId = 0;       /*DET module ID*/
uint8 Det_InstanceId = 0;      /*DET instance ID*/
uint8 Det_ApiId = 0;           /* DET API ID*/
uint8 Det_ErrorId = 0;         /* DET Error ID*/

Std_ReturnType Det_ReportError( uint16 ModuleId,
                      uint8 InstanceId,
                      uint8 ApiId,
                      uint8 ErrorId )
{


    return E_OK;
}
