#include "stlreader.h"
#include "renderer.h"
#include "interactor_style.h"

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <iostream>
#include <chrono>

int main(int argc, char* argv[]) {
    std::string directory = (argc > 1) ? argv[1] : "../models";

    auto start_overall_time = std::chrono::high_resolution_clock::now();
    std::vector<std::string> stl_files = getSTLFiles(directory);

    if (stl_files.empty()) {
        std::cerr << "No STL files found in the directory: " << directory << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<vtkSmartPointer<vtkActor>> actors = LoadSTLFiles(stl_files);

    vtkSmartPointer<vtkRenderer> renderer = CreateRenderer(actors);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<InteractorStyle> style = vtkSmartPointer<InteractorStyle>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    style->SetActors(actors);

    renderWindow->Render();
    auto read_end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> read_duration = read_end_time - start_overall_time;
    std::cout << "Time taken to read STL file: " << read_duration.count() << " seconds." << std::endl;
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;    
}
