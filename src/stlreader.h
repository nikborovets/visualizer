#ifndef STLREADER_H
#define STLREADER_H

#include <vector>
#include <string>
#include <vtkSmartPointer.h>
#include <vtkActor.h>

std::vector<std::string> getSTLFiles(const std::string& directory);
std::vector<vtkSmartPointer<vtkActor>> LoadSTLFiles(const std::vector<std::string>& stl_files);

#endif // STLREADER_H
