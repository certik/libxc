/*
 Copyright (C) 2006-2007 M.A.L. Marques

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.
  
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
  
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"

#define XC_GGA_K_GE2          200 /* Second-order gradient expansion */

static inline void 
func(const XC(gga_type) *p, int order, FLOAT x, 
     FLOAT *f, FLOAT *dfdx, FLOAT *ldfdx, FLOAT *d2fdx2)
{
  *f = 1.0 + x*x/(72.0*K_FACTOR_C);

  if(order < 1) return;

  *dfdx = 2.0*x/(72.0*K_FACTOR_C);
  *ldfdx= 1.0  /(72.0*K_FACTOR_C);
  
  if(order < 2) return;

  *d2fdx2 = 2.0/(72.0*K_FACTOR_C);
}

#define XC_KINETIC_FUNCTIONAL
#include "work_gga_x.c"

const XC(func_info_type) XC(func_info_gga_k_ge2) = {
  XC_GGA_K_GE2,
  XC_KINETIC,
  "Second-order gradient expansion of the kinetic energy density",
  XC_FAMILY_GGA,
  "CH Hodges, Can. J. Phys. 51, 1428 (1973)",
  XC_FLAGS_3D | XC_FLAGS_HAVE_EXC | XC_FLAGS_HAVE_VXC | XC_FLAGS_HAVE_FXC,
  NULL, NULL, NULL,
  work_gga_x
};
