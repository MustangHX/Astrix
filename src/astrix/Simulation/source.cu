// -*-c++-*-
/*! \file source.cu
\brief File containing function to calculate source term contribution to residual.

\section LICENSE
Copyright (c) 2017 Sijme-Jan Paardekooper

This file is part of Astrix.

Astrix is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Astrix is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Astrix.  If not, see <http://www.gnu.org/licenses/>.*/

#include <iostream>

#include "../Common/definitions.h"
#include "../Array/array.h"
#include "../Mesh/mesh.h"
#include "./simulation.h"
#include "../Common/cudaLow.h"
#include "./Param/simulationparameter.h"

namespace astrix {

//######################################################################
//######################################################################

__host__ __device__
void CalcSourceSingle(int n, ProblemDefinition problemDef,
                      int nVertex, const int3 *pTv,
                      const real2 *pTn1, const real2 *pTn2, const real2 *pTn3,
                      const real3 *pTl, const real *pVp,
                      const real4 *pState, real4 *pSource)
{
  pSource[n].x = 0.0;
  pSource[n].y = 0.0;
  pSource[n].z = 0.0;
  pSource[n].w = 0.0;

  if (problemDef == PROBLEM_SOURCE) {
    real three = (real) 3.0;
    real half = (real) 0.5;

    // Vertices belonging to triangle
    int v1 = pTv[n].x;
    int v2 = pTv[n].y;
    int v3 = pTv[n].z;
    while (v1 >= nVertex) v1 -= nVertex;
    while (v2 >= nVertex) v2 -= nVertex;
    while (v3 >= nVertex) v3 -= nVertex;
    while (v1 < 0) v1 += nVertex;
    while (v2 < 0) v2 += nVertex;
    while (v3 < 0) v3 += nVertex;

    real tl1 = pTl[n].x;
    real tl2 = pTl[n].y;
    real tl3 = pTl[n].z;

    real d1 = pState[v1].x;
    real d2 = pState[v2].x;
    real d3 = pState[v3].x;
    real dG = (d1 + d2 + d3)/three;

    real m1 = pState[v1].y;
    real m2 = pState[v2].y;
    real m3 = pState[v3].y;
    real mG = (m1 + m2 + m3)/three;

    real n1 = pState[v1].z;
    real n2 = pState[v2].z;
    real n3 = pState[v3].z;
    real nG = (n1 + n2 + n3)/three;

    real dpotdx = half*
      (pVp[v1]*pTn1[n].x*tl1 +
       pVp[v2]*pTn2[n].x*tl2 +
       pVp[v3]*pTn3[n].x*tl3);
    real dpotdy = half*
      (pVp[v1]*pTn1[n].y*tl1 +
       pVp[v2]*pTn2[n].y*tl2 +
       pVp[v3]*pTn3[n].y*tl3);

    pSource[n].x = 0.0;
    pSource[n].y = dG*dpotdx;
    pSource[n].z = dG*dpotdy;
    pSource[n].w = mG*dpotdx + nG*dpotdy;
  }
}

__host__ __device__
void CalcSourceSingle(int n, ProblemDefinition problemDef,
                      int nVertex, const int3 *pTv,
                      const real2 *pTn1, const real2 *pTn2, const real2 *pTn3,
                      const real3 *pTl, const real *pVp,
                      const real3 *pState, real3 *pSource)
{
  pSource[n].x = 0.0;
  pSource[n].y = 0.0;
  pSource[n].z = 0.0;

  if (problemDef == PROBLEM_SOURCE) {
    real three = (real) 3.0;
    real half = (real) 0.5;

    // Vertices belonging to triangle
    int v1 = pTv[n].x;
    int v2 = pTv[n].y;
    int v3 = pTv[n].z;
    while (v1 >= nVertex) v1 -= nVertex;
    while (v2 >= nVertex) v2 -= nVertex;
    while (v3 >= nVertex) v3 -= nVertex;
    while (v1 < 0) v1 += nVertex;
    while (v2 < 0) v2 += nVertex;
    while (v3 < 0) v3 += nVertex;

    real tl1 = pTl[n].x;
    real tl2 = pTl[n].y;
    real tl3 = pTl[n].z;

    real d1 = pState[v1].x;
    real d2 = pState[v2].x;
    real d3 = pState[v3].x;
    real dG = (d1 + d2 + d3)/three;

    real dpotdx = half*
      (pVp[v1]*pTn1[n].x*tl1 +
       pVp[v2]*pTn2[n].x*tl2 +
       pVp[v3]*pTn3[n].x*tl3);
    real dpotdy = half*
      (pVp[v1]*pTn1[n].y*tl1 +
       pVp[v2]*pTn2[n].y*tl2 +
       pVp[v3]*pTn3[n].y*tl3);

    pSource[n].x = 0.0;
    pSource[n].y = dG*dpotdx;
    pSource[n].z = dG*dpotdy;
  }
}

__host__ __device__
void CalcSourceSingle(int n, ProblemDefinition problemDef,
                      int nVertex, const int3 *pTv,
                      const real2 *pTn1, const real2 *pTn2, const real2 *pTn3,
                      const real3 *pTl, const real *pVp,
                      const real *pState, real *pSource)
{
  pSource[n] = 0.0;

  if (problemDef == PROBLEM_SOURCE) {
    real three = (real) 3.0;

    // Vertices belonging to triangle
    int v1 = pTv[n].x;
    int v2 = pTv[n].y;
    int v3 = pTv[n].z;
    while (v1 >= nVertex) v1 -= nVertex;
    while (v2 >= nVertex) v2 -= nVertex;
    while (v3 >= nVertex) v3 -= nVertex;
    while (v1 < 0) v1 += nVertex;
    while (v2 < 0) v2 += nVertex;
    while (v3 < 0) v3 += nVertex;

    real tl1 = pTl[n].x;
    real tl2 = pTl[n].y;
    real tl3 = pTl[n].z;

    real d1 = pState[v1];
    real d2 = pState[v2];
    real d3 = pState[v3];
    real dG = (d1 + d2 + d3)/three;

    real s = (real) 0.5*(tl1 + tl2 + tl3);
    real area = sqrt(s*(s - tl1)*(s - tl2)*(s - tl3));

    pSource[n] = dG*area;
  }
}

//######################################################################
//######################################################################

__global__ void
devCalcSource(int nTriangle, ProblemDefinition problemDef,
              int nVertex, const int3 *pTv,
              const real2 *pTn1, const real2 *pTn2, const real2 *pTn3,
              const real3 *pTl, const real *pVp,
              const realNeq *pState, realNeq *pSource)
{
  // n = vertex number
  int n = blockIdx.x*blockDim.x + threadIdx.x;

  while (n < nTriangle) {
    CalcSourceSingle(n, problemDef, nVertex,
                     pTv, pTn1, pTn2, pTn3,
                     pTl, pVp, pState, pSource);

    n += blockDim.x*gridDim.x;
  }
}

//#########################################################################
//#########################################################################

void Simulation::CalcSource(Array<realNeq> *state)
{
  int nTriangle = mesh->GetNTriangle();
  int nVertex = mesh->GetNVertex();

  ProblemDefinition problemDef = simulationParameter->problemDef;

  const int3 *pTv = mesh->TriangleVerticesData();
  const real *pVp = vertexPotential->GetPointer();
  const realNeq *pState = state->GetPointer();
  realNeq *pSource = triangleResidueSource->GetPointer();

  const real2 *pTn1 = mesh->TriangleEdgeNormalsData(0);
  const real2 *pTn2 = mesh->TriangleEdgeNormalsData(1);
  const real2 *pTn3 = mesh->TriangleEdgeNormalsData(2);

  const real3 *pTl = mesh->TriangleEdgeLengthData();

  if (cudaFlag == 1) {
    int nBlocks = 128;
    int nThreads = 128;

    // Base nThreads and nBlocks on maximum occupancy
    cudaOccupancyMaxPotentialBlockSize(&nBlocks, &nThreads,
                                       devCalcSource,
                                       (size_t) 0, 0);

    devCalcSource<<<nBlocks, nThreads>>>
      (nTriangle, problemDef, nVertex,
       pTv, pTn1, pTn2, pTn3, pTl, pVp, pState, pSource);

    gpuErrchk( cudaPeekAtLastError() );
    gpuErrchk( cudaDeviceSynchronize() );
  } else {
    for (int i = 0; i < nTriangle; i++)
      CalcSourceSingle(i, problemDef, nVertex,
                       pTv, pTn1, pTn2, pTn3, pTl,
                       pVp, pState, pSource);
  }
}

}  // namespace astrix
