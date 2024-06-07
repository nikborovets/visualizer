#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vector>
#include <string>

class SceneManager {
public:
    SceneManager() = default;
    ~SceneManager() = default;

    void SaveScene(const std::vector<vtkSmartPointer<vtkActor>>& actors, const std::string& filename);
    std::vector<vtkSmartPointer<vtkActor>> LoadScene(const std::string& filename);
};

#endif // SCENEMANAGER_H
