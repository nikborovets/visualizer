#include "renderer.h"

vtkSmartPointer<vtkRenderer> CreateRenderer(const std::vector<vtkSmartPointer<vtkActor>>& actors) {
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    double xOffset = 0.0;
    for (auto& actor : actors) {
        actor->AddPosition(xOffset, 0, 0);
        renderer->AddActor(actor);
        xOffset += 100.0;
    }

    renderer->SetBackground(0.1, 0.2, 0.4);
    return renderer;
}
