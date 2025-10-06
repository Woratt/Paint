#ifndef TOOLFACTORY_H
#define TOOLFACTORY_H

#include "brokenlinetool.h"
#include "brushtool.h"
#include "buckettool.h"
#include "circletool.h"
#include "erasertool.h"
#include "idrawingtool.h"
#include "linetool.h"
#include "rectangletool.h"
#include "tooltypes.h"
#include <memory>

class ToolFactory
{
  public:
    static std::unique_ptr<IDrawingTool> createTool(ToolType type)
    {
        switch (type)
        {
            case ToolType::Brush:
                return std::make_unique<BrushTool>();
            case ToolType::Circle:
                return std::make_unique<CircleTool>();
            case ToolType::Rectangle:
                return std::make_unique<RectangleTool>();
            case ToolType::Eraser:
                return std::make_unique<EraserTool>();
            case ToolType::Line:
                return std::make_unique<LineTool>();
            case ToolType::Bucket:
                return std::make_unique<BucketTool>();
            case ToolType::BrokenLine:
                return std::make_unique<BrokenLineTool>();
        }
    }
};

#endif // TOOLFACTORY_H
