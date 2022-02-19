Info<< "Reading field T\n" << endl;

volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


Info<< "Reading diffusivity DT\n" << endl;

volScalarField DT
(
    IOobject
    (
        "DT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimViscosity, Zero)
);

if (!DT.headerOk())
{
    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );
    DT = dimensionedScalar("DT", dimViscosity, transportProperties);
}

#include "createFvOptions.H"






   const scalar pi(M_PI);
   Info << "pi = " << pi << endl;

   forAll(T, cellI)
   {
     T[cellI] = Foam::sin(pi*0.5*(T.mesh().C()[cellI] & vector(0,1,0)));
   };


   forAll(T.boundaryField(), patchI)
   {
        forAll(T.boundaryField()[patchI], faceI)
        {
          T.boundaryFieldRef()[patchI][faceI] = Foam::sin(pi*0.5*(T.mesh().Cf().boundaryField()[patchI][faceI] & vector(0,1,0)));
        }
   };
