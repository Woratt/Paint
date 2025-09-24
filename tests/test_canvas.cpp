#include <gtest/gtest.h>
#include <QPinchGesture>
#include <iostream>
#include <QImage>
#define private public
#define protected public
#include "../canvas.h"
#include "../toolbar.h"
#undef private
#undef protected



struct CanvasFixture : public testing::Test{
    QImage* image;
    Canvas* canvas;

    void SetUp() override {
        image = new QImage(200, 200, QImage::Format_RGB32);
        image->fill(Qt::white);
        canvas = new Canvas(*image);
    }
};

// Test constructor
TEST_F(CanvasFixture, constructor){
    ASSERT_EQ(canvas->takePixmap().size(), image->size());
    ASSERT_EQ(canvas->takePixmap().toImage().format(), image->format());
    ASSERT_EQ(Canvas::history.size(), 1);
    ASSERT_EQ(Canvas::history[0].size(), image->size());

    QSize const scaledSize = canvas->pixMap.size() * canvas->zoom;
    ASSERT_EQ(canvas->offset, QPointF((canvas->width() - scaledSize.width()) / 2,
                                (canvas->height() - scaledSize.height()) / 2));
    ASSERT_EQ(canvas->pen.width(), 3);
    ASSERT_EQ(canvas->pen.color(), Qt::black);
    EXPECT_EQ(canvas->pen.capStyle(), Qt::RoundCap);
    EXPECT_EQ(canvas->pen.joinStyle(), Qt::RoundJoin);
}

// Test function increaseZoom
TEST_F(CanvasFixture, increaseZoom){

    canvas->increaseZoom();

    ASSERT_EQ(canvas->zoom, 1.1);
}

// Test function reduceZoom
TEST_F(CanvasFixture, reduceZoom){

    canvas->reduceZoom();

    ASSERT_EQ(canvas->zoom, 0.9);
}

// Test function setTool
TEST_F(CanvasFixture, setTool){
    Tool tool = Tool::Brush;

    canvas->setTool(tool);

    ASSERT_EQ(canvas->tool, tool);
}

// Test function changedWidth
TEST_F(CanvasFixture, changedWidth){
    int width = 5;
    canvas->changedWidth(width);

    ASSERT_EQ(canvas->pen.width(), width);

    width = 10;
    canvas->changedWidth(width);

    ASSERT_EQ(canvas->pen.width(), width);
}

// Test mouse press end start drawing
TEST_F(CanvasFixture, MousePressStartDrawing){
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(50, 50),      
        QPointF(50, 50),       
        QPointF(50, 50),       
        Qt::LeftButton,        
        Qt::LeftButton,       
        Qt::NoModifier        
    );
    
    canvas->setTool(Tool::Brush);
    canvas->mousePressEvent(&event);

    EXPECT_TRUE(canvas->draw);
    EXPECT_EQ(canvas->lastPoint, canvas->eventPosToImagePoint(QPoint(50, 50)));
    EXPECT_EQ(canvas->lastPoint, canvas->secondPoint);
}

// Test mouse move event
TEST_F(CanvasFixture, mouseMoveEvent){
    canvas->draw = true;
    canvas->setTool(Tool::Brush);
    canvas->lastPoint = QPoint(100, 100);

    QMouseEvent event(QEvent::MouseMove,
        QPointF(150, 150),       
        QPointF(150, 150),     
        QPointF(150, 150), 
        Qt::NoButton,           
        Qt::LeftButton,         
        Qt::NoModifier 
    );

    canvas->mouseMoveEvent(&event);

    QImage renderedImage = canvas->takePixmap().toImage();
    QColor startPos = renderedImage.pixelColor(canvas->eventPosToImagePoint(canvas->lastPoint));
    EXPECT_EQ(startPos, Qt::black);
    QColor lastPos = renderedImage.pixelColor(canvas->eventPosToImagePoint(canvas->secondPoint));
    EXPECT_EQ(lastPos, Qt::black);
    QColor averagePos = renderedImage.pixelColor(canvas->eventPosToImagePoint(QPoint(125, 125)));
    EXPECT_EQ(averagePos, Qt::black);

    canvas->setTool(Tool::Circle);

    canvas->mouseMoveEvent(&event);

    EXPECT_EQ(canvas->lastPoint, canvas->secondPoint);
}

