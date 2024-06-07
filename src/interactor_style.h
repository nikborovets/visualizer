#ifndef INTERACTOR_STYLE_H
#define INTERACTOR_STYLE_H

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vector>

class InteractorStyle : public vtkInteractorStyleTrackballCamera {
public:
    static InteractorStyle* New();
    vtkTypeMacro(InteractorStyle, vtkInteractorStyleTrackballCamera);

    void SetActors(const std::vector<vtkSmartPointer<vtkActor>>& actors) {
        this->actors = actors;
    }

    virtual void OnKeyDown() override;
    virtual void OnKeyUp() override;
    virtual void OnKeyPress() override;

    InteractorStyle();

private:
    std::vector<vtkSmartPointer<vtkActor>> actors;
    size_t currentActorIndex = 0;
    int currentColorIndex = 0;
    const double colors[6][3] = {
        {1.0, 0.0, 0.0}, // красный
        {0.0, 1.0, 0.0}, // зеленый
        {0.0, 0.0, 1.0}, // синий
        {1.0, 1.0, 0.0}, // желтый
        {0.0, 1.0, 1.0}, // голубой
        {1.0, 0.0, 1.0}  // фиолетовый
    };

    bool LeftKeyPressed;
    bool RightKeyPressed;
    bool UpKeyPressed;
    bool DownKeyPressed;
    bool AKeyPressed;
    bool ZKeyPressed;

    vtkSmartPointer<vtkActor> GetCurrentActor() {
        if (!actors.empty()) {
            return actors[currentActorIndex];
        }
        return nullptr;
    }
};

#endif // INTERACTOR_STYLE_H
