// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#ifndef INCLUDE_JET_GFX_PITCH_YAW_VIEW_CONTROLLER_H_
#define INCLUDE_JET_GFX_PITCH_YAW_VIEW_CONTROLLER_H_

#include <jet.gfx/view_controller.h>
#include <jet/constants.h>

namespace jet {
namespace gfx {

class PitchYawViewController : public ViewController {
 public:
    //!
    //! \brief Constructs pitch-yaw view controller.
    //!
    //! This constructor builds a pitch-yaw view controller with a camera and
    //! view controller's rotation origin. Because we need the origin of the
    //! rotation to define this view controller, which automatically defines the
    //! view direction, the look-at vector from the camera will be overriden.
    //! Also, since this controller only allows pitch and yaw, the look-up
    //! vector from the camera will also be overriden with calculated values
    //! internally.
    //!
    //! \param camera           Camera object
    //! \param rotationOrigin   Origin of the rotation of the view controller.
    //!
    PitchYawViewController(const CameraPtr& camera,
                           const Vector3F& rotationOrigin);
    virtual ~PitchYawViewController();

 protected:
    void onKeyDown(const KeyEvent& keyEvent) override;
    void onKeyUp(const KeyEvent& keyEvent) override;

    void onPointerPressed(const PointerEvent& pointerEvent) override;
    void onPointerHover(const PointerEvent& pointerEvent) override;
    void onPointerDragged(const PointerEvent& pointerEvent) override;
    void onPointerReleased(const PointerEvent& pointerEvent) override;
    void onMouseWheel(const PointerEvent& pointerEvent) override;

 private:
    Vector3F _origin;
    Vector3F _basisX = Vector3F(1, 0, 0);
    Vector3F _rotationAxis = Vector3F(0, 1, 0);
    Vector3F _basisZ = Vector3F(0, 0, 1);

    float _radialDistance = 1.0f;
    float _polarAngleInRadians = kHalfPiF;
    float _azimuthalAngleInRadians = 0.0f;

    float _rotateSpeed = 1.0f;
    float _zoomSpeed = 1.0f;
    float _panSpeed = 1.0f;

    void updateCamera();
};

typedef std::shared_ptr<PitchYawViewController> PitchYawViewControllerPtr;

}  // namespace gfx
}  // namespace jet

#endif  // INCLUDE_JET_GFX_PITCH_YAW_VIEW_CONTROLLER_H_