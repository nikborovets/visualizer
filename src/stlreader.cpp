#include "stlreader.h"
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtksys/SystemTools.hxx>
#include <filesystem>
#include <omp.h>
#include <chrono>
#include <algorithm>

namespace fs = std::filesystem;

std::vector<std::string> getSTLFiles(const std::string& directory) {
    std::vector<std::string> stl_files;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string ext = vtksys::SystemTools::GetFilenameExtension(entry.path().string());
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if (ext == ".stl") {
                stl_files.push_back(entry.path().string());
            }
        }
    }
    return stl_files;
}

std::vector<vtkSmartPointer<vtkActor>> LoadSTLFiles(const std::vector<std::string>& stl_files) {
    std::vector<vtkSmartPointer<vtkActor>> actors(stl_files.size());

    #pragma omp parallel for
    for (size_t i = 0; i < stl_files.size(); ++i) {
        auto read_start_time = std::chrono::high_resolution_clock::now();
        vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
        reader->SetFileName(stl_files[i].c_str());

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(reader->GetOutputPort());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);

        actors[i] = actor;
        auto read_end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> read_duration = read_end_time - read_start_time;
        // std::cout << "Time taken to read STL file " << stl_files[i] << ": " << read_duration.count() << " seconds." << std::endl;
    }

    return actors;
}
