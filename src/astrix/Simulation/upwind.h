/*! \file upwind.h
\brief Upwind matrix entries

\section LICENSE
Copyright (c) 2017 Sijme-Jan Paardekooper

This file is part of Astrix.

Astrix is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Astrix is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Astrix.  If not, see <http://www.gnu.org/licenses/>.*/
#ifndef ASTRIX_UPWIND_H
#define ASTRIX_UPWIND_H

namespace astrix {

//###########################################################################
// 2D isothermal
//###########################################################################

__host__ __device__ inline real
isoK00()
{
  return 0.0;
}

__host__ __device__ inline real
isoK01(real nx)
{
  return nx;
}

__host__ __device__ inline real
isoK02(real ny)
{
  return ny;
}

__host__ __device__ inline real
isoK10(real nx, real c, real w, real u)
{
  return c*c*nx - w*u;
}

__host__ __device__ inline real
isoK11(real nx, real w, real u)
{
  return w + u*nx;
}

__host__ __device__ inline real
isoK12(real ny, real u)
{
  return u*ny;
}

__host__ __device__ inline real
isoK20(real ny, real c, real w, real v)
{
  return c*c*ny - w*v;
}

__host__ __device__ inline real
isoK21(real nx, real v)
{
  return v*nx;
}

__host__ __device__ inline real
isoK22(real ny, real w, real v)
{
  return w + v*ny;
}

//#############################################################################

__host__ __device__ inline real
isoKMP00(real ic, real w, real l12, real l2)
{
  return ((real)1.0 - w*ic)*l12 + l2;
}

__host__ __device__ inline real
isoKMP01(real nx, real ic, real l12)
{
  return ic*nx*l12;
}

__host__ __device__ inline real
isoKMP02(real ny, real ic, real l12)
{
  return ic*ny*l12;
}

__host__ __device__ inline real
isoKMP10(real nx, real c, real uc, real w, real l123, real l12)
{
  return c*(uc*l123 + nx*l12) - w*(nx*l123 + uc*l12);
}

__host__ __device__ inline real
isoKMP11(real nx, real uc, real l123, real l12, real l3)
{
  return l3 + Sq(nx)*l123 + uc*nx*l12;
}

__host__ __device__ inline real
isoKMP12(real nx, real ny, real uc, real l123, real l12)
{
  return uc*ny*l12 + nx*ny*l123;
}

__host__ __device__ inline real
isoKMP20(real ny, real c, real vc, real w, real l123, real l12)
{
  return c*(vc*l123 + ny*l12) - w*(vc*l12 + ny*l123);
}

__host__ __device__ inline real
isoKMP21(real nx, real ny, real vc, real l123, real l12)
{
  return vc*nx*l12 + nx*ny*l123;
}

__host__ __device__ inline real
isoKMP22(real ny, real vc, real l123, real l12, real l3)
{
  return Sq(ny)*l123 + l3 + vc*ny*l12;
}

//###########################################################################
// 2D Euler
//###########################################################################

__host__ __device__ inline real
eulerK00()
{
  return 0.0;
}

__host__ __device__ inline real
eulerK01(real nx)
{
  return nx;
}

__host__ __device__ inline real
eulerK02(real ny)
{
  return ny;
}

__host__ __device__ inline real
eulerK03()
{
  return 0.0;
}

__host__ __device__ inline real
eulerK10(real nx, real a, real w, real u)
{
  return a*nx - w*u;
}

__host__ __device__ inline real
eulerK11(real G2, real nx, real w, real u)
{
  return w - u*nx*G2;
}

__host__ __device__ inline real
eulerK12(real G1, real nx, real ny, real u, real v)
{
  return u*ny - v*G1*nx;
}

__host__ __device__ inline real
eulerK13(real G1, real nx)
{
  return G1*nx;
}

__host__ __device__ inline real
eulerK20(real ny, real a, real w, real v)
{
  return a*ny - w*v;
}

__host__ __device__ inline real
eulerK21(real G1, real nx, real ny, real u, real v)
{
  return v*nx - G1*u*ny;
}

__host__ __device__ inline real
eulerK22(real G2, real ny, real w, real v)
{
  return w - v*G2*ny;
}

__host__ __device__ inline real
eulerK23(real G1, real ny)
{
  return G1*ny;
}

__host__ __device__ inline real
eulerK30(real a, real h, real w)
{
  return a*w - w*h;
}

__host__ __device__ inline real
eulerK31(real G1, real nx, real h, real w, real u)
{
  return nx*h - G1*u*w;
}

__host__ __device__ inline real
eulerK32(real G1, real ny, real h, real w, real v)
{
  return ny*h - G1*v*w;
}

__host__ __device__ inline real
eulerK33(real G, real w)
{
  return G*w;
}

//#############################################################################

__host__ __device__ inline real
eulerKMP00(real ac, real ic, real w, real l123, real l12, real l3)
{
  return ac*ic*l123 + l3 - l12*w*ic;
}

__host__ __device__ inline real
eulerKMP01(real G1, real nx, real ic, real uc, real l123, real l12)
{
  return ic*(nx*l12 - G1*uc*l123);
}

__host__ __device__ inline real
eulerKMP02(real G1, real ny, real ic, real vc, real l123, real l12)
{
  return ic*(ny*l12 - G1*vc*l123);
}

__host__ __device__ inline real
eulerKMP03(real G1, real ic, real l123)
{
  return G1*l123*ic*ic;
}

__host__ __device__ inline real
eulerKMP10(real nx, real ac, real uc, real w, real l123, real l12)
{
  return ac*(uc*l123 + nx*l12) - w*(nx*l123 + uc*l12);
}

__host__ __device__ inline real
eulerKMP11(real G1, real G2, real nx, real uc, real l123, real l12, real l3)
{
  return l3 + Sq(nx)*l123 - uc*(nx*G2*l12 + G1*uc*l123);
}

__host__ __device__ inline real
eulerKMP12(real G1, real nx, real ny, real uc, real vc, real l123, real l12)
{
  return uc*ny*l12 + nx*ny*l123 - vc*G1*(nx*l12 + uc*l123);
}

__host__ __device__ inline real
eulerKMP13(real G1, real nx, real ic, real uc, real l123, real l12)
{
  return G1*(uc*l123 + nx*l12)*ic;
}

__host__ __device__ inline real
eulerKMP20(real ny, real ac, real vc, real w, real l123, real l12)
{
  return ac*(vc*l123 + ny*l12) - w*(vc*l12 + ny*l123);
}

__host__ __device__ inline real
eulerKMP21(real G1, real nx, real ny, real uc, real vc, real l123, real l12)
{
  return vc*nx*l12 - G1*uc*(vc*l123 + ny*l12) + nx*ny*l123;
}

__host__ __device__ inline real
eulerKMP22(real G1, real G2, real ny, real vc, real l123, real l12, real l3)
{
  return Sq(ny)*l123 + l3 - vc*(G2*ny*l12 + G1*vc*l123);
}

__host__ __device__ inline real
eulerKMP23(real G1, real ny, real ic, real vc, real l123, real l12)
{
  return G1*(vc*l123 + ny*l12)*ic;
}

__host__ __device__ inline real
eulerKMP30(real ac, real hc, real w, real l123, real l12)
{
  return ac*(w*l12 + hc*l123) - w*(hc*l12 + w*l123);
}

__host__ __device__ inline real
eulerKMP31(real G1, real nx, real hc, real uc, real w, real l123, real l12)
{
  return nx*(hc*l12 + w*l123) - G1*uc*(w*l12 + hc*l123);
}

__host__ __device__ inline real
eulerKMP32(real G1, real ny, real hc, real vc, real w, real l123, real l12)
{
  return ny*(hc*l12 + w*l123) - G1*vc*(w*l12 + hc*l123);
}

__host__ __device__ inline real
eulerKMP33(real G1, real ic, real hc, real w, real l123, real l12, real l3)
{
  return G1*ic*(hc*l123 + w*l12) + l3;
}

}  // namespace astrix

#endif  // ASTRIX_UPWIND_H