// Test mouse release event
TEST_F(CanvasFixture, mouseReleaseEvent){
    canvas->draw = true;
    canvas->setTool(Tool::Circle);
    canvas->lastPoint = QPoint(100, 100);
    canvas->secondPoint = QPoint(150, 150);

    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(150, 150),  
        QPointF(150, 150),  
        QPointF(150, 150),
        Qt::LeftButton,     
        Qt::LeftButton,     
        Qt::NoModifier      
    );

    canvas->mouseReleaseEvent(&event);

    EXPECT_FALSE(canvas->draw);
    QImage renderedImage = canvas->takePixmap().toImage();
    QColor posPixRight = renderedImage.pixelColor(QPoint(150, 125));
    QColor posPixLeft = renderedImage.pixelColor(QPoint(100, 125));
    QColor posPixBottom = renderedImage.pixelColor(QPoint(125, 150));
    QColor posPixTop = renderedImage.pixelColor(QPoint(125, 100));

    EXPECT_EQ(posPixRight, Qt::black);
    EXPECT_EQ(posPixLeft, Qt::black);
    EXPECT_EQ(posPixBottom, Qt::black);
    EXPECT_EQ(posPixTop, Qt::black);
}

// Test wheel event
TEST_F(CanvasFixture, WheelEventZoomOffsets) {
    canvas->zoom = 1.0;
    QPointF oldOffset = canvas->offset;

    QWheelEvent wheelEventUp(
        QPointF(100, 100),         
        QPointF(100, 100),         
        QPoint(0, 0),              
        QPoint(0, 120),          
        Qt::NoButton,       
        Qt::NoModifier,            
        Qt::ScrollPhase::ScrollUpdate,
        false,                     
        Qt::MouseEventSource::MouseEventNotSynthesized 
    );

    canvas->wheelEvent(&wheelEventUp);

    EXPECT_LE(canvas->offset.y(), oldOffset.y());

    QWheelEvent wheelEventDown(
        QPointF(100, 100),
        QPointF(100, 100),
        QPoint(0, 0),
        QPoint(0, -120),
        Qt::NoButton,
        Qt::NoModifier,
        Qt::ScrollPhase::ScrollUpdate,
        false,
        Qt::MouseEventSource::MouseEventNotSynthesized
    );

    canvas->wheelEvent(&wheelEventDown);

    EXPECT_GE(canvas->offset.y(), oldOffset.y());
}

// Checking the transformation of a position from an event position to an image point
TEST_F(CanvasFixture, eventPosToImagePoint){
    canvas->zoom = 1.0;
    canvas->offset = QPointF(0, 0);

    QPoint widgetPoint(50, 100);
    QPoint imgPoint = canvas->eventPosToImagePoint(widgetPoint);

    EXPECT_EQ(imgPoint, QPoint(50, 100));

    canvas->zoom = 2.0;
    imgPoint = canvas->eventPosToImagePoint(QPoint(100, 100));
    EXPECT_EQ(imgPoint, QPoint(50, 50));

    canvas->zoom = 1.0;
    canvas->offset = QPointF(10, 20);
    imgPoint = canvas->eventPosToImagePoint(QPoint(30, 50));
    EXPECT_EQ(imgPoint, QPoint(20, 30));

    canvas->offset = QPointF(0, 0);
    imgPoint = canvas->eventPosToImagePoint(QPoint(-100, -100));
    EXPECT_EQ(imgPoint, QPoint(0, 0));

    imgPoint = canvas->eventPosToImagePoint(QPoint(9999, 9999));
    EXPECT_EQ(imgPoint.x(), canvas->takePixmap().width() - 1);
    EXPECT_EQ(imgPoint.y(), canvas->takePixmap().height() - 1);
}

// test pinch zoom
TEST_F(CanvasFixture, pinchTriggered){
    QPinchGesture pinch;
    pinch.setScaleFactor(1.2);
    pinch.setCenterPoint(QPointF(400, 400));
    float oldZoom = canvas->zoom;

    canvas->pinchTriggered(&pinch);
    EXPECT_GT(canvas->zoom, oldZoom);

    pinch.setScaleFactor(0.8);
    oldZoom = canvas->zoom;
    canvas->pinchTriggered(&pinch);
    EXPECT_LT(canvas->zoom, oldZoom);

    canvas->zoom = 20.0;
    pinch.setScaleFactor(2.0);
    canvas->pinchTriggered(&pinch);
    EXPECT_LE(canvas->zoom, 10.0);

    canvas->zoom = 0.01;
    pinch.setScaleFactor(0.5);
    canvas->pinchTriggered(&pinch);
    EXPECT_GE(canvas->zoom, 0.1);
}

