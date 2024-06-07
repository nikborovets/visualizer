#include "scene_manager.h"
#include <vtkProperty.h>
#include <fstream>
#include <iostream>

void SceneManager::SaveScene(const std::vector<vtkSmartPointer<vtkActor>>& actors, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& actor : actors) {
        double* position = actor->GetPosition();
        double* color = actor->GetProperty()->GetColor();
        file << position[0] << " " << position[1] << " " << position[2] << " "
             << color[0] << " " << color[1] << " " << color[2] << std::endl;
    }
    file.close();
    std::cout << "Scene saved to " << filename << std::endl;
}

std::vector<vtkSmartPointer<vtkActor>> SceneManager::LoadScene(const std::string& filename) {
    std::vector<vtkSmartPointer<vtkActor>> actors;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return actors;
    }

    double x, y, z, r, g, b;
    while (file >> x >> y >> z >> r >> g >> b) {
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetPosition(x, y, z);
        actor->GetProperty()->SetColor(r, g, b);
        actors.push_back(actor);
    }
    file.close();
    std::cout << "Scene loaded from " << filename << std::endl;

    return actors;
}
