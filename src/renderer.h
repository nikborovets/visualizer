#ifndef RENDERER_H
#define RENDERER_H

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vector>

vtkSmartPointer<vtkRenderer> CreateRenderer(const std::vector<vtkSmartPointer<vtkActor>>& actors);

#endif // RENDERER_H
