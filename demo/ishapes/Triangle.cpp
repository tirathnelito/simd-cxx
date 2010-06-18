/* 
 * File:   Triangle.cpp
 * Author: corsaro
 * 
 * Created on July 13, 2009, 1:57 AM
 */

#include <QtGui/qpainter.h>

#include "Triangle.hpp"

Triangle::Triangle(const QRect& bounds,
                   boost::shared_ptr<ShapeDynamics> dynamics,
                   const QPen& pen,
                   const QBrush& brush,
                   bool targeted)
    :   Shape(bounds, pen, brush, targeted),
        dynamics_(dynamics)
{
    QPoint p1(bounds_.width()/2, 0);
    QPoint p2(0, bounds_.width());
    QPoint p3(bounds_.width(), bounds_.width());

    triangle_ << p1 << p2 << p3;
}

Triangle::~Triangle() {
}

void 
Triangle::setBounds(const QRect& bounds)
{
  bounds_ = bounds;
  QPoint p1(bounds_.width()/2, 0);
  QPoint p2(0, bounds_.width());
  QPoint p3(bounds_.width(), bounds_.width());

  QPolygon triangle;
  triangle << p1 << p2 << p3;
  triangle_ = triangle;
}
void
Triangle::update() {
    dynamics_->simulate();
}

void
Triangle::paint(QPainter& painter) {
    painter.setBrush(brush_);
    painter.setPen(pen_);

    std::vector<QPoint> plist = dynamics_->getPositionList();
    std::vector<QPoint>::iterator idx = plist.begin();
    QBrush brush( QColor(0x33, 0x33, 0x33), Qt::SolidPattern);
    
    while (idx != plist.end()) {
      painter.translate(*idx);
      painter.drawPolygon(triangle_);
      painter.translate(-(idx->x()),
                        -(idx->y()));
      if (targeted_) {
        painter.setBrush(brush);
        int X0 = idx->x() + (bounds_.width()/2);
        int Y0 = idx->y() + 2*(bounds_.height()/3);
        int W = bounds_.width()/3;
        int H = bounds_.height()/3;
        painter.setBrush(brush);
        // painter.setPen(pen_);
        painter.drawEllipse(X0 -W/2,
                            Y0 - H/2,
                            W,
                            H);
                            painter.setBrush(brush_);
        painter.setBrush(brush_);
                            
      }

                        
      ++idx;
    }
}