// Image smaller than canvas_CentersImage
TEST_F(CanvasFixture, ImageSmallerThanCanvas_CentersImage) {
    QPixmap smallPixmap(100, 100);
    smallPixmap.fill(Qt::red);
    canvas->pixMap = smallPixmap;
    canvas->zoom = 1.0; 
    
    canvas->offset = QPointF(0, 0);
    
    canvas->clampOffset();
    
    QSize scaledSize = canvas->pixMap.size() * canvas->zoom;
    int expectedX = (canvas->width() - scaledSize.width()) / 2;
    int expectedY = (canvas->height() - scaledSize.height()) / 2;
    
    EXPECT_EQ(canvas->offset.x(), expectedX);
    EXPECT_EQ(canvas->offset.y(), expectedY);
}

// --- Image larger than canvas (constraint) ---
TEST_F(CanvasFixture, ImageLargerThanCanvas_ClampsToBounds) {
    QPixmap largePixmap(800, 800);
    largePixmap.fill(Qt::blue);
    canvas->pixMap = largePixmap;
    canvas->zoom = 1.0;
    
    canvas->offset = QPointF(-1000, -1000);
    
    canvas->clampOffset();
    
    QSize scaledSize = canvas->pixMap.size() * canvas->zoom;
    int minX = canvas->width() - scaledSize.width(); 
    int minY = canvas->height() - scaledSize.height(); 
    
    EXPECT_EQ(canvas->offset.x(), minX);
    EXPECT_EQ(canvas->offset.y(), minY);
}

// --- Offset within acceptable limits (does not change) ---
TEST_F(CanvasFixture, OffsetWithinBounds_NoChange) {
    QPixmap pixmap(800, 800); 
    canvas->pixMap = pixmap;
    canvas->zoom = 1.0;
    
    QSize scaledSize = canvas->pixMap.size() * canvas->zoom;
    int validX = (canvas->width() - scaledSize.width()) / 2; 
    int validY = (canvas->height() - scaledSize.height()) / 2; 
    
    canvas->offset = QPointF(validX, validY);
    
    canvas->clampOffset();
    
    EXPECT_EQ(canvas->offset.x(), validX);
    EXPECT_EQ(canvas->offset.y(), validY);
}

// --- Effect of zoom on centering ---
TEST_F(CanvasFixture, ZoomAffectsCentering) {
    QPixmap pixmap(800, 800);
    canvas->pixMap = pixmap;
    
    canvas->zoom = 0.5; 
    canvas->offset = QPointF(0, 0);
    canvas->clampOffset();
    
    QSize scaledSizeSmall = canvas->pixMap.size() * canvas->zoom;
    int expectedXSmall = (canvas->width() - scaledSizeSmall.width()) / 2;
    EXPECT_EQ(canvas->offset.x(), expectedXSmall);
    
    canvas->zoom = 2.0;
    canvas->offset = QPointF(0, 0);
    canvas->clampOffset();
    
    EXPECT_EQ(canvas->offset.x(), 0); 
}

// --- Boundary cases ---
TEST_F(CanvasFixture, EdgeCases) {
    QPixmap pixmap(720, 720);
    canvas->pixMap = pixmap;
    canvas->zoom = 1.0;
    
    canvas->clampOffset();
    
    EXPECT_EQ(canvas->offset.x(), 0);
    EXPECT_EQ(canvas->offset.y(), 0);
}

// --- Positive offset values (too far to the right/bottom) ---
TEST_F(CanvasFixture, PositiveOffsetClamped) {
    QPixmap pixmap(500, 400);
    canvas->pixMap = pixmap;
    canvas->zoom = 1.0;
    
    canvas->offset = QPointF(1000, 1000);
    
    canvas->clampOffset();
    
    EXPECT_EQ(canvas->offset.x(), 110);
    EXPECT_EQ(canvas->offset.y(), 160);
}

// --- Partial centering (only along one axis) ---
TEST_F(CanvasFixture, PartialCentering) {
    QPixmap pixmap(300, 800);
    canvas->pixMap = pixmap;
    canvas->zoom = 1.0;
    
    canvas->offset = QPointF(-50, -80);
    canvas->clampOffset();
    
    QSize scaledSize = canvas->pixMap.size() * canvas->zoom;
    
    int expectedX = (canvas->width() - scaledSize.width()) / 2;
    
    int minY = canvas->height() - scaledSize.height();
    
    EXPECT_EQ(canvas->offset.x(), expectedX);
    EXPECT_EQ(canvas->offset.y(), minY);
}

// --- Blank image ---
TEST_F(CanvasFixture, EmptyImage) {
    canvas->pixMap = QPixmap(); 
    canvas->zoom = 1.0;
    canvas->offset = QPointF(100, 100);
    
    EXPECT_NO_THROW(canvas->clampOffset());
    
    EXPECT_EQ(canvas->offset.x(), (canvas->width() - 0) / 2);
    EXPECT_EQ(canvas->offset.y(), (canvas->height() - 0) / 2);
}