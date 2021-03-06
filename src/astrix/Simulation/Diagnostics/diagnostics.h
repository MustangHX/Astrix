/*! \file diagnostics.h
\brief Header file for Diagnostics class

\section LICENSE
Copyright (c) 2017 Sijme-Jan Paardekooper

This file is part of Astrix.

Astrix is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Astrix is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Astrix.  If not, see <http://www.gnu.org/licenses/>.*/
#ifndef ASTRIX_DIAGNOSTICS_H
#define ASTRIX_DIAGNOSTICS_H

namespace astrix {

template <class T> class Array;
class Mesh;

template <class T, ConservationLaw CL> class Diagnostics
{
 public:
  //! Constructor for Diagnostics object.
  Diagnostics(Array<T> *state, Array<real> *pot, Mesh *mesh);
  //! Destructor
  ~Diagnostics();

  Array<real> *result;

 private:
  real TotalMass(Array<T> *state, Mesh *mesh);
  real KineticEnergy(Array<T> *state, Mesh *mesh);
  real ThermalEnergy(Array<T> *state, Array<real> *pot, Mesh *mesh);
  real TotalEnergy(Array<T> *state, Mesh *mesh);
};

}  // namespace astrix

#endif  // ASTRIX_DIAGNOSTICS_H
