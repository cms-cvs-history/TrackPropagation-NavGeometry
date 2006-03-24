#ifndef NavPlane_H
#define NavPlane_H

#include "Geometry/Surface/interface/Plane.h"
#include "TrackPropagation/NavGeometry/interface/NavSurface.h"
#include "TrackPropagation/NavGeometry/interface/LinearSearchNavSurfaceImpl.h"
#include "Geometry/Surface/interface/ReferenceCounted.h"

#include <vector>
class Bounds;

class NavPlane : public NavSurface {
public:

/*     NavPlane( const PositionType& pos, const RotationType& rot) : */
/* 	Surface( pos, rot), Plane( pos, rot), NavSurface( pos, rot) {} */

    NavPlane( const Plane* plane) : theSurfaceP(plane) {}

    // FIXME: restore covariant return type when gcc version upgraded
    //virtual const Plane& surface() const {return *theSurfaceP;} 
    virtual const Surface& surface() const {return *theSurfaceP;} 

    virtual const NavVolume* nextVolume( const NavSurface::LocalPoint& point, 
					 SurfaceOrientation::Side side) const{
	return theImpl.nextVolume( point,side);
    }

    virtual TrajectoryStateOnSurface 
    propagate( const Propagator& prop, const TrajectoryStateOnSurface& startingState) const;

    virtual const Bounds* bounds( const NavVolume* vol) { return theImpl.bounds(vol);}

    virtual void addVolume( const NavVolume* vol, const Bounds* bounds, 
			    SurfaceOrientation::Side side) {
	theImpl.addVolume( vol, bounds, side);
    }

    virtual std::pair<bool,double> 
    distanceAlongLine( const NavSurface::GlobalPoint& pos, const NavSurface::GlobalVector& dir) const;

private:

  ConstReferenceCountingPointer<Plane> theSurfaceP;
  LinearSearchNavSurfaceImpl theImpl;

};

#endif
