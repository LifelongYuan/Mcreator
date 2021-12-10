#ifndef CCAMERA_H
#define CCAMERA_H

#include<QOpenGLFunctions>
#include<QPoint>
class CCamera
{
public:
    void UpdateDistance(const short &zDelta);
    void UpdateAngle(const QPoint &MousePoint);
    void SetMouseDownPoint(const QPoint &ptMouseDown);
    void UpdateView(int n = 0);
    void ResetCamera();
    CCamera();
    virtual ~CCamera();

private:
    QPoint m_ptMouseDown;
    GLdouble m_zPos;
    GLdouble m_yAngle;
    GLdouble m_xAngle;
};

#endif // CCAMERA_H

