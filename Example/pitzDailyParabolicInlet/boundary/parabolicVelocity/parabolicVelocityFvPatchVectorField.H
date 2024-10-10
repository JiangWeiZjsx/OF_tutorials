/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2024 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::parabolicVelocityFvPatchVectorField

Description
    Boundary condition specifies a parabolic velocity inlet profile 
    (fixed value), given maximum velocity value (peak of the parabola), 
    flow direction n and direction of the parabolic coordinate y
SourceFiles
    parabolicVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef BC_H
#define BC_H

#include "fixedValueFvPatchFields.H"
#include "Function1.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
     Class parabolicVelocityFvPatchVectorField Declaration
\*---------------------------------------------------------------------------*/

class parabolicVelocityFvPatchVectorField
:
    public fixedValueFvPatchVectorField
{
    // Private Data
	//- Peak velocity magnitude
        scalar maxValue_;

        //- Flow direction
        vector n_;
       
       	//- Direction of the y-coordinate
        vector y_;

public:

    //- Runtime type information
    TypeName("parabolicVelocity");
    // Constructors

        //- Construct from patch and internal field
        parabolicVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        parabolicVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given fixedValueTypeFvPatchField
        //  onto a new patch
        parabolicVelocityFvPatchVectorField
        (
            const parabolicVelocityFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

	//- Copy constructor
        parabolicVelocityFvPatchVectorField
        (
            const parabolicVelocityFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
            (
                new parabolicVelocityFvPatchVectorField(*this)
            );
        }

	//- Copy constructor setting internal field reference
	parabolicVelocityFvPatchVectorField
        (
	    const parabolicVelocityFvPatchVectorField&,
	    const DimensionedField<vector, volMesh>&
	); 
	
	//- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchVectorField> clone
        (
            const DimensionedField<vector, volMesh>& iF
        ) const
        {
            return tmp<fvPatchVectorField>
            (
                new parabolicVelocityFvPatchVectorField
                (
                    *this,
                    iF
                )
            );
        }



    // Member Functions
        // return max value
        scalar& maxValue()
        {
    	    return maxValue_;
        }

        //return flow direction
	vector& n()
	{
	    return n_;
	}

	//return y direction
	vector& y()
	{
	    return y_;
	}

	// Evaluation functions

            //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();


        //- Write
        virtual void write(Ostream&) const;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif

// ************************************************************************* //
