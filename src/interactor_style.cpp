#include "interactor_style.h"
#include <vtkObjectFactory.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkProperty.h>

vtkStandardNewMacro(InteractorStyle);

InteractorStyle::InteractorStyle() {
    this->LeftKeyPressed = false;
    this->RightKeyPressed = false;
    this->UpKeyPressed = false;
    this->DownKeyPressed = false;
    this->AKeyPressed = false;
    this->ZKeyPressed = false;
}

void InteractorStyle::OnKeyDown() {
    vtkRenderWindowInteractor *interactor = this->Interactor;
    std::string key = interactor->GetKeySym();

    if (key == "Left") {
        this->LeftKeyPressed = true;
    } else if (key == "Right") {
        this->RightKeyPressed = true;
    } else if (key == "Up") {
        this->UpKeyPressed = true;
    } else if (key == "Down") {
        this->DownKeyPressed = true;
    } else if (key == "a") {
        this->AKeyPressed = true;
    } else if (key == "z") {
        this->ZKeyPressed = true;
    }

    vtkInteractorStyleTrackballCamera::OnKeyDown();
}

void InteractorStyle::OnKeyUp() {
    vtkRenderWindowInteractor *interactor = this->Interactor;
    std::string key = interactor->GetKeySym();

    if (key == "Left") {
        this->LeftKeyPressed = false;
    } else if (key == "Right") {
        this->RightKeyPressed = false;
    } else if (key == "Up") {
        this->UpKeyPressed = false;
    } else if (key == "Down") {
        this->DownKeyPressed = false;
    } else if (key == "a") {
        this->AKeyPressed = false;
    } else if (key == "z") {
        this->ZKeyPressed = false;
    }

    vtkInteractorStyleTrackballCamera::OnKeyUp();
}

void InteractorStyle::OnKeyPress() {
    vtkRenderWindowInteractor *interactor = this->Interactor;
    std::string key = interactor->GetKeySym();

    vtkSmartPointer<vtkActor> currentActor = actors[currentActorIndex];

    // Проверяем комбинации нажатых клавиш и обновляем позицию актера
    double x = 0.0, y = 0.0, z = 0.0;
    if (this->LeftKeyPressed) {
        x -= 5.0;
    }
    if (this->RightKeyPressed) {
        x += 5.0;
    }
    if (this->UpKeyPressed) {
        y += 5.0;
    }
    if (this->DownKeyPressed) {
        y -= 5.0;
    }
    if (this->AKeyPressed) {
        z += 5.0;
    }
    if (this->ZKeyPressed) {
        z -= 5.0;
    }
    currentActor->AddPosition(x, y, z);

    if (key == "c") {
        currentColorIndex = (currentColorIndex + 1) % 6;
        double color[3] = {colors[currentColorIndex][0], colors[currentColorIndex][1], colors[currentColorIndex][2]};
        currentActor->GetProperty()->SetColor(color);
    }
    if (key == "Tab") {
        currentActorIndex = (currentActorIndex + 1) % actors.size();
    }
    interactor->GetRenderWindow()->Render();
}
